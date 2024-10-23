/**
 * @file atrapar_corazones.cpp
 * @author Arturo Olivares Martos
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./atrapa_coracones.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica1/Exámenes/atrapa_corazones.md)
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

const int num_rondas = 10;    // Número de rondas
const int puntos_ronda = 5;   // Puntos que se ganan en cada ronda
const int num_jugadores = 4;  // Número de jugadores

int puntos[num_jugadores] = {0};    // Puntos de cada jugador

bool fin = false;   // Indica si se ha terminado el juego

mutex mtx_cout;     // Mutex para proteger la salida por pantalla

Semaphore corazon_disponible(0);    // Semáforo para saber si el corazón está disponible. 0=no disponible, 1=disponible
Semaphore puedo_generar(1);         // Semáforo para saber si se puede generar un corazón. 1=Si, 0=No
// Siempre se cumplirá que corazon_disponible+puedo_generar=1

/**
 * @brief Función que muestra los puntos de cada jugador
 */
void mostrar_puntos(){
   cout << "Puntos: ";
   for (int i=0; i<num_jugadores; ++i)
      cout << puntos[i] << " ";
   cout << endl << endl << endl << flush;
}

/**
 * @brief Función que ejecuta la hebra del generador
 */
void funcion_hebra_generador(){
   for (int i=0; i<num_rondas; ++i){
      // Esperamos a poder generar
      sem_wait(puedo_generar);

      // Genero
      mtx_cout.lock();
      cout << "Generador: Corazón visible" << endl << flush;
      mtx_cout.unlock();

      // Muestro que está visible
      sem_signal(corazon_disponible);
   }

   // Fin del juego
   sem_wait(puedo_generar);
   fin = true;
   for (int i=0; i<num_jugadores; ++i)
      corazon_disponible.sem_signal();
}

/**
 * @brief Función que ejecuta la hebra de un jugador
 * 
 * @param num_jugador Número del jugador
 */
void funcion_hebra_jugador(int num_jugador){
   
   while (!fin){

      sem_wait(corazon_disponible);
      if (!fin){ // Necesario comprobarlo. Por si se ha puesto fin=true mientras estaba bloqueado
         mtx_cout.lock();
         cout << "Jugador " << num_jugador << ": Corazón robado. Gana " << puntos_ronda << " puntos." << endl << flush;
         mtx_cout.unlock();

         // Se ha robado el corazón, se puede generar
         sem_signal(puedo_generar);

         // Sumo los puntos
         puntos[num_jugador] += puntos_ronda;

         // Muestro los puntos
         mtx_cout.lock();
         cout << "--- Fin Ronda ---" << endl << flush;
         mostrar_puntos();
         mtx_cout.unlock();
      }
   }
}

int main(){

   // Lanzamos hebra generadora y jugadores
   thread hebra_generador(funcion_hebra_generador);
   thread hebra_jugador[num_jugadores];
   for (int i=0; i<num_jugadores; ++i)
      hebra_jugador[i] = thread(funcion_hebra_jugador, i);

   // Esperamos a que terminen
   hebra_generador.join();
   for (int i=0; i<num_jugadores; ++i)
      hebra_jugador[i].join();

   // Mostramos los puntos finales
   mtx_cout.lock();
   cout << "--- FIN ---" << endl << flush;
   mostrar_puntos();
   mtx_cout.unlock();
}
