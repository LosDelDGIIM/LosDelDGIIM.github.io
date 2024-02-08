# Fundamentos de Programación. Sesión IV de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión IV de prácticas.


## 1. MinusculaAMayuscula.cpp
Diseñe un programa que lea un carácter (supondremos que el usuario introduce una minúscula), lo pase a mayúscula y lo imprima en pantalla. Hágalo sin usar las funciones ```toupper``` ni ```tolower``` de la biblioteca ```cctype```. Para ello, debe considerarse la equivalencia en C++ entre los tipos enteros y caracteres.  
Nota: el carácter debe estar entre 'a' y 'z' (sin ser 'ñ').
```cpp
#include <iostream>

using namespace std;

int main()
{
	// Numero de posiciones que hay que retroceder en la tabla ASCII
	// para pasar de minúscula a mayúscula.
    
	const int POSICIONES_ASCII = 'a' - 'A';
	char caracter_in;

	// ENTRADA

	cout << "Un caracter en minuscula: ";
	cin >> caracter_in;

	// CÁLCULO
	// Retrocede las posicinoes indicadas en la tabla ASCII.
    
	char caracter_out = caracter_in - POSICIONES_ASCII;

	// SALIDA
	cout << endl;
	cout << "Su caracter: " << caracter_out << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/MinusculaAMayuscula.cpp)

## 2. CifradoRotacion.cpp
Pra intercambiar mensajes de forma privada, se utilizan distintos algoritmos que codifican y descodifican una cadena de caracteres. Uno de los más sencillos es el cifrado de _rotación_ (o _cifrado césar_). Consiste en seleccionar un número entero como clave y desplazar las letras del alfabeto tantas posiciones como indique la clave. Consideraremos únicamente las mayúsculas.  
  
Se considera una representación circular del alfabeto. Por ejemplo, el carácter que sigue a la 'Z' es 'A'. Si la clave es 4, 'A' se reemplaza por 'E' y 'Z' por 'D'. Admitimos la clave 0 como clave válida.  
  
Construya un programa que lea un entero que será nuestra clave y un carácter (suponemos que se incluye un carácter en mayúsculas entre 'A' y 'Z' sin considerar 'Ñ'). El programa codificará el carácter según la clave introducida, mostrándolo por pantalla.
```cpp
#include <iostream>

using namespace std;

int main()
{
	int clave;
	char caracter;

	// Constantes que nos ayudarán en los cálculos para que el cáracter
	// codificado no se salga del intervalo [A, Z].
	const int MIN = 'A', MAX = 'Z';
	const int RANGO = MAX - MIN + 1; 	//Número de letras en [A, Z].

	// ENTRADAS

	cout << "La clave: ";
	cin >> clave;

	cout << "El caracter (mayuscula): ";
	cin >> caracter;

	// CÁLCULO
	
	char caracter_codificado = MIN + ((caracter - MIN + clave) % RANGO);

	/*
		Cualquier número y = MIN + (x % RANGO) (Sea x cualquier número)
		está dentro del intervalo [MIN, MAX].

		caracter - MIN está dentro del intervalo [MIN, MAX]
		Al sumarle la clave, puede que se salga, por lo que aplicamos
		la ecuación explicada anteriormente.
	*/

	// SALIDA

	cout << endl;
	cout << "El caracter codificado: " << caracter_codificado << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/CifradoRotacion.cpp)

## 3. TruncaDecimales.cpp
Se quiere construir un programa que lea un número real ```r``` y un número entero ```n``` y trunque a ```r``` tantas cifras decimales como indique ```n```. El resultado debe guardarse en una variable diferente. La única función que puede usar de ```cmath``` es ```pow```.  
  
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

	// CÁLCULOS --------------------

	// auxiliar contiene los digítos del número truncado.
	int auxiliar = numero * pow(10, digitos);

	// Desplazamos la coma hasta la posición correcta, obteniendo
	// el número numero truncado a digitos decimales.
	double numero_truncado = ((double)auxiliar) / pow(10, digitos);

	// Cuenta el número de dígitos en la parte entera:
	// (trunca numero a las unidades y cuenta el número de caracteres)
	int parte_entera = to_string((int)numero).length();

	// SALIDA ----------------------

	// Formateamos la consola para mostrar números decimales.
	cout.setf(ios::fixed);

	// Mostramos la salida, reservando un ancho para la parte entera,
	// los dígitos decimales y el punto decimal.
	cout << endl;
	cout << "Su numero truncado: " << setw(parte_entera + 1 + digitos) 
		 << setprecision(digitos) << numero_truncado << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/TruncaDecimales.cpp)

## 4. ExpresionesLogicasSimples.cpp
Escriba una expresión lógica que sea verdadera si una variable de tipo carácter llamada ```letra``` es una letra mayúscula y falso en otro caso.  
  
Escriba una expresión lógica que sea verdadera si una varaible de tipo entero llamada ```edad``` es mayor o igual que 18 y menor que 67.  
  
Escriba una expresión lógica que nos informe cuando un año es bisiesto. Los años bisiestos son aquellos que o bien son divisibles entre 4 pero no entre 100, o bien son divisibles entre 400.  
  
Escriba una expresión lógica que nos informe si el valor de una variable ```double``` llamada ```distancia``` es menor que la constante ```LIMITE``` (siendo esta una constante con un valor que fijéis).  
  
Use una variable lógica que registre si el valor de una varaible ```int``` es menor que otra, otra que informe si son iguales y otra que informe si es mayor. Sólo una deberá ser verdadera al mismo tiempo.
```cpp
#include <iostream>

using namespace std;

int main()
{
	// DECLARACIONES	

	const int ASCII_A = 'A', ASCII_Z = 'Z';
	const int EDAD_MIN = 18, EDAD_MAX = 67;
	const double LIMITE = 100.5;	

	char caracter;
	int edad;
	int anio;
	double distancia;
	int numero1, numero2;
	
	// ENTRADAS

	cout << "Un caracter: ";
	cin >> caracter;

	cout << "Una edad: ";
	cin >> edad;

	cout << "Un anio: ";
	cin >> anio;
	
	cout << "Una distancia: ";
	cin >> distancia;

	cout << "Dos numeros enteros: " << endl;
	cout << "\tNumero 1: ";
	cin >> numero1;
	cout << "\tNumero 2: ";
	cin >> numero2;

	// CÁLCULOS

	bool es_mayuscula = caracter >= ASCII_A && caracter <= ASCII_Z;

	bool edad_correcta = edad >= EDAD_MIN && edad < EDAD_MAX;

	bool anio_bisiesto = anio % 400 == 0 || (anio % 4 == 0 && anio % 100 != 0);

	bool distancia_menor_limite = distancia < LIMITE;

	bool numero1_mayor = numero1 > numero2;
	
	bool numeros_iguales = numero1 == numero2;

	bool numero1_menor = numero1 < numero2;

	// SALIDAS

	cout << endl;
	cout << endl;
	
	cout << caracter << " es mayuscula: 	" << boolalpha << es_mayuscula << endl;
	
	cout << "18 <= " << edad << " < 67: 		" << boolalpha << edad_correcta << endl;

	cout << anio << " es bisiesto: 	" << boolalpha << anio_bisiesto << endl;

	cout << distancia << " < " << LIMITE << ": 		" << boolalpha << distancia_menor_limite << endl;

	cout << endl;

	cout << numero1 << " > " << numero2 << ": " << boolalpha << numero1_mayor << endl;

	cout << numero1 << " = " << numero2 << ": " << boolalpha << numeros_iguales << endl;

	cout << numero1 << " < " << numero2 << ": " << boolalpha << numero1_menor << endl;

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/ExpresionesLogicasSimples.cpp)

## 5. ExpresionesLogicas.cpp

Nota: este ejercicio no debería programarse a este nivel ya que no se tienen los conocimientos necesarios para su resolución, sino unos que permiten hacerlo de forma rudimentaria. Se desaconseja su resolución aunque se invita a mirar la solución.

Suponga un caso de elección en el que se deciden entre tres opciones: ```A```, ```B``` y ```C```.
- El número de votantes totales (censo) está registrado en la constante ```VOTANTES```.
- El número total de de votos registrados es ```votos_emitidos```, donde el número total de de votos presenciales es ```votos_presenciales``` y el número total de de votos por correo es ```votos_correo```.
- Los votos registrados se dividen en válidos (```votos_validos```) y nulos (```votos_nulos```).
- Entre los votos válidos se distinguen entre los recibidos por correo (```votos_validos_correo```) y presencialmente (```votos_validos_presenciales```).
- Cada opción recibe un número de votos válidos que se registra en las variables ```votos_A``` ```votos_B``` ```votos_C```, respectivamente.  
    
Escriba expresiones lógicas para reflejar las situaciones que se describen a continuación. Para cada caso, el resultado debe guardarse en una variable lógica (escoja un nombre adecuado).  
  
a) El número de votos emitidos totales es mayor que el número de votantes.  
b) El número de votos válidos no es igual a la suma de los votos recibidos por las tres opciones.  
c) El número de votos registrados es igual a la suma de los votos válidos y nulos.  
d) Gana la opción ```A```.  
e) Gana la opción ```B```.  
f) Gana la opción ```C```.  
g) Empatan dos opciones.  
h) Hay un empate técnico entre las opciones ```A``` y ```B```. Definimos que ocurre un empate técnico cuando la diferencia entre los dos valores es menor que el 5 % de su suma.  
i) La opción ```A``` obtiene mayoría absoluta.  
j) La coalición ```A-C``` obtiene mayoría absoluta.  
k) Hay una coalición de dos opciones que obtiene mayoría absoluta.  
l) La opción ```B``` obtiene menos de 3 % de los votos válidos registrados.  
m) La participación es mayor que el 75 % del censo de votantes.  
n) Queremos saber si la opción ```A``` puede gobernar "sólo o en compañía de otros".  
ñ) El número de abstenciones es mayor que el número de votos válidos.  
o) El número de abstenciones es mayor que el número de votos válidos, pero las abstenciones no son mayores que los votos nulos.  
p) El número de votos por correo es mayor que el 20 % de los votos presenciales o el número de abstenciones.  
q) El número de votos nulos por correo es mayor que el número de votos nulos presenciales.  
r) El número de votos nulos por correo es mayor que el número de votos válidos por correo.  
```cpp
#include <iostream>
#include <cmath> // Para poder usar abs()

using namespace std;

int main()
{
	// DECLARACIONES	

	const int VOTANTES = 100000;

	int votos_emitidos, votos_presenciales, votos_correo;
	int votos_validos, votos_nulos;
	int votos_validos_correo, votos_validos_presenciales;
	int votos_A, votos_B, votos_C;

	// ENTRADAS ----------

	cout << "El numero total de votos: ";
	cin >> votos_emitidos;

	cout << "Votos presenciales: ";
	cin >> votos_presenciales;

	cout << "Votos por correo: ";
	cin >> votos_correo;
	
	cout << "Votos validos totales: ";
	cin >> votos_validos;

	cout << "Votos nulos totales: ";
	cin >> votos_nulos;
	
	cout << "Votos validos por correo: ";
	cin >> votos_validos_correo;

	cout << "Votos validos presenciales: ";
	cin >> votos_validos_presenciales;

	cout << "Votos para la opcion A: ";
	cin >> votos_A;

	cout << "Votos para B: ";
	cin >> votos_B;
	
	cout << "Votos para C: ";
	cin >> votos_C;

	// CÁLCULOS Y EXPRESIONES LÓGICAS ----------

	const double PORC_EMPATE_TECNICO = 0.05;
	const double PORC_POCOS_VOTOS_B = 0.03;
	const double PORC_ALTA_PARTICIPACION = 0.75;
	const double PORC_VOTOS_PRESENCIALES = 0.2;

	//Definimos algunas variables que nos van a hacer falta:
	int mitad_votos = votos_validos * 0.5; //útil para la mayoría absoluta

	int votos_A_B = votos_A + votos_B;
	int votos_A_C = votos_A + votos_C;
	int votos_B_C = votos_B + votos_C;
	
	int abstenciones = VOTANTES - votos_emitidos;

	int votos_nulos_correo = votos_correo - votos_validos_correo;
	int votos_nulos_presenciales = 
		votos_presenciales - votos_validos_presenciales;

	// Expresiones lógicas:

	// a) El número de votos emitidos totales es mayor que el número de 
	//	   votos.

	bool mas_votos_que_votantes = votos_emitidos > VOTANTES;

	// b) El número de votos válidos no es igual a la suma de los votos 
	//	  recibidos por las tres opciones.

	bool votos_validos_incorrectos = 
		 votos_validos != (votos_A_B + votos_C);

	// c) El número de votos registrados es igual a la suma de los votos 
	//	  válidos y nulos.

	bool numero_correcto_votos = 
		 votos_emitidos == (votos_validos + votos_nulos);

	// d) Gana la opción A.

	bool gana_A = votos_A > votos_B && votos_A > votos_C;

	// e) Gana la opción B.

	bool gana_B = votos_B > votos_A && votos_B > votos_C;

	// f) Gana la opción C.

	bool gana_C = votos_C > votos_B && votos_C > votos_A;

	// g) Empatan dos opciones.

	bool empatan_dos = votos_A == votos_B || votos_A == votos_C 
		 || votos_B == votos_C;

	// h) Hay un empate técnico entre las opciones A y B.

	bool empate_tecnico_A_B = 
		 abs(votos_A - votos_B) < votos_A_B * PORC_EMPATE_TECNICO;

	// i) La opción A obtiene mayoría absoluta.

	bool mayoria_abs_A = votos_A > mitad_votos;

	// j) La coalición A-C obtiene mayoría absoluta.

	bool mayoria_abs_A_C = votos_A_C > mitad_votos;

	// k) Hay una coalición de dos opciones que obtiene mayoría absoluta.

	bool mayoria_abs_A_B = votos_A_B > mitad_votos; //La usaremos proximamente.

	bool mayoria_abs_dos_opciones = mayoria_abs_A_B || mayoria_abs_A_C 
		 || votos_B_C > mitad_votos;

	// l) La opción B obtiene menos de 3 % de los votos válidos registrados.

	bool B_menos_de_porcentaje = votos_B < votos_validos * PORC_POCOS_VOTOS_B;

	// m) La participación es mayor que el 75 % del censo de votantes.

	bool participacion_alta = 
		 votos_emitidos > VOTANTES * PORC_ALTA_PARTICIPACION;

	// n) Queremos saber si la opción A puede gobernar "sólo o en compañía 
	//	  de otros".

	bool A_puede_gobernar = mayoria_abs_A || mayoria_abs_A_B 
		 || mayoria_abs_A_C;

	// ñ) El número de abstenciones es mayor que el número de votos válidos.

	bool alta_abstencion = abstenciones > votos_validos;

	// o) El número de abstenciones es mayor que el número de votos válidos, 
	//	  pero las abstenciones no son mayores que los votos nulos.

	bool muchos_votos_nulos = alta_abstencion && abstenciones <= votos_nulos;

	// p) El número de votos por correo es mayor que el 20 % de los votos 
	//	  presenciales o el número de abstenciones.

	bool muchos_votos_correo = 
		 votos_correo > votos_presenciales * PORC_VOTOS_PRESENCIALES 
		 || votos_correo > abstenciones;

	// q) El número de votos nulos por correo es mayor que el número de votos 
	//	  nulos presenciales.

	bool mas_nulos_correo = votos_nulos_correo > votos_nulos_presenciales;

	// r) El número de votos nulos por correo es mayor que el número de votos 
	//	  válidos por correo.

	bool mas_nulos_que_validos_correo = 
		 votos_nulos_correo > votos_validos_correo;

	// SALIDAS -----------------------------------

	cout << endl;
	
	// a)
	cout << "Mas votos que numero de votantes: " << boolalpha 
		 << mas_votos_que_votantes << endl;

	// b)
	cout << "Votos validos diferentes de las tres opciones: " << boolalpha 
		 << votos_validos_incorrectos << endl;

	// c)
	cout << "Votos registrados = votos validos + votos nulos: " << boolalpha 
		 << numero_correcto_votos << endl;

	// d)
	cout << "Gana A: " << boolalpha << gana_A << endl;

	// e)
	cout << "Gana B: " << boolalpha << gana_B << endl;

	// f)
	cout << "Gana C: " << boolalpha << gana_C << endl;

	// g)
	cout << "Empatan dos opciones: " << boolalpha << empatan_dos << endl;

	// h)
	cout << "Empate tecnico entre A y B: " << boolalpha << empate_tecnico_A_B 
		 << endl;

	// i)
	cout << "A tiene mayoria absoluta: " << boolalpha << mayoria_abs_A << endl;

	// j)
	cout << "Coalicion A-C tiene mayoria absoluta: " << boolalpha 
		 << mayoria_abs_A_C << endl;

	// k)
	cout << "Hay una coalicion de dos que tiene mayoria absoluta: " 
		 << boolalpha << mayoria_abs_dos_opciones << endl;

	// l)
	cout << "B tiene menos del " << (PORC_POCOS_VOTOS_B*100) 
		 << "% de los votos validos: " << boolalpha << B_menos_de_porcentaje 
		 << endl;

	// m)
	cout << "Participacion mayor que el " << (PORC_ALTA_PARTICIPACION*100) 
		 << "% de los votantes: " << boolalpha << participacion_alta << endl;

	// n)
	cout << "A puede gobernar solo o en compania de otros: " << boolalpha 
		 << A_puede_gobernar << endl;

	// ñ)
	cout << "Mas abstenciones que votos validos: " << boolalpha 
		 << alta_abstencion << endl;

	// o)
	cout << "Mas abstenciones que votos validos pero no que votos nulos: " 
		 << boolalpha << muchos_votos_nulos << endl;

	// p)
	cout << "Mas votos por correo que el " << (PORC_VOTOS_PRESENCIALES*100) 
		 << "% de los presenciales o que abstenciones: " << boolalpha 
		 << muchos_votos_correo << endl;

	// q)
	cout << "Mas votos nulos por correo que presenciales: " << boolalpha 
		 << mas_nulos_correo << endl;

	// r)
	cout << "Mas votos nulos que validos por correo: " << boolalpha 
		 << mas_nulos_que_validos_correo << endl;

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/ExpresionesLogicas.cpp)

## 6. AnalizaLineaIndice.cpp
En este ejercicio se va a procesar el contenido de una cadena de caracteres extrayendo sus componentes. El dato ```string``` que se va a procesar tiene un formato fijo y predeterminado.  
  
Las cadenas a procesar podrían ser líneas extraidas del índice de un documento. En este caso, en concreto, están formadas por:
- un número que indica la **sección** (ocupa las tres primeras casillas y tiene un máximo de tres dígitos),
- un número que indica la **subsección** (ocupa las tres siguientes casillas y tiene un máximo de tres dígitos),
- un número que indica la **subsubsección** (ocupa las tres siguientes casillas y tiene un máximo de tres dígitos),
- una serie de 40 caracteres que contiene el **título** del apartado, y
- un número que indica la página (ocupa las cuatro siguientes casillas y tiene un máximo de cuatro dígitos).  
  
Con estas indicaciones las cadenas tendrán una longitud **exacta** de 53 caracteres.  
  
Por ejemplo, en la siguiente cadena (los puntos indican los espacios de la cadena (se escriben en el ejemplo para ayudar a entenderlo) y las barras inicial y final (que no forman parte de la cadena) se escriben para que quede claro dónde empieza y termina la cadena):  
  
```| ..1..1..4El.proceso.de.Compilacion.................13 |```
  
El resultado que mostrará el programa será:  
  
Componentes:
- Seccion:        1
- Subseccion:     1
- Subsubseccion:  4
- Pagina:         13
- Titulo:         El proceso de Compilacion

- Linea procesada:
1.1.4. El proceso de Compilacion                    13  
  
Nota: En la cadena leida, las secciones se numeran con un cero en la subsección y subsubseción. Las subsecciones se numeran con un cero en la subsubseción. 
Ejemplos:  
  
```| ..1..0..0Introduccion.a.la.Programacion.............1 |```
```| ..1..1..0El.ordenador,.algoritmos.y.programas.......2 |```
```cpp
#include <iostream>

using namespace std;

int main()
{
	string input;	// Cadena original del usuario

	// ENTRADA

	cout << "Introduzca la cadena a formatear (53 caracteres): " << endl;
	getline(cin, input);

	// MANIPULACIÓN DE LA CADENA
	// Divide la cadena en cada componente usando el método substr()

	int seccion = stoi(input.substr(0, 3));

	int subseccion = stoi(input.substr(3, 3));

	int subsubseccion = stoi(input.substr(6, 3));

	string titulo = input.substr(9, 40);

	int pagina = stoi(input.substr(48, 4));

	// SALIDAS

	cout << endl;
	cout << endl;

	cout << "Componentes: " << endl;
	cout << "\tSeccion: 	" << seccion << endl;
	cout << "\tSubseccion: 	" << subseccion << endl;
	cout << "\tSubsubseccion: 	" << subsubseccion << endl;
	cout << "\tPagina:  	" << pagina << endl;
	cout << "\tTitulo: " << titulo << endl;

	cout << endl;

	cout << "Linea procesada: " << endl;
	cout << seccion << "." << subseccion << "." << subsubseccion << ". " 
		 << titulo << " " << pagina << endl;

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/AnalizaLineaIndice.cpp)

## 7. IntercambiaExtremos.cpp
Escriba un programa que lea un número entero (```original```) y construya otro a partir de él (```nuevo```), intercambiando la primera y la última cifra. Después indicará si la primera cifra de ```original``` es igual, mayor o menor que que la última del mismo valor (hágalo comparando ```original``` y ```nuevo```).
```cpp
#include <iostream>

using namespace std;

int main()
{
	int numero, nuevo;

	// ENTRADA

	cout << "Introduzca el numero: ";
	cin >> numero;

	// CÁLCULOS

	string str_numero = to_string(numero);

	char primera_cifra = str_numero.at(0);

	char ultima_cifra = str_numero.at(str_numero.length()-1);

	// Todas las cifras de numero salvo la primera y la última.
	string mitad_numero = str_numero.substr(1, str_numero.length()-2);

	nuevo = stoi(ultima_cifra + mitad_numero + primera_cifra);

	// Compara qué cifra es mayor:
	bool primera_es_mayor = numero > nuevo;
	bool cifras_iguales = numero == nuevo;
	bool primera_es_menor = numero < nuevo;

	// SALIDAS

	cout << endl;
	cout << "El numero nuevo: " << nuevo << endl;
	cout << endl;

	cout << primera_cifra << " > " << ultima_cifra << ": " << boolalpha 
		 << primera_es_mayor << endl;

	cout << primera_cifra << " = " << ultima_cifra << ": " << boolalpha 
		 << cifras_iguales << endl;

	cout << primera_cifra << " < " << ultima_cifra << ": " << boolalpha 
		 << primera_es_menor << endl;

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/IntercambiaExtremos.cpp)

# Ejercicios Opcionales
## 1. PVPAutomovil.cpp
El precio final de un automóvil para un comprador es la suma total del costo del vehículo, del porcentaje de ganancia de dicho vendedor y del I.V.A. Diseñar un algoritmo para obtener el precio final de un automóvil sabiendo que el porcentaje de ganancia de este vendedor es del 20 % y el I.V.A. aplicable es del 16 %.
```cpp
#include <iostream>

using namespace std;

int main()
{
    // Declaración de variables

	double precio;

	const double PORC_IVA = 0.16, PORC_GANANCIA = 0.2;

	// ENTRADA

	cout << "El precio del vehiculo: ";
	cin >> precio;

	// CÁLCULOS

	double ganancias = precio * PORC_GANANCIA;

	double iva_aplicado = precio * PORC_IVA;

	double precio_final = precio + ganancias + iva_aplicado;

	// SALIDA

	cout << endl;
	cout << "El precio final del vehiculo: " << precio_final << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/PVPAutomovil.cpp)

## 2. Harvesine.cpp
El sistema de posicionamiento global, más conocido por sus siglas en inglés, **GPS** (Global Positioning System), es un sistema que permite determinar en toda la Tierra la posición de un objeto.  
  
Un dispositivo GPS es capaz de captar y registrar la posición en el espacio en base a tres coordenadas: latitud y longitud (grados) y altura (metros). Los valores de latitud y longitud deben verificar $-90 ≤ lat ≤ 90$ y $-180 < lon ≤ 180$.  
  
Construir un programa que lea la latitud y longitud (posición en el plano) de dos puntos y calcule la distancia sobre plano entre los dos puntos (distancia que no considera la altura de los puntos).  
  
Use la llamada fórmula del Haversine:
1. $$a = \sin² \left(\dfrac{1}{2}(lat_2-lat_1)\right)+\cos lat_1 \cdot \cos lat_2 \cdot \sin²\left(\dfrac{1}{2}(lon_2-lon_1)\right)$$
2. $$c = 2 \arcsin \left(\min{(1, \sqrt{a})}\right)$$
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
#include <algorithm>	// Para la función min()
                        
using namespace std;

int main()
{
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
	// Pasamos los datos de longitud y latitud a radianes para operar con ellos:
	
	double rad_latitud1 = latitud1 * GRADOS_A_RADIANES;
	double rad_latitud2 = latitud2 * GRADOS_A_RADIANES;
	double rad_longitud1 = longitud1 * GRADOS_A_RADIANES;
	double rad_longitud2 = longitud2 * GRADOS_A_RADIANES;

	// Calculamos los datos a y c de la fórmula del Haversine:

	double a = pow(sin(0.5*(rad_latitud2 - rad_latitud1)), 2) 
		+ cos(rad_latitud1) * cos(rad_latitud2) 
		* pow(sin(0.5*(rad_longitud2 - rad_longitud1)), 2);

	double c = 2 * asin(min(1.0, sqrt(a)));

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
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/Haversine.cpp)

## 3. AreaTriangulo.cpp
El área $A$ de un triángulo se puede calcular a partir del valor de dos de sus lados, $a$ y $b$, y del ángulo $\thita$ que éstos forman entre sí con la fórmula:  
$$A = \dfrac{1}{2}ab\sin\theta$$  
  
Construya un programa que pida al usuario el valor de los dos lados (en centímetros), el ángulo que éstos forman (en grados), y muestre el valor del área (tenga en cuenta que el argumento de la función si va en radianes).
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double lado1, lado2, angulo;

	const double PI = 6*asin(0.5);
	const double GRADOS_A_RADIANES = PI / 180;

	// ENTRADAS

	cout << "La medida de un lado (cm): ";
	cin >> lado1;

	cout << "La medida de otro lado (cm): ";
	cin >> lado2;

	cout << "El angulo que forman (en grados): ";
	cin >> angulo;

	// CÁLCULOS
	// Pasamos el ángulo a radianes:
	
	double rad_angulo = angulo * GRADOS_A_RADIANES;

	// Aplicamos la fórmula:

	double area = 0.5 * lado1 * lado2 * sin(rad_angulo);

	// SALIDA

	cout << endl;
	cout << "El area del triangulo es de " << area << " cm cuadrados." << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/AreaTriangulo.cpp)

## 4. MinNumBits.cpp
Los compiladores utilizan siempre el mismo número de bits para representar un tipo de dato entero (este número puede variar de un compilador a otro). Por ejemplo, 32 bits para un ```int```. Pero, realmente, no se necesitan 32 bits para representar el 6, por ejemplo, ya que bastarían 3 bits:
$$6 = 1\cdot 2² + 1\cdot 2¹ + 0\cdot 2^0 = 110$$
Se pide crear un programa que lea un entero positivo ```n```, y calcule el mínimo número de dígitos que se necesitan para su representación. Para simplificar los cómputos, suponed que sólo queremos representar valores enteros positivos (incluido el cero).  Consejo: se necesitará usar el logaritmo en base 2 y obtener la parte entera de un real (se obtiene tras el truncamiento que se produce al asignar un real a un entero)
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int numero;

	// ENTRADA

	cout << "Introduzca el numero: ";
	cin >> numero;

	// CALCULOS

	int bits = log2(numero) + 1;

	// SALIDA

	cout << endl;
	cout << "Seran necesarios " << bits << " bits en binario." << endl;
	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2004/MinNumBits.cpp)
