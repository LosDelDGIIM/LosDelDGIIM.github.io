#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double lado1, lado2, angulo;

	const double PI = 6*asin(0.5);
	const double GRADOS_A_RADIANES = PI / 180;

	// ENTRADAS

	cout << "La medida de un lado (cm): ";
	cin >> lado1;

	cout << "La medida de otro lado (cm): ";
	cin >> lado2;

	cout << "El angulo que forman (en grados): ";
	cin >> angulo;

	// CÁLCULOS
	// Pasamos el ángulo a radianes:
	
	double rad_angulo = angulo * GRADOS_A_RADIANES;

	// Aplicamos la fórmula:

	double area = 0.5 * lado1 * lado2 * sin(rad_angulo);

	// SALIDA

	cout << endl;
	cout << "El area del triangulo es de " << area << " cm cuadrados." << endl;
	cout << endl;

	return 0;
}
