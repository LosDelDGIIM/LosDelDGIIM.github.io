#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	// Declaraciones
	double desviacion_tipica, media, x;
	const double PI = 6 * asin(0.5);

	// Entradas
	cout << endl;
	cout << "Introduzca la desviacion tipica de la funcion gaussiana: ";
	cin >> desviacion_tipica;
	cout << "Introduzca la media de la funcion gaussiana: ";
	cin >> media;
	cout << "Introduzca el valor de la abscisa en la que desea evaluar la funcion: ";
	cin >> x;

	// Calculos: calculamos gaussiana(x):

	double gaussiana = (1 / (desviacion_tipica * sqrt(2 * PI))) * 
		exp(-1/2.0 * pow( ((x - media) / desviacion_tipica), 2));

	// Salida
	cout << endl;
	cout << "El valor de la funcion gaussiana de desviacion tipica " << desviacion_tipica << ", media " << media << ", evaluada en la abscisa " 
		<< x << " es de: " << gaussiana << endl;
	cout << endl;

	return 0;
}
