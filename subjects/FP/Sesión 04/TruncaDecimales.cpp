#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	double numero;
	int digitos;

	// ENTRADAS
	
	cout << "Introduce un numero: ";
	cin >> numero;

	cout << "Cifras decimales: ";
	cin >> digitos;

	// CÁLCULOS --------------------

	// auxiliar contiene los digítos del número truncado.
	int auxiliar = numero * pow(10, digitos);

	// Desplazamos la coma hasta la posición correcta, obteniendo
	// el número numero truncado a digitos decimales.
	double numero_truncado = ((double)auxiliar) / pow(10, digitos);

	// Cuenta el número de dígitos en la parte entera:
	// (trunca numero a las unidades y cuenta el número de caracteres)
	int parte_entera = to_string((int)numero).length();

	// SALIDA ----------------------

	// Formateamos la consola para mostrar números decimales.
	cout.setf(ios::fixed);

	// Mostramos la salida, reservando un ancho para la parte entera,
	// los dígitos decimales y el punto decimal.
	cout << endl;
	cout << "Su numero truncado: " << setw(parte_entera + 1 + digitos) 
		 << setprecision(digitos) << numero_truncado << endl;
	cout << endl;

	return 0;
}
