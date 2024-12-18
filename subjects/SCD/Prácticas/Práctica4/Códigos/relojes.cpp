// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 4. Implementación de sistemas de tiempo real.
//
// Archivo: relojes.cpp
// Consulta de las características de los relojes C++11
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

// -----------------------------------------------------------------------------

template< typename ClockType, typename TimeUnit = std::chrono::nanoseconds >
inline constexpr double precision_reloj()
{
  typedef std::ratio_divide< typename ClockType::duration::period,
                             typename TimeUnit::period >  periodType ;
  return double( periodType::num )/ double( periodType::den );
}

// -----------------------------------------------------------------------------

template< typename ClockType >
void informe_reloj( const std::string & nomReloj )
{
   cout << endl << "--------------------------------------------------" << endl
                << "Características del reloj: " << nomReloj << endl
                << "--------------------------------------------------" << endl ;
   cout << "Período (precisión)                = " << precision_reloj<ClockType>() << " nanosegundos."<< endl ;
   typename ClockType::duration t_epoca = ClockType::now().time_since_epoch() ; // tiempo desde a época
   const duration<float,ratio<3600> > t_epoca_horas( t_epoca ); // tiempo desde la época expresado en horas con parte fraccionaria
   cout << "Tiempo desde el inicio de la época = " << t_epoca_horas.count() << " horas." << endl << flush ;
   cout << "Es un reloj monotónico             = " << (ClockType::is_steady ? "sí" : "no") << endl << flush ;
}
// -----------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
   informe_reloj<system_clock>("system_clock") ;
   informe_reloj<steady_clock>("steady_clock") ;
   informe_reloj<high_resolution_clock>("high_resolution_clock") ;
}
