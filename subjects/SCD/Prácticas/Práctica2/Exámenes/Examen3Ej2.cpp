/**
 * @file Examen3_Ej2.cpp
 * @author Arturo Olivares Martos
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./Examen3.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica2/Exámenes/Examen3.md)
 */
#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> 
#include <chrono> 
#include "../../Práctica1/Código/scd.h"

using namespace std ;
using namespace scd ;

constexpr int 
	escritores = 2,
	lectores = 4,
	min_ms = 500,	// Tiempo mínimo de escritura
	max_ms = 2000;	// Tiempo máximo de escritura y Tiempo de Lectura

mutex mtx;

/**
 * @brief Clase para monitor Lectores-Escritores.
 * 
 * @note Semántica SC
 */
class Lectores_Escritores : public HoareMonitor{
	private:
	    bool escribiendo;
	    int nlectores;
	    CondVar lectura,	// Cola de lectores
				escritura;	// Cola de escritores
        
    
	public:
	    Lectores_Escritores();
	    void lectura_ini();
	    void lectura_fin();
	    void escritura_ini();
	    void escritura_fin();
};


/**
 * @brief Constructor de la clase Lectores_Escritores.
 */
Lectores_Escritores::Lectores_Escritores(){
	escribiendo = false;
	nlectores = 0;
	
	lectura = newCondVar();
	escritura = newCondVar();
}


/**
 * @brief Función que inicia la lectura.
 */
void Lectores_Escritores::lectura_ini(){
	
	if (escribiendo) lectura.wait();
	
	nlectores++;

	lectura.signal();	// Despertamos a otro lector, para que lea
}

/**
 * @brief Función que finaliza la lectura.
 */
void Lectores_Escritores::lectura_fin(){
	nlectores--;
	
	if (nlectores == 0)		// Si no hay más lectores, despertamos a un escritor
		escritura.signal();	
}

/**
 * @brief Función que inicia la escritura.
 */
void Lectores_Escritores::escritura_ini(){
	if (escribiendo || nlectores > 0)
		escritura.wait();
	
	
	escribiendo = true;
}

/**
 * @brief Función que finaliza la escritura.
 * 
 * @note Prioriza a los lectores.
 */
void Lectores_Escritores::escritura_fin(){
	escribiendo = false;
	
	// Priorizamos a los lectores. Si hay un lector, le dejamos leer
	if (!lectura.empty()) 
	    lectura.signal();
	else 
	    escritura.signal();
}




/**
 * @brief Clase para monitor Buffer, semántica SC, múltiples productores/consumidores.
 * 
 * @note Funciona para versión FIFO
 */
class Buffer : public HoareMonitor{
	private:
	static const int           // constantes ('static' ya que no dependen de la instancia)
   		num_celdas_total = 3;   //   núm. de entradas del buffer
 	int                        // variables permanentes
   		buffer[num_celdas_total],//   buffer de tamaño fijo, con los datos

		primera_libre,          //   indice de celda de la próxima inserción
		primera_ocupada,        //   indice de celda de la próxima extracción
		ocupadas;               //   Número de celdas ocupadas

	CondVar                    // colas condicion:
		buffer_vacio,            //  cola donde esperan los consumidores (n>0)
		buffer_lleno ;           //  cola donde esperan los productores  (n<num_celdas_total)

	public:                    // constructor y métodos públicos
		Buffer() ;             // constructor
		int  Extraer( int &N);                // extraer un valor (sentencia L) (consumidor)
		void Escribir( int numero_escritor ); // insertar un valor (sentencia E) (productor)
} ;

/**
 * @brief Constructor de la clase Buffer.
 */
Buffer::Buffer(){
	primera_libre   = 0;
	primera_ocupada = 0;
	ocupadas        = 0;

	buffer_lleno   = newCondVar();
	buffer_vacio   = newCondVar();
}

/**
 * @brief Función que extrae un valor del buffer.
 * 
 * @param N Número de celdas ocupadas tras la extracción. Parámetro de salida.
 */
int Buffer::Extraer(int &N){

	// esperar bloqueado hasta que 0 < ocupadas
	if ( ocupadas == 0 ) buffer_vacio.wait();

   // hacer la operación de lectura, actualizando estado del monitor
	int valor = buffer[primera_ocupada] ;
	primera_ocupada++ ;
	primera_ocupada %= num_celdas_total ;
	ocupadas-- ;

	// Ya se ha contabilizado la extracción.
	N=ocupadas;
   
	// señalar al productor que hay un hueco libre, por si está esperando
	buffer_lleno.signal();

	// devolver valor
	return valor ;
}


/**
 * @brief Función que escribe un valor en el buffer.
 * 
 * @param numero_escritor Valor a escribir.
 */
void Buffer::Escribir( int numero_escritor ){

	// esperar bloqueado hasta que haya hueco para escribir un valor
    if ( ocupadas == num_celdas_total ) buffer_lleno.wait();

	buffer[primera_libre] = numero_escritor ;
	primera_libre++ ;
	primera_libre %= num_celdas_total ;
	ocupadas++ ;

	// señalar al consumidor que ya hay una celda ocupada (por si esta esperando)
	buffer_vacio.signal();
}



/**
 * @brief Función que simula la hebra de un escritor.
 * 
 * @param monitor Monitor de lectores-escritores.
 * @param i Número del escritor.
 * @param buffer Buffer de escritura compartido con la hebra impresora.
 */
void funcion_hebra_escritora(MRef<Lectores_Escritores> monitor, int i, MRef<Buffer> buffer){
	while (true){
		monitor->escritura_ini();
			buffer->Escribir(i);	// Escribe en el buffer.
		    mtx.lock();
		        cout << "..........................................Escritor: " << i << " ESCRIBIENDO" << endl;
			mtx.unlock();
		    chrono::milliseconds duracion(aleatorio < min_ms, max_ms > ());
		    this_thread::sleep_for(duracion);
		monitor->escritura_fin();
	}		
}

/**
 * @brief Función que simula la hebra de la impresora.
 * 
 * @param buffer Buffer de escritura compartido con las hebras escritoras.
 */
void funcion_hebra_impresora(MRef<Buffer> buffer){
	int N;
	while (true){
		// Si queremos ver como se llena el buffer, tenemos que dejar que escriban
		// Dormimos la hebra durante un tiempo de 3s
		// this_thread::sleep_for(chrono::milliseconds(3000));

		int id_escritor = buffer->Extraer(N);
		mtx.lock();
			cout << ".......ESCRIBIÓ EL ESCRITOR " << id_escritor << ". HAY " << N << " ELEMENTOS EN EL BUFFER" << endl;
		mtx.unlock();
	}		
}

/**
 * @brief Función que simula la hebra de un lector.
 * 
 * @param monitor Monitor de lectores-escritores.
 * @param i Número del lector.
 */
void funcion_hebra_lectora(MRef<Lectores_Escritores> monitor, unsigned i){
	while (true){
		monitor->lectura_ini();
		    mtx.lock();
		        cout << "LECTOR: " << i << " leyendo" << endl;
			mtx.unlock();
		monitor->lectura_fin();

		chrono::milliseconds duracion(aleatorio < max_ms, max_ms > ());
	    this_thread::sleep_for(duracion);
	}	
}


//**********************************************************************
int main()
{
	MRef<Lectores_Escritores> monitor = Create<Lectores_Escritores>();
	MRef<Buffer> buffer = Create<Buffer>();

	
	thread hebras_escritoras[escritores], hebras_lectoras[lectores];
	
	thread impresora(funcion_hebra_impresora, buffer);
	for (int i = 0; i < escritores; i++)
		hebras_escritoras[i] = thread(funcion_hebra_escritora,monitor,i, buffer);
	for (int i = 0; i < lectores; i++) 
	    hebras_lectoras[i] = thread(funcion_hebra_lectora,monitor,i);
	
	impresora.join();
	for (int i = 0; i < escritores; i++) hebras_escritoras[i].join();
	for (int i = 0; i < lectores; i++) 	hebras_lectoras[i].join();

	return 0;
}