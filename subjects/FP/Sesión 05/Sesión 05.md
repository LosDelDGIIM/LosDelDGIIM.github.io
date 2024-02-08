# Fundamentos de Programación. Sesión V de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión V de prácticas.

En esta sesión, se **introduce** el uso de las **estructuras condicionales** como **if/else**. Además, **se deberá realizar la comprobación de errores**, imprimiendo un mensaje en pantalla cuando lo introducido por el usuario no sea lo que esperamos.
  
## 1. MinusculaAMayusculaComp.cpp

Este ejercicio es una modificación del ejercicio ```1. MinusculaAMayuscula.cpp``` de la Sesión IV de prácticas, donde ahora tendremos que llevar a cabo una comprobación de los datos de entrada.  
  

Diseñe un programa que lea un carácter (supondremos que el usuario introduce una minúscula), lo pase a mayúscula y lo imprima en pantalla. Hacedlo sin usar las funciones ```toupper``` ni ```tolower``` de la biblioteca cctype. Para ello, debe considerarse la equivalencia en C++ entre los tipos enteros y caracteres.
```cpp
#include <iostream>

using namespace std;

int main()
{	
	// Numero de posiciones que hay que retroceder en la tabla ASCII
	// para pasar de minúscula a mayúscula.
	const int POSICIONES_ASCII = 'a' - 'A';
	const int MINUSCULA_MIN = 'a';
	const int MINUSCULA_MAX = 'z';

	char caracter_in, caracter_out;

	// ENTRADA

	cout << "Un caracter en minuscula: ";
	cin >> caracter_in;

	// Comprobamos si caracter_in es una letra minúscula:

	bool caracter_in_minuscula = caracter_in >= MINUSCULA_MIN && caracter_in <= MINUSCULA_MAX;

	if(!caracter_in_minuscula){
		cout << endl;
		cout << "Error: el dato introducido debe ser un caracter en minuscula." 
			 << endl;
		cout << endl;
	}

	// CÁLCULO

	// Si es una letra minúscula, la pasamos a mayúscula:

	if(caracter_in_minuscula)

		// Retrocede las posicinoes indicadas en la tabla ASCII.
		caracter_out = caracter_in - POSICIONES_ASCII;

	// SALIDA

	if(caracter_in_minuscula){
		cout << endl;
		cout << "Su caracter: " << caracter_out << endl;
		cout << endl;
	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2005/MinusculaAMayusculaComp.cpp)

## 2. TruncaDecimalesComp.cpp

Este ejercicio es una modificación del ejercicio ```3. TruncaDecimales.cpp``` de la Sesión IV de prácticas, donde ahora tendremos que llevar a cabo una comprobación de los datos de entrada.  
  
Se quiere construir un programa que lea un número real ```r``` y un número entero ```n``` y trunque ```r``` a tantas cifras decimales como indique ```n```. El resultado debe guardarse en una variable diferente. La única función que puede usar de ```cmath``` es ```pow```.  
  
Por ejemplo, si ```r = 1.2349``` y ```n = 2```, el resultado será ```1.23```  
Si ```r = 1.237``` y ```n = 2```, el resultado será ```1.23```  
Si ```r = 1.237``` y ```n = 1```, el resultado será ```1.2```  
Si ```r = 1.237``` y ```n = 0```, el resultado será ```1```
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	double numero;
	int digitos;

	// ENTRADAS
	
	cout << "Introduce un numero: ";
	cin >> numero;

	cout << "Cifras decimales: ";
	cin >> digitos;

	// Comprueba que digitos sea un número natural o 0
	bool digitos_correctos = digitos >= 0;

	if(!digitos_correctos){
		cout << endl;
		cout << "Error: El numero de digitos a redondear debe ser un numero "
			 << "natural." << endl;
		cout << endl;
	}

	// CÁLCULOS --------------------

	int parte_entera;
	double numero_truncado;

	// Realiza los cálculos sólo si digitos es un número natural:

	if(digitos_correctos){
		// auxiliar contiene los digítos del número truncado.
		int auxiliar = numero * pow(10, digitos);
	
		// Desplazamos la coma hasta la posición correcta, obteniendo
		// el número numero truncado a digitos decimales.
		numero_truncado = auxiliar / pow(10, digitos);
	
		// Cuenta el número de dígitos en la parte entera:
		// (trunca numero a las unidades y cuenta el número de caracteres)
		parte_entera = to_string((int)numero).length();
	}

	// SALIDA ----------------------

	if(digitos_correctos){
	
		// Formateamos la consola para mostrar números decimales.
		cout.setf(ios::fixed);

		cout << endl;
		cout << "Su numero truncado: " << setw(parte_entera + 1 + digitos) 
			 << setprecision(digitos) << numero_truncado << endl;	
		cout << endl;
	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2005/TruncaDecimalesComp.cpp)

## 3. TarifaAereaDescuentos.cpp
Una compañía aérea establece el precio del billete como sigue:  
En primer lugar, se fija una tarifa base de 150€, la misma para todos los destinos.  
Si el destino se encuentra a menos de 300 km, el precio final es la tarifa base.  
Para destino a más de 300km, se suman 10 céntimos por cada kilómetro de distancia al destino (a partir del kilómetro 300).  
  
La compañía aérea decide incluir descuentos a las tarifas ya calculadas con el siguiente criterio:  
1. Un primer descuento está determinado por el número de kilómetros del trayecto: Si el trayecto es mayor que 700km, se aplica un descuento del 2%.
2. El segundo descuento dependerá del número de puntos de la tarjeta de fidelización del cliente: Si el número de puntos es mayor que 100, se aplica un descuento del 3% y si es mayor que 200%, se aplica un descuento del 4%.  
   
Los dos descuentos anteriores son independientes y acumulables. En cualquier caso se aplica sobre el precio del billete. 
  
Diseñe un programa que pida el número de kilómetros al destino y el número de puntos de su tarjeta de fidelización. El programa deberá calcular el precio total al destino.
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

int main(){

	// DECLARACIONES	

	int kilometros;
	double puntos;		// quizás los puntos puedan contener decimales.

	const double PRECIO_BASE = 150.0;	// en euros
	const double PRECIO_POR_KM = 0.1;	// 10 cents

	// kilometros cuyo precio va incluido en el base:
	const int KILOMETROS_LIMITE = 300;

	const int KILOMETROS_DESCUENTO = 700;
	const double DESCUENTO_POR_KILOMETROS = 2;	// 2%

	const int PUNTOS_DESCUENTO1 = 100, PUNTOS_DESCUENTO2 = 200;
	const double DESCUENTO1_POR_PUNTOS = 3;	// 3%
	const double DESCUENTO2_POR_PUNTOS = 4;	// 4%

	// Al tratarse de una aerolínea, consideramos que unos kilómetros son
	// correctos si al menos son superiores a 10km.
	const int KILOMETROS_MIN_ADECUADOS = 10;

	// ENTRADA	

	cout << "Kilometros al destino: ";
	cin >> kilometros;

	// Comprobaciones de que los kilómetros son correctos
	bool kilometros_adecuados = kilometros > KILOMETROS_MIN_ADECUADOS;

	if(kilometros_adecuados){
	
		cout << "Puntos de su tarjeta: ";
		cin >> puntos;

	}else{
		
		cout << endl;
		cout << "Error: Los kilometros deben ser mayores que " 
			 << KILOMETROS_MIN_ADECUADOS << " km." << endl;
		cout << endl;

	}

	// Nota: no consideramos los puntos negativos como erróneos ya que la 
	// empresa puede contemplarlos como una penalización.

	// CÁLCULOS  *************************************************************

	// Si los kilómetros son los adecuados, realizamos los cálculos.

	double precio_final, precio_sin_descuento;

	if(kilometros_adecuados){
	
		if(kilometros <= KILOMETROS_LIMITE)
			precio_sin_descuento = PRECIO_BASE;
	
		else{
			// Calcula el precio, sabiendo que hasta 300 km el precio es de 
			// 150 y que a partir de estos cada kilómetros son 10 céntimos.
	
			// Kilómetros cuyo precio no va incluido en el precio base.
			int kilometros_extra = kilometros - KILOMETROS_LIMITE;
	
			precio_sin_descuento = PRECIO_BASE + kilometros_extra * PRECIO_POR_KM;
		
		}
	
		// Descuentos a aplicar:
	
		double descuento_kilometros = 0, descuento_puntos = 0;
	
		// Si los kilómetros son mayores a unos, se aplica un descuento.
		if(kilometros > KILOMETROS_DESCUENTO){
			descuento_kilometros = DESCUENTO_POR_KILOMETROS;
		}
	
		// Si los puntos del cliente son mayores a PUNTOS_DESCUENTO1 se aplica
		// un descuento y si son mayores a PUNTOS_DESCUENTO2 se aplica un 
		// descuento mayor
	
		if(puntos > PUNTOS_DESCUENTO2)
			descuento_puntos = DESCUENTO2_POR_PUNTOS;
	
		else{
			
			if(puntos > PUNTOS_DESCUENTO1)
				descuento_puntos = DESCUENTO1_POR_PUNTOS;
	
		}
	
		double descuento = descuento_kilometros + descuento_puntos;
	
		// Aplicamos el descuento
	
		precio_final = 
			precio_sin_descuento - precio_sin_descuento * (descuento / 100);

	}

	// SALIDA  **************************************************************

	if(kilometros_adecuados){
	
		// Formateamos la consola para que se muestren los céntimos de forma
		// correcta.
		cout.setf(ios::fixed);
	
		cout << endl;

		cout << "El precio del billete es de " << setw(6) << setprecision(2) 
				 << precio_final << " euros." << endl;

		cout << endl;
	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2005/TarifaAereaDescuentos.cpp)

## 4. CifradoRotacion2.cpp

Este ejercicio es una modificación del ejercicio ```2. CifradoRotacion.cpp``` de la Sesión IV de prácticas, donde ahora tendremos que llevar a cabo una comprobación de los datos de entrada, además de una dificultad añadida.  
  
Pra intercambiar mensajes de forma privada, se utilizan distintos algoritmos que codifican y descodifican una cadena de caracteres. Uno de los más sencillos es el cifrado de _rotación_ (o _cifrado césar_). Consiste en seleccionar un número entero como clave y desplazar las letras del alfabeto tantas posiciones como indique la clave. Consideraremos únicamente las mayúsculas.  
  
Se considera una representación circular del alfabeto. Por ejemplo, el carácter que sigue a la 'Z' es 'A'. Si la clave es 4, 'A' se reemplaza por 'E' y 'Z' por 'D'. Admitimos la clave 0 como clave válida.  
    
Construya un programa que lea un entero que será nuestra clave y un carácter (suponemos que se incluye un carácter en mayúsculas entre 'A' y 'Z' sin considerar 'Ñ'). El programa codificará el carácter según la clave introducida, mostrándolo por pantalla.  
  
Este es un ejercicio repetido de la sesión 4, pero en este caso, **no podrá usar el operador ```%```**, sino que podrá usar condicionales simples como estructuras if/else.
```cpp
#include <iostream>

using namespace std;

int main()
{
	int clave;
	char caracter;

	// Constantes que nos ayudarán en los cálculos para que el caracter
	// codificado no se salga del intervalo [A, Z].
	const int MIN = 'A', MAX = 'Z';
	const int RANGO = MAX - MIN + 1; 	//Número de letras en [A, Z].

	// ENTRADAS  ******************************************************

	cout << "La clave: ";
	cin >> clave;

	// Comprueba que la clave esté entre [0, RANGO-1]
	bool clave_correcta = clave >= 0 && clave <= RANGO - 1;

	if(!clave_correcta){
		cout << endl;
		cout << "La clave es incorrecta, debe estar en el intervalo [0, 25]." 
			 << endl;
		cout << endl;
	}else{
		cout << "El caracter (mayuscula): ";
		cin >> caracter;
	}

	// Comprueba que el caracter introducido sea una letra mayúscula
	bool caracter_correcto = caracter >= MIN && caracter <= MAX;

	// Si la clave era incorrecta, consideramos que el programa finaliza
	// por tanto, no se muestra esta opción
	if(!caracter_correcto && clave_correcta){
		cout << endl;
		cout << "El caracter es incorrecto, debe ser una letra mayuscula." 
			 << endl;
		cout << endl;
	}

	bool datos_correctos = clave_correcta && caracter_correcto;

	// CÁLCULO  ******************************************************

	char caracter_final;

	if(datos_correctos){
	
		// Obtiene el caracter rotado
		char caracter_rotado = caracter + clave;
	
		// Si está fuera del intervalo, hace que esté dentro
		if(caracter_rotado > MAX)
			caracter_final = caracter_rotado - RANGO;

		else
			caracter_final = caracter_rotado;
	}

	// SALIDA  ******************************************************

	if(datos_correctos){
		cout << endl;
		cout << "El caracter codificado: " << caracter_final << endl;
		cout << endl;
	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2005/CifradoRotacion2.cpp)

## 5. ConsultaMulta.cpp
En este ejercicio queremos determinar la sanción a aplicar en una autovía, cuyo límite de velocidad es 120 Km/h. En la siguiente tabla se muestra la velocidad del vehículo y la sanción correspondiente (número de puntos del carnet de conducir que se restan y la multa en euros)  
  
```(120, 150] --> 0, 100```  
```(150, 170] --> 2, 300```  
```(170, 180] --> 4, 400```  
```(180, 190] --> 6, 500```  
```(190, ...) --> 6, 600```  
  
Escriba un programa que lea la velocidad del vehículo e imprima en pantalla la sanción correspondiente (número de puntos a detraer y multa en euros).
```cpp
#include <iostream>

using namespace std;

int main(){
	
	int velocidad;

	const int INTERVALO1_VEL_MIN = 120, INTERVALO2_VEL_MIN = 150,
		INTERVALO3_VEL_MIN = 170, INTERVALO4_VEL_MIN = 180, 
		INTERVALO5_VEL_MIN = 190;

	const int PUNTOS_INTERVALO1 = 0, PUNTOS_INTERVALO2 = 2, 
		PUNTOS_INTERVALO3 = 4, PUNTOS_INTERVALO4 = 6, PUNTOS_INTERVALO5 = 6;

	const int MULTA_INTERVALO1 = 100, MULTA_INTERVALO2 = 300, 
		MULTA_INTERVALO3 = 400, MULTA_INTERVALO4 = 500, MULTA_INTERVALO5 = 600;

	// ENTRADAS

	cout << "Introduzca la velocidad: ";
	cin >> velocidad;

	// Comprobamos que se ha introducido una velocidad verídica.
	bool velocidad_positiva = velocidad >= 0;

	if(!velocidad_positiva){
		cout << endl;
		cout << "Error: la velocidad debe ser positiva." << endl;
		cout << endl;
	}

	// CÁLCULOS

	int puntos = 0, multa = 0;

	if(velocidad_positiva){
	
		if(velocidad > INTERVALO5_VEL_MIN){
	
			multa = MULTA_INTERVALO5;
			puntos = PUNTOS_INTERVALO5;

		}else{
			
			if(velocidad > INTERVALO4_VEL_MIN){
	
				multa = MULTA_INTERVALO4;
				puntos = PUNTOS_INTERVALO4;

			}else{

				if(velocidad > INTERVALO3_VEL_MIN){
	
					multa = MULTA_INTERVALO3;
					puntos = PUNTOS_INTERVALO3;

				}else{
	
					if(velocidad > INTERVALO2_VEL_MIN){
	
						multa = MULTA_INTERVALO2;
						puntos = PUNTOS_INTERVALO2;

					}else{
		
						if(velocidad > INTERVALO1_VEL_MIN){
	
							multa = MULTA_INTERVALO1;
							puntos = PUNTOS_INTERVALO1;

						}
					}	
				}
			}
		}
	}

	// SALIDAS

	// Si algún parámetro de la multa es 0, no se muestra.
	// Si ambos son 0, se muestra que no se aplica ninguna sanción.

	if(velocidad_positiva){
		
		cout << endl;

		if(multa == 0 && puntos == 0)
			cout << "A usted no se le aplica ninguna sancion." << endl;

		else{
			
			cout << "Se le aplica la siguiente sancion:" << endl;

			// Esta opción no se contempla, pero si se altera el valor de las
			// constantes podria contemplarse.
			if(multa != 0)
				cout << "\tUna multa de " << multa << " euros." << endl;

			if(puntos != 0)
				cout << "\tUna perdida de " << puntos << " puntos del carnet." 
				 << endl;

		}

		cout << endl;

	}

	return 0;
}
```
[Ir a al solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2005/ConsultaMulta.cpp)

## 6. ConversionUnidadesMedida.cpp

Este programa es una versión más desarrollado que el ejercicio ```2. ConversionUnidades.cpp``` de la Sesión III de prácticas, donde ahora las unidades de medida de entrada y salida son variables.  
  
Realice un programa que realice la converesión entre dos unidades de distancia del sistema internacional. Las unidades contempladas serán:  
```mm (milímetros)```  
```cm (centímetros)```  
```m (metros)```  
```km (kilómetros)```  
  
El programa mostrará el _prompt_ "> " y el usuario escribirá cuatro palabras:  
```> valor unidad_inicial a unidad_final```  
  
El programa mostrará el resultado de la transformación. Por ejemplo, si quisiéramos transformar 7 centímetros a metros, escribiremos:  
```> 7 cm a m```  
```7.000 cm = 0.007 m```  
  
Y para convertir 5.2 kilómetros a milímetros:
```> 5.2 km a mm```  
```5.200 km = 5200000.000 mm```  
  
Notas:
1. Se permite la transformación entre todas las unidades citadas anteriormente.
2. Intente minimizar el número de comprobaciones a realizar.
3. Tenga en cuenta todas las situaciones de error. En caso de error deberá informar del error y terminar la ejecución del programa.
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	
	double valor;
	string unidades_valor, unidades_transformar;
	char a;		// Donde almacenamos la preposición 'a'.

	const double MM_A_M = 0.001, CM_A_M = 0.01, KM_A_M = 1000;
	const double M_A_MM = 1000, M_A_CM = 100, M_A_KM = 0.001;

	// ENTRADAS  *********************************************************

	cout << "> ";
	cin >> valor;
	cin >> unidades_valor;

	// ALmacenamos 'a' para liberar el buffer y acceder a unidades_transformar
	cin >> a;	
	cin >> unidades_transformar;

	// Comprobamos que tanto el valor, las unidades del valor, las unidades a 
	// transformar y el formto son correctos:

	bool valor_correcto = valor >= 0;

	bool preposicion_correcta = a == 'a';

	bool unidades_valor_correctas = 
		unidades_valor == "mm" || unidades_valor == "cm" 
		|| unidades_valor == "m" || unidades_valor == "km";

	bool unidades_transformar_correctas =
		unidades_transformar == "mm" || unidades_transformar == "cm" 
		|| unidades_transformar == "m" || unidades_transformar == "km";

	bool datos_correctos = valor_correcto && preposicion_correcta 
		&& unidades_valor_correctas && unidades_transformar_correctas;

	// Se imprime error en caso de haberlo, especificando el error concreto

	if(!datos_correctos){
		cout << endl;
		cout << "Error:" << endl;

		if(!preposicion_correcta)
			cout << "Especifique un formato [valor] [unidades] a [unidades]" 
				 << endl;

		else{

			if(!valor_correcto)
				cout << "El valor debe ser positivo." << endl;
	
			if(!unidades_valor_correctas && !unidades_transformar_correctas)
				cout << "Las unidades \"" << unidades_valor << "\" y \"" 
					 << unidades_transformar << "\" no estan contempladas." 
					 << endl;
	
			else{
	
				if(!unidades_valor_correctas)
					cout << "Las unidades \"" << unidades_valor 
						 << "\" no estan contempladas." << endl;
		
				if(!unidades_transformar_correctas)
					cout << "Las unidades \"" << unidades_transformar 
						 << "\" no estan contempladas." << endl;
	
			}
		}

		cout << endl;
	}

	// CÁLCULOS  *********************************************************

	double valor_final = 0, valor_en_m = 0;

	// Realiza los cálculos si los datos son correctos

	if(datos_correctos){
		if(unidades_valor == unidades_transformar){
		
			// Si se quiere pasar a las mismas unidades, el valor es igual.
			valor_final = valor;
	
		}else{
	
			// En caso de no ser iguales, pasamos el valor a metros:
			if(unidades_valor == "mm"){
				valor_en_m = valor * MM_A_M;
			}
	
			if(unidades_valor == "cm"){
				valor_en_m = valor * CM_A_M;
			}
	
			if(unidades_valor == "m"){
				valor_en_m = valor;
			}
	
			if(unidades_valor == "km"){
				valor_en_m = valor * KM_A_M;
			}

			// Una vez que tenemos el valor en metros, lo pasamos a las 
			// unidades correctas:
			if(unidades_transformar == "mm"){
				valor_final = valor_en_m * M_A_MM;
			}

			if(unidades_transformar == "cm"){
				valor_final = valor_en_m * M_A_CM;
			}

			if(unidades_transformar == "m"){
				valor_final = valor_en_m;
			}

			if(unidades_transformar == "km"){
				valor_final = valor_en_m * M_A_KM;
			}
	
		}
	}

	// SALIDAS  *********************************************************

	if(datos_correctos){

		// Formateamos la consola
		cout.setf(ios::fixed);

		cout << setw(5) << setprecision(3);

		// Imprimimos el resultado
		cout << valor << (" " + unidades_valor + " = ") << valor_final 
			 << (" " + unidades_transformar);

		cout << endl;

	}
	
	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2005/ConversionUnidadesMedida.cpp)  
En este caso, merece la pena comentar que la forma más eficiente y sencilla de hacer el programa es pasar las unidades de entrada a una intermedia, como pueden ser los metros, y posteriormente pasar estos a las unidades de salida. 
Varios alumnos no hicieron esto y contemplaron todas las posibilidades, cosa que se evaluó negativamente. En este caso contamos con sólo 4 unidades de medida y hay 4! = 26 posibilidades, pero con nada que aumentemos el número de unidades, el número de combinaciones aumenta factorialmente.

Nota: a continuación, los dos últimos ejercicios deberán estar implementados con tipos enumerados.

## 7. SubidaSalarioPrecario.cpp
Cree un programa que lea el valor de la edad (dato de tipo entero) y salario (dato de tipo real) de una persona. Suba el salario un 4% si es mayor de 65 o menor de 35 años. Si a demás de cumplir la condición anterior, también tiene un salario inferior a 300€, se le subirá otro 3%, mientras que si su salario es mayor o igual que 300€ pero inferior a 900€, se le subirá sólo un 1.5%.  
  
Imprima el resultado en pantalla indicando qué subidas se han aplicado.
```cpp
#include <iostream>

using namespace std;

int main(){
	
	int edad;
	double salario;

	const int EDAD_MAYOR = 65, EDAD_MENOR = 35;
	const double PORC_EDAD = 4;		// 4%

	const int SALARIO_BAJO = 300;
	const double PORC_SALARIO = 3; 	// 3%

	const int SALARIO_REDUCIDO = 900;
	const double PORC_SALARIO2 = 1.5;	// 1.5%

	// Constantes para verificar la entrada de datos adecuados:
	const int EDAD_MIN_ADECUADA = 16, EDAD_MAX_ADECUADA = 80;
	const int SALARIO_MIN_ADECUADO = 0;

	// Creamos un tipo enumerado con todas las razones por las que podemos
	// subirle el salario al empleado.
	enum class Razones 
		{ninguna, edad, edad_salario_bajo, edad_salario_reducido};

	// ENTRADAS  *********************************************************

	cout << "Su edad: ";
	cin >> edad;

	// Consideramos que la edad es correcta si está en [16, 80], ya que se
	// trata de la edad de un trabajador.
	bool edad_correcta = edad >= EDAD_MIN_ADECUADA && edad <= EDAD_MAX_ADECUADA;

	if(!edad_correcta){
		cout << endl;
		cout << "Error: edad inadecuada." << endl;
		cout << endl;
	}else{
		cout << "Su salario: ";
		cin >> salario;
	}
	
	// Los salarios negativos se contemplan como error.
	bool salario_correcto = salario >= SALARIO_MIN_ADECUADO;

	// Se imprime el error sólo si la edad era correcta, ya que si era 
	// incorrecta el programa ya finaliza.
	if(!salario_correcto && edad_correcta){
		cout << endl;
		cout << "Error: salario inadecuado." << endl;
		cout << endl;
	}

	bool datos_correctos = edad_correcta && salario_correcto;

	// CÁLCULOS  **********************************************************

	Razones situacion;
	double salario_final;

	// Realiza los cálculos sólo si los datos son correctos
	if(datos_correctos){

		// Asigna a situacion el tipo enum correspondiente a la situación
		if(edad > EDAD_MAYOR || edad < EDAD_MENOR){
			
			if(salario < SALARIO_REDUCIDO){
				
				if(salario < SALARIO_BAJO)
					situacion = Razones::edad_salario_bajo;

				else
					situacion = Razones::edad_salario_reducido;

			}else
				situacion = Razones::edad;

		}else
			situacion = Razones::ninguna;

		// Determina el procentaje de subida

		double porc_subida;

		switch(situacion){
			case Razones::ninguna:
				porc_subida = 0;
				break;
			
			case Razones::edad:
				porc_subida = PORC_EDAD;
				break;

			case Razones::edad_salario_bajo:
				porc_subida = PORC_EDAD + PORC_SALARIO;
				break;

			case Razones::edad_salario_reducido:
				porc_subida = PORC_EDAD + PORC_SALARIO2;
				break;
		}

		// Calcula el salario final
		salario_final = salario + salario * (porc_subida / 100);

	}

	// SALIDAS  *********************************************************

	if(datos_correctos){
		cout << endl;
		cout << endl;

		cout << "Su salario final es de " << salario_final << " euros." 
			 << endl;
		
		cout << endl;

		// Imprime si se le ha subido el salario o si no

		switch(situacion){
			case Razones::ninguna:
				cout << "No se ha aplicado ninguna subida" << endl;
				break;
			
			case Razones::edad:
				cout << "Se ha aplicado una subida del " << PORC_EDAD 
					 << "% por la edad." << endl;
				break;

			case Razones::edad_salario_bajo:
				cout << "Se ha aplicado una subida del " << PORC_EDAD 
					 << "% por la edad." << endl;
				cout << "Ademas de otra del " << PORC_SALARIO 
					 << "% por el salario bajo." << endl;
				break;

			case Razones::edad_salario_reducido:
				cout << "Se ha aplicado una subida del " << PORC_EDAD 
					 << "% por la edad." << endl;
				cout << "Ademas de otra del " << PORC_SALARIO2 
					 << "% por el salario reducido." << endl;
				break;
		}

		cout << endl;
	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2005/SubidaSalarioPrecario.cpp)

## 8. MayAMinViceversa.cpp
Desarrolle un programa que pida un carácter al usuario y lo almacene en una variable ```letra_original```. El programa deberá modificarlo y guardarlo en una variable ```letra_convertida``` según el siguiente criterio:  
1. Si era una letra mayúscula, se debe pasar a minúscula.
2. Si era una letra minúscula, se debe pasar a mayúscula.
3. Si no se trata de un carácter alfabético, no deberá modificarse.  
  
Finalmente, se imprimirá en pantalla alguno de los siguientes mensajes:  
La letra era una mayúscula. Una vez convertida es ```letra_convertida```.
La letra era una mínúscula. Una vez convertida es ```letra_convertida```.
El carácter era un dígito.
El carácter no era una letra ni un dígito.  
  
La solución deberá llevarse a cabo con un tipo de dato enumerado que permita guardar el _tipo de carácter_ de ```letra_original```.  
  
Nota: Las vocales con tilde y cualquier letra que no se encuentre en el alfabeto inglés se podrán englobar en la categoría de los carácteres que no sean letras.
```cpp
#include <iostream>

using namespace std;

int main(){
	
	char letra_original;

	const int MIN_MINUSCULA = 'a', MAX_MINUSCULA = 'z';
	const int MIN_MAYUSCULA = 'A', MAX_MAYUSCULA = 'Z';

	enum class TiposCaracter {mayuscula, minuscula, digito, otro};

	// ENTRADA

	cout << "Introduzca un caracter: ";
	cin >> letra_original;

	// CÁLCULOS

	// Asignamos a la variable tipo el tipo enum correspondiente al caracter
		
	TiposCaracter tipo;
	char letra_convertida;

	if(letra_original >= MIN_MINUSCULA && letra_original <= MAX_MINUSCULA){
		tipo = TiposCaracter::minuscula;
		letra_convertida = toupper(letra_original);
	
	}else{

		if(letra_original >= MIN_MAYUSCULA && letra_original <= MAX_MAYUSCULA){
			tipo = TiposCaracter::mayuscula;
			letra_convertida = tolower(letra_original);
	
		}else{

			letra_convertida = letra_original;

			if(isdigit(letra_original))
				tipo = TiposCaracter::digito;	

			else
				tipo = TiposCaracter::otro;
		}
	}

	// SALIDAS

	cout << endl;

	switch(tipo){
		case TiposCaracter::minuscula:
			cout << "La letra era una minuscula." << endl;
			cout << "La letra convertida: " << letra_convertida;
			break;
	
		case TiposCaracter::mayuscula:
			cout << "La letra era una mayuscula." << endl;
			cout << "La letra convertida: " << letra_convertida;
			break;

		case TiposCaracter::digito:
			cout << "El caracter era un digito." << endl;
			break;

		case TiposCaracter::otro:
			cout << "El caracter no era ni una letra minuscula o mayuscula"
				 << " ni un digito." << endl;
			break;
	}

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2005/MayAMinViceversa.cpp)

# Ejercicios Opcionales
## 1. HaversineConMinimo.cpp
Este programa es una modificación del ejercicio ```2. Harvesine.cpp``` de la Sesión IV de prácticas, donde ahora tiene prohibido usar la función ```min``` de la biblioteca ```algorithm``` y deberá emplear una estructura condicional. Le recordamos el enunciado del ejercicio:  
  
El sistema de posicionamiento global, más conocido por sus siglas en inglés, **GPS** (Global Positioning System), es un sistema que permite determinar en toda la Tierra la posición de un objeto.  
  
Un dispositivo GPS es capaz de captar y registrar la posición en el espacio en base a tres coordenadas: latitud y longitud (grados) y altura (metros). Los valores de latitud y longitud deben verificar $-90 ≤ lat ≤ 90$ y $-180 < lon ≤ 180$.  
  
Construir un programa que lea la latitud y longitud (posición en el plano) de dos puntos y calcule la distancia sobre plano entre los dos puntos (distancia que no considera la altura de los puntos).  
  
Use la llamada fórmula del Haversine:
1. $$a = \sin² \left(\dfrac{1}{2}(lat_2-lat_1)\right)+\cos lat_1 \cos lat_2 \sin²\left(\dfrac{1}{2}(lon_2-lon_1)\right)$$
2. $$c = 2 \arcsin \min{\{1, \sqrt{a}\}}$$
3. La distancia será $d_p = R \cdot c$ donde:  
   $R = 6372797.560856$ metros, la longitud media del radio terrestre.  
  
Ha de tener en cuenta que:  
a) Los datos de latitud y longitud en las fórmulas vienen expresados en radianes. Recuerde que los valores de latitud y longitud que se leen están expresados en grados por lo que habrá de transformarlos a radianes.  
b) La función arcoseno ($\arcsin$) viene ya implementada en la biblioteca ```cmath``` con el nombre ```asin```.  
c) Puede usar la función ```min``` de la biblioteca ```algorithm```.  
   
Una vez calculada la distancia sobre plano, calcular la distancia real entre los dos puntos (que considera sus alturas). Se trata de la longitud del segmento que une los puntos. Observe que puede formar un triángulo rectángulo a partir del segmento que une los puntos en el plano y el segmento que une sus alturas.
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main(){
	double latitud1, latitud2, longitud1, longitud2, altura1, altura2;

	const double PI = 6*asin(0.5);
	const double GRADOS_A_RADIANES = PI / 180;

	const double RADIO_TERRESTRE = 6372797.560856;
	const int METROS_A_KM = 1000;

	// ENTRADAS

	cout << "Punto 1: " << endl;
	cout << "\tLatitud [-90, 90]: "; 
	cin >> latitud1;
	cout << "\tLongitud [-180, 180]: ";
	cin >> longitud1;
	cout << "\tAltura: ";
	cin >> altura1;
	
	cout << endl;

	cout << "Punto 2: " << endl;
	cout << "\tLatitud [-90, 90]: "; 
	cin >> latitud2;
	cout << "\tLongitud [-180, 180]: ";
	cin >> longitud2;
	cout << "\tAltura: ";
	cin >> altura2;

	// CÁLCULOS
	// Pasamos los datos de longitud y latitud a radianes para operar con 
	// ellos:
	
	double rad_latitud1 = latitud1 * GRADOS_A_RADIANES;
	double rad_latitud2 = latitud2 * GRADOS_A_RADIANES;
	double rad_longitud1 = longitud1 * GRADOS_A_RADIANES;
	double rad_longitud2 = longitud2 * GRADOS_A_RADIANES;

	// Calculamos los datos a y c de la fórmula del Haversine:

	double a = pow(sin(0.5*(rad_latitud2 - rad_latitud1)), 2) 
		+ cos(rad_latitud1) * cos(rad_latitud2) 
		* pow(sin(0.5*(rad_longitud2 - rad_longitud1)), 2);

	// Calculamos cual es el mínimo entre 1 y sqrt(a):
	double min = (1.0 <= sqrt(a)) ? 1 : sqrt(a);

	double c = 2 * asin(min);

	double distancia_plano = RADIO_TERRESTRE * c;

	double diferencia_alturas = abs(altura1 - altura2);

	// Calculamos la distancia real entre los dos puntos, sabiendo que es la
	// hipotenusa del triángulo rectángulo que forman los catetos de
	// distancia_plano y diferencia_alturas.

	double distancia_real = 
		sqrt(pow(distancia_plano, 2) + pow(diferencia_alturas, 2));

	// Finalmente, expresamos las distancias en kilómetros:
	distancia_plano = distancia_plano / METROS_A_KM;
	distancia_real = distancia_real / METROS_A_KM;

	// SALIDAS

	cout << endl;
	cout << "Distancia sobre el plano: " << distancia_plano << " km." << endl;
	cout << "Distancia real: " << distancia_real << " km." << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2005/HaversineConMinimo.cpp)

## 2. DescuentoVentas.cpp
Construya un programa para calcular el importe total a facturar de un pedido. El programa leerá el número de unidades vendidas y el precio de venta de cada unidad. Si la cantidad vendida es mayor de 100 unidades, se le aplica un descuento del 3%. Además, si la cantidad vendida es mayor de 100 unidades y el precio total es mayor que 700%, el descuento total a aplicar será del 5%.

## 3. ReajustarRenta.cpp
Cree un programa que lea los datos fiscales de una persona, reajuste su renta bruta según el criterio que se indica posteriormente e imprima su renta neta final.  
- La renta bruta es la cantidad de dinero íntegra que el trabajador gana.
- La retención fiscal es el tanto por ciento que el gobierno se queda.
- La renta neta es la cantidad que le queda al trabajador después de quitarle el porcentaje de retención fiscal, es decir:
$$Renta neta = Renta bruto - Renta bruta * Retencion / 100$$
  
Los datos a leer son:
1. Si la persoan es un trabajador autónomo o no.
2. Si es pensionista o no.
3. Si está casada o no.
4. Renta bruto (toatal de ingresos obtenidos).
5. Retención inicial.  
  
La modificación se hará de la siguiente forma:
1. Bajar un 3% la retención fiscal a los autónomos.
2. Para los no autónomos:
    1. Se sube un 1% la retención fiscal a todos los pensionistas.
    2. Al resto de los trabajadores se les aplica una subida lineal del 2%. Una vez hecha esta subida, se le aplica (sobre el resultado anterior) las siguientes subidas adicionales a la retención fiscal:
        1. Subir otro 2% si la renta bruta es menor de 20.000€
        2. Subir otro 2.5% a los casados con renta bruta supuerior a 20.000€
        3. Subir otro 3% a los solteros con renta bruta superior a 20.000€  
  
Una vez calculada la retención final, habrá que aplicarla sobre la renta bruta para así obtener la renta final del trabajador.

## 4. Parking.cpp
La tabla para el cálculo del precio a pagar en un parking es la siguiente:  
```Desde el minuto 0 al 30: 0.0412€ por minuto.```  
```Desde el minuto 31 al 90: 0.0370€ por minuto.```  
```Desde el minuto 91 al 120: 0.0311€ por minuto.```  
```Desde el minuto 121 al 660: 0.0305€ por minuto.```  
```Desde el minuto 661 al 900: 0.0270€ por minuto.```  
```Desde el minuto 901 hasta máximo 24h: se deberán abonar 35€.```  
  
Dadas las horas de entrada y salida del parking (hora y minuto), construya un programa que calcule la tarifa final en euros a cobrar.  
  
Ejemplo: si el tiempo de permanencia es de 1h y 34 min = 94 min, los primeros 30 minutos se facturan a 0.0412 el minuto, los siguientes 60 se facturan a 0.0370 el minuto, y los 4 restante a 0.0311 el minuto.  
  
Nota: Puede suponer que el dato introducido por el usuario estará en el rango [0, 24h].
