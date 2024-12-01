// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 3. Introducción al paso de mensajes con MPI
//
// Archivo: ejemplo_probe.cpp
// Uso de MPI_Probe para obtener metadatos antes de recibir
// (proceso impresor que imprime cadenas recibidas de forma sincrona)
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <random>  // para 'aleatorio'
#include <thread>  // this_thread::sleep_for
#include <chrono>  // chrono::duration, chrono::milliseconds
#include <cstring>  // strlen
#include <cstdio> // snprintf
#include <mpi.h>

using namespace std ;


// constantes definibles
const int
   id_impresor = 0,   // el proceso que recibe los mensajes es el 0
   num_iteraciones_por_emisor = 30 ;

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

void funcion_impresor( int num_emisores )
{
   MPI_Status estado ;
   int num_chars_rec ;
   // total mensajes: 2 por emisor, + 2 por cada una de sus iteraciones
   const int num_total_msgs = num_emisores*(2*num_iteraciones_por_emisor+2) ;

   cout << "inicio del impresor" << endl ;
   for( int i = 0 ; i < num_total_msgs; i++ )
   {
      // espera un mensaje de cualquier emisor, sin recibirlo
      MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );

      // leer el numero de chars del mensaje
      MPI_Get_count( &estado, MPI_CHAR, &num_chars_rec );

      // reservar memoria dinámica para los caracteres (incluyendo 0 al final)
      char * buffer = new char[num_chars_rec+1] ;

      // recibir el mensake en el buffer y añadir un cero al final
      // IMPORTANTE: especificar exactamente mismo emisor detectado en el Probe
      MPI_Recv( buffer, num_chars_rec, MPI_CHAR, estado.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );
      buffer[num_chars_rec] = 0 ;

      // imprimir  la cadena recibida
      cout << buffer << endl ;

      // liberar memoria dinámica ocupada por el buffer
      delete [] buffer ;
   }
   cout << "fin del impresor" << endl ;
}
// -----------------------------------------------------------------------------

void enviar_cadena( const char * cadena )
{
   int num_chars = strlen( cadena );
   MPI_Ssend( cadena, num_chars, MPI_CHAR, id_impresor, 0, MPI_COMM_WORLD );
}

// -----------------------------------------------------------------------------

void funcion_emisores( int id_propio )
{
   const int maxlon = 1024 ; // máxima longitud de la cadena en 'str'
   char str[maxlon] ;

   snprintf(str,maxlon,"inicio del proceso número: %d", id_propio);
   enviar_cadena( str );

   for ( int i = 0 ; i < num_iteraciones_por_emisor ; i++ )
   {
      int dur_ms = aleatorio<20,200>();
      snprintf(str,maxlon,"proceso %d: voy a dormir %d milisegndos",id_propio,dur_ms);
      enviar_cadena( str );
      this_thread::sleep_for( chrono::milliseconds( dur_ms ) );
      enviar_cadena("ya he dormido");
   }
   snprintf(str,maxlon,"fin del proceso número: %d", id_propio);
   enviar_cadena( str );
}

// -----------------------------------------------------------------------------


int main(int argc, char *argv[])
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_procesos_actual > 1 ) // si num. proc. ok
   {
      // ejecutar la función correspondiente al id. propio
      if ( id_propio == id_impresor )
         funcion_impresor( num_procesos_actual-1 );
      else
         funcion_emisores( id_propio );
   }
   else // si el numero de procesos es incorrecto
      cerr << "error: este programa se debe lanzar con al menos dos procesos" << endl ;


    MPI_Finalize();
    return 0;
}
