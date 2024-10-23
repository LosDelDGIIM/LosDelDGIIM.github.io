#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std ;
using namespace scd ;

constexpr int          num_fumadores   = 2 ;  // número de fumadores
Semaphore              mostrador_libre = 1;   // 1 si el mostrador está libre, 0 si no
mutex                  mutex_cout ; // mutex que evita salidas por pantalla mezcladas
Semaphore ingrediente_en_mostrador[2]={0,0} ; // vector de semáforos de fumadores



//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente
int producir_ingrediente()
{  
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );
      // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );
   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;
   return num_ingrediente ;
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar
void fumar( int num_fumador )
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );
   // informa de que comienza a fumar
    cout << "                 Fumador " << num_fumador << "  :"
          << " EMPIEZA a fumar (" << duracion_fumar.count() << " ms)" << endl;
   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );
   // informa de que ha terminado de fumar
    cout << "                 Fumador " << num_fumador << "  : TERMINA de fumar." << endl;
}


//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero
void funcion_hebra_estanquero(  )
{
   while (true)
   {
      // selecciona aleatoriamente un fumador
      int num_fumador = producir_ingrediente();

      // esperar hasta mostrador libre
       mostrador_libre.sem_wait( ) ;

      // Informa del ingrediente depositado
      mutex_cout.lock();
         cout << "Estanquero pone ingrediente para fumador " << num_fumador << "." << endl ;
      mutex_cout.unlock();

      // Señala que hay ingrediente disponible para fumador 'num_fumador'
      ingrediente_en_mostrador[ num_fumador ].sem_signal(  );
   }
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador )
{
   int iter=0;
   while( true )
   {  // Fumador inicia obtención de ingrediente
      ingrediente_en_mostrador[num_fumador].sem_wait(  );
      mutex_cout.lock();
         cout << "                 Fumador " << num_fumador << ": RETIRA ingrediente" << endl;
      mutex_cout.unlock();
      mostrador_libre.sem_signal(  );
      fumar(num_fumador);
   }
}

//----------------------------------------------------------------------
int main()
{ 
   // Lanza Array de hebras fumadoras
   thread hebra_fumador[ num_fumadores ];
   for( unsigned long i = 0 ; i < num_fumadores ; i++ )
      hebra_fumador[i] = thread( funcion_hebra_fumador, i );
   // Lanza Hebra Estanquero
   thread hebra_estanquero( funcion_hebra_estanquero );
   

   // Esperar finalización de hebras:
   hebra_estanquero.join();
   for( unsigned i = 0 ; i < num_fumadores ; i++ )
      hebra_fumador[i].join();
}
//----------------------------------------------------------------------