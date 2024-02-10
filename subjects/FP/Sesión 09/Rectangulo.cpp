#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Constantes

const double PI = 6 * asin(0.5);

/****************************************************************************/
// Definiciones de structs

// Punto en un plano

struct Punto2D{
	double abscisa;
	double ordenada;
};

// Circunferencia

struct Circunferencia{
	Punto2D centro;
	double radio;
};

// Rectángulo

struct Rectangulo{
	Punto2D punto_si;	// Vértice superior izquierdo
	Punto2D punto_id;	// Vértice inferior derecho
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
	Calcula el centro del rectángulo (donde se cortan las dos diagonales).

  Parámetros: rect, el rectángulo
  Devuelve: El centro del rectángulo

****************************************************************************/

Punto2D CentroRectangulo(Rectangulo rect){

	Punto2D centro;

	// El centro del rectángulo es igual que el punto medio de la recta
	// que une el punto superior izquierda con el punto inferior derecha

	centro.abscisa = (rect.punto_si.abscisa + rect.punto_id.abscisa) / 2;

	centro.ordenada = (rect.punto_si.ordenada + rect.punto_id.ordenada) / 2;

	return centro;
}

/****************************************************************************
	Dada una circunferencia, calcula su área.

  Parámetros: circf, la circunferencia.
  Devuelve: El área de la circunferencia.

****************************************************************************/

double Area(Circunferencia circf){
	return PI * circf.radio * circf.radio;		// Area = pi * r^2
}

/****************************************************************************
	Dado un rectángulo, calcula su área.

  Parámetros: rect, el rectángulo
  Devuelve: El área del rectángulo

****************************************************************************/

double Area(Rectangulo rect){

	// Calculamos los lados del rectángulo

	double lado_vert = abs(rect.punto_si.ordenada - rect.punto_id.ordenada);

	double lado_horiz = abs(rect.punto_si.abscisa - rect.punto_id.abscisa);

	return lado_horiz * lado_vert;		// Area = base * altura
}

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

	Circunferencia circf;

	// La circunferencia está centrada en el rectángulo
	circf.centro = CentroRectangulo(rect);

	circf.radio = RADIO_INICIAL;

	// Si el área de la circunferencia es menor o igual que la del rectángulo, 
	// incrementamos su radio en INCREMENTO

	while(Area(circf) <= Area(rect))
		circf.radio += INCREMENTO;

	return circf;
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

	punto.abscisa = stod(abscisa);
	punto.ordenada = stod(ordenada);

	return punto;
}

/****************************************************************************/

int main(){
	
	Punto2D punto1, punto2;

	// ENTRADAS

	punto1 = LeePunto("El vertice superior izquierdo del rectangulo: ");

	cout << endl;

	punto2 = LeePunto("El vertice inferior derecho: ");

	// CÁLCULOS

	Rectangulo rect = {punto1, punto2};

	Circunferencia circf = CircunferenciaCentrada(rect);

	// SALIDAS

	cout.setf(ios::fixed);

	cout << endl;

	cout << "La circunferencia sera: " << endl;
	cout << "\tLa de centro el punto: (" << setw(4) << setprecision(2) 
		 << circf.centro.abscisa << ", " << circf.centro.ordenada << ")" << endl;
	cout << "\tY que tenga " << setw(4) << setprecision(2) << circf.radio 
		 << " de radio." << endl;

	cout << endl;

	return 0;
}
