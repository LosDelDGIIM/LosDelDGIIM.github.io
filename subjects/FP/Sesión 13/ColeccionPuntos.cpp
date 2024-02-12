#include <iostream>
#include <cmath>

using namespace std;

/****************************************************************************
	Eleva al cuadrado un número

  Parámetro: numero
  Devuelve: numero^2

****************************************************************************/

double Cuadrado(double numero){
	return numero * numero;
}

/****************************************************************************
	Pasa una cadena a mayúsculas

  Parámetro: cadena
  Devuelve: cadena con todos sus caracteres en masyúscula

****************************************************************************/

string Mayuscula(string cadena){
	
	string cad;

	for(int i = 0; i < cadena.length(); i++){

		cad += toupper(cadena.at(i));

	}

	return cad;
}

/****************************************************************************/

class Punto2D{

	// Campos de clase

	private:
	
	double abscisa;
	double ordenada;

	// Métodos

	public:

	/****************************************************************/
	// Métodos constructores

	Punto2D() :Punto2D(0, 0) {}

	Punto2D(double x, double y) :abscisa(x), ordenada(y) {}

	/****************************************************************/
	// SETTERS

	void SetAbscisa(double x){
		abscisa = x;
	}

	void SetOrdenada(double y){
		ordenada = y;
	}

	void SetCoordenadas(double x, double y){
		abscisa = x;
		ordenada = y;
	}

	/****************************************************************/
	// GETTERS

	double GetAbscisa(){
		return abscisa;
	}

	double GetOrdenada(){
		return ordenada;
	}

	/****************************************************************/
	// Devuelve la información del punto en el formato:
	// (abscisa, ordenada)

	string ToString(){

		return "(" + to_string(abscisa) + ", " + to_string(ordenada) + ")";

	}

};

/****************************************************************************/

class Circunferencia{
	
	// Campos de clase

	private:
	
	static const double PI;

	Punto2D centro;
	double radio;		// PRE: radio >= 0

	// Métodoss

	public:
	
	/****************************************************************/
	// Métodos constructores

	Circunferencia() :radio(0) {}

	// PRE: r >= 0
	Circunferencia(Punto2D punto, double r) :centro(punto), radio(r) {}

	/****************************************************************/
	// GETTERS

	Punto2D ObtenerCentro(){
		return centro;
	}

	double ObtenerRadio(){
		return radio;
	}

	double ObtenerDiametro(){
		return 2 * radio;
	}

	/****************************************************************/
	// Devuelve el área de la circunferencia

	double ObtenerArea(){
		return PI * radio * radio;
	}

	/****************************************************************/
	// Devuelve la longitud de la circunferencia

	double ObtenerLongitud(){
		return 2 * PI * radio;
	}

	/****************************************************************/
	// Aumenta el radio de la circunferencia

	void AumentarRadio(double aumento){
		radio += aumento;
	}

	/****************************************************************/
	// Devuelve true si punto está contenido en esta circunferencia, false si 
	// no, usando la fórmula:
	// (x0 - x)^2 + (y0 - y)^2 <= r^2

	bool Contiene(Punto2D punto){

		return Cuadrado(centro.GetAbscisa() - punto.GetAbscisa()) + 
			   Cuadrado(centro.GetOrdenada() - punto.GetOrdenada()) 
												<= Cuadrado(radio);

	}

	/****************************************************************/
	// Devuelve los datos de la circunferencia en el formato:
	// {(abscisa, ordenada), radio}

	string ToString(){
		return "{" + centro.ToString() + ", " + to_string(radio) + "}";
	}
};

const double Circunferencia::PI = 6 * asin(0.5);

/****************************************************************************/

class LectorPunto2D{

	// Campos de clase

	private:
	
	string mensaje;

	// Métodos

	public:
	
	/****************************************************************/
	// Método constructor

	LectorPunto2D() :mensaje("") {}

	LectorPunto2D(string msg) :mensaje(msg) {}

	/****************************************************************/
	// Cambia el mensaje

	void SetMensaje(string msg){
		mensaje = msg;
	}

	/****************************************************************/
	// Imprime el mensaje en consola

	void ImprimeMensaje(){
		cout << mensaje << endl;
	}

	/****************************************************************/
	// Solicita por consola un punto al usuario y lo devuelve

	Punto2D Lee(){

		double abscisa, ordenada;

		abscisa = LeeReal("\tAbscisa: ");
		ordenada = LeeReal("\tOrdenada: ");

		return Punto2D(abscisa, ordenada);
	}

	/**************************************************************/
	// Imprime el mensaje y lee un número real del usuario

	double LeeReal(string msg){
		string numero;

		do{
	
			cout << msg;
			cin >> numero;

		}while(!EsReal(numero));
	
		return stod(numero);
	}

	/****************************************************************/
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

};	// Clase LectoPunto2D

/****************************************************************************/

class ColeccionPuntos2D{

	// Campos de clase

	private:
	
	static const int CAPACIDAD_MAX = 100;

	Punto2D puntos[CAPACIDAD_MAX];
	int pos_validas;

	// Métodos

	public:
	
	/****************************************************************/	
	// Métodos constructores

	ColeccionPuntos2D() :pos_validas(0) {}

	/****************************************************************/
	// GETTERS

	int GetCapacidadMaxima(){
		return CAPACIDAD_MAX;
	}

	int GetOcupados(){
		return pos_validas;
	}

	/****************************************************************/
	// Añade un nuevo Punto2D
	// PRE: pos_validas < CAPACIDAD_MAX - 1

	void Aniade(Punto2D punto){
		if(pos_validas < CAPACIDAD_MAX - 1){

			puntos[pos_validas] = punto;
			pos_validas++;

		}
	}

	/****************************************************************/
	// Devuelve el Punto2D de la posición especificada
	// PRE: 0 <= pos < pos_validas

	Punto2D Get(int pos){

		return puntos[pos];

	}

	/****************************************************************/
	// Devuelve el contenido de la clase en el formato:
	// {(x1, y1), (x2, y2), ..., (xn, yn)}

	string ToString(){

		const string SEPARADOR = ", ";

		string cad = "{";

		// Concatena todos los puntos

		for(int i = 0; i < pos_validas - 1; i++){

			cad += puntos[i].ToString() + SEPARADOR;

		}

		cad += puntos[pos_validas - 1].ToString() + "}";

		return cad;
	}

};

/****************************************************************************/

int main(){
	
	const string TERMINADOR = "FIN";

	LectorPunto2D lector;

	ColeccionPuntos2D coleccion;

	Punto2D entrada;

	// ENTRADAS ********************************************************

	// Solicita varios puntos ----------------------------------------

	string abscisa, ordenada;

	cout << "Introduzca una serie de puntos: " << endl;

	cout << "(" << TERMINADOR << " en abscisa para finalizar)" << endl << endl;

	// Entrada anticipada

	do{

		cout << "\tAbscisa: ";
		cin >> abscisa;

	}while(!lector.EsReal(abscisa) && Mayuscula(abscisa) != TERMINADOR);

	// Mientras que no se detecte TERMINADOR

	while(Mayuscula(abscisa) != TERMINADOR){

		// Solicita la ordenada

		do{

			cout << "\tOrdenada: ";
			cin >> ordenada;

		}while(!lector.EsReal(ordenada));

		// Almacena el punto

		entrada.SetCoordenadas(stod(abscisa), stod(ordenada));

		coleccion.Aniade(entrada);

		// Comienza a solicitar el siguente punto

		cout << endl;

		cout << "Siguiente punto: " << endl;
	
		do{

			cout << "\tAbscisa: ";
			cin >> abscisa;

		}while(!lector.EsReal(abscisa) && Mayuscula(abscisa) != TERMINADOR);

	}

	// Si no se introdujo ningun punto, no hace nada

	if(coleccion.GetOcupados() == 0){

		cout << endl;
		cout << "No se introdujo ningun punto" << endl;

	}else{

		// Solicita los parámetros de la circunferencia  ----------------
	
		// Solicita el centro
	
		cout << endl;
	
		cout << "Introduzca una circunferencia: " << endl;
	
		lector.SetMensaje("Centro de la circunferencia: ");
	
		lector.ImprimeMensaje();
	
		Punto2D centro = lector.Lee();
	
		// Solicita el radio
	
		cout << endl;
	
		double radio = lector.LeeReal("El radio: ");
	
		// CÁLCULOS Y SALIDAS ************************************************
	
		cout << endl << endl;
	
		Circunferencia circf(centro, radio);
	
		// Muestra qué puntos están contenidos en la circunferencia y cuales no
	
		Punto2D auxiliar;
	
		for(int i = 0; i < coleccion.GetOcupados(); i++){
	
			cout << coleccion.Get(i).ToString() << " : ";
	
			if(circf.Contiene(coleccion.Get(i)))
				cout << "Esta contenido" << endl;
	
			else
				cout << "No esta contenido" << endl;
	
		}
	
		cout << endl;

	}

	return 0;
}
