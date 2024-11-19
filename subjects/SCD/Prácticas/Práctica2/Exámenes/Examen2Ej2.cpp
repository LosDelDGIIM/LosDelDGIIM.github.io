/**
 * @file Examen2_Ej2.cpp
 * @author Arturo Olivares Martos
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./Examen2.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica2/Exámenes/Examen2.md)
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

// Capacidad del mostrador. @PRE <= NUM_FUMADORES
const int CAPACIDAD = 2;

// Número de iteraciones del estanquero
const int NUM_ITEMS = 4;

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

      int mostrador[CAPACIDAD];     // Ingredientes en el mostrador
      CondVar ingr_no_disponible[num_fumadores];
      CondVar mostrador_lleno;

      bool abierto;

   public:
      Estanco();
      void ponerIngrediente(int vec[], int num);
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
   for (int i=0; i<CAPACIDAD; ++i)
      mostrador[i] = VACIO;
   for (int i=0; i<num_fumadores; ++i)
      ingr_no_disponible[i] = newCondVar();
   mostrador_lleno = newCondVar();
   abierto = true;
}

/**
 * @brief Función que pone una serie de ingredientes en el mostrador
 * 
 * @param vec Vector de ingredientes a poner
 * @param num número de ingredientes a poner
 */
void Estanco::ponerIngrediente(int vec[], int num){
   for (int i=0; i<num; ++i)
      mostrador[i] = vec[i];
   
   for (int i=0; i<num; ++i)
      ingr_no_disponible[vec[i]].signal();
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

      // Si el ingrediente no está en el mostrador, esperamos
      int pos = -1;
      for (int j=0; j<CAPACIDAD && pos==-1; ++j)
         if (mostrador[j] == i)
            pos = j;
      if (pos == -1)
         ingr_no_disponible[i].wait();

      // Por si se ha cerrado mientras estábamos bloqueados
      if (abierto){
         // Buscamos en qué posición está el ingrediente, y lo cogemos
         int pos = -1;
         for (int j=0; j<CAPACIDAD && pos==-1; ++j)
            if (mostrador[j] == i)
               pos = j;
               
         mostrador[pos] = VACIO;
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

   // Si alguna casilla de mostrador no es vacía, esperamos y volveremos a comprobar
   int pos=0;
   while (pos<CAPACIDAD){
      if (mostrador[pos] != VACIO){
         mostrador_lleno.wait();
         pos = 0;
      }
      else pos ++;
   }
   
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
   int num_ingr_producido[CAPACIDAD];

   for (int i=0; i<NUM_ITEMS; ++i){

      // Producimos los ingredientes
      for (int j=0; j<CAPACIDAD; ++j){
         
         bool encontrado = false;
         while (!encontrado){
            // Producimos hasta que sea distintos a todos los anteriores (j-1, j-2, ... , 0)
            num_ingr_producido[j] = producir_ingrediente();

            // Compruebo si es distinto a todos los anteriores
            bool repetido = false;
            for (int k=0; k<j && !repetido; ++k)
               repetido = (num_ingr_producido[j] == num_ingr_producido[k]);

            encontrado = !repetido;
         }
      }

      mtx_cout.lock();
         cout << "Estanquero : Todos los ingredientes producidos (";
         for (int k=0; k<CAPACIDAD; ++k)
            cout << num_ingr_producido[k] << " ";
         cout << ")" << endl << flush;
      mtx_cout.unlock();



      monitor->esperarRecogidaIngrediente();

      mtx_cout.lock();
         cout << i<< " Estanquero : Ingredientes puestos." << endl << flush;
      mtx_cout.unlock();
      monitor->ponerIngrediente(num_ingr_producido, CAPACIDAD);
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
