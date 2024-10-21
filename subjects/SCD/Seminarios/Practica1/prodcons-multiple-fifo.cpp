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
   num_items = 100 ,   // número de items
    num_prod = 5,
    num_cons = 5,
    num_items_prod = num_items / num_prod,
    num_items_cons = num_items / num_cons,
	tam_vec   = 10 ;   // tamaño del buffer
unsigned  
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha consumido.
   siguiente_dato       = 0 ;  // siguiente dato a producir en 'producir_dato' (solo se usa ahí)

int buffer[tam_vec];

Semaphore sem_prod = tam_vec, sem_cons = 0;
mutex cer_prod, cer_cons;
int i_prod = 0, i_cons = 0;

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

unsigned producir_dato()
{
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = siguiente_dato ;
   siguiente_dato++ ;
   cont_prod[dato_producido] ++ ;
   cout << "producido: " << dato_producido << endl << flush ;
   return dato_producido ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
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

//----------------------------------------------------------------------

int inc(int i){
    if (i == tam_vec - 1) return 0;
    else return i + 1;
}

//----------------------------------------------------------------------

void  funcion_hebra_productora(  )
{
   int dato;

   for( unsigned i = 0 ; i < num_items_prod ; i++ )
   {
      dato = producir_dato() ;

      sem_wait(sem_prod);
      cer_prod.lock();
      cout << "Escrito " << dato << endl;

      buffer[i_prod] = dato;
      i_prod = inc(i_prod);

      cer_prod.unlock();
      sem_signal(sem_cons);
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(  )
{
   int dato;

   for( unsigned i = 0 ; i < num_items_cons ; i++ )
   {

       sem_wait(sem_cons);
       cer_cons.lock();

       dato = buffer[i_cons];
       i_cons = inc(i_cons);
        cout << "                  leido: " << dato << endl ;

       cer_cons.unlock();
       sem_signal(sem_prod);

      consumir_dato( dato ) ;
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO o FIFO ?)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;

   thread prods[num_prod];
   thread cons[num_cons];

   for(int i = 0; i < num_prod; i++){
       prods[i] = thread(funcion_hebra_productora);
   }
   for(int i = 0; i < num_cons; i++){
       cons[i] = thread(funcion_hebra_consumidora);
   }

   for(int i = 0; i < num_prod; i++){
       prods[i].join();
   }
   for(int i = 0; i < num_cons; i++){
       cons[i].join();
   }

   test_contadores();
}
