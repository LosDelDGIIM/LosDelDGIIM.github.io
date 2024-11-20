/**
 * @file contrabandista.cpp
 * @author Arturo Olivares Martos
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./hebraSanitaria.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica1/Exámenes/hebraSanitaria.md)
 */

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <vector>
#include "../Código/scd.h"

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


Semaphore sanitaria_libre = 0;   // Semáforo para controlar la hebra sanitaria. 1=Activada, 0=Desactivada
Semaphore poder_fumar = 0;       // Semáforo para controlar si un fumador vicioso puede fumar. 1=Si, 0=No.
                                 // Inicialmente a 0 para que no fume antes de que la sanitaria le libere
int cigarrillos[num_fumadores] = {0}; // Número de cigarrillos consecutivos fumados por cada fumador
int fumador_vicioso = -1; // Número del fumador vicioso
const int LIM_CIGARRILLOS = 5; // Número de cigarrillos consecutivos para ser considerado vicioso



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
   sanitaria_libre.sem_signal();
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

         if (cigarrillos[num_fumador] == LIM_CIGARRILLOS){
            cout << "Fumador " << num_fumador << "  : Llamando a la hebra sanitaria." << endl << flush;
            fumador_vicioso = num_fumador;
            sanitaria_libre.sem_signal();
            poder_fumar.sem_wait();
            cout << "Soy el fumador " << num_fumador << " y me han llamado vicioso." << endl << flush;
            cigarrillos[num_fumador] = 0;
         }

         cout << "Fumador " << num_fumador << "  : Ingrediente retirado." << endl << flush;
         mostrador_vacio.sem_signal();

         fumar(num_fumador);
         cigarrillos[num_fumador]++;
      }
   }
}

/**
 * @brief Función que ejecuta la hebra sanitaria
 * 
 * Llama a la hebra sanitaria cuando un fumador ha fumado 5 cigarrillos consecutivos
 */
void funcion_hebra_sanitaria(){
   while (!fin){
      sanitaria_libre.sem_wait();
      if (!fin){
         cout << "Sanitaria : Fumar mata: ya lo sabes fumador " << fumador_vicioso << "." << endl << flush;
         poder_fumar.sem_signal();
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
   thread hebra_sanitaria(funcion_hebra_sanitaria);

   for (int i=0; i<num_fumadores; ++i)
      hebra_fumador[i]=thread(funcion_hebra_fumador, i);

   // Es necesario poner un join para que el main no termine antes que las hebras
   hebra_estanquero.join();
   hebra_sanitaria.join();
   for (int i=0; i<num_fumadores; ++i)
      hebra_fumador[i].join();

   return 0;
}
