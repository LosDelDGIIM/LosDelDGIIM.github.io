# Fundamentos de Programación. Sesión XIII de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión XIII de prácticas.

## 1. Binario.cpp
Queremos disponer de una clase que nos permita trabajar con datos binarios (la clase ```Bin```) y realizar las operaciones básicas típicas sobre éstos.  
  
Vamos a restringir el tamaño a un máximo de ```32 bits``` y sólo consideraremos valores positivos. Así, podremos operar con valores (decimales) entre $0$ y $2^{32} -1 = 4294967295$.
Investigue y vea que el tipo ```unsigned int``` requiere 4 bytes (32 bits) para su almacenamiento y que el máximo valor que puede representarse es $4294967295$ (consulte ```UINT_MAX``` en ```climits```). Esto nos ayudará a adoptar un dato ```unsigned int``` como campo privado de la clase. Es económico (4 bytes para cada valor a representar) y disponemos de un amplio surtido de operaciones aritméticas que pueden realizarse con datos ```unsigned int```.  
  
La clase ```Bin``` responderá al siguiente esquema. Los métodos se comportan como se describe a continuación. Usted debe elegir las precondiciones para cada caso.
```cpp
class Bin{
    unsigned int valor_bin; // PRE: 0 <= valor_bin < 2^{32}-1
    
public:
    Bin();
    Bin(unsigned int valor);
    Bin(string valor);
    
    void SetValor(unsigned int valor);
    void SetValor(string valor);
    
    int MinNumBits();
    unsigned int GetValorDecimal();
    string ToString(int num_casillas);
    
    Bin Suma(Bin otro);
    Bin Resta(Bin otro);
    Bin AND(Bin otro);
    Bin OR(Bin otro);
    Bin DespDcha(int veces);
    Bin DespIzda(int veces);
    
private:
    string DecToBin(unsigned int num_decimal, int num_casillas);
    unsigned int BinToDec(string cad);
};
```

- Constructores:
  ```cpp
    Bin();
    Bin(unsigned int valor);
    Bin(string valor);
  ```
  Crean un objeto ```Bin``` y lo inicializan al valor dado. El constructor sin argumentos inicializa el objeto con valor 0.
- Métodos que modifican el objeto (setters):
  ```cpp
    void SetValor(unsigned int valor);
    void SetValor(string valor);
  ```
  Modifica el valor del dato binario sustituyéndolo por ```valor```.
- Métodos de consulta (getters):
  ```cpp
    int MinNumBits();
  ```
  Devuelve cuańtos bits se requieren para representar el valor.
  ```cpp
    unsigned int GetValorDecimal();
  ```
  Devuelve el valor decimal del dato binario.
  ```cpp
    string ToString(int num_casillas);
  ```
  Devuelve un tring con el valor binario. El valor binario ocupa ```num_casillas```. En el caso de no precisar tantas casillas, se rellenan con ceros a la izquierda. Si se necesitan más casillas se usan las que se requieran para no perder información. El valor binario obtenido siempre está delimitado por los caracteres '[' y ']'.
- Métodos de cálculo:
  ```cpp
    Bin Suma(Bin otro);
    Bin Resta(Bin otro);
    Bin AND(Bin otro);
    Bin OR(Bin otro);
  ```
  Realiza la operación indicada y devuelve un nuevo objeto con el resultado. Ni el objeto implícito ni ```otro``` se modifican.
- Métodos de desplazamiento de bits:
  ```cpp
    Bin DespDcha(int veces);
    Bin DespIzda(int veces);
  ```
  Realiza la operación indicada y devuelve un nuevo objeto on el resultado. Los huecos se rellenan con ceros. El objeto implícito no se modifica.
- Métodos privados:
  ```cpp
    string DecToBin(unsigned int num_decimal, int num_casillas);
    unsigned int BinToDec(string cad);
  ```
  Son las funciones desarrolladas en los ejercicios  ```9. DecToBin.cpp``` y ```10. BinToDec.cpp``` de la [Sesión VIII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2008/Sesi%C3%B3n%2008.md) de prácticas.  
  
Nota: ```valor_bin``` es el valor **en decimal** del número binario a representar. Los métodos de la clase harán parecer desde fuera que la clase almacena un dato binario pero no, ya que es más cómodo almacenar y trabajar sobre el decimal que sobre el binario.  
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2013/Binario.cpp)

## 2. MayorPalindromo.cpp
Este ejercicio trabaja sobre la clase ```SecuenciaCaracteres```. Puede encontrar su código en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/SecuenciaCaracteres.cpp).  
  
Un _palíndromo_ es una secuencia que se lee igual de izquierda a derecha que de derecha a izquierda.  
  
Se pide que define un método en la clase ```SecuenciaCaracteres``` que calcule y devuelva el palíndromo de mayor longitud contenido en una secuencia. Dicho palíndromo existe siempre y será un objeto de la clase ```SecuenciaCaracteres```.  
```cpp
SecuenciaCaracteres MayorPalindromoContenido();
```
  
Si hay varios con la misma longitud, tiene libertad para elegir cuál devolver.  
  
Por ejemplo, el mayor palíndromo en ```CABBADE``` es ```ABBA```.  
El mayor en ```ABCDEF``` es cualquier carácter, por ejemplo, ```A```.  
El mayor en ```ABBA``` es ```ABBA```.  
El mayor en ```gAAtySHHSvvABCCBAfh``` es ```ABCCBA```.  
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2013/MayorPalindromo.cpp)

## 3. Empleados.cpp 
Retomando la solución del ejercicio ```3. Empleados.cpp``` de la [Sesión XII](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2012/Sesi%C3%B3n%2012.md) de prácticas, cuyo enunciado recordamos:  
  
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
  
En este programa, deberá leer un archivo de ```Empleados``` (como siempre), meterlos en un array ordenarlos por salario, dejando comentado el código para su ordenación por fecha de nacimiento y nombre y apellidos. El cambio deberá realizarse con el menor esfuerzo posible.
  
Nota: recomendamos la ejecución del programa con redirección de datos de entrada. Le dejamos aquí el [fichero](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/Empleados.txt) listo con la entrada.  
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2013/Empleados.cpp)

## 4. SecuenciaEmpleados.cpp 
Reescriba la solución al ejercicio anterior (```3. Empleados.cpp```), cuyo enunciado le recordamos:  
  
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
  
En este programa, deberá leer un archivo de ```Empleados``` (como siempre), meterlos en un array ordenarlos por salario, dejando comentado el código para su ordenación por fecha de nacimiento y nombre y apellidos. El cambio deberá realizarse con el menor esfuerzo posible.
  
Nota: recomendamos la ejecución del programa con redirección de datos de entrada. Le dejamos aquí el [fichero](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2010/Empleados.txt) listo con la entrada.  
  
En esta ocasión, deberá crear una clase ```SecuenciaEmpleados``` que siga la misma lógica que las clases ```SecuenciaCaracteres``` o ```SecuenciaEnteros``` previamente vistas.  
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2013/SecuenciaEmpleados.cpp)

## 5. RectanguloCircunferencia.cpp
Reescriba la solución al ejercicio ```2. RectanguloCircunferencia.cpp``` de la [Sesión XI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2011/Sesi%C3%B3n%2011.md) de prácticas:  
  
Desarrolle un programa que pida al usuario un rectángulo y calcule la circunferencia centrada en el punto de corte de las diagonales del rectángulo de forma que su superficie sea la menor entre todas las circunferencias de mayor área que la del rectángulo.  
  
Para el cálculo de la circunferencia, comience con una circunferencia de radio ```0.5``` y vaya incrementando su valor en ```0.25``` hasta hallar la primera circunferencia de área mayor que el rectángulo.  
  
Ahora, deberá crear la clase:  
```Punto2D```  
Clase que representa un punto en el plano bidimensional.  
  
Deberá mantener las clases:  
```Circunferencia``` y ```Rectangulo``` con una leve modificación en la clase ```Rectangulo```:  
Ahora, guardará como datos miembro el vértice superior izquierdo y las longitudes de la base y de la altura.  
  
Finalmente, deberá crear la clase:  
```LectorPunto2D``` con la siguiente estructura:  
```cpp
class LectorPunto2D{
    string mensaje;
    
public:
    LectorPunto2D(string msg);
    
    void SetMensaje(string msg);
    void ImprimeMensaje();
    
    Punto2D Lee();
};
```
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2013/RectanguloCircunferencia.cpp)

## 6. ColeccionPuntos.cpp
Recuperando las clases ```Circunferencia```, ```Punto2D``` y ```LectorPunto2D``` del ejercicio superior (```5. RectanguloCircunferenia.cpp```), deberá implementar la clase:  
```ColeccionPuntos2D```, que se usará para almacenar y gestionar una colección de datos de tipo ```Punto2D```.  
  
Realice un progama que lea los datos necesarios para la creación de un objeto ```Circunferencia```. A continuación, lea un número indeterminado de objetos ```Punto2D```, almacenándolos en un objeto de tipo ```ColeccionPuntos2D```. La lectura finaliza cuando el usuario introduzca ```FIN``` como abscisa de un punto.  
  
Muestre cuáles son los puntos de la colección que están contenidos en la región limitada por la circunferencia.  
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2013/ColeccionPuntos.cpp)

## 7. CircunferenciasEnRectangulo.cpp
Recupere las clases ```Circunferencia```, ```Punto2D```, ```LectorPunto2D``` y ```Rectangulo``` del ejercicio ```5. RectanguloCircunferencia.cpp``` y reescriba la solución del ejercicio ```3. RectanguloCircunferenciasInscritas.cpp``` de la [Sesión XI](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2011/Sesi%C3%B3n%2011.md) de prácticas, cuyo enunciado recordamos a continuación:  
  
Escriba un programa que lea las coordenadas que definen un rectángulo y calcule y muestre una serie de datos de tipo ```Circunferencia```, todas centrada en en el punto de corte de las diagonales del rectángulo.  
  
Las circunferencias en las que estamos interesadas serán todas las circunferencias inscritas en el rectángulo. Para ello comience con una circunferencia de ```radio = 0.5``` y vaya incrementando su valor ```0.25``` en cada iteración.  
  
Muestre cuántas circunferencias inscritas se han generado.  
  
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2013/CircunferenciasEnRectangulo.cpp)

# Ejercicios Opcionales
## 1. 
