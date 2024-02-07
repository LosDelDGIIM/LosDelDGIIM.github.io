#include <iostream>

using namespace std;

int main()
{
	// Numero de posiciones que hay que retroceder en la tabla ASCII
	// para pasar de minúscula a mayúscula.
    
	const int POSICIONES_ASCII = 'a' - 'A';
	char caracter_in;

	// ENTRADA

	cout << "Un caracter en minuscula: ";
	cin >> caracter_in;

	// CÁLCULO
	// Retrocede las posicinoes indicadas en la tabla ASCII.
    
	char caracter_out = caracter_in - POSICIONES_ASCII;

	// SALIDA
	cout << endl;
	cout << "Su caracter: " << caracter_out << endl;
	cout << endl;

	return 0;
}
