#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Constantes globales

const double PI = 6 * asin(0.5);

const double RADIO_MINIMO = 0.5, INCREMENTO = 0.25;

// Definición de structs

struct Punto2D{
	double x;
	double y;
};

/****************************************************************************/

class Rectangulo{
	private:
	
	Punto2D vert_s_i;	// Vértice superior izquierdo
	Punto2D vert_i_d;	// Vértice inferior derecho

	// Longitudes de una base y de una altura

	double long_base;
	double long_altura;

	public:
	
	/****************************************************************/
	// Método constructor

	Rectangulo() :long_base(0), long_altura(0) {

		Punto2D punto;

		punto.x = 0;
		punto.y = 0;

		vert_s_i = punto;
		vert_i_d = punto;

	}

	Rectangulo(Punto2D punto1, Punto2D punto2) :vert_s_i(punto1),
											    vert_i_d(punto2) {
	
		// Calcula las longitudes de una base y de una altura

		long_base = abs(vert_s_i.x - vert_i_d.x);
		long_altura = abs(vert_s_i.y - vert_i_d.y);
	}

	/****************************************************************/
	// Devuelve el punto de corte de las dos diagoanales del rectángulo

	Punto2D ObtenerCentro(){
		Punto2D centro;

		// Calcula el centro del rectángulo, con las medias entre las 
		// coordenadas de dos vértices opuestos

		centro.x = (vert_s_i.x + vert_i_d.x) / 2;
		centro.y = (vert_s_i.y + vert_i_d.y) / 2;

		return centro;
	}

	/****************************************************************/
	// Devuelve el área del rectángulo

	double ObtenerArea(){
		return long_base * long_altura;		// base * altura
	}

	/****************************************************************/
	// Devuelve el máximo radio posible que puede tener una circunferencia 
	// inscrita en este rectángulo
	
	double RadioMaximoCircunferenciaInscrita(){
	
		// Devuelve la mitad del lado menor del rectángulo

		double minimo = (long_altura < long_base)? long_altura : long_base;

		return minimo / 2;

	}

};

/****************************************************************************/

class Circunferencia{
	private:
	
	Punto2D centro;
	double radio;

	public:
	
	/****************************************************************/
	// Métodos constructores

	Circunferencia(double r) :radio(r) {

		Punto2D c;

		c.x = 0;
		c.y = 0;

		centro = c;
	}

	Circunferencia(Punto2D punto, double r) :centro(punto), radio(r) {}

	/****************************************************************/
	// Devuelve el área de la circunferencia

	double ObtenerArea(){
		return PI * radio * radio;	// Devuelve pi * r^2
	}

	/****************************************************************/
	// Aumenta el radio de la circunferencia

	void AumentarRadio(double aumento){
		radio += aumento;
	}

	/****************************************************************/
	// Devuelve los datos de la circunferencia en formato texto

	string ToString(){
		return "Circunferencia de centro (" + to_string(centro.x) + ", " 
				+ to_string(centro.y) + ") y radio " + to_string(radio);
	}

	/****************************************************************/
	// Devuelve si la circunferencia tiene un radio válido para inscribirse 
	// en el rectángulo especificado

	bool PuedeInscribirse(Rectangulo rect){

		double radio_maximo = rect.RadioMaximoCircunferenciaInscrita();

		return radio <= radio_maximo;

	}

};

/****************************************************************************
	Determina si cadena es un número real o si no.

  Parámetros: cadena
  Devuelve: true si cadena es un número real, false si no

****************************************************************************/

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
}

/****************************************************************************
	Imprime un mensaje en consola y solicita la ordenada y la abscisa de
	un punto, devolviendo el punto introducido.

  Parámetros: titulo, el mensaje que se imprime al usuario
  Devuelve: El punto que el usuario introdujo

****************************************************************************/

Punto2D LeePunto(string titulo){

	string abscisa, ordenada;

	cout << titulo << endl;

	// Solicita la abscisa

	do{

		cout << "\tLa abscisa: ";
		cin >> abscisa;

	}while(!EsReal(abscisa));

	// Solicita la ordenada

	do{

		cout << "\tLa ordenada: ";
		cin >> ordenada;

	}while(!EsReal(ordenada));

	// Crea el objeto punto a partir de la abscisa y de la ordenada

	Punto2D punto;

	punto.x = stod(abscisa);
	punto.y = stod(ordenada);

	return punto;
}

/****************************************************************************
	Cuenta el número de circunferencias que se pueden inscribir en un 
	rectángulo

  Parámetros: rect
  Devuelve: El número de circunferencias que se pueden inscribir en rect

****************************************************************************/

int ContarCircunferenciasInscritas(Rectangulo rect){

	int contador = 0;

	// Coge el radio de la circunferencia inicial

	Circunferencia circf(RADIO_MINIMO);

	// Mientras que el radio sea válido, se cuenta

	while(circf.PuedeInscribirse(rect)){

		contador++;
		circf.AumentarRadio(INCREMENTO);

	}

	return contador;
}

/****************************************************************************/

int main(){
	
	const int LONG_ARRAY = 100;

	Punto2D punto1, punto2;

	// ENTRADAS

	cout << "Parametros del rectangulo:" << endl;

	cout << endl;

	punto1 = LeePunto("El vertice superior izquierdo del rectangulo: ");

	cout << endl;

	punto2 = LeePunto("El vertice inferior derecho del rectangulo: ");

	// CÁLCULOS

	// Creamos nuestro rectángulo

	Rectangulo rect(punto1, punto2);

	int numero_circfs = ContarCircunferenciasInscritas(rect);

	// SALIDAS

	cout << endl;

	if(numero_circfs == 0){

		cout << "No puede inscribirse ninguna circunferencia." << endl;

	}else{

		cout << "Pueden inscribirse " << numero_circfs << " circunferencias:" 
		 << endl;

		cout << endl;
	
		// Inicializa la primera circunferencia
	
		Circunferencia circf(rect.ObtenerCentro(), RADIO_MINIMO);
	
		for(int i = 0; i < numero_circfs; i++){
	
			cout << circf.ToString() << endl;
	
			circf.AumentarRadio(INCREMENTO);
	
		}

	}

	cout << endl;

	return 0;
}
