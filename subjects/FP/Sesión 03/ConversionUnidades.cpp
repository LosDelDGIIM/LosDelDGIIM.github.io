#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
	double metros;
	const double PULGADA_MM = 25.4, PIE_CM = 30.48, YARDA_M = 0.9144, MILLA_KM = 1.609344;

	// Entrada
	cout << endl;
	cout << "Introduzca la distancia (en metros): ";
	cin >> metros;

	// Cálculos, basados en factores de conversión
	double pulgadas = metros * 1000 / PULGADA_MM;
	double pies = metros * 100 / PIE_CM;
	double yardas = metros * YARDA_M;
	double millas = metros / 1000 / MILLA_KM;

	// Salidas
	cout << endl;
	cout << metros << " metros son: " << endl;
	cout << "\t" << pulgadas << " pulgadas." << endl;
	cout << "\t" << pies << " pies." << endl;
	cout << "\t" << yardas << " yardas." << endl;
	cout << "\t" << millas << " millas." << endl;
	cout << endl;

	return 0;
}
