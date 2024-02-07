#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	//Declaración de variables
	double cantidad_a_pagar, cantidad_pagada;
	int monedas_2e = 0, monedas_1e = 0, monedas_50c = 0, monedas_20c = 0, 
		monedas_10c = 0, monedas_5c = 0, monedas_2c = 0, monedas_1c = 0;

	//Entradas
	cout << endl;
	cout << "Introduzca la cantidad a pagar (en euros): ";
	cin >> cantidad_a_pagar;
	cout << "Introduzca la cantidad con la que se ha pagado (en euros): ";
	cin >> cantidad_pagada;
	cout << endl;
	cout << endl;

	// Cálculos:
	// Se calcula la cantidad a devolver

	double cantidad_a_devolver = cantidad_pagada - cantidad_a_pagar;
	
	// Separa la cantidad a devolver en la parte entera, correspondiente a los
	// euros y la fraccionaria, correspondiente a los centimos.
    
	double euros_devuelta;
	double centimos_devuelta = modf(cantidad_a_devolver, &euros_devuelta);

	// Se calcula mediante cocientes el número de monedas de cada tipo. las 
	// variables euros_devuelta y centimos_devuelta van disminuyendo su valor 
	// mediante restos conforme se devuelven monedas.

	monedas_2e = euros_devuelta / 2;
	euros_devuelta -= monedas_2e * 2;

	monedas_1e = euros_devuelta;

	monedas_50c = centimos_devuelta / 0.5;
	centimos_devuelta -= monedas_50c * 0.5;

	monedas_20c = centimos_devuelta / 0.2;
	centimos_devuelta -= monedas_20c * 0.2;

	monedas_10c = centimos_devuelta / 0.1;
	centimos_devuelta -= monedas_10c * 0.1;

	monedas_5c = centimos_devuelta / 0.05;
	centimos_devuelta -= monedas_5c * 0.05;

	monedas_2c = centimos_devuelta / 0.02;
	centimos_devuelta -= monedas_2c * 0.02;

	monedas_1c = centimos_devuelta*100;

	//Salidas
	cout << "Ha(n) de devolverle al cliente " << cantidad_a_devolver << " euros:" 
		<< endl;
	cout << "\t" << monedas_2e << " moneda(s) de 2 euros." << endl;
	cout << "\t" << monedas_1e << " moneda(s) de 1 euro." << endl;
	cout << "\t" << monedas_50c << " moneda(s) de 50 centimos." << endl;
	cout << "\t" << monedas_20c << " moneda(s) de 20 centimos." << endl;
	cout << "\t" << monedas_10c << " moneda(s) de 10 centimos." << endl;
	cout << "\t" << monedas_5c << " moneda(s) de 5 centimos." << endl;
	cout << "\t" << monedas_2c << " moneda(s) de 2 centimos." << endl;
	cout << "\t" << monedas_1c << " moneda(s) de 1 centimo." << endl;

	return 0;
}

// Nota: Este programa es totalmente válido, pero debido a problemas con los ordenadores a la hora de dividir,  
// puede que el output que de el programa no esté bien. Te retamos a crear un programa que no tenga este fallo.
