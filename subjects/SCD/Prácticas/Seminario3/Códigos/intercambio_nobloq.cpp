// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 3. Introducción al paso de mensajes con MPI
//
// Archivo: intercambio_sincrono.cpp
// Intercambio asíncrono (inseguro) de mensajes entre pares de procesos
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
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_procesos_actual % 2 == 0 )
   {
      int         valor_enviado = id_propio*(id_propio+1), // dato a enviar
                  valor_recibido,
                  id_vecino ;
      MPI_Status  estado ;
      MPI_Request ticket_envio,
                  ticket_recepcion;

      if ( id_propio % 2 == 0 )
         id_vecino = id_propio+1 ;
      else
         id_vecino = id_propio-1 ;

      // las siguientes dos llamadas pueden aparecer en cualquier orden
      MPI_Irecv( &valor_recibido, 1, MPI_INT, id_vecino, 0, MPI_COMM_WORLD, &ticket_recepcion );
      MPI_Isend( &valor_enviado,  1, MPI_INT, id_vecino, 0, MPI_COMM_WORLD, &ticket_envio );

      MPI_Wait( &ticket_envio, &estado );
      MPI_Wait( &ticket_recepcion, &estado );

      cout<< "Soy el proceso " << id_propio << " y he recibido el valor " << valor_recibido << " del proceso " << id_vecino  << endl ;
   }
   else if ( id_propio == 0 ) // si n.procs. impar, el primero da error
      cerr << "Se esperaba un número par de procesos, pero hay "
           << num_procesos_actual << endl ;

   MPI_Finalize();
   return 0;
}
