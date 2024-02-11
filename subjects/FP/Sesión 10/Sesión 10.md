# Fundamentos de Programación. Sesión X de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión X de prácticas.

En esta sesión de prácticas, se introducen los **arrays anidados**, también llamados **matrices** en el caso de un array anidado dentro de otro, por lo que los ejercicios estarán orientados a su uso.

## 1. ArrayEmpleados.cpp
Una empresa tiene los datos de sus empleados guardados en un fichero de texto. Por simplicidad, cada línea guarda los datos de un único empleado y no hay líneas vacías (en consecuencia, habrá tantas líneas como empleados). Los datos registrados son los siguientes:
- Apellidos (```string```).
- Nombre (```string```).
- Fecha de nacimiento (```string```, en formato ```dd/mm/aaaa```).
- Sueldo bruto (```double```).  
  
Se encuentran en dicho orden y separador por ```|```.  
Por ejemplo:  
```Martinez Lopez|Juan Carlos|10/12/2000|2345.55|```  
```Abad y Paz de Molina|Maria del Carmen|01/01/1999|3002.88|```  
```Pi Garcia|Jose|05/05/1987|1987.44|```  
```Martin Martinez|Patricia|04/06/1998|1234.56|```  
  
Escriba un programa para mostrar un lista ordenado (ascendente) de los empleados.  Guarde los datos en un único array.  
  
Escriba, el código para realizar la ordenación por _sueldo bruto_:  
```Martin Martinez         Patricia            04 Jun 1998     1234.56```  
```Pi Garcia               Jose                05 May 1987     1987.44```  
```Martinez Lopez          Juan Carlos         10 Dic 2000     2345.55```  
```Abad y Paz de Molina    Maria del Carmen    01 Ene 1999     3002.88```  
  
Si la ordenación fuera por _apellidos_:  
```Abad y Paz de Molina    Maria del Carmen    01 Ene 1999     3002.88```  
```Martin Martinez         Patricia            04 Jun 1998     1234.56```  
```Martinez Lopez          Juan Carlos         10 Dic 2000     2345.55```  
```Pi Garcia               Jose                05 May 1987     1987.44```  
  
Si fuera por _fecha de nacimiento_:  
```Pi Garcia               Jose                05 May 1987     1987.44```  
```Martin Martinez         Patricia            04 Jun 1998     1234.56```  
```Abad y Paz de Molina    Maria del Carmen    01 Ene 1999     3002.88```  
```Martinez Lopez          Juan Carlos         10 Dic 2000     2345.55```  
  
La ordenación deberá poder realizarse por cualquiera de los campos indicados (salario, apellidos o fecha de nacimiento) aunque la versión que se compilará, tal cual se entregue, será la que ordena por el salario.  
  
El programa, no obstante, debe poder modificarse para obtener la ordenación por los otros criterios con el mínimo número de cambios posibles y evitando la repetición de código.  
  
Realice las pruebas necesarias para asegurar que se realizan correctamente todas las ordenaciones. Cada vez que cambie el criterio de ordenación deberá recompilar el programa, necesariamente6 . Asegúrese de que los cambios realizados son mínimos y razonables.  
  
Nota: recomendamos la ejecución del programa con redirección de datos de entrada. Le dejamos aquí el [fichero](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/Empleados.txt) listo con la entrada.
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

// Constantes globales y tipo enumerado

const char SEPARADOR_FECHAS = '/', SEPARADOR_DATOS = '|';

enum class TipoOrdenacion {salario, apellidos, fecha};

/****************************************************************************
	Devuelve la posición en la que se encuentra el primer caracter 
	especificado en la cadena especificada

  Parámetros: cadena, (donde se busca el caracter)
			  caracter (el caracter a buscar)

  Devuelve: la posición en la que se encuentra caracter dentro de cadena
  PRE: Dentro de cadena hay al menos un caracter igual a caracter

****************************************************************************/

int PosicionCaracter(string cadena, char caracter){

	int i = 0;

	while(i < cadena.length() && cadena.at(i) != caracter)
		i++;
	
	return i;
}

/****************************************************************************
	Elimina los espacios iniciales y finales de una cadena

  Parámetros: cadena
  Devuelve: La cadena tras eliminarle los espacios iniciales y finales

****************************************************************************/

string EliminaEspacios(string cadena){

	const char ESPACIO = ' ';

	int pos = 0;

	// Busca el primer caracter distinto de ESPACIO

	while(pos < cadena.length() && cadena.at(pos) == ESPACIO)
		pos++;
	
	// Se queda con la subcadena que hay a partir de ese caracter

	string cadena_mod = cadena.substr(pos);

	// Busca el primer caracter distinto de ESPACIO empezando por detrás

	pos = cadena.length() - 1;

	while(pos > 0 && cadena.at(pos) == ESPACIO)
		pos--;

	// Se que da con la subcadena que hay hasta ese caracter

	cadena_mod = cadena_mod.substr(0, pos);

	return cadena_mod;
}

/****************************************************************************
	Determina si las cadenas están ordenadas alfabéticamete, siendo la primra
	menor que la segunda en términos de orden.

  Parámetros: cadena1, cadena2
  Devuelve: true si cadena1 < cadena2 si ordenamos las cadenas alfabéticamente,
			false si no
  PRE: cadena1 y cadena2 no pueden estar vacías

****************************************************************************/

bool OrdenadasAlfabeticamente(string cadena1, string cadena2){

	bool ordenadas;

	int pos = 0;

	char car1 = toupper(cadena1.at(pos));
	char car2 = toupper(cadena2.at(pos));

	// Mientas que las cadenas sean iguales, se busca el siguiente carcter

	while(car1 == car2 && pos < cadena1.length() && pos < cadena2.length()){
	
		car1 = toupper(cadena1.at(pos));
		car2 = toupper(cadena2.at(pos));

		pos++;
	}

	// Si se ha llegado al último caracter si éxito

	if(pos == cadena1.length() || pos == cadena2.length()){

		// Si la primera cadena tiene menos caracteres o los mismos

		if(cadena1.length() <= cadena2.length())
			ordenadas = true;

		else
			ordenadas = false;

	}

	// Si la diferencia de su código ascii es negativo, car2 tendrá un código
	// mayor que car1, por lo que estará más cerca de 'Z' que car1

	else
		ordenadas = car1 - car2 <= 0;

	return ordenadas;
}

/****************************************************************************
	Pasa todos los caracteres de una cadena a mayúscula

  Parámetro: cadena
  Devuelve: cadena con todos sus caracteres en mayúscula

****************************************************************************/

string Mayusculas(string cadena){
	string cadena_mod;

	for(int i = 0; i < cadena.length(); i++){
		cadena_mod += toupper(cadena.at(i));
	}

	return cadena_mod;
}

/****************************************************************************
	Dado un string con las tres primeras letras de un mes, determina el número
	del mes

  Parámetros: mes
  Devuelve: el número del mes
  PRE: mes debe ser uno de los contemplados en el array MESES

****************************************************************************/

int NumeroMes(string mes){
	const int NUM_MESES = 12;

	const string MESES[NUM_MESES] = {"ENE", "FEB", "MAR", "ABR", "MAY", "JUN", 
									"JUL", "AGO", "SEP", "OCT", "NOV", "DIC"};

	mes = Mayusculas(mes);

	int i = 1;

	// Mientras que mes no esté en MESES, aumentamos i

	while(i < NUM_MESES && MESES[i-1] != mes){
		i++;
	}

	return i;
}

/****************************************************************************
	Determina si las dos fechas están ordenadas cronológicamente

  Parámetros: fecha1, fecha2
  Devuelve: true si fecha1 sucede antes que fecha2
  PRE: fecha1 y fecha2 deben tener el formato:

	dd/mmm/aaaa

	Con _ = SEPARADOR_FECHAS
	Y mmm las tres primeras letras del mes

****************************************************************************/

bool OrdenadasCronologicamente(string fecha1, string fecha2){

	// Obtenemos el día

	int pos_dia = PosicionCaracter(fecha1, SEPARADOR_FECHAS);

	int dia1 = stoi(fecha1.substr(0, pos_dia));
	int dia2 = stoi(fecha2.substr());

	// Acortamos fecha1 y fecha2

	fecha1 = fecha1.substr(pos_dia + 1);
	fecha2 = fecha2.substr(pos_dia + 1);

	// Obtenemos el mes

	int pos_mes = PosicionCaracter(fecha1, SEPARADOR_FECHAS);

	int mes1 = NumeroMes(fecha1.substr(0, pos_mes));
	int mes2 = NumeroMes(fecha2.substr(0, pos_mes));

	// Acortamos fecha 1 y fecha2

	fecha1 = fecha1.substr(pos_mes + 1);
	fecha2 = fecha2.substr(pos_mes + 1);

	// Obtenemos los años

	int anio1 = stoi(fecha1);
	int anio2 = stoi(fecha2);

	// Comprobamos si fecha1 sucede antes que fecha2

	bool ordenados;

	if(anio1 < anio2){
		ordenados = true;
	
	}else{

		if(anio1 > anio2)		// fecha2 sucede antes
			ordenados = false;

		else{	// Son iguales => vemos los meses
		
			if(mes1 < mes2)
				ordenados = true;
	
			else{	

				if(mes1 > mes2)		// fecha2 sucede antes
					ordenados = false;

				else{ // Son iguales => vemos los días

					// Si los días son iguales, dia1 sucede antes
					ordenados = dia1 <= dia2;

				}

			}

		}
	}

	return ordenados;
}

/****************************************************************************
	Determina si dos datos están ordenados en función del criterio especificado

  Prámetros: dato1, dato2, criterio
  Devuelve: true si dato1 < dato2, false si no

****************************************************************************/

bool EstanOrdenados(string dato1, string dato2, TipoOrdenacion criterio){
	
	bool ordenados;
	
	// Según el criterio, compara dato1 y dato2 de diferentes formas

	switch(criterio){
		case TipoOrdenacion::apellidos:
	
			ordenados = OrdenadasAlfabeticamente(dato1, dato2);
			break;

		case TipoOrdenacion::fecha:
	
			ordenados = OrdenadasCronologicamente(dato1, dato2);
			break;

		case TipoOrdenacion::salario:
		
			ordenados = stod(dato1) < stod(dato2);
			break;
	}

	return ordenados;
}

/****************************************************************************/

int main(){

	// Selecciona por qué criterio se ordenan los empleados *****************	

	TipoOrdenacion criterio;

	// Ordena a los empleados según el sueldo bruto ---------------------

	criterio = TipoOrdenacion::salario;

	// Ordena a los empleados por apellidos -----------------------------

	// criterio = TipoOrdenacion::apellidos;

	// Ordena los empleados por su fecha de nacimiento ------------------

	// criterio = TipoOrdenacion::fecha;

	// ***********************************************************************

	// Ctes para el array info_empleados

	const int MAX_FILAS = 100, COLUMNAS = 4;

	const int COLUMNA_APELLIDOS = 0, COLUMNA_NOMBRES = 1, COLUMNA_FECHAS = 2
			, COLUMNA_SALARIOS = 3;

	string info_empleados[MAX_FILAS][COLUMNAS];

	int filas_validas = 0;

	// ENTRADAS ***************************************************************

	string entrada;

	// Solicita los datos del primer empleado

	getline(cin, entrada);

	// Elimina los espacios iniciales y finales de la entrada

	entrada = EliminaEspacios(entrada);

	// Mientras que haya empleados por leer y huecos libres en info_empleados

	while(entrada.length() != 0 && filas_validas < MAX_FILAS - 1){

		// Se repite COLUMNAS - 1 veces

		for(int i = 0; i < COLUMNAS - 1; i++){

			// Obtiene la posición del primer SEPARADOR_DATOS

			int posicion_corte = PosicionCaracter(entrada, SEPARADOR_DATOS);

			// Almacena el valor hasta el separador

			info_empleados[filas_validas][i] = 
											entrada.substr(0, posicion_corte);

			// Acorta la entrada

			entrada = entrada.substr(posicion_corte + 1);

		}

		// Almacena el último dato

		info_empleados[filas_validas][COLUMNA_SALARIOS] = 
									entrada.substr(0, entrada.length());

		filas_validas++;

		// Solicita los datos del siguiente empleado

		getline(cin, entrada);

		entrada = EliminaEspacios(entrada);
	}

	// info_empleados está apunto de llenarse, se guarda el último empleado

	if(entrada.length() != 0){

		// Se repite COLUMNAS - 1 veces

		for(int i = 0; i < COLUMNAS - 1; i++){

			// Obtiene la posición del primer SEPARADOR_DATOS

			int posicion_corte = PosicionCaracter(entrada, SEPARADOR_DATOS);

			// Almacena el valor hasta el separador

			info_empleados[filas_validas][i] = 
											entrada.substr(0, posicion_corte);

			// Acorta la entrada

			entrada = entrada.substr(posicion_corte + 1);

		}

		// Almacena el último dato

		info_empleados[filas_validas][COLUMNA_SALARIOS] = 
									entrada.substr(0, entrada.length());

		filas_validas++;

		// Imprime que no se admiten más emleados por estar info_emleados lleno

		cout << endl;
		cout << "Maximo de empleados alcanzado." << endl;
		cout << endl;
	}

	// CÁLCULOS **********************************************************

	// Ordena según el ajuste especificado usando selection sort ----------

	int posiciones_ordenadas = 0;

	int columna;

	// Selecciona la columna en función del criterio

	switch(criterio){
		case TipoOrdenacion::apellidos: 
			columna = COLUMNA_APELLIDOS;
			break;

		case TipoOrdenacion::fecha: 
			columna = COLUMNA_FECHAS;
			break;

		case TipoOrdenacion::salario:
		default: 
			columna = COLUMNA_SALARIOS;
			break;
	}

	// Se ejecuta tantas veces como empleados haya menos uno

	for(int vuelta = 0; vuelta < filas_validas - 1; vuelta++){

		// Busca el mínimo del array -------------------------

		// Inicializa minimo en el dato del primer empleado

		int posicion_minimo = posiciones_ordenadas;
		string minimo = info_empleados[posicion_minimo][columna];

		// Recorre todas las posiciones en búsqueda del mínimo

		for(int i = posicion_minimo + 1; i < filas_validas; i++){

			string dato = info_empleados[i][columna];

			// Comprueba si dato < minimo en función de criterio

			if(EstanOrdenados(dato, minimo, criterio)){

				minimo = dato;
				posicion_minimo = i;

			}

		}

		// Si el mínimo no estaba en la primera posición del array ordenado

		if(posiciones_ordenadas != posicion_minimo){

		   // Intercambia el elemento de posicion_minimo y posiciones_ordenadas

			for(int i = 0; i < COLUMNAS; i++){

				string auxiliar = info_empleados[posiciones_ordenadas][i];
				info_empleados[posiciones_ordenadas][i] = 
										info_empleados[posicion_minimo][i];
				info_empleados[posicion_minimo][i] = auxiliar;

			}

		}

		// Tenemos una nueva posición ordenada

		posiciones_ordenadas++;	

	}

	// SALIDAS

	cout << endl;

	// Imprime el criterio por el que se han ordenado

	switch(criterio){
		case TipoOrdenacion::apellidos:
			cout << "Ordenados por apellidos:" << endl;
			break;

		case TipoOrdenacion::fecha:
			cout << "Ordenados por fecha de nacimiento:" << endl;
			break;

		case TipoOrdenacion::salario:
		default:
			cout << "Ordenados por sueldo: " << endl;
			break;
	}

	cout << endl;

	// Imprime la cabecera de una tabla

	cout << setw(20) << "APELLIDOS		";
	cout << setw(20) << "NOMBRE		";
	cout << setw(20) << "NACIMIENTO		";
	cout << setw(20) << "SUELDO		" << endl;

	// Imprime los datos de todos los empleados, ordenados por el criterio
	// seleccionado

	for(int i = 0; i < filas_validas; i++){

		// Imprime el apellido del empleado, además de una coma

		cout << setw(20) << info_empleados[i][COLUMNA_APELLIDOS] << ",";

		for(int j = 1; j < COLUMNAS; j++){

			cout << "		" << setw(20) << info_empleados[i][j];

		}

		cout << endl;

	}

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/ArrayEmpleados.cpp)

## 2. InflacionMatriz.cpp
En la siguiente tabla mostramos el IPC de varios paises entre 2001 y 2021:  
  
| Año  | España | Inglaterra | USA  | Zona Euro |
|------|--------|------------|------|-----------|
| 2021 | 6.500% | 5.400%     | 7.0% | 5.00%     |
| 2020 | -0.50% | 0.600%     | 1.4% | -0.3%     |
| 2019 | 0.800% | 1.300%     | 2.3% | 1.30%     |
| 2018 | 1.200% | 2.100%     | 1.9% | 1.50%     |
| 2017 | 1.100% | 2.900%     | 2.1% | 1.30%     |
| 2016 | 1.600% | 1.600%     | 2.1% | 1.10%     |
| 2015 | 0.000% | 0.230%     | 0.7% | 0.20%     |
| 2014 | -1.00% | 0.550%     | 0.8% | -0.2%     |
| 2013 | 0.300% | 2.000%     | 1.5% | 0.80%     |
| 2012 | 2.900% | 2.710%     | 1.7% | 2.20%     |
| 2011 | 2.400% | 4.200%     | 3.0% | 2.80%     |
| 2010 | 3.000% | 3.730%     | 1.5% | 2.20%     |
| 2009 | 0.800% | 2.830%     | 2.7% | 0.90%     |
| 2008 | 1.400% | 3.110%     | 0.1% | 1.60%     |
| 2007 | 4.200% | 2.120%     | 4.1% | 3.10%     |
| 2006 | 2.700% | 2.970%     | 2.5% | 1.90%     |
| 2005 | 3.700% | 1.920%     | 3.4% | 2.20%     |
| 2004 | 3.200% | 1.640%     | 3.3% | 2.40%     |
| 2003 | 2.600% | 1.250%     | 1.9% | 2.00%     |
| 2002 | 4.000% | 1.690%     | 2.4% | 2.30%     |
| 2001 | 2.700% | 1.070%     | 1.6% | 2.10%     |
  
Escriba un programa que solicite un número ```n``` de años ($2\leq n\leq 5$) y muestre qué pais (España, Inglaterra, USA ó Zona Euro) es el que:  
1. Tiene el mayor IPC medio en ```n``` años.
2. TIene el menor IPC medio en ```n``` años.  
   
Muestre además, sus valores y los años entre los que se han calculado los resultados.  
  
Repita hasta introducir un valor de ```n``` negativo.
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

/****************************************************************************/
// Constantes globales

const int ANIO_INICIAL = 2001, ANIO_FINAL = 2021;
const int NUM_ANIOS = ANIO_FINAL - ANIO_INICIAL + 1;

const int PAISES = 4;

const string NOMBRES_PAISES[PAISES] = {"Espania", "Reino Unido", 
										"Estados Unidos", "Zona euro"};

enum class Pais {Espana, UK, USA, Euro};

// IPC de España, Inglaterra, USA y la Zona Euro

const double IPC[PAISES][NUM_ANIOS] = 
				{ {2.7, 4, 2.6, 3.2, 3.7, 2.7, 4.2, 1.4, 0.8, 3, 2.4, 2.9, 0.3, 
				-1, 0, 1.6, 1.1, 1.2, 0.8, -0.5, 6.5}, 
				{1.07, 1.69, 1.25, 1.64, 1.92, 2.97, 2.12, 3.11, 2.83, 3.73, 
				4.2, 2.71, 2, 0.55, 0.23, 1.6, 2.9, 2.1, 1.3, 0.6, 5.4}, 
				{1.6, 2.4, 1.9, 3.3, 3.4, 2.5, 4.1, 0.1, 2.7, 1.5, 3, 1.7, 1.5, 
				0.8, 0.7, 2.1, 2.1, 1.9, 2.3, 1.4, 7}, 
				{2.1, 2.3, 2, 2.4, 2.2, 1.9, 3.1, 1.6, 0.9, 2.2, 2.8, 2.2, 0.8, 
				-0.2, 0.2, 1.1, 1.3, 1.5, 1.3, -0.3, 5}};

/****************************************************************************/
// Definición de structs

// Almacena un valor de IPC medio

struct IPCMedio{
	double ipc;		// Valor del IPC medio
	Pais pais;		// Indica de que país es el IPC
	int anio_inicial;		// Indica el año inicial de cálculo
	int anio_final;			// Indica el año final
};

/****************************************************************************
	Imprime en consola el IPC medio, indicando el país, el valor del ipc
	y los años entre los que se ha calculado con el siguiente formato:

		pais
		ipc%
		Entre anio_inicial y anio_final

  Parámetros: ipc_medio

****************************************************************************/

void cout_IPCMedio(IPCMedio ipc_medio){

	cout << "\t" << NOMBRES_PAISES[(int)ipc_medio.pais] << endl;

	cout << "\t" << ipc_medio.ipc << "%" << endl;

	cout << "\tEntre " << ipc_medio.anio_inicial << " y " 
		 << ipc_medio.anio_final << endl;
}

/****************************************************************************
	Devuelve el IPC del año especificado y del país especificado

  Parámetros: anio, pais
  Devuelve: El IPC del anio especificado

  PRE: ANIO_INICIAL <= anio <= ANIO_FINAL

	*Necesita a la cte global IPC[][]

****************************************************************************/

double Obtener_IPC(int anio, Pais pais){
	
	return IPC[(int) pais][anio - ANIO_INICIAL];
}

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

	// Se repite mientas que no sea entero

	do{

		cout << mensaje;
		cin >> numero;

	}while(!EsEntero(numero));

	return stoi(numero);
}

/****************************************************************************/

int main(){

	const int MIN_N_ANIOS = 2, MAX_N_ANIOS = 5;
	const int TERMINADOR_MAXIMO = -1;

	const string MSG_INTERVALO_N = "(entre " + to_string(MIN_N_ANIOS) 
									+ " y " + to_string(MAX_N_ANIOS) + ")";

	// Se formatea la consola para mostrar de forma correcta los porcentajes
	
	cout.setf(ios::fixed);

	cout << setw(4) << setprecision(2);

	// Se comienza con la entrada de datos

	cout << "Introduzca un numero de anios negativo para finalizar." << endl;

	cout << endl;

	// Solicita un número de años 
	// MIN_N_ANIOS <= n <= MAX_N_ANIOS ó n <= TERMINADOR_MAXIMO

	int n;

	cout << "--------------------------------" << endl;

	do{
		
		n = LeerEntero("Numero de anios " + MSG_INTERVALO_N + ": ");

	}while(n > TERMINADOR_MAXIMO && (n < MIN_N_ANIOS || n > MAX_N_ANIOS));

	// Mientras que n no sea negativo

	while(n > TERMINADOR_MAXIMO){

		// Calcula el IPC medio mayor y menor en n años --------------------

		// Los años entre los que se van calculando los ipc medios

		int primer_anio = ANIO_INICIAL;

		int ultimo_anio = primer_anio + n - 1;

		// Almacena cuales y donde son los maximos y minimo ipcs

		// Inicializamos su valor en unos valores imposibles para que se 
		// se alteren en el bucle

		IPCMedio mayor_ipc = {-100, Pais::Espana, 2001, 2021};

		IPCMedio menor_ipc = {100, Pais::Espana, 2001, 2021};

		IPCMedio actual;	// ALmacena el IPC que se está calculando ahora

		// Mientras que se pueddan seguir considerando años

		while(ultimo_anio <= ANIO_FINAL){

			// Se guardan los años en los que se calcula el IPC medio

			actual.anio_inicial = primer_anio;

			actual.anio_final = ultimo_anio;

			// Lo repite por cada país

			for(int pais = 0; pais < PAISES; pais++){

				// Guarda la información del ipc medio que se calcula

				actual.pais = (Pais) pais;

				// Se calcula el IPC medio entre primer_anio y ultimo_anio
				// del país pais

				double sumatoria = 0;

				for(int anio = primer_anio; anio <= ultimo_anio; anio++){

					sumatoria += Obtener_IPC(anio, actual.pais);

				}

				actual.ipc = sumatoria / n;

				// Si es mayor que el mayor o menor que el menor se guarda

				if(actual.ipc > mayor_ipc.ipc)
					mayor_ipc = actual;

				if(actual.ipc < menor_ipc.ipc)
					menor_ipc = actual;

			}

			// Busca en el siguiente intervalo de años

			primer_anio++;
			ultimo_anio = primer_anio + n - 1;			
		}

		// Imprime cual ha sido el resultado ------------------------------

		cout << endl;

		// Imprime cual es el mayor IPC medio en n años

		cout << "Mayor IPC medio en " << n << " anios: " << endl;

		cout_IPCMedio(mayor_ipc);

		cout << endl;

		// Imprime cual es el menor IPC medio en n años

		cout << "Menor IPC medio en " << n << " anios: " << endl;

		cout_IPCMedio(menor_ipc);

		cout << endl;

		// Solicita el siguiente número de anios --------------------------
		// MIN_N_ANIOS <= n <= MAX_N_ANIOS ó n <= TERMINADOR_MAXIMO
	
		cout << "--------------------------------" << endl;

		do{
		
		n = LeerEntero("Numero de anios " + MSG_INTERVALO_N + ": ");

		}while(n > TERMINADOR_MAXIMO && (n < MIN_N_ANIOS || n > MAX_N_ANIOS));

	}

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/InflacionMatriz.cpp)

## 3. RobotTablero.cpp
Este ejercicio desarrolla un problema mayor al visto en el ejercicio ```10. RobotLinea.cpp``` de la [Sesión IX](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/Sesi%C3%B3n%2009.md) de prácticas:  
  
Inicialmente, el robot se ubica en la posición ```pos```, siendo ```pos``` una pareja de enteros positivos ```(f, c)``` donde: $1\leq f\leq 10$ y $1\leq c\leq 10$.  
Luego, el robot ejecuta una serie de órdenes mediante un array ```ord``` de tipo ```char``` con longitud ```lon```. Cada orden es una letra ```I```, ```D```, ```A```, o ```B```. Indicando si el robot se mueve hacia la izquierda, derecha, arriba o abajo, respectivamente.  
Las posiciones **válidas** del robot cumplen que para cada posición ```pos``` sus coordenadas son correctas (esto es, $1\leq f\leq 10$ y $1\leq c\leq 10$).  
  
Se pide implementar un programa que lea la posición inical ```pos``` y la secuencia de órdenes a ejecutar, ```ord```.  
Después de la lectura:
- Si la serie de órdenes es correcta, muestre cuántas veces se visitó cada posición (Use una representación bidimensional).
- Si la serie de órdenes NO es  correcta, el programa terminará indicando cuántas órdenes se pudieron ejecutar.  
  
Ejemplo:  
```Posicion inicial = (5, 5)```  
```Ordenes = IIAAAADDBDDDBB```  
```Num. ordenes = 14```  
```------------------------```  
```La serie de ordenes es: correcta```  
```Se ejecutaron 14 ordenes```  
  
```   : 1 2 3 4 5 6 7 8 9 10    ```  
```   -----------------------   ```  
```10 : . . . . . . . . . . :  10```  
``` 9 : . . 1 1 1 . . . . . :  9```  
``` 8 : . . 1 . 1 1 1 1 . . :  8```  
``` 7 : . . 1 . . . . 1 . . :  7```  
``` 6 : . . 1 . . . . 1 . . :  6```  
``` 5 : . . 1 1 1 . . . . . :  5```  
``` 4 : . . . . . . . . . . :  4```  
``` 3 : . . . . . . . . . . :  3```  
``` 2 : . . . . . . . . . . :  2```  
``` 1 : . . . . . . . . . . :  1```  
```   -----------------------   ```  
```   : 1 2 3 4 5 6 7 8 9 10```  
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

// Definición de struct

struct Punto{
	int fila;
	int columna;
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

	// Se repite mientras que no sea entero

	do{

		cout << mensaje;
		cin >> numero;

	}while(!EsEntero(numero));

	return stoi(numero);
}

/****************************************************************************
	Imprime un mensaje en consola y lee el número entero que introduce el 
	usuario. Repite la entrada mientras que el valor introducido no sea
	un número entero o no esté en el intervalo [min, max]

  Parámetros: titulo, el mensaje que se muestra al usuario
			  min, el mínimo número válido
			  max, el máximo número válido
  Devuelve: el número entero que introduce el usuario

****************************************************************************/

int LeerEnteroEnRango(string mensaje, int min, int max){
	int numero;

	// Se repite mientras que no esté en el intervalo [min, max]

	do{

		numero = LeerEntero(mensaje);

	}while(numero < min || numero > max);

	return numero;
}

/****************************************************************************/

int main(){
	
	// Coordenadas mínimas y máximas de las filas y columnas

	const int MIN_FILAS = 1, MIN_COLUMNAS = 1;
	const int MAX_FILAS = 10, MAX_COLUMNAS = 10;

	const int NUM_FILAS = MAX_FILAS - MIN_FILAS + 1;
	const int NUM_COLUMNAS = MAX_COLUMNAS - MIN_COLUMNAS + 1;

	const string MSG_INTERVALO_FILAS = "(entre " + to_string(MIN_FILAS) + " y " 
												+ to_string(MAX_FILAS) + ")";

	const string MSG_INTERVALO_COLUMNAS = "(entre " + to_string(MIN_COLUMNAS) 
									+ " y " + to_string(MAX_COLUMNAS) + ")";

	// Repertorio válido de instrucciones

	const char INS_IZQDA = 'I', INS_DCHA = 'D';
	const char INS_ARRIBA = 'A', INS_ABAJO = 'B';

	int mapa[NUM_FILAS][NUM_COLUMNAS];

	// ENTRADAS ************************************************************

	// Se solicita la posición inicial del robot

	cout << "Introduzca la posición inicial del robot: " << endl;

	int fila, columna;

	fila = LeerEnteroEnRango("\tFila " + MSG_INTERVALO_FILAS + ": ", 
											MIN_FILAS, MAX_COLUMNAS);

	columna = LeerEnteroEnRango("\tColumna " + MSG_INTERVALO_COLUMNAS + ": ", 
											MIN_COLUMNAS, MAX_COLUMNAS);

	// Se almacena la posición en pos

	Punto pos = {fila, columna};

	// Se solicita el repertorio de instrucciones a ejecutar

	cout << endl;

	bool secuencia_invalida;

	string cad_ordenes;

	do{

		cout << "Secuencia de ordenes: " << endl;
		cin >> cad_ordenes;

		int i = 0;

		// Se presupone que la secuencia sea valida

		secuencia_invalida = false;

		// Mientras que no sea invalida, recorre cad_ordenes

		while(i < cad_ordenes.length() && !secuencia_invalida){

			// Si alguna instruccion no está contemplada

			char c = toupper(cad_ordenes.at(i));

			secuencia_invalida = c != INS_IZQDA && c != INS_DCHA 
							&& c != INS_ARRIBA && c != INS_ABAJO;

			if(!secuencia_invalida)
				i++;
		}

	}while(secuencia_invalida);

	// Se rellena ord con los valores de cad_ordenes

	int lon = cad_ordenes.length();

	char ord[lon];

	for(int i = 0; i < lon; i++){
		ord[i] = toupper(cad_ordenes.at(i));
	}

	// CÁLCULOS *************************************************************

	int instruccion = -1;

	bool dentro_mapa = true;

	while(instruccion < lon && dentro_mapa){
	
		// Se cuenta que el robot ha pasado por dicha posición del mapa

		mapa[pos.fila-1][pos.columna-1]++;

		// Aumenta el número de instrucción

		instruccion++;	

		switch(ord[instruccion]){
			case INS_IZQDA:	// Izquierda
				pos.columna--;
				break;

			case INS_DCHA:	// Derecha
				pos.columna++;
				break;

			case INS_ARRIBA:	// Arriba
				pos.fila++;
				break;

			case INS_ABAJO:	// Abajo
				pos.fila--;
				break;
		}	

		// Evalúa si el robot sigue estando dentro del mapa

		dentro_mapa = pos.fila >= MIN_FILAS && pos.fila <= MAX_FILAS && 
				pos.columna >= MIN_COLUMNAS && pos.columna <= MAX_COLUMNAS;
	}

	// SALIDAS **************************************************************

	cout << setw(1);

	cout << endl;

	// Si se salió del mapa, imprime el número de órdenes

	if(!dentro_mapa)
		cout << "Numero de ordenes: " << instruccion << endl;

	else{		// Si no, imprime el mapa

		// Parte superior mapa --------------------------------------------

		cout << "   : ";

		// Se imprimen el número de columnas

		for(int i = MIN_COLUMNAS; i <= MAX_COLUMNAS; i++){
			cout << i << " ";
		}

		cout << "   " << endl;

		cout << "   ";

		// Por cada columna que haya imprime tres separadores

		for(int i = 0; i < NUM_COLUMNAS; i++){

			cout << "---";

		}

		cout << "   " << endl;

		// Parte central mapa --------------------------------------------

		// Se imprime el mapa

		for(int i = MAX_FILAS; i >= MIN_FILAS; i--){

			// Se imprime el número de fila

			cout << setw(2) << i << " : ";

			// Se imprimen todas las columnas de la fila

			for(int j = MIN_COLUMNAS; j <= MAX_COLUMNAS; j++){

				// Si el robot no ha pasado por la casilla se imprime un punto
				if(mapa[i-1][j-1] == 0)
					cout << ". ";

				else
					cout << mapa[i-1][j-1] << " ";

			}

			// Se vuelve a imprimir el número de fila al final

			cout << ":  " << i << endl;

		}

		// Parte inferior mapa --------------------------------------------

		cout << "   ";

		// Por cada columna que haya imprime tres separadores

		for(int i = 0; i < NUM_COLUMNAS; i++){

			cout << "---";

		}

		cout << "   " << endl;

		cout << "   : ";

		// Se imprime el número de columnas

		for(int i = MIN_COLUMNAS; i <= MAX_COLUMNAS; i++){
			cout << i << " ";
		}

		cout << "   " << endl;

	}

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/RobotTablero.cpp)

## 4. RobotGeneraOrdenes.cpp
Vamos a trabajar ahora con un robot similar al del ejercicio superior, ```3. RobotTablero.cpp```:  
  
Ahora, va a poder moverse por una región rectangular del tablero de ```NUM_FILAS``` filas y ```NUM_COLS``` columnas.  
  
El objetivo es hacer uqe recorra todas las casillas del tablero, pasando una vez por cada casillas. Empezará por la casilla ```(1, 1)``` y desde allí se desplazará, casilla a casilla, hasta cubrir todo el tablero.  
  
El programa solicitará la casilla inicial y generará una cadena de órdenes para:  
1. Mover el robot a la casilla ```(1, 1)```.
2. Recorrer todo el tablero.  
  
El robot debe recorrer el tablero en forma de zig-zag (esto es, por filas: recorre primero la fila 1, luego la fila 2, ...).  
  
Además, el programa deberá tener comentada la forma de recorrer el tablero en forma de espiral (recorriendo primero los bordes y, por último, el centro). Dicho cambio se tendrá que realizar lo más sencillo posible.  
  
Ejemplo:  
```Posicion inicial = (5, 5)```  
```Ordenes = IIIIBBBBDDDDDDAIIIIIIADDDDDDAIIIIIIADDDDDDAIIIIII```  
```Num. ordenes = 49```  
```------------------------```  
```La serie de ordenes es: correcta```  
```Se ejecutaron 49 ordenes```  
  
```   : 1 2 3 4 5 6 7 ```  
```   -----------------   ```  
``` 6 : 1 1 1 1 1 1 1 :  6```  
``` 5 : 2 2 2 2 2 1 1 :  5```  
``` 4 : 2 1 1 1 1 1 1 :  4```  
``` 3 : 2 1 1 1 1 1 1 :  3```  
``` 2 : 2 1 1 1 1 1 1 :  2```  
``` 1 : 1 1 1 1 1 1 1 :  1```  
```   -----------------   ```  
```   : 1 2 3 4 5 6 7 ```  
```cpp
#include <iostream>
#include <iomanip>

using namespace std;

// Enumerado que determina el modo de pasar por las casills

enum class RecorrerMapa {Zigzag, Espiral};

// Definición de struct

struct Punto{
	int fila;
	int columna;
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

	// Se repite mientras que no sea un número entero

	do{

		cout << mensaje;
		cin >> numero;

	}while(!EsEntero(numero));

	return stoi(numero);
}

/****************************************************************************
	Imprime un mensaje en consola y lee el número entero que introduce el 
	usuario. Repite la entrada mientras que el valor introducido no sea
	un número entero o mientras que el número no esté en el intervalo
	[min, max]

  Parámetros: titulo, el mensaje que se muestra al usuario
			  min, el mínimo valor válido
			  max, el máximo valor válido
  Devuelve: el número entero que introduce el usuario

****************************************************************************/

int LeerEnteroEnRango(string mensaje, int min, int max){
	int numero;

	// Se repite mientras que no esté en el intervalo [min, max]

	do{

		numero = LeerEntero(mensaje);

	}while(numero < min || numero > max);

	return numero;
}

/****************************************************************************/

int main(){
	
	// Determina en qué modo recorrerá el robot el mapa *********************

	RecorrerMapa modo;

	// Para que el robot recorra el mapa en Zigzag:

	modo = RecorrerMapa::Zigzag;

	// Para que el robot recorra el mapa en Espiral:

	// modo = RecorrerMapa::Espiral;

	// **********************************************************************

	// Coordenadas mínimas y máximas de las filas y columnas

	const int MIN_FILAS = 1, MIN_COLUMNAS = 1;
	const int MAX_FILAS = 10, MAX_COLUMNAS = 10;

	const int NUM_FILAS = MAX_FILAS - MIN_FILAS + 1;
	const int NUM_COLUMNAS = MAX_COLUMNAS - MIN_COLUMNAS + 1;

	const string MSG_INTERVALO_FILAS = "(entre " + to_string(MIN_FILAS) + " y " 
												+ to_string(MAX_FILAS) + ")";

	const string MSG_INTERVALO_COLUMNAS = "(entre " + to_string(MIN_COLUMNAS) 
									+ " y " + to_string(MAX_COLUMNAS) + ")";

	// Repertorio válido de instrucciones

	const char INS_IZQDA = 'I', INS_DCHA = 'D';
	const char INS_ARRIBA = 'A', INS_ABAJO = 'B';

	int mapa[NUM_FILAS][NUM_COLUMNAS];

	// ENTRADAS ************************************************************

	// Se solicita la posición inicial del robot

	cout << "Introduzca la posición inicial del robot: " << endl;

	int fila, columna;

	fila = LeerEnteroEnRango("\tFila " + MSG_INTERVALO_FILAS + ": ", 
												MIN_FILAS, MAX_FILAS);

	columna = LeerEnteroEnRango("\tColumna " + MSG_INTERVALO_COLUMNAS + ": ", 
												MIN_COLUMNAS, MAX_COLUMNAS);

	// Se almacena la posición en pos

	Punto pos = {fila, columna};

	// CÁLCULOS *************************************************************

	// Generación de la secuencia de instrucciones *************************

	// 1.- Calculamos el número de instrucciones que usaremos ---------------
		
	// Número de instrucciones para recorrer el mapa a partir de (1, 1)

	int dimension_mapa = NUM_FILAS * NUM_COLUMNAS;

	// Número de instrucciones para llevar el robot a (1, 1)

	int desplazamiento_horiz = pos.fila - MIN_FILAS;

	int desplazamiento_vert = pos.columna - MIN_COLUMNAS;

	// Declara el array que usaremos para las instrucciones

	int lon = dimension_mapa + desplazamiento_horiz + desplazamiento_vert;

	char ord[lon];

	int posiciones_llenas = 0;

	// 2.- Genera la secuencia para llevar el robot a (1, 1)  ----------------

	// Lleva el robot a la columna 1

	for(int i = pos.columna; i > MIN_COLUMNAS; i--){

		ord[posiciones_llenas] = INS_IZQDA;

		posiciones_llenas++;

	}

	// Lleva el robot a la fila 1

	for(int i = pos.fila; i > MIN_FILAS; i--){
		
		ord[posiciones_llenas] = INS_ABAJO;

		posiciones_llenas++;

	}

	// 3.- Genera la secuencia para recorrer el mapa en función del modo 

	switch(modo){
	
		// 3.- Genera la secuencia para recorrerlo en ZigZag ----------------

		case RecorrerMapa::Zigzag:{
			
			bool avanzar_dcha = true;

			// Rellena la primera fila
		
			char rellenar = (avanzar_dcha)? INS_DCHA : INS_IZQDA;
		
			for(int i = MIN_COLUMNAS; i < MAX_COLUMNAS; i++){
		
				// Avanza hacia la derecha o hacia la izquierda
		
				ord[posiciones_llenas] = rellenar;
		
				posiciones_llenas++;
		
			}
		
			// Recorre todas las filas a partir de la segunda
		
			for(int i = MIN_FILAS + 1; i <= MAX_FILAS; i++){
		
				// Avanza a la siguiente fila
		
				ord[posiciones_llenas] = INS_ARRIBA;
		
				posiciones_llenas++;
			
				// Invierte la dirección de avance
		
				avanzar_dcha = !avanzar_dcha;
		
				// Recorre toda la fila
		
				rellenar = (avanzar_dcha)? INS_DCHA : INS_IZQDA;
		
				for(int i = MIN_COLUMNAS; i < MAX_COLUMNAS; i++){
		
					// Avanza hacia la derecha o hacia la izquierda
		
					ord[posiciones_llenas] = rellenar;
		
					posiciones_llenas++;
		
				}
			}

			break;}

		// 3.2- Genera la secuencia para recorrerlo en Espiral ---------------

		case RecorrerMapa::Espiral:{
	
			// Recorre la primera fila

			for(int i = MIN_COLUMNAS; i < MAX_COLUMNAS; i++){
			
				// Avanza hacia la derecha
		
				ord[posiciones_llenas] = INS_DCHA;
		
				posiciones_llenas++;
		
			}
		
			// Indican el número de caracteres que se colocan por cada fila o 
			// columna de la espiral
		
			int rellena_filas = NUM_FILAS - 1;
			int rellena_columnas = NUM_COLUMNAS - 1;
		
			// Indica si el robot tiene que ir a la derecha y arriba o no
		
			bool dcha_y_arriba = true;
		
			// Mientras que no se rellenen todas las casillas
		
			while(posiciones_llenas < lon - 1){
		
				// Se rellena una columna de la espiral
		
				char rellenar_espiral = (dcha_y_arriba)? INS_ARRIBA: INS_ABAJO;
		
				for(int i = 0; i < rellena_filas; i++){
					ord[posiciones_llenas] = rellenar_espiral;
			
					posiciones_llenas++;
				}
			
				// Se rellena una fila de la espiral
		
				rellenar_espiral = (dcha_y_arriba)? INS_IZQDA : INS_DCHA;
		
				for(int i = 0; i < rellena_columnas; i++){
					ord[posiciones_llenas] = rellenar_espiral;
		
					posiciones_llenas++;
				}
		
				// Se alternan las posiciones
		
				dcha_y_arriba = !dcha_y_arriba;
		
				// En la siguiente vuelta, las filas y las columnas tendrán
				// una casilla menos a rellenar
		
				rellena_filas--;
				rellena_columnas--;
			}

			break;}
	}

	// Se ejecuta el repertorio de instrucciones en el robot *****************

	int instruccion = -1;	// Para que se aumente al entrar en el bucle

	bool dentro_mapa = true;

	while(instruccion < posiciones_llenas && dentro_mapa){
	
		// Se cuenta que el robot ha pasado por dicha posición del mapa

		mapa[pos.fila-1][pos.columna-1]++;

		// Aumenta el número de instrucción

		instruccion++;	

		switch(ord[instruccion]){
			case INS_IZQDA:	// Izquierda
				pos.columna--;
				break;

			case INS_DCHA:	// Derecha
				pos.columna++;
				break;

			case INS_ARRIBA:	// Arriba
				pos.fila++;
				break;

			case INS_ABAJO:	// Abajo
				pos.fila--;
				break;
		}	

		// Evalúa si el robot sigue estando dentro del mapa

		dentro_mapa = pos.fila >= MIN_FILAS && pos.fila <= MAX_FILAS && 
				pos.columna >= MIN_COLUMNAS && pos.columna <= MAX_COLUMNAS;
	}

	// SALIDAS **************************************************************

	cout << setw(1);

	cout << endl;

	// Si se salió del mapa, imprime el número de órdenes

	if(!dentro_mapa)
		cout << "Numero de ordenes: " << instruccion << endl;

	else{

		// Imprime por qué método se ha recorrido el mapa -----------------

		switch(modo){
			case RecorrerMapa::Zigzag:
				cout << "Se ha recorrido el mapa en forma de zig-zag." << endl;
				break;

			case RecorrerMapa::Espiral:
				cout << "Se ha recorrido el mapa en forma de espiral." << endl;
				break;
		}

		cout << endl;

		// Parte superior mapa --------------------------------------------

		cout << "   : ";

		// Se imprimen el número de columnas

		for(int i = MIN_COLUMNAS; i <= MAX_COLUMNAS; i++){
			cout << i << " ";
		}

		cout << "   " << endl;

		cout << "   -----------------------   " << endl;

		// Parte central mapa --------------------------------------------

		// Se imprime el mapa

		for(int i = MAX_FILAS; i >= MIN_FILAS; i--){

			// Se imprime el número de fila

			// Si tiene sólo 1 cifra se introduce un espacio

			if(i < 10)
				cout << " ";

			cout << i << " : ";

			// Se imprimen todas las columnas de la fila

			for(int j = MIN_COLUMNAS; j <= MAX_COLUMNAS; j++){

				if(mapa[i-1][j-1] == 0)
					cout << ". ";

				else
					cout << mapa[i-1][j-1] << " ";

			}

			// Se vuelve a imprimir el número de fila al final

			cout << ":  " << i << endl;

		}

		// Parte inferior mapa --------------------------------------------

		cout << "   -----------------------   " << endl;

		cout << "   : ";

		// Se imprime el número de columnas

		for(int i = MIN_COLUMNAS; i <= MAX_COLUMNAS; i++){
			cout << i << " ";
		}

		cout << "   " << endl;

	}

	cout << endl;

	return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/RobotGeneraOrdenes.cpp)

# Ejercicios Opcionales
## 1. Ranking.cpp
Se quiere elaborar el ránking anual nacional de una prueba de atletismo, Se trata de los 1500 ML en pista (AL). Cada Federación territorial ha recopilado los tiempos oficiales de todas las competiciones celebradas y se han remitido a la Federación nacional que ha elaborado un fichero de texto. En el fichero no hay ningún orden en los datos aunque la información de cada registro (un resultado concreto) ocupa una sóla línea. Cada línea tiene la siguiente información:  
```fecha de evento, código de licencia y tiempo```:
- La fecha se encuentra en una palabra de longitud 10 con formato: ```dd/mm/aaaa```.
- El código de licencia se encuentra en una palabra de longitud variable (su formato no tiene importancia para este problema).
- El tiempo se encuentra en una palabra de longitud 12 con formato: ```hh:mm:ss:mmm```  
  
El número de registros que se van a procesar se desconoce. Se sabe que no hay más cuando se encuentra la palabra ```FIN``` en lugar de una fecha.  
Por ejemplo:  
```07/05/2021   GR-4567     00:03:45:105```  
```12/04/2021   MA-67       00:03:43:129```  
```17/10/2021   J-1237      00:03:47:587```  
```01/02/2021   GR-1234     00:04:01:045```  
```05/12/2021   M-11234     00:03:52:345```  
```22/05/2021   B-1092      00:03:52:345```  
```FIN```  
  
Escribir un programa que elabore el ránking, ordenando los datos de manera creciente de acuerdo al ```tiempo```. El resultado debe aparecer bien formateado. Por ejemplo, para los datos dados anteriormente:  
  
```Ranking de la prueba: 1500ML```  
```1    MA-67       12 Abril        2021    03:43:129```  
```2    GR-4567      7 Mayo         2021    03:45:105```  
```3    J-1237      17 Octubre      2021    03:47:587```  
```4    M-11234      5 Diciembre    2021    03:52:345```  
```5    B-1092      22 Mayo         2021    03:53:345```  
```6    GR-1234      1 Febrero      2021    04:01:045```  
  
Algunas notas prácticas sobre la resolución:
- Para mejorar la capacidad de abstracción y facilitar la resolución recomendamos usar ```struct``` para caracterizar a las entidades básicas como ```fecha``` y ```tiempo```.
- La tripleta ```(fecha, licencia, tiempo)``` caracteriza a la entidad ``` marca ```.
- El código de licencia ocupa 10 casillas.
- Cree una función que compare dos datos de tipo ```tiempo```.

## 2. RLEMatriz.cpp
Recordamos la codificación RLE del ejercicio ```2. RLE.cpp``` de la [Sesión VI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2006/Sesi%C3%B3n%2006.md) de prácticas:  
  
El método RLE (Run Length Encoding) codifica una secuencia de datos formada por series de valores idénticos consecutivos como una secuencia de parejas de número-carácter (indica el número de veces que se repite dicho carácter de forma consecutiva). Se trata de un mecanismo de compresión de datos (zip) sin pérdidas.  
  
Por ejemplo, la cadena:  
```A A A X X X X X D D D D D D Q .```  
  
Codificada mediante RLE es:  
```3A 5X 6D 1Q```  
  
El programa solicitará un número indefinido de secuencias de caracteres. El número total de secuencias no podrá ser mayor que 50 y la longitud de cada secuencia tampoco. Guardar la entrada en una matriz.  
  
El programa codificará cada una de las entradas, guardándolas en una nueva matriz ```codificada```. Mostrarla.  
  
A continuación, el programa descodificará dicha matriz, guardándola en una nueva matriz ```descodificada```.  
  
El programa comparará las matrices de entrada y ```descodificada```, informando si son iguales o distintas.

## 3. HistogramaVocales.cpp
Queremos calcular la frecuencia absoluta de las vocales presentes en un texto y mostrar el resultado en forma de histograma usando caracteres. El histograma resultante deberá tener un aspecto como el de la figura:  
  
```7   -```  
```6 - -```  
```5 - -```  
```4 - -   -```  
```3 - - - -```  
```2 - - - - -```  
```1 - - - - -```  
```  a e i o u```  
  
Dicho histograma se puede mostrar a partir de una matriz de caracteres. El ejemplo tiene tantas líneas como la frecuencia e la vocal que más se repite (7), y tantas columnas como el número de vocales.  
  
Escriba un programa que lea una serie indefinida de caracteres de la entrada estándar (terminados por ```|```) y que muestre el histograma que representa la frecuencia absoluta de las vocales introducidas.  
  
Suponga que la frecuencia absoluta no puede ser mayor que 500.

## 3. HistogramaLetras.cpp
Vamos a mejorar el ejercicio anterior, ```3. HistogramaVocales.cpp```, calculando el histograma para todas las letras del alfabeto inglés:  
  
Escriba un programa que lea una serie indefinida de caracteres de la entrada estanar (terminados por ```|```) y que meustre el histograma que representa la frecuencia absoluta de las letras introducidas.  
  
Ejemplo: Dadas las letras: 
  
| Letra | Frecuencia |
|-------|------------|
| a     | 9          |
| b     | 0          |
| c     | 6          |
| d     | 6          |
| e     | 8          |
| f     | 1          |
| g     | 1          |
| h     | 2          |
| i     | 8          |
| j     | 2          |
| k     | 0          |
| l     | 5          |
| m     | 3          |
| n     | 4          |
| o     | 10         |
| p     | 2          |
| q     | 2          |
| r     | 4          |
| s     | 1          |
| t     | 4          |
| u     | 3          |
| v     | 0          |
| w     | 0          |
| x     | 0          |
| y     | 1          |
| z     | 0          |
  
Histograma:  
```10 | . . . . . . . . . . . . . . x . . . . . . . . . . . ```  
```   | . . . . . . . . . . . . . . x . . . . . . . . . . . ```  
``` 9 | x . . . . . . . . . . . . . x . . . . . . . . . . . ```  
```   | x . . . . . . . . . . . . . x . . . . . . . . . . . ```  
``` 8 | x . . . x . . . x . . . . . x . . . . . . . . . . . ```  
```   | x . . . x . . . x . . . . . x . . . . . . . . . . . ```  
``` 7 | x . . . x . . . x . . . . . x . . . . . . . . . . . ```  
```   | x . . . x . . . x . . . . . x . . . . . . . . . . . ```  
``` 6 | x . x x x . . . x . . . . . x . . . . . . . . . . . ```  
```   | x . x x x . . . x . . . . . x . . . . . . . . . . . ```  
``` 5 | x . x x x . . . x . . x . . x . . . . . . . . . . . ```  
```   | x . x x x . . . x . . x . . x . . . . . . . . . . . ```  
``` 4 | x . x x x . . . x . . x . x x . . x . x . . . . . . ```  
```   | x . x x x . . . x . . x . x x . . x . x . . . . . . ```  
``` 3 | x . x x x . . . x . . x x x x . . x . x x . . . . . ```  
```   | x . x x x . . . x . . x x x x . . x . x x . . . . . ```  
``` 2 | x . x x x . . x x x . x x x x x x x . x x . . . . . ```  
```   | x . x x x . . x x x . x x x x x x x . x x . . . . . ```  
``` 1 | x . x x x x x x x x . x x x x x x x x x x . . . x . ```  
```   | x . x x x x x x x x . x x x x x x x x x x . . . x . ```  
```   | x . x x x x x x x x . x x x x x x x x x x . . . x . ```  
```   ----------------------------------------------------- ```  
```     a b c d e f g h i j k l m n o p q r s t u v w x y z ```  
  
## 5. ASCIIArt.cpp
Cree un programa que sea capaz de dibujar, en un tablero de ```51x51```, limitado por los píxeles ```(0, 0)```, ```(0, 50)```, ```(50, 0)``` y ```(50, 50)```, círculos y rectángulos:  
- El fondo se dibujará con el carácter ```.```.
- Las figuras se dibujarán con el carácter ```\*```.
- Las intersecciones entre figuras con el carácter ```x```.  
  
Desarrolle un programa que pida al usuario si quiere dibujar un círculo o un rectángulo y que posteriormente solicite los datos para dibujar la opción deseada. Si la figura no cabe en el lienzo en su totalidad, dibuje la parte que sí cabe.  
  
Nota: puede reusar los ```structs``` creados en el ejercicio ```1. Rectangulo.cpp``` de la [Sesión IX](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/Sesi%C3%B3n%2009.md) de prácticas.

## 6. GraficoTemperaturas.cpp
Queremos visualizar dos gráficas que resuman las temperaturas registradas diariamente:
1. Las medias semanales de las mínimas.
2. Las medias semanales de las máximas. 
   
Realice un programa que dibuje dichas gráficas de forma similar a los histogramas del ejercicio ```4. HistogramaLetras.cpp```.  
  
Puede encontrar datos de tiempo en la página [https://www.eltiempo.es/](https://www.eltiempo.es/).

## 7. AsignarAsientos.cpp
Escribir un programa para asignar asientos de pasajeros en un avión.  
Asumimos un avión pequeño de 7 filas con un pasillo central y dos asientos a cada lado. Cada asiento en una fila está etiquetado con ```A```, ```B```, ```C``` o ```D```.  
  
El programa mostrará con una x el asiento que está ya asignado.  
Por ejemplo, después de asignar los asientos ```1A, 2B, 4C```, lo que se mostrará en pantalla tendrá un aspecto como el que se muestra en la figura:  
  
```1 | x B | C D |```  
```2 | A x | C D |```  
```3 | A B | C D |```  
```4 | A B | x D |```  
```5 | A B | C D |```  
```6 | A B | C D |```  
```7 | A B | C D |```  
  
Después de mostrar los asientos disponibles, el programa pregunta por el asiento deseado: el usuario teclea un asiento (número de fila, después la letra) y el programa actualiza la asignación mostrando el esquema anterior. Esto continúa hasta que todos los asientos se asignen o hasta que el usuario indique que no quiere asignar más asientos (introduciendo el valor -1 en el número de la fila).  
Si el usuario introduce un asiento ya asignado, el programa mostrará un mensaje indicando que el asiento está ocupado y volverá a solicitarlo.

## 8. RedCiudades.cpp
Se desea construir una matriz de datos double para almacenar las distancias de los caminos directos que conectan un conjunto de ciudades. Si entre dos ciudades no existe un camino directo, se almacenará un cero. Se supone que la distancia de una ciudad consigo misma será cero y que las distancias son simétricas. Un ejemplo con 5 ciudades sería el mostrado en la figura:  
  
|    | C1  | C2 | C3  | C4 | C5  |
|----|-----|----|-----|----|-----|
| C1 | 0   | 50 | 100 | 0  | 150 |
| C2 | 50  | 0  | 70  | 0  | 0   |
| C3 | 100 | 70 | 0   | 60 | 80  |
| C4 | 0   | 0  | 60  | 0  | 90  |
| C5 | 150 | 0  | 80  | 90 | 0   |
  
Suponga que nunca se trabajará con más de 50 ciudades.  
Escriba un programa que lea el número de ciudades de la red, y las distancias entre las ciudades (recuerde que 0 indica que entre dos ciudades no existe un camino directo) y rellene adecuadamente la matriz de distancias.  
A continuación, resuelva las siguientes tareas, mostrando el resultando en pantalla:
1. Obtener la ciudad (su índice) con el mayor número de conexiones directas.
2. Dada una ciudad ```j```, obtener las ciudades conectadas directamente con ```j```.
3. Dadas dos ciudades ```i``` y ```j``` para las cuales no existe un camino directo, obtener aquella ciudad intermedia ```z``` que permite hacer el trayecto entre ```i``` y ```j``` de manera más económica. Si no existiera dicha ciudad, se indicará expresamente.
4. Lea una serie de valores ```int```, número de ciudades, e indique si todas las ciudades tienen conexiones directas entre sí. El terminador será ```-1```.

## 9. RankingAmpliacion.cpp
Se quiere ampliar la funcionalidad del ejercicio ```1. Ranking.cpp``` de esta misma sesión. Recordamos su enunciado:  
  
Se quiere elaborar el ránking anual nacional de una prueba de atletismo, Se trata de los 1500 ML en pista (AL). Cada Federación territorial ha recopilado los tiempos oficiales de todas las competiciones celebradas y se han remitido a la Federación nacional que ha elaborado un fichero de texto. En el fichero no hay ningún orden en los datos aunque la información de cada registro (un resultado concreto) ocupa una sóla línea. Cada línea tiene la siguiente información:  
```fecha de evento, código de licencia y tiempo```:
- La fecha se encuentra en una palabra de longitud 10 con formato: ```dd/mm/aaaa```.
- El código de licencia se encuentra en una palabra de longitud variable (su formato no tiene importancia para este problema).
- El tiempo se encuentra en una palabra de longitud 12 con formato: ```hh:mm:ss:mmm```  
  
El número de registros que se van a procesar se desconoce. Se sabe que no hay más cuando se encuentra la palabra ```FIN``` en lugar de una fecha.  
Por ejemplo:  
```07/05/2021   GR-4567     00:03:45:105```  
```12/04/2021   MA-67       00:03:43:129```  
```17/10/2021   J-1237      00:03:47:587```  
```01/02/2021   GR-1234     00:04:01:045```  
```05/12/2021   M-11234     00:03:52:345```  
```22/05/2021   B-1092      00:03:52:345```  
```FIN```  
  
Escribir un programa que elabore el ránking, ordenando los datos de manera creciente de acuerdo al ```tiempo```. El resultado debe aparecer bien formateado. Por ejemplo, para los datos dados anteriormente:  
  
```Ranking de la prueba: 1500ML```  
```1    MA-67       12 Abril        2021    03:43:129```  
```2    GR-4567      7 Mayo         2021    03:45:105```  
```3    J-1237      17 Octubre      2021    03:47:587```  
```4    M-11234      5 Diciembre    2021    03:52:345```  
```5    B-1092      22 Mayo         2021    03:53:345```  
```6    GR-1234      1 Febrero      2021    04:01:045```  
  
Algunas notas prácticas sobre la resolución:
- Para mejorar la capacidad de abstracción y facilitar la resolución recomendamos usar ```struct``` para caracterizar a las entidades básicas como ```fecha``` y ```tiempo```.
- La tripleta ```(fecha, licencia, tiempo)``` caracteriza a la entidad ``` marca ```.
- El código de licencia ocupa 10 casillas.
- Cree una función que compare dos datos de tipo ```tiempo```.

En esta ocasión, disponemos de varias pruebas en las que participarán distintos corredores. La entrada será la misma salvo que comenzará por la prueba en cuestión:  
  
Por ejemplo:  
```100ML 07/05/2021   GR-4567     00:03:45:105```  
```100ML 12/04/2021   MA-67       00:03:43:129```  
```100ML 17/10/2021   J-1237      00:03:47:587```  
```100ML 01/02/2021   GR-1234     00:04:01:045```  
```100ML 05/12/2021   M-11234     00:03:52:345```  
```100ML 22/05/2021   B-1092      00:03:52:345```  
```500ML 12/04/2021   MA-67       00:03:43:129```  
```500ML 17/10/2021   J-1237      00:03:47:587```  
```500ML 01/02/2021   GR-1234     00:04:01:045```  
```500ML 05/12/2021   M-11234     00:03:52:345```  
```500ML 22/05/2021   B-1092      00:03:52:345```  
```800ML 07/05/2021   GR-4567     00:03:45:105```  
```800ML 12/04/2021   MA-67       00:03:43:129```  
```800ML 17/10/2021   J-1237      00:03:47:587```  
```800ML 01/02/2021   GR-1234     00:04:01:045```  
```800ML 22/05/2021   B-1092      00:03:52:345```  
  
Un mismo corredor puede participar en distintas pruebas. Se pide elaborar un ranking por separado para cada prueba.
