#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
	double kilometros_por_hora;
	int minutos, segundos;

	// Entradas
	cout << endl;
	cout << "Introduzca la velocidad del atleta en kilometros por hora: ";
	cin >> kilometros_por_hora;

	// Cálculos, basados en factores de conversión
	double tiempo = 1 / kilometros_por_hora;  //Calcula las horas por kilometro
	segundos = tiempo * 3600; 
	
	// Ajusta los tiempos para mostrarlos adecuadamente
	minutos = segundos / 60;
	segundos = segundos % 60;

	// Salida
	cout << endl;
	cout << kilometros_por_hora << " km/h son " << minutos << ":" << segundos << " min/km." << endl;
	cout << endl;

	return 0;
}
