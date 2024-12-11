
/**
 * @file Examen4.cpp
 * @author José Juan Urrutia Milán
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./Examen4.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica3/Exámenes/Examen4.md
 */
#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
	num_filosofos = 5 ,                 // número de filósofos 
	num_filo_ten  = 2*num_filosofos,    // número de filósofos y tenedores 
	num_procesos  = num_filo_ten+1 ;    // número de procesos total

const int id_camarero= num_procesos-1; // Identificador del camarero
const int id_filosofo_especial = 8;    // Identificador del filósofo que come con las manos
const int
	tag_sentar=0,				// Etiqueta para sentarse para los filósofos normales
	tag_levantar=1,				// Etiqueta para levantarse para los filósofos normales
	tag_especial_sentar=2,		// Etiqueta para sentarse para el filósofo especial
	tag_especial_levantar=3;	// Etiqueta para levantarse para el filósofo especial


/**
 * @brief Función que produce un número aleatorio entre dos valores
 * 
 * @tparam min Valor mínimo. Constante conocida en tiempo de compilación
 * @tparam max Valor máximo. Constante conocida en tiempo de compilación
 */
template< int min, int max > int aleatorio(){
	static default_random_engine generador( (random_device())() );
	static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
	return distribucion_uniforme( generador );
}

/**
 * @brief Función que ejecuta la hebra del filósofo
 * 
 * @param id Identificador global del filósofo
 */
void funcion_filosofos( int id ){
	int id_ten_izq = (id+1)              % num_filo_ten, //id. tenedor izq.
		id_ten_der = (id+num_filo_ten-1) % num_filo_ten; //id. tenedor der.
	int  peticion=0, valor;

	while ( true ){
		
		// Solicitamos Sentarnos
		if(id != id_filosofo_especial){
			// No es el filosofo que come con las manos
			cout <<"+++++++++++++++++++++++++  Filosofo " <<id << " solicita SENTARSE." <<endl;
			MPI_Ssend(&peticion, 1, MPI_INT,id_camarero,tag_sentar,MPI_COMM_WORLD);
		}else{ 
			// Es el filosofo que come con las manos	    
			cout <<"*************************  Filosofo " <<id << " solicita SENTARSE." <<endl;
			MPI_Ssend(&peticion, 1, MPI_INT,id_camarero,tag_especial_sentar,MPI_COMM_WORLD);
		}

		// Solicitamos los tenedores. Solo si no es el filosofo que come con las manos
		if(id != id_filosofo_especial){
			cout <<"Filosofo " <<id << " solicita ten. izq." <<id_ten_izq <<endl;
			MPI_Ssend(&peticion, 1, MPI_INT,id_ten_izq,0,MPI_COMM_WORLD);

			cout <<"Filosofo " <<id <<" solicita ten. der." <<id_ten_der <<endl;
			MPI_Ssend(&peticion, 1, MPI_INT,id_ten_der,0,MPI_COMM_WORLD);
		}
		
		// Comemos
		cout <<endl<<"Filosofo " <<id <<" comienza a COMER" <<endl ;
		sleep_for( milliseconds( aleatorio<1000,1800>() ) );

		// Liberamos los tenedores. Solo si no es el filosofo que come con las manos
		if(id != id_filosofo_especial){
			cout <<"Filosofo " <<id <<" suelta ten. izq. " <<id_ten_izq <<endl;
			MPI_Ssend(&peticion, 1, MPI_INT,id_ten_izq,0,MPI_COMM_WORLD);

			cout<< "Filosofo " <<id <<" suelta ten. der. " <<id_ten_der <<endl;
			MPI_Ssend(&peticion, 1, MPI_INT,id_ten_der,0,MPI_COMM_WORLD);
		}


		// Solicitamos Levantarnos
		if(id != id_filosofo_especial){
			// No es el filosofo que come con las manos
			cout <<"+++++++++++++++++++++++++++  Filosofo " <<id << " solicita LEVANTARSE." <<endl;
			MPI_Ssend(&peticion, 1, MPI_INT,id_camarero,tag_levantar,MPI_COMM_WORLD);
			
		}else{
			// Es el filosofo que come con las manos
			cout <<"*************************  Filosofo " <<id << " solicita LEVANTARSE." <<endl;
			MPI_Ssend(&peticion, 1, MPI_INT,id_camarero,tag_especial_levantar,MPI_COMM_WORLD);
		}

		cout<<endl << "Filosofo " << id << " comienza a PENSAR" << endl;
		sleep_for( milliseconds( aleatorio<1000,1800>() ) );
	}
}


/**
 * @brief Función que representa cada tenedor
 * 
 * @param id Identificador global del tenedor
 */
void funcion_tenedores( int id ){
  int valor, id_filosofo ;  // valor recibido, identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones

  while ( true ){
	// Esperamos a que un filósofo pida coger el tenedor
	MPI_Recv(&valor, 1, MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&estado);
	id_filosofo=estado.MPI_SOURCE;
	cout <<".......................................Ten. " <<id <<
					" ha sido COGIDO por filo. " <<id_filosofo <<endl;

	// Esperamos a que el filósofo correspondiente suelte el tenedor
	MPI_Recv(&valor, 1, MPI_INT,id_filosofo,0,MPI_COMM_WORLD,&estado);
	cout <<".......................................Ten. "<< id<< 
					" ha sido SOLTADO por filo. " <<id_filosofo <<endl ;
  }
}


/**
 * @brief Función que representa al camarero
 */
void funcion_camarero( ){
	int sentados=0;
	int id_filosofo, tag, valor, flag = 0; 
	MPI_Status estado;       

	bool peticion_encontrada;
	bool procesa_sentar = false;	// Bandera que indica si se procesa una petición de sentarse o de levantarse

	while ( true ){
		
		if(sentados < 4){
			// Sondea en bucle peticiones de sentarse o levantarse de filósofos distintos del especial
			// Cuando detecta una peticion, termina el bucle
			peticion_encontrada = false;
			while(!peticion_encontrada){

					// Cambia el tipo de petición que se va a procesar
					procesa_sentar = !procesa_sentar;
					
					if(procesa_sentar){
						// Busca si alguien se quiere sentar
						MPI_Iprobe(MPI_ANY_SOURCE, tag_sentar, MPI_COMM_WORLD, &flag, &estado);
					}else{
						// Busca si alguien se quiere levantar
						MPI_Iprobe(MPI_ANY_SOURCE, tag_levantar, MPI_COMM_WORLD, &flag, &estado);
					}
					
					peticion_encontrada = flag > 0;
			} // while
		
			tag = (procesa_sentar)? tag_especial_sentar : tag_levantar;
			id_filosofo = estado.MPI_SOURCE;
			
			// Comprobacion
			if (tag != estado.MPI_TAG){
				cerr << "Error en la comprobación de la etiqueta" << endl;
				exit(1);
			}
			
			MPI_Recv(&valor, 1, MPI_INT, id_filosofo, tag, MPI_COMM_WORLD, &estado);
		
		}else if(sentados == 4){

			// Sondea en bucle peticiones de sentarse del especial, como de levantarse del resto.
			// Cuando detecta una peticion, termina el bucle
			peticion_encontrada = false;
			while(!peticion_encontrada){
			
				// Cambia el tipo de petición que se va a procesar
				procesa_sentar = !procesa_sentar;
				
				if(procesa_sentar){
					// Mira si el 4 se quiere sentar
					MPI_Iprobe(MPI_ANY_SOURCE, tag_especial_sentar, MPI_COMM_WORLD, &flag, &estado);
				}else{
					// Mira si otro se quiere levantar
					MPI_Iprobe(MPI_ANY_SOURCE, tag_levantar, MPI_COMM_WORLD, &flag, &estado);
				
				}
				
				peticion_encontrada = flag > 0;
			} // while
			
			tag = (procesa_sentar)? tag_especial_sentar : tag_levantar;
			id_filosofo = estado.MPI_SOURCE;

			// Comprobacion
			if (tag != estado.MPI_TAG){
				cerr << "Error en la comprobación de la etiqueta" << endl;
				exit(1);
			}
			
			MPI_Recv(&valor, 1, MPI_INT, id_filosofo, tag, MPI_COMM_WORLD, &estado);
			
		}else{
			// Hay 5 filosofos sentados, no se sienta nadie mas
			// Solo puede recibir una petición de levantarse del especial
			MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_especial_levantar, MPI_COMM_WORLD, &estado);
		}
		
		// Actualizamos el número de sentados
		switch(estado.MPI_TAG){
			case tag_especial_sentar:
			case tag_sentar:
				sentados++;
				break;
						
			case tag_especial_levantar:
			case tag_levantar:
				sentados--;
				break;
		}

	}	// while true del camarero
}


// ---------------------------------------------------------------------
int main( int argc, char** argv ){
	int id_propio, num_procesos_actual ;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
	MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


	if ( num_procesos == num_procesos_actual ){
		if (id_propio==id_camarero) 
			funcion_camarero();
		else if ( id_propio % 2 == 0 )
			funcion_filosofos( id_propio ); 
		else                               
			funcion_tenedores( id_propio ); 
	}
	else{
		if ( id_propio == 0 ){ // solo el primero escribe error, indep. del rol
			cout 	<< "el numero de procesos debería ser:    " << num_procesos << endl
					<< "   y el numero de procesos es: " << num_procesos_actual << endl
					<< "(programa abortado)" << endl ;
		}
	}

	MPI_Finalize( );
	return 0;
}

// ---------------------------------------------------------------------
