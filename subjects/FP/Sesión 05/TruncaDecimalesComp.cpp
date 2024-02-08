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

	// Comprueba que digitos sea un número natural o 0
	bool digitos_correctos = digitos >= 0;

	if(!digitos_correctos){
		cout << endl;
		cout << "Error: El numero de digitos a redondear debe ser un numero "
			 << "natural." << endl;
		cout << endl;
	}

	// CÁLCULOS --------------------

	int parte_entera;
	double numero_truncado;

	// Realiza los cálculos sólo si digitos es un número natural:

	if(digitos_correctos){
		// auxiliar contiene los digítos del número truncado.
		int auxiliar = numero * pow(10, digitos);
	
		// Desplazamos la coma hasta la posición correcta, obteniendo
		// el número numero truncado a digitos decimales.
		numero_truncado = auxiliar / pow(10, digitos);
	
		// Cuenta el número de dígitos en la parte entera:
		// (trunca numero a las unidades y cuenta el número de caracteres)
		parte_entera = to_string((int)numero).length();
	}

	// SALIDA ----------------------

	if(digitos_correctos){
	
		// Formateamos la consola para mostrar números decimales.
		cout.setf(ios::fixed);

		cout << endl;
		cout << "Su numero truncado: " << setw(parte_entera + 1 + digitos) 
			 << setprecision(digitos) << numero_truncado << endl;	
		cout << endl;
	}

	return 0;
}
