# Fundamentos de Programación. Sesión VI de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión VI de prácticas.

En esta sesión, se **introduce** el uso de las **estructuras cíclicas**, como bucles **while**, **do while** y **for**, por lo que su uso de aquí en adelante estará permitido. Como dificultad extra, ahora en vez de finalizar el programa cuando los datos no sean válidos, se **deberán pedir continuamente** al usuario hasta que lo sean.

## 1. SecOrdenadaMasLarga.cpp
Construya un programa que calcule cuándo se produjo la mayor secuencia de días consecutivos con temperaturas crecientes. El programa leerá una secuencia de reales representando temperaturas, hasta que se introduzca un valor fuera de un rango establecido, y debe calcular la subsecuencia de números ordenada, de menor a mayor, de mayor longitud. El programa nos debe decir la posición donde comienca la subsecuencia y su longitud.  
  
Por ejemplo, ante la siguiente entrada:  
```17.2 17.3 16.2 16.4 17.1 19.2 18.9 -1```  
  
El programa debe indicar que la mayor subsecuencia empieza en la posición ```3``` (en el ```16.2```) y tiene longitud ```4``` (termina en ```19.2```).  
  
El rango de validez de una temperatura quedará determinado por el intervalo ```[MIN_TEMP_VALIDA, MAX_TEMP_VALIDA]```. Deberá fijar dichas constantes según su criterio. Es posible también que el primer valor leído sea incorrecto (esté fuera de rango), por lo que deberá introducir además una constante ```MIN_LONG_VALIDA``` (fije también su valor con un número que considere adecuado), de forma que si la subsecuencia creciente de temperaturas más larga no tiene una longitud superior a dicha constante, el programa deberá indicar que la subsecuencia más larga tiene una longitud no válida.
```cpp
#include <iostream>

using namespace std;

int main(){
	
	const double MIN_TEMP_VALIDA = -50, MAX_TEMP_VALIDA = 50;
	const int MIN_LONG_VALIDA = 3;

	double temperatura;

	const string mensaje = "Temperatura: ";

	// ENTRADAS Y CÁLCULOS

	// Solicita la primera temperatura

	cout << "Introduzca todas las temperaturas registradas:" << endl;
	cout << "(Si la temperatura no esta entre " << MIN_TEMP_VALIDA << " y " 
		 << MAX_TEMP_VALIDA << " la lectura de datos termina)" << endl << endl;

	cout << mensaje;
	cin >> temperatura;

	// Posicion de inicio y longitud de la mayor subsecuencia
	int inicio = 0, longitud = 0;

	// Posicion de inicio y longitud de la subsecuencia que se está procesando
	int inicio_temporal = 0, longitud_temporal = 0;

	// Posicion de la temperatura que se está procesando
	int posicion = 0;

	// La inicializamos para que la primera temperatura (si es válida)
	// comience una nuea subsecuencia.
	double temp_anterior = 51;

	while(temperatura >= MIN_TEMP_VALIDA && temperatura <= MAX_TEMP_VALIDA){
	
		posicion++;		// Analizamos la siguiente temperatura

		// Si la temperatura sigue perteneciendo a la subsecuencia actual
		if(temperatura >= temp_anterior){
			
			longitud_temporal++;		// Se aumenta el número de elementos

		}else{		// Si no, se comienza a procesar una nueva subsecuencia

			// Si la subsecuencia anterior tenía más elementos que la mayor
			// subsecuencia hasta el momento, esta se guarda como mayor
			if(longitud_temporal > longitud){

				longitud = longitud_temporal;
				inicio = inicio_temporal;

			}		

			// En cualquier caso, comenzamos a procesar una nueva subsecuencia

			longitud_temporal = 1;

			inicio_temporal = posicion;

		}

		// Solicitamos la siguiente temperatura a procesar

		temp_anterior = temperatura;

		cout << mensaje;
		cin >> temperatura;
	}

	// Si la última subsecuencia procesada era mayor que la máxima hasta el
	// momento, se guarda como mayor

	if(longitud_temporal > longitud){

		longitud = longitud_temporal;
		inicio = inicio_temporal;

	}	

	// SALIDAS

	cout << endl << endl;

	if(longitud == 0)	// Primer valor fuera del intervalo adecuado
		cout << "La primera temperatura no es valida." << endl;

	// Longitud no valida
	else if(longitud < MIN_LONG_VALIDA)
		cout << "La subsecuencia mas larga tiene una longitud no valida " 
			 << "(menor que " << MIN_LONG_VALIDA << " elementos)." << endl;

	else{	// Todo ha ido bien, se imprimen las salidas

		cout << "La mayor subsecuencia:" << endl;
		cout << "\tEmpieza en la posicion " << inicio << "." << endl;
		cout << "\tTiene longitud " << longitud << "." << endl;

	}

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/SecOrdenadaMasLarga.cpp)

## 2. RLE.cpp
El método RLE (Run Length Encoding) codifica una secuencia de datos formada por series de valores idénticos consecutivos como una secuencia de parejas de número-carácter (indica el número de veces que se repite dicho carácter de forma consecutiva). Se trata de un mecanismo de compresión de datos (zip) sin pérdidas.  
  
Realice un programa que lea una secuencia de caracteres terminada con el carácter "." y la codifique (sin incluir el ".") mediante el método RLE. Se aconseja ejecutar el programa con redirección de entrada.  
  
Por ejemplo, ante la entrada:  
```A A A X X X X X D D D D D D Q .```  
  
El programa deberá imprimir:  
```3A 5X 6D 1Q```
```cpp
#include <iostream>

using namespace std;

int main(){
	
	const char TERMINADOR = '.';

	// ENTRADAS

	char caracter;

	cout << "A continuacion, introduzca la sucesion de caracteres que desea " 
		 << "codificar:" << endl;
	cout << "Para finalizar la introducción de datos, introduzca un \"" 
		 << TERMINADOR << "\"." << endl;

	cout << endl;

	cin >> caracter;

	// ENTRADAS Y CÁLCULOS

	// Variables útiles para el bucle

	int contador = 0;

	char caracter_anterior = caracter;

	string salida;		// Cadena cifrada

	// Bucle que permite seguir leyendo la entrada

	while(caracter != TERMINADOR){

		// Si el caracter es igual al anterior, sigue contando
		if(caracter == caracter_anterior)
			contador++;

		else{

			// Almacena la cuenta de los caracteres anteriores
			salida += to_string(contador) + " " + caracter_anterior + "  ";

			// Comienza una nueva cuenta
			contador = 1;

		}

		// Actualiza caracter_anterior
		caracter_anterior = caracter;

		// Lee el nuevo caracter
		cin >> caracter;
	
	}

	// Guarda la última sucesión de caracteres introducida en caso de que 
	// el primer caracter no sea TERMINADOR
	if(contador != 0)
		salida += to_string(contador) + " " + caracter_anterior;

	// SALIDAS

	cout << endl;

	// Si el primer caracter era TERMINADOR
	if(salida == "")
		cout << "No se introdujo ninguna cadena de caracteres" << endl;

	else{
		cout << "La cadena cifrada: " << endl;
		cout << salida << endl;
	}

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/RLE.cpp)

## 3. Adivinar.cpp
Diseñe un programa para jugar a adivinar un número. El programa generará un número aleatorio (entre ```MIN``` y ```MAX```) y el usuario tendrá que adivinarlo. En cada jugada el jugador introducirá un valor y el juego indicará si el número introducido por el jugador está por encima o por debajo del número a adivinar.  
  
Como reglas de parada, considerad que el usuario:
1. Haya acertado.
2. No quiera seguir jugando y en este caso usa un carácter especial ```TERMINADOR``` para poder abandonar la partida.  
   
Si no sabe cómo generar números aleatorios, le recomendamos ojear el siguiente [archivo](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/GenerarNumerosAleatorios.md).
```cpp
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
	
	const int MIN = 1, MAX = 100;
	const int NUM_VALORES = MAX - MIN + 1; // Valores entre MIN y MAX
	const int TERMINADOR = -1;

	int numero;

	// ENTRADAS Y CÁLCULOS

	const string MENSAJE = "Intente adivinar el numero: ";

	cout << "Si no quiere seguir jugando, introduzca \"" << TERMINADOR << "\"." << endl << endl;
	cout << MENSAJE << "(entre " << MIN << " y " << MAX << ") ";

	cin >> numero;

	// Generamos el número aleatorio:

	time_t t;
	srand(time(&t));	// Inicia el generador de números aleatorios

	// Almacenamos el número aleatorio, modificándolo para que esté en el
	// intervalo [MIN, MAX]
	int adivinar;
	adivinar = (rand() % NUM_VALORES) + MIN;

	// Bucle que permite seguir jugando

	while(numero != TERMINADOR && numero != adivinar){
		
		cout << endl;

		// Imprime si el número a adivinar es mayor o menor que el introducido

		if(numero > adivinar)
			cout << "El numero es menor que " << numero << "." << endl;

		else
			cout << "El numero es mayor que " << numero << "." << endl;

		// Solicita el siguiente número del jugador

		cout << MENSAJE;
		cin >> numero;

	}

	// SALIDAS

	cout << endl << endl;

	// Si el jugador se ha rendido
	if(numero == TERMINADOR)
		cout << "El numero era " << adivinar << "." << endl;

	// Si no, es que ha acertado el número
	else
		cout << "Felicidades, has acertado, el numero era " << adivinar << "." << endl;

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Adivinar.cpp)

## 4. CDFGaussiana.cpp
Estamos interesados en obtener el área que cubre la función gaussiana en un intervalo dado. Si consideramos el intervalo $]-\infty, x]$, el valor del área de la región que queda bajo la curva de $g(x)$ (siendo $g$ la función gaussiana) se calcula con la _distribución acumulada_ (_cumulative distribution function_ o CDF) en el punto $5x$:
$$CDF(x) = \int_{-\infty}^x g(x)~dx$$
Puede obtenerse un valor aproximado de $CDF(x)$ como la suma de valores de $g(x)$ empezando por valores alejados de la media (y menores que ella). Esto es, en vez de resolver la integral, estaremos interesados en aproximarla con un sumatorio de rectángulos de anchura relativamente pequeña.  
  
Escriba un programa que calcule $CDF(x)$. El programa debe pedir los parámetros que definen una función gaussiana ($\mu$ y $\sigma$) y el valor de la abscisa $x$, para el que se va a calcular $CDF(x)$. Para el cálculo de $CDF(x)$, realizaremos una suma. Debemos concretar de qué forma la realizaremos:
1. Necesitamos un valor inicial para $x$ (úsese $\mu - 3\sigma$).
2. Un salto entre dos valores consecutivos de $x$ (use una constante).  
   
Recordamos la expresión de la función $g(x)$:
$$g(x) = \dfrac{1}{\sigma\sqrt{2\pi}} e^{\left[\dfrac{-1}{2}\left(\dfrac{x-\mu}{\sigma}\right)²\right]}$$
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main(){
	
	const double PI = 6 * asin(0.5);

	const double SALTO = 0.1;

	double mu, sigma, x;

	bool error_sigma = false;

	// ENTRADAS  ***********************************************************

	// Se asegura de que sigma no sea 0

	do{
		// Imprime que sigma debe ser mayor que 0, en caso de haber introducido
		// un valor de sigma menor o igual a 0
		if(error_sigma)
			cout << endl << "La desviacion tipica debe ser mayor que 0." 
				 << endl;

		cout << "Desviacion Tipica: ";
		cin >> sigma;

		error_sigma = sigma <= 0;

	}while(error_sigma);

	// Mu (la media) y x pueden adoptar el valor de cualquier real

	cout << endl;
	cout << "Media: ";
	cin >> mu;

	cout << endl;
	cout << "El valor de x (abscisa) para CDF(x): ";
	cin >> x;

	// CÁLCULOS  *********************************************************

	// Calculamos la primera parte de la gaussiana, no depende de la abscisa

	double parte1_gaussiana = 1 / (sigma * sqrt(2 * PI));

	// La abscisa donde comenzamos la sumatoria

	double x_inicial = mu - 3 * sigma;

	// Cálculo de la sumatoria de las alturas, desde x_inicial hasta el x 
	// especificado por el usuario, realizando saltos de SALTO entre los 
	// sumandos. Usamos la variable "x sub i" en el bucle

	double sumatoria_alturas = 0;

	for(double xi = x_inicial; xi <= x; xi += SALTO){
		
		// Segunda parte de la gaussiana, depende de xi:

		double parte2_gaussiana = exp(-0.5 * pow((xi - mu) / sigma, 2));

		// Obtenemos el valor de la gaussiana en xi

		double gaussiana = parte1_gaussiana * parte2_gaussiana;

		// Vamos realizando la sumatoria de las alturas

		sumatoria_alturas += gaussiana;

	}

	// Multiplicamos la base de los rectángulos por la sumatoria de las alturas
	// para obtener la sumatoria del área de los rectángulos

	double sumatoria_areas = SALTO * sumatoria_alturas;

	// SALIDA  ********************************************************

	cout << endl << endl;
	cout << "CDF(" << x << ") = " << sumatoria_areas << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/CDFGaussiana.cpp)

## 5. AproxRaizCuadrada.cpp
El cálculo de la raíz cuadrada puede realizarse con la función ```sqrt``` disponible en la librería ```cmath```. Además, pueden emplearse aproximaciones numéricas para evitar śu cálculo con la función anteriormente mencionada. Puede verse un método muy sencillo en el siguiente enlace: [https://www.youtube.com/watch?v=sOSdi9z8S6E](https://www.youtube.com/watch?v=sOSdi9z8S6E).  
  
Impleméntelo para el cálculo de datos ```double```.  
  
Implemente a continuación una estimación basada en la proporcionalidad entre triángulos. Se trata de aproximar la función $y = \sqrt{x}$ por ractas en los tramos determinados por lso valores con raíces exactas. Consideraremos las raíces exactas: ```0, 1, 4, 9, 16``` con abscisas ```0, 1, 2, 3, 4``` respectivamente. Consideraremos la función resultante de unir los segmentos ```(0,0)```, ```(1,1)```, ```(2,4)```, ```(3,9)```, ```(4,16)```, que aproxima a $y = \sqrt{x}$. Si tomamos un valor de abscisa cualquiera entre 1 y 16, podremos calcular su imagen con la función previamente definida, que aproxima a la raíz cuadrada.  
  
Impleméntelo para el cálculo de datos ```dobule```.  
  
Finalmente, muestre una comparativa en la que se muestran los valores estimados por los dos métodos y por la función ```sqrt``` de ```cmath``` para valores de $x$ desde 0 a 16 con saltos de 0.5.
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
	
	const double MIN = 0, MAX = 16;
	const double SALTO = 0.5;

	double numero;

	bool error_numero = false;

	// ENTRADA  *******************************************************

	do{
		// Muestra al usuario por qué su entrada no es válida
		if(error_numero)
			cout << endl << "El numero debe ser un real positivo." << endl;

		cout << "Raiz cuadrada de: ";
		cin >> numero;

		error_numero = numero < 0;

	}while(error_numero);

	// CÁLCULOS Y SALIDAS **********************************************

	// Para no repetir código, dentro del bucle de la tabla que imprimimos al
	// final incluimos el cálculo de la raíz de numero por los tres métodos,
	// de forma que la primera vuelta del bucle está dedicada al cálculo
	// de su raíz y el resto del bucle está dedicado a crear la tabla.

	// El bucle tiene tantas vueltas como debe tener para crear la tabla
	// mas una al inicio

	for(double i = MIN - SALTO; i <= MAX; i += SALTO){

		double x;		// Real al que se le hace la raíz cuadrada

		// Si es la primera vuelta del bucle, le hacemos la raíz a numero
		if(i == MIN - SALTO)
			x = numero;

		// Si no, calculamos la raíz del correspondiente número de la tabla
		else
			x = i;

		// Metodo 1:  ---------------------------------------------------

		// 1.- Buscamos el número entero al cuadrado que más se aproxime a x:

		int cuadrado_superior = 1;
	
		// Buscamos el cuadrado superior
		while(cuadrado_superior * cuadrado_superior <= x){
			cuadrado_superior++;
		}
	
		// Calculamos el cuadrado inferior 
		int cuadrado_inferior = cuadrado_superior - 1;
	
		// Calculamos la distancia de cada uno a x
		double distancia_inferior = x - cuadrado_inferior * cuadrado_inferior;
	
		double distancia_superior = cuadrado_superior * cuadrado_superior - x;

		// El entero al cuadrado más proximo es aquel cuyo cuadrado guarda 
		// menor distancia con x
		int proximo = (distancia_inferior < distancia_superior)?
						cuadrado_inferior : cuadrado_superior;
	
		// 2.- Calculamos la raiz de x, aplicando la fórmula del enunciado
		// (La fórmula del vídeo)
	
		double raiz1;
	
		// proximo es el denominador
		if(proximo != 0)
			raiz1 = proximo + abs(x - proximo * proximo) / (2 * proximo);

		// Le damos un valor por defecto a aquellos números a los que no se les 
		// puede aplicar el método
		else	
			raiz1 = 0;	

		// Metodo 2:  -----------------------------------------------------

		// 1.- Buscamos los cuadrados exactos más cercanos, que ya obtuvimos
		// en el método 1:
		// sqrt(cuadrado_inferior^2) <= sqrt(x) <= sqrt(cuadrado_superior^2)

		// Usamos nuevas variables para simplificar los cálculos:

		int a = cuadrado_inferior;
		int b = cuadrado_superior;

		// 2.- Existe una relación entre la distancia de a^2 y b^2 y entre
		// la distancia de a y b (calculamos las distancias):

		int distancia_a_b_2 = (b * b) - (a * a);

		int distancia_a_b = b - a;

		// Esta misma relación es la que guarda la distancia de a^2 y x 
		// entre la distancia de a y la raíz de x

		double distancia_a_2_x = x - (a * a);

		// Por una regla de tres, obtenemos que:
		// distancia_raiz_x_a = distancia_a_2_x * distancia_a_b 
		//								/ distancia_a_b_2 
		// Luego:
		// sqrt(x)-a = distancia_a_2_x * distancia_a_b / distancia_a_b_2
		// Despejando:

		double raiz2 = (distancia_a_2_x * distancia_a_b / distancia_a_b_2) + a;

		// Metodo 3:

		double raiz3 = sqrt(x);

		// SALIDAS   ------------------------------------------------------

		// Si es la primera vuelta del bucle, imprimimos los resultados de la 
		// raiz de numero:
		if(i == MIN - SALTO){

			// Formateo de la consola
	
			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
		
			cout << setw(5) << setprecision(3);
		
			cout << endl << "La raiz cuadrada de " << numero << " es:" << endl;
			cout << "\tMetodo 1: " << raiz1 << endl;
			cout << "\tMetodo 2: " << raiz2 << endl;
			cout << "\tMetodo 3: " << raiz3 << endl;

			// Después de la primera vuelta del bulce se procesará e imprimirá
			// La tabla, por lo que ya podemos mostrar su cabecera:

			cout << endl << endl;
		
			cout << "Raices desde " << MIN << " hasta " << MAX 
				 << " con saltos de " << SALTO << "." << endl;
		
			cout << endl;
		
			cout << "                |	Metodo 1 |	Metodo 2     |	Metodo 3 |" 
				 << endl;
			cout << "      Numero    |	Formula  |	Triangulos   |	sqrt(x)  |" 
				 << endl;
		
			cout << endl;
	
		}

		else{
	
			// SALIDAS TABLA

			cout << "	" << setprecision(1) << x << "		" 
				 << setprecision(3) << raiz1 << "		" << raiz2 << "		" 
				 << raiz3 << endl;
	
			cout << endl;

		}

	}

	// A partir de la tabla, podemos observar que el segundo método es más 
	// exacto que el primero

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/AproxRaizCuadrada.cpp)

## 6. DecToBin.cpp
Escriba un programa que convierta números naturales (o cero) a binario, usando un ```string``` para representar un número en binario, mediante los carácteres '0' y '1'. El programa pedirá inicialmente un número de bits (```n```), que tendrán los valores binarios con los que se va a trabajar.  
  
Dado ```n```, los números válidos estarán comprendidos en el intervalo $[0, 2^n-1]$ (todos los que pueden representarse con ```n``` bits o menos).  
  
Si fuera necesario, se rellenará con '0' a la izquierda del primer '1'.  
Por ejemplo, si ```n = 8``` y se quiere convertir el valor 11, se generará el ```string``` ```00001011```; y al convertir el valor 128 se genera el ```string``` ```10000000```.
```cpp
#include <iostream>
#include <cmath>	//Para poder usar pow()

using namespace std;

int main(){
	
	int decimal;
	int n; 			//Número de bits

	bool error_n = false;
	bool error_decimal = false;

	// ENTRADAS CON FILTROS **************************************************

	do{
		// Si hubo un error, lo imprime
		if(error_n)
			cout << endl << "Error: el numero de bits debe de ser mayor que 0."
				 << endl;
			
		// Solicita el número de bits
		cout << "Numero de bits: ";
		cin >> n;

		// Comprueba si es un número válido de cifras binarias
		error_n = n <= 0;

	}while(error_n);

	// Número decimal máximo que se puede reprsentar con n bits
	int maximo = pow(2, n) - 1;

	do{
		// Si hubo un error, lo imprime
		if(error_decimal)
			cout << endl << "Error: el dato debe estar en el intervalo [0," 
				 << maximo << "]." << endl;

		// Solicita el número decimal
		cout << "Numero entero positivo entre [0," << maximo << "]: ";
		cin >> decimal;

		// Comprueba si es válido o no
		error_decimal = decimal < 0 || decimal > maximo;

	}while(error_decimal);

	// CÁLCULOS  **********************************************************

	// Cálculo del número binario

	string n_binario;	// decimal en binario

	int auxiliar = decimal; // Trabajamos con una copia de decimal
	
	while(auxiliar != 0) {
		// Comparar último bit con 1  
		
		if (auxiliar & 1) 
			n_binario = "1" + n_binario;  	// Es 1
		else 
			n_binario = "0" + n_binario;	// Es 0
		
		auxiliar >>= 1; // Desplazar a la derecha el auxiliar
	}

	// Ajustar los bits para representar n bits

	if(n_binario.length() != n){		// Si el número de bits no es igual

		// Se calcula cuantos ceros le faltan al número binario delante
		int diferencia = n - n_binario.length();

		// Generamos un string de tantos ceros como bits le falten al
		// número binario para llegar a n bits

		string str_ceros;

		for(int i = 0; i < diferencia; i++){

			str_ceros += '0';

		}

		// Cancatenamos a ese número de ceros el string con el número binario
		// obteniendo finalmente el valor deseado

		n_binario = str_ceros + n_binario;
	}

	// SALIDA  *************************************************************
	
	cout << endl;
	cout << decimal << " en binario con " << n << " bits es " << n_binario << "." << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/DecToBin.cpp)

## 7. BinToDec.cpp
Escriba un programa que muestre el valor decimal de un valor dado en binario. El programa pedirá el valor binario, que se leerá sobre un dato ```string```, se calculará su valor decimal, que se guardará en un entero y se mostrará el resultado.
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main(){
	
	string binario;
	int decimal = 0;

	bool error_lectura = false;

	// ENTRADAS CON FILTROS Y CÁLCULOS

	do{
		// Imprime que se ha introducido un dato incorrecto, en dicho caso
		if(error_lectura)
			cout << endl << "Error: debe introducir un numero binario entero."
				 << endl;

		// Hasta que no se detecte que ha habido un error, no ha habido ninguno
		error_lectura = false;

		// Se solicita el número binario al usuario
		cout << "Numero binario: ";
		cin >> binario;

		// INEFICIENTE: USAR WHILE

		// Se comprueba que la cadena introducida sólo tenga '0' y '1'
		for(int i = 0; i < binario.length(); i++){

			// Si no se ha detectado ningún error, se busca uno
			if(!error_lectura)

				// Si un caracter es distinto de 0 o 1, hay un error
				error_lectura = binario.at(i) != '0' && binario.at(i) != '1';

		}

	}while(error_lectura);

	// CÁLCULOS

	int exponente = 0;
	
	// Recorre el número binario, comenzando por su bit menos significativo
	for(int i = binario.length()-1; i>= 0; i--){

		// En caso de haber un 1 en dicha posición, se le suma al número 
		// decimal 2^exponente
		if(binario.at(i) == '1')
			decimal += pow(2, exponente);

		// Aumentamos el exponente para analizar la siguiente cifra
		exponente++;

	}

	// SALIDA

	cout << endl;
	cout << binario << " en decimal es " << decimal << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/BinToDec.cpp)

# Ejercicios Opcionales
## 1. Divisores.cpp
Realice un programa que lea desde teclado un número natural e imprima en pantalla todos sus **divisores**. Para obtener los divisores, basta recorrer todos lso enteros menores que el valor introducido y comprobar si lo dividen.
```cpp
#include <iostream>

using namespace std;

int main(){
	
	int numero;

	bool error_lectura = false;

	// ENTRADA

	do{
		// Imprime al usuario por qué su entrada no es válida.
		if(error_lectura)
			cout << endl << "Debe introducir un numero entero positivo." 
				 << endl;

		cout << "Numero entero positivo: ";
		cin >> numero;

		error_lectura = numero <= 0;

	}while(error_lectura);

	// CÁLCULOS

	string salida;	// Donde se van almacenando todos los divisores 

	// Recorre todos los enteros del 1 a numero
	for(int i = 1; i <= numero; i++){

		// Si el resto es 0, es un divisor
		if(numero % i == 0)
			// Lo añadimos a la lista de divisores
			salida += " " + to_string(i);

	}

	// SALIDA

	cout << endl;
	cout << "Los divisores de " << numero << " son:" << salida << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Divisores.cpp)

## 2. InteresDoblar.cpp

## 3. ParkingLimitadoDinero.cpp
Recordando las tarifas de parking del ejercicio ```4. Parking.cpp``` de la [Sesión IV](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/Sesi%C3%B3n%2004.md) de prácticas:  
```Desde el minuto 0 al 30: 0.0412€ por minuto.```  
```Desde el minuto 31 al 90: 0.0370€ por minuto.```  
```Desde el minuto 91 al 120: 0.0311€ por minuto.```  
```Desde el minuto 121 al 660: 0.0305€ por minuto.```  
```Desde el minuto 661 al 900: 0.0270€ por minuto.```  
```Desde el minuto 901 hasta máximo 24h: se deberán abonar 35€.```  
  
Escriba un programa que lea la hora actual (hora y minuto) y una cantidad de dinero. El programa nos indicará cuántos minutos podremos estar estacionados como máximo si tenemos dicho dinero de presupuesto; además de la hora límite (hora y minuto) a la que tendremos que sacar el coche del parking.

## 4. Carrera.cpp
Para controlar los tiempos que emplean los corredores de una carrera popular se desea disponer de un programa muy sencillo que se irá ampliando en sucesivas versiones. En esta primera versión el programa empezará pidiendo la hora de inicio de la carrera (hora, minuto y segundo) y la distancia.  
  
Después, para cada corredor que llega a meta (por orden de llegada) se pide el número de dorsal y la hora de llegada (hora, minuto y segundo). Tras leer estos datos, el programa mostrará el tiempo que ha empleado en completar la carrera (horas, minutos y segundos) y su ritmo (en km/h y en minutos/km).  
  
El programa finalizará cuando al solicitar el número de dorsal se introduzca un valor negativo.

## 5. AproxPiMadhava.cpp
En el siglo XIV, el matemático indio Madhava de Sangamagrama calculó el arcotangente a través de un desarrollo de Taylor:
$$\arctan(x) = \sum_{i=0}^{\infty} \dfrac{(-1)^i x^{2i+1}}{2i+1}$$
Sustituyendo $x = \dfrac{1}{\sqrt{3}}$, obtenemos:
$$\arctan\left(\dfrac{1}{\sqrt{3}}\right) = \dfrac{\pi}{6} = \sum_{i=0}^{\infty} \dfrac{(-1)^i \left(\dfrac{1}{\sqrt{3}}\right)^{2i+1}}{2i+1}$$
Por lo tanto, podemos usar la siguiente aproximación:
$$\dfrac{\pi}{6} = \sum_{i=0}^{tope} \dfrac{(-1)^i \left(\dfrac{1}{\sqrt{3}}\right)^{2i+1}}{2i+1}$$
Construya un programa que:  
1. Lea el valor ```tope```, obligando a que esté entre 1 y 100000, calcule la aproximación de $\pi$ mediante la anterior serie e imprima el resultado en pantalla.  
2. Lea un entero que indique cuántos decimales de precisión deseamos, calcule la aproximación de $\pi$ mediante la anterior serie y nos indique cuántas iteraciones (sumas) ha tenido que realizar para conseguir la aproximación deseada.  
  
Como valor de $\pi$ consideramos: ```3.14159265358979323846```.  
  
Nota: en la implementación de esta solución:  
1. No puede usar ```pow```.
2. Tampoco puede usar el condicional ```if```.

## 6. AproxPiGregory-Leibniz.cpp
En el siglo XVII, el matemático alemán Gottfried Leibniz y el matemático escocés James Gregory introdujeron una forma de calcular $\pi$ a través de una serie, es decir, de una suma de términos:

$$\dfrac{\pi}{4} = \sum_{i=0}^{\infty} \dfrac{(-1)^i}{2i + 1} = 1 - \dfrac{1}{2\cdot 1+1} + \dfrac{1}{2\cdot 2+1} - \dfrac{1}{2\cdot 3 + 1} + \ldots$$

Se pide desarrollar un programa que pida un número llamado ```tope``` e imprima en pantalla el resultado de la siguiente sumatoria:
$$\dfrac{\pi}{4} \approx \sum_{i=0}^{tope} \dfrac{(-1)^i}{2i + 1} = 1 - \dfrac{1}{2\cdot 1+1} + \dfrac{1}{2\cdot 2+1} - \dfrac{1}{2\cdot 3 + 1} + \ldots + \dfrac{(-1)^{tope}}{2\cdot tope + 1}$$
```tope``` deberá estar comprendido entre 1 y 100000.  
  
Debe resolver el problema de dos formas distintas:  
1. Usando la función ```pow``` de ```cmath``` para implementar $(-1)^i$.  
2. Sin usar la función ```pow```. Observe qu el valor de $(-1)^i$ es 1 para los valores pares de $i$ y -1 para los impares.
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
	
	int tope;

	bool error_lectura = false;

	// ENTRADA

	do{
		// Imprime al usuario por qué su entrada no era válida
		if(error_lectura)
			cout << endl << "Tope debe ser un entero entre 1 y 100000." << endl;

		cout << "Introduzca el tope de la sumatoria: ";
		cin >> tope;

		error_lectura = tope <= 0 || tope > 100000;

	}while(error_lectura);

	// CÁLCULOS

	// Método a) (Usando pow())

	double sumatoria_a = 0;

	for(int i = 0; i <= tope; i++){

		sumatoria_a += pow(-1, i) / (2 * i + 1);

	}

	// Calculamos pi a partir de pi / 4
	double aprox_pi_a = 4 * sumatoria_a;

	// Método b) (Sin usar pow())

	double sumatoria_b = 0;

	for(int i = 0; i <= tope; i++){

		// Si i es par, el numerador es 1 y si no -1
		int numerador = (i % 2 == 0)? 1 : -1 ;

		sumatoria_b += numerador / (2.0 * i + 1);

	}

	// Calculamos pi a partir de pi / 4
	double aprox_pi_b = 4 * sumatoria_b;

	// SALIDAS

	// Mostramos 30 decimales de pi
	cout << setw(32) << setprecision(30);

	cout << endl;
	cout << "La aproximacion de pi con tope = " << tope << " :" << endl;
	cout << "\tSolucion a) : " << aprox_pi_a << endl;
	cout << "\tSolucion b) : " << aprox_pi_b << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/AproxPiGregory-Leibniz.cpp)

## 7. AproxPiWallis.cpp
Una aproximación de $\pi$ incluida en el siglo XVII por el matemático inglés John Wallis viene dada por:
$$\dfrac{\pi}{2} \approx \dfrac{2}{1}\cdot\dfrac{2}{3}\cdot\dfrac{4}{3}\cdot\dfrac{4}{5}\cdot\dfrac{6}{5}\cdot\dfrac{6}{7}$$
Construya un programa que lea el valor ```tope``` obligando a que esté entre 1 y 100000, calcule la aproximación de $\pi$ mediante la anterior fórmula (multiplicando un total de ```tope``` fracciones) e imprima el resultado en pantalla.  
  
Debe resolver este problema de dos formas distintas:  
1. Observe que el numerador y el denominador varían de forma alternativa (aunque ambos de la misma forma, a saltos de 2). Cuando a uno le toca cambiar, el otro permanece igual. Este comportamiento se puede controlar con una única variable de tipo ```bool```.  
2. Otra forma de implementar los cambios en el numerador y denominador es observando que en cada iteración, el numerador es el denominador de la iteración anterior más 1 y el denominador es el numerador de la iteración anterior más 1.  
  
Ejemplo de entrada: ```1000``` Salida correcta: ```3.1400238186006```  
Ejemplo de entrada: ```100000``` Salida correcta: ```3.14157694582286```
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	
	int tope;

	bool error_lectura = false;

	// ENTRADA

	do{
		// Imprime al usuario por qué su entrada no era válida
		if(error_lectura)
			cout << endl << "Tope debe ser un entero entre 1 y 100000." << endl;

		cout << "Tope (numero de multiplicaciones): ";
		cin >> tope;

		error_lectura = tope <= 0 || tope > 100000;

	}while(error_lectura);

	// CÁLCULOS

	// Solucion a)

	double multiplicacion_a = 1;	// Neutro del producto

	int numerador_a = 2;
	int denominador_a = 1;

	bool cambia_numerador = false;

	for(int i = 0; i < tope; i++){

		// Se van realizando las multiplicaciones
		multiplicacion_a *= ((double)numerador_a) / denominador_a;

		// Cambia el numerador o el denominador, según indique cambia_numerador
		if(cambia_numerador)
			numerador_a += 2;
		else
			denominador_a += 2;

		// Cambia el valor de cambia_numerador
		cambia_numerador = !cambia_numerador;

	}

	// Calculamos pi a partir de pi/2
	double aprox_pi_a = 2 * multiplicacion_a;

	// Solución b)

	double multiplicacion_b = 1;		// Neutro del proucto

	int numerador_b = 2;
	int denominador_b = 1;

	int numerador_anterior;
	int denominador_anterior;

	for(int i = 0; i < tope; i++){

		// Se van realizando las multiplicaciones
		multiplicacion_b *= ((double) numerador_b) / denominador_b;

		// Se actualizan los numeradores y denominadores anteriores
		denominador_anterior = denominador_b;
		numerador_anterior = numerador_b;

		// Se ajustan los siguientes numerador y denominador
		numerador_b = denominador_anterior + 1;
		denominador_b = numerador_anterior + 1;

	}

	// Calculamos pi a partir de pi/2
	double aprox_pi_b = 2 * multiplicacion_b;

	// SALIDAS

	// Mostramos 14 decimales de pi
	cout << setw(16) << setprecision(14);

	cout << endl;
	cout << "La aproximacion de pi: " << endl;
	cout << "\tSolucion a) : " << aprox_pi_a << endl;
	cout << "\tSolucion b) : " << aprox_pi_b << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/AproxPiWallis.cpp)

## 8. Narcisista.cpp
Un número de ```n``` dígitos se dice que es **narcisista** si se puede obtener como la suma de las potencias ```n```-ésimas de cada uno de sus dígitos. Por ejemplo, 153 y 8208 son números narcisistas, porque:
$$153 = 1³ + 5³ + 3³$$
$$8208 = 8⁴ + 2⁴ + 8⁴$$
Construya un programa que nos indique si un número natural es narcisista.
