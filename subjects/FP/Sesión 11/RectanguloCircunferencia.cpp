#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Constantes globales

const double PI = 6 * asin(0.5);

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
};

/****************************************************************************/

class Circunferencia{
	private:
	
	Punto2D centro;
	double radio;		// PRE: radio >= 0

	public:
	
	/****************************************************************/
	// Métodos constructores

	Circunferencia() :radio(0) {

		Punto2D c;

		c.x = 0;
		c.y = 0;

		centro = c;

	}

	// PRE: r >= 0
	Circunferencia(Punto2D punto, double r) :centro(punto), radio(r) {}

	/****************************************************************/
	// Devuelve el área de la circunferencia

	double ObtenerArea(){
		return PI * radio * radio;	// Devuelve pi * r^2
	}

	/****************************************************************/
	// Aumenta el raio de la circunferencia

	void AumentarRadio(double aumento){
		radio += aumento;
	}

	/****************************************************************/
	// Devuelve los datos de la circunferencia en formato texto

	string ToString(){
		return "Circunferencia de centro (" + to_string(centro.x) + ", " 
				+ to_string(centro.y) + ") y radio " + to_string(radio);
	}
};

/****************************************************************************
	Dado un rectángulo, devuelve la circunferencia centrada en el punto de
	corte de las diagonales del rectángulo cuya superficie es la menor
	que todas las superficies de área mayor que el rectángulo

  Parámetros: rect, el rectángulo en el que centramos la circunferencia
  Devuelve: La circunferencia

****************************************************************************/

Circunferencia CircunferenciaCentrada(Rectangulo rect){

	// Valores especificados en el enunciado
	const double RADIO_INICIAL = 0.5;
	const double INCREMENTO = 0.25;

	// Inicializa la circunferencia en los valores iniciales

	Circunferencia circf(rect.ObtenerCentro(), RADIO_INICIAL);

	// Obtiene el área del rectángulo

	double area_rect = rect.ObtenerArea();

	// Si el área de la circunferencia es menor o igual que la del rectángulo, 
	// incrementamos su radio en INCREMENTO

	while(circf.ObtenerArea() <= area_rect)
		circf.AumentarRadio(INCREMENTO);

	return circf;
}

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

/****************************************************************************/

int main(){
	
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

	// Obtenemos la circunferencia

	Circunferencia circf = CircunferenciaCentrada(rect);

	// SALIDAS

	// Obtenemos los datos de la circunferencia para imprimirlos

	cout << endl;
	cout << endl;

	cout << "La circunferencia sera: " << endl;
	cout << circf.ToString() << endl;

	cout << endl;
	
	return 0;
}
