/**
 * @file contrabandista.cpp
 * @author Arturo Olivares Martos
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./contrabandista.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica1/Exámenes/contrabandista.md)
 */

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "../Código/scd.h"

using namespace std ;
using namespace scd ;

constexpr int num_fumadores = 2; // número de fumadores
Semaphore mostrador_libre = 1;   // 1 si el mostrador está libre, 0 si no
mutex mutex_cout;                // mutex que evita salidas por pantalla mezcladas
vector<Semaphore> ingrediente_en_mostrador; // vector de semáforos de fumadores

const int tam_buzon = 3;
int buzon[tam_buzon];
int primera_libre=0, primera_ocupada=0;   // Implementación FIFO del buffer

Semaphore ocupadas_buzon(0);       // Posiciones ocupadas en el buzon. 0=vacio
Semaphore libres_buzon(tam_buzon); // Posiciones libres en el buzon. tam_buzon=lleno

mutex mtx_buzon;  // Mutex para proteger el acceso al buzon.
                  // Como tan solo lee una hebra, para ese caso no es necesario.
                  // Lo usamos para proteger la escritura en el buzon.

//-------------------------------------------------------------------------
/**
 * @brief Función que simula la acción de producir un ingrediente
 * 
 * @return int Número de ingrediente producido
 */
int producir_ingrediente(){
   // calcular milisegundos aleatorios de duración de la acción de producción
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   mutex_cout.lock();
      cout << "Estanquero: empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;
   mutex_cout.unlock();

   // espera bloqueada un tiempo igual a 'duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   mutex_cout.lock();
      cout << "Estanquero: termina de producir ingrediente " << num_ingrediente << endl;
   mutex_cout.unlock();

   return num_ingrediente ;
}


/**
 * @brief Función que simula la acción de enviar un cigarro.
 * 
 * @param num_fumador Número del fumador.
 */
void enviar_cigarro(int num_fumador){

   // calcular milisegundos aleatorios de duración de la acción de enviar un cigarro
   chrono::milliseconds duracion_envio( aleatorio<20,200>() );

   // Informa de que comienza a enviar
   mutex_cout.lock();
      cout  << "* Fumador " << num_fumador << ":"
            << " EMPIEZA a enviar un cigarro (" << duracion_envio.count() << " ms)" << endl;
   mutex_cout.unlock();

   // Espera bloqueada un tiempo igual a 'duracion_envio' milisegundos
   this_thread::sleep_for( duracion_envio );

   // Informa de que ha terminado de fumar
   mutex_cout.lock();
      cout  << "* Fumador " << num_fumador << ":"
            << " TERMINA de enviar el cigarro." << endl;
   mutex_cout.unlock();
}


/**
 * @brief Función que simula la acción de dormir.
 */
void dormir(){

   // calcular milisegundos aleatorios de duración de la acción de dormir)
   chrono::milliseconds duracion_dormir( aleatorio<20,150>() );
   // informa de que comienza a dormir
   cout << "- Contrabandista:"
          << " EMPIEZA a dormir (" << duracion_dormir.count() << " ms)" << endl;
   // espera bloqueada un tiempo igual a ''duracion_dormir' milisegundos
   this_thread::sleep_for( duracion_dormir );
   // informa de que ha terminado de fumar
   cout << "- Contrabandista: TERMINA de dormir." << endl;
}



/**
 * @brief Función que simula la hebra del estanquero.
 */
void funcion_hebra_estanquero(){

   while (true){

      // selecciona aleatoriamente un fumador
      int num_fumador = producir_ingrediente();

      // esperar hasta mostrador libre
      mostrador_libre.sem_wait() ;

      // Informa del ingrediente depositado
      mutex_cout.lock();
         cout << "Estanquero: Ingrediente para el fumador " << num_fumador << " puesto." << endl ;
      mutex_cout.unlock();

      // Señala que hay ingrediente disponible para fumador 'num_fumador'
      ingrediente_en_mostrador[num_fumador].sem_signal();
   }
}



/**
 * @brief Función que simula la hebra de un fumador.
 * 
 * @param num_fumador Número del fumador.
 */
void  funcion_hebra_fumador(int num_fumador){
   
   while(true){ 
      
      // Fumador inicia obtención de ingrediente
      ingrediente_en_mostrador[num_fumador].sem_wait(  );
      mutex_cout.lock();
         cout << "* Fumador " << num_fumador << ": RETIRA ingrediente." << endl << flush;
      mutex_cout.unlock();
      mostrador_libre.sem_signal(  );

      // Enviamos al contrabandista el cigarro
      libres_buzon.sem_wait();
      enviar_cigarro(num_fumador);
      mtx_buzon.lock();
         buzon[primera_libre] = num_fumador;
         primera_libre = (primera_libre+1)%tam_buzon;
      mtx_buzon.unlock();
      ocupadas_buzon.sem_signal();
   }
}


/**
 * @brief Función que simula la hebra del contrabandista.
 */
void funcion_hebra_contrabandista(){
   // Registra cuántos cigarros aporta cada fumador
   int origen_cigarros[num_fumadores]={0};

   // Número de extracciones consecutivas antes de informar
   const int extracciones_consecutivas = 4;

   // Número de extracciones realizadas desde que se inició la hebra
   int num_extracciones = 0;
   
   while (true){
      dormir();   // El contrabandista duerme. Tiempo aleatorio

      // Si no hay cigarros en el buzon, espera
      ocupadas_buzon.sem_wait();

      // Retira un cigarro del buzon
      int origen = buzon[primera_ocupada];
      primera_ocupada = (primera_ocupada+1)%tam_buzon;
      libres_buzon.sem_signal();

      // Informa que ha retirado un cigarro
      mutex_cout.lock();
         cout  << "- Contrabandista:"
               << " RETIRA cigarro de fumador " << origen << "." << endl;
      mutex_cout.unlock();

      // Registra el origen del cigarro
      origen_cigarros[origen]++;
      num_extracciones++;

      // Si ha llegado a las extracciones consecutivas, informa de los orígenes
      if (num_extracciones%extracciones_consecutivas == 0){
         mutex_cout.lock();
            cout << endl;
            cout << "Contrabandista: " << num_extracciones << " extracigarros extraídos." << endl;
            cout << "- Origenes de los cigarros: " << endl;
            for (int i=0; i<num_fumadores; i++)
               cout << "\t- Fumador " << i << ": " << origen_cigarros[i] << " cigarros." << endl;
            cout << endl << endl << endl << flush;
         mutex_cout.unlock();
      }
   }
   
}





int main(){

   // Inicializamos los semáforos de los fumadores
   for (int i=0; i<num_fumadores; i++)
      ingrediente_en_mostrador.push_back(Semaphore(0));

   // Lanza Array de hebras fumadoras
   thread hebra_fumador[ num_fumadores ];
   for( unsigned long i = 0 ; i < num_fumadores ; i++ )
      hebra_fumador[i] = thread( funcion_hebra_fumador, i );
   // Lanza Hebra Estanquero
   thread hebra_estanquero( funcion_hebra_estanquero );
   // Lanza Hebra Contrabandista
   thread hebra_contrabandista( funcion_hebra_contrabandista );
   

   // Esperar finalización de hebras:
   hebra_estanquero.join();
   hebra_contrabandista.join();
   for( unsigned i = 0 ; i < num_fumadores ; i++ )
      hebra_fumador[i].join();

   return 0;
}
