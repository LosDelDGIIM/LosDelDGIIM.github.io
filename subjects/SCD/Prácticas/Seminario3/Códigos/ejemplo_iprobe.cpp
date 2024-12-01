// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 3. Introducción al paso de mensajes con MPI
//
// Archivo: ejemplo_iprobe.cpp
// Uso de MPI_Iprobe para sondeo no bloqueante
// (el proceso receptor (0) recibe con más prioridad un mensaje de
// los emisores con id más bajo)
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// Actualizado para prioridades en Octubre de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <random>  // para 'aleatorio'
#include <thread>  // this_thread::sleep_for
#include <chrono>  // chrono::duration, chrono::milliseconds
#include <cstring>  // strlen
#include <mpi.h>

using namespace std ;
using namespace this_thread ;  // sleep_for
using namespace chrono ;       // milliseconds, seconds, etc..


// constantes definibles
const int
   id_receptor = 0 ;  // el proceso que recibe los mensajes es el 0

const int
   num_mensajes_por_emisor = 100 ;

// -----------------------------------------------------------------------------
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}
// -----------------------------------------------------------------------------
// función que ejecuta el receptor: recibe 'n' mensajes de cada receptor

void funcion_receptor( int id_min, int id_max )
{
   int num_emisores = id_max - id_min +1 ;  // total de emisores
   int total_mensajes = num_mensajes_por_emisor*num_emisores ; // total msgs
   int cuenta[num_emisores]; // número de mensajes recibidos por emisor

   // inicializar la cuenta:
   for( unsigned i = 0 ; i < num_emisores ; i++ )
      cuenta[i] = 0 ;

   cout << "inicio del receptor" << endl ;

   for( int i = 0 ; i < total_mensajes ; i++ )
   {
      MPI_Status estado ;     // estado de la recepción
      int        hay_mensaje, // ==0 si no hay mensajes, >0 si hay mensajes
                 id_emisor ,  // identificador de emisor a recibir/recibido
                 valor ;      // valor recibido

      // comprobar si hay mensajes, en orden creciente de los posibles emisores
      // (id_emisor toma valores entre id_min e id_max, ambos incluidos)
      for( id_emisor = id_min ; id_emisor <= id_max ; id_emisor++ )
      {
         // recibir mensaje del emisor
         MPI_Iprobe( id_emisor, MPI_ANY_TAG, MPI_COMM_WORLD, &hay_mensaje, &estado ) ;
         if ( hay_mensaje ) break ;
      }

      // comprobar si hay mensajes pendientes o no
      if ( hay_mensaje )              // si no hay mensaje:
         cout << "Hay al menos un mensaje, del emisor: " << id_emisor << endl ;
      else
      {                             // si no hay mensaje
         id_emisor = MPI_ANY_SOURCE ;  //   aceptar de cualquiera
         cout << "No hay mensajes. Recibo de cualquiera." << endl ;
      }

      // recibir el mensaje e informar
      MPI_Recv( &valor, 1,MPI_INT, id_emisor, 0, MPI_COMM_WORLD, &estado );
      id_emisor = estado.MPI_SOURCE ;
      cout << "Receptor ha recibido de " << id_emisor << endl ;

      // incrementar cuenta e imprimir estadísticas
      cuenta[id_emisor-id_min] ++ ;
      cout << "Núm. de mensajes recibidos de cada emisor:  " ;
      for( unsigned i = 0 ; i < num_emisores ; i++ )
         cout << cuenta[i] << ", " ;
      cout << endl << endl ;

      // dormir un poco
      sleep_for( milliseconds( aleatorio<8,12>() ) );
   }
}
// -----------------------------------------------------------------------------
// función que ejecutan los emisores: emite 'n' mensajes a receptor

void funcion_emisores( int id_propio )
{
   for( unsigned i = 0 ; i < num_mensajes_por_emisor ; i++ )
   {
      int valor ;
      sleep_for( milliseconds( aleatorio<8,12>() ) );
      MPI_Ssend( &valor, 1,MPI_INT, id_receptor, 0, MPI_COMM_WORLD );
   }
   cout << "acaba emisor : " << id_propio << endl ;
}

// -----------------------------------------------------------------------------


int main(int argc, char *argv[])
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( 1 < num_procesos_actual ) // si num. proc. ok
   {
      // ejecutar la función correspondiente al id. propio
      if ( id_propio == id_receptor )
         funcion_receptor( id_propio+1, num_procesos_actual-1 );
      else
         funcion_emisores( id_propio );
   }
   else // si el numero de procesos es incorrecto
      cerr << "error: este programa se debe lanzar con al menos dos procesos" << endl ;


    MPI_Finalize();
    return 0;
}
