# Fundamentos de Programación. Sesión XIV de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión XIV de prácticas.

# Clase TablaRectangularEnteros
En esta sesión de prácticas, usará la clase ```TablaRectangularEnteros``` en un par de ejercicios. Le dejamos a continuación dos versiones de esta clase, una implementada mediante una matiz de enteros y otra mediante un array de ```SecuenciaEnteros```.  
Le dejamos el código de las dos implementaciones, además de la clase ```SecuenciaEnteros```:  
  
[TablaRectangularEnterosMatriz]()
[TablaRectangularEnterosSecuencia]()
[SecuenciaEnteros]()

## 1. FilaCercanaTRMatriz.cpp
Este ejercicio está basado en la clase [TablaRectangularEnterosMatriz](), que llamaremos ahora ```TablaRectangularEnteros```.  
  
Amplíe la clase ```TablaRectangularEnteros``` con un método que busque la fila de la matriz que más se parezca a una objeto ```SecueniaEnteros``` proporcionado que llamaremos ```referencia```. El método devolverá el número de la fila.  
  
La similitud entre dos ```SecuenciaEnteros``` $x = (x_1, \ldots, x_n)$ y $y = (y_1, \ldots, y_n)$ vendrá dada por la distancia euclídea entre ambos:
$$dist(x,y) = \sqrt{(x_1 - y_1)² + \ldots + (x_n - y_n)²}$$
Además, la búsqueda sólo se hará sobre un conjunto seleccionado de filas de la tabla, enumeradas en la ```SecuenciaEnteros``` ```filas_a_comparar```.  
  
Por ejemplo, dada una matriz $M$ ($7 \times 4$) y las secuencias:  
```referencia = 2, 8, 1, 1``` y ```filas_a_comparar = 0, 2, 4, 5```.  
El programa deberá encontrar ```5``` como la fila más cercana a la secuencia ```referencia```:  
```--> 3 1 0 8```  
```    4 5 1 5```  
```--> 5 7 1 7```  
```    7 9 6 1```  
```--> 4 9 5 5```  
```--> 2 8 2 2```  
```    7 3 2 5```  
  
[Ir a la solución]()

## 2. FilaCercanaTRSecuencia.cpp
Este ejercicio está basado en la clase [TablaRectangularEnterosSecuencia](), que llamaremos ahora ```TablaRectangularEnteros```.  
  
Reescriba el ejercicio superior (```1. FilaCercanaTRMatriz.cpp```) usando ahora la clase ```TablaRectangularEnterosSecuencia``` como la clase ```TablaRectangularEnteros```.  
  
[Ir a la solución]()

## 3. EmpleadosDepartamentosMatriz.cpp
Seguimos trabajando en el famoso problema de los empleados, cuya última versión fue la del ejercicio ```4. SecuenciaEmpleados.cpp``` de la [Sesión XIII]() de prácticas.  
  
Recordamos que recomendamos trabajar con un fichero redirigiendo la entrada estándar. Use el siguiente [fichero](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/Empleados.txt).
  
Se desea organizar los datos de los empleados de una empresa agrupados por departamentos. No todos los departamentos tienen el mismo número de empleados, por lo que se escoge una tabla dentada como estructura de datos para guardar los datos de los empleados de la empresa.  
  
Escriba un programa que lea los datos de los empleados de la empresa y los guarde en una tabla dentada. Después:
1. Muestre un listado de todos los empleados, por orden de lectura, sin distinción de departamentos.
2. Muestre un listado de todos los empleados, agrupados por departamentos indicando el número de empleados en cada departamento.
3. Calcular y mostrar los empleados de menor y mayor sueldo, indicando su departamento.
4. Calcular y mostrar el sueldo medio, y a continuación, un listado de los empleados con un salario mayor que el sueldo medio y otro con con los empleados con salario menor. Estos dos listados estarán ordenados por apellidos.  
  
Deberá usar las clases:
- ```Empleado``` y ```Fecha```.
- ```SecuenciaEmpleados```.
- ```TablaDentadaEmpleados``` Que crearemos a continuación.
- ```ParejaEnteros``` Que también crearemos ahora.

Sobre la clase ```TablaDentadaEmpleados``` le proponemos la siguiente representación:
```cpp
class TablaDentadaEmpleados{
    static const int NUM_FILS = 50;     // Filas disponibles
    static const int NUM_COLS = 40;     // Columnas disponibles
    
    Empleado matriz_privada[NUM_FILS][NUM_COLS];
    
    int filas_utilizadas;       // PRE: 0 <= filas_utilizadas <= NU_FILS
    
    int cols_utilizadas[NUM_FILS];
    // PRE: 0 <= cols_utilizaadas[i] <= NUM_COLS
    // para i = 0, ..., filas_utilizadas - 1
};
```

Además, podría ser útil implementar los métodos:
```cpp
ParejaEnteros LocalizacionSalarioMenor();
ParejaEnteros LocalizacionSalarioMayor();

double SalarioMedio();
SecuenciaEmpleados EmpleadosSalrioMenor(double valor);
SecuenciaEmpleados EmpleadosSalrioMayor(double valor);
```
  
La clase ```ParejaEnteros``` sirve para gestionar una pareja de valores ```int```. En este caso nos interesa para obtener la localización de un empleado. Sugerimos:  
```cpp
class ParejaEnteros{
    int primero, segundo;
    
public:
    ParejaEnteros(int p, int s) :primero(p), segundo(s) {}
    
    void SetPrimero(int p) {primero = p;}
    void SetSegundo(int s) {segundo = s;}
    
    int GetPrimero() {return primero;}
    int GetSegundo() {return segundo;}
    
    string ToString(){
        return "{" + to_string(primero) + ", " + 
                to_string(segundo) + "}";
    }
};
```
  
El programa debe estar preparado para recibir este [archivo]() de input.
  
## 4. EmpleadosDepartamentosSecuencia.cpp
Reescriba la solución del ejercicio superior (```EmpleadosDepartamentosSecuencia.cpp```) ahora usando un array de ```SecuenciaEmpleados```.
  
# Ejercicios Opcionales
## 1. SumaFilasTablaDentada.cpp
Se desea crear una matriz dentada de valores reales leyendo sus valores de la entrada estándar y realizar algunos cálculos con ella.  
  
Todos los valores necesarios (número de grupos, número de datos de cada grupo y los valores de cada grupo) se introducen en una sola línea.  
  
Por ejemplo, una línea de entrada podría ser la siguiente:  
```3 2 3.1 0.4 5 1.0 1.0 1.0 1.0 1.0 2 5.2 4.7```  
  
Se puede observar que se distinguen tres grupos de datos (lo indica el primer número ```int``` de la línea). Cada grupo empieza por un valor ```int``` que indica el número de elementos que lo componen (en el ejemplo, los grupos tienen dos, cinco y dos elementos, respectivamente). A continuación de este valor se encentran tantos valores ```double``` como indique el valor entero que encabeza cada grupo. Escribir un programa que escriba en ```cout``` la suma de los valores de cada grupo.  
  
En el ejemplo, el primer grupo contendrá los valores ```3.1``` y ```0.4```, el segundo ```1.0, 1.0, 1.0, 1.0, 1.0``` y el tercero ```5.2``` y ```4.7```. El programa debería escribir:  
```3.5, 5.0, 9.9```  
  
Implementar la clase ```TablaDentadaReales``` con una matriz de datos ```double```.  

## 2. SumaFilasTablaDentadaSecuencia.cpp
Reescriba la solución del ejercicio superior (```SumaFilasTablaDentada.cpp```) usando ahora un array de una nueva clase ```SecuenciaReales``` en la implementación de la clase ```TablaDentadaReales```.  

## 3. TablaDentadaATablaRectangular.cpp
Escriba un método de la clase ```TablaDentadaReales``` que devuelva un objeto ```TablaRectangularReales```. Ambas implementadas con una matriz de enteros.  

## 4. TablaDentadaATablaRectangular.cpp
Repita el ejercicio superior (```TablaDentadaATablaRectangular.cpp```) usando ahora en la implementación de ambas clases un array de ```SecuenciaReales```.  

## 5. TextoFrasePalabra.cpp
Crea las clases ```Palabra```, ```Frase``` y ```Texto```, viendo una ```Palabra``` como una secuencia de caracteres, una ```Frase``` como una secuencia de palabras y un ```Texto``` como una secuencia de frases.  
  
Escriba un programa que lea una serie indeterminada de cadenas, almacenándolas en un objeto ```Texto```. El programa mostrará cuántas frases, palabras y caracteres componen el texto.  

## 6. TFPComprimir.cpp
Recupere las clases ```Palabra```, ```Frase``` y ```Texto``` del ejercicio superior (```5. TextoFrasePalabra.cpp```).  
  
Implemente en la clase ```Texto``` el método ```Comprime```, que elimina todas las líneas en blanco. Cuando haya dos o más línea en blanco seguidas, se eliminan de forma que sólo quede una.  

## 7. TFPReemplazar.cpp
Recupere las clases ```Palabra```, ```Frase``` y ```Texto``` del ejercicio (```5. TextoFrasePalabra.cpp```).  
  
Implemente en la clase ```Texto``` los métodos:  
  
```void Reemplazar(Palabra buscada, Palabra nueva, int linea)```  
Que sustituye todas las ocurrencias de la palabra ```buscada``` por la palabra ```nueva``` en la línea número ```linea```. Las dos palabras deben ser exactamente iguales.  
  
```void ReemplazarTodo(Palabra buscada, Palabra nueva)```  
Que sustituye todas las ocurrencias de la palabra ```buscada``` por la palabra ```nueva``` en todas las líneas del texto.  
