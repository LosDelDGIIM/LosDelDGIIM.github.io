/**
 * @file Examen3_Ej1.cpp
 * @author Arturo Olivares Martos
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./Examen3.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica2/Exámenes/Examen3.md)
 */
#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <vector>
#include "../../Práctica1/Código/scd.h"

using namespace std ;
using namespace scd ;

constexpr int          num_fumadores   = 3 ; 
Semaphore              mostrador_libre = 1;  
Semaphore ingrediente_en_mostrador[3]={0,0,0} ;
Semaphore dormidos[3] = {0,0,0} ;      // Semáforo para dormir a los fumadores. 0=Duérmete, 1=Despierta

int ingredientes_proporcionados[3] = {0,0,0} ;  // Número de ingredientes proporcionados a cada fumador
const int ITER_DORMIR = 3; // Número de la iteración en la que debe dormirse el fumador

const int NUMS_INFORMADORA = 2; // Número de hebras a las que la informadora espera
const int IDS_INFORMADORA[NUMS_INFORMADORA] = {1,2}; // Identificadores de las hebras a las que la hebra informadora debe esperar
Semaphore sem_informadora = 0; // Semáforo para que la informadora espere a las hebras. 0=Espera, 1=Despierta

/**
 * @brief Produce un ingrediente aleatorio
 */
int producir_ingrediente(){
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );
   this_thread::sleep_for( duracion_produ );
   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;
   return num_ingrediente ;
}


/**
 * @brief Fuma un tiempo aleatorio
 * 
 * @param num_fumador Número del fumador
 */
void fumar( int num_fumador ){
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );
   this_thread::sleep_for( duracion_fumar );
   cout << "                    Fumador " << num_fumador << ": TERMINA FUMAR" << endl<<flush;
}

/**
 * @brief Función que simula la hebra del estanquero
 */
void funcion_hebra_estanquero(  ){    

   while (true){
      int num_fumador = producir_ingrediente();
      mostrador_libre.sem_wait( ) ;
      cout  << "Estanquero : PONE ingrediente a fumador " 
            << num_fumador << "." << endl ;
      
      // Actualizamos el número de ingredientes proporcionados antes del signal que avisa al fumador de que tiene un ingrediente
      //       para que el fumador reciba este dato actualizado
      ingredientes_proporcionados[num_fumador]++;
      
      // Si el fumador va a estar formido, tengo que despertarlo
      if (ingredientes_proporcionados[num_fumador] == ITER_DORMIR+1)
         dormidos[num_fumador].sem_signal();


      // Avisamos de que hay un ingrediente en el mostrador
      ingrediente_en_mostrador[ num_fumador ].sem_signal(  );
   }
}

/**
 * @brief Función que simula la hebra de un fumador
 * 
 * @param num_fumador Número del fumador
 */
void  funcion_hebra_fumador( int num_fumador )
{  
   int num_iter;  // Número de iteración. Para saber si debe dormir o no
   while( true ){
      
      // Espera a obtener un ingrediente
      ingrediente_en_mostrador[num_fumador].sem_wait(  );
      cout << "                    Fumador " << num_fumador << "  : OBTIENE ING" << endl;
      
      // Antes del signal al estanquero, obtenemos el número de ingredientes que se nos han proporcionado
      // Al ser antes del signal, no se produce condición de carrera
      num_iter = ingredientes_proporcionados[num_fumador];
      mostrador_libre.sem_signal(  ); 

      // Si es la iteración en la que debe dormir, se duerme
      if(num_iter == ITER_DORMIR){
         cout << "                    Fumador " << num_fumador << "  : Me duermo" << endl;
         dormidos[num_fumador].sem_wait();
         cout << "                    Fumador " << num_fumador << "  : Me despierto" << endl;

         // Si está en IDS_INFORMADORA, avisa a la informadora
         bool encontrado=false;
         for (int i=0; i<NUMS_INFORMADORA && !encontrado; i++){

            // Está en IDS_INFORMADORA, por lo que debe avisar a la informadora
            if (IDS_INFORMADORA[i] == num_fumador){
               sem_informadora.sem_signal();
               encontrado=true;
            }
         }  // for de búsqueda de IDS_INFORMADORA
      
      } // if de dormir

      else // Si no debe dormir, fuma
         fumar( num_fumador);
      
   }  // while True
}

/**
 * @brief Función que simula la hebra de la informadora
 */
void funcion_hebra_informadora(){

   // Esperamos a todas las hebras que están en IDS_INFORMADORA
   for (int num_esperada=0; num_esperada<NUMS_INFORMADORA; num_esperada++){
      sem_informadora.sem_wait();
      //cout << "* Informadora: Hebra " << IDS_INFORMADORA[num_esperada] << " ha despertado." << endl;
   }
   
   cout << "*****************LAS FUMADORAS ";
   for (int i=0; i<NUMS_INFORMADORA; i++){
      cout << IDS_INFORMADORA[i];
      if (i != NUMS_INFORMADORA-1){
         cout << ", ";
      }
   }
   cout << " HAN DESCANSADO.*******************" << endl;


   // Podría poner el siguiente COUT, pero he dejado el anterior para que sea generalizado
   // cout << "*****************LAS FUMADORAS 1 Y 2 HAN DESCANSADO.*******************" << endl;

}

//----------------------------------------------------------------------
// FUNCION MAIN
//----------------------------------------------------------------------

int main(){
   thread   hebra_estanquero( funcion_hebra_estanquero ),
            hebra_informadora12( funcion_hebra_informadora ),
            hebra_fumador[ num_fumadores ];

   for( unsigned i = 0 ; i < num_fumadores ; i++ )
      hebra_fumador[i] = thread( funcion_hebra_fumador, i );


   hebra_estanquero.join();
   hebra_informadora12.join();
   for( unsigned i = 0 ; i < num_fumadores ; i++ )
      hebra_fumador[i].join();

   return 0;
}
