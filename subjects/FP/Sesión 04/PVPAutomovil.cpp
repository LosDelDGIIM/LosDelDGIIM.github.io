#include <iostream>

using namespace std;

int main()
{
    // Declaración de variables

	double precio;

	const double PORC_IVA = 0.16, PORC_GANANCIA = 0.2;

	// ENTRADA

	cout << "El precio del vehiculo: ";
	cin >> precio;

	// CÁLCULOS

	double ganancias = precio * PORC_GANANCIA;

	double iva_aplicado = precio * PORC_IVA;

	double precio_final = precio + ganancias + iva_aplicado;

	// SALIDA

	cout << endl;
	cout << "El precio final del vehiculo: " << precio_final << endl;
	cout << endl;

	return 0;
}
