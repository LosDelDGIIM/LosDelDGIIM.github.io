#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	// Declaraciones
	double x, y, h;

	// Entradas
	cout << endl;
	cout << "Introduzca el valor de x: ";
	cin >> x;

	cout << "Introduzca el valor de y: ";
	cin >> y;

	cout << "Introduzca el valor de h: ";
	cin >> h;

	// Cálculos
	double a = (1 + (pow(x, 2)/y)) / ((pow(x, 3)) / (1 + y));

	double b = (1 + 1/3.0 * sin(h) - 1/7.0 * cos(h)) / (2 * h);

	double c = sqrt(1 + pow(((exp(x)) / (pow(x, 2))), 2));

	// Salidas
	cout << endl;
	cout << "Para x = " << x << ", y = " << y << " y h = " << h << " :"<<endl;
	cout << "\tEl valor de la expresion a es: " << a << endl;
	cout << "\tEl valor de la expresion b es: " << b << endl;
	cout << "\tEl valor de la expresion c es: " << c << endl;
	cout << endl;

	return 0;
}
