// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 3. Introducción al paso de mensajes con MPI
//
// Archivo: sendrecv1.cpp
// Envio asíncrono seguro de un mensaje y recepción del mismo
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <mpi.h>
#include <iostream>

using namespace std; // incluye declaraciones de funciones, tipos y ctes. MPI

const int id_emisor             = 0,  // identificador de emisor
          id_receptor           = 1,  // identificador de receptor
          num_procesos_esperado = 2;  // numero de procesos esperados

int main( int argc, char *argv[] )
{
 int        id_propio,           // identificador de este proceso
            num_procesos_actual; // numero de procesos lanzados


 MPI_Init( &argc, &argv );                          // inicializa MPI
 MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );       // averiguar mi ident
 MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual ); // averiguar n.procs

 if ( num_procesos_esperado == num_procesos_actual ) // si num. procs. ok
 {
   // hacer envío o recepción (según id_propio)
   if ( id_propio == id_emisor ) // emisor: enviar
   {
      int valor_enviado = 100 ; // buffer del emisor (tiene 1 entero: MPI_INT)

      MPI_Send( &valor_enviado, 1, MPI_INT, id_receptor, 0, MPI_COMM_WORLD );
      cout << "Proceso " << id_propio << " ha enviado " << valor_enviado << endl ;
   }
   else // receptor: recibir
   {
      int valor_recibido ; // buffer del receptor (tiene 1 entero: MPI_INT)
      MPI_Status estado ;  // estado de la recepción

      MPI_Recv( &valor_recibido, 1, MPI_INT, id_emisor, 0, MPI_COMM_WORLD, &estado );
      cout << "Proceso " << id_propio << " ha recibido " << valor_recibido << endl ;
   }
 }
 else if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      // escribir un mensaje de error
      cerr
         << "el número de procesos esperados es:    " << num_procesos_esperado << endl
         << "el número de procesos en ejecución es: " << num_procesos_actual << endl
         << "(programa abortado)" << endl ;


 MPI_Finalize( ); // terminar MPI: debe llamarse siempre por cada proceso.
 return 0;        // terminar proceso
}
