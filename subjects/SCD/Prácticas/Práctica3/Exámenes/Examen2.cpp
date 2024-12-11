// El enunciado del problema se encuentra en el archivo:
// https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica3/Exámenes/Examen2.md

#include<iostream>
#include<thread>
#include<random>
#include<chrono>
#include<mpi.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

// Variables compartidas

const int id_buffer = 0;
const int id_cons_impar = 1;
const int id_cons_par = 2;
const int num_cons = 2;
const int num_prod = 3;
const int num_proc = 1 + num_cons + num_prod;

const int num_items = 4*num_cons*num_prod;

const int TAG_PROD = 1;
const int TAG_CONS = 2;

// --

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

#define dormir(a,b) sleep_for( milliseconds( aleatorio<a,b>() ) );

//

int Producir(int rank){
	int static contador = 0;
	dormir(10, 100);
	
	int dato = ((rank-3)*num_items/num_prod) + contador;
	contador++;
	return dato;
}

void funcion_productor(int rank){
	int dato;

	for(int i = 0; i < num_items/num_prod; i++){
		dato = Producir(rank);
		
		cout << "Productor " << rank-3 << " produce dato " << dato << endl;
		MPI_Ssend(&dato, 1, MPI_INT, id_buffer, TAG_PROD, MPI_COMM_WORLD);
	}
}

//

void Consumir(int rank, int dato){
	cout << "Consumidor " << ((rank % 2 == 0)?"par":"impar") << " consume dato " << dato << endl;
	dormir(110, 200);
}

void funcion_consumidor(int rank){
	int dato, peticion;
	MPI_Status status;
	
	for(int i = 0; i < num_items/num_cons; i++){
		MPI_Ssend(&peticion, 1, MPI_INT, id_buffer, TAG_CONS, MPI_COMM_WORLD);
		MPI_Recv(&dato, 1, MPI_INT, id_buffer, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		Consumir(rank, dato);
	}
}

//

const int TAM = 10;

void inline inc(int* i){
	*i = (*i+1) % TAM;
}

void prod(int& buff, int dato, int* ocupadas, int* primera_libre){
	buff = dato;
	(*ocupadas)++;
	inc(primera_libre);
}

void cons(int buff, int* dato, int* ocupadas, int* primera_ocupada, const MPI_Status* status){
	*dato = buff;
	(*ocupadas)--;
	inc(primera_ocupada);
	MPI_Ssend(dato, 1, MPI_INT, (*status).MPI_SOURCE, 0, MPI_COMM_WORLD);
}

void funcion_buffer(){
	int buffer[TAM];
	int primera_libre = 0;
	int primera_ocupada = 0;
	int ocupadas = 0;
	
	int tag, id, dato;
	MPI_Status status;
	int flag = 0;
	
	for(int i = 0; i < 2*num_items; i++){
		// Determina de quién debe recibir y recibe
		
		if(ocupadas == 0 || ocupadas == TAM){
		
			if(ocupadas == 0){
				tag = TAG_PROD;
				id = MPI_ANY_SOURCE;
			}else{
				tag = TAG_CONS;
				id = (buffer[primera_ocupada] % 2 == 0)? id_cons_par : id_cons_impar;
			}
			
			MPI_Recv(&dato, 1, MPI_INT, id, tag, MPI_COMM_WORLD, &status);
	
			switch(status.MPI_TAG){
				case TAG_PROD:
					prod(buffer[primera_libre], dato, &ocupadas, &primera_libre);
					break;
					
				case TAG_CONS:
					cons(buffer[primera_ocupada], &dato, &ocupadas, &primera_ocupada, &status);
					break;
			}
		
		}else{	// Recibo de productor o de consumidor correspondiente
		
			bool msg_a = false;
			bool msg_b = false;
			
			id = (buffer[primera_ocupada] % 2 == 0)? id_cons_par : id_cons_impar;
			
			do{
				// Mira si hay productores
				MPI_Iprobe(MPI_ANY_SOURCE, TAG_PROD, MPI_COMM_WORLD, &flag, &status);
				msg_a = flag > 0;
				
				// Mira si está el consumidor correspondiente
				MPI_Iprobe(id, TAG_CONS, MPI_COMM_WORLD, &flag, &status);
				msg_b = flag > 0;
				
			}while(!msg_a && !msg_b);	// Hasta que llegue uno de los dos
			
			// Damos prioridad al consumidor
			if(msg_b){
				MPI_Recv(&dato, 1, MPI_INT, id, TAG_CONS, MPI_COMM_WORLD, &status);
				cons(buffer[primera_ocupada], &dato, &ocupadas, &primera_ocupada, &status);
			}
			
			// Si también se recibió un productor
			if(msg_a) {
				MPI_Recv(&dato, 1, MPI_INT, MPI_ANY_SOURCE, TAG_PROD, MPI_COMM_WORLD, &status);
				prod(buffer[primera_libre], dato, &ocupadas, &primera_libre);
				
				// Una iteración menos
				if(msg_b) i++;
			}
			
		
		} // else
		
	} // for
}

// --

int main(int argc, char** argv){

	int size, rank;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(size == num_proc){
	
		if(rank == id_buffer){
			funcion_buffer();
		}else if(rank == id_cons_impar || rank == id_cons_par){
			funcion_consumidor(rank);
		}else{
			funcion_productor(rank);
		}
	
	}else{
		if(rank == 0){
			cerr << "Error: debe ejecutar el programa con " << num_proc << " procesos" << endl;
		}
	}
	
	MPI_Finalize();
	return 0;
}
