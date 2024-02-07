#include <iostream>

using namespace std;

int main()
{
	//Declaraciones
	double distancia_recorrida, litros_consumidos, litros_restantes;
	
	//Entradas
	cout << endl;
	cout << "Introduzca el numero de kilometros que ha recorrido con su " << "vehiculo: ";
	cin >> distancia_recorrida;

	cout << "Introduzca los litros que ha consumido su vehiculo durante esos " << distancia_recorrida << " kilometros: ";
	cin >> litros_consumidos;

	cout << "Finalmente, introduzca los litros restantes que contiene el " << "deposito de su vehiculo: ";
	cin >> litros_restantes;

	//Cálculos, basados en factores de conversión
	double kilometros_por_litro = distancia_recorrida / litros_consumidos;
	double litros_por_100km = 100 / kilometros_por_litro;
	double km_de_autonomia = litros_restantes * kilometros_por_litro;

	//Salidas
	cout << endl;
	cout << endl;
	cout << "Su vehiculo es capaz de recorrer " << kilometros_por_litro << " kilometros por litro." << endl;
	cout << "Cada 100km, su vehiculo consume " << litros_por_100km << " litros." << endl;
	cout << "Con " << litros_restantes << " litros restantes en el deposito, " << "su vehiculo es capaz de recorrer " << km_de_autonomia << 
		" kilometros." << endl;
	cout << endl;

	return 0;
}
