// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 9 (ejemplo9.cpp)
// Calculo concurrente de una integral mediante integración numérica.
//
// Historial:
// Creado en Abril de 2017
// Resuelto por Arturo Olivares en Septiembre de 2024
// -----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>  // incluye now, time\_point, duration
#include <future>
#include <vector>
#include <cmath>

using namespace std;
using namespace std::chrono;

const long num_muestras = 1024l*1024l*1024l,	// 2^{30} número de muestras (del orden de mil millones)
           num_hebras   = 2;					// número de hebras concurrentes (divisor de 'm')



/**
 * @brief Función que evalua la función f(x) = 4/(1+x^2)
 */
double f( double x ){
	return 4.0/(1.0+x*x) ;
}


/**
 * @brief Calcula la integral de forma secuencial.
 * 
 * Integral de la función f(x) = 4/(1+x^2) en el intervalo [0,1]
 * 
 * @return double Resultado de la integral
 */
double calcular_integral_secuencial(){

	double suma = 0.0 ;                                	// inicializar suma
	for (long j = 0 ; j < num_muestras ; j++){      	// para cada $j$ entre $0$ y $m-1$:
		const double x_j = double(j+0.5)/num_muestras;	//      calcular $x_j$
		suma += f(x_j);									//      añadir $f(x_j)$ a la suma actual
	}
	return suma/num_muestras;                         	// devolver valor promedio de $f$
}



/**
 * @brief Función que ejecuta cada hebra.
 * 
 * Procesa las muestras correspondientes a una hebra (desde i hasta i+num_muestras-1)
 * 
 * @param i Índice de la hebra, (0 <= i < n)
 */
double funcion_hebra(long i){

	double suma_parcial = 0.0 ;
	
	#define OPT_1

	#if defined(OPT_1)
		double muest_hebra = num_muestras/num_hebras;
		for (long j = i*muest_hebra; j < (i+1)*muest_hebra; ++j){
			const double x_j = double(j+0.5)/num_muestras;
			suma_parcial += f(x_j);
		}
	#elif defined(OPT_2)
		for (long j = i ; j < num_muestras ; j+=num_hebras){
			const double x_j = double(j+0.5)/num_muestras;
			suma_parcial += f(x_j);
		}
	#endif

	return suma_parcial;
}

/**
 * @brief Calcula la integral de forma concurrente.
 * 
 * Crea un array de futuros, uno por cada hebra, y lanza cada hebra.
 */
double calcular_integral_concurrente(){
	
	future<double> futuros[num_hebras];

	// Lanzamos cada una de las hebras
	for (long i = 0 ; i < num_hebras ; i++)
		futuros[i] = async(launch::async, funcion_hebra, i);
	
	// Acumulamos cada suma parcial
	double suma = 0.0 ;
	for (long i = 0 ; i < num_hebras ; i++)
		suma += futuros[i].get();

	return suma/num_muestras;
}


/**
 * @brief Función principal.
 */
int main(){

	// Ejecución secuencial
  time_point<steady_clock> inicio_sec  = steady_clock::now() ;
  const double             result_sec  = calcular_integral_secuencial();
  time_point<steady_clock> fin_sec     = steady_clock::now() ;

	// Ejecución concurrente
  time_point<steady_clock> inicio_conc = steady_clock::now() ;
  const double             result_conc = calcular_integral_concurrente();
  time_point<steady_clock> fin_conc    = steady_clock::now() ;

	// Cálculo de tiempos
  duration<float,milli>    tiempo_sec  = fin_sec  - inicio_sec ,
                           tiempo_conc = fin_conc - inicio_conc ;
  const float              porc        = 100.0*tiempo_conc.count()/tiempo_sec.count() ;

	// Constante PI
  constexpr double PI = 3.14159265358979323846 ;

  cout << "Número de muestras (m)   : " << num_muestras << endl
       << "Número de hebras (n)     : " << num_hebras << endl
       << setprecision(18)
       << "Valor de PI              : " << PI << endl
       << "Resultado secuencial     : " << result_sec  << endl
       << "Resultado concurrente    : " << result_conc << endl
       << setprecision(5)
       << "Tiempo secuencial        : " << tiempo_sec.count()  << " milisegundos. " << endl
       << "Tiempo concurrente       : " << tiempo_conc.count() << " milisegundos. " << endl
       << setprecision(4)
       << "Porcentaje t.conc/t.sec. : " << porc << "%" << endl;
}
