#include <iostream>
#include <iomanip>

using namespace std;

// Definición de struct

struct Punto{
	int fila;
	int columna;
};

/****************************************************************************
	Determina si una cadena es un número entero o si no.

  Parámetros: cadena
  Devuelve: true si cadena es un número entero, false si no

****************************************************************************/

bool EsEntero(string cadena){

	// Incluir en SIGNOS todos los signos válidos

	const string SIGNOS = "+-";

	bool es_entero;

	// Si la cadena está vacía no es un entero
	if(cadena.length() == 0)
		es_entero = false;

	else{

		// Si el primer caracter es un signo y hay más caracteres se borra

		if(SIGNOS.find(cadena.at(0)) != string::npos && cadena.length() > 1)
			cadena.erase(0, 1);

		// Comprobamos que todos los caracteres sean dígitos

		int i = 0;

		es_entero = true;

		while(i < cadena.length() && es_entero){

			if(!isdigit(cadena.at(i)))
				es_entero = false;

			else
				i++;

		}
	}

	return es_entero;
}

/****************************************************************************
	Imprime un mensaje en consola y lee el número entero que introduce el 
	usuario. Repite la entrada mientras que el valor introducido no sea
	un número entero.

  Parámetros: titulo, el mensaje que se muestra al usuario
  Devuelve: el número entero que introduce el usuario

****************************************************************************/

int LeerEntero(string mensaje){
	string numero;

	// Se repite mientras que no sea entero

	do{

		cout << mensaje;
		cin >> numero;

	}while(!EsEntero(numero));

	return stoi(numero);
}

/****************************************************************************
	Imprime un mensaje en consola y lee el número entero que introduce el 
	usuario. Repite la entrada mientras que el valor introducido no sea
	un número entero o no esté en el intervalo [min, max]

  Parámetros: titulo, el mensaje que se muestra al usuario
			  min, el mínimo número válido
			  max, el máximo número válido
  Devuelve: el número entero que introduce el usuario

****************************************************************************/

int LeerEnteroEnRango(string mensaje, int min, int max){
	int numero;

	// Se repite mientras que no esté en el intervalo [min, max]

	do{

		numero = LeerEntero(mensaje);

	}while(numero < min || numero > max);

	return numero;
}

/****************************************************************************/

int main(){
	
	// Coordenadas mínimas y máximas de las filas y columnas

	const int MIN_FILAS = 1, MIN_COLUMNAS = 1;
	const int MAX_FILAS = 10, MAX_COLUMNAS = 10;

	const int NUM_FILAS = MAX_FILAS - MIN_FILAS + 1;
	const int NUM_COLUMNAS = MAX_COLUMNAS - MIN_COLUMNAS + 1;

	const string MSG_INTERVALO_FILAS = "(entre " + to_string(MIN_FILAS) + " y " 
												+ to_string(MAX_FILAS) + ")";

	const string MSG_INTERVALO_COLUMNAS = "(entre " + to_string(MIN_COLUMNAS) 
									+ " y " + to_string(MAX_COLUMNAS) + ")";

	// Repertorio válido de instrucciones

	const char INS_IZQDA = 'I', INS_DCHA = 'D';
	const char INS_ARRIBA = 'A', INS_ABAJO = 'B';

	int mapa[NUM_FILAS][NUM_COLUMNAS] = {{0}};

	// ENTRADAS ************************************************************

	// Se solicita la posición inicial del robot

	cout << "Introduzca la posición inicial del robot: " << endl;

	int fila, columna;

	fila = LeerEnteroEnRango("\tFila " + MSG_INTERVALO_FILAS + ": ", 
											MIN_FILAS, MAX_COLUMNAS);

	columna = LeerEnteroEnRango("\tColumna " + MSG_INTERVALO_COLUMNAS + ": ", 
											MIN_COLUMNAS, MAX_COLUMNAS);

	// Se almacena la posición en pos

	Punto pos = {fila, columna};

	// Se solicita el repertorio de instrucciones a ejecutar

	cout << endl;

	bool secuencia_invalida;

	string cad_ordenes;

	do{

		cout << "Secuencia de ordenes: " << endl;
		cin >> cad_ordenes;

		int i = 0;

		// Se presupone que la secuencia sea valida

		secuencia_invalida = false;

		// Mientras que no sea invalida, recorre cad_ordenes

		while(i < cad_ordenes.length() && !secuencia_invalida){

			// Si alguna instruccion no está contemplada

			char c = toupper(cad_ordenes.at(i));

			secuencia_invalida = c != INS_IZQDA && c != INS_DCHA 
							&& c != INS_ARRIBA && c != INS_ABAJO;

			if(!secuencia_invalida)
				i++;
		}

	}while(secuencia_invalida);

	// Se rellena ord con los valores de cad_ordenes

	int lon = cad_ordenes.length();

	char ord[lon];

	for(int i = 0; i < lon; i++){
		ord[i] = toupper(cad_ordenes.at(i));
	}

	// CÁLCULOS *************************************************************

	int instruccion = -1;

	bool dentro_mapa = true;

	while(instruccion < lon && dentro_mapa){
	
		// Se cuenta que el robot ha pasado por dicha posición del mapa

		mapa[pos.fila-1][pos.columna-1]++;

		// Aumenta el número de instrucción

		instruccion++;	

		switch(ord[instruccion]){
			case INS_IZQDA:	// Izquierda
				pos.columna--;
				break;

			case INS_DCHA:	// Derecha
				pos.columna++;
				break;

			case INS_ARRIBA:	// Arriba
				pos.fila++;
				break;

			case INS_ABAJO:	// Abajo
				pos.fila--;
				break;
		}	

		// Evalúa si el robot sigue estando dentro del mapa

		dentro_mapa = pos.fila >= MIN_FILAS && pos.fila <= MAX_FILAS && 
				pos.columna >= MIN_COLUMNAS && pos.columna <= MAX_COLUMNAS;
	}

	// SALIDAS **************************************************************

	cout << setw(1);

	cout << endl;

	// Si se salió del mapa, imprime el número de órdenes

	if(!dentro_mapa)
		cout << "Numero de ordenes: " << instruccion << endl;

	else{		// Si no, imprime el mapa

		// Parte superior mapa --------------------------------------------

		cout << "   : ";

		// Se imprimen el número de columnas

		for(int i = MIN_COLUMNAS; i <= MAX_COLUMNAS; i++){
			cout << i << " ";
		}

		cout << "   " << endl;

		cout << "   ";

		// Por cada columna que haya imprime tres separadores

		for(int i = 0; i < NUM_COLUMNAS; i++){

			cout << "---";

		}

		cout << "   " << endl;

		// Parte central mapa --------------------------------------------

		// Se imprime el mapa

		for(int i = MAX_FILAS; i >= MIN_FILAS; i--){

			// Se imprime el número de fila

			cout << setw(2) << i << " : ";

			// Se imprimen todas las columnas de la fila

			for(int j = MIN_COLUMNAS; j <= MAX_COLUMNAS; j++){

				// Si el robot no ha pasado por la casilla se imprime un punto
				if(mapa[i-1][j-1] == 0)
					cout << ". ";

				else
					cout << mapa[i-1][j-1] << " ";

			}

			// Se vuelve a imprimir el número de fila al final

			cout << ":  " << i << endl;

		}

		// Parte inferior mapa --------------------------------------------

		cout << "   ";

		// Por cada columna que haya imprime tres separadores

		for(int i = 0; i < NUM_COLUMNAS; i++){

			cout << "---";

		}

		cout << "   " << endl;

		cout << "   : ";

		// Se imprime el número de columnas

		for(int i = MIN_COLUMNAS; i <= MAX_COLUMNAS; i++){
			cout << i << " ";
		}

		cout << "   " << endl;

	}

	cout << endl;

	return 0;
}
