#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
	
	const double SALTO = 0.01;
	const double PI = 6 * asin(0.5);

	double mu, sigma, x_inicial, x_final, salto_intervalo;

	// ENTRADAS

	do{

		cout << "Desviacion tipica (mayor que 0): ";
		cin >> sigma;
		cout << endl;

	}while(sigma <= 0);

	cout << "Media: ";
	cin >> mu;

	cout << endl;

	cout << "Introduzca un intervalo de abscisas: " << endl;
	cout << "\tLimite inferior: ";
	cin >> x_inicial;

	cout << "\tLimite superior: ";
	cin >> x_final;

	cout << endl;

	do{
	
		cout << "El salto entre valores (mayor que 0): ";
		cin >> salto_intervalo;

	}while(salto_intervalo <= 0);

	cout << endl << endl;

	// CÁLCULOS

	// Si el usuario introdujo en el límite superior del intervalo un valor
	// menor que el límite inferior del intervalo, lo modificamos para que
	// estén bien colocadas las variables:

	if(x_final < x_inicial){
		double auxiliar = x_final;
		x_final = x_inicial;
		x_inicial = auxiliar;
	}

	// La primera parte de la gaussiana no depende del valor de la abscisa,
	// calculamos ya su valor para reducir trabajo computacional
	double parte1_gaussiana = 1 / (sigma * sqrt(2 * PI));

	// Para reducir más trabajo computacional, calculamos la primera vez
	// la sumatoria de las alturas desde mu - 3 * sigma hasta la primera
	// abscisa del intervalo. Para la segunda abscisa, partimos de esta
	// sumatoria y continuamos hasta llegar a dicha abscisa
	// (algoritmo implementado en el bucle for anidado)
	
	double siguiente_abscisa_cdf = mu - 3 * sigma;

	double sumatoria_alturas = 0;

	// Formateamos la consola para las salidas

	cout.setf(ios::fixed);

	// Recorre todas las abscisas del intervalo especificado por el usuario
	// con el salto entre abscisa especificado por el usuario

	for(double i = x_inicial; i <= x_final; i += salto_intervalo){

		// i es el valor de la abscisa que se está procesando

		// 1.- Calculamos g(i)

		double parte2_gaussiana = exp(-0.5 * pow((i - mu) / sigma, 2));

		double gaussiana = parte1_gaussiana * parte2_gaussiana;

		// 2.- Calculamos CDF(i)

		// Recorre las abscisas desde la última que se tuvo en cuenta para
		// la sumatoria hasta i

		for(double j = siguiente_abscisa_cdf; j <= i; j += SALTO){

			// Se calcula la gaussiana en cada abscisa y se va sumando su
			// valor, obteniendo la sumatoria de las alturas de los rectangulos

			double parte2_gauss_CDF = exp(-0.5 * pow((j - mu) / sigma, 2));

			sumatoria_alturas += parte1_gaussiana * parte2_gauss_CDF;

		}

		// Multiplicamos la sumatoria de las alturas por la base (SALTO) de
		// los rectángulos para obtener la sumatoria del área de los
		// rectángulos, que es una aproximación de CDF(i) .

		double cdf = sumatoria_alturas * SALTO;

		// Calculamos la siguiente abscisa desde la que se partirá para 
		// calcular el siguiente CDF(i)

		siguiente_abscisa_cdf = i + SALTO;

		// SALIDAS

		cout << "g(" << setw(4) << setprecision(2) << i << ") = " 
			 << setw(12) << setprecision(10) << gaussiana;

		cout << "		";

		cout << "CDF(" << setw(4) << setprecision(2) << i << ") = " 
			 << setw(12) << setprecision(10) << cdf << "\n";

	}

	cout << endl;

	return 0;
}
