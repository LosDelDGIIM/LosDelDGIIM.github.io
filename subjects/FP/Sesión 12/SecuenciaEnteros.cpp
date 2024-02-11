#include <iostream>

using namespace std;

/****************************************************************************/

class SecuenciaEnteros{
	
	// Campos de clase

	private:
	
	static const int TAMANIO = 100; 	// Tamaño del array

	int array[TAMANIO];

	int pos_validas;	// PRE: 0 <= pos_validas < TAMANIO

	// Métodos

	public:
	
	/***********************************************************************/
	// Método constructor

	SecuenciaEnteros() :pos_validas(0) {}

	/***********************************************************************/
	// GETTERS

	int Longitud(){
		return pos_validas;
	}

	int Casillas(){
		return TAMANIO;
	}

	/***********************************************************************/
	// Añade un elemento a la secuencia
	// PRE: pos_validas < TAMANIO

	void Aniade(int n){
		if(pos_validas < TAMANIO){

			array[pos_validas] = n;
			pos_validas++;

		}
	}

	/***********************************************************************/
	// Obtiene el elmento de la posición especificada
	// PRE: 0 <= indice < pos_validas

	int Obtener(int indice){
		return array[indice];
	}

	/***********************************************************************/
	// Elimina el elemento especificado del array
	// PRE: 0 <= indice < pos_validas

	void Eliminar(int indice){

		for(int i = indice + 1; i < pos_validas; i++){
			array[i - 1] = array[i];
		}

		pos_validas--;

	}
	
	/***********************************************************************/
	// Devuelve el contenido de la secuencia en el siguiente formato:
	// [n, n, ..., n]
	
	string ToString(){
		
		string cad = "[";

		for(int i = 0; i < pos_validas - 1; i++){
			cad += to_string(array[i]) + ", ";
		}

		cad += to_string(array[pos_validas - 1]) + "]";

		return cad;
	}

	/***********************************************************************/
	// Intercambia dos valores en la secuencia
	// PRE: 0 <= indice1, indice2 < pos_validas

	void Intercambia(int indice1, int indice2){

		int auxiliar = array[indice1];
		array[indice1] = array[indice2];
		array[indice2] = auxiliar;

	}

};	// Clase SecuenciaEnteros

/****************************************************************************/

