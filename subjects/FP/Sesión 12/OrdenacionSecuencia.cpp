#include <iostream>
#include <random>
#include <chrono>

using namespace std;

/****************************************************************************/

class Lector{

	// Campo de clase

	private:
	string mensaje;

	// Métodos

	public:

	/**************************************************************/
	// Método constructor

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

/****************************************************************************
	Cuenta el número de veces que aparece un caracter en una cadena

  Parámetros: cad, caracter
  Devuelve: el número de veces que aparece caracter en cad

****************************************************************************/

int ContarVeces(string cad, char caracter){
	
	int contador = 0;

	for(int i = 0; i < cad.length(); i++)
		if(cad.at(i) == caracter)
			contador++;

	return contador;
}

/****************************************************************************
	Determina si un número es menor que otro o no, considerando como mayor
	aquel que más nueves tenga en él (si son iguales, el que más ochos y así 
	sucesivamente hasta el cero)

  Parámetros: num1, num2
  Devuelve: true si num1 < num2

****************************************************************************/

bool EsMenor(int num1, int num2){
	
	const int MAYOR_DIGITO = 9, MENOR_DIGITO = 0;
	const char ASCII_0 = '0';

	int digito = MAYOR_DIGITO;

	bool seguir = true;
	bool menor = false;

	string str_num1 = to_string(num1);
	string str_num2 = to_string(num2);

	while(seguir && digito >= MENOR_DIGITO){

		// Cuenta el número de digito en num1 y num2

		int veces1 = ContarVeces(str_num1, ASCII_0 + digito);
		int veces2 = ContarVeces(str_num2, ASCII_0 + digito);

		// Si son distintos, se deterina cual es menor

		if(veces1 != veces2){
	
			seguir = false;

			menor = veces1 < veces2;

		}else
			digito--;	// Si son iguales, se considera el siguiente dígito
	}

	return menor;
}

/****************************************************************************/

class GeneradorAleatorioEnteros{
private:
	
	mt19937 generador_mersenne;    // Mersenne twister
	uniform_int_distribution<int>  distribucion_uniforme;
	
	/************************************************************************/
	
	long long Nanosec(){
		return 
			(chrono::high_resolution_clock::now().time_since_epoch().count());
	}
	
	/************************************************************************/ 
	
public:
	
	/************************************************************************/
		
	GeneradorAleatorioEnteros() : GeneradorAleatorioEnteros(0, 1) 
	{ }
	
	/************************************************************************/  
	GeneradorAleatorioEnteros(int min, int max) {
	
		const int A_DESCARTAR = 70000;
		// ACM TOMS Volume 32 Issue 1, March 2006
		
		auto semilla = Nanosec();
		generador_mersenne.seed(semilla);
		generador_mersenne.discard(A_DESCARTAR);
		distribucion_uniforme = uniform_int_distribution<int> (min, max);
	}
	
	/************************************************************************/
	
	int Siguiente(){
	  return (distribucion_uniforme(generador_mersenne));
	}
	
	/************************************************************************/

};

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

	/***********************************************************************/
	// Obtiene la posición del menor valor del array, comenzando por la 
	// casilla pos y siguiendo el criterio de orden de EsMenor()
	// PRE: 0 <= pos < pos_validas

	int MinimoDesde(int pos){

		// Almacena la posición del mínimo valor

		int pos_min = pos;

		// Recorre array buscando el menor

		for(int i = pos + 1; i < pos_validas; i++){

			if(EsMenor(array[i], array[pos_min])){

				pos_min = i;

			}

		}

		return pos_min;
	}

	/***********************************************************************/
	// Ordena la secuencia por Selection Sort

	void OrdenaSeleccion_NuevoOrden(){
		
		// Recorre la secuencia entera

		for(int i = 0; i < pos_validas - 1; i++){

			// Obtiene la posición del menor elemento a partir de i

			int pos_min = MinimoDesde(i);

			// Lo intercambia con el elemento de la posición i

			Intercambia(i, pos_min);	

		}

	}

	/***********************************************************************/
	// Ordena la secuencia por Insertion Sort

	void OrdenaInsercion_NuevoOrden(){

		for(int i = 1; i < pos_validas; i++){

			// Valor a insertar la subsecuencia ordenada

			int num = array[i];

			int indice = i;

			// Se busca posición en la zona ordenada, desplzando los mayores 
			// a la derecha

			while(indice > 0 && EsMenor(num, array[indice - 1])){

				array[indice] = array[indice - 1];

				indice--;

			}

			// Almacena el valor en el hueco creado

			array[indice] = num;

		}

	}

	/***********************************************************************/
	// ORdena la secuencia por Bubble Sort

	void OrdenaIntercambio_NuevoOrden(){

		for(int i = 0; i < pos_validas; i++){

			for(int j = pos_validas - 1; j > i; j--){

				if(EsMenor(array[j], array[j - 1]))
					Intercambia(j, j-1);

			}

		}

	}

	/***********************************************************************/
	// Ordena la secuencia por un Bubble Sort mejorado, que detiene su 
	// ejecución cuando en una pasada no realiza ningún cambio

	void OrdenaIntercambioMejorado_NuevoOrden(){

		bool cambiado = true;	// Para entrar en el for

		for(int i = 0; i < pos_validas && cambiado; i++){

			cambiado = false;	// No se ha cambiado todavía ningún valor

			for(int j = pos_validas - 1; j > i; j--){

				if(EsMenor(array[j], array[j - 1])){

					Intercambia(j, j-1);
					cambiado = true;	// Se ha cambiado un valor

				}

			}

		}

	}

};	// Clase SecuenciaEnteros

/****************************************************************************/

int main(){
	
	const int MIN_RANDOM = 0, MAX_RANDOM = 999;
	const int MIN_N_ELEMENTOS = 2;

	int num_elementos;

	SecuenciaEnteros secuencia;

	// ENTRADAS ----------------------------------------------------------

	Lector leer("Elementos de la secuencia (entre " + to_string(MIN_N_ELEMENTOS) 
						+ " y " + to_string(secuencia.Casillas()) + "): ");

	num_elementos = leer.LeeEnteroEnRango(MIN_N_ELEMENTOS, 
														secuencia.Casillas());

	// CÁLCULOS ----------------------------------------------------------

	// Rellena la secuencia con num_elementos elementos aleatorios

	GeneradorAleatorioEnteros generador(MIN_RANDOM, MAX_RANDOM);

	for(int i = 0; i < num_elementos; i++){
		secuencia.Aniade(generador.Siguiente());
	}

	// Crea varias secuencias que se ordenaran de forma distinta

	const int METODOS = 4;
	SecuenciaEnteros secuencias[METODOS];

	for(int i = 0; i < METODOS; i++){
		secuencias[i] = secuencia;
	}

	// Ordena cada secuencia por un método

	secuencias[0].OrdenaSeleccion_NuevoOrden();
	secuencias[1].OrdenaInsercion_NuevoOrden();
	secuencias[2].OrdenaIntercambio_NuevoOrden();
	secuencias[3].OrdenaIntercambioMejorado_NuevoOrden();

	// SALIDAS ----------------------------------------------------------

	// Muestra cada secuencia
	
	cout << endl;

	cout << "Secuencia original: " << endl;
	cout << secuencia.ToString() << endl;

	cout << endl;

	string mensajes[METODOS] = {"Ordenada por seleccion: ", 
				"Ordenada por insercion: ", "Ordenada por intercambio: ", 
									"Ordenada por intercambio mejorado: "};

	// Imrpime cada secuencia

	for(int i = 0; i < METODOS; i++){
		cout << mensajes[i] << endl;
		cout << secuencias[i].ToString() << endl;
		cout << endl;
	}
	
	return 0;
}
