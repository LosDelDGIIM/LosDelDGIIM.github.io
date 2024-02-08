#include <iostream>

using namespace std;

int main(){
	
	int numero;

	bool error_lectura = false;

	// ENTRADA

	do{
		// Imprime al usuario por qué su entrada no es válida.
		if(error_lectura)
			cout << endl << "Debe introducir un numero entero positivo." 
				 << endl;

		cout << "Numero entero positivo: ";
		cin >> numero;

		error_lectura = numero <= 0;

	}while(error_lectura);

	// CÁLCULOS

	string salida;	// Donde se van almacenando todos los divisores 

	// Recorre todos los enteros del 1 a numero
	for(int i = 1; i <= numero; i++){

		// Si el resto es 0, es un divisor
		if(numero % i == 0)
			// Lo añadimos a la lista de divisores
			salida += " " + to_string(i);

	}

	// SALIDA

	cout << endl;
	cout << "Los divisores de " << numero << " son:" << salida << endl;
	cout << endl;

	return 0;
}
