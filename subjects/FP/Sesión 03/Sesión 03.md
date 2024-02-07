# Fundamentos de Programación. Sesión III de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión III de prácticas.


## 1. RadarTramo.cpp
Un radar de tramo está organizado en tres sectores:  
1. El primero, de 5.3 km, tiene la velocidad limitada a 80 km/h.  
2. El segundo, de 8.1 km, tiene la velocidad limitada a 100 km/h.
3. El tercero, de 6.4 km, tiene la velocidad limitada a 80 km/h. 
  
  
El tramo tiene dos pórticos de control, al inicio y al final.  
  
Escribir un programa que calcule y muestre el _tiempo umbral de sanción_, o sea, el tiempo mínimo que puede emplear un vehículo en recorrer el tramo completo sin ser sancionado. Muestre el resultado en segundos, y en minutos y segundos.
```cpp
#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
    
	// Multiplicar por esta constante para pasar de km/h a m/s.
	double const MS = 1000.0/3600;
	double sector1 = 5.3, sector2 = 8.1, sector3 = 6.4;
	double vel_max1 = 80, vel_max2 = 100, vel_max3 = 80;

	// Cálculos: 
	// Calculamos los segundos necesarios para recorrer cada sector
	// a velocidad máxima, almacenánolos en la variable segundos.

	double segundos = (sector1 * 1000) / (vel_max1 * MS);	//Sector 1
	segundos += ((sector2 * 1000) / (vel_max2 * MS));	    //Sector 2
	segundos += ((sector3 * 1000) / (vel_max3 * MS));	    //Sector 3

	//Es posible que los segundos totales contengan decimales, los truncamos:
	int segundos_totales = segundos;

	//Salida: Imprimime el resultado en segundos y en minutos y segundos

	cout << endl;
	cout << "El tiempo que necesita un vehiculo en recorrer los tramos: " << endl;
	cout << "\tSector 1: " << sector1 << "km, a " << vel_max1 << "km/h." << endl;
	cout << "\tSector 2: " << sector2 << "km, a " << vel_max2 << "km/h." << endl;
	cout << "\tSector 3: " << sector3 << "km, a " << vel_max3 << "km/h." << endl;	
	cout << endl;

	cout << "Es de " << segundos_totales << " segundos." << endl;
	cout << "Que son " << (segundos_totales / 60) << " minutos y " << (segundos_totales % 60) << " segundos.";
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/RadarTramo.cpp)

## 2. Cambio.cpp
Escribid un programar para una caja de supermercado que lea el total a pagar y la cantidad pagada (se supone que la cantidad pagada es mayor o igual que el total a pagar) e indique el número de monedas de 2€, 1€, 50 céntimos, 20 céntimos, 10 céntimos, 5 céntimos, 2 céntimos y 1 céntimo que se deben dar de cambio. Deberán indicarse la menor cantidad de monedas de cada clase.
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	//Declaración de variables
	double cantidad_a_pagar, cantidad_pagada;
	int monedas_2e = 0, monedas_1e = 0, monedas_50c = 0, monedas_20c = 0, 
		monedas_10c = 0, monedas_5c = 0, monedas_2c = 0, monedas_1c = 0;

	//Entradas
	cout << endl;
	cout << "Introduzca la cantidad a pagar (en euros): ";
	cin >> cantidad_a_pagar;
	cout << "Introduzca la cantidad con la que se ha pagado (en euros): ";
	cin >> cantidad_pagada;
	cout << endl;
	cout << endl;

	// Cálculos:
	// Se calcula la cantidad a devolver

	double cantidad_a_devolver = cantidad_pagada - cantidad_a_pagar;
	
	// Separa la cantidad a devolver en la parte entera, correspondiente a los
	// euros y la fraccionaria, correspondiente a los centimos.
    
	double euros_devuelta;
	double centimos_devuelta = modf(cantidad_a_devolver, &euros_devuelta);

	// Se calcula mediante cocientes el número de monedas de cada tipo. las 
	// variables euros_devuelta y centimos_devuelta van disminuyendo su valor 
	// mediante restos conforme se devuelven monedas.

	monedas_2e = euros_devuelta / 2;
	euros_devuelta -= monedas_2e * 2;

	monedas_1e = euros_devuelta;

	monedas_50c = centimos_devuelta / 0.5;
	centimos_devuelta -= monedas_50c * 0.5;

	monedas_20c = centimos_devuelta / 0.2;
	centimos_devuelta -= monedas_20c * 0.2;

	monedas_10c = centimos_devuelta / 0.1;
	centimos_devuelta -= monedas_10c * 0.1;

	monedas_5c = centimos_devuelta / 0.05;
	centimos_devuelta -= monedas_5c * 0.05;

	monedas_2c = centimos_devuelta / 0.02;
	centimos_devuelta -= monedas_2c * 0.02;

	monedas_1c = centimos_devuelta*100;

	//Salidas
	cout << "Ha(n) de devolverle al cliente " << cantidad_a_devolver << " euros:" 
		<< endl;
	cout << "\t" << monedas_2e << " moneda(s) de 2 euros." << endl;
	cout << "\t" << monedas_1e << " moneda(s) de 1 euro." << endl;
	cout << "\t" << monedas_50c << " moneda(s) de 50 centimos." << endl;
	cout << "\t" << monedas_20c << " moneda(s) de 20 centimos." << endl;
	cout << "\t" << monedas_10c << " moneda(s) de 10 centimos." << endl;
	cout << "\t" << monedas_5c << " moneda(s) de 5 centimos." << endl;
	cout << "\t" << monedas_2c << " moneda(s) de 2 centimos." << endl;
	cout << "\t" << monedas_1c << " moneda(s) de 1 centimo." << endl;

	return 0;
}

// Nota: Este programa es totalmente válido, pero debido a problemas con los ordenadores a la hora de dividir,  
// puede que el output que de el programa no esté bien. Te retamos a crear un programa que no tenga este fallo.
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/Cambio.cpp)
  

## 3. ConsumoGasolina.cpp
Escriba un programa que calcule el consumo de gasolina. Pedirá la distancia recorrida (en kms), los litros de gasolina consumidos y los litros que quedan en el depósito. El programa debe informar el consumo en km/litro, los litros/100km y cuántos kilómetros de autonomía le restan con ese nivel de consumo.  
```cpp
#include <iostream>

using namespace std;

int main()
{
	//Declaraciones
	double distancia_recorrida, litros_consumidos, litros_restantes;
	
	//Entradas
	cout << endl;
	cout << "Introduzca el numero de kilometros que ha recorrido con su " << "vehiculo: ";
	cin >> distancia_recorrida;

	cout << "Introduzca los litros que ha consumido su vehiculo durante esos " << distancia_recorrida << " kilometros: ";
	cin >> litros_consumidos;

	cout << "Finalmente, introduzca los litros restantes que contiene el " << "deposito de su vehiculo: ";
	cin >> litros_restantes;

	//Cálculos, basados en factores de conversión
	double kilometros_por_litro = distancia_recorrida / litros_consumidos;
	double litros_por_100km = 100 / kilometros_por_litro;
	double km_de_autonomia = litros_restantes * kilometros_por_litro;

	//Salidas
	cout << endl;
	cout << endl;
	cout << "Su vehiculo es capaz de recorrer " << kilometros_por_litro << " kilometros por litro." << endl;
	cout << "Cada 100km, su vehiculo consume " << litros_por_100km << " litros." << endl;
	cout << "Con " << litros_restantes << " litros restantes en el deposito, " << "su vehiculo es capaz de recorrer " << km_de_autonomia << 
		" kilometros." << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/ConsumoGasolina.cpp)

## 4. AjusteTiempo.cpp
Lea desde teclado tres variables correspondientes a un número de horas, minutos y segundos, respectivamente. Diseñe un algoritmo que calcule las horas, minutos y segundos dentro de su rango correspondiente.  
  
Por ejemplo, dadas 10 horas, 119 minutos y 280 segundos, su programa debería mostrar:  
12 horas, 3 minutos y 40 segundos.  
   
En el caso de que nos salgan más de 24 horas, daremos también los días correspondientes (pero ya no pasaremos a los años o meses si los días superan una cantidad).
```cpp
#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
	int dias, horas, minutos, segundos;

	// Las variables con prefijo "input_" sirven para mostrar en la salida los valores que el usuario introdujo
	int input_horas, input_minutos, input_segundos;

	// Entradas
	cout << endl;
	cout << "Introduzca el numero de horas (un valor entero): ";
	cin >> input_horas;
	cout << "Introduzca el numero de minutos (un valor entero): ";
	cin >> input_minutos;
	cout << "Introduzca el numero de segundos (un valor entero): ";
	cin >> input_segundos;

	// Cálculos
	// Se van ajustando los tiempos desde atrás hacia adelante, comenzando
	// por los segundos y terminando con los días.
	horas = input_horas;
	minutos = input_minutos;
	segundos = input_segundos;

	// Si hay algún minuto lo almacena en minutos y deja los segundos sobrantes
	// en la variable segundos.
	minutos += segundos / 60;
	segundos = segundos % 60;

	horas += minutos / 60;
	minutos = minutos % 60;

	dias = horas / 24;
	horas = horas % 24;

	// Salidas
	cout << endl;
	cout << input_horas << " hora(s), " << input_minutos << " minuto(s) y " << input_segundos << " segundo(s) son:" << endl;
	cout << dias << " dia(s), " << horas << " hora(s), " << minutos << " minuto(s) y " << segundos << " segundo(s)." << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/AjusteTiempo.cpp)

## 5. RitmoVelocidad_a.cpp y RitmoVelocidad_b.cpp 
En atletismo, se expresa la rapidez de un atleta en términos de ritmo (minutos y segundos por kilómetro) en lugar de las convencionales unidades de velocidad (kilómetros por hora, por ejemplo).  
  
Escriba dos programas para convertir entre estas dos medidas:  
1. El primero (a) leerá el ritmo (minutos y segundos, por separado) y mostrará la velocidad del atleta en kilómetros por hora.
2. El segundo (b) leerá la velocidad del atleta en kilómetros por hora y mostrará su ritmo (minutos y segundos).
```cpp
// RitmoVelocidad_a.cpp
#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
	int minutos, segundos;
	double kilometros_por_hora;

	// Entradas
	cout << endl;
	cout << "Introduzca la velocidad del atleta en minutos y segundos por kilometro: " << endl;
	cout << "\tMinutos (valor entero): ";
	cin >> minutos;
	cout << "\tSegundos (valor entero): ";
	cin >> segundos;

	// Cálculos, basados en un factor de conversión.
	kilometros_por_hora = 1 / (minutos / 60.0 + segundos / 3600.0);
	
	// Salida
	cout << endl;
	cout << minutos << ":" << segundos << " min/km son " << kilometros_por_hora << " km/h." << endl;
	cout << endl;

	return 0;
}
```
```cpp
// RitmoVelocidad_b.cpp
#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
	double kilometros_por_hora;
	int minutos, segundos;

	// Entradas
	cout << endl;
	cout << "Introduzca la velocidad del atleta en kilometros por hora: ";
	cin >> kilometros_por_hora;

	// Cálculos, basados en factores de conversión
	double tiempo = 1 / kilometros_por_hora;  //Calcula las horas por kilometro
	segundos = tiempo * 3600; 
	
	// Ajusta los tiempos para mostrarlos adecuadamente
	minutos = segundos / 60;
	segundos = segundos % 60;

	// Salida
	cout << endl;
	cout << kilometros_por_hora << " km/h son " << minutos << ":" << segundos << " min/km." << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución - RitmoVelocidad_a](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/RitmoVelocidad_a.cpp)  
[Ir a la solución - RitmoVelocidad_b](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/RitmoVelocidad_b.cpp)

## 6. Gaussiana.cpp 
La función gaussiana es muy importante en Estadística. Es una función real de variable real en la que el parámetro $\mu$ se conoce como _esperanza_ o _media_ y $\sigma$ como _desviación típica_. La función se define mediante la siguiente expresión:  
$$Gaussiana(x) = \dfrac{1}{\sigma\sqrt{2\pi}} e^{\left[\dfrac{-1}{2}\left(\dfrac{x-\mu}{\sigma}\right)²\right]}$$
Realizar un programa que lea los coeficientes reales $\mu$ y $\sigma$ de una función gaussiana. A continuación, el programa leerá un valor de abscisa $x$ y se imprimirá el valor que toma la función en $x$.  
  
  Para realizar las operaciones indicadas, debe utilizar las siguientes funciones (disponibles en ```cmath```):  
  * Para elevar el número $e$ a un valor cualquiera, use la función ```exp```. Por ejemplo, para calcular $e⁸$ debería usar la expresión ```exp(8)```.
  * Para calcular la raíz cuadrada, use ```sqrt```. Por ejemplo, para calcular $\sqrt{8}$ debería usar la expresión ```sqrt(8)```.
  * Para elevar un numero a otro, utilice la función ```pow``` en la siguiente forma: ```pow(base, exponente)```. Por ejemplo, para calcular $2^{10}$ debería usar la expresión ```pow(2,10)```.  
    
Para consultar los resultados correctos, pueden visitar el siguiente enlace [https://www.easycalculation.com/statistics/normal-pdf.php](https://www.easycalculation.com/statistics/normal-pdf.php).
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	// Declaraciones
	double desviacion_tipica, media, x;
	const double PI = 6 * asin(0.5);

	// Entradas
	cout << endl;
	cout << "Introduzca la desviacion tipica de la funcion gaussiana: ";
	cin >> desviacion_tipica;
	cout << "Introduzca la media de la funcion gaussiana: ";
	cin >> media;
	cout << "Introduzca el valor de la abscisa en la que desea evaluar la funcion: ";
	cin >> x;

	// Calculos: calculamos gaussiana(x):

	double gaussiana = (1 / (desviacion_tipica * sqrt(2 * PI))) * 
		exp(-1/2.0 * pow( ((x - media) / desviacion_tipica), 2));

	// Salida
	cout << endl;
	cout << "El valor de la funcion gaussiana de desviacion tipica " << desviacion_tipica << ", media " << media << ", evaluada en la abscisa " 
		<< x << " es de: " << gaussiana << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/Gaussiana.cpp)

# Ejercicios opcionales
## 1. IncrementoSalario.cpp
Construya un programa para leer el valor de una variable ```salario_base``` de tipo ```double```, la incremente un 2% e imprima el resultado en pantalla.
```cpp
#include <iostream>

using namespace std;

int main()
{
	// Declaración
    const double PORC_AUMENTO = 1.02;
	double salario_base, salario_final;

	// Entrada
	cout << endl;
	cout << "Introduzca el salario base: ";
	cin >> salario_base;

	// Cálculo
	salario_final = salario_base * PORC_AUMENTO;

	// Salida
	cout << endl;
	cout << "Tras aplicarle un aumento del 2%, el salario base de " <<
		salario_base << " euros pasara a " << salario_final << " euros." 
		<< endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/IncrementoSalario.cpp)

## 2. ConversionUnidades.cpp
Realice un programa que nos pida una longitud cualquiera dada en metros. El programa deberá calcular el equivalente de dicha longitud en pulgadas, pies, yardas y millas, y mostrarnos los resultados en pantalla. Para el cálculo, utilice la siguiente tabla de conversión del sistema métrico:  
  
```1 pulgada = 25.4 milímetros```  
```1 yarda = 0.9144 metros```  
```1 pie = 30.48 centímetros```  
```1 milla = 1.609344 kilómetros```  
```cpp
#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
	double metros;
	const double PULGADA_MM = 25.4, PIE_CM = 30.48, YARDA_M = 0.9144, MILLA_KM = 1.609344;

	// Entrada
	cout << endl;
	cout << "Introduzca la distancia (en metros): ";
	cin >> metros;

	// Cálculos, basados en factores de conversión
	double pulgadas = metros * 1000 / PULGADA_MM;
	double pies = metros * 100 / PIE_CM;
	double yardas = metros * YARDA_M;
	double millas = metros / 1000 / MILLA_KM;

	// Salidas
	cout << endl;
	cout << metros << " metros son: " << endl;
	cout << "\t" << pulgadas << " pulgadas." << endl;
	cout << "\t" << pies << " pies." << endl;
	cout << "\t" << yardas << " yardas." << endl;
	cout << "\t" << millas << " millas." << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/ConversionUnidades.cpp)

## 3. DesplazamientoIntervalo.cpp 
Queremos construir una expresión numérica que desplace un entero un número dado de posiciones, pero lo mantenga dentro de un intervalo.  
Por ejemplo, si el intervalo fijado es [65, 90], el desplazamiento es de 3 unidades y el entero a desplazar es 70, el resultado sería 73. Si el entero fuese el 89 y el desplazamiento el 3, el resultado sería 92. Al no estar el 92 dentro del intervalo, se realiza un ciclo de forma que el 91 se transformaría en el 65 y el 92 en el 66. 
  
Se pide constuir un programa que lea dos enteros ```minimo``` y ```maximo``` que determinarán el intervalo ```[minimo, maximo]``` (supondremos que el usuario introduce como ```maximo``` un valor mayor o igual que ```minimo```). A continuación, el programa leerá un valor entero ```desplazamiento``` (supondremos que el usuario introduce un valor entre 0 y ```maximo-minimo```).  
Finalmente, el programa leerá un entero ```a_desplazar``` (supondremos que el usuario introduce un número entre ```minimo``` y ```maximo```). El programa sumará al valor leído el ```desplazamiento``` y lo convertirá en un entero dentro del intervalo ```[minimo, maximo]``` tal y como se ha descrito anteriormente.
```cpp
#include <iostream>

using namespace std;

int main()
{
	// Declaraciones
	int minimo, maximo, a_desplazar, desplazamiento;

	// Entradas
	cout << endl;
	cout << "Introduzca el valor minimo del intervalo cerrado (dato entero): ";
	cin >> minimo;

	cout << "Introduzca el valor maximo del intervalo abierto (dato entero): ";
	cin >> maximo;

	cout << "Introduzca el numero de posiciones que ha de desplazarse el "
		<< "numero entero (dato entero entre 0 y " << (maximo-minimo) << "): ";
	cin >> desplazamiento;

	cout << "Introduzca el valor del numero entero que se desplazara " <<
		desplazamiento << " posiciones (dato entero entre " << minimo << " y " << maximo << "): ";
	cin >> a_desplazar;

	// Cálculos
	// Suma la posición del entero más las unidades a desplazarlo
    
	int desplazado = a_desplazar + desplazamiento;

	// Si el resultado se sale del intervalo (desplazdo > maximo), el programa
	// calcula por cuanto se ha pasado del máximo y se lo suma al mínimo.
	// Esta cuenta se vuelve a almacenar en la variable desplazado.
	// Si no se pasó, la variable no se altera.
    
	desplazado = (desplazado > maximo)? (minimo-1 + (desplazado - maximo)) : desplazado;

	// Salida
	cout << endl;
	cout << "El entero " << a_desplazar << " desplazado " << desplazamiento
		<< " unidades a lo largo del intervalo [" << minimo << ", " << maximo << "] es: " << desplazado << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/DesplazamientoIntervalo.cpp)

## 4. Expresiones.cpp
Declarar las variables necesarias y traducir las siguientes fórmulas a expresiones válidas de C++:  
1. $$\dfrac{1+\dfrac{x²}{y}}{\dfrac{x³}{1+y}}$$
2. $$\dfrac{1+\dfrac{1}{3}\sin h - \dfrac{1}{7}\cos h}{2h}$$
3. $$\sqrt{1+\left(\dfrac{e^x}{x²}\right)²}$$
  
Algunas funciones de ```cmath```:  
$\sin x$ : ```sin(x)```  
$\cos x$ : ```cos(x)```  
$x^y$ : ```pow(x,y)```  
$\ln x$ : ```log(x)```  
$e^x$ : ```exp(x)```  

```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	// Declaraciones
	double x, y, h;

	// Entradas
	cout << endl;
	cout << "Introduzca el valor de x: ";
	cin >> x;

	cout << "Introduzca el valor de y: ";
	cin >> y;

	cout << "Introduzca el valor de h: ";
	cin >> h;

	// Cálculos
	double a = (1 + (pow(x, 2)/y)) / ((pow(x, 3)) / (1 + y));

	double b = (1 + 1/3.0 * sin(h) - 1/7.0 * cos(h)) / (2 * h);

	double c = sqrt(1 + pow(((exp(x)) / (pow(x, 2))), 2));

	// Salidas
	cout << endl;
	cout << "Para x = " << x << ", y = " << y << " y h = " << h << " :"<<endl;
	cout << "\tEl valor de la expresion a es: " << a << endl;
	cout << "\tEl valor de la expresion b es: " << b << endl;
	cout << "\tEl valor de la expresion c es: " << c << endl;
	cout << endl;

	return 0;
}

```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2003/Expresiones.cpp)

