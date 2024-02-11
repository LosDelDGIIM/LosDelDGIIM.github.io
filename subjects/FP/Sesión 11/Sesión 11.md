# Fundamentos de Programación. Sesión XI de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión XI de prácticas.

En esta sesión de prácticas, se introducen las **clases**, los lo que los ejercicios estarán orientados a su uso.
No lo mencionaremos, pero las funciones **main** debe tener código que nos permita visualizar el correcto funcionamiento de las clases, o el programa que se solicita en cada ejercicio.

## 1. Dinero.cpp
Defina una clase ```Dinero``` para trabajar de forma precisa con datos monetarios. La clase tendrá dos datos miembro: ```euros``` y ```céntimos```.  
  
La clase deberá permitir que se introduzca un número de céntimos arbitrario (siempre que sea positivo o cero) y se encargará de ajustar las cantidades debidamente.  
Por ejemplo, si asignamos ```20 euros y 115 céntimos```, el objeto deberá almacenar el valor ```21 en euros y 15 en céntimos```. No olvide añadir un método ```ToString()``` para reperesentar de forma textual el contenido de un objeto  ```Dinero```.  
  
Haga un programa que calcule el precio final de un producto a partir de su precio inicial, de un incremento fijo mensual y de un número de mese. EL programa irá mostrando, mes a mes, el precio del producto.
```cpp
#include <iostream>

using namespace std;

class Dinero{

	/*****************************************************************/
	// Campos de clase	

	private:
	
	int euros;		// PRE: euros >= 0
	int centimos;	// PRE: centimos >= 0

	public:
	
	/*****************************************************************/
	// Métodos constructores

	Dinero() :euros(0), centimos(0) {}

	// PRE: e >= 0, c >= 0
	Dinero(int e, int c){
		Asignar(e, c);
	}

	/*****************************************************************/
	// Devuelve la información de los campos en un texto

	string ToString(){
		return to_string(euros) + " euros y " + to_string(centimos) 
				+ " centimos ";
	}

	/*****************************************************************/
	// Incrementa el saldo según porc

	// PRE: porc >= 0

	void Incrementar(double porc){
	
		// Pasa el saldo a céntimos

		double dinero = euros * 100 + centimos;

		// Aplica el porcentaje redondeando los céntimos

		int dinero_final = (dinero + dinero * porc / 100) + 0.5;

		// Vuelve a ajustar el saldo en los campos de clase

		Asignar(0, dinero_final);

	}

	/*****************************************************************/

	private: 

	/*****************************************************************/
	// Asigna los euros y los céntimos especificados a los campos de clase
	// con un formato válido (100 cents = 1 e)

	// PRE: e >= 0, c >= 0

	void Asignar(int e, int c){
	
		// Calcula los euros que hay en los centimos
		int euros_en_c = c / 100;

		// Estos centimos ya no cuenta como céntimos
		c -= euros_en_c * 100;

		// Se asignan los euros y los céntimos

		euros = e + euros_en_c;

		centimos = c;
	}

};

/****************************************************************************
	Determina si una cadena es un número entero o si no.

  Parámetros: cadena
  Devuelve: true si cadena es un número entero, false si no

****************************************************************************/

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

/****************************************************************************
	Imprime un mensaje en consola y lee el número entero que introduce el 
	usuario. Repite la entrada mientras que el valor introducido no sea
	un número entero.

  Parámetros: titulo, el mensaje que se muestra al usuario
  Devuelve: el número entero que introduce el usuario

****************************************************************************/

int LeerEntero(string mensaje){
	string numero;

	do{

		cout << mensaje;
		cin >> numero;

	}while(!EsEntero(numero));

	return stoi(numero);
}

/****************************************************************************
	Imprime un mensaje en consola y lee el número entero que introduce el 
	usuario. Repite la entrada mientras que el valor introducido no sea
	un número entero o mientras que este no sea mayor o igual que la referencia

  Parámetros: titulo, el mensaje que se muestra al usuario
			  referencia, valor mínimo que acepta la función
  Devuelve: el número entero que introduce el usuario

****************************************************************************/

int LeerEnteroMayorOIgual(string mensaje, int referencia){

	int numero;

	do{

		numero = LeerEntero(mensaje);

	}while(numero < referencia);

	return numero;
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
	Imprime un mensaje en consola y lee un número real. Mientras que el número 
	introducido por el usuario no sea real, repite la lectura.

  Prámetros: mensaje
  Devuelve: Un número double introducido por el usuario

****************************************************************************/

double LeerReal(string mensaje){
	string numero;

	do{
		cout << mensaje;
		cin >> numero;
	}while(!EsReal(numero));

	return stod(numero);
}

/****************************************************************************
	Imprime un mensaje en consola y lee un número real. Mientras que el número 
	introducido por el usuario no sea real o mientras que el real no sea mayor 
	o igual que la refenrencia, repite la lectura.

  Prámetros: mensaje, referencia
  Devuelve: Un número double introducido por el usuario

****************************************************************************/

double LeerRealMayorOIgual(string mensaje, double referencia){
	double numero;

	do{
	
		numero = LeerReal(mensaje);

	}while(numero < referencia);

	return numero;
}

/****************************************************************************/

int main(){
	
	const int MIN_VALOR_DINERO = 0, MIN_VALOR_PORC = 0, MIN_VALOR_MES = 0;
	int euros, centimos;

	double incremento;

	int meses;

	// ENTRADAS

	// Solicita el saldo de la cuenta

	cout << "Saldo: " << endl;

	euros = LeerEnteroMayorOIgual("\tEuros: ", MIN_VALOR_DINERO);
	centimos = LeerEnteroMayorOIgual("\tCentimos: ", MIN_VALOR_DINERO);

	Dinero monedero(euros, centimos);

	cout << endl;

	// Solicita el porcentaje del incremento y el número de meses

	incremento = LeerRealMayorOIgual("Incremento mensual: ", MIN_VALOR_PORC);

	meses = LeerEnteroMayorOIgual("Numero de meses: ", MIN_VALOR_MES);

	// CÁLCULOS Y SALIDAS

	cout << endl;

	// Por cada mes incrementa el salario y lo imprime en consola

	for(int i = 1; i <= meses; i++){

		monedero.Incrementar(incremento);

		cout << "Mes " << i << ": " << monedero.ToString() << endl;

	}
	
	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2011/Dinero.cpp)

## 2. RectanguloCircunferencia.cpp 
Este ejercicio consiste en reescribir la solución al ejercicio ```1. Rectangulo.cpp``` de la [Sesión IX](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/Sesi%C3%B3n%2009.md) de prácticas:  
  
Desarrolle un programa que pida al usuario un rectángulo y calcule la circunferencia centrada en el punto de corte de las diagonales del rectángulo de forma que su superficie sea la menor entre todas las circunferencias de mayor área que la del rectángulo.  
  
Para el cálculo de la circunferencia, comience con una circunferencia de radio ```0.5``` y vaya incrementando su valor en ```0.25``` hasta hallar la primera circunferencia de área mayor que el rectángulo.  
  
En esta ocasión, deberá mantener el struct:  
```Punto2D```  
```struct``` que representa un punto en el plano bidimensional.  
  
Pero tendrá que crear dos clases:  

```Circunferencia```  
Clase que representa una circunferencia en el plano bidimensional.  
  
```Rectangulo```  
Clase que representa a un rectángulo en el plano bidimensional.  
Un rectángulo viene determinado por el vértice superior izquierdo y por el vértice inferior derecho.  
```cpp
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
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2011/RectanguloCircunferencia.cpp)

## 3. RectanguloCircunferenciasInscritas.cpp
Recupere las clases del ejercicio superior (```2. RectanguloCircunferencias.cpp```) para este problema:  
  
Escriba un programa que lea las coordenadas que definen un rectángulo y calcule y muestre una serie de datos de tipo ```Circunferencia```, todas centrada en en el punto de corte de las diagonales del rectángulo.  
  
Las circunferencias en las que estamos interesadas serán todas las circunferencias inscritas en el rectángulo. Para ello comience con una circunferencia de ```radio = 0.5``` y vaya incrementando su valor ```0.25``` en cada iteración.  
  
Muestre cuántas circunferencias inscritas se han generado.
```cpp
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
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2011/RectanguloCircunferenciasInscritas.cpp)

## 4. Gaussiana.cpp 
Este ejercicio consta de reescribir el ejercicio ```4. GaussianaCDFReglaEmpirica.cpp``` de la [Sesión VIII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/Sesi%C3%B3n%2008.md) de prácticas, cuyo enunciado recordaremos a continuación. En esta ocasión, el interés es añadir una clase ```Gaussiana``` que tenga como campos de clase la media y la desviación típica. Recuerde añadir un método ```ToString``` que nos permita ver estos valores.  
  
Estamos interesados en obtener el área que cubre la función gaussiana en un intervalo dado. Si consideramos el intervalo $]-\infty, x]$, el valor del área de la región que queda bajo la curva de $g(x)$ (siendo $g$ la función gaussiana) se calcula con la _distribución acumulada_ (_cumulative distribution function_ o CDF) en el punto $5x$:
$$CDF(x) = \int_{-\infty}^x g(x)~dx$$
Puede obtenerse un valor aproximado de $CDF(x)$ como la suma de valores de $g(x)$ empezando por valores alejados de la media (y menores que ella). Esto es, en vez de resolver la integral, estaremos interesados en aproximarla con un sumatorio de rectángulos de anchura relativamente pequeña.  
  
Se pedía escribir un programa que calcule $CDF(x)$. El programa debía pedir los parámetros que definen una función gaussiana ($\mu$ y $\sigma$) y el valor de la abscisa $x$, para el que se va a calcular $CDF(x)$. Para el cálculo de $CDF(x)$, realizaremos una suma. Debemos concretar de qué forma la realizaremos:
1. Necesitamos un valor inicial para $x$ (úsese $\mu - 3\sigma$).
2. Un salto entre dos valores consecutivos de $x$ (use una constante).  
   
Recordamos la expresión de la función $g(x)$:
$$g(x) = \dfrac{1}{\sigma\sqrt{2\pi}} e^{\left[\dfrac{-1}{2}\left(\dfrac{x-\mu}{\sigma}\right)²\right]}$$

Escriba un programa que lea los parámetros de una distribución gaussiana ($\mu$ y $\sigma$), y muestre los valores de:
1. $g(x)$ 
2. $CDF(x)$ según como se ha explicado anteriormente.
3. $CDF(x)$ por aproximación empírica.  
Para valores de $x$ omprendidos entre $\mu - 3\sigma$ y $\mu + 3\sigma$ usando ```0.25``` como salto entre los valores de abscisas.  
  
A continuación explicamos cómo calcular $CDF(x)$ mediante aproximación empírica:  
$$CDF(x) \approx w = 1 - g(|x|)(b_1t + b_2t² + b_3t³ + b_4t⁴ + b_5t⁵)$$  
$$t = \dfrac{1}{1+ b_0|x|}$$  
```$b_0$ = 0.2316419```  
```$b_1$ = 0.319381530```  
```$b_2$ = -0.356563782```  
```$b_3$ = 1.781477937```  
```$b_4$ = -1.821255978```  
```$b_5$ = 1.330274429```  
  
Finalmente, si $x \geq 0$, entonces $CDF(x) = w$.  
Si no, $CDF(x) = 1 - w$.
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/****************************************************************************
	Eleva un número al cuadrado

  Parámetro: x
  Devuelve: x^2

****************************************************************************/

double Cuadrado(double x){
	return x * x;
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
	Imprime el mensaje y lee un número real por consola. Si el número
	introducio no era un número real, vuelve a repetir la entrada hasta que 
	el usuario inroduzca uno

  Parámetros: mensaje
  Devuelve: Un número real introducido por el usuario

****************************************************************************/

double LeeReal(string mensaje){
	string numero;

	// Repita la entrada mientas numero no sea un número real

	do{

		cout << mensaje;
		cin >> numero;

	}while(!EsReal(numero));

	return stod(numero);
}

/****************************************************************************
	Imprime el mensaje y lee un número real por consola. Si el número 
	introducido no era un real o era menor o igual que la referencia repite 
	la entrada hasta que el usuario introduzca un real mayro que la referencia

  Parámetro: mensaje, referencia
  Devuelve: Un número real introducido por el usuario mayor que referencia

****************************************************************************/

double LeeRealMayorQue(string mensaje, double referencia){

	double numero;

	// Repite la entrada mientras que numero <= referencia

	do{
		numero = LeeReal(mensaje);
	}while(numero <= referencia);

	return numero;
}

/****************************************************************************/

class Gaussiana{

	private:

	// Constante estática

	static const double PI;		

	// Campos de clase

	double media;
	double desviacion;	// PRE: desviacion > 0

	public:

	/***********************************************************/
	// Métodos constructores

	// Lo inicializa en la gaussiana normalizada
	Gaussiana() :media(0), desviacion(1) {}

	// PRE: sigma > 0
	Gaussiana(double mu, double sigma) :media(mu), desviacion(sigma) {}

	/***********************************************************/
	// Devuelve el valor de la gaussiana en la abscisa x con la media y 
	// la desviación típica indicadas
		
	double Evaluar(double x){

		double parte1 = 1 / (desviacion * sqrt(2 * PI));

 		double exponente = -0.5 * Cuadrado((x - media) / desviacion);

		return parte1 * exp(exponente);

	}

	/***********************************************************/
	// Devuelve el valor de CDF(x) realizando una aproximación 
	// de la integral

	double CDF_1(double x){

		const double SALTO = 0.001;

		// Abscisa en la que comienza a realizar la sumatoria de área de 
		// rectángulos

		double abscisa_inicial = media - 3 * desviacion;

		// Realiza la sumatoria del área de varios rectángulos, aproximando 
		// el valor de la integral

		double sumatoria = 0;

		for(double xi = abscisa_inicial; xi <= x; xi += SALTO){

			sumatoria += Evaluar(xi);

		}

		// Devuelve el área de los rectángulos 
		// (sumatoria de las alturas por la base)

		return sumatoria * SALTO;

	}

	/***********************************************************/
	// Devuelve el valor de CDF(x) realizando una aproximación numérica 

	double CDF_2(double x){

		const double B0 =  0.231641900;
		const double B1 =  0.319381530;
		const double B2 = -0.356563782;
		const double B3 =  1.781477937;
		const double B4 = -1.821255978;
		const double B5 =  1.330274429;

		double z = (x - media) / desviacion;

		double t = 1.0 / (1 + B0*fabs(z));
		double t2 = t*t;
		double t3 = t2*t;
		double t4 = t3*t;
		double t5 = t4*t;

		// Calcula el valor absoluto de la gaussiana normalizada en x

		Gaussiana g_normalizada;

		double gaussiana = g_normalizada.Evaluar(fabs(x));

		double w = 1 - gaussiana * (B1*t + B2*t2 + B3*t3 + B4*t4 + B5*t5);

		// Si la abscisa era positiva devuelve w y si no, 1 - w 

		return (x >= 0)? w : 1 - w;
	}

	/***********************************************************/
	// Devuelve en formato string los datos de la clase

	string ToString(){
		return "(" + to_string(media) + ", " + to_string(desviacion);
	}

};

const double Gaussiana::PI = 6 * asin(0.5);

/****************************************************************************/

int main(){
	
	const double SALTO_ABSCISA = 0.25;

	const int RANGO_DATOS = 3;

	double media, desviacion;

	// ENTRADAS

	media = LeeReal("Media: ");

	desviacion = LeeRealMayorQue("Desviacion tipica: ", 0);

	// CÁLCULOS Y SALIDAS
	
	double min_abscisa = media - RANGO_DATOS * desviacion;
	double max_abscisa = media + RANGO_DATOS * desviacion;	

	Gaussiana g(media, desviacion);

	// Formatea la consola

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);

	cout << endl;

	for(double x = min_abscisa; x <= max_abscisa; x += SALTO_ABSCISA){

		double gaussiana = g.Evaluar(x);
		double cdf_1 = g.CDF_1(x);
		double cdf_2 = g.CDF_2(x);

		// SALIDAS

		cout << "G(" << setw(6) << setprecision(3) << x << ") = " 
			 << setw(5) << setprecision(3) << gaussiana << " ----- ";
		cout << "CDF_1 (" << setw(6) << setprecision(3) << x << ") = " 
			 << setw(5) << setprecision(3) << cdf_1 << " ----- ";
		cout << "CDF_2 (" << setw(6) << setprecision(3) << x << ") = " 
			 << setw(5) << setprecision(3) << cdf_2;			
		cout << endl;

	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2011/Gaussiana.cpp)

## 5. Lector.cpp
Cree una clase ```Lector``` para encapsular las funciones creadas en los ejercicios ```2. LecturaEnteros.cpp``` y ```2. LecturaReales.cpp``` de la [Sesión VIII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/Sesi%C3%B3n%2008.md) de prácticas.
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

class Lector{

	// Campos de clase

	private:
	string mensaje;

	// Métodos

	public:

	/**************************************************************/
	// Métodos constructores

    Lector(){}

	Lector(string msg) : mensaje(msg) {}

	/**************************************************************/	
	// Cambia el mensaje

	void SetTitulo(string msg){
		mensaje = msg;
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

	int LeeEnteroEnRango(int min, int max){
		int numero;

		do{
			numero = LeeEntero();
		}while(numero < min || numero > max);

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

	double LeeRealEnRango(double min, double max){
		double numero;

		do{
			numero = LeeReal();
		}while(numero < min || numero > max);

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

/****************************************************************************/

int main(){
	
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);

	// Ejecuta el código especificado en el enunciado:

	// Lectura de un entero arbitrario

	Lector lector_temp("Temperatura (sin decimales): "); 
	
	int temp = lector_temp.LeeEntero();
	
	cout << endl;
	cout << "Temperatura leida = " << temp << endl;
	cout << endl;


	// Lectura de enteros acotados superior e inferiormente 
	
	int hora, minuto, segundo;
	
	Lector lector_hora; 
	
	lector_hora.SetTitulo ("Introduzca hora: "); 	
	hora = lector_hora.LeeEnteroEnRango (0, 23);
	
	lector_hora.SetTitulo ("Introduzca minuto: "); 		
	minuto = lector_hora.LeeEnteroEnRango (0, 59);
	
	lector_hora.SetTitulo ("Introduzca segundo: "); 		
	segundo = lector_hora.LeeEnteroEnRango (0, 59);

	cout << endl;
	cout << "Hora: " << hora << ":" << minuto << ":" << segundo << endl;
	cout << endl << endl;
		
		
	// Lectura de un entero acotado inferiormente 
	
	int ingreso;
	
	Lector lector_ingreso("Cantidad a ingresar: "); 

	ingreso = lector_ingreso.LeeEnteroMayorOIgual (0);
	
	cout << endl;
	cout << "Valor del ingreso = " << ingreso << endl;
	cout << endl << endl;
	
	
	// Lectura de un valor real arbitrario 
	
	double temperatura;
	
	Lector lector_temperatura("Temperatura (con decimales): "); 

	temperatura = lector_temperatura.LeeReal ();
	
	cout << endl;
	cout << "Valor de la temperatura = " 
	     << setw(6) << setprecision(2) << temperatura << endl;
	cout << endl << endl;
	
	
	// Lectura de un real acotado superior e inferiormente 
	
	Lector lector_iva ("Introduzca IVA -entre 4.0 y 21.0-: "); 	 
	
	double iva = lector_iva.LeeRealEnRango (4.0, 21.0);
	
	cout << endl;
	cout << "Valor del IVA = " << setw(5) << setprecision(2) << iva << endl;
	cout << endl << endl;
	
	
	// Lectura de un real acotado superior e inferiormente 
	
	lector_iva.SetTitulo("Introduzca IVA (>=4.0): "); 	 

	iva = lector_iva.LeeRealMayorOIgual (4.0);
	
	cout << endl;
	cout << "Valor del IVA = " << setw(5) << setprecision(2) << iva << endl;
	cout << endl << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2011/Lector.cpp)

# Ejercicios Opcionales
## 1. CoordenadasGPS.cpp
Se quiere construir la clase ```CoordenadasGPS``` para representar las coordenadas geográficas de una posición terrestre, dada por tres datos reales, a saber, su longitud, latitud y altura. La clase debe proporcionar métodos para asignar y recuperar los datos de latitud y longitud.  
  
Se pide hacerlo de la siguiente forma:
- Sólo se podrán asignar los datos de longitud y latitud en grados. Los métodos correspondientes transformarán esos grados en radianes y los asignarán a los datos miembro. La altura vendrá en metros. Debe comprobar que los grados sean correctos, es decir, los grados de latitud deben estar en el intervalo $[-90, 90] y los de longitud en $[-180, 180). La altura debe estar entre -423 (Valle del Jordán) y 8848 (Everest).
- Para consultar los datos de longitud y latitud, se definirán métodos específicos para cada caso: ```GetLatitudGrados()```, ```GetLatitudRadianes()```, ...  
  
Escriba también un método ```ToString()```.

## 2. Instante.cpp
Defina la clase Instante para representar un instante de tiempo dentro de un día.  
Por lo tanto, la clase debe representar un número de horas, minutos y segundos.  
Añada métodos para:
- Obtener el número de segundos y minutos transcurridos desde las ```0h, 0min, 0seg```.  
  Por ejmplo, si el instante es ```1h, 2min, 1seg```, los minutos transcurridos son ```62``` y los segundos ```3721```.
- Establecer el instante a partir del número de segundos transcurridos. Por ejemplo, si se establece a ```3721```, el instante debe contener ```1h, 2min, 1seg```.
- No olivde el método ```ToString``` con el siguiente formato (suponemos que el instante es de ```1h, 2min, 1seg```): ```(1 h : 2 m : 1 s)```.  
  
Cree un programa que lea un número de horas, minutos y segundos iniciales y finales. El programa creará los objetos ```instante_inial``` e ```instante_final``` y calculará el número de segundos que hay de diferencia entre ambos instantes. A continuación, creará un objeto ```instante_diferencia``` correspondiente a la cantidad de horas, minutos y segundos de diferencia entre el instante final y el inicial e imprimirá en pantalla el valor de ```instante_diferencia```. El programa también imprimirá, por separado, el total de segundos y minutos enteros que hay en ```instante_diferencia```.

## 3. DepositoBancario.cpp
Cree una clase que, dados un capital y unos intereses, desarrolle métodos para:
- Calcular el capital que se obtendrá al cabo de un número de años.
- Calcular el número de años que deben pasar hasta doblar la cantidad inicial.  
  
Recordamos que, notados por $C_i$ el capital del año $i$ y por $I$ a los intereses, la forma de obtener el capital del siguiente año viene dada por:
$$C_{i+1} = C_i + C_i \cdot \dfrac{I}{100}$$

## 4. Login.cpp
Se está diseñando un sistema web que recolecta datos personales de un usuario y debe sugerirle un nombre de usuario (login). Dicho login estará basado en el nombre y los apellidos; en concreto estará formado por los ```n``` primeros caracteres de cada nombre y apellido (en minúsculas, unidos y sin espacios en blanco).  
Por ejemplo si el nombre es ```Antonio Francisco Molina Ortega``` y ```n = 2```.  
El nombre de usuario sugerido será ```anfrmoor```.  
  
Debe tener en cuenta que el número de palabras que forman el nombre y los apellidos puede ser cualquiera. Además, si ```n``` es mayor que alguna de las palabras que aparecen en el nombre, se incluirá la palabra completa.  
Por ejemplo, si el nombre es ```Ana Campos de la Blanca``` y ```n = 4```:  
La sugerencia será ```anacampdelablan```.  
  
Implemente la clase ```Login``` que tendrá como único dato miembro el número máximo de caracteres que nos interesan de cada palabra del nombre. Hay que definir el método ```Codifica``` que recibirá una cadena de caracteres (tipo ```string```) formada por el nombre y apellidos (separados por uno o más espacios en blanco) y devuelva otra cadena con la sugerencia de login.

## 5. ManipuladorString.cpp
Escriba la clase ```ManipuladorString```. Esta clase se encargará de modificar un dato ```string``` y realizar cálculos complejos sobre él con funciones no ofertadas por la clase ```string```. Proponemos que trabaje sobre el siguiente esquema:  
```cpp
class ManipuladorString{
    string cadena;
    
public:
    ManipuladorString();
    ManipuladorString(string cad);
    
    void setCadena(string cad);
    string getCadena();
    
    void eliminaPrimerosSeparadores(); // quita espacios en blanco al inicio
    void eliminaUltimosSeparadores();  // quita espacios en blanco al final
    void eliminaPrimerosYUltimosSeparadores();
    void convierteMayusculas();
    void convierteMinusculas();
};
```
