#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
	int minutos, segundos;
	double kilometros_por_hora;

	// Entradas
	cout << endl;
	cout << "Introduzca la velocidad del atleta en minutos y segundos por kilometro: " << endl;
	cout << "\tMinutos (valor entero): ";
	cin >> minutos;
	cout << "\tSegundos (valor entero): ";
	cin >> segundos;

	// Cálculos, basados en un factor de conversión.
	kilometros_por_hora = 1 / (minutos / 60.0 + segundos / 3600.0);
	
	// Salida
	cout << endl;
	cout << minutos << ":" << segundos << " min/km son " << kilometros_por_hora << " km/h." << endl;
	cout << endl;

	return 0;
}
