/**
 * @file Examen3_Ej2.cpp
 * @author Gonzalo Olmo
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./Examen3.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica3/Exámenes/Examen3.md
 */

#include <chrono> // duraciones (duration), unidades de tiempo
#include <cstdlib>
#include <iostream>
#include <mpi.h>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <thread> // this_thread::sleep_for

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

#define TERM -1

const int
	etiq_prod = 1,
	etiq_cons = 2,
	num_prod = 4,
	num_cons = 5,
    id_ini_productores = 0,
    id_ini_consumidores = num_prod + 1,
    id_buffer = num_prod,
    num_procesos_esperado = num_prod + num_cons + 1,
    num_items = 20,
    tam_vector = 10;

/**
 * @brief Función que produce un número aleatorio entre dos valores
 * 
 * @tparam min Valor mínimo. Constante conocida en tiempo de compilación
 * @tparam max Valor máximo. Constante conocida en tiempo de compilación
 */
template <int min, int max> int aleatorio() {
	static default_random_engine generador((random_device())());
	static uniform_int_distribution<int> distribucion_uniforme(min, max);
	return distribucion_uniforme(generador);
}
// ---------------------------------------------------------------------
/**
 * @brief Función que simula la producción de un valor entre 0 y 9
 * 
 * @note Duerme un tiempo aleatorio entre 10 y 100 milisegundos
 * 
 * @return int Valor producido
 */
int producir() {
	sleep_for(milliseconds(aleatorio<10, 100>()));
	return aleatorio<0, 9>();
}

/**
 * @brief Función que simula la consumición de un valor
 * 
 * @param orden Orden del consumidor (global)
 */
void funcion_productor(int orden) {
	for (unsigned int i = 0; i < num_items/num_prod; i++) {
		// producir valor
		int valor_prod = producir();
		int rec;
		MPI_Status estado;
		// enviar valor
		cout << "Productor va a enviar valor " << valor_prod << endl << flush;
		MPI_Ssend(&valor_prod, 1, MPI_INT, id_buffer, etiq_prod, MPI_COMM_WORLD);
		MPI_Recv(&rec, 1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD, &estado);
		if (rec == TERM) {
			break;
		}
		MPI_Ssend(&valor_prod, 1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD);
	}
	cout << "Termina productor " << orden<< endl;
}
// ---------------------------------------------------------------------

void consumir(int valor_cons) {
	// espera bloqueada
	sleep_for(milliseconds(aleatorio<110, 200>()));
	cout << "Consumidor ha consumido valor " << valor_cons << endl << flush;
}
// ---------------------------------------------------------------------

void funcion_consumidor(int orden) {
	int peticion, valor_rec = 1;
	MPI_Status estado;

	for (unsigned int i = 0; i < num_items/num_cons; i++) {
		MPI_Ssend(&peticion, 1, MPI_INT, id_buffer, etiq_cons, MPI_COMM_WORLD);
		MPI_Recv(&valor_rec, 1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD, &estado);
		if (valor_rec == TERM) {
			break;
		}
		cout << "Consumidor ha recibido valor " << valor_rec << endl << flush;
		consumir(valor_rec);
	}
	cout << "Termina consumidor " << orden << endl;
}

/**
 * @brief Función que simula un buffer de tamaño tam_vector
 */
void funcion_buffer() {
	int buffer[tam_vector],      // buffer con celdas ocupadas y vacías
	    valor,                   // valor recibido o enviado
	    primera_libre = 0,       // índice de primera celda libre
	    primera_ocupada = 0,     // índice de primera celda ocupada
	    num_celdas_ocupadas = 0; // número de celdas ocupadas
	MPI_Status estado;           // metadatos del mensaje recibido
	bool terminar = false;

	for (unsigned int i = 0; i < num_items * 2 && !terminar; i++) {
		// 1. determinar si puede enviar solo prod., solo cons, o todos
		int etiq;

		if (num_celdas_ocupadas == 0)               // si buffer vacío
			// solo prods
			etiq = etiq_prod;
		else if (num_celdas_ocupadas == tam_vector) // si buffer lleno
			// solo cons
			etiq = etiq_cons;
		else                                        // si no vacío ni lleno
			// cualquiera
			etiq = MPI_ANY_TAG;

		// 2. recibir un mensaje del emisor o emisores aceptables

		MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq, MPI_COMM_WORLD,
		         &estado);

		// 3. procesar el mensaje recibido

		switch (estado.MPI_TAG){ // leer emisor del mensaje en metadatos

			case etiq_prod: // si ha sido el productor: insertar en buffer
				// Da permiso
				MPI_Ssend(&valor, 1, MPI_INT, estado.MPI_SOURCE, 0, MPI_COMM_WORLD);
				MPI_Recv(&valor, 1, MPI_INT, estado.MPI_SOURCE, 0, MPI_COMM_WORLD, &estado) ;

				// Dos valores iguales consecutivos recibidos
				if (valor == buffer[(primera_libre-1)%tam_vector]) {
					cout << "Empezamos a terminar el programa" << endl;
					terminar = true;
					int aux;
					MPI_Request request;
					// terminar procesos productores
					for (int i = 0; i < id_buffer; i++) {
						MPI_Irecv(&aux, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
						MPI_Irecv(&aux, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
						aux = TERM;
						MPI_Ssend(&aux, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
					}

					// terminar procesos consumidores
					for (int i = id_buffer+1; i < num_procesos_esperado; i++) {
						MPI_Irecv(&aux, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
						aux = TERM;
						MPI_Ssend(&aux, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
					}
				}
				if (!terminar) {
					buffer[primera_libre] = valor;
					primera_libre = (primera_libre + 1) % tam_vector;
					num_celdas_ocupadas++;
					cout << "Buffer ha recibido valor " << valor << endl;
				}
				break;

			case etiq_cons: // si ha sido el consumidor: extraer y enviarle
				if (!terminar) {
					valor = buffer[primera_ocupada];
					primera_ocupada = (primera_ocupada + 1) % tam_vector;
					num_celdas_ocupadas--;
					cout << "Buffer va a enviar valor " << valor << endl;
					MPI_Ssend(&valor, 1, MPI_INT, estado.MPI_SOURCE, 0, MPI_COMM_WORLD);
				}
				break;
		}
	}
	cout << "Termina buffer" << endl;
}

// ---------------------------------------------------------------------

int main(int argc, char *argv[]) {
	int id_propio, num_procesos_actual;

	if (num_items%num_prod != 0 || num_items%num_prod != 0) {
		cout << "Numero de productores y consumidores no valido" << endl;
		exit(1);
	}

	// inicializar MPI, leer identif. de proceso y número de procesos
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id_propio);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procesos_actual);

	if (num_procesos_esperado == num_procesos_actual) {
		// ejecutar la operación apropiada a 'id_propio'
		if (id_ini_productores <= id_propio && id_propio < id_ini_productores + num_prod)
			funcion_productor(id_propio-id_ini_productores);
		else if (id_propio == id_buffer)
			funcion_buffer();
		else
			funcion_consumidor(id_propio-id_ini_consumidores);
	} else {
		if (id_propio == 0) // solo el primero escribe error, indep. del rol
		{
			cout << "el número de procesos esperados es:    "
			     << num_procesos_esperado << endl
			     << "el número de procesos en ejecución es: "
			     << num_procesos_actual << endl
			     << "(programa abortado)" << endl;
		}
	}

	// al terminar el proceso, finalizar MPI
	MPI_Finalize();
	return 0;
}
