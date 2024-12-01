// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 3. Introducción al paso de mensajes con MPI
//
// Archivo: sendrecv2.cpp
// Difusión de un mensaje en una cadena de procesos
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <mpi.h>

using namespace std;

const int num_min_procesos = 2 ;

int main( int argc, char *argv[] )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_min_procesos <= num_procesos_actual  )
   {
      const int  id_anterior  = id_propio-1, // ident. proceso anterior
                 id_siguiente = id_propio+1 ; // ident. proceso siguiente
      int        valor;  // valor recibido o leído, y enviado
      MPI_Status estado; // estado de la recepción

      do
      {
         // recibir o leer valor
         if ( id_anterior < 0   ) // si soy el primero (no hay anterior)
         {
            cout << "Introduce un número aquí debajo (-1 para acabar): " << endl ;
            cin >> valor ;        //     pedir valor por teclado (-1 para acabar)
         }
         else                     // si no soy el primer proceso: recibirlo
            MPI_Recv( &valor, 1, MPI_INT, id_anterior, 0, MPI_COMM_WORLD, &estado );

         // imprimir valor
         cout<< "Proc."<< id_propio<< ": recibido/leído: "<< valor<< endl ;

         // si no soy el último (si hay siguiente): enviar valor,
         if ( id_siguiente < num_procesos_actual )
            MPI_Send( &valor, 1, MPI_INT, id_siguiente, 0, MPI_COMM_WORLD );
      }
      while( valor >= 0 ); // acaba cuando se teclea un valor negativo
   }
   else
      cerr << "Se esperaban 2 procesos como mínimo, pero hay 1." << endl ;

   MPI_Finalize();
   return 0;
}
