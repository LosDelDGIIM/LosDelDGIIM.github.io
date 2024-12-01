/**
 * @file prodconsMultiple.cpp
 * @brief Problema de los productores-consumidores distribuido con MPI con múltiples productores y consumidores
 * 
 * 
 * @author Arturo Olivares Martos
 */

#include <iostream>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <mpi.h>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

// constantes que determinan la asignación de identificadores a roles:
const int
	num_productores 	  = 4 , // número de productores
	num_consumidores 	  = 5 , // número de consumidores
	num_procesos_esperado = num_productores + num_consumidores + 1 , // número total de procesos esperado
	num_items             = 20 , // numero de items producidos o consumidos
	tam_vector            = 10 ; // tamaño del vector

// Ha de ser un número entero
const int items_por_productor = num_items / num_productores,
		  items_por_consumidor = num_items / num_consumidores;

const int id_buffer = num_productores;


// Constantes referentes a las etiquetas
const int
	etiq_productor = 1,
	etiq_consumidor = 2;


/**
 * @brief Función que obtiene el ID del productor
 * 
 * @param id_propio_global Identificador de proceso
 * @pre Se trata de un productor
 */
int obtener_id_productor( int id_propio_global ){
	return id_propio_global;
}

/**
 * @brief Función que obtiene el ID del consumidor
 * 
 * @param id_propio_global Identificador de proceso
 * @pre Se trata de un consumidor
 */
int obtener_id_consumidor( int id_propio_global ){
	return id_propio_global - num_productores - 1;
}

/**
 * Función que determina si un identificador de proceso es de un productor
 * 
 * @param id_propio_global Identificador de proceso 
 * @return true si es productor, false en caso contrario
 */
bool es_productor( int id_propio_global){
	return 	0<=id_propio_global &&
			id_propio_global < num_productores;
}

/**
 * Función que determina si un identificador de proceso es de un buffer
 * 
 * @param id_propio_global Identificador de proceso
 * 
 * @return true si es buffer, false en caso contrario
 */
bool es_buffer( int id_propio_global ){
	return id_propio_global == num_productores ;
}

/**
 * Función que determina si un identificador de proceso es de un consumidor
 * 
 * @param id_propio_global Identificador de proceso
 * @return true si es consumidor, false en caso contrario
 */
bool es_consumidor( int id_propio_global){
	return 	num_productores < id_propio_global &&
			id_propio_global < num_productores + num_consumidores +1;
}



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
 * @brief Función que simula la producción de un valor.
 * 
 * Se produce un valor en secuencia (1,2,3,...) y se espera un tiempo aleatorio
 * 
 * @return int Valor producido
 * 
 * @param id_productor Identificador del productor. Desde 0 hasta num_productores-1
 */
int producir(int id_productor){
	static int contador = items_por_productor * id_productor;
	sleep_for( milliseconds( aleatorio<10,200>()) );
	contador++ ;
	cout << "Productor " << id_productor << " ha producido valor " << contador << endl << flush;
	return contador ;
}

/**
 * @brief Función que simula el consumo de un valor
 * 
 * @param valor_cons Valor a consumir
 * @param id_consumidor Identificador del consumidor. Desde 0 hasta num_consumidores-1
 */
void consumir( int valor_cons, int id_consumidor ){
	// espera bloqueada
	sleep_for( milliseconds( aleatorio<10,200>()) );
	cout << "Consumidor " << id_consumidor << " ha consumido valor " << valor_cons << endl << flush ;
}

/**
 * @brief Función que ejecuta la hebra del productor
 * 
 * @param id_productor Identificador del productor. Desde 0 hasta num_productores-1
 */
void funcion_productor(int id_productor){
	for ( unsigned int i= 0 ; i < items_por_productor ; i++ ){
		// producir valor
		int valor_prod = producir(id_productor);
		// enviar valor
		cout << "Productor " << id_productor << " va a enviar valor " << valor_prod << endl << flush;
		MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, etiq_productor, MPI_COMM_WORLD );
	}
}

/**
 * @brief Función que ejecuta la hebra del consumidor
 * 
 * @param id_consumidor Identificador del consumidor. Desde 0 hasta num_consumidores-1
 */
void funcion_consumidor( int id_consumidor ){
	int         peticion,
				valor_rec = 1 ;
	MPI_Status  estado ;

	for( unsigned int i=0 ; i < items_por_consumidor; i++ ){
		MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, etiq_consumidor, MPI_COMM_WORLD);
		MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, etiq_consumidor, MPI_COMM_WORLD,&estado );	// Esta etiqueta no sería necesaria
		cout << "Consumidor " << id_consumidor << " ha recibido valor " << valor_rec << endl << flush ;
		consumir( valor_rec, id_consumidor );
	}
}


/**
 * @brief Función que ejecuta la hebra del buffer
 */
void funcion_buffer(){
   int        buffer[tam_vector],      // buffer con celdas ocupadas y vacías
              valor,                   // valor recibido o enviado
              primera_libre       = 0, // índice de primera celda libre
              primera_ocupada     = 0, // índice de primera celda ocupada
              num_celdas_ocupadas = 0, // número de celdas ocupadas
              etiq_aceptable ;    // identificador de emisor aceptable
   MPI_Status estado ;                 // metadatos del mensaje recibido

   for( unsigned int i=0 ; i < num_items*2 ; i++ ){	// *2, una vez por cada valor producido y consumido
      
		// 1. determinar si puede enviar solo prod., solo cons, o todos
		if ( num_celdas_ocupadas == 0 )					// si buffer vacío
			etiq_aceptable = etiq_productor ;			// $~~~$ solo prod.
		else if ( num_celdas_ocupadas == tam_vector )	// si buffer lleno
			etiq_aceptable = etiq_consumidor ;			// $~~~$ solo cons.
		else											// si no vacío ni lleno
			etiq_aceptable = MPI_ANY_TAG ;				// $~~~$ cualquiera

		// 2. recibir un mensaje del emisor o emisores aceptables
		MPI_Recv( &valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_aceptable, MPI_COMM_WORLD, &estado );

		// 3. procesar el mensaje recibido
		switch( estado.MPI_TAG ){	// leer emisor del mensaje en metadatos
		
			case etiq_productor: // si ha sido un productor: insertar en buffer
				buffer[primera_libre] = valor ;
				primera_libre = (primera_libre+1) % tam_vector ;
				num_celdas_ocupadas++ ;
				cout << "Buffer ha recibido valor " << valor << " del productor " << obtener_id_productor(estado.MPI_SOURCE) << endl ;
				break;

			case etiq_consumidor: // si ha sido un consumidor: extraer y enviarle
				valor = buffer[primera_ocupada] ;
				primera_ocupada = (primera_ocupada+1) % tam_vector ;
				num_celdas_ocupadas-- ;
				cout << "Buffer va a enviar valor " << valor << " al consumidor " << obtener_id_consumidor(estado.MPI_SOURCE) << endl ;
				MPI_Ssend( &valor, 1, MPI_INT, estado.MPI_SOURCE, etiq_consumidor, MPI_COMM_WORLD );
				break;
		}
	}
}


// ---------------------------------------------------------------------
int main( int argc, char *argv[] ){
	int id_propio_global,
		num_procesos_actual;

	// inicializar MPI, leer identif. de proceso y número de procesos
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &id_propio_global );
	MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

	if ( num_procesos_esperado == num_procesos_actual ){
		// ejecutar la operación apropiada a 'id_propio'
		if ( es_productor( id_propio_global ) ){
			funcion_productor(obtener_id_productor( id_propio_global ));
		}
		else if ( es_buffer( id_propio_global ) )
			funcion_buffer();
		else if ( es_consumidor( id_propio_global ) ){
			funcion_consumidor(obtener_id_consumidor( id_propio_global ));
		}
		else	// A priori no debe llegar aquí
			cout << "Error: identificador de proceso desconocido" << endl;
	}
	else{
		
		if ( id_propio_global == 0 ){ // solo el primero escribe error, indep. del rol
			cout 	<< "el número de procesos esperados es:    " << num_procesos_esperado << endl
					<< "el número de procesos en ejecución es: " << num_procesos_actual << endl
					<< "(programa abortado)" << endl ;
		}
	}

	// al terminar el proceso, finalizar MPI
	MPI_Finalize( );
	return 0;
}



/**
 * 4 productores
 * 5 consumidores
 * 20 items
 * 10 celdas
 * 
 * items_por_productor = 5
 * productor 0 -> 1,2,3,4,5
 * productor 1 -> 6,7,8,9,10
 * productor 2 -> 11,12,13,14,15
 * productor 3 -> 16,17,18,19,20
 */