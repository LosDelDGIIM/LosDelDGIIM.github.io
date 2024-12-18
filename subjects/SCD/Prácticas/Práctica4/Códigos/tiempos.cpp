// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 4. Implementación de sistemas de tiempo real.
//
// Archivo: tiempos.cpp
// Operaciones con duraciones e instantes.
//
// Historial:
// Creado en Diciembre de 2017
// -----------------------------------------------------------------------------

#include <string>
#include <iostream> // cout, cerr
#include <thread>
#include <chrono>   // utilidades de tiempo
#include <ratio>    // std::ratio_divide

using namespace std ;
using namespace std::chrono ;

// tipo para duraciones en segundos, en coma flotante:
typedef duration<float,ratio<1,1000>> milliseconds_f ;

void medir_sleep_for() ;
void medir_sleep_until() ;

// -----------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
   medir_sleep_for();
   medir_sleep_until();
}
// -----------------------------------------------------------------------------

void medir_sleep_for()
{
   time_point<steady_clock> instante_inicio = steady_clock::now() ;

   this_thread::sleep_for( milliseconds(200) );

   time_point<steady_clock> instante_fin   = steady_clock::now() ;
   steady_clock::duration   duracion       = instante_fin - instante_inicio ;

   cout << endl
        << "Medición de duración de 'sleep_for( 200ms )'" << endl
        << "   duración == " << milliseconds_f(duracion).count() << " milisegundos." << endl ;
}
// -----------------------------------------------------------------------------

void medir_sleep_until()
{
   time_point<steady_clock> instante_inicio    = steady_clock::now(),
                            instante_despertar = instante_inicio + seconds(1) ;

   this_thread::sleep_until( instante_despertar );

   time_point<steady_clock> instante_fin       = steady_clock::now() ;
   steady_clock::duration duracion             = instante_fin - instante_inicio ;
   cout << endl
        << "Medición de duración de 'sleep_until( 1 segundo en el futuro )'" << endl
        <<"    duración = " << milliseconds_f(duracion).count() <<" milisegundos." << endl;
}
