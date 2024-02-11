# Fundamentos de Programación. Sesión XII de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión XII de prácticas.

# Clase SecuenciaCaracteres
A partir de esta sesión de prácticas, y a lo largo de las siguientes, serán de interés varios ejercicios que trabajen sobre la clase ```SecuenciaCaracteres```. La implementación básica de esta clase se nos proporciona aquí y podremos usarla en cada ejercicio futuro.  
  
En cada ejercicio que esta se nos mencione, tendremos un enlace a su código, listo para ser copiado.
[Código de la clase](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/SecuenciaCaracteres.cpp)
# Clase SecuenciaEnteros
A partir de esta sesión de prácticas, y a lo largo de las siguientes, serán de interés varios ejercicios que trabajen sobre la clase ```SecuenciaEnteros```. La implementación básica de esta clase se nos proporciona aquí y podremos usarla en cada ejercicio futuro.  
  
En cada ejercicio que esta se nos mencione, tendremos un enlace a su código, listo para ser copiado.
[Código de la clase](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/SecuenciaEnteros.cpp)
## 1. InflacionMatriz.cpp
Reescriba la solución al ejercicio ```2. InflacionMatriz.cpp``` de la [Sesión X](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/Sesi%C3%B3n%2010.md) de prácticas, ahora con una nueva clase ```GestorIPC``` cuya definición indicamos tras recordar el enunciado del ejercicio:  
  
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
  
Ahora, deberá crear una clase ```GestorIPC```. Aconsejamos hacerlo con la siguiente definición:
```cpp
struct InfoIPC{
    int indice_pais;
    double valor_medio_IPC;
    int anio_inicio;
    int num_anios;
};

class GestorIPC{
    PRIMER_ANIO = 2001;
    ULTIMO_ANIO = 2021;
    NUM_ANIOS = ULTIMO_ANIO - PRIMER_ANIO + 1;
    NUM_PAISES = 4;
    
    string PAISES[NUM_PAISES];
    double IPC[NUM_ANIOS][NUM_PAISES];
    
public:
    int PrimerAnio();
    int UltimoAnio();
    int NumAnios();
    int NumPaises();
    
    string NombrePais(int pais);
    double ValorIPC(int anio, int pais);
    
    double IPC_Medio_PaisPeriodo(int pais, int primer_anio, int num_anios);
    
    InfoIPC Info_IPC_MinMedio_Periodo(int num_anios);
    InfoIPC Info_IPC_MaxMedio_Periodo(int num_anios);
};
```

[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/InflacionMatriz.cpp)

## 2. NumerosSecuenciables.cpp 
Recordamos la definición de número secuenciable del ejercicio ```6. Secuenciable.cpp``` de la [Sesión VII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2007/Sesi%C3%B3n%2007.md) de prácticas:  
  
Diremos que un número entero es _secuenciable_ si se puede expresar como suma de números consecutivos.  
Por ejemplo: $6 = 1 + 2 + 3$, $15 = 7 + 8$.  
Dicha descomposición no tiene por qué ser única.  
Por ejemplo: $15 = 7 + 8 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5$.  
Curiosidad: los únicos números con 0 descomposiciones son las potencias de 2.  
  
Ahora, cree una clase ```GestorNumerosSecuenciables``` con un esquema similar al siguiente:  
```cpp
class GestorNumerosSecuenciables{
    int valor;  // PRE: 1 <= valor
    
public:
    GestorNumerosSecuenciables();
    GestorNumerosSecuenciables(int n);
    
    void SetValor(int n);
    int GetValor();
    
    bool EsSeuenciable();
    int NumSecuencias();
};
```

Cree un programa que solicite dos números enteros (el segundo mayor que el primero) y un número de secuencias; y que imprima todos los números entre el rango introducido que tienen ese número de secuencias.  
  
Por ejemplo:  
```Numero inicial: 1```  
```Numero final (mayor que 1): 20```  
```Numero de secuencias: 2```  
  
```Numeros secuenciables con 2 secuencias:```  
```9 ( 2 secuencias)```  
	```9 = 2 + 3 + 4```  
	```9 = 4 + 5```  
```18 ( 2 secuencias)```  
	```18 = 3 + 4 + 5 + 6```  
	```18 = 5 + 6 + 7```  
  
```Hay 2 numeros con 2 secuencias```  

[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/NumerosSecuenciables.cpp)

## 3. Empleados.cpp
Este ejercicio parte del problema planteado en el ejercicio ```1. ArrayEmpleados.cpp``` de la [Sesión X](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/Sesi%C3%B3n%2010.md) de prácticas:  
  
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
  
Ahora, deberá crear una clase ```Empleado``` para representar a los empleados.  
  
Use un array de objetos ```Empleado``` para almacenar los empleados leidos. Muestre su contenido después de leer los datos de los empleados. Calcule los salarios mínimos y máximos, muestre sus valores y los nombres y apellidos de los empleados que ganan menos y más. Calcule el salario medio, muestre su valor y después muestre un listado de los empleados cuyo salario es superior al salario medio.  
  
Nota: recomendamos la ejecución del programa con redirección de datos de entrada. Le dejamos aquí el [fichero](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/Empleados.txt) listo con la entrada.  
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/Empleados.cpp)

## 4. EliminaOcurrencias.cpp
Este ejercicio trabaja sobre la clase ```SecuenciaCaracteres```. Puede encontrar su código en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/SecuenciaCaracteres.cpp).  
  
Añada el método ```EliminaOcurrencias``` para eliminar todas las apariciones que hubiese de un determinado carácter ```a_borrar``` en la secuencia.  
  
Por ejemplo, después de eliminar el carácter 'o' de la secuencia  ```{'S', 'o', 'Y', 'y', 'o'}```, esta debe quedar:  
```{'S', 'Y', ' ', 'y'}```.  
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/EliminaOcurrencias.cpp)

## 5. EliminaExcesoBlancos.cpp
Este ejercicio trabaja sobre la clase ```SecuenciaCaracteres```. Puede encontrar su código en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/SecuenciaCaracteres.cpp).  
  
Añada el método ```EliminaExcesoBlancos()``` para eliminar el exceso de caracteres en blanco, es decir, que sustituya todas las secuencias de espacios en blanco por un sólo espacio.  
  
Por ejemplo, si el vector original es ```{' ', 'a', 'h', ' ', ' ', ' ', 'c'}```, que contiene una secuencia de tres espacios consecutivos, el vector resultante debe ser ```{' ', 'a', 'h', ' ', 'c'}```.  
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/EliminaExcesoBlancos.cpp)

## 6. OrdenacionSecuencia.cpp 
Este ejercicio trabaja sobre la clase ```SecuenciaEnteros```. Puede encontrar su código en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/SecuenciaEnteros.cpp).  
  
En este ejercicio, definimos un nuevo criterio de orden entre dos números enteros positivos:  
  
Un valor entero $a$ será mayor que otro, $b$, si el número de dígitos '9' es mayor en $a$ que en $b$. Si el número de '9's es igual, el mayor será el que tiene más '8's. Si hubiera empate, consideraremos el '7'. Repetir hasta llegar a '0'.  
Si la frencuencia de todos los dígitos es igual en ambos valores, se les considera iguales.  
  
Añada cuatro nuevos métodos a la clase ```SecuenciaEnteros```:
- ```void OrdenaSeleccion_NuevoOrden()```.
- ```void OrdenaInsercion_NuevoOrden()```.
- ```void OrdenaIntercambio_NuevoOrden()```.
- ```void OrdenaIntercambioMejorado_NuevoOrden()```.  
  
Escriba un programa que pida el número de elementos de la secuencia (casillas a ocupar) y rellene esa secuencia con números aleatorios entre ```0``` y ```999```, la ordene con los métodos implementados y muestre el resultado.  
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/OrdenacionSecuencia.cpp)

# Ejercicios Opcionales
## 1. Gaussiana.cpp
Modifique el enunciado del ejercicio ```4. Gaussiana.cpp``` de la [Sesión XI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2011/Sesi%C3%B3n%2011.md) de problemas y haga que ahora $\pi$ sea una constante estática a nivel de clase.  
Le recordamos el enunciado del ejercicio:  
  
Añada una clase ```Gaussiana``` que tenga como campos de clase la media y la desviación típica. Recuerde añadir un método ```ToString``` que nos permita ver estos valores.  
  
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

[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/Gaussiana.cpp)

## 2. Menu.cpp 
En este ejercicio proponemos que construya la clase ```Menu``` con el objetivo de poder gestionar rápidamente menús en los que las opciones se presentan con texto, asociando un número a cada opción y se selecciona la opción introduciendo el número asociado a la opción deseada. Se intentará generalizar la solución desarrollada de manera que sea adaptable al mayor número de problemas.  
  
Desde la función ```main``` la clase se verá de la siguiente manera. Suponga que va a ofrecer cuatro opciones (más la opción de salida). Las siguientes instrucciones bastan para crear el un objeto ```Menu``` llamado ```menu_principal```:  
  
```cpp
string opciones = "Terminar|Alta|Baja|Consulta|Modificacion|";
Menu menu_principal(opciones);
```  
  
La gestión del menú podría hacerse en una estructura de programa como la siguiente:  
```cpp
bool terminar = false;

while (!terminar) {
    menu_principal.ImprimeOpciones();
    int tarea = menu_principal.EligeOpcion();
    
    switch (tarea) {
    
        case (0) : { // Terminar
        
            terminar = true;
            break;
            
        } // case (0)
        
        case (1) : { // Alta
            ......
        } // case (1)
        
        ......
        
    } // switch
} // while
```
  
La ejecución de ```ImprimeOpciones``` muestra la lista de tareas disponibles y la de ```EligeOpcion``` permite que el usuario introduzca un número que indica la tarea que desea. El número suministrado debe ser correcto (en este ejemplo entre 0 y 4) y si no es así, se vuelve a pedir repetidamente. En este ejemplo sería como sigue:  
```1.- Alta```  
```2.- Baja```  
```3.- Consulta```  
```4.- Modificacion```  
```0.- Terminar```  
```Introduzca la opcion elegida --> ```

## 3. ContadorMayusculas.cpp
Realice un programa que vaya leyendo caracteres hasta que se encuentre un punto ```.```. Queremos contar el número de veces que aparece cada mayúscula.  
  
Cree una clase ```ContadorMayusculas``` que implemente los métodos necesarios para realizar la cuenta de las mayúsculas. La clase debe proporcionar los métodos:
- ```void IncrementaCuenta(char mayuscula)```.
- ```int CuantasHay(char mayuscula)```.  
  
Los contadores deberán almacenarse en un array como miembro privado de la clase.

## 4. Eratostenes.cpp
La _Criba de Erastóstenes_ permite hallar todos los números primos menores que un número ```n```. Recordamos el algoritmo mediante un fragmento de enunciado del ejercicio ```6. Erastotenes.cpp``` de la [Sesión IX](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2009/Sesi%C3%B3n%2009.md) de prácticas:  
  
El procedimiento consiste en escribir todos los números naturales entre 2 y ```N``` y tachar los número que no sean primos de la siguiente forma:  
- El primero (el 2) se considera primo y se tachan todos sus múltiplos.
- Se busca el siguiente número no tachado, ```p```, que se considera primo y se tachan todos sus múltiplos.
- Repetir el proceso hasta que el cuadrado de ```p``` (el siguiente número no tachado que se considera primo) es mayor que ```N```.  

En esta ocasión, se pide definir una clase ```Erastotenes```. Un objeto de la clase podrá almacenar los números primos calculados en un array de enteros:
```cpp
static const int TAMANIO = 500;
int vector_privado[TAMANIO];

//PRE: 0 <= total_utilizados <= TAMANIO
int total_utilizados; // Número de casillas ocupadas
```
  
Lo que significa que en un objeto ```Eratostenes``` se podrá guardar un máximo de ```TAMANIO``` númeos primos. El usuario de la clase quiere generar primos menores o iguales que un valor dado, por ejemplo:
```cpp
Eratostenes primos;
primos.CalculaHasta(100);
```

El método ```void CalculaHasta(int n)``` calcula y guarda en el array interno los primos menores o iguales que ```n```. Este es el método en el que se implementa la criba. Cuando se ejecute el método, se almacenarán en un vector interno del objeto todos los primos menores que ```n```.  
  
Se dará cuenta que el valor proporcionado puede ser demasiado ambicioso. Por ejemplo, si ```n``` vale 5000, no habrá espacio en el vector interno (500 casillas) para todos los primos menores que 5000. Debería guardar en el objeto Eratostenes dos valores:
- ```n```, el valor que se suministró para calcular los primos guardados.
- ```n_real```, guarda el menor valor entero mayor o igual a todos los primos del vector. Si se puedieron guardar todos los primos solicitados, ```n = n_real```.  
  
La clase ofrecerá estos métodos:
- ```int GetReferencia()```, devuelve ```n```.
- ```int GetReferenciaReal()```, devuelve ```n_real```.
- ```int TotalCalculados()```, devuelve cuántos primos hay almacenados.
- ```int Elemento(int k)```, devuelve el $k$-ésimo primo almacenaldo.  
  
Un programa que use esta clase podría ser:
```cpp
Eratostenes primos;
primos.CalculaHasta(100);

cout << "Primos <= " << primos.GetReferencia() << endl;
cout << "Obtenidos <= " << primos.GetReferenciaReal() << endl;
     
cout << "El mayor es: << primos.Elemento(primos.TotalCalculados()-1) << endl;

cout << "Primos: " << endl;

for (int i=0; i<primos.TotalCalculados(); i++)
    cout << setw(5) << primos.Elemento(i);
```

5. RedSocial.cpp
Implemente una clase ```RedSocial``` para gestionar una red social. La red debe almacenar los nombres de los usuarios y las relaciones de amistad. Se propone la siguiente representación:
```cpp
class RedSocial{
    static const int MAX_USUARIOS = 100;
    string usuarios[MAX_USUARIOS];
    bool relaciones_amistad[MAX_USUARIOS][MAX_USUARIOS];
    int usuarios_utiles;

public:
    ...
};
```
  
Donde ```relaciones_amistad``` es una matriz cuadrada tal que la commponente  ```(i, j)``` es ```true``` si el usuario $i$ es amigo del usuario $j$ y ```false``` si no. Asumiremos que las relaciones de amistad son simétricas, por lo que también lo será la matriz.  
  
Se pide implementar los siguientes métodos:
- ```RedSocial()``` Crea una red vacía.
- ```int numUsuarios()``` Devuelve el número de usuarios de la red.
- ```void agregaUsuario(string usr)``` Añade el usuario ```usr``` a la red (sin amigos).
- ```void eliminaUsuario(string usr)``` Elimina el usuario ```usr``` de la red.
- ```bool existe(string usr)``` Informa si ```usr``` es un usuario de la red.
- ```void hacerAmigos(string usr1, string usr2)``` Registra una relación de amistad entre ```usr1``` y ```usr2```.
- ```void deshacerAmigos(string usr1, string usr2)``` Elimina una relación de amistad entre ```usr1``` y ```usr2```.
- ```bool sonAmigos(string usr1, string usr2)``` Informa si hay relación de amistad entre ```usr1``` y ```usr2```.  
  
Escriba un programa que cree una red y lea los nombres de los usuarios de la red (termina cuando se introduce ```FIN``` en el primer nombre). Después lee una serie de lineas que contienen parejas de nombres que indican las relaciones de amistad y va actualizando las relaciones de amistad en la red.  
  
Queremos ampliar la funcionalidad con:
- Un método que, dado un usuario ```A``` de la red, sugiera un amigo potencial para ```A```. Un amigo potencial es aquel usuario de la red (no amigo de ```A```) que tiene más amigos en común con ```A```.  
Escriba en la función main código para que solicite el nombre de un usuario y sugiera una relación de amistad par él.  
- Un método que decida si dos usuarios son _amigos circunstanciales_, es decir, si son amigos pero no tienen amigos en común.  
Escriba en la función main código para que muestre todos los amigos circunstanciales presentes en la red.

## 6. EliminaRepetidos.cpp
Este ejercicio trabaja sobre la clase ```SecuenciaCaracteres```. Puede encontrar su código en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/SecuenciaCaracteres.cpp).  
  
Añada un método ```EliminaRepetidos``` que quite los elementos repetidos, de forma que cada componente sólo aparezca una única vez. Se mantendrá la primera aparición, de izquierda a derecha.  
Por ejemplo, si el vector contiene ```{'b','a','a','h','a','a','a','a','c','a','a','a','g'}```, después de quitar los repetidos, se quedaría como: ```{'b','a','h','c','g'}```.

[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/EliminaRepetidos.cpp)

## 7. EliminaDesdeHasta.cpp
Este ejercicio trabaja sobre la clase ```SecuenciaCaracteres```. Puede encontrar su código en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/SecuenciaCaracteres.cpp).  
  
Añada los métodos ```EliminaDesde``` y ```EliminaHasta``` para eliminar todos los caracteres desde una posición dada y hasta una posición dada (incluída).  
  
Por ejemplo, en la secuencia ```{'|',' ','H','o','l','a',' ',' ','|'}```, la ejecución de ```EliminaDesde(6)``` da como resultado que la secuencia se queda en: ```{'|',' ','H','o','l','a'}```.  
Si sobre esta se ejecuta ```EliminaHasta(1)```, da como resultado ```{'H', 'o', 'l', 'a'}```.

[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/EliminaDesdeHasta.cpp)

## 8. BusquedaInterpolacion.cpp
Este ejercicio trabaja sobre la clase ```SecuenciaEnteros```. Puede encontrar su código en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/SecuenciaEnteros.cpp).  
  
Implemente un método ```BusquedaInterpolacion()``` en la clase ```SecuenciaEnteros```. El método busca un valor buscado entre las posiciones ```izda y dcha```.
