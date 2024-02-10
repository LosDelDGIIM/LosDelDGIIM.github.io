#include <iostream>
#include <iomanip>

using namespace std;

// Enumerado que determina el modo de pasar por las casills

enum class RecorrerMapa {Zigzag, Espiral};

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

	// Se repite mientras que no sea un número entero

	do{

		cout << mensaje;
		cin >> numero;

	}while(!EsEntero(numero));

	return stoi(numero);
}

/****************************************************************************
	Imprime un mensaje en consola y lee el número entero que introduce el 
	usuario. Repite la entrada mientras que el valor introducido no sea
	un número entero o mientras que el número no esté en el intervalo
	[min, max]

  Parámetros: titulo, el mensaje que se muestra al usuario
			  min, el mínimo valor válido
			  max, el máximo valor válido
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
	
	// Determina en qué modo recorrerá el robot el mapa *********************

	RecorrerMapa modo;

	// Para que el robot recorra el mapa en Zigzag:

	modo = RecorrerMapa::Zigzag;

	// Para que el robot recorra el mapa en Espiral:

	// modo = RecorrerMapa::Espiral;

	// **********************************************************************

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
												MIN_FILAS, MAX_FILAS);

	columna = LeerEnteroEnRango("\tColumna " + MSG_INTERVALO_COLUMNAS + ": ", 
												MIN_COLUMNAS, MAX_COLUMNAS);

	// Se almacena la posición en pos

	Punto pos = {fila, columna};

	// CÁLCULOS *************************************************************

	// Generación de la secuencia de instrucciones *************************

	// 1.- Calculamos el número de instrucciones que usaremos ---------------
		
	// Número de instrucciones para recorrer el mapa a partir de (1, 1)

	int dimension_mapa = NUM_FILAS * NUM_COLUMNAS;

	// Número de instrucciones para llevar el robot a (1, 1)

	int desplazamiento_horiz = pos.fila - MIN_FILAS;

	int desplazamiento_vert = pos.columna - MIN_COLUMNAS;

	// Declara el array que usaremos para las instrucciones

	int lon = dimension_mapa + desplazamiento_horiz + desplazamiento_vert;

	char ord[lon];

	int posiciones_llenas = 0;

	// 2.- Genera la secuencia para llevar el robot a (1, 1)  ----------------

	// Lleva el robot a la columna 1

	for(int i = pos.columna; i > MIN_COLUMNAS; i--){

		ord[posiciones_llenas] = INS_IZQDA;

		posiciones_llenas++;

	}

	// Lleva el robot a la fila 1

	for(int i = pos.fila; i > MIN_FILAS; i--){
		
		ord[posiciones_llenas] = INS_ABAJO;

		posiciones_llenas++;

	}

	// 3.- Genera la secuencia para recorrer el mapa en función del modo 

	switch(modo){
	
		// 3.- Genera la secuencia para recorrerlo en ZigZag ----------------

		case RecorrerMapa::Zigzag:{
			
			bool avanzar_dcha = true;

			// Rellena la primera fila
		
			char rellenar = (avanzar_dcha)? INS_DCHA : INS_IZQDA;
		
			for(int i = MIN_COLUMNAS; i < MAX_COLUMNAS; i++){
		
				// Avanza hacia la derecha o hacia la izquierda
		
				ord[posiciones_llenas] = rellenar;
		
				posiciones_llenas++;
		
			}
		
			// Recorre todas las filas a partir de la segunda
		
			for(int i = MIN_FILAS + 1; i <= MAX_FILAS; i++){
		
				// Avanza a la siguiente fila
		
				ord[posiciones_llenas] = INS_ARRIBA;
		
				posiciones_llenas++;
			
				// Invierte la dirección de avance
		
				avanzar_dcha = !avanzar_dcha;
		
				// Recorre toda la fila
		
				rellenar = (avanzar_dcha)? INS_DCHA : INS_IZQDA;
		
				for(int i = MIN_COLUMNAS; i < MAX_COLUMNAS; i++){
		
					// Avanza hacia la derecha o hacia la izquierda
		
					ord[posiciones_llenas] = rellenar;
		
					posiciones_llenas++;
		
				}
			}

			break;}

		// 3.2- Genera la secuencia para recorrerlo en Espiral ---------------

		case RecorrerMapa::Espiral:{
	
			// Recorre la primera fila

			for(int i = MIN_COLUMNAS; i < MAX_COLUMNAS; i++){
			
				// Avanza hacia la derecha
		
				ord[posiciones_llenas] = INS_DCHA;
		
				posiciones_llenas++;
		
			}
		
			// Indican el número de caracteres que se colocan por cada fila o 
			// columna de la espiral
		
			int rellena_filas = NUM_FILAS - 1;
			int rellena_columnas = NUM_COLUMNAS - 1;
		
			// Indica si el robot tiene que ir a la derecha y arriba o no
		
			bool dcha_y_arriba = true;
		
			// Mientras que no se rellenen todas las casillas
		
			while(posiciones_llenas < lon - 1){
		
				// Se rellena una columna de la espiral
		
				char rellenar_espiral = (dcha_y_arriba)? INS_ARRIBA: INS_ABAJO;
		
				for(int i = 0; i < rellena_filas; i++){
					ord[posiciones_llenas] = rellenar_espiral;
			
					posiciones_llenas++;
				}
			
				// Se rellena una fila de la espiral
		
				rellenar_espiral = (dcha_y_arriba)? INS_IZQDA : INS_DCHA;
		
				for(int i = 0; i < rellena_columnas; i++){
					ord[posiciones_llenas] = rellenar_espiral;
		
					posiciones_llenas++;
				}
		
				// Se alternan las posiciones
		
				dcha_y_arriba = !dcha_y_arriba;
		
				// En la siguiente vuelta, las filas y las columnas tendrán
				// una casilla menos a rellenar
		
				rellena_filas--;
				rellena_columnas--;
			}

			break;}
	}

	// Se ejecuta el repertorio de instrucciones en el robot *****************

	int instruccion = -1;	// Para que se aumente al entrar en el bucle

	bool dentro_mapa = true;

	while(instruccion < posiciones_llenas && dentro_mapa){
	
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

	else{

		// Imprime por qué método se ha recorrido el mapa -----------------

		switch(modo){
			case RecorrerMapa::Zigzag:
				cout << "Se ha recorrido el mapa en forma de zig-zag." << endl;
				break;

			case RecorrerMapa::Espiral:
				cout << "Se ha recorrido el mapa en forma de espiral." << endl;
				break;
		}

		cout << endl;

		// Parte superior mapa --------------------------------------------

		cout << "   : ";

		// Se imprimen el número de columnas

		for(int i = MIN_COLUMNAS; i <= MAX_COLUMNAS; i++){
			cout << i << " ";
		}

		cout << "   " << endl;

		cout << "   -----------------------   " << endl;

		// Parte central mapa --------------------------------------------

		// Se imprime el mapa

		for(int i = MAX_FILAS; i >= MIN_FILAS; i--){

			// Se imprime el número de fila

			// Si tiene sólo 1 cifra se introduce un espacio

			if(i < 10)
				cout << " ";

			cout << i << " : ";

			// Se imprimen todas las columnas de la fila

			for(int j = MIN_COLUMNAS; j <= MAX_COLUMNAS; j++){

				if(mapa[i-1][j-1] == 0)
					cout << ". ";

				else
					cout << mapa[i-1][j-1] << " ";

			}

			// Se vuelve a imprimir el número de fila al final

			cout << ":  " << i << endl;

		}

		// Parte inferior mapa --------------------------------------------

		cout << "   -----------------------   " << endl;

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
