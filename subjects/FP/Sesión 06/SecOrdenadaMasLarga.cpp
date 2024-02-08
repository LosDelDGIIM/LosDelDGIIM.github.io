#include <iostream>

using namespace std;

int main(){
	
	const double MIN_TEMP_VALIDA = -50, MAX_TEMP_VALIDA = 50;
	const int MIN_LONG_VALIDA = 3;

	double temperatura;

	const string mensaje = "Temperatura: ";

	// ENTRADAS Y CÁLCULOS

	// Solicita la primera temperatura

	cout << "Introduzca todas las temperaturas registradas:" << endl;
	cout << "(Si la temperatura no esta entre " << MIN_TEMP_VALIDA << " y " 
		 << MAX_TEMP_VALIDA << " la lectura de datos termina)" << endl << endl;

	cout << mensaje;
	cin >> temperatura;

	// Posicion de inicio y longitud de la mayor subsecuencia
	int inicio = 0, longitud = 0;

	// Posicion de inicio y longitud de la subsecuencia que se está procesando
	int inicio_temporal = 0, longitud_temporal = 0;

	// Posicion de la temperatura que se está procesando
	int posicion = 0;

	// La inicializamos para que la primera temperatura (si es válida)
	// comience una nuea subsecuencia.
	double temp_anterior = 51;

	while(temperatura >= MIN_TEMP_VALIDA && temperatura <= MAX_TEMP_VALIDA){
	
		posicion++;		// Analizamos la siguiente temperatura

		// Si la temperatura sigue perteneciendo a la subsecuencia actual
		if(temperatura >= temp_anterior){
			
			longitud_temporal++;		// Se aumenta el número de elementos

		}else{		// Si no, se comienza a procesar una nueva subsecuencia

			// Si la subsecuencia anterior tenía más elementos que la mayor
			// subsecuencia hasta el momento, esta se guarda como mayor
			if(longitud_temporal > longitud){

				longitud = longitud_temporal;
				inicio = inicio_temporal;

			}		

			// En cualquier caso, comenzamos a procesar una nueva subsecuencia

			longitud_temporal = 1;

			inicio_temporal = posicion;

		}

		// Solicitamos la siguiente temperatura a procesar

		temp_anterior = temperatura;

		cout << mensaje;
		cin >> temperatura;
	}

	// Si la última subsecuencia procesada era mayor que la máxima hasta el
	// momento, se guarda como mayor

	if(longitud_temporal > longitud){

		longitud = longitud_temporal;
		inicio = inicio_temporal;

	}	

	// SALIDAS

	cout << endl << endl;

	if(longitud == 0)	// Primer valor fuera del intervalo adecuado
		cout << "La primera temperatura no es valida." << endl;

	// Longitud no valida
	else if(longitud < MIN_LONG_VALIDA)
		cout << "La subsecuencia mas larga tiene una longitud no valida " 
			 << "(menor que " << MIN_LONG_VALIDA << " elementos)." << endl;

	else{	// Todo ha ido bien, se imprimen las salidas

		cout << "La mayor subsecuencia:" << endl;
		cout << "\tEmpieza en la posicion " << inicio << "." << endl;
		cout << "\tTiene longitud " << longitud << "." << endl;

	}

	cout << endl;

	return 0;
}
