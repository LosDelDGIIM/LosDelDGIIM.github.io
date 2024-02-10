#include <iostream>

using namespace std;

int main(){
	
	const int MIN = 0, MAX = 100;

	// Número de valores entre MIN y MAX
	const int NUM_VALORES = MAX - MIN + 1;

	int num_intentos[NUM_VALORES];

	// CÁLCULOS

	// Calculamos los intentos en todos los valores entre MIN y MAX

	int jugadas;
	int intento;
	int max_generar, min_generar;

	int casilla = 0;

	for(int i = MIN; i <= MAX; i++){

		// i es el número a adivinar

		jugadas = 0;

		max_generar = MAX;
		min_generar = MIN;

		// Se ejecuta hasta que lo adivine

		do{
			// Se calcula el punto medio de [min_generar, max_generar]
			intento = (max_generar + min_generar) / 2;

			// Se van cerrando las cotas del intervalo
			// (+1 o -1 porque como intento != i, no nos interesa
			// incluir dicho valor en el intervalo, si no el siguiente valor)

			if(i > intento)
				min_generar = intento + 1;

			else
				max_generar = intento - 1;
	
			jugadas++;		// Aumentan las jugadas

		}while(intento != i);

		// Se guarda el número de jugadas que ha costado adivinar i

		num_intentos[casilla] = jugadas;

		casilla++;
	}

	// SALIDAS

	cout << endl;

	casilla = 0;

	// Se muestra el número de intentos por cada número

	for(int i = MIN; i <= MAX; i++){

		cout << "Numero:	" << i << "	Intentos:	" << num_intentos[casilla] 
			 << endl;

		casilla++;

	}

	cout << endl;

	return 0;
}
