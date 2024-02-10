#include <iostream>

using namespace std;

int main(){
	
	// Número máximo de casillas de array1 y array2
	const int TOPE = 100;

	const string TERMINADOR = "FIN";

	// Constantes para mensajes repetitivos

	const string MSG_TERMINADOR = "(Cuando termine, introduzca \"" 
								+ TERMINADOR + "\")";
	const string MSG_VALOR = "Valor: ";
	const string MSG_TOPE = "Se alcanzo el tope (" + to_string(TOPE) 
							+ " casillas).";

	int array1[TOPE], array2[TOPE];

	// Números de posiciones válidas en cada array
	int pos_validas1 = 0, pos_validas2 = 0;

	// ENTRADAS **********************************************************

	// array 1 --------------------------------------------------------

	string entrada1;

	cout << "Introduzca los valores (enteros) del array 1: " << endl;
	cout << MSG_TERMINADOR << endl;
	cout << endl;

	cout << MSG_VALOR;
	cin >> entrada1;

	// Mientras que entrada no sea "FIN" y haya poosiciones en el array

	while(entrada1 != TERMINADOR && pos_validas1 < TOPE - 1){

		// Se almacena el valor y se aumenta el número de posiciones válidas		

		array1[pos_validas1] = stoi(entrada1);

		pos_validas1++;

		// Solicita el siguiente valor

		cout << MSG_VALOR;
		cin >> entrada1;
	}

	// Si se llena el array, guarda el último valor si no es TERMINADOR 
	// e imprime MSG_TOPE

	if(pos_validas1 == TOPE - 1 && entrada1 != TERMINADOR){
		array1[pos_validas1] = stoi(entrada1);
		pos_validas1++;

		cout << endl << MSG_TOPE << endl;
	}

	// array 2 --------------------------------------------------------

	string entrada2;

	cout << endl;
	cout << "Introduzca los valores (enteros) del array 2: " << endl;
	cout << MSG_TERMINADOR << endl;
	cout << endl;

	cout << MSG_VALOR;
	cin >> entrada2;

	// Mientras que entrada no sea "FIN" y haya poosiciones en el array

	while(entrada2 != TERMINADOR && pos_validas2 < TOPE - 1){
	
		// Se almacena el valor y se aumenta el número de posiciones válidas		

		array2[pos_validas2] = stoi(entrada2);

		pos_validas2++;

		// Solicita el siguiente valor

		cout << MSG_VALOR;
		cin >> entrada2;
	}

	// Si se llena el array, guarda el último valor e imprime MSG_TOPE

	if(pos_validas2 == TOPE - 1 && entrada2 != TERMINADOR){
		array2[pos_validas2] = stoi(entrada2);	
		pos_validas2++;

		cout << endl << MSG_TOPE << endl;
	}

	// CÁLCULOS ***********************************************************

	// Se calcula el valor medio de los valores de cada array

	// array 1 --------------------------------------------------------

	double sumatoria_array1 = 0;

	// Recorre todas las posiciones válidas de array1
	for(int i = 0; i < pos_validas1; i++){
		sumatoria_array1 += array1[i];
	}

	// Se divide la suma de todos los elementos entre el número de elementos

	double valor_medio1;

	// Si no tenía elementos, consideramos que la media es 0
	if(pos_validas1 == 0)
		valor_medio1 = 0;

	else
		valor_medio1 = sumatoria_array1 / pos_validas1;

	// array 2 --------------------------------------------------------

	double sumatoria_array2 = 0;

	// Recorre todas las posiciones válidas de array2
	for(int i = 0; i < pos_validas2; i++){
		sumatoria_array2 += array2[i];
	}

	// Se divide la suma de todos los elementos entre el número de elementos

	double valor_medio2;

	// Si no tenía elementos, se considera que la media es 0
	if(pos_validas2 == 0)	
		valor_medio2 = 0;

	else
		valor_medio2 = sumatoria_array2 / pos_validas2;

	// ------------------------------------------------------------------
	// Se comprueba si los dos arrays contienen los mismos valores en el 
	// mismo orden

	bool diferentes;

	int i = 0;

	// Si contienen diferente número de elementos válidos o si tienen 
    // distinto valor medio ya sabemos que son arrays diferentes

	if(pos_validas1 != pos_validas2 || valor_medio1 != valor_medio2)
		diferentes = true;

	else{

		diferentes = false;

		// Mientras que haya elementos válidos y que no se haya detectado
		// que sean diferentes, se recorre todo el array

		while(i < pos_validas1 && !diferentes){
	
			// Si en la misma posición un elemento de un array es distinto de 
			// un elemento de otro, son diferentes

			if(array1[i] != array2[i])
				diferentes = true;	

			else
				i++;
		}

	}

	// SALIDAS ************************************************************

	cout << endl;

	cout << "El valor medio del array1 es: " << valor_medio1 << endl;

	cout << endl;

	cout << "El valor medio del array2 es: " << valor_medio2 << endl;

	cout << endl;

	if(diferentes)
		cout << "El array1 y el array2 son diferentes." << endl;
	else
		cout << "Los arrays son iguales." << endl;

	cout << endl;

	return 0;
}
