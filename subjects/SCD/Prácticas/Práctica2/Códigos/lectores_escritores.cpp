/**
 * @file lectores_escritores.cpp
 * @brief Problema de los lectores-escritores con monitores de Hoare
 * 
 * @author Arturo Olivares Martos
 */

#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include <chrono>
#include "../../Práctica1/Código/scd.h"

using namespace std ;
using namespace scd ;

#define No_INANICION

#ifdef No_INANICION
    const int MAX_LEC = 5;    // Número máximo de lectores consecutivos
#endif

/**
 * @brief Clase que controla el acceso a un recurso compartido por varios lectores y escritores
 */
class MonLecEsc : public HoareMonitor{
  private:
    int lec_dentro;             // Número de lectores dentro
    bool esc_dentro;            // ¿Hay un escritor dentro?
    CondVar cola_lec, cola_esc;

    #ifdef No_INANICION
        int cuanto_leo;          // Número de lectores que pueden leer todavía, para evitar inanición de escritores
    #endif

  public:
    MonLecEsc();
    void inicia_lectura();
    void termina_lectura();
    void inicia_escritura();
    void termina_escritura();
};

/**
 * @brief Constructor de la clase MonLecEsc
 */
MonLecEsc::MonLecEsc(){
    lec_dentro = 0;
    esc_dentro = false;
    cola_lec = newCondVar();
    cola_esc = newCondVar();

    #ifdef No_INANICION
        cuanto_leo = MAX_LEC;
    #endif
}

/**
 * @brief Método que inicia la lectura
 */
void MonLecEsc::inicia_lectura(){

    // Controlamos si puede entrar a leer o no
    #ifdef No_INANICION
        if(esc_dentro || cuanto_leo == 0)
            cola_lec.wait();
    #else
        if(esc_dentro)
            cola_lec.wait();
    #endif

    // Controlamos que hay un lector más
    lec_dentro++;

    
    // Tan solo limitamos si hay escritores esperando
    #ifdef No_INANICION
        if(!cola_esc.empty())
            cuanto_leo--;
    #endif

    // Despertamos al siguiente lector
    #ifdef No_INANICION
        if(cuanto_leo > 0)
            cola_lec.signal();
    #else
        cola_lec.signal();
    #endif
}

/**
 * @brief Método que termina la lectura
 */
void MonLecEsc::termina_lectura(){
    lec_dentro--;

    if(lec_dentro == 0)
        cola_esc.signal();
}

/**
 * @brief Método que inicia la escritura
 */
void MonLecEsc::inicia_escritura(){
    if(esc_dentro || lec_dentro > 0){
        cout << "\t\t-Escritor espera" << endl;
        cola_esc.wait();
    }

    esc_dentro = true;
    
    // Ya ha entrado un escritor. Reseteamos el contador de límite de lectores
    #ifdef No_INANICION
        cuanto_leo = MAX_LEC;
    #endif
}

/**
 * @brief Método que termina la escritura
 */
void MonLecEsc::termina_escritura(){
    esc_dentro = false;

    // Se ha establecido una prioridad.
    // Si hay lectores esperando, se despierta a uno antes que a un escritor
    if(!cola_lec.empty()){
        cola_lec.signal();
    }else{
        cola_esc.signal();
    }
}


/**
 * @brief Función que simula un tiempo de espera.
 * 
 * @param escritor Indica si el hilo que llama a la función es un escritor
 */
void duerme(bool escritor){
    if(escritor){
       this_thread::sleep_for(chrono::milliseconds(aleatorio<2000,2000>()));
    }else{
       this_thread::sleep_for(chrono::milliseconds(aleatorio<100,1000>()));
    }
}

mutex m_cout;
/**
 * @brief Función que imprime un mensaje en pantalla de forma exclusiva
 * 
 * @param s Mensaje a imprimir
 */
void imprime(const string& s){
    m_cout.lock();
        cout << s << endl;
    m_cout.unlock();
}


/**
 * @brief Función que simula la acción de un lector
 * 
 * @param monitor Monitor que controla el acceso al recurso compartido
 * @param id Identificador del lector
 */
void lector(MRef<MonLecEsc> monitor, int id){
    while(true){
        monitor->inicia_lectura();
        imprime("Lector nº " + to_string(id) + " entra a leer");
        duerme(false);
        imprime("-Lector nº " + to_string(id) + " sale de leer");
        monitor->termina_lectura();
        duerme(false);
    }
}

/**
 * @brief Función que simula la acción de un escritor
 * 
 * @param monitor Monitor que controla el acceso al recurso compartido
 * @param id Identificador del escritor
 */
void escritor(MRef<MonLecEsc> monitor, int id){
    while(true){
        monitor->inicia_escritura();
        imprime("Escritor nº" + to_string(id) + " entra a escribir");
        duerme(true);
        imprime("Escritor nº" + to_string(id) + " sale de escribir");
        monitor->termina_escritura();
    }
}

// --------------------------------------------------

int main(int argc, char** argv){
    int num_lectores = 10;
    int num_escritores = 3;

    thread lectores[num_lectores], escritores[num_escritores];
    MRef<MonLecEsc> monitor = Create<MonLecEsc>();

    for(int i = 0; i < num_lectores; i++)
        lectores[i] = thread(lector, monitor, i);
    for(int i = 0; i < num_escritores; i++)
        escritores[i] = thread(escritor, monitor, i);

    
    for(int i = 0; i < num_lectores; i++)
        lectores[i].join();
    for(int i = 0; i < num_escritores; i++)
        escritores[i].join();
    return 0;
}
