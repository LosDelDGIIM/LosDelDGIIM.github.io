// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 3. Introducción al paso de mensajes con MPI
//
// Archivo: intercambio_sincrono.cpp
// Intercambio síncrono (seguro) de mensajes entre pares de procesos
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <mpi.h>
using namespace std;

int main( int argc, char *argv[] )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv);
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_procesos_actual % 2 == 0 ) // si número de procesos correcto (par)
   {
      int        valor_enviado = id_propio*(id_propio+1), // dato a enviar
                 valor_recibido,
                 id_vecino ;
      MPI_Status estado ;

      if ( id_propio % 2 == 0 ) // si proceso par: enviar y recibir
      {
         id_vecino = id_propio+1 ; // el vecino es siguiente
         MPI_Ssend( &valor_enviado,  1, MPI_INT, id_vecino, 0, MPI_COMM_WORLD );
         MPI_Recv ( &valor_recibido, 1, MPI_INT, id_vecino, 0, MPI_COMM_WORLD, &estado );
      }
      else  // si proceso impar: recibir y enviar
      {
         id_vecino = id_propio-1 ; // el vecino es el anterior
         MPI_Recv ( &valor_recibido, 1, MPI_INT, id_vecino, 0, MPI_COMM_WORLD, &estado );
         MPI_Ssend( &valor_enviado,  1, MPI_INT, id_vecino, 0, MPI_COMM_WORLD );
      }
      cout  << "Proceso "<< id_propio <<" recibe "<< valor_recibido
            << " de "<< id_vecino << endl ;
   }
   else if ( id_propio == 0 ) // si n.procs. impar, el primero da error
      cerr << "Se esperaba un número par de procesos, pero hay "
           << num_procesos_actual << endl ;

   MPI_Finalize();
   return 0;
}
