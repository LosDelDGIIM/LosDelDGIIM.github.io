#include <iostream>
#include <cmath>

using namespace std;

int main(){
	double latitud1, latitud2, longitud1, longitud2, altura1, altura2;

	const double PI = 6*asin(0.5);
	const double GRADOS_A_RADIANES = PI / 180;

	const double RADIO_TERRESTRE = 6372797.560856;
	const int METROS_A_KM = 1000;

	// ENTRADAS

	cout << "Punto 1: " << endl;
	cout << "\tLatitud [-90, 90]: "; 
	cin >> latitud1;
	cout << "\tLongitud [-180, 180]: ";
	cin >> longitud1;
	cout << "\tAltura: ";
	cin >> altura1;
	
	cout << endl;

	cout << "Punto 2: " << endl;
	cout << "\tLatitud [-90, 90]: "; 
	cin >> latitud2;
	cout << "\tLongitud [-180, 180]: ";
	cin >> longitud2;
	cout << "\tAltura: ";
	cin >> altura2;

	// CÁLCULOS
	// Pasamos los datos de longitud y latitud a radianes para operar con 
	// ellos:
	
	double rad_latitud1 = latitud1 * GRADOS_A_RADIANES;
	double rad_latitud2 = latitud2 * GRADOS_A_RADIANES;
	double rad_longitud1 = longitud1 * GRADOS_A_RADIANES;
	double rad_longitud2 = longitud2 * GRADOS_A_RADIANES;

	// Calculamos los datos a y c de la fórmula del Haversine:

	double a = pow(sin(0.5*(rad_latitud2 - rad_latitud1)), 2) 
		+ cos(rad_latitud1) * cos(rad_latitud2) 
		* pow(sin(0.5*(rad_longitud2 - rad_longitud1)), 2);

	// Calculamos cual es el mínimo entre 1 y sqrt(a):
	double min = (1.0 <= sqrt(a)) ? 1 : sqrt(a);

	double c = 2 * asin(min);

	double distancia_plano = RADIO_TERRESTRE * c;

	double diferencia_alturas = abs(altura1 - altura2);

	// Calculamos la distancia real entre los dos puntos, sabiendo que es la
	// hipotenusa del triángulo rectángulo que forman los catetos de
	// distancia_plano y diferencia_alturas.

	double distancia_real = 
		sqrt(pow(distancia_plano, 2) + pow(diferencia_alturas, 2));

	// Finalmente, expresamos las distancias en kilómetros:
	distancia_plano = distancia_plano / METROS_A_KM;
	distancia_real = distancia_real / METROS_A_KM;

	// SALIDAS

	cout << endl;
	cout << "Distancia sobre el plano: " << distancia_plano << " km." << endl;
	cout << "Distancia real: " << distancia_real << " km." << endl;
	cout << endl;

	return 0;
}
