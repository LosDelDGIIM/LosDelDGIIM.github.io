/**
 * @file ejecutivo2.cpp
 * @author Arturo Olivares Martos
 * @brief Implementación del segundo ejemplo de ejecutivo cíclico.
 * @date 18 de diciembre de 2024
 * 
 * 
 * Datos de las tareas:
 * --------------------
 * Ta.  T    C
 * --------------------
 * A   500  100
 * B   500  150
 * C  1000  200
 * D  2000  240
 * 
 * El ciclo principal dura T_M
 *    T_M = \mcm(500, 500, 1000, 2000) = 2000
 * 
 * Respecto de la elección de T_S, tenemos que ha de cumplir:
 *    - T_S >= C_i para todo i
 *    - T_S ha de ser un divisor de T_M
 *    - Como sugerencia, T_S <= D_i para todo i
 *    
 *    Los distintos candidatos que planteamos son 250 o 500, pero elegimos:
 *    T_S = 500 ms.
 * 
 * Planificación (con Ts == 500 ms)
 * *--------*----------*---------*--------*
 * | A B C  | A B D    | A B C   | A B    |
 * *--------*----------*---------*--------*
 * 
 * Veamos cuánto tiempo se encuentra el procesador ocioso en cada ciclo secundario:
 * - Ciclo 1:
 *       - A: 100 ms
 *       - B: 150 ms
 *       - C: 200 ms
 *       - Ocioso: 50 ms
 * - Ciclo 2:
 *       - A: 100 ms
 *       - B: 150 ms
 *       - D: 240 ms
 *       - Ocioso: 10 ms
 * - Ciclo 3:
 *       - A: 100 ms
 *       - B: 150 ms
 *       - C: 200 ms
 *       - Ocioso: 50 ms
 * - Ciclo 4:
 *       - A: 100 ms
 *       - B: 150 ms
 *       - Ocio: 250 ms
 * 
 * Por tanto, el mínimo tiempo de espera que queda en cada ciclo secundario es de 10 ms (ciclo 2).
 * 
 * En el caso de que la tarea D tuviese un tiempo de cómputo de 250 ms, el ciclo 2 quedaría completo.
 * No obstante, debido al retraso que se produce en cada bloqueo, el ciclo 2 duraría más de 500ms, aunque esto no provoca problema porque el ciclo 3 está 50 ms ocioso.
 * En el caso de que esto ocurriese en el ciclo 4, como ya habríamos terminado el ciclo principal, no sería planificable.
 */

#include <string>
#include <iostream> // cout, cerr
#include <thread>
#include <chrono>   // utilidades de tiempo
#include <ratio>    // std::ratio_divide

using namespace std ;
using namespace std::chrono ;
using namespace std::this_thread ;

// tipo para duraciones en segundos y milisegundos, en coma flotante:
//typedef duration<float,ratio<1,1>>    seconds_f ;
typedef duration<float,ratio<1,1000>> milliseconds_f ;

/**
 * @brief Función que simula una tarea genérica con un nombre y un tiempo de cómputo.
 * 
 * @param nombre Nombre de la tarea.
 * @param tcomputo Tiempo de cómputo de la tarea.
 */
void Tarea( const std::string & nombre, milliseconds tcomputo ){
   cout << "   Comienza tarea " << nombre << " (C == " << tcomputo.count() << " ms.) ... " ;
   sleep_for( tcomputo );
   cout << "fin." << endl ;
}

// tareas concretas del problema:
void TareaA() { Tarea( "A", milliseconds(100) );  }
void TareaB() { Tarea( "B", milliseconds(150) );  }
void TareaC() { Tarea( "C", milliseconds(200) );  }
void TareaD() { Tarea( "D", milliseconds(240) );  }

// -----------------------------------------------------------------------------
// implementación del ejecutivo cíclico:
int main( int argc, char *argv[] ){
   // Ts = duración del ciclo secundario (en unidades de milisegundos, enteros)
   const milliseconds Ts_ms( 500 );

   // ini_sec = instante de inicio de la iteración actual del ciclo secundario
   time_point<steady_clock> ini_sec = steady_clock::now();

   while( true ){ // ciclo principal
   
      cout << endl
           << "---------------------------------------" << endl
           << "Comienza iteración del ciclo principal." << endl ;

      for( int i = 1 ; i <= 4 ; i++ ){ // ciclo secundario (4 iteraciones)
      
         cout << endl << "Comienza iteración " << i << " del ciclo secundario." << endl ;
         // Retraso al inicio del ciclo:
         milliseconds_f retraso = steady_clock::now() - ini_sec;
         cout << "Retraso: " << retraso.count() << " ms." << endl;

         switch( i ){
            case 1 : TareaA(); TareaB(); TareaC();           break ;
            case 2 : TareaA(); TareaB(); TareaD();           break ;
            case 3 : TareaA(); TareaB(); TareaC();           break ;
            case 4 : TareaA(); TareaB();                     break ;
         }

         // calcular el siguiente instante de inicio del ciclo secundario
         ini_sec += Ts_ms ;

         // esperar hasta el inicio de la siguiente iteración del ciclo secundario
         sleep_until( ini_sec );
      }
   }
}
