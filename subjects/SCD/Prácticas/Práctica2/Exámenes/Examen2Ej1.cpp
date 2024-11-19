/**
 * @file Examen2_Ej1.cpp
 * @author Arturo Olivares Martos
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./Examen2.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica2/Exámenes/Examen2.md)
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
const int NUM_FUMADORES = 3 ;

// Número de iteraciones del estanquero
const int NUM_ITMS = 10;

// Capacidad del mostrador. @PRE <= NUM_FUMADORES
const int CAPACIDAD = 2;

// Compartida. Indica que ya se ha terminado de generar
bool fin=false;

// Semáforo para determinar si el ingrediente i está disponible. 0=no disponible, 1=disponible
vector<Semaphore> ingr_disponible;

// Semáforo para saber si el mostrador está vacío. mostrador_libres=i -> i posiciones libres
Semaphore mostrador_libres = CAPACIDAD;

// Mutex para la salida por pantalla
mutex mtx;


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

   const int num_ingrediente = aleatorio<0,NUM_FUMADORES-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

//----------------------------------------------------------------------
/**
 * @brief Función que ejecuta la hebra del estanquero
 */
void funcion_hebra_estanquero(){
   int num_ingr_producido[CAPACIDAD];

   for (int i=0; i<NUM_ITMS; ++i){

      // Producimos los ingredientes
      for (int j=0; j<CAPACIDAD; ++j){
         
         bool encontrado = false;
         while (!encontrado){
               // Producimos hasta que sea distintos a todos los anteriores (j-1, j-2, ... , 0)
               num_ingr_producido[j] = producir_ingrediente();

               // Compruebo si es distinto a todos los anteriores
               bool repetido = false;
               for (int k=0; k<j && !repetido; ++k)
                  repetido = (num_ingr_producido[j] == num_ingr_producido[k]);

               encontrado = !repetido;
            }
      }
      mtx.lock();
         cout << "Estanquero : Todos los ingredientes producidos (";
         for (int k=0; k<CAPACIDAD; ++k)
            cout << num_ingr_producido[k] << " ";
         cout << ")" << endl << flush;
      mtx.unlock();

      // Esperamos a que el mostrador esté vacío
      for (int k=0; k<CAPACIDAD; ++k)
         mostrador_libres.sem_wait();

      // Ponemos los ingredientes en el mostrador
      for (int k=0; k<CAPACIDAD; ++k)
         ingr_disponible[num_ingr_producido[k]].sem_signal();
      
      // Avisamos de que hemos puesto los ingrediente
      mtx.lock();
         cout << "Estanquero : Ingredientes puestos." << endl << flush;
      mtx.unlock();
   } // for i

   // Ya hemos terminado.
   // Hacemos un sem_wait a mostrador_vacío para asegurarnos de que se han cogido todos los ingredientes
   for (int k=0; k<CAPACIDAD; ++k)
      mostrador_libres.sem_wait();
   fin = true;
   for (int i=0; i<NUM_FUMADORES; ++i){
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
         mostrador_libres.sem_signal();
         fumar(num_fumador);
      }
   }
}

//----------------------------------------------------------------------
int main(){
   // Inicializamos los semáforos
   for (int i=0; i<NUM_FUMADORES; ++i)
      ingr_disponible.push_back(Semaphore(0));


   thread hebra_estanquero(funcion_hebra_estanquero);
   thread hebra_fumador[NUM_FUMADORES];

   for (int i=0; i<NUM_FUMADORES; ++i)
      hebra_fumador[i]=thread(funcion_hebra_fumador, i);

   // Es necesario poner un join para que el main no termine antes que las hebras
   hebra_estanquero.join();
   for (int i=0; i<NUM_FUMADORES; ++i)
      hebra_fumador[i].join();

   return 0;
}
