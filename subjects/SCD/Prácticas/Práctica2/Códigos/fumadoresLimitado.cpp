/**
 * @file fumadores.cpp
 * @brief Problema de los fumadores limitado con monitores
 * 
 * @author Arturo Olivares Martos
 */

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <vector>
#include "../../Práctica1/Código/scd.h"

using namespace std ;
using namespace scd ;

// numero de fumadores 
const int num_fumadores = 3 ;

// Número de iteraciones del estanquero
const int num_items = 5;

// Mutex cout
mutex mtx_cout;


//-------------------------------------------------------------------------
/**
 * @brief Función que simula la acción de producir un ingrediente
 * 
 * @return int Número de ingrediente producido
 */
int producir_ingrediente(){
   // calcular milisegundos aleatorios de duración de la acción de producción
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   mtx_cout.lock();
      cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;
   mtx_cout.unlock();

   // espera bloqueada un tiempo igual a 'duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   mtx_cout.lock();
      cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;
   mtx_cout.unlock();

   return num_ingrediente ;
}


/**
 * @brief Función que simula la acción de fumar.
 * Tiene un retardo aleatorio de la hebra.
 * 
 * @param num_fumador Número del fumador
 */
void fumar( int num_fumador ){

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar
   mtx_cout.lock();
      cout << "Fumador " << num_fumador << "  :"
         << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;
   mtx_cout.unlock();

   // espera bloqueada un tiempo igual a 'duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar
   mtx_cout.lock();
      cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
   mtx_cout.unlock();
}



class Estanco : public HoareMonitor{
   private:
      static const int VACIO = -1;

      int mostrador;    // Indica el ingrediente que hay en el mostrador. -1=No hay ingrediente
      CondVar ingr_no_disponible[num_fumadores];
      CondVar mostrador_lleno;

      bool abierto;

   public:
      Estanco();
      void ponerIngrediente(int i);
      bool obtenerIngrediente(int i);
      void esperarRecogidaIngrediente();
      void cierreEstanco();
      bool estaAbierto();
};

/**
 * @brief Constructor de la clase Estanco
 * 
 * Inicializa el mostrador a -1, ya que no hay ningún ingrediente en el mostrador
 */
Estanco::Estanco(){
   mostrador = VACIO;
   for (int i=0; i<num_fumadores; ++i)
      ingr_no_disponible[i] = newCondVar();
   mostrador_lleno = newCondVar();
   abierto = true;
}

/**
 * @brief Función que pone un ingrediente en el mostrador
 * 
 * @param i Ingrediente a poner
 */
void Estanco::ponerIngrediente(int i){
   mostrador = i;
   ingr_no_disponible[i].signal();
}

/**
 * @brief Función que obtiene un ingrediente del mostrador
 * 
 * @param i Ingrediente a obtener
 * @return true Si el estanco está abierto, false si está cerrado
 */
bool Estanco::obtenerIngrediente(int i){

   // Si el estanco está abierto
   if (abierto){

      // Si el ingrediente no es el que está en el mostrador, esperamos
      if (mostrador != i)
         ingr_no_disponible[i].wait();

      // Por si se ha cerrado mientras estábamos bloqueados
      if (abierto){
         // Lo cogemos, y avisamos al estanquero
         mostrador = VACIO;
         mtx_cout.lock();
            cout << "Fumador " << i << "  : Ingrediente retirado." << endl << flush;
         mtx_cout.unlock();
         mostrador_lleno.signal();
      }
   }
   return abierto;
}

/**
 * @brief Función que espera a que se recoja un ingrediente
 */
void Estanco::esperarRecogidaIngrediente(){
   if (mostrador != VACIO)
      mostrador_lleno.wait();
}

/**
 * @brief Función que cierra el estanco
 */
void Estanco::cierreEstanco(){
   abierto = false;

   // Desbloqueamos a los fumadores que estén esperando
   for (int i=0; i<num_fumadores; ++i)
      ingr_no_disponible[i].signal();
}

/**
 * @brief Función que indica si el estanco está abierto
 * 
 * @return true Si el estanco está abierto
 * @return false Si el estanco está cerrado
 */
bool Estanco::estaAbierto(){
   return abierto;
}



//----------------------------------------------------------------------
/**
 * @brief Función que ejecuta la hebra del estanquero
 * 
 * @param monitor Monitor del estanco
 */
void funcion_hebra_estanquero(MRef<Estanco> monitor){
   int num_ingr_producido;

   for (int i=0; i<num_items; ++i){
      num_ingr_producido = producir_ingrediente();
      monitor->esperarRecogidaIngrediente();

      mtx_cout.lock();
         cout << i<< " Estanquero : Ingrediente " << num_ingr_producido << " puesto." << endl << flush;
      mtx_cout.unlock();
      monitor->ponerIngrediente(num_ingr_producido);
   }
   monitor->esperarRecogidaIngrediente();

   mtx_cout.lock();
      cout << "Fin Estanquero : Cerramos." << endl << flush;
   mtx_cout.unlock();
   monitor->cierreEstanco();
}

/**
 * @brief Función que ejecuta la hebra de un fumador
 * 
 * @param num_fumador Número del fumador
 * @param monitor Monitor del estanco
 */
void  funcion_hebra_fumador( int num_fumador, MRef<Estanco> monitor ){
   
   /*
      ObtenerIngrediente es necesario que nos informe sobre si el estanco está abierto o cerrado
      Si esta funcion tan solo se encargase de esperar a que el ingrediente estuviese disponible,
         como tras obtener el último ingrediente se hace un signal y se libera al estanquero,
         este podría cerrar el estanco antes de que el fumador sepa que ese ingrediente es válido.
   */
   while (monitor->obtenerIngrediente(num_fumador))
      fumar(num_fumador);
}

//----------------------------------------------------------------------
int main(){

   MRef<Estanco> monitor = Create<Estanco>();
   
   thread hebra_estanquero(funcion_hebra_estanquero, monitor);
   thread hebra_fumador[num_fumadores];

   for (int i=0; i<num_fumadores; ++i)
      hebra_fumador[i]=thread(funcion_hebra_fumador, i, monitor);

   // Es necesario poner un join para que el main no termine antes que las hebras
   hebra_estanquero.join();
   for (int i=0; i<num_fumadores; ++i)
      hebra_fumador[i].join();

   return 0;
}
