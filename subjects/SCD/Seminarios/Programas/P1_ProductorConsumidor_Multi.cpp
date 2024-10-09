#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

//**********************************************************************
// Variables globales
const unsigned 
   num_items = 500 ,   // número de items
	tam_vec   = 5 ,   // tamaño del buffer
   num_productores = 10, // número de productores
   num_consumidores = 20; // número de consumidores
unsigned  
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha consumido.
   siguiente_dato       = 0 ;  // siguiente dato a producir en 'producir_dato' (solo se usa ahí)

// Semáforos usados para controlar la sincronización
// - espera_consumidor: indica cuántos valores hay disponibles para consumir.
// - espera_productor: indica cuántos huecos hay disponibles para producir.
Semaphore espera_consumidor = 0;
Semaphore espera_productor = tam_vec;

// Mutex necesario para Exclusión Mutua
// En LIFO, primera_libre es compartida, necesitamos un mutex para protegerla.
mutex mtx_lifo;
// En FIFO, como hay muchos productores y consumidores, necesitamos un mutex para proteger la variable de condición.
mutex mtx_fifo_esc;
mutex mtx_fifo_lect;
// Para que no se entrelacen los couts
mutex mtx_cout;


// Variables para el buffer según estructura LIFO y FIFO
#define FIFO
#ifdef LIFO
   int vec[tam_vec];
   int primera_libre = 0;
#elif defined FIFO
   int vec[tam_vec];
   int primera_libre = 0;
   int ultima_libre = 0;
#endif


/**
 * @brief Función que simula la producción de un dato.
 * 
 * @param id_productor Identificador del productor.
 * @param n Posición del dato que se ha de producir.
 * 
 * @return unsigned Dato producido.
 */
unsigned producir_dato(int id_productor, int n){
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = id_productor * num_items/num_productores + n;
   cont_prod[dato_producido] ++ ;
   mtx_cout.lock();
      cout << "Productor " << id_productor << " produce: " << dato_producido << endl << flush ;
   mtx_cout.unlock();
   return dato_producido ;
}

/**
 * @brief Función que simula el consumo de un dato.
 * 
 * @param dato Dato a consumir.
 * @param id_consumidor Identificador del consumidor.
 */
void consumir_dato( int id_consumidor, unsigned dato ){
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx_cout.lock();
      cout << "\t\t\t\t\tConsumidor " << id_consumidor << " consume: " << dato << endl ;
   mtx_cout.unlock();
}


/**
 * @brief Función que comprueba los contadores de producción y consumo.
 */
void test_contadores(){
   bool ok = true ;
   cout << "comprobando contadores ...." << endl ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

/**
 * @brief Función que simula la hebra productora.
 * @param productor_id Identificador del productor.
 */
void  funcion_hebra_productora(int productor_id){
   int items_por_productor = num_items/num_productores;
   for( unsigned i = 0 ; i < items_por_productor ; i++ ){
      // No esperamos, ya que se perdería concurrencia
      int dato = producir_dato(productor_id, i);

      // Comprobamos que se puede producir
      sem_wait(espera_productor);
      #ifdef LIFO
         mtx_lifo.lock();
            vec[primera_libre++] = dato;
         mtx_lifo.unlock();
      #elif defined FIFO
         mtx_fifo_esc.lock();
            vec[ultima_libre++] = dato;
            ultima_libre %= tam_vec;
         mtx_fifo_esc.unlock();
      #endif
      sem_signal(espera_consumidor);
   }
}

//----------------------------------------------------------------------

/**
 * @brief Función que simula la hebra consumidora.
 * 
 * @param consumidor_id Identificador del consumidor.
 */
void funcion_hebra_consumidora(int consumidor_id){
   int items_por_consumidor = num_items/num_consumidores;
   for( unsigned i = 0 ; i < items_por_consumidor ; i++ ){
      int dato = 0;
      sem_wait(espera_consumidor);
      #ifdef LIFO
         mtx_lifo.lock();
            dato = vec[--primera_libre];
         mtx_lifo.unlock();
      #elif defined FIFO
         mtx_fifo_lect.lock();
            dato = vec[primera_libre++];
            primera_libre %= tam_vec;
         mtx_fifo_lect.unlock();
      #endif
      sem_signal(espera_productor);

      consumir_dato( consumidor_id, dato ) ;
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO o FIFO ?)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora[num_productores];
   thread hebra_consumidora[num_consumidores];

   for(int i = 0; i < num_productores; i++)
      hebra_productora[i] = thread(funcion_hebra_productora, i);
   for(int i = 0; i < num_consumidores; i++)
      hebra_consumidora[i] = thread(funcion_hebra_consumidora, i);


   for(int i = 0; i < num_productores; i++)
      hebra_productora[i].join();
   for (int i = 0; i < num_consumidores; i++)
      hebra_consumidora[i].join();

   test_contadores();
}
