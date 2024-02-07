#include <iostream>

using namespace std;

int main()
{
	// DECLARACIONES	

	const int ASCII_A = 'A', ASCII_Z = 'Z';
	const int EDAD_MIN = 18, EDAD_MAX = 67;
	const double LIMITE = 100.5;	

	char caracter;
	int edad;
	int anio;
	double distancia;
	int numero1, numero2;
	
	// ENTRADAS

	cout << "Un caracter: ";
	cin >> caracter;

	cout << "Una edad: ";
	cin >> edad;

	cout << "Un anio: ";
	cin >> anio;
	
	cout << "Una distancia: ";
	cin >> distancia;

	cout << "Dos numeros enteros: " << endl;
	cout << "\tNumero 1: ";
	cin >> numero1;
	cout << "\tNumero 2: ";
	cin >> numero2;

	// CÁLCULOS

	bool es_mayuscula = caracter >= ASCII_A && caracter <= ASCII_Z;

	bool edad_correcta = edad >= EDAD_MIN && edad < EDAD_MAX;

	bool anio_bisiesto = anio % 400 == 0 || (anio % 4 == 0 && anio % 100 != 0);

	bool distancia_menor_limite = distancia < LIMITE;

	bool numero1_mayor = numero1 > numero2;
	
	bool numeros_iguales = numero1 == numero2;

	bool numero1_menor = numero1 < numero2;

	// SALIDAS

	cout << endl;
	cout << endl;
	
	cout << caracter << " es mayuscula: 	" << boolalpha << es_mayuscula << endl;
	
	cout << "18 <= " << edad << " < 67: 		" << boolalpha << edad_correcta << endl;

	cout << anio << " es bisiesto: 	" << boolalpha << anio_bisiesto << endl;

	cout << distancia << " < " << LIMITE << ": 		" << boolalpha << distancia_menor_limite << endl;

	cout << endl;

	cout << numero1 << " > " << numero2 << ": " << boolalpha << numero1_mayor << endl;

	cout << numero1 << " = " << numero2 << ": " << boolalpha << numeros_iguales << endl;

	cout << numero1 << " < " << numero2 << ": " << boolalpha << numero1_menor << endl;

	cout << endl;

	return 0;
}
