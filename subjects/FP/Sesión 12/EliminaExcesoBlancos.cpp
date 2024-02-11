#include <iostream>

using namespace std;

/***************************************************************************/

class Lector{

	// Campo de clase

	private:
	string mensaje;

	// Métodos

	public:

	/**************************************************************/
	// Método constructor

	Lector() :mensaje() {}

	Lector(string msg) : mensaje(msg) {}

	/**************************************************************/	
	// Cambia el mensaje

	void SetTitulo(string msg){
		mensaje = msg;
	}

	/**************************************************************/	
	// Obtiene el mensaje

	string GetTitulo() {
		return mensaje;
	}

	/**************************************************************/
	// Métodos de enteros
	/**************************************************************/
	// Imprime el mensaje y se repite mientras que no sea un número entero

	int LeeEntero(){
		string numero;
	
		do{
	
			cout << mensaje;
			cin >> numero;
	
		}while(!EsEntero(numero));
	
		return stoi(numero);
	}

	/**************************************************************/
	// Devuelve un entero mayor o igual que referencia, repitiendo 
	// la entrada al usuario si esto no se da

	int LeeEnteroMayorOIgual(int referencia){
		int numero;

		do{
			numero = LeeEntero();
		}while(numero < referencia);

		return numero;
	}

	/**************************************************************/
	// Devuelve un entero entre min y max, repitiendo la entrada al 
	// usuario si esto no se da
	// PRE: min <= max

	int LeeEnteroEnRango(int min, int max){
		int numero;

		do{
			numero = LeeEntero();
		}while(numero < min || numero > max);

		return numero;
	}

	/**************************************************************/
	// Devuelve un número entero entre min y max o menor o igual que 
	// terminador, repitiendo la entrada si ninguna de estas condicioens se da
	// PRE: terminador <= min <= max

	int LeeEnteroEnRangoConTerminador(int min, int max, 
														int terminador){
		int numero;

		// Repite la entrada si numero no pertenece al intervalo
		// (-inf, terminador] U [min, max]

		do{
			numero = LeeEntero();
		}while(numero > max || (numero > terminador && numero < min));

		return numero;
	}

	/**************************************************************/
	// Métodos de reales
	/**************************************************************/
	// Imprime el mensaje y lee un número real del usuario

	double LeeReal(){
		string numero;

		do{
	
			cout << mensaje;
			cin >> numero;

		}while(!EsReal(numero));
	
		return stod(numero);
	}

	/**************************************************************/
	// Devuelve un número mayor o igual que referencia, repitiendo 
	// la entrada si esto no se da

	double LeeRealMayorOIgual(double referencia){
		double numero;
	
		do{
			numero = LeeReal();
		}while(numero < referencia);
	
		return numero;
	}

	/**************************************************************/
	// Devuelve un número real entre min y max, repitiendo la entrada 
	// si esto no se da
	// PRE: min <= max

	double LeeRealEnRango(double min, double max){
		double numero;

		do{
			numero = LeeReal();
		}while(numero < min || numero > max);

		return numero;
	}

	/**************************************************************/
	// Devuelve un número real entre min y max o menor o igual que terminador,
	// repitiendo la entrada si ninguna de estas condicioens se da
	// PRE: terminador <= min <= max

	double LeeRealEnRangoConTerminador(double min, double max, 
														double terminador){
		double numero;

		// Repite la entrada si numero no pertenece al intervalo
		// (-inf, terminador] U [min, max]

		do{
			numero = LeeReal();
		}while(numero > max || (numero > terminador && numero < min));

		return numero;
	}

	/**************************************************************/
	// Métodos que determinan si un número es real o entero
	/**************************************************************/

	private:

	// Determina si un número es entero o si no

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

	/**************************************************************/

	// Determina si un número es real o si no

	bool EsReal(string cadena){
	
		const string SIGNOS = "+-";
	
		const char PUNTO_DECIMAL = '.';
	
		bool es_real;
	
		// Si cadena está vacía no es un número real
		if(cadena.length() == 0)
			es_real = false;
	
		else{
		
			// Si el primer caracter es un signo y hay más caracteres se borra
	
			if(SIGNOS.find(cadena.at(0)) != string::npos && cadena.length() > 1)
				cadena.erase(0, 1);
	
			int i = 0;
	
			es_real = true;
	
			bool hay_punto = false;
	
			// Comprobamos todos los caracteres
	
			while(es_real && i < cadena.length()){
	
				// Si no es un dígito
	
				if(!isdigit(cadena.at(i))){
		
					// Se comprueba que sea un punto y que haya más caracteres
	
					if(cadena.at(i) == PUNTO_DECIMAL && cadena.length() > 1){
		
						// Si ya había un punto, hay 2 puntos => no es un real
	
						if(hay_punto) 
							es_real = false;
	
						// Si no había ninguno, lo tenemos en cuenta ahora
	
						else{
							hay_punto = true;
							i++;
						}
	
					}else	// No es un real
						es_real = false;
		
				}else	// Es un dígito
					i++;
	
			}
	
		}
	
		return es_real;

	}	// EsReal(string cadena)

};	// Clase Lector

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

	
};	// Clase SecuenciaCaracateres

/***************************************************************************/

int main(){
	
	string cad;

	// ENTRADAS

	cout << "Introduzca la cadena: " << endl;
	getline(cin, cad);

	// CÁLCULOS

	SecuenciaCaracteres secuencia(cad);

	secuencia.EliminaExcesoBlancos();

	// SALIDAS

	cout << endl;

	cout << "Su cadena: " << endl;
	cout << secuencia.ToString() << endl;

	cout << endl;
	
	return 0;
}
