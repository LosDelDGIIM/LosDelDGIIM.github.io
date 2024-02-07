#include <iostream>

using namespace std;

int main()
{
	int numero, nuevo;

	// ENTRADA

	cout << "Introduzca el numero: ";
	cin >> numero;

	// CÁLCULOS

	string str_numero = to_string(numero);

	char primera_cifra = str_numero.at(0);

	char ultima_cifra = str_numero.at(str_numero.length()-1);

	// Todas las cifras de numero salvo la primera y la última.
	string mitad_numero = str_numero.substr(1, str_numero.length()-2);

	nuevo = stoi(ultima_cifra + mitad_numero + primera_cifra);

	// Compara qué cifra es mayor:
	bool primera_es_mayor = numero > nuevo;
	bool cifras_iguales = numero == nuevo;
	bool primera_es_menor = numero < nuevo;

	// SALIDAS

	cout << endl;
	cout << "El numero nuevo: " << nuevo << endl;
	cout << endl;

	cout << primera_cifra << " > " << ultima_cifra << ": " << boolalpha 
		 << primera_es_mayor << endl;

	cout << primera_cifra << " = " << ultima_cifra << ": " << boolalpha 
		 << cifras_iguales << endl;

	cout << primera_cifra << " < " << ultima_cifra << ": " << boolalpha 
		 << primera_es_menor << endl;

	cout << endl;

	return 0;
}
