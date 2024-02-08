#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	
	int tope;

	bool error_lectura = false;

	// ENTRADA

	do{
		// Imprime al usuario por qué su entrada no era válida
		if(error_lectura)
			cout << endl << "Tope debe ser un entero entre 1 y 100000." << endl;

		cout << "Tope (numero de multiplicaciones): ";
		cin >> tope;

		error_lectura = tope <= 0 || tope > 100000;

	}while(error_lectura);

	// CÁLCULOS

	// Solucion a)

	double multiplicacion_a = 1;	// Neutro del producto

	int numerador_a = 2;
	int denominador_a = 1;

	bool cambia_numerador = false;

	for(int i = 0; i < tope; i++){

		// Se van realizando las multiplicaciones
		multiplicacion_a *= ((double)numerador_a) / denominador_a;

		// Cambia el numerador o el denominador, según indique cambia_numerador
		if(cambia_numerador)
			numerador_a += 2;
		else
			denominador_a += 2;

		// Cambia el valor de cambia_numerador
		cambia_numerador = !cambia_numerador;

	}

	// Calculamos pi a partir de pi/2
	double aprox_pi_a = 2 * multiplicacion_a;

	// Solución b)

	double multiplicacion_b = 1;		// Neutro del proucto

	int numerador_b = 2;
	int denominador_b = 1;

	int numerador_anterior;
	int denominador_anterior;

	for(int i = 0; i < tope; i++){

		// Se van realizando las multiplicaciones
		multiplicacion_b *= ((double) numerador_b) / denominador_b;

		// Se actualizan los numeradores y denominadores anteriores
		denominador_anterior = denominador_b;
		numerador_anterior = numerador_b;

		// Se ajustan los siguientes numerador y denominador
		numerador_b = denominador_anterior + 1;
		denominador_b = numerador_anterior + 1;

	}

	// Calculamos pi a partir de pi/2
	double aprox_pi_b = 2 * multiplicacion_b;

	// SALIDAS

	// Mostramos 14 decimales de pi
	cout << setw(16) << setprecision(14);

	cout << endl;
	cout << "La aproximacion de pi: " << endl;
	cout << "\tSolucion a) : " << aprox_pi_a << endl;
	cout << "\tSolucion b) : " << aprox_pi_b << endl;
	cout << endl;

	return 0;
}
