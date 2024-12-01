// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 3. Introducción al paso de mensajes con MPI
//
// Archivo: holamundo.cpp
// Ejecución de varios procesos, cada uno de los cuales imprime un mensaje
// en la salida estándar.
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <mpi.h>
#include <iostream>
using namespace std;

int main( int argc, char *argv[] )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );

   cout << "Hola desde proceso " << id_propio << " de " << num_procesos_actual << endl ;

   MPI_Finalize();
   return 0;
}
