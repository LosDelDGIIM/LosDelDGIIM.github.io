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

	/***********************************************************************/
	// Elimina todos los caracteres desde una posición (incluida esta)
	// PRE: 0 <= pos < total_utilizados

	void EliminaDesde(int pos){

		if(pos >= 0 && pos < total_utilizados){

			// Restringe las posiciones válidas

			total_utilizados = pos;

		}

	}

	/***********************************************************************/
	// Elimina todos los caracteres hasta una posición (incluida esta)
	// PRE: 0 <= pos < total_utilizados

	void EliminaHasta(int pos){

		if(pos >= 0 && pos < total_utilizados){

			// Restringe las posiciones válidas

			total_utilizados -= pos + 1;

			int almacenar = 0;

			int seleccionar = pos + 1;

			// Mueve la cadena hacia la izquierda

			for(int i = 0; i < total_utilizados; i++){

				vector_privado[almacenar] = vector_privado[seleccionar];

				almacenar++;

				seleccionar++;

			}

		}

	}

	/***********************************************************************/
	// Elimina el exceso de espacios en blanco en la cadena, dejando uno

	void EliminaExcesoBlancos(){

		const char ESPACIO = ' ';

		int buscar = 0;

		int retardo_almacenar = 0;

		bool espacios_seguidos;

		// Busca el primer espacio doble

		while(buscar < total_utilizados - 1 && !espacios_seguidos){

			espacios_seguidos = vector_privado[buscar] == ESPACIO 
								&& vector_privado[buscar + 1] == ESPACIO;

			buscar++;

		}

		// Si encontró alguno, retarda el almacenamiento

		if(espacios_seguidos){
			retardo_almacenar++;
			buscar++;
		}

		// Recorre toda la secuencia

		while(buscar < total_utilizados){

			// Si encuentra más espacios seguidos retrasa el almacenamiento

			if(vector_privado[buscar - 1] == ESPACIO 
										&& vector_privado[buscar] == ESPACIO)
				retardo_almacenar++;

			else	// Va moviendo a la izquierda los caracteres
				vector_privado[buscar - retardo_almacenar] = 
														vector_privado[buscar];

			buscar++;

		}

		// Se calculan las nuevas casillas utilizadas
		
		total_utilizados -= retardo_almacenar;

	}

	/***********************************************************************/
	// Devuelve una subcadena de esta secuencia de caracteres comenzando en
	// la posición especificada y obteniendo longitud número de caracteres

	// PRE: 0 <= inicio < total_utilizados
	//		0 <= inicio + longitud <= total_utilizados

	SecuenciaCaracteres Subcadena(int inicio, int longitud){

		SecuenciaCaracteres cad;

		int pos = inicio;
		int caracteres = 0;

		// Mientras que se puedan seguir considerando caracteres y no se 
		// tengan todos

		while(pos < total_utilizados && caracteres != longitud){

			// Concatena a cad el caracter en la posición pos

			cad.Aniade(vector_privado[pos]);

			caracteres++;
			pos++;

		}

		return cad;
	}

	/***********************************************************************/
	// Devuelve true si el vector es un palíndromo. 
	
	bool EsPalindromo ()
	{
		bool es_palindromo;
		int izda, dcha; // Para recorrer el vector por los dos extremos 

		es_palindromo = true; 
		
		izda = 0;	// Para recorrer de izqierda a derecha
		dcha = total_utilizados - 1; // Para recorrer de derecha a izquierda

		while (izda < dcha && es_palindromo) {

			if (vector_privado[izda] != vector_privado[dcha])

				es_palindromo = false; // terminar

			else {	// seguir buscando

				izda++; // posición siguiente
				dcha--;	// posición anterior
			}

		} // while (izda < dcha && es_palindromo)

		return es_palindromo;
	}

	/***********************************************************************/
	// Devuelve la posición del primer caracter del tipo especificado
	// que se encuentra a continuación de la posición especificada
	// Si este no existe, se devolverá un -1

	// PRE: 0 <= pos < total_utilizados

	int Busca(char caracter, int inicio){

		int pos = inicio;

		int posicion_encontrada = -1;	// Valor de error si no encuentra nada

		bool seguir_buscando = true;

		// Se repite mientras que nos enecuentre caracter

		while(pos < total_utilizados && seguir_buscando){

			if(vector_privado[pos] != caracter)
				pos++;
	
			else
				seguir_buscando = false;

		}

		// Si se encontró, se devuelve su posición y si no, -1

		if(!seguir_buscando)
			posicion_encontrada = pos;

		return posicion_encontrada;
	}

	/***********************************************************************/
	// Busca y devuelve cual es el mayor palíndromo que alberga nuestra 
	// secuencia de caracters	

	SecuenciaCaracteres MayorPalindromo(){

		// Posición y longitud del palíndromo máximo encontrado

		int long_palindromo = 1;

		int pos_palindromo = 0;

		SecuenciaCaracteres cad_auxiliar;

		// Recorre la cadena

		for(int pos = 0; pos < total_utilizados; pos++){
			
			char caracter = vector_privado[pos];

			// Posición a partir de la cual busca palíndromos

			int pos_busqueda = pos + 1;

			// Busca la siguiente aparición del caracter caracter

			int posicion_final = Busca(caracter, pos_busqueda);

			// Mientras que haya apariciones

			while(posicion_final != -1){
	
				// Se guarda su longitud

				int longitud = posicion_final - pos + 1;

				// Se obtiene el candidato a palíndromo

				cad_auxiliar = Subcadena(pos, longitud);
				
				// Si tiene longitud mayor al mayor palíndromo

				if(longitud > long_palindromo){

					// Se evalúa que sea un palíndromo

					if(cad_auxiliar.EsPalindromo()){
				
						// Se almacena como máximo

						pos_palindromo = pos;
						long_palindromo = longitud;

					}

				}

				// Busca la siguiente aparición de caracter

				pos_busqueda = posicion_final + 1;

				posicion_final = Busca(caracter, pos_busqueda);

			}	// while(posicion_final != -1)
			
		}	// for()

		return Subcadena(pos_palindromo, long_palindromo);
	}

};	// Clase SecuenciaCaracateres

/***************************************************************************/

int main(){
	
	// Batería de pruebas

	const int PRUEBAS = 4;

	SecuenciaCaracteres sec[PRUEBAS] = {SecuenciaCaracteres("CABBADE"), 
								SecuenciaCaracteres("ABCDEF"), 
								SecuenciaCaracteres("ABBA"), 
								SecuenciaCaracteres("gAAtySHHSvvABCCBAfh")};

	// SALIDAS

	for(int i = 0; i < PRUEBAS; i++){
		
		cout << "El mayor palindromo en " << sec[i].ToString() << " es : " 
			 << endl;

		cout << sec[i].MayorPalindromo().ToString() << endl;

		cout << endl;

	}

	return 0;
}
