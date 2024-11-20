#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <vector>
#include "scd.h"

using namespace std ;
using namespace scd ;

constexpr int          num_fumadores   = 3 ; 
Semaphore              mostrador_libre = 1;  
Semaphore ingrediente_en_mostrador[3]={0,0,0} ; 

//-------------------------------------------------------------------------
int producir_ingrediente()
{
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );
   this_thread::sleep_for( duracion_produ );
   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;
   return num_ingrediente ;
}

//----------------------------------------------------------------------
void funcion_hebra_estanquero(  )
{    
   while (true)
   {
      int num_fumador = producir_ingrediente();
      mostrador_libre.sem_wait( ) ;
      cout << "Estanquero : PONE ingrediente a fumador " 
              << num_fumador << "." << endl ;
      ingrediente_en_mostrador[ num_fumador ].sem_signal(  );      
   }
}

//-------------------------------------------------------------------------
void fumar( int num_fumador )
{
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );
   this_thread::sleep_for( duracion_fumar );
   cout << "                    Fumador " << num_fumador << ": TERMINA FUMAR" << endl<<flush;
}

//----------------------------------------------------------------------
void  funcion_hebra_fumador( int num_fumador )
{  while( true )
   {  ingrediente_en_mostrador[num_fumador].sem_wait(  );
      cout << "                    Fumador " << num_fumador << "  : OBTIENE ING" << endl;
      mostrador_libre.sem_signal(  );  
      fumar( num_fumador);
   }
}

//----------------------------------------------------------------------
// FUNCION MAIN
//----------------------------------------------------------------------

int main()
{
   thread hebra_estanquero( funcion_hebra_estanquero ),
          hebra_fumador[ num_fumadores ];

   for( unsigned i = 0 ; i < num_fumadores ; i++ )
      hebra_fumador[i] = thread( funcion_hebra_fumador, i );


   hebra_estanquero.join();
   for( unsigned i = 0 ; i < num_fumadores ; i++ )
      hebra_fumador[i].join();
}
//----------------------------------------------------------------------
