/**
 * @file filosofosInterbloqueo.cpp
 * @brief Problema de los filósofos con camarero.
 * 
 * Para evitar el interbloqueo, se añade un nuevo proceso, llamado camarero.
 * Cada filosofo:
 * 		- Antes de solicitar los tenedores, solicita sentarse al camarero.
 * 		- Después de liberar los tenedores, avisa al camarero de que se va a levantar.
 * 
 * @author Arturo Olivares Martos
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
	num_filosofos = 5 ,              // número de filósofos 
	num_filo_ten  = 2*num_filosofos, // número de filósofos y tenedores 
	num_procesos  = num_filo_ten +1;   // número de procesos total (+1 por el camarero)

const int
	tag_sentarse = 0,	// Etiqueta para sentarse
	tag_levantarse = 1;	// Etiqueta para levantarse


const int id_camarero = num_procesos - 1; // Identificador del camarero


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
 * @brief Función que determina si un proceso es un filósofo
 * 
 * @param id_global Identificador global del proceso
 * @return true Si es filósofo, false en caso contrario
 */
bool es_filosofo( int id_global ){
	return !es_camarero(id_global) && id_global % 2 == 0 ;
}

/**
 * @brief Función que determina si un proceso es un tenedor
 * 
 * @param id_global Identificador global del proceso
 * @return true Si es tenedor, false en caso contrario
 */
bool es_tenedor( int id_global ){
	return !es_camarero(id_global) && id_global % 2 == 1 ;
}

/**
 * @brief Función que determina si un proceso es el camarero
 * 
 * @param id_global Identificador global del proceso
 * @return true Si es camarero, false en caso contrario
 */
bool es_camarero( int id_global ){
	return id_global == id_camarero;
}

/**
 * @brief Función que obtiene el id del filósofo a partir del id global
 * 
 * @param id_global Identificador global del proceso
 * @return int Identificador del filósofo
 * 
 * @pre es_filosofo(id_global) == true
 */
int obtener_id_filosofo( int id_global ){
	return id_global / 2 ;
}

/**
 * @brief Función que obtiene el id global a partir del id del filósofo
 * 
 * @param id_filosofo Identificador del filósofo
 * @return int Identificador global del proceso
 */
int obtener_id_global_filosofo( int id_filosofo ){
	return id_filosofo * 2 ;
}

/**
 * @brief Función que obtiene el id del tenedor a partir del id global
 * 
 * @param id_global Identificador global del proceso
 * @return int Identificador del tenedor
 * 
 * @pre es_tenedor(id_global) == true
 */
int obtener_id_tenedor( int id_global ){
	return (id_global-1) / 2 ;
}

/**
 * @brief Función que obtiene el id global a partir del id del tenedor
 * 
 * @param id_tenedor Identificador del tenedor
 * @return int Identificador global del proceso
 */
int obtener_id_global_tenedor( int id_tenedor ){
	return id_tenedor * 2 + 1 ;
}

/**
 * @brief Función que obtiene los identificadores de los tenedores de un filósofo
 * 
 */
void obtener_tenedores (int id_filosofo, int& id_ten_izq, int& id_ten_der){
	id_ten_izq = (id_filosofo+1)              % num_filo_ten; //id. tenedor izq.
	id_ten_der = (id_filosofo+num_filo_ten-1) % num_filo_ten; //id. tenedor der.
}


/**
 * @brief Función que ejecuta la hebra del filósofo
 * 
 * @param id_filosofo Identificador del filósofo, distinto a id_global
 */
void funcion_filosofos( int id_filosofo ){
	int id_ten_izq, id_ten_der ; // identificadores de mis tenedores
	obtener_tenedores( id_filosofo, id_ten_izq, id_ten_der );

	int peticion=1;

	while ( true ) {
		// Sentarse
		cout <<"Filosofo " <<id_filosofo << " solicita sentarse" <<endl;
		MPI_Ssend( &peticion, 1, MPI_INT, id_camarero, tag_sentarse, MPI_COMM_WORLD );


		// Solicitar tenedores
		cout <<"Filosofo " <<id_filosofo << " solicita el tenedor izquierdo: " <<id_ten_izq <<endl;
		MPI_Ssend( &peticion, 1, MPI_INT, obtener_id_global_tenedor(id_ten_izq), 0, MPI_COMM_WORLD );
		cout <<"Filosofo " <<id_filosofo <<" solicita el tenedor derecho: " <<id_ten_der <<endl;
		MPI_Ssend( &peticion, 1, MPI_INT, obtener_id_global_tenedor(id_ten_der), 0, MPI_COMM_WORLD );

		// Comer
		cout <<"Filosofo " <<id_filosofo <<" comienza a comer" <<endl ;
		sleep_for( milliseconds( aleatorio<10,100>() ) );

		// Liberar tenedores
		cout <<"Filosofo " <<id_filosofo <<" suelta el tenedor izquierdo: " <<id_ten_izq <<endl;
		MPI_Ssend( &peticion, 1, MPI_INT, obtener_id_global_tenedor(id_ten_izq), 0, MPI_COMM_WORLD );
		cout<< "Filósofo " <<id_filosofo <<" suelta el tenedor derecho " <<id_ten_der <<endl;
		MPI_Ssend( &peticion, 1, MPI_INT, obtener_id_global_tenedor(id_ten_der), 0, MPI_COMM_WORLD );

		// Levantarse
		cout <<"Filosofo " <<id_filosofo << " solicita levantarse" <<endl;
		MPI_Ssend( &peticion, 1, MPI_INT, id_camarero, tag_levantarse, MPI_COMM_WORLD );

		// Pensar
		cout << "Filosofo " << id_filosofo << " comienza a pensar" << endl;
		sleep_for( milliseconds( aleatorio<10,100>() ) );
	}
}

/**
 * @brief Función que representa cada tenedor
 */
void funcion_tenedores( int id_tenedor ){
	int valor, id_filosofo ;  // valor recibido, identificador del filósofo
	MPI_Status estado ;       // metadatos de las dos recepciones

	while ( true ){
		// Esperamos a que un filósofo pida coger el tenedor
		MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &estado );
		id_filosofo = obtener_id_filosofo(estado.MPI_SOURCE);
		cout <<"Tenedor " <<id_tenedor <<" ha sido cogido por filosofo " <<id_filosofo <<endl;

		// Esperamos a que el filósofo correspondiente suelte el tenedor (Tenemos que esperar con el id_global del filósofo)
		MPI_Recv(&valor, 1, MPI_INT, obtener_id_global_filosofo(id_filosofo), 0, MPI_COMM_WORLD, &estado );
		cout <<"Tenedor "<< id_tenedor<< " ha sido liberado por filosofo " <<id_filosofo <<endl ;
	}
}


/**
 * @brief Función que representa al camarero
 */
void funcion_camarero(){
	int valor, id_filosofo;
	int tag_aceptable;
	MPI_Status estado;

	int num_filosofos_sentados = 0;
	const int NUM_MAX_FILOSOFOS_SENTADOS = num_filosofos - 1;

	while ( true ){
		// Si hay menos de 4 filósofos sentados, aceptamos cualquier petición.
		// En caso contrario, solo aceptamos peticiones de levantarse.
		tag_aceptable = (num_filosofos_sentados < NUM_MAX_FILOSOFOS_SENTADOS) ? MPI_ANY_TAG : tag_levantarse;
		MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_aceptable, MPI_COMM_WORLD, &estado);

		// Analizamos la peticion
		if (estado.MPI_TAG == tag_sentarse){
			num_filosofos_sentados++;
			cout << "Filosofo " << obtener_id_filosofo(estado.MPI_SOURCE) << " se sienta. Hay " << num_filosofos_sentados << " filósofos sentados" << endl;
		} else if (estado.MPI_TAG == tag_levantarse){
			num_filosofos_sentados--;
			cout << "Filosofo " << obtener_id_filosofo(estado.MPI_SOURCE) << " se levanta. Hay " << num_filosofos_sentados << " filósofos sentados" << endl;
		}
	}
}


int main( int argc, char** argv ){
	int id_global, num_procesos_actual ;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &id_global );
	MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


	if ( num_procesos == num_procesos_actual ){
		if ( es_filosofo( id_global ) ){
			funcion_filosofos( obtener_id_filosofo( id_global ) );
		} else if ( es_tenedor( id_global ) ){
			funcion_tenedores( obtener_id_tenedor( id_global ) );
		} else if ( es_camarero( id_global ) ){
			funcion_camarero();
		}
		else{
			cout << "Error: proceso desconocido" << endl ;
		}
	} else {	// Número de procesos incorrecto
		if ( id_global == 0 ) // solo el primero escribe error, indep. del rol
		{ cout 	<< "El número de procesos esperados es:    " << num_procesos << endl
				<< "El número de procesos en ejecución es: " << num_procesos_actual << endl
				<< "(programa abortado)" << endl ;
		}
	}

	MPI_Finalize( );
	return 0;
}

