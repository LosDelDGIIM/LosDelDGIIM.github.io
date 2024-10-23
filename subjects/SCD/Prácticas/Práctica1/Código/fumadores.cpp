#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <vector>
#include "scd.h"

using namespace std ;
using namespace scd ;

// numero de fumadores 
const int num_fumadores = 3 ;

// Número de iteraciones del estanquero
const int num_items = 10;

// Compartida. Indica que ya se ha terminado de generar
bool fin=false;

// Semáforo para determinar si el ingrediente i está disponible. 0=no disponible, 1=disponible
vector<Semaphore> ingr_disponible;

// Semáforo para saber si el mostrador está vacío. 1=Vacío, 0=Lleno
Semaphore mostrador_vacio = 1;


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
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a 'duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

//----------------------------------------------------------------------
/**
 * @brief Función que ejecuta la hebra del estanquero
 */
void funcion_hebra_estanquero(){
   int num_ingr_producido;

   for (int i=0; i<num_items; ++i){
      num_ingr_producido = producir_ingrediente();
      mostrador_vacio.sem_wait();
      cout << i<< " Estanquero : Ingrediente " << num_ingr_producido << " puesto." << endl << flush;
      ingr_disponible[num_ingr_producido].sem_signal();
   }

   // Ya hemos terminado.
   // Hacemos un sem_wait a mostrador_vacío para asegurarnos de que se han cogido todos los ingredientes
   sem_wait(mostrador_vacio);
   fin = true;
   for (int i=0; i<num_fumadores; ++i){
      // Para desbloquear en el caso de que estuvieran esperando. No fumarán porque fin=true
      ingr_disponible[i].sem_signal();
      cout << "Fin Estanquero : Desbloqueamos al fumador " << i << "." << endl << flush;
   }
}

/**
 * @brief Función que simula la acción de fumar.
 * Tiene un retardo aleatorio de la hebra.
 * 
 * @param num_fumador Número del fumador
 */
void fumar( int num_fumador ){

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar
   cout << "Fumador " << num_fumador << "  :"
        << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a 'duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar
   cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
}

/**
 * @brief Función que ejecuta la hebra de un fumador
 * 
 * @param num_fumador Número del fumador
 */
void  funcion_hebra_fumador( int num_fumador ){
   while (!fin){

      ingr_disponible[num_fumador].sem_wait();

      if (!fin){ // Necesario comprobarlo. Por si se ha puesto fin=true mientras estaba bloqueado
         cout << "Fumador " << num_fumador << "  : Ingrediente retirado." << endl << flush;
         mostrador_vacio.sem_signal();
         fumar(num_fumador);
      }
   }
}

//----------------------------------------------------------------------
int main(){
   // Inicializamos los semáforos
   for (int i=0; i<num_fumadores; ++i)
      ingr_disponible.push_back(Semaphore(0));


   thread hebra_estanquero(funcion_hebra_estanquero);
   thread hebra_fumador[num_fumadores];

   for (int i=0; i<num_fumadores; ++i)
      hebra_fumador[i]=thread(funcion_hebra_fumador, i);

   // Es necesario poner un join para que el main no termine antes que las hebras
   hebra_estanquero.join();
   for (int i=0; i<num_fumadores; ++i)
      hebra_fumador[i].join();

   return 0;
}
