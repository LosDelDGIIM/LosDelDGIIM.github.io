#include <iostream>

using namespace std;

/***************************************************************************/

class SecuenciaCaracteres {

private:

    static const int TAMANIO = 50; // Núm.casillas disponibles
    char vector_privado[TAMANIO];

    // PRE: 0<=total_utilizados<=TAMANIO

    int total_utilizados; // Núm.casillas ocupadas

public:

    /***********************************************************************/
    // Constructor sin argumentos

    SecuenciaCaracteres (void) : total_utilizados (0)
    {}
    
	/***********************************************************************/
    // Constructor con argumento string.
    // "Copia" el contenido del string en la secuencia 

    SecuenciaCaracteres (string cad) 
    {
    	int num_caracteres;
    	
    	int long_cad = cad.length();
    	
		if (long_cad > TAMANIO) num_caracteres = TAMANIO;
		else num_caracteres = long_cad;
		
		for (int pos=0; pos<num_caracteres; pos++) 
			vector_privado[pos] = cad.at(pos);
			
		total_utilizados = num_caracteres;	
	}
	
    /***********************************************************************/
    // Constructor con char e int.
    // Rellena la secuencia con "n" caracteres "c".

	SecuenciaCaracteres (char c, int n)
	{
		int num_caracteres;

		if (n > TAMANIO) num_caracteres = TAMANIO;
		else num_caracteres = n;
			
		for (int pos=0; pos<num_caracteres; pos++) 
			vector_privado[pos] = c;		

		total_utilizados = num_caracteres;		
	}

    /***********************************************************************/
    // Devuelve el número de casillas ocupadas

    int TotalUtilizados (void)
    {
        return (total_utilizados);
    }

    /***********************************************************************/
    // Devuelve el número de casillas disponibles

    int Capacidad (void)
    {
        return (TAMANIO);
    }

    /***********************************************************************/
    // Añade un elemento ("nuevo") al vector.
    // PRE: total_utilizados < TAMANIO
    // 		La adición se realiza si hay alguna casilla disponible.
    // 		El nuevo elemento se coloca al final del vector.
    // 		Si no hay espacio, no se hace nada.

    void Aniade (char nuevo)
    {
        if (total_utilizados < TAMANIO){
            vector_privado[total_utilizados] = nuevo;
            total_utilizados++;
        }
    }

    /***********************************************************************/
    // Devuelve el elemento de la casilla "indice"
    // PRE: 0 <= indice < total_utilizados

    char Elemento (int indice)
    {
        return (vector_privado[indice]);
    }

    /***********************************************************************/
    // Eliminar el carácter de la posición dada por "indice".
    // Realiza un borrado físico (desplazamiento y sustitución).
    // PRE: 0 <= indice < total_utilizados

    void Elimina (int indice)
    {
        if ((indice >= 0) && (indice < total_utilizados)) {

            int tope = total_utilizados-1; // posic. del último

            for (int i = indice ; i < tope ; i++)
                vector_privado[i] = vector_privado[i+1];

            total_utilizados--;
        }
    }
 
    /***********************************************************************/
    // Compone un string con todos los caracteres que están
    // almacenados en la secuencia y lo devuelve.

    string ToString()
    {
        string cadena;

        for (int i=0; i<total_utilizados; i++)
            cadena = cadena + vector_privado[i];

        return (cadena);
    }
 
	/***********************************************************************/
	// Elimina todas las apariciones del caracter car en la secuencia

	void EliminaOcurrencias(char car){
		
		EliminaOcurrenciasDesde(car, 0);
	
	}

	/***********************************************************************/
	// Elimina todas las apariciones del caracter car en la secuencia
	// a partir de una casilla indicada

	void EliminaOcurrenciasDesde(char car, int pos){
		
		int buscar_ocurrencia = pos - 1;  // Para que comience el bucle en pos

		int almacenar;	// Guarda la posición donde va almaenando los valores
	
		bool encuentra_ocurrencia = false;

		int casillas = total_utilizados;

		// Busca la primera ocurrencia

		while(buscar_ocurrencia < total_utilizados && !encuentra_ocurrencia){

			buscar_ocurrencia++;

			encuentra_ocurrencia = vector_privado[buscar_ocurrencia] == car;

		}

		// Disminuye el número de casillas utilizadas e inicializa almacenar

		if(encuentra_ocurrencia){
			total_utilizados--;
			almacenar = buscar_ocurrencia;
		}

		// Recorre todas las casillas del array hasta la última casilla

		while(buscar_ocurrencia < casillas){

			buscar_ocurrencia++;

			// Si no es el caracter buscado, va moviendo los caracteres

			if(vector_privado[buscar_ocurrencia] != car){

				vector_privado[almacenar] = vector_privado[buscar_ocurrencia];

				almacenar++;

			// Si no, elimina otra casilla

			}else{

				total_utilizados--;

			}

		}
	
	}

	/***********************************************************************/
	// Elimina todas las apariciones repetidas de los caracteres
	// conservndo sólo la primera aparición de estos

	void EliminaRepetidos(){

		int buscar = 0;

		char caracter;

		// Mientras que haya casillas por analizar

		while(buscar < total_utilizados){

			caracter = vector_privado[buscar];

			// Elimina todos los caracteres siguientes iguales a caracter

			EliminaOcurrenciasDesde(caracter, buscar + 1);

			buscar++;

		}

	}

};	// Clase SecuenciaCaracateres

/***************************************************************************/

int main(){
	
	string cad;

	// ENTRADAS

	cout << "Introduzca la cadena: " << endl;
	getline(cin, cad);

	// CÁLCULOS

	SecuenciaCaracteres secuencia(cad);

	secuencia.EliminaRepetidos();

	// SALIDAS

	cout << endl;

	cout << "Su cadena: " << endl;
	cout << secuencia.ToString() << endl;

	cout << endl;
	
	return 0;
}
