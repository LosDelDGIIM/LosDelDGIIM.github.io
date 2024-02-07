#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int numero;

	// ENTRADA

	cout << "Introduzca el numero: ";
	cin >> numero;

	// CALCULOS

	int bits = log2(numero) + 1;

	// SALIDA

	cout << endl;
	cout << "Seran necesarios " << bits << " bits en binario." << endl;
	cout << endl;

	return 0;
}
