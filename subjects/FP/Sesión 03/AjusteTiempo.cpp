#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
	int dias, horas, minutos, segundos;

	// Las variables con prefijo "input_" sirven para mostrar en la salida los valores que el usuario introdujo
	int input_horas, input_minutos, input_segundos;

	// Entradas
	cout << endl;
	cout << "Introduzca el numero de horas (un valor entero): ";
	cin >> input_horas;
	cout << "Introduzca el numero de minutos (un valor entero): ";
	cin >> input_minutos;
	cout << "Introduzca el numero de segundos (un valor entero): ";
	cin >> input_segundos;

	// Cálculos
	// Se van ajustando los tiempos desde atrás hacia adelante, comenzando
	// por los segundos y terminando con los días.
	horas = input_horas;
	minutos = input_minutos;
	segundos = input_segundos;

	// Si hay algún minuto lo almacena en minutos y deja los segundos sobrantes
	// en la variable segundos.
	minutos += segundos / 60;
	segundos = segundos % 60;

	horas += minutos / 60;
	minutos = minutos % 60;

	dias = horas / 24;
	horas = horas % 24;

	// Salidas
	cout << endl;
	cout << input_horas << " hora(s), " << input_minutos << " minuto(s) y " << input_segundos << " segundo(s) son:" << endl;
	cout << dias << " dia(s), " << horas << " hora(s), " << minutos << " minuto(s) y " << segundos << " segundo(s)." << endl;
	cout << endl;

	return 0;
}
