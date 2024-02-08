#include <iostream>
#include <cmath>

using namespace std;

int main(){
	
	const double PI = 6 * asin(0.5);

	const double SALTO = 0.1;

	double mu, sigma, x;

	bool error_sigma = false;

	// ENTRADAS  ***********************************************************

	// Se asegura de que sigma no sea 0

	do{
		// Imprime que sigma debe ser mayor que 0, en caso de haber introducido
		// un valor de sigma menor o igual a 0
		if(error_sigma)
			cout << endl << "La desviacion tipica debe ser mayor que 0." 
				 << endl;

		cout << "Desviacion Tipica: ";
		cin >> sigma;

		error_sigma = sigma <= 0;

	}while(error_sigma);

	// Mu (la media) y x pueden adoptar el valor de cualquier real

	cout << endl;
	cout << "Media: ";
	cin >> mu;

	cout << endl;
	cout << "El valor de x (abscisa) para CDF(x): ";
	cin >> x;

	// CÁLCULOS  *********************************************************

	// Calculamos la primera parte de la gaussiana, no depende de la abscisa

	double parte1_gaussiana = 1 / (sigma * sqrt(2 * PI));

	// La abscisa donde comenzamos la sumatoria

	double x_inicial = mu - 3 * sigma;

	// Cálculo de la sumatoria de las alturas, desde x_inicial hasta el x 
	// especificado por el usuario, realizando saltos de SALTO entre los 
	// sumandos. Usamos la variable "x sub i" en el bucle

	double sumatoria_alturas = 0;

	for(double xi = x_inicial; xi <= x; xi += SALTO){
		
		// Segunda parte de la gaussiana, depende de xi:

		double parte2_gaussiana = exp(-0.5 * pow((xi - mu) / sigma, 2));

		// Obtenemos el valor de la gaussiana en xi

		double gaussiana = parte1_gaussiana * parte2_gaussiana;

		// Vamos realizando la sumatoria de las alturas

		sumatoria_alturas += gaussiana;

	}

	// Multiplicamos la base de los rectángulos por la sumatoria de las alturas
	// para obtener la sumatoria del área de los rectángulos

	double sumatoria_areas = SALTO * sumatoria_alturas;

	// SALIDA  ********************************************************

	cout << endl << endl;
	cout << "CDF(" << x << ") = " << sumatoria_areas << endl;
	cout << endl;

	return 0;
}





