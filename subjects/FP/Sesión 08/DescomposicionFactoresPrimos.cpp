#include <iostream>

using namespace std;

/****************************************************************************
	Función que devuelve un string que contiene el resultado de la
	descomposición en factores primos de n

  Parámetros: n
  Devuelve: Una cadena que muestra los factores primos de n, con el formato:
					primo * primo * ... * primo

****************************************************************************/

string Calcula_DescFactPrimos_1 (int n){
	string resultado;	

	// Menor primo posible
	int divisor = 2;

	// Mientras que n tenga factores primos

	while(n != 1){
		// Mientras que divisor no sea un factor primo de n
		// pasamos a analizar el siguiente
		while(n % divisor != 0)
			divisor++;
	
		// Actualizamos n para buscar más factores primos
		n /= divisor;
	
		// Almacenamos el factor primo en resultado
		resultado += to_string(divisor);
	
		// Si no es el último factor primo, concatenamos el asterisco
		if(n != 1)
			resultado += " * ";
	} 

	return resultado;
}

/****************************************************************************
	Función que devuelve un string que contiene el resultado de la
	descomposición en factores primos de n

  Parámetros: n
  Devuelve: Una cadena que muestra los factores primos de n, con el formato:
  primo_1^veces_primo_1 * primo_2^veces_primo_2 * ... * primo_n^veces_primo_n

****************************************************************************/

string Calcula_DescFactPrimos_2 (int n){
	string resultado;	

	const string MULTIPLICAR = " * ";
	const char EXPONENTE = '^';

	int divisor = 2;
	int divisor_anterior = divisor;

	// Contador de veces seguidas que aparece un mismo factor primo
	int veces = 0;

	// Mientras que n siga teniendo factores primos
	while(n != 1){

		// Mientras que divisor no sea un factor primo de n
		// pasamos a analizar el siguiente
		while(n % divisor != 0)
			divisor++;

		// Actualizamos n para buscar más factores primos
		n /= divisor;

		if(divisor == divisor_anterior)
			veces++;		// Vamos contando factores iguales

		else{
			// Si el contador no es 0, almacenamos el factor
			// (Podría ser 0 si 2 no es factor primo de numero)

			if(veces != 0){
				if(veces == 1)	// No indicamos el exponente
					resultado += to_string(divisor_anterior) + MULTIPLICAR;

				else
					resultado += to_string(divisor_anterior) + EXPONENTE 
							+ to_string(veces) + MULTIPLICAR;
			}

			veces = 1;	// Reiniciamos el contador
		}		

		divisor_anterior = divisor;   // Actualizamos divisor_anterior

	}  // Cierra while(n != 1)

	// Si la última secuencia de factores primos no se almacenó,
	// la almacenamos ahora

	if(veces != 0){
		if(veces == 1)		// No indicamos el exponente
			resultado += to_string(divisor_anterior);

		else
			resultado += to_string(divisor_anterior) + EXPONENTE 
						+ to_string(veces);

	}

	return resultado;
}

/****************************************************************************
	Función que muestra en consola las dos cadenas que recibe, con el formato:
						cadena1 = cadena2

  Parámetros: cadena1, cadena2

****************************************************************************/

void MostrarCadenas(string cadena1, string cadena2){
	cout << cadena1 << " = " << cadena2 << endl;
}

/****************************************************************************
	Función que muestra en consola la cadena que devuelve la función
	Calcula_DescFactPrimos_1(int n)

  Parámetros: n

****************************************************************************/

void CalculaMuestra_DescFactPrimos_1 (int n){
	string descomposicion = Calcula_DescFactPrimos_1(n);

	MostrarCadenas(to_string(n), descomposicion);
}

/****************************************************************************
	Función que muestra en consola la cadena que devuelve la función
	Calcula_DescFactPrimos_2(int n)

  Parámetros: n

****************************************************************************/

void CalculaMuestra_DescFactPrimos_2 (int n){
	string descomposicion = Calcula_DescFactPrimos_2(n);

	MostrarCadenas(to_string(n), descomposicion);
}

/****************************************************************************/

int main(){
	
	int numero;

	// ENTRADAS

	bool entrada_invalida;

	do{

		cout << "Introduzca un entero mayor o igual que 0: ";
		cin >> numero;

		entrada_invalida = numero <= 0;

	}while(entrada_invalida);

	// SALIDAS

	cout << endl;

	CalculaMuestra_DescFactPrimos_1(numero);

	CalculaMuestra_DescFactPrimos_2(numero);

	cout << endl;

	return 0;
}
