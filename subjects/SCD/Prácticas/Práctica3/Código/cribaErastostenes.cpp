/**
 * @file cribaErastostenes.cpp
 * @brief Problema de la criba de Eratóstenes distribuida como un pipeline de procesos
 * 
 * Si hay N+1 procesos, los primeros N procesos obtienen un primo y el N+1-ésimo imprime los primos.
 * Por tanto, se hayan los primeros N primos.
 * 
 * @note 	Compilación: 	mpicxx -std=c++11 -g -Wall -o cribaErastostenes cribaErastostenes.cpp
 * 			Ejecución: 		mpirun --oversubscribe -np N+1 ./cribaErastostenes
 * 
 * @author Arturo Olivares Martos
 * @date 01/12/2024
 */

#include <iostream>
#include <mpi.h>

using namespace std;

// Bandera que indica que se ha terminado de buscar los primos
bool fin=false;

// Valor que enviaremos para indicar que se ha terminado de buscar los primos
const int TERMINA=-1;

/**
 * @brief Función que implementa el proceso impresor
 * 
 * @param num_primos Número de primos a imprimir
 */
void funcion_impresor(int num_primos){
	int primo_recibido;
	MPI_Status status;

	cout << "Números primos:" << endl;

	// Recibimos los números primos de los filtros y los imprimimos
	for (int i = 0; i < num_primos; i++){
		MPI_Recv(&primo_recibido, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
		cout << "\t- Proceso " << status.MPI_SOURCE << " (Primo " << i+1<< "):\t" << primo_recibido << endl << flush;
	}

	// Notificamos al primer filtro que hemos terminado.
	// No podemos notificar a todos, porque los procesos están bloqueados esperando recibir un candidato del filtro anterior
	// 		y si no se les notifica, no terminarán. Por tanto, ha de propagarse la notificación
	MPI_Send(&TERMINA, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

/**
 * @brief Función que implementa el primer proceso filtro.
 * 
 * Su primo asociado es el primer primo (2).
 * Envía al siguiente filtro los números mayores que 2 que no son múltiplos de 2, es decir, los impares.
 * 
 * @param rank_impresor Identificador del proceso impresor
 */
void funcion_primer_filtro(int rank_impresor){
	int rank = 0;	// Este es el rank del primer filtro

	int primo=2,	// Primo asociado a este filtro
		x=1;		// Candidatos a primos, ya que no son múltiplos del primo. Tener en cuenta que se va a sumar 2

	int flag;		// Ahí se espera recibir el mensaje de terminación

	// Enviamos el primer primo al impresor
	MPI_Send(&primo,1,MPI_INT,rank_impresor,0,MPI_COMM_WORLD);

	// Enviamos los impares al siguiente filtro
	while(!fin){
		x+=2;
		MPI_Send(&x,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
		
		MPI_Iprobe(rank_impresor,0,MPI_COMM_WORLD,&flag,MPI_STATUS_IGNORE);
		if (flag>0){	// SI ha llegado un mensaje del impresor, consultamos si es de terminación
			// Este Recv no sería necesario, ya que el impresor solo envía una vez. Pero es buena práctica
			MPI_Recv(&flag,1,MPI_INT,rank_impresor,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			fin = (flag==TERMINA);
		}
	}

	// Notificamos al siguiente filtro que hemos terminado
	MPI_Send(&TERMINA,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
}


/**
 * @brief Función que implementa un proceso filtro.
 * 
 * Del filtro anterior, recibe los que pueden ser candidatos a primos (no múltiplos de los primos anteriores).
 * Su primo asociado será el primer candidato que reciba.
 * Enviará al siguiente filtro los candidatos que no sean múltiplos de su primo asociado.
 * 
 * @param rank_impresor Identificador del proceso impresor
 * @param rank Identificador del proceso
 */
void funcion_filtro(int rank_impresor, int rank){
	int primo,	// Primo asociado a este filtro. Sus múltiplos no los envía al siguiente filtro, se descartan
		x=0;	// Candidatos a primos, ya que no son múltiplos de ninguno de los múltiplos anteriores
	

	// Recibimos del filtro anterior un primo (por ser el primer candidato que recibimos)
	MPI_Recv(&primo,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

	// Enviamos el primo recibido al impresor
	MPI_Send(&primo,1,MPI_INT,rank_impresor,0,MPI_COMM_WORLD);

	while(!fin){

		// Recibimos un candidato del filtro anterior
		MPI_Recv(&x,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		
		// Se comprueba si ha recibido el mensaje de terminación
		fin = (x==TERMINA);

		// Si el número recibido no es múltiplo de este primo (tampoco será múltiplo de los primos anteriores)
		// 		es un candidato, por lo que lo enviamos al siguiente filtro	
		if (x%primo != 0 || fin)	// También propagamos el mensaje de terminación
			MPI_Send(&x,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
	}
}


/**
 * @brief Función que implementa el último proceso filtro.
 * Es un proceso filtro normal, pero envía los candidatos al siguiente filtro (puesto que es el impresor).
 * 
 * Del filtro anterior, recibe los que pueden ser candidatos a primos (no múltiplos de los primos anteriores).
 * Su primo asociado será el primer candidato que reciba.
 * 
 * @param rank_impresor Identificador del proceso impresor
 */
void funcion_ultimo_filtro(int rank_impresor){
	int primo;	// Primo asociado a este filtro. Sus múltiplos no los envía al siguiente filtro, se descartan
	
	int rank = rank_impresor-1;	// Este es el rank del último filtro

	// Recibimos del filtro anterior un primo (por ser el primer candidato que recibimos)
	MPI_Recv(&primo,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

	// Enviamos el primo recibido al impresor
	MPI_Send(&primo,1,MPI_INT,rank_impresor,0,MPI_COMM_WORLD);
}


// ---------------------------------------------------------------------
int main( int argc, char *argv[] ){
	int rank, size;

	// inicializar MPI, leer identif. de proceso y número de procesos
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	// Comprobamos que el número de procesos es mayor que 3 (impresor, primer filtro y último filtro)
	if (size < 3){
		cerr << "El número de procesos ha de ser mayor que 3" << endl;
		MPI_Finalize( );
		return 1;
	}

	int num_primos_buscados = size - 1;	// Número de primos a buscar				


	if (rank == size -1){	// Se trata del proceso impresor
		funcion_impresor(num_primos_buscados);
	}else if (rank == 0){	// Se trata del primer proceso filtro. Ha de iniciar
		funcion_primer_filtro(size-1);
	}else if (rank == size-2){	// Se trata del último proceso filtro.
		funcion_ultimo_filtro(size-1);
	}else{	// Se trata de un proceso filtro
		funcion_filtro(size-1, rank);
	}

	// Al terminar el proceso, finalizar MPI
	MPI_Finalize( );
	return 0;
}
