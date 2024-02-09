#include <iostream>

using namespace std;

int main(){

	const string SEPARADOR = " * ";
	const char EXPONENTE = '^';

	int numero;

	bool entrada_trivial;

	// ENTRADA

	do{

		cout << "Introduzca un entero positivo mayor que 0: "; 
		cin >> numero;

	}while(numero < 1);

	// Si nos piden descomponer 1 en factores primos
	entrada_trivial = numero == 1;

	// CÁLCULOS   *********************************************************

	// Trabajamos sobre una copia de numero
	int dividendo = numero;

	// Donde almacenamos las dos salidas
	string salida1, salida2;

	// Se realizan los cálculos si numero != 1
	if(!entrada_trivial){

		// Inicializamos divisor en el menor factor primo
		int divisor = 2;

		int divisor_anterior = divisor;

		// Contador de veces seguidas que aparece un mismo factor primo
		int veces = 0;

		// Mientras que dividendo siga teniendo factores primos
		while(dividendo != 1){

			// Mientras que divisor no sea un factor primo de dividendo
			// pasamos a analizar el siguiente
			while(dividendo % divisor != 0)
				divisor++;

			// Actualizamos dividendo para buscar más factores primos
			dividendo /= divisor;

			// Salida a

			// Almacenamos el factor primo en una salida
			salida1 += to_string(divisor);

			// Si no es el último factor primo, concatenamos SEPARADOR
			if(dividendo != 1)
				salida1 += SEPARADOR;

			// Salida b

			if(divisor == divisor_anterior)
				veces++;		// Vamos contando factores iguales

			else{
				// Si el contador no es 0, almacenamos el factor
				// (Podría ser 0 si 2 no es factor primo de numero)

				if(veces != 0){
					if(veces == 1)	// No indicamos el exponente
						salida2 += to_string(divisor_anterior) + SEPARADOR;

					else
						salida2 += to_string(divisor_anterior) + EXPONENTE 
								+ to_string(veces) + SEPARADOR;
				}

				veces = 1;	// Reiniciamos el contador
			}		
	
			divisor_anterior = divisor;   // Actualizamos divisor_anterior

		}  // Cierra while(dividendo != 1)

		// Salida b

		// Si la última secuencia de factores primos no se almacenó,
		// la almacenamos ahora

		if(veces != 0){
			if(veces == 1)		// No indicamos el exponente
				salida2 += to_string(divisor_anterior);

			else
				salida2 += to_string(divisor_anterior) + EXPONENTE 
							+ to_string(veces);

		}
			

	}  // Cierra if(!entrada_trivial)

	// SALIDAS

	cout << endl;

	// Si numero != 1
	if(!entrada_trivial){

		cout << numero << " = " << salida1 << endl;
		cout << numero << " = " << salida2 << endl;

	} else
		cout << "Por convenio, el 1 no se considera ni primo ni compuesto." << endl;

	cout << endl;

	return 0;
}
