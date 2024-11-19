/**
 * @file prodcons_su.cpp
 * @brief Fichero de implementación de un monitor SU para el problema del productor/consumidor.
 * 
 * Se puede elegir entre versión LIFO o FIFO, dependiendo de si se define LIFO o FIFO.
 * @author Arturo Olivares Martos
 */

#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include <mutex>
#include "../../Práctica1/Código/scd.h"

using namespace std;
using namespace scd;

constexpr int
   num_items = 40,   // número de items a producir/consumir
   num_productores = 4, // número de productores
   num_consumidores = 8; // número de consumidores
int
   siguiente_dato = 0; // siguiente valor a devolver en 'producir_dato'
   
constexpr int               
   min_ms    = 5,     // tiempo minimo de espera en sleep_for
   max_ms    = 20 ;   // tiempo máximo de espera en sleep_for


mutex
   mtx_cout;                 // mutex de escritura en pantalla
unsigned
   cont_prod[num_items] = {0}, // contadores de verificación: producidos
   cont_cons[num_items] = {0}; // contadores de verificación: consumidos



/**
 * @brief Función que simula la producción de un dato.
 * 
 * @param id_productor Identificador del productor.
 * @param n Posición del dato que se ha de producir.
 * 
 * @return unsigned Dato producido.
 */
unsigned producir_dato(int id_productor, int n){
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = id_productor * num_items/num_productores + n ;
   cont_prod[dato_producido] ++ ;
   mtx_cout.lock();
      cout << "Productor " << id_productor << " produce: " << dato_producido << endl << flush ;
   mtx_cout.unlock();
   return dato_producido ;
}

/**
 * @brief Función que simula el consumo de un dato.
 * 
 * @param dato Dato a consumir.
 * @param id_consumidor Identificador del consumidor.
 */
void consumir_dato( int id_consumidor, unsigned dato ){
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx_cout.lock();
      cout << "\t\t\t\t\tConsumidor " << id_consumidor << " consume: " << dato << endl ;
   mtx_cout.unlock();
}

/**
 * @brief Función que comprueba los contadores de producción y consumo.
 */
void test_contadores(){
   bool ok = true ;
   cout << "comprobando contadores ...." << endl ;

   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      if ( cont_prod[i] != 1 )
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

// *****************************************************************************
// clase para monitor buffer, version LIFO, semántica SC, multiples prod/cons


// #define LIFO
#define FIFO

/**
 * @brief Clase para monitor buffer, semántica SC, múltiples productores/consumidores.
 * 
 * @note Funciona para versión LIFO o FIFO, depende del define LIFO o FIFO.
 */
class Buffer : public HoareMonitor
{
 private:
 static const int           // constantes ('static' ya que no dependen de la instancia)
   num_celdas_total = 10;   //   núm. de entradas del buffer
 int                        // variables permanentes
   buffer[num_celdas_total],//   buffer de tamaño fijo, con los datos
   #ifdef LIFO
   primera_libre ;            //   indice de celda de la próxima inserción ( == número de celdas ocupadas)
   #elif defined FIFO
      primera_libre,          //   indice de celda de la próxima inserción
      primera_ocupada,        //   indice de celda de la próxima extracción
      ocupadas;               //   Número de celdas ocupadas
   #endif

 CondVar                    // colas condicion:
   buffer_vacio,            //  cola donde espera el consumidor (n>0)
   buffer_lleno ;           //  cola donde espera el productor  (n<num_celdas_total)

 public:                    // constructor y métodos públicos
   Buffer() ;             // constructor
   int  leer();                // extraer un valor (sentencia L) (consumidor)
   void escribir( int valor ); // insertar un valor (sentencia E) (productor)
} ;

/**
 * @brief Constructor de la clase Buffer.
 */
Buffer::Buffer(){
   #ifdef LIFO
      primera_libre = 0 ;
   #elif defined FIFO
      primera_libre   = 0;
      primera_ocupada = 0;
      ocupadas        = 0;
   #endif

   buffer_lleno   = newCondVar();
   buffer_vacio   = newCondVar();
}

/**
 * @brief Función que extrae un valor del buffer.
 */
int Buffer::leer(){

   // Esperamos a que haya algún valor en el buffer
   #ifdef LIFO
      // esperar bloqueado hasta que 0 < primera_libre
      if ( primera_libre == 0 ) buffer_vacio.wait();
   #elif defined FIFO
      // esperar bloqueado hasta que 0 < ocupadas
      if ( ocupadas == 0 ) buffer_vacio.wait();
   #endif

   // hacer la operación de lectura, actualizando estado del monitor
   int valor;
   #ifdef LIFO
      primera_libre-- ;
      valor = buffer[primera_libre] ;
   #elif defined FIFO
      valor = buffer[primera_ocupada] ;
      primera_ocupada++ ;
      primera_ocupada %= num_celdas_total ;
      ocupadas-- ;
   #endif
   
   // señalar al productor que hay un hueco libre, por si está esperando
   buffer_lleno.signal();

   // devolver valor
   return valor ;
}


/**
 * @brief Función que escribe un valor en el buffer.
 * 
 * @param valor Valor a escribir.
 */
void Buffer::escribir( int valor ){

   // esperar bloqueado hasta que haya hueco para escribir un valor
   #ifdef LIFO
      // esperar bloqueado hasta que primera_libre < num_celdas_total
      if ( primera_libre == num_celdas_total ) buffer_lleno.wait();
   #elif defined FIFO
      // esperar bloqueado hasta que primera_libre < num_celdas_total
      if ( ocupadas == num_celdas_total ) buffer_lleno.wait();
   #endif

   // hacer la operación de inserción, actualizando estado del monitor
   #ifdef LIFO
      buffer[primera_libre] = valor ;
      primera_libre++ ;
   #elif defined FIFO
      buffer[primera_libre] = valor ;
      primera_libre++ ;
      primera_libre %= num_celdas_total ;
      ocupadas++ ;
   #endif

   // señalar al consumidor que ya hay una celda ocupada (por si esta esperando)
   buffer_vacio.signal();
}


// -----------------------------------------------------------------------------
/**
 * @brief Función que simula la hebra productora.
 * @param id_hebra Identificador de la hebra.
 * @param monitor Monitor.
 */
void funcion_hebra_productora( int id_hebra, MRef<Buffer> monitor ){
   
   int items_por_productor = num_items/num_productores;
   for( unsigned i = 0 ; i < items_por_productor ; i++ ){
      int valor = producir_dato( id_hebra, i );
      monitor->escribir( valor );
   }
}

/**
 * @brief Función que simula la hebra consumidora.
 * @param id_hebra Identificador de la hebra.
 * @param monitor Monitor.
 */
void funcion_hebra_consumidora( int id_hebra, MRef<Buffer>  monitor ){
   int items_por_consumidor = num_items/num_consumidores;
   for( unsigned i = 0 ; i < items_por_consumidor ; i++ ){
      int valor = monitor->leer();
      consumir_dato( id_hebra, valor );
   }
}

int main()
{
   cout << "--------------------------------------------------------------------" << endl
        << "Problema del productor-consumidor únicos (Monitor SU)               " << endl
        << "--------------------------------------------------------------------" << endl
        << flush ;

   // crear monitor  ('monitor' es una referencia al mismo, de tipo MRef<...>)
   MRef<Buffer> monitor = Create<Buffer>() ;

   // crear y lanzar los productores y consumidores
   thread hebra_prod[num_productores], hebra_cons[num_consumidores];
   for( unsigned i = 0 ; i < num_productores ; i++ )
      hebra_prod[i] = thread( funcion_hebra_productora, i, monitor );
   for( unsigned i = 0 ; i < num_consumidores ; i++ )
      hebra_cons[i] = thread( funcion_hebra_consumidora, i, monitor );

   // esperar a que terminen las hebras
   for( unsigned i = 0 ; i < num_productores ; i++ )
      hebra_prod[i].join();
   for( unsigned i = 0 ; i < num_consumidores ; i++ )
      hebra_cons[i].join();

   test_contadores() ;
}
