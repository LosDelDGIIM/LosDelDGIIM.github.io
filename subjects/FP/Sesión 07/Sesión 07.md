# Fundamentos de Programación. Sesión VII de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión VII de prácticas.


## 1. DescomposicionFactoresPrimos.cpp
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
```cpp
#include <iostream>

using namespace std;

int main(){

	const string SEPARADOR = " * ";
	const char EXPONENTE = '^';

	int numero;

	bool entrada_trivial;

	// ENTRADA

	do{

		cout << "Introduzca un entero positivo mayor que 0: "; 
		cin >> numero;

	}while(numero < 1);

	// Si nos piden descomponer 1 en factores primos
	entrada_trivial = numero == 1;

	// CÁLCULOS   *********************************************************

	// Trabajamos sobre una copia de numero
	int dividendo = numero;

	// Donde almacenamos las dos salidas
	string salida1, salida2;

	// Se realizan los cálculos si numero != 1
	if(!entrada_trivial){

		// Inicializamos divisor en el menor factor primo
		int divisor = 2;

		int divisor_anterior = divisor;

		// Contador de veces seguidas que aparece un mismo factor primo
		int veces = 0;

		// Mientras que dividendo siga teniendo factores primos
		while(dividendo != 1){

			// Mientras que divisor no sea un factor primo de dividendo
			// pasamos a analizar el siguiente
			while(dividendo % divisor != 0)
				divisor++;

			// Actualizamos dividendo para buscar más factores primos
			dividendo /= divisor;

			// Salida a

			// Almacenamos el factor primo en una salida
			salida1 += to_string(divisor);

			// Si no es el último factor primo, concatenamos SEPARADOR
			if(dividendo != 1)
				salida1 += SEPARADOR;

			// Salida b

			if(divisor == divisor_anterior)
				veces++;		// Vamos contando factores iguales

			else{
				// Si el contador no es 0, almacenamos el factor
				// (Podría ser 0 si 2 no es factor primo de numero)

				if(veces != 0){
					if(veces == 1)	// No indicamos el exponente
						salida2 += to_string(divisor_anterior) + SEPARADOR;

					else
						salida2 += to_string(divisor_anterior) + EXPONENTE 
								+ to_string(veces) + SEPARADOR;
				}

				veces = 1;	// Reiniciamos el contador
			}		
	
			divisor_anterior = divisor;   // Actualizamos divisor_anterior

		}  // Cierra while(dividendo != 1)

		// Salida b

		// Si la última secuencia de factores primos no se almacenó,
		// la almacenamos ahora

		if(veces != 0){
			if(veces == 1)		// No indicamos el exponente
				salida2 += to_string(divisor_anterior);

			else
				salida2 += to_string(divisor_anterior) + EXPONENTE 
							+ to_string(veces);

		}
			

	}  // Cierra if(!entrada_trivial)

	// SALIDAS

	cout << endl;

	// Si numero != 1
	if(!entrada_trivial){

		cout << numero << " = " << salida1 << endl;
		cout << numero << " = " << salida2 << endl;

	} else
		cout << "Por convenio, el 1 no se considera ni primo ni compuesto." << endl;

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/DescomposicionFactoresPrimos.cpp)

## 2. GaussianaCDFIntervalo.cpp
Recordando el enunciado del ejercicio ```4. CDFGaussiana.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
Estamos interesados en obtener el área que cubre la función gaussiana en un intervalo dado. Si consideramos el intervalo $]-\infty, x]$, el valor del área de la región que queda bajo la curva de $g(x)$ (siendo $g$ la función gaussiana) se calcula con la _distribución acumulada_ (_cumulative distribution function_ o CDF) en el punto $5x$:
$$CDF(x) = \int_{-\infty}^x g(x)~dx$$
Puede obtenerse un valor aproximado de $CDF(x)$ como la suma de valores de $g(x)$ empezando por valores alejados de la media (y menores que ella). Esto es, en vez de resolver la integral, estaremos interesados en aproximarla con un sumatorio de rectángulos de anchura relativamente pequeña.  
  
Recordamos la expresión de la función $g(x)$:
$$g(x) = \dfrac{1}{\sigma\sqrt{2\pi}} e^{\left[\dfrac{-1}{2}\left(\dfrac{x-\mu}{\sigma}\right)²\right]}$$  
  
Ahora estamos interesados en calcular $g(x)$ y $CDF(x)$ en un intervalo de valores de la abscisa:  
  
Escriba un programa que pida los parámetros que definen una función gaussiana ($\mu$ y $\sigma$), los extremos del intervalo de valores de la abscisa y la diferencia (salto) entre dos valores consecutivos de $x$. A continuación, mostrará para cada valor de $x$ los valores de $g(x)$ y $CDF(x)$.  
  
Recordamos que para el cálculo de $CDF(x)$ basta con fijar:  
1. Un valor inicial de abscisa para el cálculo de $CDF(x)$ (tómese $\mu - 3\sigma$).
2. Un salto entre dos valores consecutivos de $x$ (use una constante).
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
	
	const double SALTO = 0.01;
	const double PI = 6 * asin(0.5);

	double mu, sigma, x_inicial, x_final, salto_intervalo;

	// ENTRADAS

	do{

		cout << "Desviacion tipica (mayor que 0): ";
		cin >> sigma;
		cout << endl;

	}while(sigma <= 0);

	cout << "Media: ";
	cin >> mu;

	cout << endl;

	cout << "Introduzca un intervalo de abscisas: " << endl;
	cout << "\tLimite inferior: ";
	cin >> x_inicial;

	cout << "\tLimite superior: ";
	cin >> x_final;

	cout << endl;

	do{
	
		cout << "El salto entre valores (mayor que 0): ";
		cin >> salto_intervalo;

	}while(salto_intervalo <= 0);

	cout << endl << endl;

	// CÁLCULOS

	// Si el usuario introdujo en el límite superior del intervalo un valor
	// menor que el límite inferior del intervalo, lo modificamos para que
	// estén bien colocadas las variables:

	if(x_final < x_inicial){
		double auxiliar = x_final;
		x_final = x_inicial;
		x_inicial = auxiliar;
	}

	// La primera parte de la gaussiana no depende del valor de la abscisa,
	// calculamos ya su valor para reducir trabajo computacional
	double parte1_gaussiana = 1 / (sigma * sqrt(2 * PI));

	// Para reducir más trabajo computacional, calculamos la primera vez
	// la sumatoria de las alturas desde mu - 3 * sigma hasta la primera
	// abscisa del intervalo. Para la segunda abscisa, partimos de esta
	// sumatoria y continuamos hasta llegar a dicha abscisa
	// (algoritmo implementado en el bucle for anidado)
	
	double siguiente_abscisa_cdf = mu - 3 * sigma;

	double sumatoria_alturas = 0;

	// Formateamos la consola para las salidas

	cout.setf(ios::fixed);

	// Recorre todas las abscisas del intervalo especificado por el usuario
	// con el salto entre abscisa especificado por el usuario

	for(double i = x_inicial; i <= x_final; i += salto_intervalo){

		// i es el valor de la abscisa que se está procesando

		// 1.- Calculamos g(i)

		double parte2_gaussiana = exp(-0.5 * pow((i - mu) / sigma, 2));

		double gaussiana = parte1_gaussiana * parte2_gaussiana;

		// 2.- Calculamos CDF(i)

		// Recorre las abscisas desde la última que se tuvo en cuenta para
		// la sumatoria hasta i

		for(double j = siguiente_abscisa_cdf; j <= i; j += SALTO){

			// Se calcula la gaussiana en cada abscisa y se va sumando su
			// valor, obteniendo la sumatoria de las alturas de los rectangulos

			double parte2_gauss_CDF = exp(-0.5 * pow((j - mu) / sigma, 2));

			sumatoria_alturas += parte1_gaussiana * parte2_gauss_CDF;

		}

		// Multiplicamos la sumatoria de las alturas por la base (SALTO) de
		// los rectángulos para obtener la sumatoria del área de los
		// rectángulos, que es una aproximación de CDF(i) .

		double cdf = sumatoria_alturas * SALTO;

		// Calculamos la siguiente abscisa desde la que se partirá para 
		// calcular el siguiente CDF(i)

		siguiente_abscisa_cdf = i + SALTO;

		// SALIDAS

		cout << "g(" << setw(4) << setprecision(2) << i << ") = " 
			 << setw(12) << setprecision(10) << gaussiana;

		cout << "		";

		cout << "CDF(" << setw(4) << setprecision(2) << i << ") = " 
			 << setw(12) << setprecision(10) << cdf << "\n";

	}

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/GausianaCDFIntervalo.cpp)

## 3. GestionMenuDoble.cpp
Escriba un programa en el que se presente un menú principal para que el usuario pueda elegir entre las siguientes opciones:  
```A --> Calcular adición.```  
```P --> Calcular producto.```  
```X --> Salir.```  
  
Si el usuario elige en el menú principal:  
1. **Salir**, el programa terminará su ejecución.
2. **Calcular adición**, se presentará un menú (secundario) para que el usuario pueda elegir entre las siguientes opciones:  
   ```S --> Calcular suma.```  
   ```R --> Calcular resta.```  
   ```X --> Salir.```  
3. **Calcular producto**, se presentará un menú (secundario) para que el usuario pueda elegir entre las siguientes opciones:  
   ```M --> Calcular multiplicación.```  
   ```D --> Calcular división entera.```  
   ```R --> Calcular resto.```  
   ```X --> Salir.```  
  
Nota: para realizar las operaciones de producto no podrá usar los operadores ```*```, ```/``` ni ```%```. Deberá emplear sumas y restas.  
  
En las operaciones seleccionadas desde los menús secundarios, el programa pedirá dos números **enteros**, realizará la operación seleccionada, mostrará el resultado y volverá a mostrar el manú secundario seleccionado anteriormente.  
  
En los dos menús secundarios, la selección de **Salir** hace que el programa vuelva a mostrar el menú principal.
```cpp
#include <iostream>

using namespace std;

int main(){
	
	// Para saber el menú que hay que mostrar o si hay que salir del programa

	enum class Menu {Principal, Adicion, Producto, Salir};

	Menu estado = Menu::Principal;

	// Variables con las que se realizan los cálculos

	int numero1, numero2, salida;

	// Variables para la selección en cada menú

	char entrada;
	bool entrada_invalida;

	// true si hay que mostrar una salida de un resultado, false si no

	bool mostrar_salida;

	// Mientras que el usuario no seleccione Salir en el menú principal

	while(estado != Menu::Salir){

		switch(estado){

			// Si debemos mostrar el menú principal	

			case Menu::Principal:

				// Muestra el menú principal y lee la entrada, filtrándola

				do{

					cout << "----------------------" << endl;
					cout << "A->Calcular adición." << endl;
					cout << "P->Calcular producto." << endl;
					cout << "X->Salir." << endl;
					cout << endl;
					cout << "> ";
				
					cin >> entrada;

					cout << endl;

					entrada = tolower(entrada);

					entrada_invalida = entrada != 'a' && entrada != 'p' 
										&& entrada != 'x';

				}while(entrada_invalida);

				// Dependiendo de la entrada, asigna a estado un valor
				// u otro

				if(entrada == 'a')
					estado = Menu::Adicion;

				else if(entrada == 'p')
					estado = Menu::Producto;

				else
					estado = Menu::Salir;

				// No es necesario imprimir ningún cálculo

				mostrar_salida = false;

				break;		// De case Menu::Principal:

			// Si debemos mostrar el menú de adición

			case Menu::Adicion:
	
				// Muestra el menú de adición y lee la entrada, filtrándola

				do{

					cout << "-------------------" << endl;
					cout << "S->Calcular suma." << endl;
					cout << "R->Calcular resta." << endl;
					cout << "X->Salir." << endl;
					cout << endl;
					cout << "> ";
				
					cin >> entrada;

					cout << endl;

					entrada = tolower(entrada);

					entrada_invalida = entrada != 's' && entrada != 'r' 
										&& entrada != 'x';

				}while(entrada_invalida);

				// Si hay que volver al menú principal, se cambia estado
				// (No hay que mostrar resultados del cálculos)

				if(entrada == 'x'){
					estado = Menu::Principal;
					mostrar_salida = false;
				}

				// Si no, el programa solicita dos números enteros

				else {

					cout << "Introduce el primer entero: ";
					cin >> numero1;

					cout << "Introduce el segundo entero: ";
					cin >> numero2;

					// Dependiendo de la selección los suma o resta

					if(entrada == 's')
						salida = numero1 + numero2;

					else
						salida = numero1 - numero2;

					// Hay que mostrar el resultado al final

					mostrar_salida = true;
				}

				break;		// De case Menu::Adicion:

			// Si hay que mostrar el menú del producto

			case Menu::Producto:

				// Muestra el menú y lee la entrada, filtrándola

				do{
	
					cout << "---------------------------" << endl;
					cout << "M->Calcular multiplicacion." << endl;
					cout << "D->Calcular division entera." << endl;
					cout << "R->Calcular resto." << endl;
					cout << "X->Salir." << endl;
					cout << endl;
					cout << "> ";

					cin >> entrada;

					cout << endl;

					entrada = tolower(entrada);
		
					entrada_invalida = entrada != 'm' && entrada != 'd' 
									&& entrada != 'r' && entrada != 'x';

				}while(entrada_invalida);

				// Si se selecciona salir, se cambia estado
				// (no hay que mostrar ningún resultado de cálculo)

				if(entrada == 'x'){
					estado = Menu::Principal;
					mostrar_salida = false;
				}

				// Si no, se solicitan dos números

				else{

					cout << "Introduce el primer entero: ";
					cin >> numero1;

					// true si hay que realizar una división

					bool division = entrada == 'd' || entrada == 'r';

					// Si hay que hacer una división y el divisor es 0,
					// se vuelve a solicitar

					do{

						cout << "Introduce el segundo entero: ";
						cin >> numero2;

					}while(division && numero2 == 0);

					// salida_negativa == true si un numero es positivo
					// y otro negativo

					bool salida_negativa = (numero1 < 0 && numero2 >= 0) 
						|| (numero2 < 0 && numero1 >=0);

					// Calculamos el opuesto de los números 
					// en el caso de ser negativos (su valor absoluto)

					if(numero1 < 0)
						numero1 = -numero1;

					if(numero2 < 0)
						numero2 = -numero2;

					// Si hay que multiplicarlos

					if(entrada == 'm'){

						// Realizamos una sumatoria de numero1 numero2 veces

						// Para reducir peso computacional, gracias a la 
						// conmutatividad del producto, podemos hacer
						// que el mínimo número sea el que defina
						// las vueltas del for

						// numero2 será el mínimo de ambos:

						if(numero1 < numero2){
							int auxiliar = numero1;
							numero1 = numero2;
							numero2 = auxiliar;
						}

						// Se suma numero1 numero2 veces, obteniendo
						// numero1 * numero2

						salida = 0;

						for(int i = 0; i < numero2; i++)
							salida += numero1;

						// Si un número era positivo y otro negativo, el
						// resultado debe ser negativo

						if(salida_negativa)
							salida = -salida;

					// Si hay que dividirlos (de forma entera) o hacer el resto

					}else{

						// Se trabaja con una copia de numero1

						int auxiliar = numero1;

						// Se cuenta el número de veces que hay que 
						// sustraer numero2 a numero1 para que 
						// numero1 sea menor a numero2

						int contador = 0;

						while(auxiliar >= numero2){
							auxiliar -= numero2;
							contador++;
						}

						// Dicha cuenta es el resultado de la división
						// entera numero1 / numero2

						if(entrada == 'd'){	// Si había que dividirlos

							salida = contador;

						}else{	// if(entrada == 'r') , salida = resto

							// El valor restante en auxiliar es el resto

							salida = auxiliar;

						}

						// Si un número era positivo y otro negativo, el
						// resultado debe ser negativo

						if(salida_negativa)
							salida = -salida;

					}	// Cierre if(entrada != 'm')

					// Se muestra al final la salida de los cálculos
		
					mostrar_salida = true;

				} // Cierre if(entrada != 'x')

				break;		// De case Menu::Producto:

		}	// Cierre switch(estado)

		// SALIDAS DE CÁLCULOS

		if(mostrar_salida){
			cout << endl;
			cout << "El resultado es " << salida << "." << endl;
			cout << endl;
		}

		// Se deja espacio entre cada vez que se vuelve a mostrar un menú

		cout << endl << endl << endl << endl;

	}	// Cierre while(estado != Menu::Salir)
	

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/GestionMenuDoble.cpp)

## 4. AdivinarAmpliacion.cpp
Recordando el enunciado del ejercicio ```3. Adivinar.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
Diseñe un programa para jugar a adivinar un número. El programa generará un número aleatorio (entre ```MIN``` y ```MAX```) y el usuario tendrá que adivinarlo. En cada jugada el jugador introducirá un valor y el juego indicará si el número introducido por el jugador está por encima o por debajo del número a adivinar.  
  
Como reglas de parada, considerad que el usuario:
1. Haya acertado.
2. No quiera seguir jugando y en este caso usa un carácter especial ```TERMINADOR``` para poder abandonar la partida.  
   
Si no sabe cómo generar números aleatorios, le recomendamos ojear el siguiente [archivo](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/GenerarNumerosAleatorios.md).  
  
En esta ocasión, deberemos ampliar el programa de forma que cuando un juego termine, el programa pedirá si queremos volver a jugar o no.  
  
Al terminar (no se quiere jugar más), el programa mostrará cuántos juegos se han realizado (contabilizando los juegos abandonados como juegos válidos).
```cpp
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
	
    const char CHAR_SEGUIR = 's', CHAR_SALIR = 'n';
	const int MIN = 1, MAX = 100;
	const int NUM_VALORES = MAX - MIN + 1; // Valores entre MIN y MAX
	const int TERMINADOR = -1;

	int numero;

	char entrada;		// (S/N) de desea seguir jugando

	bool seguir;		// true para seguir jugando

	int juegos = 0; 	// Número de juegos

	// ENTRADAS Y CÁLCULOS

	const string MENSAJE = "Intente adivinar el numero: ";

	// Iniciamos el generador de números aleatorios
	time_t t;
	srand(time(&t));

	do{

		// Generamos el número aleatorio
	
		// Almacenamos el número aleatorio, modificándolo para que esté en el
		// intervalo [MIN, MAX]
		int adivinar;
		adivinar = (rand() % NUM_VALORES) + MIN;

		// Primera salida (información del TERMINADOR)

		cout << "Si se rinde, introduzca \"" << TERMINADOR << "\"." 
				 << endl << endl;

		// Lectura anticipada

		// Se asegura que el número introducido esté en [MIN, MAX]

		bool fuera_rango;

		do{
	
			cout << MENSAJE << "(entre " << MIN << " y " << MAX << ") ";

			cin >> numero;

			fuera_rango = numero != TERMINADOR 
							&& (numero < MIN || numero > MAX);

		}while(fuera_rango);
	
		// Bucle que permite seguir jugando
	
		while(numero != TERMINADOR && numero != adivinar){
			
			cout << endl;
	
			// Imprime si adivinar es mayor o menor que el introducido
	
			if(numero > adivinar)
				cout << "El numero es menor que " << numero << "." << endl;
	
			else
				cout << "El numero es mayor que " << numero << "." << endl;
	
			// Solicita el siguiente número del jugador
			// Se asegura que el número introducido esté en [MIN, MAX]
	
			do{

				cout << MENSAJE;
				cin >> numero;

				fuera_rango = numero != TERMINADOR 
							&& (numero < MIN || numero > MAX);

			}while(fuera_rango);

		}
	
		// SALIDAS
	
		cout << endl << endl;
	
		// Si el jugador se ha rendido
		if(numero == TERMINADOR)
			cout << "El numero era " << adivinar << "." << endl;
	
		// Si no, es que ha acertado el número
		else
			cout << "Felicidades, has acertado, el numero era " << adivinar 
				 << "." << endl;
	
		cout << endl;

		// SEGUIR JUGANDO

		do{

			cout << endl;
			cout << "Quiere seguir jugando? (S/N): ";
	
			cin >> entrada;
	
			cout << endl << endl;

			// Pasamos entrada a minúscula para simplificar las comparaciones
			entrada = tolower(entrada);

			// Si no es igual a s/n la entrada es inválida, se repite

		}while(entrada != CHAR_SEGUIR && entrada != CHAR_SALIR);

		seguir = entrada == CHAR_SEGUIR;	// Si se introdujo s se sigue jugando

		juegos++;	// Se aumenta el contador del número de juegos

	}while(seguir);

	// Se imprime el número de juegos totales, contando también rendiciones 

	cout << "Se han jugado un total de " << juegos << " juegos." << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/AdivinarAmpliacion.cpp)

## 5. AdivinarAutonomo.cpp
Continuando con el ejercicio superior (```4. AdivinarAmpliacion.cpp```), en este caso el programa se ejecutará sin la intervención del usuario.  
  
El programa consistirá en:  
1. Generar un número aleatorio a adivinar (entre ```MIN``` y ```MAX```).
2. Generar números aleatorios dentro del mismo rango hasta que el valor generado coincida con el buscado. Cada vez que se genera un valor se produce una jugada. Estamos interesados en conocer el núemro de jugadas por juego.  
  
El proceso descrito (es decir, un juego) se repetirá ```NUMERO_JUEGOS``` veces.  
  
El programa deberá calcular el número medio de jugadas por juego.
```cpp
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
	
	const int MIN = 1, MAX = 100;
	const int NUM_VALORES = MAX - MIN + 1;		// Valores entre MIN y MAX

	const int NUMERO_JUEGOS = 50;

	int juego = 0;
	int jugadas = 0;

	int sumatoria_jugadas = 0;

	// Para mostrar las jugadas que se han hecho por cada juego
	string info_jugadas; 

	// CÁLCULOS   ********************************************************

	// Iniciamos el generador de números aleatorios

	time_t t;
	srand(time(&t));

	// Se juegan NUMERO_JUEGOS juegos

	for(int i = 0 ; i < NUMERO_JUEGOS; i++){

		jugadas = 0;	// Reiniciamos el número de jugadas

		juego++;	// Comenzamos un nuevo juego

		// 1.- Se genera el número aleatorio a adivinar   ------------------

		// Almacenamos el número aleatorio, modificándolo para que esté en el
		// intervalo [MIN, MAX]
		int adivinar = (rand() % NUM_VALORES) + MIN;

		// 2.- EL programa intenta adivinar el número aleatoriamente -------

		int intento;

		// Se ejecuta hasta que lo adivine

		srand(5);

		do{

			// Número aleatorio que intenta adivinar la variable adivinar
			intento = (rand() % NUM_VALORES) + MIN;

			jugadas++;		// Aumentan las jugadas

		}while(intento != adivinar);

		// 3.- Se tiene en cuenta el número de jugadas y se almacenan para
		// imprimirlas en consola.

		info_jugadas += "Juego " + to_string(juego) + ":	" 
					 + to_string(jugadas) + " jugadas.\n";

		sumatoria_jugadas += jugadas;

	}

	// Se calcula la media de jugadas por juegos:

	double media_intentos = ((double) sumatoria_jugadas) / NUMERO_JUEGOS;

	// SALIDAS ***********************************************************

	cout << info_jugadas << endl;

	cout << "La media de intentos por juego es de " << media_intentos 
		 << " jugadas/juego." << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/AdivinarAutonomo.cpp)

## 6. AdivinarAutonomoInteligente.cpp
Continuando con el ejercicio superior (```5. AdivinarAutonomo.cpp```), en este caso, mejoraremos la heurística del programa, de forma que se den menos jugadas por juego.  
  
En este caso, no generaremos números aleatorios, sino que partiremos del valor medio entre ```MIN``` y ```MAX```. Si es el valor buscado hemos terminado; pero si no, sabemos que el valor buscado estará en la mitad izquierda (si el buscado es menor que el número proporcionado); o en la mitad derecha (si el buscado es mayor que el número proporcionado), descartando así la mitad de los casos. Sabiendo ya la mitad en la que tenemos que buscar, volveremos al mismo razonamiento: buscaremos el valor medio de la nueva mitad y comprobaremos si es el valor buscado. En caso de no serlo, reduciríamos el problema otra vez a la mitad, quedándonos ahora con un cuarto de todo el rango total en tan sólo 2 jugadas. Repetiríamos el proceso hasta encontrar el número.  
  
Cada vez que se compara un nuevo valor con el busado se produce una jugada. Estamos interesados en saber el número de jugadas por juego.  
  
Todo el proceso descrito anteriormente (cada juego) se repite ```NUMERO_JUEGOS``` veces.  
  
El programa deberá mostrar en pantalla el número medio de jugadas por juego.
```cpp
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
	
	const int MIN = 1, MAX = 100;
	const int NUM_VALORES = MAX - MIN + 1;		// Valores entre MIN y MAX

	const int NUMERO_JUEGOS = 50;

	int juego = 0;
	int jugadas = 0;

	int sumatoria_jugadas = 0;

	// Para mostrar las jugadas que se han hecho por cada juego
	string info_jugadas; 

	// CÁLCULOS   ********************************************************

	// Iniciamos el generador de números aleatorios	
	time_t t;
	srand(time(&t));

	// Se juegan NUMERO_JUEGOS juegos

	for(int i = 0 ; i < NUMERO_JUEGOS; i++){
	
		// Intervalos entre los que se encuentra el número a generar
		// Se van acotando cada vez más con el desarrollo del bucle
		// Reiniciamos su valor por cada vuelta de bucle
		int min_generar = MIN, max_generar = MAX;

		jugadas = 0;	// Reiniciamos el número de jugadas

		juego++;	// Comenzamos un nuevo juego

		// 1.- Se genera el número aleatorio a adivinar   ------------------

		// Almacenamos el número aleatorio, modificándolo para que esté en el
		// intervalo [MIN, MAX]
		int adivinar = (rand() % NUM_VALORES) + MIN;;

		// 2.- EL programa intenta adivinar el número   ---------------------

		int intento;

		// Se ejecuta hasta que lo adivine

		do{
			// Se calcula el punto medio de [max_generar, min_generar]
			intento = (max_generar + min_generar) / 2;

			// Se van cerrando las cotas del intervalo
			// (+1 o -1 porque como intento != adivinar, no nos interesa
			// incluir dicho valor en el intervalo, si no el siguiente valor)

			if(adivinar > intento)
				min_generar = intento + 1;

			else
				max_generar = intento - 1;
	
			jugadas++;		// Aumentan las jugadas

		}while(intento != adivinar);

		// 3.- Se tiene en cuenta el número de jugadas y se almacenan para
		// imprimirlas en consola.

		info_jugadas += "Juego " + to_string(juego) + ":	" 
					 + to_string(jugadas) + " jugadas.\n";

		sumatoria_jugadas += jugadas;

	}

	// Se calcula la media de jugadas por juegos:

	double media_intentos = ((double) sumatoria_jugadas) / NUMERO_JUEGOS;

	// SALIDAS ***********************************************************

	cout << info_jugadas << endl;

	cout << "La media de intentos por juego es de " << media_intentos 
		 << " jugadas/juego." << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/AdivinarAutonomoInteligente.cpp)

# Ejercicios Opcionales
## 1. MultiplicacionRusa.cpp
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

## 2. InteresReinvierteAnidado.cpp

## 3. DivisoresVarios.cpp
Recordando el enunciado del ejercicio ```1. Divisores.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/edit/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
Realice un programa que lea desde teclado un número natural e imprima en pantalla todos sus **divisores**. Para obtener los divisores, basta recorrer todos los enteros menores que el valor introducido y comprobar si lo dividen.  
  
Ahora, el programa deberá leer un número entero ```tope``` e imprimir en pantalla todos los divisores de todos los números enteros del intervalo ```[1, tope]```.

## 4. Perfecto.cpp
Un número _perfecto_ es aquel que es igual a la suma de todos sus divisores positivos excepto él mismo. El primer número perfecto es el 6, ya que sus divisores son 1, 2, 3 y $1+2+3=6$.  
  
Escriba un programa que muestre el mayor número perfecto que sea menor a un número dado por el usuario.

## 5. IgualCuadrado.cpp
Escribir un programa que encuentre dos números enteros $n$ y $m$ mayores que 1 que verifiquen:
$$\sum_{i=1}^m i² = n²$$

## 6. Secuenciable.cpp
Diremos que un número entero es _secuenciable_ si se puede expresar como suma de números consecutivos.  
Por ejemplo: $6 = 1 + 2 + 3$, $15 = 7 + 8$.  
Dicha descomposición no tiene por qué ser única.  
Por ejemplo: $15 = 7 + 8 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5$.  
  
Escriba un programa que lea un entero $n$ y nos diga cuántas descomposiciones posibles tiene.   
  
Por ejemplo:  
```15 --> 3 descomposiciones.```  
```94 --> 1 descomposiciones.```  
```108 --> 3 descomposiciones.```  
  
Curiosidad (**no debe usarse para resolver el ejercicio**): los únicos números con 0 descomposiciones son las potencias de 2.

## 7. GestionMenusGaussiana.cpp
Escriba un programa que presente un menú principal como este:  
```a) Introducir parámetros de la funcion (esperanza y desviacion).```  
```b) Salir del programa.```  
  
Si el usuario elige ```b```, el programa terminará. Si elige la opción de introducir los parámetros, el programa leerá dos parámetros (esperanza y desviación típica). A continuación, el programa presentará un menú con las siguientes opciones:  
```a) Introducir rango de valores de abscisas.```  
```b) Volver al menu anterior.```  
  
Si el usuario elige ```b```, el programa deberá mostrar el menú principal. Si elige la opción de introducir valores de abscisas, el programa le pedirá los extremos del intervalo y el incremento entre dos valores consecutivos de la abscisa. El programa mostrará los valores de la función gaussiana en todos los valores posibles de la abscisa indicados.  
Después de mostrar los valroes de la función, el programa volverá al menú de introducción de lrango e valores de abscisas.  
  
Recordamos la expresión de la función gaussiana:
$$Gaussiana(x) = \dfrac{1}{\sigma\sqrt{2\pi}} e^{\left[\dfrac{-1}{2}\left(\dfrac{x-\mu}{\sigma}\right)²\right]}$$
