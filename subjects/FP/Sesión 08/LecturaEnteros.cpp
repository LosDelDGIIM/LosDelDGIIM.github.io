#include <iostream>

using namespace std;

/****************************************************************************
	Función que comprueba si un caracter es un dígito

  Parámetro: caracter
  Devuelve: true si el caracter está comprendido en el intervalo [0, 9],
	false si no

****************************************************************************/

bool EsDigito(char caracter){

	const int ASCII_0 = '0', ASCII_9 = '9';

	// Comprueba si el código ascii de caracter está entre los códigos
	// ascii del 0 y el 9

	return caracter >= ASCII_0 && caracter <= ASCII_9;

}

/****************************************************************************
	Función que comprueba si todos los caracteres de una cadena son dígitos

  Parámetros: cadena
  Devuelve: true si todos los caracteres de la cadena eran dígitos, false si no

****************************************************************************/

bool CadenaSoloContieneDigitos(string cadena){
	
	// Suponemos que la cadena sólo tiene dígitos
	bool todo_digitos =  true;

	// Recorremos la cadena en busca de un caracter que no sea un dígito
	// en caso de encontrarlo, se detiene la ejecución del bucle

	int i = 0;

	while(todo_digitos && i < cadena.length()){

		if(!EsDigito(cadena.at(i)))
			todo_digitos = false;

		i++;
	}

	return todo_digitos;
}

/****************************************************************************
	Función que comprueba si un string es un número entero o no

  Parámetros: cadena
  Devuelve: true (si cadena era un entero), false si no

****************************************************************************/

bool EsEntero (string cadena){
	const char MENOS = '-';	

	bool es_entero;

	// Si la cadena está vacía, no es un número entero

	if(cadena.length() == 0)
		es_entero = false;

	else{

		// Si es un número negativo, se elimina el signo
		if(cadena.at(0) == MENOS)
			cadena.erase(0, 1);	// Elimina el primer caracter
		
		// Si al quitar el menos hay más caracteres
		if(cadena.length() != 0){
		
			// Hasta que no se encuentre un fallo es un entero
			es_entero = CadenaSoloContieneDigitos(cadena);
		
		}else	// Si no, no es un entero (habrían introducido "-")
			es_entero = false;

	}

	return es_entero;
}

/****************************************************************************
	Función que lee y devuelve un dato entero. Si el valor introducido
	no era un entero, vuelve a repetir la entrada hasta obtener un entero

  Parámetros: titulo (mensaje que muestra al pedir el entero)
  Devuelve: el entero

****************************************************************************/

int LeeEntero (string titulo){

	string entrada;	

	bool es_entero;

	// Repite la entrada mientras que no introduzcan un entero

	do{
		// Solicita el entero
		cout << titulo;
		getline(cin, entrada);
	
		// Se comprueba que sea un número entero
		es_entero = EsEntero(entrada);

	}while(!es_entero);

	return stoi(entrada);	
}

/****************************************************************************
	Función que lee y devuelve un dato entero dentro del rango establecido.
	Si el valor introducido no fuera un entero o estuviese fuera
	del rango establecido, se volvería a repetir la entrada.

  Parámetros: titulo (mensaje a mostrar), 
			  menor, mayor (definen el rango de valores válidos)
  Devuelve: el entero dentro del intervalo [menor, mayor]
  PRE: menor <= mayor

****************************************************************************/

int LeeEnteroEnRango (string titulo, int menor, int mayor){
	
	string entrada;
	int entero;

	bool no_valido;

	// Se repite mientras que no sea un valor válido

	do{
		// Lee un dato entero
		entero = LeeEntero(titulo);

		// Es inválido si el dato no está en el intervalo [menor, mayor]
		no_valido = entero < menor || entero > mayor;

	}while(no_valido);

	return entero;
}

/****************************************************************************
	Función que lee y devuelve un dato entero mayor o igual que referencia.
	Si el valor introducido no fuera un entero o fuera menor que referencia, 
	se volvería a repetir la entrada.

  Parámetros: titulo (mensaje a mostrar), referencia
  Devuelve: el entero mayor o igual que referencia

****************************************************************************/

int LeeEnteroMayorOIgual (string titulo, int referencia){
	
	string entrada;
	int entero;

	bool no_valido;

	// Se repite mientras que no sea un valor válido

	do{
		// Lee un dato entero
		entero = LeeEntero(titulo);

		// No es válido si es menor que referencia
		no_valido = entero < referencia;

	}while(no_valido);

	return entero;
}

/****************************************************************************/

int main(){
	
	const int MENOR = 0, MAYOR = 50, REFERENCIA = 10;

	const string MSG_ENTERO = "Introduzca un entero: ";

	const string MSG_RANGO = "Introduzca un entero entre " + to_string(MENOR) 
							+ " y " + to_string(MAYOR) + " : ";

	const string MSG_MAYOR_IGUAL = "Introduzca un entero mayor o igual que "
							+ to_string(REFERENCIA) + " : ";

	// ENTRADAS

	int entero = LeeEntero(MSG_ENTERO);

	cout << endl;

	int rango = LeeEnteroEnRango(MSG_RANGO, MENOR, MAYOR);

	cout << endl;

	int mayor_igual = LeeEnteroMayorOIgual(MSG_MAYOR_IGUAL, REFERENCIA);

	// SALIDAS

	cout << endl << endl;

	cout << "Un entero: " << entero << endl;

	cout << "Un entero entre " << MENOR << " y " << MAYOR << ": " 
		 << rango << endl;

	cout << "Un entero mayor o igual que " << REFERENCIA << ": " 
		 << mayor_igual << endl;	

	cout << endl;

	return 0;
}
