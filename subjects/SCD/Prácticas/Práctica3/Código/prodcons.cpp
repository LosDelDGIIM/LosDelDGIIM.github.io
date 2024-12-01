/**
 * @file prodcons.cpp
 * @brief Problema de los productores-consumidores distribuido con MPI
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
	id_productor          = 0 , // identificador del proceso productor
	id_buffer             = 1 , // identificador del proceso buffer
	id_consumidor         = 2 , // identificador del proceso consumidor
	num_procesos_esperado = 3 , // número total de procesos esperado
	num_items             = 20 , // numero de items producidos o consumidos
	tam_vector            = 10 ; // tamaño del vector



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
 */
int producir(){
	static int contador = 0 ;
	sleep_for( milliseconds( aleatorio<10,200>()) );
	contador++ ;
	cout << "Productor ha producido valor " << contador << endl << flush;
	return contador ;
}

/**
 * @brief Función que simula el consumo de un valor
 * 
 * @param valor_cons Valor a consumir
 */
void consumir( int valor_cons ){
	// espera bloqueada
	sleep_for( milliseconds( aleatorio<10,200>()) );
	cout << "Consumidor ha consumido valor " << valor_cons << endl << flush ;
}

/**
 * @brief Función que ejecuta la hebra del productor
 */
void funcion_productor(){
	for ( unsigned int i= 0 ; i < num_items ; i++ ){
		// producir valor
		int valor_prod = producir();
		// enviar valor
		cout << "Productor va a enviar valor " << valor_prod << endl << flush;
		MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD );
	}
}

/**
 * @brief Función que ejecuta la hebra del consumidor
 */
void funcion_consumidor(){
	int         peticion,
				valor_rec = 1 ;
	MPI_Status  estado ;

	for( unsigned int i=0 ; i < num_items; i++ ){
		MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD);
		MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD,&estado );
		cout << "Consumidor ha recibido valor " << valor_rec << endl << flush ;
		consumir( valor_rec );
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
              id_emisor_aceptable ;    // identificador de emisor aceptable
   MPI_Status estado ;                 // metadatos del mensaje recibido

   for( unsigned int i=0 ; i < num_items*2 ; i++ ){	// *2, una vez por cada valor producido y consumido
      
		// 1. determinar si puede enviar solo prod., solo cons, o todos
		if ( num_celdas_ocupadas == 0 )					// si buffer vacío
			id_emisor_aceptable = id_productor ;		// $~~~$ solo prod.
		else if ( num_celdas_ocupadas == tam_vector )	// si buffer lleno
			id_emisor_aceptable = id_consumidor ;		// $~~~$ solo cons.
		else											// si no vacío ni lleno
			id_emisor_aceptable = MPI_ANY_SOURCE ;		// $~~~$ cualquiera

		// 2. recibir un mensaje del emisor o emisores aceptables
		MPI_Recv( &valor, 1, MPI_INT, id_emisor_aceptable, 0, MPI_COMM_WORLD, &estado );

		// 3. procesar el mensaje recibido
		switch( estado.MPI_SOURCE ){	// leer emisor del mensaje en metadatos
		
			case id_productor: // si ha sido el productor: insertar en buffer
				buffer[primera_libre] = valor ;
				primera_libre = (primera_libre+1) % tam_vector ;
				num_celdas_ocupadas++ ;
				cout << "Buffer ha recibido valor " << valor << endl ;
				break;

			case id_consumidor: // si ha sido el consumidor: extraer y enviarle
				valor = buffer[primera_ocupada] ;
				primera_ocupada = (primera_ocupada+1) % tam_vector ;
				num_celdas_ocupadas-- ;
				cout << "Buffer va a enviar valor " << valor << endl ;
				MPI_Ssend( &valor, 1, MPI_INT, id_consumidor, 0, MPI_COMM_WORLD);
				break;
		}
	}
}


// ---------------------------------------------------------------------
int main( int argc, char *argv[] ){
	int id_propio, num_procesos_actual;

	// inicializar MPI, leer identif. de proceso y número de procesos
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
	MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

	if ( num_procesos_esperado == num_procesos_actual ){
		// ejecutar la operación apropiada a 'id_propio'
		if ( id_propio == id_productor )
			funcion_productor();
		else if ( id_propio == id_buffer )
			funcion_buffer();
		else
			funcion_consumidor();
	}
	else{
		
		if ( id_propio == 0 ){ // solo el primero escribe error, indep. del rol
			cout 	<< "el número de procesos esperados es:    " << num_procesos_esperado << endl
					<< "el número de procesos en ejecución es: " << num_procesos_actual << endl
					<< "(programa abortado)" << endl ;
		}
	}

	// al terminar el proceso, finalizar MPI
	MPI_Finalize( );
	return 0;
}
