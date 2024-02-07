#include <iostream>

using namespace std;

int main()
{
	// Declaración
    const double PORC_AUMENTO = 1.02;
	double salario_base, salario_final;

	// Entrada
	cout << endl;
	cout << "Introduzca el salario base: ";
	cin >> salario_base;

	// Cálculo
	salario_final = salario_base * PORC_AUMENTO;

	// Salida
	cout << endl;
	cout << "Tras aplicarle un aumento del 2%, el salario base de " <<
		salario_base << " euros pasara a " << salario_final << " euros." 
		<< endl;
	cout << endl;

	return 0;
}
