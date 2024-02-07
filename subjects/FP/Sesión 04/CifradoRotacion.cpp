#include <iostream>

using namespace std;

int main()
{
	int clave;
	char caracter;

	// Constantes que nos ayudarán en los cálculos para que el cáracter
	// codificado no se salga del intervalo [A, Z].
	const int MIN = 'A', MAX = 'Z';
	const int RANGO = MAX - MIN + 1; 	//Número de letras en [A, Z].

	// ENTRADAS

	cout << "La clave: ";
	cin >> clave;

	cout << "El caracter (mayuscula): ";
	cin >> caracter;

	// CÁLCULO
	
	char caracter_codificado = MIN + ((caracter - MIN + clave) % RANGO);

	/*
		Cualquier número y = MIN + (x % RANGO) (Sea x cualquier número)
		está dentro del intervalo [MIN, MAX].

		caracter - MIN está dentro del intervalo [MIN, MAX]
		Al sumarle la clave, puede que se salga, por lo que aplicamos
		la ecuación explicada anteriormente.
	*/

	// SALIDA

	cout << endl;
	cout << "El caracter codificado: " << caracter_codificado << endl;
	cout << endl;

	return 0;
}
