#include <iostream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <mpi.h>

#define NUM_FILOSOFOS 5
#define NUM_PROCESOS (2*(NUM_FILOSOFOS)+1)
#define RANK_CAMARERO ((NUM_PROCESOS)-1)

#define TAG_SENTARSE 0
#define TAG_LEVANTARSE 1

using namespace std ;
void Filosofo( int id );
void Tenedor ( int id );
void Camarero() ;

// ---------------------------------------------------------------------

void retraso_aleatorio()
{
    static bool primera = true ;
    
    // inicializar generador de nœmeros aleatorios (la primera vez)
    if ( primera )
    {  srand(time(NULL)) ;
       primera = false ;
    }
    // retraso aleatorio, de entre una y dos décimas de segundo
    usleep( 1000L * (100L + rand() % 100L ) );
}

// ---------------------------------------------------------------------

int main(int argc,char** argv )
{
    int rank,size;
    
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    
    if ( size != NUM_PROCESOS )
    {
        if( rank == 0 )
        cout << "El numero de procesos debe ser " << NUM_PROCESOS << endl << flush;
        MPI_Finalize( );
        return 0;
    }
    
    if ( rank == RANK_CAMARERO )
        Camarero() ; // el 10 es el camarero
    else if ( (rank%2) == 0 )
        Filosofo( rank ); // los pares (0,2,4,6,8) son Filosofos
    else
        Tenedor( rank ); // los impares (1,3,5,7,9) son Tenedores
        
    MPI_Finalize( );
    return 0;
}

// ---------------------------------------------------------------------

void Filosofo( int id )
{
    const int
        primero = (id+1) % (NUM_PROCESOS-1) ,
        segundo = (id+(NUM_PROCESOS-2)) % (NUM_PROCESOS-1) ;
        
    while ( true )
    {
        // solicita sentarse
        cout << "Filosofo " << id << " solicita sentarse." << endl << flush;
        MPI_Ssend( &id, 1, MPI_INT, RANK_CAMARERO, TAG_SENTARSE, MPI_COMM_WORLD );
        
        // solicita y coge primer tenedor
        cout << "Filosofo " << id << " solicita primer tenedor: " << primero << endl << flush;
        MPI_Ssend( &id, 1, MPI_INT, primero, primero, MPI_COMM_WORLD );
        cout << "Filosofo " << id << " coge primer tenedor: " << primero << endl << flush;
        
        // solicita coge segundo tenedor
        cout << "Filosofo " << id << " coge segundo tenedor: " << segundo << endl << flush;
        MPI_Ssend( &id, 1, MPI_INT,segundo,MPI_COMM_WORLD);
        cout << "Filosofo " << id << " coge segundo tenedor: " << segundo << endl << flush;
        
        // come
        cout << "Filosofo " << id << " COMIENDO" << endl << flush;
        retraso_aleatorio() ;
        
        // suelta el segundo tenedor
        cout << "Filosofo " << id << " suelta tenedor: " << segundo << endl << flush;
        MPI_Ssend( &id, 1, MPI_INT, primero, primero, MPI_COMM_WORLD );
        
        // suelta el primer tenedor
        cout << "Filosofo " << id << " suelta tenedor: " << primero << endl << flush;
        MPI_Ssend( &id, 1, MPI_INT, segundo, segundo, MPI_COMM_WORLD );
        
        // solicita levantarse
        cout << "Filosofo " << id << " solicita sentarse." << endl << flush;
        MPI_Ssend ( &id, 1, MPI_INT, RANK_CAMARERO, TAG_SENTARSE, MPI_COMM_WORLD );
        
        // piensa
        cout << "Filosofo " << id << " PENSANDO" << endl << flush ;
        retraso_aleatorio() ;
    }
}

// ---------------------------------------------------------------------

void Tenedor( int id )
{
    int valor ;
    MPI_Status status;
    
    while ( true )
    {
        // espera un mensaje desde cualquier filosofo vecino
        cout <<"Tenedor " << id << " espera petición." << endl << flush;
        MPI_Recv( &valor, 1, MPI_INT, MPI_ANY_SOURCE, id, MPI_COMM_WORLD, &status ); 
        cout << "Tenedor " << id << " recibe petición de " << status.MPI_SOURCE << endl << flush ;
        
        // espera a que el filosofo suelte el tenedor
        MPI_Recv( 1, &valor, MPI_INT, status.MPI_SOURCE, id, MPI_COMM_WORLD, &status );
        cout<<"Tenedor " << id << " recibe liberación de " << status.MPI_SOURCE << endl << flush;
    }
}

// ---------------------------------------------------------------------

void Camarero()
{
    int valor, num_sentados = 0, tag_aceptada ;
    MPI_Status status;
    
    while ( true )
    {
        if ( num_sentados < NUM_FILOSOFOS-1 )
            tag_aceptada = MPI_ANY_TAG ;
        else
            tag_aceptada = TAG_LEVANTARSE ;
            
        // espera un mensaje desde cualquier filosofo con etiqueta aceptable
        cout << "Camarero espera petición de sentarse/levantarse (sentados == " << num_sentados << ")" << endl << flush;
        
        MPI_Recv( &valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_aceptada, MPI_COMM_WORLD, &status);
        cout << "Camarero recibe petici—n de filosofo " << status.MPI_SOURCE << endl << flush ;
        
        if ( status.MPI_TAG == TAG_LEVANTARSE )
           num_sentados -- ;
        else
            num_sentados ++ ;
    }
}