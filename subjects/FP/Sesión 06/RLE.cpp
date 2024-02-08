#include <iostream>

using namespace std;

int main(){
	
	const char TERMINADOR = '.';

	// ENTRADAS

	char caracter;

	cout << "A continuacion, introduzca la sucesion de caracteres que desea " 
		 << "codificar:" << endl;
	cout << "Para finalizar la introducción de datos, introduzca un \"" 
		 << TERMINADOR << "\"." << endl;

	cout << endl;

	cin >> caracter;

	// ENTRADAS Y CÁLCULOS

	// Variables útiles para el bucle

	int contador = 0;

	char caracter_anterior = caracter;

	string salida;		// Cadena cifrada

	// Bucle que permite seguir leyendo la entrada

	while(caracter != TERMINADOR){

		// Si el caracter es igual al anterior, sigue contando
		if(caracter == caracter_anterior)
			contador++;

		else{

			// Almacena la cuenta de los caracteres anteriores
			salida += to_string(contador) + " " + caracter_anterior + "  ";

			// Comienza una nueva cuenta
			contador = 1;

		}

		// Actualiza caracter_anterior
		caracter_anterior = caracter;

		// Lee el nuevo caracter
		cin >> caracter;
	
	}

	// Guarda la última sucesión de caracteres introducida en caso de que 
	// el primer caracter no sea TERMINADOR
	if(contador != 0)
		salida += to_string(contador) + " " + caracter_anterior;

	// SALIDAS

	cout << endl;

	// Si el primer caracter era TERMINADOR
	if(salida == "")
		cout << "No se introdujo ninguna cadena de caracteres" << endl;

	else{
		cout << "La cadena cifrada: " << endl;
		cout << salida << endl;
	}

	cout << endl;

	return 0;
}
