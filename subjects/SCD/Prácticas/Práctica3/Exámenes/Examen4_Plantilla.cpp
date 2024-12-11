
#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_filosofos = 5 ,              // número de filósofos 
   num_filo_ten  = 2*num_filosofos, // número de filósofos y tenedores 
   num_procesos  = num_filo_ten+1 ;   // número de procesos total
const int camarero= num_filo_ten;  
const int tag_sentar=0, tag_levantar=1;


//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
//----------------------------------------------------------------------
template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

// ---------------------------------------------------------------------

void funcion_filosofos( int id )
{
  int id_ten_izq = (id+1)              % num_filo_ten, //id. tenedor izq.
      id_ten_der = (id+num_filo_ten-1) % num_filo_ten; //id. tenedor der.
  int  peticion=0, valor;

  while ( true )
  {

    cout <<"+++++++++++++++++++++++++  Filosofo " <<id << " solicita SENTARSE." <<endl;
    MPI_Ssend(&peticion, 1, MPI_INT,camarero,tag_sentar,MPI_COMM_WORLD);


    cout <<"Filosofo " <<id << " solicita ten. izq." <<id_ten_izq <<endl;
    MPI_Ssend(&peticion, 1, MPI_INT,id_ten_izq,0,MPI_COMM_WORLD);

    cout <<"Filosofo " <<id <<" solicita ten. der." <<id_ten_der <<endl;
    MPI_Ssend(&peticion, 1, MPI_INT,id_ten_der,0,MPI_COMM_WORLD);

    cout <<endl<<"Filosofo " <<id <<" comienza a COMER" <<endl ;
    sleep_for( milliseconds( aleatorio<1000,1800>() ) );

    cout <<"Filosofo " <<id <<" suelta ten. izq. " <<id_ten_izq <<endl;
    MPI_Ssend(&peticion, 1, MPI_INT,id_ten_izq,0,MPI_COMM_WORLD);

    cout<< "Filosofo " <<id <<" suelta ten. der. " <<id_ten_der <<endl;
    MPI_Ssend(&peticion, 1, MPI_INT,id_ten_der,0,MPI_COMM_WORLD);

    cout <<"+++++++++++++++++++++++++++  Filosofo " <<id << " solicita LEVANTARSE." <<endl;
    MPI_Ssend(&peticion, 1, MPI_INT,camarero,tag_levantar,MPI_COMM_WORLD);


    cout<<endl << "Filosofo " << id << " comienza a PENSAR" << endl;
    sleep_for( milliseconds( aleatorio<1000,1800>() ) );
 }
}


// ---------------------------------------------------------------------
void funcion_tenedores( int id )
{
  int valor, id_filosofo ;  // valor recibido, identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones

  while ( true )
  {
     MPI_Recv(&valor, 1, MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&estado);
     id_filosofo=estado.MPI_SOURCE;
     cout <<".......................................Ten. " <<id <<
                        " ha sido COGIDO por filo. " <<id_filosofo <<endl;

     MPI_Recv(&valor, 1, MPI_INT,id_filosofo,0,MPI_COMM_WORLD,&estado);
     cout <<".......................................Ten. "<< id<< 
                        " ha sido SOLTADO por filo. " <<id_filosofo <<endl ;
  }
}

// ---------------------------------------------------------------------
void funcion_camarero( )
{
  int sentados=0, id_filosofo, tag, valor; 
  MPI_Status estado ;       

  while ( true )
  {
     if (sentados<4) 
          MPI_Recv(&valor, 1, MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&estado);
      else  
          MPI_Recv(&valor, 1, MPI_INT,MPI_ANY_SOURCE,tag_levantar,MPI_COMM_WORLD,&estado); 
      
      id_filosofo=estado.MPI_SOURCE; tag=estado.MPI_TAG;
      
      if (tag==tag_sentar)
         sentados++;
      else 
         sentados--;   
     cout <<endl<<"######################################################  CAMARERO DICE QUE HAY  " <<sentados <<
                                            " FILOSOFOS EN LA MESA " <<endl<<endl;

  }
}
// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if ( num_procesos == num_procesos_actual )
   {
    if (id_propio==camarero) 
      funcion_camarero();
    else if ( id_propio % 2 == 0 )
      funcion_filosofos( id_propio ); 
    else                               
      funcion_tenedores( id_propio ); 
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el numero de procesos debería ser:    " << num_procesos << endl
             << "   y el numero de procesos es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
