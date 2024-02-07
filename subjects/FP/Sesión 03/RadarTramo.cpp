#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
    
	// Multiplicar por esta constante para pasar de km/h a m/s.
	double const MS = 1000.0/3600;
	double sector1 = 5.3, sector2 = 8.1, sector3 = 6.4;
	double vel_max1 = 80, vel_max2 = 100, vel_max3 = 80;

	// Cálculos: 
	// Calculamos los segundos necesarios para recorrer cada sector
	// a velocidad máxima, almacenánolos en la variable segundos.

	double segundos = (sector1 * 1000) / (vel_max1 * MS);	//Sector 1
	segundos += ((sector2 * 1000) / (vel_max2 * MS));	    //Sector 2
	segundos += ((sector3 * 1000) / (vel_max3 * MS));	    //Sector 3

	//Es posible que los segundos totales contengan decimales, los truncamos:
	int segundos_totales = segundos;

	//Salida: Imprimime el resultado en segundos y en minutos y segundos

	cout << endl;
	cout << "El tiempo que necesita un vehiculo en recorrer los tramos: " << endl;
	cout << "\tSector 1: " << sector1 << "km, a " << vel_max1 << "km/h." << endl;
	cout << "\tSector 2: " << sector2 << "km, a " << vel_max2 << "km/h." << endl;
	cout << "\tSector 3: " << sector3 << "km, a " << vel_max3 << "km/h." << endl;	
	cout << endl;

	cout << "Es de " << segundos_totales << " segundos." << endl;
	cout << "Que son " << (segundos_totales / 60) << " minutos y " << (segundos_totales % 60) << " segundos.";
	cout << endl;

	return 0;
}
