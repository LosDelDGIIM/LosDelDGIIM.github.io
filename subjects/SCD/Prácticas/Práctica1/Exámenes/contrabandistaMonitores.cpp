/**
 * @file contrabandistaMintores.cpp
 * @author Arturo Olivares Martos
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./contrabandista.md.
 * 
 * Esta resolución es empleando monitores
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica1/Exámenes/contrabandista.md)
 */

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <vector>
#include "../../Práctica1/Código/scd.h"

using namespace std ;
using namespace scd ;

// numero de fumadores 
const int num_fumadores = 3 ;

// Mutex cout
mutex mtx_cout;


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
   mtx_cout.lock();
      cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;
   mtx_cout.unlock();

   // espera bloqueada un tiempo igual a 'duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   mtx_cout.lock();
      cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;
   mtx_cout.unlock();

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
   mtx_cout.lock();
      cout  << "* Fumador " << num_fumador << ":"
            << " EMPIEZA a enviar un cigarro (" << duracion_envio.count() << " ms)" << endl;
   mtx_cout.unlock();

   // Espera bloqueada un tiempo igual a 'duracion_envio' milisegundos
   this_thread::sleep_for( duracion_envio );

   // Informa de que ha terminado de fumar
   mtx_cout.lock();
      cout  << "* Fumador " << num_fumador << ":"
            << " TERMINA de enviar el cigarro." << endl;
   mtx_cout.unlock();
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


class Estanco : public HoareMonitor{
   private:
      static const int VACIO = -1;

      int mostrador;    // Indica el ingrediente que hay en el mostrador. -1=No hay ingrediente
      CondVar ingr_no_disponible[num_fumadores];
      CondVar mostrador_lleno;

   public:
      Estanco();
      void ponerIngrediente(int i);
      void obtenerIngrediente(int i);
      void esperarRecogidaIngrediente();
};

/**
 * @brief Constructor de la clase Estanco
 * 
 * Inicializa el mostrador a -1, ya que no hay ningún ingrediente en el mostrador
 */
Estanco::Estanco(){
   mostrador = VACIO;
   for (int i=0; i<num_fumadores; ++i)
      ingr_no_disponible[i] = newCondVar();
   mostrador_lleno = newCondVar();
}

/**
 * @brief Función que pone un ingrediente en el mostrador
 * 
 * @param i Ingrediente a poner
 */
void Estanco::ponerIngrediente(int i){
   mostrador = i;
   ingr_no_disponible[i].signal();
}

/**
 * @brief Función que obtiene un ingrediente del mostrador
 * 
 * @param i Ingrediente a obtener
 */
void Estanco::obtenerIngrediente(int i){
   if (mostrador != i)
      ingr_no_disponible[i].wait();

   // Lo cogemos, y avisamos al estanquero
   mostrador = VACIO;
   mtx_cout.lock();
      cout << " * Fumador " << i << "  : Ingrediente retirado." << endl << flush;
   mtx_cout.unlock();
   mostrador_lleno.signal();
}

/**
 * @brief Función que espera a que se recoja un ingrediente
 */
void Estanco::esperarRecogidaIngrediente(){
   if (mostrador != VACIO)
      mostrador_lleno.wait();
}


#define FIFO

/**
 * @brief Clase para monitor buffer, semántica SC, múltiples productores/consumidores.
 * 
 * @note Funciona para versión LIFO o FIFO, depende del define LIFO o FIFO.
 */
class Buffer : public HoareMonitor{
 private:
 static const int           // constantes ('static' ya que no dependen de la instancia)
   num_celdas_total = 10;   //   núm. de entradas del buffer
 int                        // variables permanentes
   buffer[num_celdas_total],//   buffer de tamaño fijo, con los datos
   #ifdef LIFO
   primera_libre ;            //   indice de celda de la próxima inserción ( == número de celdas ocupadas)
   #elif defined FIFO
      primera_libre,          //   indice de celda de la próxima inserción
      primera_ocupada,        //   indice de celda de la próxima extracción
      ocupadas;               //   Número de celdas ocupadas
   #endif

 CondVar                    // colas condicion:
   buffer_vacio,            //  cola donde espera el consumidor (n>0)
   buffer_lleno ;           //  cola donde espera el productor  (n<num_celdas_total)

 public:                    // constructor y métodos públicos
   Buffer() ;             // constructor
   int  leer();                // extraer un valor (sentencia L) (consumidor)
   void escribir( int valor ); // insertar un valor (sentencia E) (productor)
} ;

/**
 * @brief Constructor de la clase Buffer.
 */
Buffer::Buffer(){
   #ifdef LIFO
      primera_libre = 0 ;
   #elif defined FIFO
      primera_libre   = 0;
      primera_ocupada = 0;
      ocupadas        = 0;
   #endif

   buffer_lleno   = newCondVar();
   buffer_vacio   = newCondVar();
}

/**
 * @brief Función que extrae un valor del buffer.
 */
int Buffer::leer(){

   // Esperamos a que haya algún valor en el buffer
   #ifdef LIFO
      // esperar bloqueado hasta que 0 < primera_libre
      if ( primera_libre == 0 ) buffer_vacio.wait();
   #elif defined FIFO
      // esperar bloqueado hasta que 0 < ocupadas
      if ( ocupadas == 0 ) buffer_vacio.wait();
   #endif

   // hacer la operación de lectura, actualizando estado del monitor
   int valor;
   #ifdef LIFO
      primera_libre-- ;
      valor = buffer[primera_libre] ;
   #elif defined FIFO
      valor = buffer[primera_ocupada] ;
      primera_ocupada++ ;
      primera_ocupada %= num_celdas_total ;
      ocupadas-- ;
   #endif
   
   // señalar al productor que hay un hueco libre, por si está esperando
   buffer_lleno.signal();

   // devolver valor
   return valor ;
}

/**
 * @brief Función que escribe un valor en el buffer.
 * 
 * @param valor Valor a escribir.
 */
void Buffer::escribir( int valor ){

   // esperar bloqueado hasta que haya hueco para escribir un valor
   #ifdef LIFO
      // esperar bloqueado hasta que primera_libre < num_celdas_total
      if ( primera_libre == num_celdas_total ) buffer_lleno.wait();
   #elif defined FIFO
      // esperar bloqueado hasta que primera_libre < num_celdas_total
      if ( ocupadas == num_celdas_total ) buffer_lleno.wait();
   #endif

   // Simulamos el envío
   enviar_cigarro(valor);

   // hacer la operación de inserción, actualizando estado del monitor
   #ifdef LIFO
      buffer[primera_libre] = valor ;
      primera_libre++ ;
   #elif defined FIFO
      buffer[primera_libre] = valor ;
      primera_libre++ ;
      primera_libre %= num_celdas_total ;
      ocupadas++ ;
   #endif

   // señalar al consumidor que ya hay una celda ocupada (por si esta esperando)
   buffer_vacio.signal();
}


//----------------------------------------------------------------------
/**
 * @brief Función que ejecuta la hebra del estanquero
 * 
 * @param monitor Monitor del estanco
 */
void funcion_hebra_estanquero(MRef<Estanco> monitor){
   int num_ingr_producido;

   while(true){
      num_ingr_producido = producir_ingrediente();
      monitor->esperarRecogidaIngrediente();

      mtx_cout.lock();
         cout << " Estanquero : Ingrediente " << num_ingr_producido << " puesto." << endl << flush;
      mtx_cout.unlock();
      monitor->ponerIngrediente(num_ingr_producido);
   }
}

/**
 * @brief Función que ejecuta la hebra de un fumador
 * 
 * @param num_fumador Número del fumador
 * @param monitor Monitor del estanco
 * @param buffer Buffer de cigarros
 */
void  funcion_hebra_fumador( int num_fumador, MRef<Estanco> monitor, MRef<Buffer> buffer ){
   
   while (true){
      monitor->obtenerIngrediente(num_fumador);
      buffer->escribir(num_fumador);
   }
}



/**
 * @brief Función que simula la hebra del contrabandista.
 * 
 * @param buffer Buffer de cigarros
 */
void funcion_hebra_contrabandista(MRef<Buffer> buffer){
   // Registra cuántos cigarros aporta cada fumador
   int origen_cigarros[num_fumadores]={0};

   // Número de extracciones consecutivas antes de informar
   const int extracciones_consecutivas = 4;

   // Número de extracciones realizadas desde que se inició la hebra
   int num_extracciones = 0;
   
   while (true){
      dormir();   // El contrabandista duerme. Tiempo aleatorio


      // Retira un cigarro del buzon
      int origen = buffer->leer();

      // Informa que ha retirado un cigarro
      mtx_cout.lock();
         cout  << "- Contrabandista:"
               << " RETIRA cigarro de fumador " << origen << "." << endl;
      mtx_cout.unlock();

      // Registra el origen del cigarro
      origen_cigarros[origen]++;
      num_extracciones++;

      // Si ha llegado a las extracciones consecutivas, informa de los orígenes
      if (num_extracciones%extracciones_consecutivas == 0){
         mtx_cout.lock();
            cout << endl;
            cout << "Contrabandista: " << num_extracciones << " extracigarros extraídos." << endl;
            cout << "- Origenes de los cigarros: " << endl;
            for (int i=0; i<num_fumadores; i++)
               cout << "\t- Fumador " << i << ": " << origen_cigarros[i] << " cigarros." << endl;
            cout << endl << endl << endl << flush;
         mtx_cout.unlock();
      }
   }
   
}

//----------------------------------------------------------------------
int main(){

   MRef<Estanco> monitor = Create<Estanco>();
   MRef<Buffer> buffer = Create<Buffer>();
   
   thread hebra_estanquero(funcion_hebra_estanquero, monitor);
   thread hebra_contrabandista(funcion_hebra_contrabandista, buffer);
   thread hebra_fumador[num_fumadores];

   for (int i=0; i<num_fumadores; ++i)
      hebra_fumador[i]=thread(funcion_hebra_fumador, i, monitor, buffer);

   // Es necesario poner un join para que el main no termine antes que las hebras
   hebra_estanquero.join();
   hebra_contrabandista.join();
   for (int i=0; i<num_fumadores; ++i)
      hebra_fumador[i].join();

   return 0;
}
