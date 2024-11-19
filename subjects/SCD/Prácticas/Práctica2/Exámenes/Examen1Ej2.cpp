/**
 * @file Examen1_Ej2.cpp
 * @author Arturo Olivares Martos
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./ExamenI.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica2/Exámenes/ExamenI.md)
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


const int NUM_FUM = 4;
const int NUM_INGS = NUM_FUM -1; // ID 1, NUM_FUM-1 compiten
const int INGR_CODICIADO = 1; // Compiten por el ingrediente 1

// Número de iteraciones del estanquero
const int NUM_ITMS = 5;

// Mutex cout
mutex mtx_cout;

// Número de cigarros fumados por cada fumador
int num_cigarros[NUM_FUM] = {0};


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

   const int num_ingrediente = aleatorio<0,NUM_INGS-1>() ;

   // informa de que ha terminado de producir
   mtx_cout.lock();
      cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;
   mtx_cout.unlock();

   return num_ingrediente ;
}


class Estanco : public HoareMonitor{
   private:
      int mostrador;    // Indica el ingrediente que hay en el mostrador. -1=No hay ingrediente
      CondVar ingr_no_disponible[NUM_FUM];
      CondVar mostrador_lleno;

      bool abierto;

      bool ini_verif;
      CondVar verif;
   public:
      Estanco();
      void ponerIngrediente(int i);
      bool obtenerIngredientePara(int i);
      void esperarRecogidaIngrediente();
      void cierreEstanco();
      bool estancoAbierto();

      void verificacion();
      void inicia_verificacion();
};

/**
 * @brief Constructor de la clase Estanco
 * 
 * Inicializa el mostrador a -1, ya que no hay ningún ingrediente en el mostrador
 */
Estanco::Estanco(){
   mostrador = -1;
   for (int i=0; i<NUM_FUM; ++i)
      ingr_no_disponible[i] = newCondVar();
   mostrador_lleno = newCondVar();
   abierto = true;

   ini_verif = false;
   verif = newCondVar();
}

/**
 * @brief Función que pone un ingrediente en el mostrador
 * 
 * @param i Ingrediente a poner
 */
void Estanco::ponerIngrediente(int i){
   mostrador = i;

   // Si es el ingrediente INGR_CODICIADO, elegimos de forma aleatoria a quién se lo damos
   int elegido = i;
   if (i == INGR_CODICIADO){
      int aux = aleatorio<0,1>();
      elegido = (aux == 0) ? INGR_CODICIADO : NUM_FUM-1;
      mtx_cout.lock();
         cout << "Estanquero : He decidido dar el ingrediente " << i << " al fumador " << elegido << endl << flush;
      mtx_cout.unlock();
   }

   // Despertamos al fumador que necesita el ingrediente
   ingr_no_disponible[elegido].signal();
}

/**
 * @brief Función que obtiene un ingrediente del mostrador
 * 
 * @param id Fumador que quiere el ingrediente
 * * @return true Si el estanco está abierto, false si está cerrado
 */
bool Estanco::obtenerIngredientePara(int id){

   // Si el estanco está abierto
   if (abierto){

      int ingr = id; // Por defecto, el fumador coge el ingrediente asociado a su ID
      if (id == NUM_FUM-1)    // Si es el fumador que compite por el ingrediente codiciado
         ingr = INGR_CODICIADO;

      mtx_cout.lock();
         cout << "Fumador " << id << "  : Esperando ingrediente " << ingr << endl << flush;
      mtx_cout.unlock();


      // Si el ingrediente no es el que está en el mostrador, esperamos
      if (mostrador != ingr)
      ingr_no_disponible[id].wait();

      // Por si se ha cerrado mientras estábamos bloqueados
      if (abierto){
         // Lo cogemos, y avisamos al estanquero
         mostrador = -1;
         mtx_cout.lock();
            cout << "Fumador " << id << "  : Ingrediente " << ingr << " retirado." << endl << flush;
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
   if (mostrador != -1)
      mostrador_lleno.wait();
}

/**
 * @brief Función que cierra el estanco
 */
void Estanco::cierreEstanco(){
   abierto = false;

   // Desbloqueamos a los fumadores que estén esperando
   for (int i=0; i<NUM_FUM; ++i)
      ingr_no_disponible[i].signal();

   // Desbloqueamos a la hebra verificadora
   verif.signal();
}

/**
 * @brief Función que indica si el estanco está abierto
 * 
 * @return true Si el estanco está abierto
 * @return false Si el estanco está cerrado
 */
bool Estanco::estancoAbierto(){
   return abierto;
}

/**
 * @brief Función que realiza la verificación de los ingredientes
 */
void Estanco::verificacion(){
   if (!ini_verif)
      verif.wait();
   
   if (estancoAbierto()){

      // Mostramos el número de cigarros fumados por los que compiten por el ingrediente codiciado
      mtx_cout.lock();
         cout << "VERIFICACIÓN" << endl << flush;
         cout << "\t- Fumador " << INGR_CODICIADO << "  : Ha fumado " << num_cigarros[INGR_CODICIADO] << " cigarros." << endl << flush;
         cout << "\t- Fumador " << NUM_FUM-1 << "  : Ha fumado " << num_cigarros[NUM_FUM-1] << " cigarros." << endl << flush;
      mtx_cout.unlock();

      ini_verif = false;
   }
}


/**
 * @brief Función que inicia la verificación
 */
void Estanco::inicia_verificacion(){
   ini_verif = true;
   verif.signal();
}


//----------------------------------------------------------------------
/**
 * @brief Función que ejecuta la hebra del estanquero
 * 
 * @param monitor Monitor del estanco
 */
void funcion_hebra_estanquero(MRef<Estanco> monitor){
   int num_ingr_producido;

   int num_veces_ingr[NUM_INGS] = {0};
   const int NUM_LIM = 12;

   for (int i=0; i<NUM_ITMS; ++i){
      num_ingr_producido = producir_ingrediente();
      num_veces_ingr[num_ingr_producido]++;
      if (num_ingr_producido == INGR_CODICIADO && num_veces_ingr[num_ingr_producido] == NUM_LIM){
         monitor->inicia_verificacion();
      }
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

/**
 * @brief Función que ejecuta la hebra de un fumador
 * 
 * @param num_fumador Número del fumador
 * @param monitor Monitor del estanco
 */
void funcion_hebra_fumador( int num_fumador, MRef<Estanco> monitor ){
   
   while (monitor->obtenerIngredientePara(num_fumador)){
      fumar(num_fumador);
      num_cigarros[num_fumador]++;
   }
}


void funcion_hebra_verificadora(MRef<Estanco> monitor){
   while (monitor->estancoAbierto()){
      monitor->verificacion();
   }
}

//----------------------------------------------------------------------
int main(){

   MRef<Estanco> monitor = Create<Estanco>();
   
   thread hebra_estanquero(funcion_hebra_estanquero, monitor);
   thread hebra_verificadora(funcion_hebra_verificadora, monitor);
   thread hebra_fumador[NUM_FUM];

   for (int i=0; i<NUM_FUM; ++i)
      hebra_fumador[i]=thread(funcion_hebra_fumador, i, monitor);

   // Es necesario poner un join para que el main no termine antes que las hebras
   hebra_estanquero.join();
   hebra_verificadora.join();
   for (int i=0; i<NUM_FUM; ++i)
      hebra_fumador[i].join();

   return 0;
}
