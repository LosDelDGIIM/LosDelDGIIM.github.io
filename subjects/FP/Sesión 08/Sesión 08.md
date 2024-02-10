# Fundamentos de Programación. Sesión VIII de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión VIII de prácticas.

En esta sesión de prácticas se introducen las **funciones**, por lo que muchos de los siguientes ejercicios estarán orientados a su uso. Además, deberá incluir en la función **main** código para probar las funciones.
Será necesario también **documentar las funciones** de forma breve, incluyendo comentarios que indiquen qué devuelve, qué parámeros recibe y alguna precondición si esta es necesaria.

## 1. RedondearTruncarDecimal.cpp
En ```cmath``` está definida la función ```round```, que permite redondear un real al entero más próximo.  
  
Por ejemplo:  
```round(3.6) = 4```  
```round(3.5) = 4```  
```round(3.1) = 3```  
```round(3.49) = 3```  
  
Nuestro interés es hacer algo similar pero para permitir el redondeo de la parte decimal, especificando el número de cifras decimales que nos interese. Por ejemplo:  
- El resultado de redondear 3.49 a la primera cifra decimal es 3.5.  
- El resultado de redondear 3.49 a la segundo cifra decimal es 3.49.  
- El resultado de redondear 3.496 a la segunda cifra decimal es 3.5.  
  
Defina la función **Redondea** para calcular un número real aproimado a un número de cifras dado.  
  
Además, podemos plantear el truncamiento de la parte decimal. Por ejemplo:  
- El resultado de truncar 3.49 a una cifra decimal es 3.4.  
- El resultado de truncar 3.496 a la segunda cifra decimal es 3.49.  
- El resultado de truncar 3.496 sin decimales es 3 (3.0).  
  
Defina la función **Trunca**, para truncar un número real usando un número de cifras decimales dado.  
  
En la implementación de estas funciones, necesitará calcular potencias enteras (potencias de 10 en este caso). Para ello, desarrolle una función **Potencia**.  
  
En la función **main**, cree un programa que solicite un número real y un número natural que represente la cifra decimal del real a la que nos referimos (por ejemplo, si queremos hacer referencia al 2 de 1.23, introduciremos un 1 por ser la primera cifra decimal). El programa imprimirá el resultado de truncar dicho número a dicha cifra y de redondear dicho número a dicha cifra.
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

/***********************************************************************
	Función que calcula 10 elevado a exponente

  Parámetros: exponente
  Devuelve: 10 elevado a exponente
  PRE: exponente >= 0

***********************************************************************/

double Potencia_10(int exponente){
	double resultado = 1;	

	// Se calcula 10 * 10 * ... * 10 repitiendo 10 exponente veces

	for(int i = 0; i < exponente; i++)
		resultado *= 10;

	return resultado;
}

/***********************************************************************
	Función que devuelve num truncado a cifras cifras decimales

  Parámetros: num, cifras
  Devuelve: num truncado a cifras cifras decimales
  PRE: cifras >= 0

***********************************************************************/

double Trunca(double num, int cifras){
	double potencia_10 = Potencia_10(cifras);	 // 10 ^ cifras

	// Almacena las cifras del número truncado
	int auxiliar = num * potencia_10;

	// Desplazamos el punto decimal
	return auxiliar / potencia_10;
}

/***********************************************************************
	Función que devuelve num redondeado a cifras cifras decimales

  Parámetros: num, cifras
  Devuelve: num redondeado a cifras cifras decimales
  PRE: cifras >= 0

***********************************************************************/

double Redondear(double num, int cifras){
	
	// Trabajamos sobre el valor absoluto del número
	bool negativo = num < 0;

	if(negativo)
		num = -num;

	// Almacena las cifras del número truncado a cifras + 1
	int auxiliar = num * Potencia_10(cifras + 1);

	// ALmacena las cifras del número truncado a cifras
	int cifras_truncado = auxiliar / 10;	// = num * Potencia_10(cifras)

	// Obtiene la cifra posterior a la cifra decimal a redondear

	int cifra_redondear = auxiliar - 10 * cifras_truncado;

	// Almacena las cifras del número redondeado 

	int cifras_redondeado = (cifra_redondear < 5)? 
							cifras_truncado : cifras_truncado + 1;

	// Desplazamos el punto decimal
	double redondeado = cifras_redondeado / Potencia_10(cifras);

	// Si num era negativo, pasamos el resultado para que sea negativo
	if(negativo)
		redondeado = -redondeado;

	return redondeado;
}

/***********************************************************************/

int main(){

	// El algoritmo está limitado: no puede redondear ni truncar números a 
	// más de 7 cifras decimales por las limitaciones de las variables
	const int MAXIMO_SOPORTADO = 7;

	double numero;
	int cifras;

	// ENTRADAS

	cout << "Introduzca un numero: ";
	cin >> numero;

	bool cifras_invalidas = false;

	do{
		// Imprime por qué la última entrada no fue válida
		if(cifras_invalidas)
			cout << endl << "Las cifras deben estar entre 0 y " 
				 << MAXIMO_SOPORTADO << endl;

		cout << "Numero de cifras decimales: ";
		cin >> cifras;

		cifras_invalidas = cifras < 0 || cifras > MAXIMO_SOPORTADO;

	}while(cifras_invalidas);

	// SALIDAS

	// Formateamos la consola, para que se puedan visualizar bien
	// los digitos decimales deseados

	cout.setf(ios::fixed);

	cout << setw(cifras+3) << setprecision(cifras);

	cout << endl;

	cout << "Numero truncado: " << Trunca(numero, cifras) << endl;
	cout << "Numero redondeado: " << Redondear(numero, cifras) << endl;

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/RedondearTruncarDecimal.cpp)

## 2. LecturaEnteros.cpp
Desarrolle la implementación de las siguientes funciones para leer números enteros:  
  
```int LeeEntero(string titulo)```  
Lee y devuelve un dato ```int```. Si el valor leido no fuera un ```int```, la función volvería a pedirlo hasta que se proporcione un entero orrecto. La lectura se etiqueta con ```titulo```.  
Algunos ejemplos de valores que la función no debe reconocer como enteros son:  
```94.5```, ```77 88```, ```0xA2```, ```55.0```.  
  
```int LeeEnteroEnRango(string titulo, int menor, int mayor)```  
Lee y devuelve un dato ```int``` en un rango dado. Si el valor leido no fuera ```int``` o esté fuera del rango ```[menor, mayor]```, la función volvería a pedirlo hasta que se proporcionara un valor correcto. La lectura se etiqueta con título.  
  
```int LeeEnteroMayorOIgual(string titulo, int referencia)```  
Lee y devuelve un dato ```int``` que debe ser mayor o igual que ```referencia```. Si el valor leído no fuera ```int``` o fuera menor que ```referencia```, la función volvería a pedirlo hasta que se proporcionara un valor correcto. La lectura se etiqueta con título.  
  
En la función **main** deberá incluir código para probar el funcionamiento de estas tres funciones.
```cpp
#include <iostream>

using namespace std;

/****************************************************************************
	Función que comprueba si un caracter es un dígito

  Parámetro: caracter
  Devuelve: true si el caracter está comprendido en el intervalo [0, 9],
	false si no

****************************************************************************/

bool EsDigito(char caracter){

	const int ASCII_0 = '0', ASCII_9 = '9';

	// Comprueba si el código ascii de caracter está entre los códigos
	// ascii del 0 y el 9

	return caracter >= ASCII_0 && caracter <= ASCII_9;

}

/****************************************************************************
	Función que comprueba si todos los caracteres de una cadena son dígitos

  Parámetros: cadena
  Devuelve: true si todos los caracteres de la cadena eran dígitos, false si no

****************************************************************************/

bool CadenaSoloContieneDigitos(string cadena){
	
	// Suponemos que la cadena sólo tiene dígitos
	bool todo_digitos =  true;

	// Recorremos la cadena en busca de un caracter que no sea un dígito
	// en caso de encontrarlo, se detiene la ejecución del bucle

	int i = 0;

	while(todo_digitos && i < cadena.length()){

		if(!EsDigito(cadena.at(i)))
			todo_digitos = false;

		i++;
	}

	return todo_digitos;
}

/****************************************************************************
	Función que comprueba si un string es un número entero o no

  Parámetros: cadena
  Devuelve: true (si cadena era un entero), false si no

****************************************************************************/

bool EsEntero (string cadena){
	const char MENOS = '-';	

	bool es_entero;

	// Si la cadena está vacía, no es un número entero

	if(cadena.length() == 0)
		es_entero = false;

	else{

		// Si es un número negativo, se elimina el signo
		if(cadena.at(0) == MENOS)
			cadena.erase(0, 1);	// Elimina el primer caracter
		
		// Si al quitar el menos hay más caracteres
		if(cadena.length() != 0){
		
			// Hasta que no se encuentre un fallo es un entero
			es_entero = CadenaSoloContieneDigitos(cadena);
		
		}else	// Si no, no es un entero (habrían introducido "-")
			es_entero = false;

	}

	return es_entero;
}

/****************************************************************************
	Función que lee y devuelve un dato entero. Si el valor introducido
	no era un entero, vuelve a repetir la entrada hasta obtener un entero

  Parámetros: titulo (mensaje que muestra al pedir el entero)
  Devuelve: el entero

****************************************************************************/

int LeeEntero (string titulo){

	string entrada;	

	bool es_entero;

	// Repite la entrada mientras que no introduzcan un entero

	do{
		// Solicita el entero
		cout << titulo;
		getline(cin, entrada);
	
		// Se comprueba que sea un número entero
		es_entero = EsEntero(entrada);

	}while(!es_entero);

	return stoi(entrada);	
}

/****************************************************************************
	Función que lee y devuelve un dato entero dentro del rango establecido.
	Si el valor introducido no fuera un entero o estuviese fuera
	del rango establecido, se volvería a repetir la entrada.

  Parámetros: titulo (mensaje a mostrar), 
			  menor, mayor (definen el rango de valores válidos)
  Devuelve: el entero dentro del intervalo [menor, mayor]
  PRE: menor <= mayor

****************************************************************************/

int LeeEnteroEnRango (string titulo, int menor, int mayor){
	
	string entrada;
	int entero;

	bool no_valido;

	// Se repite mientras que no sea un valor válido

	do{
		// Lee un dato entero
		entero = LeeEntero(titulo);

		// Es inválido si el dato no está en el intervalo [menor, mayor]
		no_valido = entero < menor || entero > mayor;

	}while(no_valido);

	return entero;
}

/****************************************************************************
	Función que lee y devuelve un dato entero mayor o igual que referencia.
	Si el valor introducido no fuera un entero o fuera menor que referencia, 
	se volvería a repetir la entrada.

  Parámetros: titulo (mensaje a mostrar), referencia
  Devuelve: el entero mayor o igual que referencia

****************************************************************************/

int LeeEnteroMayorOIgual (string titulo, int referencia){
	
	string entrada;
	int entero;

	bool no_valido;

	// Se repite mientras que no sea un valor válido

	do{
		// Lee un dato entero
		entero = LeeEntero(titulo);

		// No es válido si es menor que referencia
		no_valido = entero < referencia;

	}while(no_valido);

	return entero;
}

/****************************************************************************/

int main(){
	
	const int MENOR = 0, MAYOR = 50, REFERENCIA = 10;

	const string MSG_ENTERO = "Introduzca un entero: ";

	const string MSG_RANGO = "Introduzca un entero entre " + to_string(MENOR) 
							+ " y " + to_string(MAYOR) + " : ";

	const string MSG_MAYOR_IGUAL = "Introduzca un entero mayor o igual que "
							+ to_string(REFERENCIA) + " : ";

	// ENTRADAS

	int entero = LeeEntero(MSG_ENTERO);

	cout << endl;

	int rango = LeeEnteroEnRango(MSG_RANGO, MENOR, MAYOR);

	cout << endl;

	int mayor_igual = LeeEnteroMayorOIgual(MSG_MAYOR_IGUAL, REFERENCIA);

	// SALIDAS

	cout << endl << endl;

	cout << "Un entero: " << entero << endl;

	cout << "Un entero entre " << MENOR << " y " << MAYOR << ": " 
		 << rango << endl;

	cout << "Un entero mayor o igual que " << REFERENCIA << ": " 
		 << mayor_igual << endl;	

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/LecturaEnteros.cpp)

## 3. FormateaString.cpp
Escriba una función para dar formato a un ```string```, obteniendo como resultado un nuevo ```string``` de acuerdo al formato indicado en su llamada:  
  
```string FormateaString(string cad, int num_casillas, TipoAjuste ajuste, char relleno=' ')```  
Transforma el contenido del dato ```cad``` a un nuevo ```string```, que tendrá un número mínimo de ```num_casillas```. Si el número de casillas solicitado (```num_casillas```) es mayor que el tamaño de ```cad```, se completan las casillas necesarias con el carácter ```relleno```. Si la longitud de ```cad``` fuera mayor que ```num_casillas```, simplemente se devuelve una copia de ```cad```.  
  
El tipo enumerado ```TipoAjuste``` se define a continuación:  
```enum class TipoAjuste {izquierda, centro, derecha};```  
Este indica la alineación de la cadena resultado.  
  
Veamos a continuación algunos ejemplos de ejecución (los carácteres ```|``` representan el principio y final del ```string```):  
```FormateaString("Maria", 10, TipoAjuste::derecha, '*') devuelve: |*****Maria|```  
```FormateaString("Maria", 10, TipoAjuste::centro, ' ') devuelve: |  Maria   |```  
```FormateaString("Maria", 10, TipoAjuste::izquierda, '-') devuelve: |Maria-----|```  
```FormateaString("Maria", 3, TipoAjuste::derecha, '*') devuelve: |Maria|```  
  
En la función **main**, desarrolle un programa que permita al usuario llamar a esta función (que el usuario introduzca los valores que servirán de parámetros a la función, imprimiendo la salida de la función).
```cpp
#include <iostream>

using namespace std;

// Los tipos de ajustes contemplados

enum class TipoAjuste {izquierda, centro, derecha};

/****************************************************************************
	Función que genera una cadena en la que hay veces veces el caracter
	caracter.

  Parámetros: veces (el número que se repite el caracter)
			  caracter (el caracter a repetir)
  Devuelve: una cadena que contiene caracter veces veces
  PRE: veces >= 0

****************************************************************************/

string GenerarCaracteres (int veces, char caracter){
	string devuelta;	

	// Concatena caracter a devuelta veces número de veces
	for(int i = 0; i < veces; i++)
		devuelta += caracter;

	return devuelta;
}

/****************************************************************************
	Función que centra la cadena cadena mediante caracteres relleno:

	Los caracteres relleno se añadirán según el tipo de ajuste seleccionado:
		Si se selecciona izquierda, los caracteres relleno se colocan a la 
			derecha para dejar cad alineado a la izquierda.
		Si se selecciona derecha, los caracteres relleno se colocan a la 
			izquierda para dejar cad alineado a la derecha.
		Si se selecciona centro, los caracteres relleno se dividen entre la
			izquierda y la derecha de cad, alineándolo al centro.

  Parámetros: cadena, numero_caracteres, ajuste, relleno
  Devuele: Una nueva cadena que contiene la cadena anterior centrada en el
	sitio indicado, con la ayuda de tantos caracteres como se especificaron
	del tipo especificado
  PRE: numero_caracteres >= 0

****************************************************************************/

string Centrar(string cadena, int numero_caracteres, TipoAjuste ajuste
												   , char relleno){

	string cadena_centrada;

	// Realiza un ajuste u otro dependiendo del tipo de ajuste

	switch(ajuste){
		case TipoAjuste::izquierda:
			
			// Añade los caracteres relleno a la derecha

			cadena_centrada = cadena 
							+ GenerarCaracteres(numero_caracteres, relleno);
			
			break;

		case TipoAjuste::derecha:
			
			// Añade los carcteres relleno a la izquierda

			cadena_centrada = GenerarCaracteres(numero_caracteres, relleno) 
							+ cadena;

			break;

		case TipoAjuste::centro:
	
			// Reparte el número de caracteres entre delante y detrás

			int caracteres_delante = numero_caracteres / 2;

			int caracteres_detras = numero_caracteres - caracteres_delante;

			// Añade los caracteres relleno correspondientes a ambos lados

			cadena_centrada = GenerarCaracteres(caracteres_delante, relleno) 
					+ cadena + GenerarCaracteres(caracteres_detras, relleno);

			break;
	}

	return cadena_centrada;
}

/****************************************************************************
	Función que transforma el contenido de cad a un nuevo string según el
	formato indicado en los parámetros:

	La nueva cadena tendrá una longitud mínima de num_casillas casillas:
		Si cad tenía ya ese número de casillas, no se modifica.
		Si la longitud de cad era menor a ese númemro, se añaden caracteres
			relleno hasta llegar a la longitud deseada.

	Se centrará según el criterio especificado en la función
	Centrar(cadena, numero_caracteres, ajuste, relleno)

  Parámetros: cad, num_casillas, ajuste, relleno
  Devuelve: La cadena formateada según los parámetros.
  PRE: num_casillas >= 0

****************************************************************************/

string FormateaString (string cad, int num_casillas, TipoAjuste ajuste, 
													char relleno = ' '){

	string devuelta;

	// Si cad ya tenía la longitud mínima, no se modifica
	if(num_casillas <= cad.length())
		devuelta = cad;

	else{		// Si no, se modifica: 
	
		// Se calcula el número de caracteres de relleno que son necesarios
		// incluir para llegar a la longitud deseada

		int caracteres_necesarios = num_casillas - cad.length();

		// Se centra la cadena

		devuelta = Centrar(cad, caracteres_necesarios, ajuste, relleno);

	}

	return devuelta;
}

/****************************************************************************/

int main(){
	
	string cadena;
	int casillas;
	TipoAjuste ajuste;
	char relleno;

	// ENTRADAS

	// Cadena

	cout << "Cadena a formatear: ";
	getline(cin, cadena);

	// Número mínimo de casillas

	bool casillas_validas;

	do{

		cout << "Numero minimo de casillas: ";
		cin >> casillas;

		casillas_validas = casillas >= 0;

	}while(!casillas_validas);

	// Ajuste

	bool entrada_valida;

	char caracter;

	do{
	
		cout << "Tipo de ajuste (i -> izquierda, c -> centro, d -> derecha): ";
		cin >> caracter;

		entrada_valida = caracter == 'i' || caracter == 'c' || caracter == 'd';

	}while(!entrada_valida);

	// Se asigna el tipo enumerado en función del caracter introducido

	switch(caracter){
		case 'i':
			ajuste = TipoAjuste::izquierda;
			break;

		case 'c':
			ajuste = TipoAjuste::centro;
			break;

		case 'd':
			ajuste = TipoAjuste::derecha;
			break;
	}

	// Caracter relleno

	cout << "Caracter para rellenar: ";
	cin >> relleno;

	// SALIDAS

	cout << endl;

	cout << FormateaString(cadena, casillas, ajuste, relleno);

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/FormateaString.cpp)

## 4. GaussianaCDFReglaEmpirica.cpp
Recordamos el enunciado del ejercicio ```4. CDFGaussiana.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas, donde mostrábamos cómo aproximar el cálculo de $CDF(x)$:  
  
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

using namespace std;

double const PI = 6 * asin(0.5);

/****************************************************************************
	Función que calcula g(x) (la función gaussiana evaludada en x)

  Parámetros: x, sigma, mu (la abscisa y los parámetros de la gaussiana)
  Devuelve g(x) (el valor de la gaussiana de desviación típica y media
	especificadas evaluada en la abscisa x)
  PRE: sigma > 0

****************************************************************************/

double Gaussiana(double x, double sigma, double mu){
	double parte1_gaussiana = 1 / (sigma * sqrt(2 * PI));
	double parte2_gaussiana = exp(-0.5 * pow((x - mu) / sigma, 2));

	return parte1_gaussiana * parte2_gaussiana;
}

/****************************************************************************
	Función que calcula CDF(x) realizando una aproximación del área bajo
	la curva entre las abscisas [mu-3sigma, x]

  Parámetros: x, sigma, mu (la abscisa y los parámetros de la gaussiana)
  Devuelve: CDF(x)
  PRE: sigma > 0

****************************************************************************/

double CDF_Aproximacion1(double x, double sigma, double mu){
	const double SALTO = 0.25;	

	// Calculamos la parte de la gaussiana que se mantiene constante

	double parte1_gaussiana = 1 / (sigma * sqrt(2 * PI));

	double sumatoria_alturas = 0;

	// Recorremos las abscisas desde mu - 3sigma hasta la abscisa indicada,
	// dando saltos de SALTO entre cada abscisa 

	for(double xi = mu - 3 * sigma; xi <= x; xi += SALTO){

		// Segunda parte de la gaussiana, depende de xi:

		double parte2_gaussiana = exp(-0.5 * pow((xi - mu) / sigma, 2));

		// Obtenemos el valor de la gaussiana en xi

		double gaussiana = parte1_gaussiana * parte2_gaussiana;

		// Vamos realizando la sumatoria de las alturas

		sumatoria_alturas += gaussiana;

	}

	// Para obtener CDF(x) (el área bajo la curva), multiplicamos la 
	// sumatoria de las alturas por la base de los rectángulos que hemos 
	// considerado (base = SALTO) para obtener la sumatoria de las áreas de 
	// los rectángulos

	return sumatoria_alturas * SALTO;
}

/****************************************************************************
	Función que calcula CDF(x) realizando una aproximación por la fórmula:

		w = 1 - g(|x|) * (b1 * t + b2 * t^2 + ... + b5 * t^5)
	
							1
		con:	t = ---------------	
					  1 + b0 * |x|
	
				b0 = 0.2316419			b1 = 0.319381530
				b2 = -0.356563782		b3 = 1.781477937
				b4 = -1.821255978		b5 = 1.330274429
		
		Si x >= 0:
			CDF(x) = w
		Si no:
			CDF(x) = 1 - w

  Parámetros: x, sigma, mu (la abscisa y los parámetros de la gaussiana)
  Devuelve: CDF(x)
  PRE: sigma > 0

****************************************************************************/

double CDF_Aproximacion2(double x, double sigma, double mu){
	const double B0 = 0.2316419, B1 = 0.319381530, B2 = -0.35653782,
				 B3 = 1.781477937, B4 = -1.821255978, B5 = 1.330274429;

	// Calcula t
	double t = 1 / (1 + B0 * abs(x));

	// Calcula w
	double w = 1 - Gaussiana(abs(x), sigma, mu) * (B1 * t + B2 * pow(t, 2) 
				+ B3 * pow(t, 3) + B4 * pow(t, 4) + B5 * pow(t, 5));

	// Si x>=0 --> CDF(x) = w ; Si no --> CDF(x) = 1 - w
	double cdf = (x >= 0)? w : 1 - w;

	return cdf;
}

/****************************************************************************/

int main(){
	double x, sigma, mu;

	// ENTRADAS

	do{

		cout << "Desviacion tipica (mayor que 0): ";
		cin >> sigma;

	}while(sigma <= 0);

	cout << "Media: "; 
	cin >> mu;

	cout << "Abscisa: "; 
	cin >> x;

	// SALIDAS

	cout << endl;

	cout << "g(" << x << ") = " << Gaussiana(x, sigma, mu) 
	 	 << " (funcion gaussiana)" << endl;
	cout << "CDF(" << x << ") = " << CDF_Aproximacion1(x, sigma, mu) 
		 << " (aproximacion de la sumatoria del area de rectangulos)" << endl;
	cout << "CDF(" << x << ") = " << CDF_Aproximacion2(x, sigma, mu) 
		 << " (aproximacion de Abramowitz y Stegun)" << endl;

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/GaussianaCDFReglaEmpirica.cpp)

## 5. CompruebaNIFNIE.cpp
Escriba un programa que lea un núemro indefinido de NIFs/NIEs hasta que se introduzca FIN y que verifique su validez. Modularice el programa adecuadamente con funciones.  
  
Un DNI es correcto si consta de 9 caracteres, siendo los 8 primeros dígitos y el último carácter una letra mayúscula. Para que el DNI sea correcto, la letra ha de serlo. Para comprobar si la letra es correcta, dividimos el número que forman esos 8 caracteres entre 23 y el resto de dicha división es el que indexa la letra correspondiente en la siguiente tabla:  
  
| Resto | Letra |
|-------|-------|
| 0     | T     |
| 1     | R     |
| 2     | W     |
| 3     | A     |
| 4     | G     |
| 5     | M     |
| 6     | Y     |
| 7     | F     |
| 8     | P     |
| 9     | D     |
| 10    | X     |
| 11    | B     |
| 12    | N     |
| 13    | J     |
| 14    | Z     |
| 15    | S     |
| 16    | Q     |
| 17    | V     |
| 18    | H     |
| 19    | L     |
| 20    | C     |
| 21    | K     |
| 22    | E     |
  
Un NIE es correcto si consta de 9 caracteres, siendo el primer carácter una ```X```, ```Y``` o ```Z```, seguido de 7 dígitos y de una letra mayúscula. Para que el NIE sea correcto, ha de serlo la última letra. para ello, sustituiremos la primera letra por un dígito:  
  
| Letra | Dígito |
|-------|--------|
| X     | 0      |
| Y     | 1      |
| Z     | 2      |
  
Una vez hecho este cambio, tendremos un formato similar a un DNI. La última letra del NIE será válida si lo es la letra de este DNI que hemos creado.  
  
Como banco de pruebas, le dejamos un documento con inputs en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/LISTA%20NIF%20NIE%20VALIDOS.txt).
```cpp
#include <iostream>

using namespace std;

/***********************************************************/
//	Constantes que definen la longitud de un DNI, de un NIE y las letras
//  iniciales que puede contener el NIE

const int LONGITUD_DNI = 9, LONGITUD_NIE = 9;

const int DIGITOS_DNI = 8, DIGITOS_NIE = 7;

const int LETRA_NIE_1 = 'X', LETRA_NIE_2 = 'Y', LETRA_NIE_3 = 'Z';

/***********************************************************/

/****************************************************************************
	Función que comprueba si un caracter es un dígito.

  Parámetros: caracter
  Devuelve: true si caracter es un dígito, false si no

****************************************************************************/

bool EsDigito(char caracter){
	const int ASCII_0 = '0', ASCII_9 = '9';

	// Devuelve si el código ascii de caracter se encuentra entre los códigos
	// ascii del 0 y del 9 (en resumen, si caracter es un dígito)

	return caracter >= ASCII_0 && caracter <= ASCII_9;
}

/****************************************************************************
	Función que comprueba si un caracter es un caracter alfabético.

  Parámetros: carracter
  Devuelve: true si caracter es un caracter alfabético, false si no

	*Nota: En este caso, no consideramos a la ñ como un dato alfabético

****************************************************************************/

bool EsAlfabetico(char caracter){
	const int ASCII_A = 'A', ASCII_Z = 'Z';

	// Pasamos caracter a mayuscula para facilitar la comprobación

	caracter = toupper(caracter);

	// Devuelve si el código ascii de caracter en mayúscula se encuentra entre 
	// los códigos ascii de A y de Z (es decir, si era un caracter alfabético)

	return caracter >= ASCII_A && caracter <= ASCII_Z;
}

/****************************************************************************
	Función que determina si la cadena indicada tenía numero número de
	dígitos a partir de la posición inicio.

  Parámetros: cadena, inicio, numero
  Devuele: true si cadena contiene numero dígitos desde la posición inicio
  PRE: 0 <= inicio < cadena.length()
	   numero es un dato natural

****************************************************************************/

bool ContarDigitos(string cadena, int inicio, int numero){
	// Supone que los dígitos son correctos
	bool digitos_correctos = true;

	// Recorre la cadena desde inicio, hasta procesar numero caracteres
	// si alguno no era un número, digitos_correctos pasa a valer false
	// y se detiene la ejecución del bucle

	int i = inicio;

	while(digitos_correctos && i < numero){
		if(!EsDigito(cadena.at(i)))
			digitos_correctos = false;

		i++;
	}	

	return digitos_correctos;
}

/****************************************************************************
	Función que determina si el formato de un DNI es correcto o no
  
	Comprueba que el DNI sea del formato:
		NNNNNNNNC

	Donde N representa a cualquier dígito y C a cualquier caracter alfabético

  Parámetros: dni
  Devuelve: true si el DNI tenía formato correcto, false si no

	*Nota: Necesita valor de constantes globales LONGITUD_DNI y DIGITOS_DNI

****************************************************************************/

bool DNIFormatoCorrecto(string dni){

	bool digitos_correctos;
	bool letra_final;
	bool formato_correcto;

	// Si la longitud del DNI es la adecuada, comprueba que tenga un 
	// formato correcto

	if(dni.length() == LONGITUD_DNI){

		// Comprueba si el último caracter es alfabético

		letra_final = EsAlfabetico(dni.at(LONGITUD_DNI - 1));

		// Comprueba que todos los CANTIDAD_NUMEROS primeros caracteres
		// sean dígitos 

		digitos_correctos = ContarDigitos(dni, 0, DIGITOS_DNI);

		// Si se verifican las dos condiciones, es un formato de DNI válido

		formato_correcto = letra_final && digitos_correctos;

	}else		// Si no, directamente no es un formato de DNI
		formato_correcto = false;

	return formato_correcto;
}

/****************************************************************************
	Función que determina si el formato de un NIE es válido o no
  
	Comprueba que el NIE sea del formato:
		CNNNNNNNC

	Donde N representa a cualquier dígito y C a cualqueir caracter alfabético

  Parámetros: nie
  Devuelve: true si el NIE tenía formato correcto, false si no

	*Nota: necesita valor de constantes globales LONGITUD_NIE y DIGITOS_NIE

****************************************************************************/

bool NIEFormatoCorrecto(string nie){

	bool digitos_correctos;
	bool letra_inicial;
	bool letra_final;
	bool formato_correcto;

	// Comprueba que la longitud del NIE sea válida

	if(nie.length() == LONGITUD_NIE){

		// Comprueba que tenga CANTIDAD_NUMEROS número de dígitos a partir
		// de la posición 1

		digitos_correctos = ContarDigitos(nie, 1, DIGITOS_NIE);

		// Comprueba que el primer caracter del NIE sea alfabético

		letra_inicial = EsAlfabetico(nie.at(0));

		// Comprueba que el últio caracter del NIE sea alfabético

		letra_final = EsAlfabetico(nie.at(LONGITUD_NIE - 1));

		// Si se dan las tres, el formato es válido

		formato_correcto = digitos_correctos && letra_inicial && letra_final;

	}else	// Si no, tenía un formato equivocado
		formato_correcto = false;

	return formato_correcto;
}

/****************************************************************************
	Función que devuelve la letra correspondiente a un DNI

	Para ello, se calcula el módulo del número del DNI entre DIVISOR y 
	dependiendo del valor se asigna una letra u otra.

  Parámetros: dni (número del DNI)
  Devuelve: El caracter que le corresonde al DNI

****************************************************************************/

char ObtenerLetraDNI(long dni){

	const int DIVISOR = 23;

	// Contiene todas las letras que se pueden asignar a un DNI, ordenadas
	// según los posibles valores de resto (del 0 al 22)

	const string LETRAS = "TRWAGMYFPDXBNJZSQVHLCKE";

	// Se calcula el resto y se devuelve el caracter correspondiente

	int resto = dni % DIVISOR;

	return LETRAS.at(resto);
}

/****************************************************************************
	Función que determina si la letra de un DNI es correcta o no
  
	Para ello, se extrae el número del DNI y se comprueba que la letra
	especificada coincida con la letra que debe tener el número del DNI

  Parámetros: dni
  Devuelve: true si la letra del DNI era válida, false si no
  PRE: dni debe tener un formato válido, debe filtrarse por la función
	DNIFormatoCorrecto(dni)

	*Nota: Necesita valor de constante global DIGITOS_DNI

****************************************************************************/

bool DNILetraCorrecta(string dni){

	// Nos quedamos con el número del DNI y con la letra

	long numero_DNI = stol(dni.substr(0, DIGITOS_DNI));

	char letra = toupper(dni.at(dni.length() - 1));

	// Devolvemos el resultado de comparar la letra del DNI que introdujo
	// el usuario y la letra que debería tener ese número de DNI

	return letra == ObtenerLetraDNI(numero_DNI);
}

/****************************************************************************
	Función que determina si la primera letra de un NIE es correcta o no.
	Para ser correcta, debe ser igual a X, Y o Z.

  Parámetros: nie
  Devuelve: true si la primera letra es correcta, false si no
  PRE: nie no puede estar vacío

	*Nota: necesita los valores de las constantes globales LETRA_NIE_1,
	LETRA_NIE_2 y LETRA_NIE_3

****************************************************************************/

bool PrimeraLetraCorrectaNIE(string nie){
	char primera_letra = toupper(nie.at(0));

	return primera_letra == LETRA_NIE_1 || primera_letra == LETRA_NIE_2 
							|| primera_letra == LETRA_NIE_3;
}

/****************************************************************************
	Función que determina si las letras de un NIE son correctas o no
  
	Para ello, el primer caracter debe ser X, Y o Z

	Posteniormente se calcula la letra final, que se obtiene de la misma
	forma que la del DNI. La letra inicial se sustituye por un número
	para obtener un número similar al DNI:
		X --> 0
		Y --> 1
		Z --> 2

  Parámetros: nie
  Devuelve: true si el NIE era válido, false si no
  PRE: nie debe tener un formato correcto, debe filtrarse mediante la función
	NIEFormatoCorrecto(nie)

	*Nota: Necesita los valores de las constantes globales DIGITOS_NIE 
		   y LETRA_NIE_1

****************************************************************************/

bool NIELetrasCorrectas(string nie){

	bool letras_correctas;

	// Nos quedamos con la última y la primera letra

	char letra_inicial = toupper(nie.at(0));

	char letra_final = toupper(nie.at(nie.length() - 1));

	// Comprobamos si la letra inicial era válida:

	bool letra_inicial_valida = PrimeraLetraCorrectaNIE(nie);

	// Si la primera letra no era válida, las letras no son correctas

	if (!letra_inicial_valida)
		letras_correctas = false;

	else{		// letra_inicial es la contemplada

		// Restamos el código ascii de letra_inicial menos el código ascii
		// de la primera letra válida del NIE, obteniendo el primer núemro
		// del NIE

		int primer_numero = letra_inicial - LETRA_NIE_1;

		// Se obtiene el número del NIE, una vez sustituida la letra inicial
		// por el dígito corresondiente
		
		long numero_nie = 
				stol(to_string(primer_numero) + nie.substr(1, DIGITOS_NIE));

		// Se comprueba si la letra final es la correcta

		letras_correctas = letra_final == ObtenerLetraDNI(numero_nie);

	}

	return letras_correctas;
}

/***************************************************************************
	Función que comprueba si un DNI es válido o no

  Parámetros: dni
  Devuelve: true si el DNI es válido (si tiene un formato adecuado y la letra 
	adecuada al número), false si no

****************************************************************************/

bool DNIValido(string dni){
	bool dni_valido;

	// Filtramos que el formato sea válido antes de comprobar la letra

	if(DNIFormatoCorrecto(dni)){
	
		if(DNILetraCorrecta(dni))
			dni_valido = true;

		else
			dni_valido = false;

	}else
		dni_valido = false;

	return dni_valido;
}

/****************************************************************************
	Función que comprueba si un NIE es válido o no

  Parámetros: nie
  Devuelve: true si el NIE es válido (si tiene un formato adecuado, si
	las letras iniciales son las contempladas y si la letra final se 
	corresponde con el número y la letra inicial), false si no

****************************************************************************/

bool NIEValido(string nie){
	bool nie_valido;

	// Filtramos que el formato sea válido antes de comprobar las letras

	if(NIEFormatoCorrecto(nie)){

		if(NIELetrasCorrectas(nie))
			nie_valido = true;

		else
			nie_valido = false;

	}else
		nie_valido = false;

	return nie_valido;
}

/****************************************************************************
	Función que pasa una cadena entera a mayúsculas

  Parámetros: cadena
  Devuele: la cadena en mayúsculas

****************************************************************************/

string CadenaAMayuscula(string cadena){
	string cadena_en_mayusculas;	

	// Recorre cadena en todos los caracteres, pasándolos a mayúscula
	// y concatenándolos en cadena_en_mayusculas

	for(int i = 0; i < cadena.length(); i++)
		cadena_en_mayusculas += toupper(cadena.at(i));

	return cadena_en_mayusculas;
}

/****************************************************************************
	Función que imprime mensaje en consola, lee una cadena de caracteres
	y la devuelve toda en mayúsculas

  Parámetros: mensaje
  Devuele: La lectura en mayúsculas

****************************************************************************/

string LeerEnMayuscula (string mensaje){
	string lectura;

	cout << mensaje;
	getline(cin, lectura);

	return CadenaAMayuscula(lectura);
}

/****************************************************************************/

int main(){
	
	const string TERMINADOR = "FIN";

	// Lectura y comprobación de DNIs

	string entrada_dni;

	cout << "Introduzca los DNIs a comprobar (FIN para terminar): " << endl;
	entrada_dni = LeerEnMayuscula("DNI: ");

	// Mientras que no se introduzca TERINADOR

	while(entrada_dni != TERMINADOR){
	
		// Comprueba si el DNI es válido

		if(DNIValido(entrada_dni))
			cout << "DNI valido." << endl;
	
		else
			cout << "DNI invalido." << endl;

		cout << endl;

		// Lee el siguiente DNI

		entrada_dni = LeerEnMayuscula("DNI: ");
	}
	
	cout << endl << endl;

	// Lectura y comprobación de NIEs

	string entrada_nie;

	cout << "----------------------------------------------------" << endl;
	cout << "Introduzca los NIEs a comprobar (FIN para terminar): " << endl;
	entrada_nie = LeerEnMayuscula("NIE: ");

	// Mientras que no se introuduzca TERMINADOR

	while(entrada_nie != TERMINADOR){

		// Comprueba que el NIE sea válido

		if(NIEValido(entrada_nie))
			cout << "NIE valido." << endl;
	
		else
			cout << "NIE invalido." << endl;

		cout << endl;

		// Lee el siguiente NIE

		entrada_nie = LeerEnMayuscula("NIE: ");
	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/CompruebaNIFNIE.cpp)

## 6. DescomposicionFactoresPrimos.cpp
Recordando el enunciado del ejercicio ```1. DescomposicionFactoresPrimos.cpp``` de la [Sesión VII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/Sesi%C3%B3n%2007.md) de prácticas:  
  
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
  
En esta ocasión, tendrá que escribir dos funciones ```void``` que calculen y muestren la descomposición en factores primos de ```n```:  
```void CalculaMuestra_DescFactPrimos_1(int n)```  
```void CalculaMuestra_DescFactPrimos_2(int n)```  
  
Y otras dos funciones para calcular la descomposición en factores primos de ```n``` devolviendo la expresión textual en un ```string```:  
```string Calcula_DescFactPrimos_1(int n)```  
```string Calcula_DescFactPrimos_2(int n)```  
  
La función **main** deberá emular el mismo funcionamiento del ejercicio de la Sesión VII.
```cpp
#include <iostream>

using namespace std;

/****************************************************************************
	Función que devuelve un string que contiene el resultado de la
	descomposición en factores primos de n

  Parámetros: n
  Devuelve: Una cadena que muestra los factores primos de n, con el formato:
					primo * primo * ... * primo

****************************************************************************/

string Calcula_DescFactPrimos_1 (int n){
	string resultado;	

	// Menor primo posible
	int divisor = 2;

	// Mientras que n tenga factores primos

	while(n != 1){
		// Mientras que divisor no sea un factor primo de n
		// pasamos a analizar el siguiente
		while(n % divisor != 0)
			divisor++;
	
		// Actualizamos n para buscar más factores primos
		n /= divisor;
	
		// Almacenamos el factor primo en resultado
		resultado += to_string(divisor);
	
		// Si no es el último factor primo, concatenamos el asterisco
		if(n != 1)
			resultado += " * ";
	} 

	return resultado;
}

/****************************************************************************
	Función que devuelve un string que contiene el resultado de la
	descomposición en factores primos de n

  Parámetros: n
  Devuelve: Una cadena que muestra los factores primos de n, con el formato:
  primo_1^veces_primo_1 * primo_2^veces_primo_2 * ... * primo_n^veces_primo_n

****************************************************************************/

string Calcula_DescFactPrimos_2 (int n){
	string resultado;	

	const string MULTIPLICAR = " * ";
	const char EXPONENTE = '^';

	int divisor = 2;
	int divisor_anterior = divisor;

	// Contador de veces seguidas que aparece un mismo factor primo
	int veces = 0;

	// Mientras que n siga teniendo factores primos
	while(n != 1){

		// Mientras que divisor no sea un factor primo de n
		// pasamos a analizar el siguiente
		while(n % divisor != 0)
			divisor++;

		// Actualizamos n para buscar más factores primos
		n /= divisor;

		if(divisor == divisor_anterior)
			veces++;		// Vamos contando factores iguales

		else{
			// Si el contador no es 0, almacenamos el factor
			// (Podría ser 0 si 2 no es factor primo de numero)

			if(veces != 0){
				if(veces == 1)	// No indicamos el exponente
					resultado += to_string(divisor_anterior) + MULTIPLICAR;

				else
					resultado += to_string(divisor_anterior) + EXPONENTE 
							+ to_string(veces) + MULTIPLICAR;
			}

			veces = 1;	// Reiniciamos el contador
		}		

		divisor_anterior = divisor;   // Actualizamos divisor_anterior

	}  // Cierra while(n != 1)

	// Si la última secuencia de factores primos no se almacenó,
	// la almacenamos ahora

	if(veces != 0){
		if(veces == 1)		// No indicamos el exponente
			resultado += to_string(divisor_anterior);

		else
			resultado += to_string(divisor_anterior) + EXPONENTE 
						+ to_string(veces);

	}

	return resultado;
}

/****************************************************************************
	Función que muestra en consola las dos cadenas que recibe, con el formato:
						cadena1 = cadena2

  Parámetros: cadena1, cadena2

****************************************************************************/

void MostrarCadenas(string cadena1, string cadena2){
	cout << cadena1 << " = " << cadena2 << endl;
}

/****************************************************************************
	Función que muestra en consola la cadena que devuelve la función
	Calcula_DescFactPrimos_1(int n)

  Parámetros: n

****************************************************************************/

void CalculaMuestra_DescFactPrimos_1 (int n){
	string descomposicion = Calcula_DescFactPrimos_1(n);

	MostrarCadenas(to_string(n), descomposicion);
}

/****************************************************************************
	Función que muestra en consola la cadena que devuelve la función
	Calcula_DescFactPrimos_2(int n)

  Parámetros: n

****************************************************************************/

void CalculaMuestra_DescFactPrimos_2 (int n){
	string descomposicion = Calcula_DescFactPrimos_2(n);

	MostrarCadenas(to_string(n), descomposicion);
}

/****************************************************************************/

int main(){
	
	int numero;

	// ENTRADAS

	bool entrada_invalida;

	do{

		cout << "Introduzca un entero mayor o igual que 0: ";
		cin >> numero;

		entrada_invalida = numero <= 0;

	}while(entrada_invalida);

	// SALIDAS

	cout << endl;

	CalculaMuestra_DescFactPrimos_1(numero);

	CalculaMuestra_DescFactPrimos_2(numero);

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/DescomposicionFactoresPrimos.cpp)  
Nótese que la implementación de las dos primeras funciones se hace a partir de las dos últimas. Esto es lo que se esperaría de una buena implementación para no repetir código.

# Ejercicios Opcionales
## 1. Narcisista.cpp 
Recordamos la definición de número _narcisista_ del ejercicio ```8. Narcisista.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
Un número de ```n``` dígitos se dice que es **narcisista** si se puede obtener como la suma de las potencias ```n```-ésimas de cada uno de sus dígitos. Por ejemplo, 153 y 8208 son números narcisistas, porque:
$$153 = 1³ + 5³ + 3³$$
$$8208 = 8⁴ + 2⁴ + 8⁴$$  
  
Construya un programa que nos indique si un número natural es narcisista (ahora, usando funciones).

## 2. LecturaReales.cpp
Este programa recuerda al ejercicio ```2. LecturaEnteros.cpp``` hecho al inicio de la sesión.  
   
Escriba las siguientes funciones para leer números reales:  
  
```double LeeReal(string titulo)```  
Lee y deuelve un dato ```double```. Si el valor leido no fuera ```double```, la función volvería a pedirlo hasta que se proporcionase un valor correcto. La lectura se etiqueta con ```titulo```.  
Ejemplos de entradas que no se consideran ```double``` son:  
```77 88```, ```0xA2```, ```1e5```.  
Se admiten entradas como:  
```.55```, ```22.```.  
  
```double LeeRealEnRango(string titulo, double menor, double mayor)```  
Lee y devuelve un dato ```double``` comprendido en el intervalo ```[menor, mayor]```. Si el dato leido no es ```double``` o no está en dicho intervalo, se volverá a solicitar al usuario hasta que sea un dato válido. La lectura se etiqueta con ```titulo```.  
  
```double LeeRealMayorOIgual(string titulo, double referencia)```  
Lee y devuelve un dato ```double``` mayor o igual que ```referencia```. Si el dato leido no es ```double``` o no es mayor o igual que ```referencia```, se volverá a solicitar al usuario hasta que sea un dato válido. La lectura se etiqueta con ```titulo```.  
  
En la función **main** deberá incluir código para probar el funcionamiento de estas tres funciones.

## 3. ToStringDoubleInt.cpp
Este programa recuerda al ejercicio ```3. FormateaString.cpp``` hecho al inicio de la sesión.  
  
Escriba dos funciones para convertir un número a su representación textual en forma de ```string```. Estas funciones presentarán una mejora sobre la función ```to_string``` de C++11.  
  
Recordamos que:  
```to_tring(23.51) devuelve 23.510000```  
```to_tring(23) devuelve 23```  
  
Esta función tiene algunos inconvenientes:  
1. Siempre proporciona 6 cifras decimales, redondeando la última.
2. No suprime los '0's finales en la parte decimal.
3. No permite especificar el número de casillas para la parte entera y decimal.  
  
Las funciones que se piden a continuación resuelven estos problemas:  
```string ToStringInt(int entero, int num_casillas, char relleno)```  
La función convierte el dato ```entero``` a un ```string``` con ```num_casillas``` casillas que contiene el valor textual de ```entero```. Las casillas no ocupadas por los dígitos de entero (en caso de haberlas) se rellenarán con el carácter ```relleno```: EL número quedará alineado a la derecha (los huecos a la izquierda).  
Si ```num_casillas``` es mayor que el número de casillas que se necesitan para representar ```entero```, se rellenan las casillas iniciales con ```relleno```. Si la representación de ```entero``` necesita más casillas que ```num_casillas```, se ocuparán dichas casillas.  
  
Ejemplo (```|``` representan el inicio y final del string):  
```ToStringInt(15, 6, ' ') devuelve |    15|```  
```ToStringInt(15, 6, '#') devuelve |####15|```  
```ToStringInt(155, 2, ' ') devuelve |155|```  
  
```string ToStringDouble(double real, int num_casillas, int decimales, char relleno)```  
Convierte ```real``` a un ```string``` que contiene su valor textual de acuerdo con el formato indicado según los valores de ```num_casillas``` (que actúa igual que en ```ToStringInt```), ```decimales``` (número de casillas para la parte decimal del resultado) y ```relleno``` (carácter que se usará para las casillas no ocupadas). El número quedará alineado a la derecha (los huecos, en caso de haberlos, a la izquierda).  
- Si ```num_casillas``` es mayor que el número de casillas que se necesita, se completará el inicio de la parte entera con ```relleno``` tantas veces como sea necesario.
- La cadena resultante tendrá ```decimales``` dígitos en la parte decimal. Si tiene que quedarse con menos de los que tuviera ```real```, se redondeará la última cifra decimal.
  1. Si ```decimales = 0``` no se considera el punto ni la parte decimal, obtendríamos un número entero.
  2. Si ```decimales``` es mayor que el que se necesita para la parte decimal, se copleta con ```0```s.  
  
Ejemplos (donde ```|``` indica el principio y final del ```string```):  
```ToStringDouble(3.49, 3, 1, ` `) devuelve |3.5|```  
```ToStringDouble(3.49, 4, 2, ` `) devuelve |3.49|```  
```ToStringDouble(3.496, 4, 2, ` `) devuelve |3.50|```  
```ToStringDouble(3.496, 4, 1, ` `) devuelve | 3.5|```  
```ToStringDouble(3.496, 4, 2, `*`) devuelve |*3.5|```  
```ToStringDouble(333.999999, 1, 0, ` `) devuelve |334|```  
```ToStringDouble(3, 4, 0, ` `) devuelve |   3|```  
```ToStringDouble(3.0, 1, 0, ` `) devuelve |3|```  
```ToStringDouble(3.0, 5, 2, ` `) devuelve |*3.00|```  
  
En la función **main** ha de incluir un programa que nos permita conocer el resultado de las funciones pasándoles cualquier parámetro que decida el usuario.

## 4. AdivinarAmpliacion.cpp
Recordando el enunciado del ejercicio ```4. AdivinarAmpliacion.cpp``` de la [Sesión VII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/Sesi%C3%B3n%2007.md) de prácticas:  
  
Diseñe un programa para jugar a adivinar un número. El programa generará un número aleatorio (entre ```MIN``` y ```MAX```) y el usuario tendrá que adivinarlo. En cada jugada el jugador introducirá un valor y el juego indicará si el número introducido por el jugador está por encima o por debajo del número a adivinar.  
  
Como reglas de parada, considerad que el usuario:
1. Haya acertado.
2. No quiera seguir jugando y en este caso usa un carácter especial ```TERMINADOR``` para poder abandonar la partida.  
   
Si no sabe cómo generar números aleatorios, le recomendamos ojear el siguiente [archivo](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/GenerarNumerosAleatorios.md).  
  
En esta ocasión, deberemos ampliar el programa de forma que cuando un juego termine, el programa pedirá si queremos volver a jugar o no.  
  
Al terminar (no se quiere jugar más), el programa mostrará cuántos juegos se han realizado (contabilizando los juegos abandonados como juegos válidos).  
  
En esta ocasión, debe implementar la función:  
```bool LeeOpcion2Alternativas()```  
Que imprime un mensaje en pantalla y lee una opción que sólo admite los caracteres ```s```, ```S```, ```n``` o ```N```. La función devuelve la opción escogida en un valor de tipo ```bool```.  
  
Use esta función para reescribir el código del ejercicio anterior, modularizándolo en funciones.

## 5. ProgresionGeom.cpp
Una _progresión geométrica_ es una sucesión de números reales que se define de forma recursiva mediante la expresión:  
$$a_1 = a_1$$
$$a_{i+1} = a_i \cdot r$$
  
Con la que obtenemos la sucesión:  
$$a_1, a_1\cdot r, a_1\cdot r², a_1\cdot r³, \ldots$$  
  
Se pide desarrollar un programa que nos pida probar las siguientes funciones a implementar (ha de pensar qué tipo de valor han de devolver y qué parámetros necesitan):
  
```SumaHasta```  
Que calcule la suma de los $k$ primeros valores de una progresión geométrica:  
$$\sum_{i=1}^k a_i$$  
  
```SumaHasta2```  
Desarrolle una nueva versión de la función anterior, donde ahora hará uso de la siguiente expresión para calcular la suma de los $k$ primeros términos:  
$$\sum_{i=1}^k a_i = \sum_{i=1}^k a_1\cdot r^{i-1} = a_1\cdot \dfrac{r^k -1}{r-1}$$
Para el cálculo de $r^k$ debe implementar una nueva función llamada ```Potencia```.  
  
```SumaHastaInfinito```  
Que calcule el límite de la serie (la "suma de infinitos términos") mediante la expresión:  
$$\sum_{i=1}^{\infty} a_i = \dfrac{a_1}{1-r}$$
Siempre y cuando $|r| < 1$ (incluir como precondición).  
  
```MultiplicaHasta```  
Que multiplique los $k$ primeros términos de la progresión geométrica mediante la expresión:  
$$\prod_{i=1}^k a_i = \prod_{i=1}^k a_1 \cdot r^{i-1} = \sqrt{(a_1\cdot a_k)^k}$$

## 6. SumaSerie.cpp
Dada la siguiente sucesión de números reales:  
$$a_i = \dfrac{(-1)^i(i²-1)}{2i}$$
Desarrolle una función ```Termino``` que nos proporcione el término $i$-ésimo de la sucesión anterior. Debe pensar qué parámetros debe recibir la función y qué tipo de variable debe devolver. No puede usar la función ```pow```.  
  
Escriba a continuación una nueva función ```SumaHasta```que nos permita calcular la suma de los $k$ primeros términos de la sucesión anterior, usando en su implementación la función ```Termino```. 
  
Debe desarrollar en la función **main** un programa que permita al usuario decidir el valor de $k$ y mostrar en pantalla el resultado de:  
$$\sum_{i=1}^k a_i$$

## 7. MultiplicacionRusa.cpp
Recordando el enuciado del ejercicio ```1. MultiplicacionRusa.cpp``` de la [Sesión VII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/Sesi%C3%B3n%2007.md) de prácticas:  
  
El algoritmo de la multiplicación rusa es una forma distinta de calcular la multiplicación de dos números enteros $n \cdot m$. Para ello, este algorimo va multiplicando por 2 el multiplicador $m$ y dividiendo (sin decimales) por dos el multiplicando $n$ hasta que $n$ tome el valor 1 y suma todos aquellos multiplicadores cuyos multiplicandos sean impares.  
  
Por ejemplo, para multiplicar $37 \cdot 12$, se harían las siguiente iteraciones:  
  
| Iteración | Multiplicando | Multiplicador |
|-----------|---------------|---------------|
| 1         | **37**        | **12**        |
| 2         | 18            | 24            |
| 3         | **9**         | **48**        |
| 4         | 4             | 96            |
| 5         | 2             | 192           |
| 6         | **1**         | **384**       |
  
$37 \cdot 12 = 12 + 48 + 384 = 444$  
  
Cree un programa que lea dos enteros y calcule su producto con este algoritmo.  
  
Repítalo usando ahora funciones para modularizar la solución.

## 8. Parking.cpp
Recordando el enunciado del ejercicio ```3. ParkingLimitadoDinero.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
Recordando las tarifas de parking del ejercicio ```4. Parking.cpp``` de la [Sesión IV](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/Sesi%C3%B3n%2004.md) de prácticas:  
```Desde el minuto 0 al 30: 0.0412€ por minuto.```  
```Desde el minuto 31 al 90: 0.0370€ por minuto.```  
```Desde el minuto 91 al 120: 0.0311€ por minuto.```  
```Desde el minuto 121 al 660: 0.0305€ por minuto.```  
```Desde el minuto 661 al 900: 0.0270€ por minuto.```  
```Desde el minuto 901 hasta máximo 24h: se deberán abonar 35€.```  
  
Escriba un programa que lea la hora actual (hora y minuto) y una cantidad de dinero. El programa nos indicará cuántos minutos podremos estar estacionados como máximo si tenemos dicho dinero de presupuesto; además de la hora límite (hora y minuto) a la que tendremos que sacar el coche del parking.  
  
Reescriba ahora la solucion al problema empleando funciones para su modularización.

## 9. DecToBin.cpp
Recordando el enunciado del ejercicio ```6. DecToBin``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
Escriba un programa que convierta números naturales (o cero) a binario, usando un ```string``` para representar un número en binario, mediante los carácteres '0' y '1'. El programa pedirá inicialmente un número de bits (```n```), que tendrán los valores binarios con los que se va a trabajar.  
  
Dado ```n```, los números válidos estarán comprendidos en el intervalo $[0, 2^n-1]$ (todos los que pueden representarse con ```n``` bits o menos).  
  
Si fuera necesario, se rellenará con '0' a la izquierda del primer '1'.  
Por ejemplo, si ```n = 8``` y se quiere convertir el valor 11, se generará el ```string``` ```00001011```; y al convertir el valor 128 se genera el ```string``` ```10000000```.  
  
Ahora, desarrolle un programa que un número natural (o 0) ```n``` y otro número natural ```t``` ($t \geq 2^n-1$); y muestre la representación binaria de todos los valores $0 \leq x \leq n$. Con el siguiente formato (donde en la columna ```estricto``` mostramos la representación usando sólo los bits que necesite el número).  
  
Un ejemplo de ejecución para ```n = 11``` y ```t = 10```:  
  
```Maximo valor a codificar en binario: 11```  
```Numero de bits: 10```  
  
```|    x | Estricto | 10 bits   |```  
```|------|----------|-----------|```  
```|    0 |        0 | 0000000000|```  
```|    1 |        1 | 0000000001|```  
```|    2 |       10 | 0000000010|```  
```|    3 |       11 | 0000000011|```  
```|    4 |      100 | 0000000100|```  
```|    5 |      101 | 0000000101|```  
```|    6 |      110 | 0000000110|```  
```|    7 |      111 | 0000000111|```  
```|    8 |     1000 | 0000001000|```  
```|    9 |     1001 | 0000001001|```  
```|    10|     1010 | 0000001010|```  
```|    11|     1011 | 0000001011|```  
  
Esta tarea la realizará una función:  
```string DecToBin(int num_decimal, int num_bits)```  
QUe recibe el número a codificar, ```num_decimal``` y el número de bits ```num_bits``` y devolverá un string por caracteres ```0``` o ```1``` que contiene la representación binaria de ```num_decimal``` con ```num_bits```. Si ```num_bits``` es menor que el número mínimo de bits que se necesitan para representar el número, se ignorará ```num_bits``` y se suarán los bits necesarios.  
Por ejemplo:  
```DecToBin(35, 8) devuelve 00100011```  
```DecToBin(35, 4) devuelve 100011```  

## 10. BinToDec.cpp
Continuando con el problema planteado en el ejercicio ```7. BinToDec.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
Escriba un programa que muestre el valor decimal de un valor dado en binario. El programa pedirá el valor binario, que se leerá sobre un dato ```string```, se calculará su valor decimal, que se guardará en un entero y se mostrará el resultado.  
  
A continuación, se pide reescribir el programa implementando las siguientes funciones:  
  
```EsNumBinario```  
Que compruebe si un dato ```string``` contiene la representación binaria de un número positivo o cero (esto es, que la secuencia de caracteres contenga exclusivamente ```0``` y ```1```).  
  
```SimplificaBinario```  
Que dado un ```string``` que sea un número positivo o cero en binario, elimine los ```0```s que se incluyen delante del primer ```1```.  
Ejemplo:  
```SimplificaBinario(0010) devuelve 10```  
  
```BinToDec```  
Que dado un ```string``` que sea un número positivo o cero en binario, devuelva su valor en decimal mediante una variable ```int```.

## 11. MaximaVelocidadImputada.cpp
Recordando el enunciado del ejercicio ```5. ConsultaMulta.cpp``` de la [Sesión V](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2005/Sesi%C3%B3n%2005.md) de prácticas:  
  
En este ejercicio queremos determinar la sanción a aplicar en una autovía, cuyo límite de velocidad es 120 Km/h. En la siguiente tabla se muestra la velocidad del vehículo y la sanción correspondiente (número de puntos del carnet de conducir que se restan y la multa en euros)  
  
```(120, 150] --> 0, 100```  
```(150, 170] --> 2, 300```  
```(170, 180] --> 4, 400```  
```(180, 190] --> 6, 500```  
```(190, ...) --> 6, 600```  
  
Escriba un programa que lea matrículas de vehículos válidas (una matrícula de un vehículo es válida si está representada por 7 caracteres de los cuales los 4 primeros son dígitos y los 3 últimos letras mayúsculas del alfabeto inglés) y la velocidad registrada por el radar a cada una de dichas matrículas, hasta leer una matrícula inválida. El programa deberá calcular qué sanción se le aplica a cada vehículo (o si no se le aplica ninguna sanción)
