# Fundamentos de Programación. Sesión IX de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión IX de prácticas.

En esta sesión de prácticas se introducen los **structs** y los **arrays**, por lo que los siguientes ejercicios estarán orientados a su uso. Los dos primeros ejercicios están orientados a los **structs** y los 5 siguientes a **arrays**.  
En ningún momento quedará permitido el paso de arrays a funciones, esto se aprenderá en la asignatura de _Metodología de la Programación_.
Por tanto, se perdonará que los ejercicios de arrays no estén correctamente modularizados.

## 1. Rectangulo.cpp
En este programa, deberá crear varios ```structs```:  
  
```Punto2D```  
```struct``` que representa un punto en el plano bidimensional.  
  
```Circunferencia```  
```struct``` que representa una circunferencia en el plano bidimensional.  
  
```Rectangulo```  
```struct``` que representa a un rectángulo en el plano bidimensional.  
Un rectángulo viene determinado por el vértice superior izquierdo y por el vértice inferior derecho.  
  
Desarrolle un programa que pida al usuario un rectángulo y calcule la circunferencia centrada en el punto de corte de las diagonales del rectángulo de forma que su superficie sea la menor entre todas las circunferencias de mayor área que la del rectángulo.  
  
Para el cálculo de la circunferencia, comience con una circunferencia de radio ```0.5``` y vaya incrementando su valor en ```0.25``` hasta hallar la primera circunferencia de área mayor que el rectángulo.
```cpp
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
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/Rectangulo.cpp)

## 2. Carrera.cpp
Recordando el enunciado del ejercicio ```4. Carrera.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
Para controlar los tiempos que emplean los corredores de una carrera popular se desea disponer de un programa muy sencillo que se irá ampliando en sucesivas versiones. En esta primera versión el programa empezará pidiendo la hora de inicio de la carrera (hora, minuto y segundo) y la distancia.  
  
Después, para cada corredor que llega a meta (por orden de llegada) se pide el número de dorsal y la hora de llegada (hora, minuto y segundo). Tras leer estos datos, el programa mostrará el tiempo que ha empleado en completar la carrera (horas, minutos y segundos) y su ritmo (en km/h y en minutos/km).  
  
El programa finalizará cuando al solicitar el número de dorsal se introduzca el dorsal 0.

En este programa, deberá crear un ```struct```:  
  
```Instante```  
Que representa una tripleta ```(hora, minuto, segundo)```.  
  
Se pide reescribir la solución al problema anterior usando ahora esta nueva estructura.
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

/****************************************************************************/
// Constantes

// Límites de valores que consideramos válidos

const int MAX_HORA = 24, MIN_HORA = 0;
const int MAX_MINS = 60, MIN_MINS = 0;
const int MAX_SEG = 60, MIN_SEG = 0;

// Conversión entre unidades

const int DIAS_A_HORAS = 24, HORAS_A_MINS = 60, MINS_A_SEGS = 60;

/****************************************************************************/
// Definiciones de structs

// Hora del día en un instante

struct Instante{
	int hora;
	int minuto;
	int segundo;
};

// Tiempo que transcurre entre dos instantes	

struct Tiempo{
	int horas;
	int minutos;
	int segundos;
};

/****************************************************************************
	Pasa la hora en un instante a los segundos que han pasado desde el
	instante inicial del día (00:00:00)

  Parámetros: instante
  Devuelve: El tiempo en segundos que transcurre desde 00:00:00 hasta el 
	instante

	*Nota: Necesita las ctes globales HORAS_MINS y MINS_SEGS

****************************************************************************/

int InstanteASegundos(Instante instante){
	return instante.hora * HORAS_A_MINS * MINS_A_SEGS 
		+ instante.minuto * MINS_A_SEGS + instante.segundo;
}

/****************************************************************************
	Calcula el tiempo que transcurre entre dos instantes

  Parámetros: inst1 (el primer instante), inst2
  Devuelve: El tiempo que transcurre entre instante1 e instante2

****************************************************************************/

Tiempo TiempoEntre(Instante inst1, Instante inst2){
	int segundos1 = InstanteASegundos(inst1);
	int segundos2 = InstanteASegundos(inst2);

	Tiempo tiempo_transcurrido;

	int segundos_transcurridos;

	// Si el primer instante sucede después o al mismo tiempo que el segundo
	// instante, consideramos que ha pasado un día

	if(segundos1 >= segundos2)

		// A los segundos de un día le restamos los segundos que transcurren
		// entre inst1 e inst2

		segundos_transcurridos = MINS_A_SEGS * HORAS_A_MINS * DIAS_A_HORAS 
								- (segundos1 - segundos2);

	else
		segundos_transcurridos = segundos2 - segundos1;

	// Calculamos los minutos y las horas exactas a las que equivalen
	// esos segundos

	int minutos_transcurridos = segundos_transcurridos / MINS_A_SEGS;

	int horas_transcurridas = minutos_transcurridos / HORAS_A_MINS;

	// Los almacenamos de forma correspondiente en tiempo_transcurrido

	tiempo_transcurrido.segundos = segundos_transcurridos % MINS_A_SEGS;

	tiempo_transcurrido.minutos = minutos_transcurridos % HORAS_A_MINS;

	tiempo_transcurrido.horas = horas_transcurridas;

	return tiempo_transcurrido;
}

/****************************************************************************
	Calcula la velocidad media de un corredor en km / h.

  Parámetros: km (distancia en km de la distancia),
			  tiempo (tiempo que tardó en completarlos)
  Devuelve: la velocidad media del corredor en km / h
  PRE: tiempo != 0 (que haya al menos un campo suyo distinto de 0)

****************************************************************************/

double Velocidad_km_h(double km, Tiempo tiempo){

	// Calcula las horas que hay en tiempo

	double horas = tiempo.horas + ((double)tiempo.minutos) / HORAS_A_MINS 
					+ ((double) tiempo.segundos) / (HORAS_A_MINS * MINS_A_SEGS);

	return km / horas;
}

/****************************************************************************
	Calcula el ritmo medio de un corredor en min/km

  Parámetros: km (distancia en km de la distancia),
			  tiempo (tiempo que tardó en completarlos)
  Devuelve: El ritmo medio del corredor en min / km
  PRE: km != 0

****************************************************************************/

double Ritmo_min_km(double km, Tiempo tiempo){
	
	// Calcula los minutos que hay en tiempo

	double minutos = tiempo.horas * HORAS_A_MINS + tiempo.minutos 
					+ ((double) tiempo.segundos) / MINS_A_SEGS;

	return minutos / km;
}

/****************************************************************************
	Devuelve en un texto la información de un dato de tipo Tiempo

  Parámetros: tiempo
  Devuelve: la información de los campos de tiempo en forma textual

****************************************************************************/

string TiempoToString(Tiempo tiempo){
	return to_string(tiempo.horas) + " horas, " + to_string(tiempo.minutos) 
			+ " minutos y " + to_string(tiempo.segundos) + " segundos";
}

/****************************************************************************
	Solicita al usuario la hora del día en un instante, devolviendo lo
	introducido por el usuario en un tipo de dato Instante.
	Antes de solicitar la hora, imprime el mensaje correspondiente

  Parámetros: mensaje (mensaje que imprime antes de solicitar datos)
  Devuelve: La hroa del día en el instante especificado por el usuario

	*Nota: necesita las ctes globales MAX_HORA, MIN_HORA, MAX_MIN, MIN_MIN,
		MAX_SEG, MIN_SEG.

****************************************************************************/

Instante LeerHora(string mensaje){
	
	// Imprime el mensaje

	cout << mensaje << endl;	

	int hora, minuto, segundo;

	// Lee las hora, el minuto y el segundo, obligando a que esté entre
	// el rengo de valores válidos

	do{

		cout << "\tHora: ";
		cin >> hora;

	}while(hora < MIN_HORA || hora > MAX_HORA);

	do{

		cout << "\tMinuto: ";
		cin >> minuto;

	}while(minuto < MIN_MINS || minuto > MAX_MINS);

	do{

		cout << "\tSegundo: ";
		cin >> segundo;

	}while(segundo < MIN_SEG || segundo > MAX_SEG);

	// Crea un objeto de tipo Instante y lo devuelve

	Instante inst;

	if(hora == MIN_HORA && minuto == MIN_MINS && segundo == MIN_SEG)
		inst = {24, 0, 0};

	else
		inst = {hora, minuto, segundo};

	return inst;
}

/****************************************************************************/

int main(){
	
	// La distancia mínima de la carrera es de 100m
	const double DISTANCIA_MIN = 0.1;	//(km)
	const int DORSAL_MIN = 0;

	double distancia_carrera;
	Instante comienzo_carrera;

	// ENTRADAS

	// Datos de la carrera
	
	do{

		cout << "Distancia (mayor o igual que " << DISTANCIA_MIN << " km) : ";
		cin >> distancia_carrera;

	}while(distancia_carrera < DISTANCIA_MIN);

	comienzo_carrera = LeerHora("Hora de inicio de la carrera: ");

	// Se comienzan a solicitar corredores

	cout << endl;
	cout << "(Para terminar, introduzca el dorsal " << DORSAL_MIN << ")" << endl;
	cout << endl;

	int dorsal;

	// Se solicita el dorsal del primer corredor

	do{
	
		cout << "Dorsal (mayor o igual que " << DORSAL_MIN << "): ";
		cin >> dorsal;

	}while(dorsal < DORSAL_MIN);

	Instante tiempo_corredor;

	// Se formatea la consola

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);

	while(dorsal != DORSAL_MIN){

		// Se solicita el tiempo del corredor

		tiempo_corredor = LeerHora("Completa la carrera en: ");

		// Se calcula el tiempo que ha tardado, su velocidad y su ritmo

		Tiempo tiempo = TiempoEntre(comienzo_carrera, tiempo_corredor);

		double velocidad = Velocidad_km_h(distancia_carrera, tiempo);

		double ritmo = Ritmo_min_km(distancia_carrera, tiempo);

		// Se imprime en consola la información de los resultados del corredor

		cout << endl;

		cout << "El corredor " << dorsal << " ha tardado " 
			 << TiempoToString(tiempo) << " en completar la carrera." << endl;
		cout << "Ha llevado una velocidad media de " << setw(6) 
			 << setprecision(3) << velocidad << " km/h." << endl;
		cout << "Y un ritmo medio de " << setw(6) << setprecision(3) << ritmo 
			 << " min/km." << endl;

		cout << endl;

		// Se solicita el dorsal del siguiente corredor
	
		do{
		
			cout << "Dorsal (mayor o igual que " << DORSAL_MIN << "): ";
			cin >> dorsal;
	
		}while(dorsal < DORSAL_MIN);
	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/Carrera.cpp)

## 3. MediaCompararArrays.cpp
Se pide crear un programa que contenga dos arrays de tipo ```int``` con ```TOPE``` casillas.  
Se rellenará cada array de la siguiente manera: se pedirá por teclado una serie indeterminada de números hasta que se introduzca la palabra ```FIN```.  
  
En primer lugar, el programa mostrará el valor medio de los valores introducidos. Después, indicará si los dos arrays contienen los mismos valores (y en el mismo orden) o si no.
```cpp
#include <iostream>

using namespace std;

int main(){
	
	// Número máximo de casillas de array1 y array2
	const int TOPE = 100;

	const string TERMINADOR = "FIN";

	// Constantes para mensajes repetitivos

	const string MSG_TERMINADOR = "(Cuando termine, introduzca \"" 
								+ TERMINADOR + "\")";
	const string MSG_VALOR = "Valor: ";
	const string MSG_TOPE = "Se alcanzo el tope (" + to_string(TOPE) 
							+ " casillas).";

	int array1[TOPE], array2[TOPE];

	// Números de posiciones válidas en cada array
	int pos_validas1 = 0, pos_validas2 = 0;

	// ENTRADAS **********************************************************

	// array 1 --------------------------------------------------------

	string entrada1;

	cout << "Introduzca los valores (enteros) del array 1: " << endl;
	cout << MSG_TERMINADOR << endl;
	cout << endl;

	cout << MSG_VALOR;
	cin >> entrada1;

	// Mientras que entrada no sea "FIN" y haya poosiciones en el array

	while(entrada1 != TERMINADOR && pos_validas1 < TOPE - 1){

		// Se almacena el valor y se aumenta el número de posiciones válidas		

		array1[pos_validas1] = stoi(entrada1);

		pos_validas1++;

		// Solicita el siguiente valor

		cout << MSG_VALOR;
		cin >> entrada1;
	}

	// Si se llena el array, guarda el último valor si no es TERMINADOR 
	// e imprime MSG_TOPE

	if(pos_validas1 == TOPE - 1 && entrada1 != TERMINADOR){
		array1[pos_validas1] = stoi(entrada1);
		pos_validas1++;

		cout << endl << MSG_TOPE << endl;
	}

	// array 2 --------------------------------------------------------

	string entrada2;

	cout << endl;
	cout << "Introduzca los valores (enteros) del array 2: " << endl;
	cout << MSG_TERMINADOR << endl;
	cout << endl;

	cout << MSG_VALOR;
	cin >> entrada2;

	// Mientras que entrada no sea "FIN" y haya poosiciones en el array

	while(entrada2 != TERMINADOR && pos_validas2 < TOPE - 1){
	
		// Se almacena el valor y se aumenta el número de posiciones válidas		

		array2[pos_validas2] = stoi(entrada2);

		pos_validas2++;

		// Solicita el siguiente valor

		cout << MSG_VALOR;
		cin >> entrada2;
	}

	// Si se llena el array, guarda el último valor e imprime MSG_TOPE

	if(pos_validas2 == TOPE - 1 && entrada2 != TERMINADOR){
		array2[pos_validas2] = stoi(entrada2);	
		pos_validas2++;

		cout << endl << MSG_TOPE << endl;
	}

	// CÁLCULOS ***********************************************************

	// Se calcula el valor medio de los valores de cada array

	// array 1 --------------------------------------------------------

	double sumatoria_array1 = 0;

	// Recorre todas las posiciones válidas de array1
	for(int i = 0; i < pos_validas1; i++){
		sumatoria_array1 += array1[i];
	}

	// Se divide la suma de todos los elementos entre el número de elementos

	double valor_medio1;

	// Si no tenía elementos, consideramos que la media es 0
	if(pos_validas1 == 0)
		valor_medio1 = 0;

	else
		valor_medio1 = sumatoria_array1 / pos_validas1;

	// array 2 --------------------------------------------------------

	double sumatoria_array2 = 0;

	// Recorre todas las posiciones válidas de array2
	for(int i = 0; i < pos_validas2; i++){
		sumatoria_array2 += array2[i];
	}

	// Se divide la suma de todos los elementos entre el número de elementos

	double valor_medio2;

	// Si no tenía elementos, se considera que la media es 0
	if(pos_validas2 == 0)	
		valor_medio2 = 0;

	else
		valor_medio2 = sumatoria_array2 / pos_validas2;

	// ------------------------------------------------------------------
	// Se comprueba si los dos arrays contienen los mismos valores en el 
	// mismo orden

	bool diferentes;

	int i = 0;

	// Si contienen diferente número de elementos válidos o si tienen 
    // distinto valor medio ya sabemos que son arrays diferentes

	if(pos_validas1 != pos_validas2 || valor_medio1 != valor_medio2)
		diferentes = true;

	else{

		diferentes = false;

		// Mientras que haya elementos válidos y que no se haya detectado
		// que sean diferentes, se recorre todo el array

		while(i < pos_validas1 && !diferentes){
	
			// Si en la misma posición un elemento de un array es distinto de 
			// un elemento de otro, son diferentes

			if(array1[i] != array2[i])
				diferentes = true;	

			else
				i++;
		}

	}

	// SALIDAS ************************************************************

	cout << endl;

	cout << "El valor medio del array1 es: " << valor_medio1 << endl;

	cout << endl;

	cout << "El valor medio del array2 es: " << valor_medio2 << endl;

	cout << endl;

	if(diferentes)
		cout << "El array1 y el array2 son diferentes." << endl;
	else
		cout << "Los arrays son iguales." << endl;

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/MediaCompararArrays.cpp)

## 4. Inflacion.cpp
En la siguiente tabla mostramos el IPC de España entre 1990 y 2021.  
  
| Año  | IPC   | Año  | IPC  | Año  | IPC  | Año  | IPC  |  
|------|-------|------|------|------|------|------|------|  
| 2021 | 6.50% | 2013 | 0.3% | 2005 | 3.7% | 1997 | 2.0% |  
| 2020 | -0.5% | 2012 | 2.9% | 2004 | 3.2% | 1996 | 3.2% |  
| 2019 | 0.80% | 2011 | 2.4% | 2003 | 2.6% | 1995 | 4.3% |  
| 2018 | 1.20% | 2010 | 3.0% | 2002 | 4.0% | 1994 | 4.3% |  
| 2017 | 1.10% | 2009 | 0.8% | 2001 | 2.7% | 1993 | 4.9% |  
| 2016 | 1.60% | 2008 | 1.4% | 2000 | 4.0% | 1992 | 5.3% |  
| 2015 | 0.00% | 2007 | 4.2% | 1999 | 2.9% | 1991 | 5.5% |  
| 2014 | -1.0% | 2006 | 2.7% | 1998 | 1.4% | 1990 | 6.5% |  
  
Queremos conocer el valor actualizado según las variaciones del IPC que debería tener un bien cualquiera conociendo su valor monetario en un año concreto. Por ejemplo, en 2001 una barra de pan costaba 0.30€ y una entrada de cine 3,90€. En 2021 la barra de pan costaba alrededor de 0.70€ y la entrada de cine 7,78€. ¿El incremento de precio es razonable?  
  
Escriba un programa que solicite un valor monetario y el año de referencia de ese valor. A continuación, solicite un otro año (puede ser anterior al primero). El programa debe mostrar el valor monetario dado actualizado según el IPC en el año indicado.  Repetir hasta que se introduzca un valor monetario negativo. 
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

int main(){

	const int PRECIO_MINIMO = 0;

	const int ANIO_INICIAL = 1990;
	const int ANIO_FINAL = 2021;
	const int NUM_ANIOS = ANIO_FINAL - ANIO_INICIAL + 1;

	// IPC de España entre ANIO_INICIAL y ANIO_FINAL

	const double IPC [NUM_ANIOS] = {6.5, 5.5, 5.3, 4.9, 4.3, 4.3, 3.2, 2, 1.4, 
						2.9, 4, 2.7, 4, 2.6, 3.2, 3.7, 2.7, 4.2, 1.4, 0.8, 3, 
						2.4, 2.9, 0.3, -1, 0, 1.6, 1.1, 1.2, 0.8, -0.5, 6.5};

	double precio;
	int anio_precio, anio_final;

	// Formateo de consola

	cout.setf(ios::fixed);

	cout << "Introduzca un precio menor o igual que " << PRECIO_MINIMO 
		 << " para terminar." << endl << endl;

	// Solicita el primer precio

	cout << "Precio: ";
	cin >> precio;

	while(precio > PRECIO_MINIMO){

		// Solicita los años de compra y de consulta

		// Consideramos ANIO_INICIAL - 1 un año válido porque conocemos
		// el IPC de ANIO_INICIAL

		do{
	
			cout << "Anio de compra del producto [" << ANIO_INICIAL - 1 
				 << ", " << ANIO_FINAL << "]: ";
			cin >> anio_precio;

		}while(anio_precio < ANIO_INICIAL - 1 || anio_precio > ANIO_FINAL);
	
		do{
	
			cout << "Anio de consulta [" << ANIO_INICIAL - 1 
				 << ", " << ANIO_FINAL << "]: ";
			cin >> anio_final;
	
		}while(anio_final < ANIO_INICIAL - 1 || anio_final > ANIO_FINAL);
	
		// CÁLCULOS
	
		// Se inicializa el precio final en precio inicial
		double precio_final = precio;	
	
		if(anio_precio <= anio_final){
	
			// Si el anño final es mayor avanzamos años

			for(int i = anio_precio + 1; i <= anio_final; i++){
					
				precio_final += precio_final * IPC[i - ANIO_INICIAL] / 100;
	
			}

		}else{

			// Si no, retrocedemos años

			for(int i = anio_precio - 1; i >= anio_final; i--){
	
				precio_final -= precio_final * IPC[i - ANIO_INICIAL] / 100;
	
			}

		}
	
		// SALIDAS

		cout << endl;

		cout << "Precio en " << anio_final << " : " << setw(9) 
			 << setprecision(6) << precio_final << endl;
	
		cout << endl;

		// Solicitamos el siguiente precio

		cout << "Precio: ";
		cin >> precio;
	}

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/Inflacion.cpp)

## 5. SueldoFuncionarios.cpp
Considerando la tabla del IPC del ejercicio ```4. Inflacion.cpp``` realizado anteriormente:  
  
| Año  | IPC   | Año  | IPC  | Año  | IPC  | Año  | IPC  |  
|------|-------|------|------|------|------|------|------|  
| 2021 | 6.50% | 2013 | 0.3% | 2005 | 3.7% | 1997 | 2.0% |  
| 2020 | -0.5% | 2012 | 2.9% | 2004 | 3.2% | 1996 | 3.2% |  
| 2019 | 0.80% | 2011 | 2.4% | 2003 | 2.6% | 1995 | 4.3% |  
| 2018 | 1.20% | 2010 | 3.0% | 2002 | 4.0% | 1994 | 4.3% |  
| 2017 | 1.10% | 2009 | 0.8% | 2001 | 2.7% | 1993 | 4.9% |  
| 2016 | 1.60% | 2008 | 1.4% | 2000 | 4.0% | 1992 | 5.3% |  
| 2015 | 0.00% | 2007 | 4.2% | 1999 | 2.9% | 1991 | 5.5% |  
| 2014 | -1.0% | 2006 | 2.7% | 1998 | 1.4% | 1990 | 6.5% |  
  
Y la tabla de variación de los sueldos de los funcionarios en España desde 2010 hasta 2021:  
  
| Año  | Subida | Año  | Subida |  
|------|--------|------|--------|  
| 2021 | 0.90%  | 2015 | 0.000% |  
| 2020 | 2.00%  | 2014 | 0.000% |  
| 2019 | 2.50%  | 2013 | 0.000% |  
| 2018 | 1.75%  | 2012 | 0.000% |  
| 2017 | 1.00%  | 2011 | 0.000% |  
| 2016 | 1.00%  | 2010 | -5.00% | 
  
El programa leerá el valor de un sueldo y el año de referencia de ese sueldo. A continuación, leerá el un segundo año (debe ser posterior). Calcule el salario que le correspondería en ese segundo año si se aplicaran las variaciones del IPC y el salario que le corresponde de acuerdo a las subidas reales aplicadas. Muestre ambos valores, su diferencia y el porcentaje de ganancia/pérdida respecto al salario calculado con las variaciones del IPC.  Repetir hasta que se introduzca un valor monetario negativo.
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/****************************************************************************/
// Constantes

// Registros de subida del sueldo de los funcionarios y del IPC de España
// entre ANIO_INICIAL y ANIO_FINAL

const int ANIO_INICIAL = 2010, ANIO_FINAL = 2021;
const int NUM_ANIOS = ANIO_FINAL - ANIO_INICIAL + 1;

const double PORC_SUBIDA[NUM_ANIOS] = {-5, 0, 0, 0, 0, 0, 1, 1, 1.75, 2.5, 2,
																		 0.9};
const double IPC [NUM_ANIOS] = {3, 2.4, 2.9, 0.3, -1, 0, 1.6, 1.1, 1.2, 0.8, 
																-0.5, 6.5};

/****************************************************************************
	Calcula el precio introducido en el año final teniendo en cuenta el
	valor del IPC en España

  Parámetros: precio, anio_inicial, anio_final
  Devuelve: El valor de precio en el anio_final según las variaciones del IPC
  PRE: ANIO_INICIAL <= anio_inicial, anio_final <= ANIO_FINAL

	*Nota: necesita el valor de las ctes ANIO_INICIAL, ANIO_FINAL, IPC

****************************************************************************/

double CalculaPrecio_IPC(double precio, int anio_inicial, int anio_final){
	double precio_final = precio;	
	
	// Aumenta el precio según el IPC

	for(int i = anio_inicial + 1; i <= anio_final; i++){
				
		precio_final += precio_final * IPC[i - ANIO_INICIAL] / 100;

	}

	return precio_final;
}

/****************************************************************************
	Calcula el salario introducido de un funcionario en el año final
	teniendo en cuenta las variaciones de los sueldos de los funcionarios
	en España

  Parámetros: salario, anio_inicial, anio_final
  Devuelve: El valor del salario en el anio_final según las variaciones de los
	sueldos de los funcionarios
  PRE: ANIO_INICIAL <= anio_inicial, anio_final <= ANIO_FINAL

	*Nota: Necesita el valor de las ctes ANIO_INICIAL, ANIO_FINAL, PORC_SUBIDA

****************************************************************************/

double CalculaSalario_Funcionario(double salario, int anio_inicial, 
															int anio_final){
	double salario_final = salario;	
	
	// Aumenta el salario según el porcentaje de subida

	for(int i = anio_inicial + 1; i <= anio_final; i++){
				
		salario_final += salario_final * PORC_SUBIDA[i - ANIO_INICIAL] / 100;

	}

	return salario_final;
}

/****************************************************************************/

int main(){

	const int MIN_SALARIO = 0;

	double sueldo;
	int anio;
	int anio_posterior;

	// Se solicita el primer sueldo

	cout << "Para terminar, introduzca un sueldo menor o igual que " << MIN_SALARIO 
		 << endl << endl;

	cout << "Sueldo: ";
	cin >> sueldo;

	// Se formatea la consola

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);

	while(sueldo > MIN_SALARIO){

		// ENTRADAS

		do{
		
			cout << "Anio (entre " << ANIO_INICIAL << " y " << ANIO_FINAL 
				 << "): ";
			cin >> anio;
		
		}while(anio < ANIO_INICIAL || anio > ANIO_FINAL);
		
		do{
		
			cout << "Anio a consultar (entre " << anio << " y " 
				 << ANIO_FINAL << "): ";
			cin >> anio_posterior;
		
		}while(anio_posterior < anio || anio_posterior > ANIO_FINAL);
		
		// CÁLCULOS
		
		double salario_ipc = CalculaPrecio_IPC(sueldo, anio, anio_posterior);
		
		double salario_real = 
					CalculaSalario_Funcionario(sueldo, anio, anio_posterior);
		
		double diferencia = abs(salario_ipc - salario_real);

		double porc_ganancia_perdida = salario_real * 100 / salario_ipc;
		
		// SALIDAS
		
		cout << endl;

		cout << setw(7) << setprecision(2);
		
		cout << "Salario teorico (segun IPC): " << salario_ipc << "e" 
			 << endl;

		cout << "Salario real: " 
			 << salario_real << "e" << endl;

		cout << "Diferencia: " << diferencia << "e" 
			 << endl;
		
		cout << setw(9) << setprecision(5) <<  porc_ganancia_perdida 
			 << " % del salario teorico." << endl;

		cout << endl;

		// Se solicita el siguiente sueldo

		cout << "Sueldo: ";
		cin >> sueldo;

	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/SueldoFuncionarios.cpp)

## 6. Erastotenes.cpp
Recordando el ejercicio ```1. DescomposicionFactoresPrimos.cpp``` de la [Sesión VII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/Sesi%C3%B3n%2007.md) de prácticas:  
  
Escriba un programa que lea un número entero positivo y muestre su descomposición en factores primos.  
Hágalo de forma que se calcule y muestre el resultado de dos maneras:  
1. La primera (y más sencilla) consiste en enumerar todos los primos de la descomposición (en el caso de que un primo intervenga más de una vez, se mostrará tantas veces como sea preciso).  
Por ejemplo:  
```360 = 2 * 2 * 2 * 3 * 3 * 5```  
```121 = 11 * 11```  
```11 = 11```  
  
2. La segunda consiste en expresar el resultado como el producto de potencias (en caso de que un primo intervenga más de una vez, se mostrará una potencia cuya base sea el valor del primo y el exponente será el número de veces que se repite). Evite elevar un número a 1.  
Por ejemplo:  
```360 = 2^3 * 3^2 * 5```  
```121 = 11^2```  
```11 = 11```  
  
En esta ocasión, deberá realizar un programa que lea un número indeterminado de enteros positivos (finalice cuando se introduzca un 0) y expresse cada uno de ellos en base al producto de sus factores primos mediante el formato 2 descrito anteriormente.  
  
Para ello, deberá previamente calcular y guardar en un array los números primos antes de leer ninguno (los primeros ```N``` números primos, úsese la constante deseada). Para ello, se usará el algorimo de la _Criba de Erastótenes_. 
  
Recomendamos la creación de un struct:  
```cpp
struct Pareja {
    int primo;
    int potencia;
};
```  
  
De forma que cada descomposición se guarde en un array antes de la salida.  
  
El algorimo de la Criba de Erastótenes es el siguiente:  
El procedimiento consiste en escribir todos los números naturales entre 2 y ```N``` (úsese ```N = 5000```) y tachar los número que no sean primos de la siguiente forma:  
- El primero (el 2) se considera primo y se tachan todos sus múltiplos.
- Se busca el siguiente número no tachado, ```p```, que se considera primo y se tachan todos sus múltiplos.
- Repetir el proceso hasta que el cuadrado de ```p``` (el siguiente número no tachado que se considera primo) es mayor que ```N```.
```cpp
#include <iostream>

using namespace std;

// Definición de structs

struct Pareja{
	int primo;
	int potencia;
};

/****************************************************************************
	Imprime un mensaje y lee un número entero.
	Mientras que el número introducido no esté entre los valores mínimo y
	máximo, vuelve a solicitar el número.

  Parámetros: mensaje, el mensaje que se muestra al solicitar el número
			  minimo, maximo, los números que definen el rango
  Devuelve: un entero positivo

****************************************************************************/

int LeerEnteroEnRango(string mensaje, int minimo, int maximo){

	int entrada;

	// Se repite mientras entrada no esté en [minimo, maximo]

	do{

		cout << mensaje;
		cin >> entrada;

	}while(entrada < minimo || entrada > maximo);

	return entrada;
}

/****************************************************************************/

int main(){
	
	//---------------------------------------------------------------------
	// Cálculo de todos los números primos entre PRIMER_PRIMO y MAX_PRIMO

	const int MAX_PRIMO = 5000;
	const int PRIMER_PRIMO = 2;

	// Longitud del array que almacena los primos
	const int MAX_DATOS = MAX_PRIMO / 2;

	// Número de valores entre PRIMER_PRIMO y MAX_PRIMO
	const int LONG_ARRAYS = MAX_PRIMO - PRIMER_PRIMO + 1;

	// Donde almacenamos todos los números entre PRIMER_PRIMO Y MAX_PRIMO

	int numeros[LONG_ARRAYS];
	bool es_primo[LONG_ARRAYS];

	int primos[MAX_DATOS];
	int pos_validas_primos = 0;

	// Rellena numeros con todos los números entre PRIMER_PRIMO y MAX_PRIMO

	int numero = PRIMER_PRIMO;

	for(int i = 0; i < LONG_ARRAYS; i++){
	
		numeros[i] = numero;
		numero++;

		// Se presupone que un número es primo hasta que no se "tache"
		es_primo[i] = true;
	}

	int primo = PRIMER_PRIMO;

	int posicion = 0;

	// Mientras que primo^2 no sea mayor que MAX_PRIMO

	while(primo * primo <= MAX_PRIMO){

		// Comprueba todos los números a partir de primo (está en posicion)

		for(int i = posicion + 1; i < LONG_ARRAYS; i++){

			// Si numeros[i] es múltiplo de primo
			if(numeros[i] % primo == 0)
				es_primo[i] = false;	// No es un número primo (se "tacha")		

		}

		// Busca el siguiente número primo

		posicion++;

		while(!es_primo[posicion])
			posicion++;

		primo = numeros[posicion];
	}

	// Guarda todos los números primos en el array primos

	for(int i = 0; i < LONG_ARRAYS; i++){
		if(es_primo[i]){
			primos[pos_validas_primos] = numeros[i];
			pos_validas_primos++;
		}
	}

	// ---------------------------------------------------------------------
	// Entradas y cálculos

	const int TERMINADOR = 0;
	const string MSG = "Numero (entre " + to_string(TERMINADOR+1) + " y " 
						+ to_string(MAX_PRIMO) + "): "; 

	const int CASILLAS_DESCOMPOSICION = 50;

	const char ELEVADO = '^';
	const string SEPARADOR = " * ";

	cout << "Para finalizar, introduzca " << TERMINADOR << endl << endl;

	int entrada = LeerEnteroEnRango(MSG, TERMINADOR, MAX_PRIMO);

	while(entrada != TERMINADOR){

		// Se trabaja con una copia de entrada

		int numero = entrada;

		// Las inicializamos todas en 0

		Pareja descomposicion[CASILLAS_DESCOMPOSICION];
		
		int utilizados_descomposicion = 0;

		int i = 0;

		if(numero == 1){

			descomposicion[0].primo = 1;
			utilizados_descomposicion++;

		}else{

			// Mientas que haya primos o mientras que numero sea distinto de 1

			while(i < pos_validas_primos && numero != 1){
				int primo = primos[i];	// Se coge un primo del array
				int contador = 0;
	
				// Se cuentan las veces que el primo es divisor de numero
	
				while(numero % primo == 0){
					numero /= primo;
					contador++;
				}
		
				// Si lo divide al menos una vez, se almacena qué primo
				// era y cuantas veces lo dividía
	
				if(contador != 0){
					descomposicion[utilizados_descomposicion].primo = primo;
					descomposicion[utilizados_descomposicion].potencia = 
																	contador;
					
					utilizados_descomposicion++;
				}
				
				i++;	// Se comprueba el siguiente primo
			}
		}

		// Imprime la salida ----------------------------------------

		cout << entrada << " = ";

		// Recorre todos los valores útiles del array descomposicion

		for(int i = 0; i < utilizados_descomposicion - 1; i++){

			// Imprime el primo y la potencia si es necesario

			cout << descomposicion[i].primo;

			if(descomposicion[i].potencia > 1)
				cout << ELEVADO << descomposicion[i].potencia;

			cout << SEPARADOR;
		}

		// Imprime el último primo de la descomposición con su potencia

		cout << descomposicion[utilizados_descomposicion - 1].primo;

		if(descomposicion[utilizados_descomposicion - 1].potencia > 1)
			cout << ELEVADO 
				 << descomposicion[utilizados_descomposicion - 1].potencia;

		// Solicita el siguiente número -----------------------------

		cout << endl << endl;

		entrada = LeerEnteroEnRango(MSG, TERMINADOR, MAX_PRIMO);
	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/Erastotenes.cpp)

## 7. IntentosAdivinarAutonomoInteligente.cpp
Recuperando la heurística del ejercicio ```6. AdivinarAutonomoInteligente.cpp``` de la [Sesión VII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/Sesi%C3%B3n%2007.md) de prácticas:  
  
(Recordamos que estábamos interesados en adivinar un valor escogido entre ```MIN``` y ```MAX``` de forma inteligente) En este caso, partiremos del valor medio entre ```MIN``` y ```MAX```. Si es el valor buscado hemos terminado; pero si no, sabemos que el valor buscado estará en la mitad izquierda (si el buscado es menor que el número proporcionado); o en la mitad derecha (si el buscado es mayor que el número proporcionado), descartando así la mitad de los casos. Sabiendo ya la mitad en la que tenemos que buscar, volveremos al mismo razonamiento: buscaremos el valor medio de la nueva mitad y comprobaremos si es el valor buscado. En caso de no serlo, reduciríamos el problema otra vez a la mitad, quedándonos ahora con un cuarto de todo el rango total en tan sólo 2 jugadas. Repetiríamos el proceso hasta encontrar el número.  
  
Ahora, queremos saber cuántos intentos se realizan para localizar cada uno de los valores entre ```MIN``` y ```MAX```:  
Para cada valor ```MIN``` $\leq$ ```i``` $\leq$ ```MAX```, calcule y guarde el número de intentos que hacen falta para localizar $i$ según la heurística anterior. Muestre una tabla que indique los valores de $i$ y el número de intentos realizados para localizarlo.  
Deberá separar los procesos de cálculo y de presentación de resultados.
```cpp
#include <iostream>

using namespace std;

int main(){
	
	const int MIN = 0, MAX = 100;

	// Número de valores entre MIN y MAX
	const int NUM_VALORES = MAX - MIN + 1;

	int num_intentos[NUM_VALORES];

	// CÁLCULOS

	// Calculamos los intentos en todos los valores entre MIN y MAX

	int jugadas;
	int intento;
	int max_generar, min_generar;

	int casilla = 0;

	for(int i = MIN; i <= MAX; i++){

		// i es el número a adivinar

		jugadas = 0;

		max_generar = MAX;
		min_generar = MIN;

		// Se ejecuta hasta que lo adivine

		do{
			// Se calcula el punto medio de [min_generar, max_generar]
			intento = (max_generar + min_generar) / 2;

			// Se van cerrando las cotas del intervalo
			// (+1 o -1 porque como intento != i, no nos interesa
			// incluir dicho valor en el intervalo, si no el siguiente valor)

			if(i > intento)
				min_generar = intento + 1;

			else
				max_generar = intento - 1;
	
			jugadas++;		// Aumentan las jugadas

		}while(intento != i);

		// Se guarda el número de jugadas que ha costado adivinar i

		num_intentos[casilla] = jugadas;

		casilla++;
	}

	// SALIDAS

	cout << endl;

	casilla = 0;

	// Se muestra el número de intentos por cada número

	for(int i = MIN; i <= MAX; i++){

		cout << "Numero:	" << i << "	Intentos:	" << num_intentos[casilla] 
			 << endl;

		casilla++;

	}

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/IntentosAdivinarAutonomoInteligente.cpp)
# Ejercicios Opcionales
En esta ocasión, los 3 primeros ejercicios están orientados a **structs** y los 7 siguientes a **arrays**.
## 1. Circunferencia.cpp
Recupere los ```structs``` ```Punto2D``` y ```Circunferencia``` del ejercicio ```1. Rectangulo.cpp``` del inicio de la sesión de prácticas, para llevar a cabo el siguiente programa:  
  
Desarrolle funciones para obtener la longitud de una circunferencia, el área del círculo, y una función que indique si una circunferencia contiene a un punto.  
Recordamos que un punto $P = (x, y)$ está dentro de una circunferencia $C$ de centro $(a,b)$ y radio $r$ si:  
$$d(C, P) = \sqrt{(a-x)² + (b-y)²} < r$$  
  
Desarrolle un programa que pida al usuario las coordenadas del centro de una circunferencia y el radio de la misma; y que imprima en pantalla la longitud de la circunferencia y el área que esta encierra. Además, deberá pedir al usuario una secuencia de puntos terminada por FIN y, por cada punto, deberá imprimir si la circunferencia contiene o no al punto.

## 2. GaussianaCDF.cpp
Recordando el enunciado del ejercicio ```CDFGaussiana.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
Estamos interesados en obtener el área que cubre la función gaussiana en un intervalo dado. Si consideramos el intervalo $]-\infty, x]$, el valor del área de la región que queda bajo la curva de $g(x)$ (siendo $g$ la función gaussiana) se calcula con la _distribución acumulada_ (_cumulative distribution function_ o CDF) en el punto $5x$:
$$CDF(x) = \int_{-\infty}^x g(x)~dx$$
Puede obtenerse un valor aproximado de $CDF(x)$ como la suma de valores de $g(x)$ empezando por valores alejados de la media (y menores que ella). Esto es, en vez de resolver la integral, estaremos interesados en aproximarla con un sumatorio de rectángulos de anchura relativamente pequeña.  
  
Escriba un programa que calcule $CDF(x)$. El programa debe pedir los parámetros que definen una función gaussiana ($\mu$ y $\sigma$) y el valor de la abscisa $x$, para el que se va a calcular $CDF(x)$. Para el cálculo de $CDF(x)$, realizaremos una suma. Debemos concretar de qué forma la realizaremos:
1. Necesitamos un valor inicial para $x$ (úsese $\mu - 3\sigma$).
2. Un salto entre dos valores consecutivos de $x$ (use una constante).  
   
Recordamos la expresión de la función $g(x)$:
$$g(x) = \dfrac{1}{\sigma\sqrt{2\pi}} e^{\left[\dfrac{-1}{2}\left(\dfrac{x-\mu}{\sigma}\right)²\right]}$$  
  
Ahora, defina un tipo de dato ```Gaussiana``` mediante un ```struct``` que permite almacenar los datos ($\mu$ y $\sigma$) que definen a una distribución gaussiana.  
Escriba un programa que:
1. Lea los parámetros que definen a una distribución gaussiana (filtrándolos) y los almacene.
2. Muestre los valores de $x$, $g(x)$ y $CDF(x)$ para los valores de $x$ en el intervalo $[\mu - 3\sigma, \mu + 3\sigma]$ con un salto determinado.
3. Pregunte si desea continuar y, de ser así, volver al paso 1. Terminar el programa si no.

## 3. MaximaVelocidadImputada.cpp
Recordando el ejercicio ```11. MaximaVelocidadImputada.cpp``` de la [Sesión VIII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/Sesi%C3%B3n%2008.md) de prácticas:  
  
En este ejercicio queremos determinar la sanción a aplicar en una autovía, cuyo límite de velocidad es 120 Km/h. En la siguiente tabla se muestra la velocidad del vehículo y la sanción correspondiente (número de puntos del carnet de conducir que se restan y la multa en euros)  
  
```(120, 150] --> 0, 100```  
```(150, 170] --> 2, 300```  
```(170, 180] --> 4, 400```  
```(180, 190] --> 6, 500```  
```(190, ...) --> 6, 600```  
  
Escriba un programa que lea matrículas de vehículos válidas (una matrícula de un vehículo es válida si está representada por 7 caracteres de los cuales los 4 primeros son dígitos y los 3 últimos letras mayúsculas del alfabeto inglés) y la velocidad registrada por el radar a cada una de dichas matrículas, hasta leer una matrícula inválida. El programa deberá calcular qué sanción se le aplica a cada vehículo (o si no se le aplica ninguna sanción).  
  
Ahora, al terminar la ejecución del programa, se debe mostrar en pantalla:
- El número de vehículos totales y número de vehículos a sancionar.
- La mayor velocidad registrada por el radar entre todos esos vehículos.
- La velocidad media de los vehículos.
- El dinero total que se va a recaudar con las sanciones.
- El total de puntos que se van a retirar a los conductores.
- La cuantía media (de dinero y puntos) por sanción.

## 4. CambioMonedasCaja.cpp
Recordando el enunciado del ejercicio ```2. Cambio.cpp``` de la [Sesión III](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/Sesi%C3%B3n%2003.md) de prácticas:  
  
Escriba un programar para una caja de supermercado que lea el total a pagar y la cantidad pagada (se supone que la cantidad pagada es mayor o igual que el total a pagar) e indique el número de monedas de 2€, 1€, 50 céntimos, 20 céntimos, 10 céntimos, 5 céntimos, 2 céntimos y 1 céntimo que se deben dar de cambio. Deberán indicarse la menor cantidad de monedas de cada clase.  
  
Ahora, deberá tener en cuenta el número de monedas disponibles en la caja, de manera que si no hay monedas de un determinado valor, debe suplirlo usando unidades de valor infereior.  
  
La funcionalidad del programa será la siguiente:
1. Inicialmente, el programa pedirá información sobre la cantidad de monedas en caja de cada tipo.
2. Posteriormente, solicitará un precio a pagar y la cantidad pagada. El programa debe informar de cuánto cambio se proporcionará, indicando explícitamente las monedas de cada tipo a devolver. El programa restará las monedas usadas del total de la caja (el precio a pagar no es dinero que se introduce en la caja, la caja nunca aumenta la cantidad de monedas).
3. Volver al paso 2, se solicitará un nuevo precio a pagar y cantidad pagada. Se repetirá hasta que se introduzca '0' como precio a pagar. Tras la finalización del programa, se debe informar de cuántas monedas se han sacado de la caja en toda la ejecución del programa, así como el total de dinero ganado (suma de todos los precios a pagar).  
  
Nota: en caso de que la cantidad de monedas en caja no sea suficiente para proporcionar un cambio, el programa finalizará informando de ello (e informando de la cantidad de monedas extraídas y dinero ganado antes de la compra actual).

## 5. Desnivel.cpp
Supongamos un vector de enteros relativo a un conjunto de alturas de un track GPS. Cada entero representa la altura de la posición GPS en un instante dado. Se quiere calcular lo siguiente:
- **Máximo desnivel**: Se define como la máxima diferencia (en valor absoluto) entre dos alturas consecutivas.  
Por ejemplo, si el vector es ```1 3 2 4 7 5```, las diferencias son:  
```+2 -1 +2 +3 -2```, siendo ```3``` la máxima en valor absoluto.  
Si el vector fuera ```1 3 2 4 1 2 ```, las diferencias serían:  
```+2 -1 +2 -3 +1```, siendo ```3``` la máxima en valor absoluto.  
- **Desnivel acumulado positivo**: La idea es ir buscando puntos consecutivos en los que la altura vaya aumentando. El desnivel acumulado se calcula como la suma de todas esas diferencias positivas.  
Por ejemplo, si el vector es ```1 3 2 4 7 5```, las diferencias son:  
```+2 -1 +2 +3 -2```, por lo que el desnivel acumulado positivo será:
$$2 + 2 + 3 = 7$$  
  
Construir un programa que, primero, lea un número natural distinto de 0, ```n```, número de valores de altura a introducir. A continuación, el programa leerá ```n``` número enteros consecutivos, almacenándolos en un vector.  El programa calculará el **máximo desnivel** y el **desnivel acumulado positivo**, imprimiéndolos en pantalla.

## 6. LeyDHondt.cpp
La Ley **D'Hondt** es el método usado en España para asignar escaños a una circunscripción electoral.  
Se quiere construir un programa que lea el número total de escaños a distribuir, el número de partidos que han participado en las elecciones y los votos obtenidos por cada uno de ellos. El programa mostrará cuántos escaños obtuvo cada partido.  
  
La asignación de los escaños se hace a través de un proceso iterativo en el que en cada iteración se asigna un escaño a un partido y así hasta llegar al número total de escaños a repartir. Se calculan cocientes sucesivos para cada partido político.  La fórmula de los cocientes es:
$$Cociente = \dfrac{IV_i}{S_i+1}$$
Donde $IV_i$ es el número total de votos obtenidos por el partido $i$ y $S_i$ es el número de escaños que ha obtenido hasta el momento el partido $i$.  
  
El número de votos recibidos por cada partido se divide sucesivamente por cada uno de los divisores, desde 1 hasta el número total de escaños a repartir. La asignación de cada escaño se determina hallando el máximo de los cocientes y asignando a cada uno un escaño, hasta que estos se agoten.  
  
Ejemplo: Supongamos unas elecciones a las que se presentan ```n = 4``` partidos, entre los que se deben repartir 5 escaños. La asignación de escaños se hace como sigue:  
Cada escaño se asigna al partido cuyo cociente sea máximo (se indica en negrita):  
  
| Partido  | Partido A | Partido B | Partido C | Partido D |  
|----------|-----------|-----------|-----------|-----------|  
| Votos    | 340000    | 280000    | 160000    |  60000    |   
| Escaño 1 | **340000/1**  | 280000/1  | 160000/1  |  60000/1  |  
| Escaño 2 | 340000/2  | **280000/1**  | 160000/1  |  60000/1  |  
| Escaño 3 | **340000/2**  | 280000/2  | 160000/1  |  60000/1  |  
| Escaño 4 | 340000/3  | 280000/2  | **160000/1**  |  60000/1  |  
| Escaño 5 | 340000/3  | **280000/2**  | 160000/2  |  60000/1  |  
  
Sugerencia: Represente la información de cada partido con un ```struct```:  
```cpp
struct Partido{
    char sigla; // Nombre
    long votos;
    int escanos;
};
```

## 7. EliminaRepetidos.cpp
Escriba un programa que lea un número indeterminado de naturales (termina cuando se introduce un número negativo o 0), aunque nunca leerá más de 50. Los irá almacenando en un array ```datos```.  
  
A continuación, elimina del array los repetidos, dejando sólo una copia. No se dejan huecos en medio y todos los números quedan en los índices más bajos del vector.  
  
Se pide implementar tres versiones del borrado:
1. Usar un **array auxiliar** ```sin_repetir``` en el que almacenamos una única aparición de cada componente:  
```Copiar la primera componente de datos en sin_repetir```  
```Desde la segunda casilla de datos, hasta la última:```  
```   Si el valor de la casilla NO está en sin_repetir: ```  
```      Se añade al vector sin_repetir ```  
```Sustituir todas las componentes de datos por las de sin_repetir```  
2. Sin usar estructuras auxiliares, borrar del vector las repetidas:  
```Desde la primera casilla de datos, hasta la última:```  
```   Guardar el valor de la casilla, v```  
```   Desde esta hasta la penúltima: ```  
```      Si datos[j] = v: datos[j]=datos[j+1] ```
4. Usar dos apuntadores: ```pos_lectura``` y ```pos_escritura```; y un array ```repetidos```.

## 8. RLE.cpp
Recordamos el enunciado del ejercicio ```2. RLE.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
El método RLE (Run Length Encoding) codifica una secuencia de datos formada por series de valores idénticos consecutivos como una secuencia de parejas de número-carácter (indica el número de veces que se repite dicho carácter de forma consecutiva). Se trata de un mecanismo de compresión de datos (zip) sin pérdidas.  
  
Por ejemplo, la cadena:  
```A A A X X X X X D D D D D D Q .```  
  
Se codifica como:  
```3A 5X 6D 1Q```  
  
Se pide hacer un programa que:  
1. Lea y almacene en un vector ```cadena``` un número indeterminado de caracteres (no más de 50). Se termina de leer cuando se supere el máximo establecido o se lea el carácter ```.```.
2. Codifique mediante el método RLE el array anterior, guardándolo en un array ```codificado```.
3. Descodifice el array ```codificado```, guardando el resultdo en un array ```descodificado```.
4. Compare los arrays ```cadena``` y ```descodificado```, e informe si son iguales o no.

## 9. SubsecuenciaOrdenadaMasLarga.cpp
Recordando el enunciado del ejercicio ```1. SecOrdenadaMasLarga.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
Construya un programa que calcule cuándo se produjo la mayor secuencia de días consecutivos con temperaturas crecientes. El programa leerá una secuencia de reales representando temperaturas, hasta que se introduzca un valor fuera de un rango establecido, y debe calcular la subsecuencia de números ordenada, de menor a mayor, de mayor longitud. El programa nos debe decir la posición donde comienca la subsecuencia y su longitud.  
  
Por ejemplo, ante la siguiente entrada:  
```17.2 17.3 16.2 16.4 17.1 19.2 18.9 -1```  
  
El programa debe indicar que la mayor subsecuencia empieza en la posición ```3``` (en el ```16.2```) y tiene longitud ```4``` (termina en ```19.2```).  
  
El rango de validez de una temperatura quedará determinado por el intervalo ```[MIN_TEMP_VALIDA, MAX_TEMP_VALIDA]```. Deberá fijar dichas constantes según su criterio. Es posible también que el primer valor leído sea incorrecto (esté fuera de rango), por lo que deberá introducir además una constante ```MIN_LONG_VALIDA``` (fije también su valor con un número que considere adecuado), de forma que si la subsecuencia creciente de temperaturas más larga no tiene una longitud superior a dicha constante, el programa deberá indicar que la subsecuencia más larga tiene una longitud no válida.  
  
Ahora, separe la entrada de los cálculos con el uso de un array. Establecer además en 100 un máximo de temperaturas para leer.

## 10. RobotLinea.cpp
Tenemos un robot que se mueve en una línea, utilizando pasos de longitud fija.  
Inicialmente, el robot se ubica en ```pos```, un valor entero $1 \leq pos \leq 100$.  
Luego, el robot ejecuta una serie de órdenes, indicadas mediante un array ```ord``` de tipo ```char```, con longitud ```lon```. Cada orden es una letra ```I``` o ```D```, indicando si el robot se mueve a la izquierda (decrementando la posición actual en una unidad), o a la derecha (incrementando la posición actual en una unidad).  
  
Las posiciones válidas del robot son: $1 \leq pos \leq 100$.  
Se dice que una serie de órdenes al robot es correcta si nunca se sale del rango establecido.  
  
Se pide implementar un programa para que, dada una posición inicial ```pos``` por el usuario y una lista de órdenes ```ord``` de longitud ```lon```, haga lo siguiente:
- Si la serie de órdenes es correcta, muestre el itinerario, así como el número de veces que se visitó cada posición.
- Si la serie de órdenes NO es correcta, el programa ejecutará las órdenes posibles hasta que la ejecución no pueda continuar (hasta que ```pos``` se salga de los márgenes establecidos), indicando cuántas órdenes pudo ejecutar.  
  
Ejemplos:  
```Posicion inicial (pos): 10```  
```Longitud (lon): 6```  
```Ordenes (ord): DDIIII```  
  
```Posiciones (validas) visitadas:```  
```   10 --> 11 --> 12 --> 11 --> 10 --> 9 --> 8 ```  
```Salida del programa:```  
```   Serie de ordenes: correcta ```  
```   Frecuencia de visitas: ```  
```       (8, 1), (9, 1), (10, 2), (11, 2), (12, 1) ```  
```-------------------------------------------------```  
  

```Posicion inicial (pos): 1```  
```Longitud (lon): 4```  
```Ordenes (ord): DIID```  
  
```Posiciones (validas) visitadas:```  
```   1 --> 2 --> 1```  
```Salida del programa:```  
```   Serie de ordenes: incorrecta ```  
```   Se ejecutaron 2 ordenes```  
