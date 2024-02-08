#include <iostream>
#include <cmath>
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

		cout << "Introduzca el tope de la sumatoria: ";
		cin >> tope;

		error_lectura = tope <= 0 || tope > 100000;

	}while(error_lectura);

	// CÁLCULOS

	// Método a) (Usando pow())

	double sumatoria_a = 0;

	for(int i = 0; i <= tope; i++){

		sumatoria_a += pow(-1, i) / (2 * i + 1);

	}

	// Calculamos pi a partir de pi / 4
	double aprox_pi_a = 4 * sumatoria_a;

	// Método b) (Sin usar pow())

	double sumatoria_b = 0;

	for(int i = 0; i <= tope; i++){

		// Si i es par, el numerador es 1 y si no -1
		int numerador = (i % 2 == 0)? 1 : -1 ;

		sumatoria_b += numerador / (2.0 * i + 1);

	}

	// Calculamos pi a partir de pi / 4
	double aprox_pi_b = 4 * sumatoria_b;

	// SALIDAS

	// Mostramos 30 decimales de pi
	cout << setw(32) << setprecision(30);

	cout << endl;
	cout << "La aproximacion de pi con tope = " << tope << " :" << endl;
	cout << "\tSolucion a) : " << aprox_pi_a << endl;
	cout << "\tSolucion b) : " << aprox_pi_b << endl;
	cout << endl;

	return 0;
}
