# Sistemas Concurrentes y Distribuidos. Seminario 1 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen del Seminario 1 de Prácticas.

En este seminario aprenderemos a manejar hebras nativas de C++11, así como ver las principales clases para manejarlas y sincronizarlas.  
Este seminario nos servirá para las prácticas P1 y P2.

# 1. Definiciones

La teoría de procesos y hebras se vió ya en la asignatura de Sistemas Operativos. Por tanto, aquí sólo destacamos lo siguiente:  
Los procesos son devoradores de memoria y son pesados al cambiar de contexto, por lo que se crearon las hebras, flujos de control que trabajan de forma concurrente y comparten zona de memoria del proceso, como el código y variables.  
Las hebras sólo necesitan una pila, pc y sp. Es una entidad ligera en cuanto al uso de recursos.

# 2. Hebras en C++11

Usaremos C++11 porque introduce funcionalidad para gestión de hebras, como tipos de datos, clases y funciones.  
  
En esta sección, veremos:
- Cómo crear y finalizar hebras.
- Sincronizarlas mediante uniones.
- Paso de parámetros a hebras y obtención de resultados.
- Cómo crear vectores de hebras y futuros.
- Medición de tiempos.
  
En los programas que usan hebras, será necesario incluir la librería `thread`.  
Para compilar los programas que usan hebras, usaremos:
```bash
g++ -std=c++11 -pthread -o [ejecutable] [fichero].cpp
```
Donde `ejecutable` es el nombre que queremos dar al binario ejecutable y `fichero` es nuestro código C++.

***
## Creación de hebras

La clase `thread` de la `std` nos permite crear objetos de tipo hebra.  
Estas hebras ejecutarán una función que le asignaremos y tras el fín de esta función, terminarán.  
Podemos declarar hebras para luego lanzarlas:
```c++
thread hebra1, hebra2;

// ...

hebra1 = thread(funcion1);  // Se lanza la hebra1
hebra2 = thread(funcion2);  // Se lanza la hebra2
```
O declaralas y lanzarlas a la vez:
```c++
thread hebra1(funcion1), 
       hebra2(funcion2);
```
Estos usos de la clase `thread` son equivalentes al que obtendríamos con la función `fork` del sistema operativo.  
  
Si la función que le pasamos a la hebra recibe $n$ argumentos, se los especificaremos después del nombre de la función:
```c++
thread hebra(funcion, arg1, arg2, ..., argn)
```

#### Ejemplo
Si ejecutamos el siguiente código:
```c++
#include <iostream>
#include <thread>     
using namespace std ; 

void funcion_hebra_1(  )
{ for( unsigned long i = 0 ; i < 5000 ; i++ )
     cout << "hebra 1, i == " << i << endl << flush ;
}
void funcion_hebra_2(  )
{  for( unsigned long i = 0 ; i < 5000 ; i++ )
      cout << "                hebra 2, i == " << i << endl << flush ;
}
int main()
{
  thread hebra1( funcion_hebra_1 ), 
         hebra2( funcion_hebra_2 ); 
         
  return 0;
}
```
Se crean 3 hebras para su ejecución: la principal, la `hebra1` y la `hebra2`.  
Sin embargo, este código no hace lo que esperamos, ya que la hebra principal no espera a que las hebras terminen, sino que finaliza el programa.  
Para que el programa funcione como esperamos, será necesario que la hebra principal espere al resto de hebras antes de finalizar (veremos cómo hacerlo más adelante).  

***
## Finalización de hebras

Las hebras pueden terminar cuando se da alguna de estas condiciones:
- Cuando ejecutan un `return` dentro de su función.
- Cuando se lanza una excepción.
- Cuando se elimina el objeto `thread` asociado a la hebra.
- Cuando cualquier hebra llega a una función `exit`, `abort` o `terminate`.
- Cuando finaliza la hebra principal.

***
## Sincronizar hebras

Para hacer que una hebra espere hasta que termine otra, tenemos disponible el método `join` de la clase `thread`.  
Al igual que se explicó en teoría, cuando una hebra ejecuta `join` sobre otra:
- Si la hebra sobre la que se ejecuta ha terminado, la hebra continúa con la ejecución de la siguiente instrucción.
- Si la hebra sobre la que se ejecuta no ha terminado, la hebra espera a que dicha hebra termine.

#### Ejemplo
En el siguiente ejemplo, vemos un uso de la función `join`, recuperando el ejemplo anterior
```c++
#include <iostream>
#include <thread>     
using namespace std ; 

void funcion_hebra_1(  )
{ for( unsigned long i = 0 ; i < 5000 ; i++ )
     cout << "hebra 1, i == " << i << endl << flush ;
}
void funcion_hebra_2(  )
{  for( unsigned long i = 0 ; i < 5000 ; i++ )
      cout << "                hebra 2, i == " << i << endl << flush ;
}
int main()
{
  thread hebra1( funcion_hebra_1 ), 
         hebra2( funcion_hebra_2 ); 
         
  hebra1.join();  // La hebra principal espera hasta que termine hebra1
  hebra2.join();  // La hebra principal espera hasta que termine hebra2
         
  return 0;
}
```

***
## Obtención de valores resultados

Sabemos ya cómo hacer que una hebra ejecute una función, pero hasta ahora no sabemos cómo recuperar el valor resultado de dicha función (en caso de no ser una función `void`).  
Disponemos de distintos métodos para obtener el resultado:

### Usar una variable global compartida
Podemos usar una variable global compartida para que, al final de la función ejecutada, la hebra correspondiente guarde el valor resultado en dicha variable compartida, para que posteriormente la hebra que lanzó esta hebra lo use:
```c++
#include <iostream>
#include <thread>

int resultado_hebra;

void funcion_hebra(int param){
    // ...
    resultado_hebra = resultado;
}

int main(){
    thread hebra(funcion_hebra, param);
    hebra.join();
    
    cout << resultado_hebra << endl;
}
```
Aunque funciona el código, se trata de un mecanismo **inseguro**, cualquier hebra puede modificar el valor de la variable `resultado_hebra` y no tenemos ningún mecanismo para hacer que sólo la hebra correspondiente pueda escribir en la variable y la hebra que obtiene el resultado pueda leerla.

### Usar un parámetro de salida
En vez de usar una variable global, podemos en su lugar hacer uso de un parámetro de la función como si fuera un parámetro de salida:
```c++
#include <iostream>
#include <thread>

void funcion_hebra(int param, int& resultado_hebra){
    // ...
    resultado_hebra = resultado;
}

int main(){
    thread hebra(funcion_hebra, param, ref(resultado_hebra));
    hebra.join();
    
    cout << resultado_hebra << endl;
}
```
**Nota:** Notemos que para pasar una referencia a una función, necesitamos usar el operador `ref`, para crear una copia del objeto.  
Aunque este método parece menos inseguro que el anterior, sigue siendo **inseguro**, ya que cualquier hebra que se lance tras la declaración de la variable `resultado_hebra`, podrá usar dicha variable, puediendo modificar su contenido.

### Uso de futuros
Hace falta incluir la librería `future`.  
  
Un futuro es una clase de tipo genérico (depende del tipo de variable que se espera como resultado de la función) que nos permite otra forma de lanzar hebras a ejecución.  
Cada futuro se asocia con una hebra anónima que ejecuta la función especificada. Lo único que podemos consultar de dicha hebra es el valor resultado que obtenemos tras ejecutar la función.  
Para lanzar un futuro, usamos la función `async`, cuyo primer parámetro es el modo de lanzamiento, en el que típicamente escribiremos como parámetro `launch::async`. El resto de parámetros de la función se asemejan a los de `thread`.  
Para lanzar un futuro, usamos:
```c++
future<[tipo]> futuro = async(launch::async, funcion, param);
```
Para recuperar el valor de la función que ha ejecutado el futuro, usaremos el método `get` sobre el futuro, que implica un `join` implícito (es decir, primero se espera a que termine la ejecución de la hebra anónima asociada al futuro y posteriormente se salva el valor resultado de la función).  
  
Observamos el uso de un futuro en el ejemplo que venimos manejando hasta ahora:
```c++
#include <iostream>
#include <future>

int funcion_hebra(int param){
    // ...
    return resultado;
}

int main(){
    future<int> futuro = async(launch::async, funcion_hebra, param);
    
    cout << futuro.get() << endl;
}
```
Es el método más seguro para recuperar parámetros de una función.  
  
Los futuros son similares a las *promesas*, usadas en otros ámbitos como la programación web.

***
## Vectores de hebras y futuros

Para crear vectores de hebras y futuros, será común hacer:
```c++
const int num_hebras = x;
thread hebras[num_hebras];

// Lanzar las hebras
for(int i = 0; i < num_hebras; i++)
    hebras[i] = thread(funcion, i);
    
// Esperar a todas las hebras
for(int i = 0; i < num_hebras; i++)
    hebras[i].join();
```
Y con futuros:
```c++
const int num_futuros = x;
future<dato> futuros[num_futuros];

// Lanzar los futuros
for(int i = 0; i < num_futuros; i++)
    futuros[i] = async(launch::aync, funcion, i);
    
// Esperar a todos los futuros
for(int i = 0; i < num_futuros; i++)
    futuros[i].join();
```

***
## Medición de tiempos

Para medir tiempos en nuestro programs, usaremos la librería `chrono`. Para mayor comodidad, se recomienda incluir `using namespace std::chrono`.  
  
Dentro de esta librería contamos con dos tipos de datos:
- Instantes (`time_point`): representan un instante concreto.
- Duraciones (`duration`): representan diferencias de instantes. Es un tipo genérico, que se instancia con un tipo de dato donde guardar la duración y con una unidad de tiempo (segundos, milisegundos, microsegundos, ...).
  
Existen 3 clases que nos proporcionan de distintos relojes:
- Reloj de sistema: `system_clock`, indicado por la fecha/hora del sistema. Se puede cambiar el instante al cambiar fecha y hora, pudiendo resultar en duraciones negativas.
- Reloj monotónico: `steady_clock`, que siempre toma tiempos hacia adelante.
- Reloj de alta precisión: `high_precision_clock`, reloj de máxima precisión. Dependiendo del SO, se implementa mediante `system_clock` o `steady_clock`.  
  
Usaremos `steady_clock`, por ser monotónico (que siempre va hacia adelante).  
  
Un ejemplo de una medición de tiempo es:
```c++
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(){
    time_point<steady_clock> instante_inicial = steady_clock::now();
    
    // ...
    
    time_point<steady_clock> instante_final = steady_clock::now();
    
    // Obtener la duración en microsegundos
    duration<float, micro> duracion = instante_final - instante_inicial;
    
    // Consultar la duracion
    cout << "tiempo de ejecucion: " << duracion.count() << " microsegundos." << endl;
}
```
# 3. Sincronización básica

Aprenderemos ahora el uso de dos clases de `C++11` que nos permiten garantizar la exclusión mutua en regiones críticas (vea en los apuntes de teoría qué es la exclusión mutua).  
  
Disponemos de dos clases que nos permiten esta funcionalidad:

## Tipos atómicos
(Incluir la librería `<atomic>`)  
Se trata de un tipo de dato genérico, `atomic<T>` que nos permite crear variables que tienen protegidas operaciones pequeñas, para que estas se hagan de forma atómica.  
  
Si `expr` es un literal simple (no una variable) y `k` es una variable de tipo `atomic<T>>`, podremos hacer las operaciones:  
`k = expr`, `k++`, `k--`, `k += expr` y `k -= expr`  
de forma atómica.  
  
Este tipo de dato aprovecha instrucciones máquina que permiten dichos funcionamientos.

## Objetos mutex
Los objetos `mutex` son una implementación de los cerrojos en `C++11`. Con ellos podemos tener en nuestro códigos secciones críticas más complicadas de las que nos permiten los tipos atómicos.  
  
Para usar un objeto `mutex`, lo declaramos (no hace falta pasar ningún valor) y posteriormente, podremos usar sobre él dos métodos: `lock` y `unlock`. El lector debería estar familiarizado con los cerrojos y dichos métodos (si no, consultar los apuntes de Arquitectura de Computadores).  
```c++
mutex cerrojo;

cerrojo.lock();
// Sección crítica
cerrojo.unlock();
```
  
A tener en cuenta:
- Por cada sección crítica que tengamos, hace falta tener una variable `mutex` distinta.  
- La espera de la función `lock` se trata de una espera ocupada.
- Los tiempos obtenidos con `mutex` son mucho más superiores para los obtenidos con tipos atómicos en un mismo código.  
  
Por tanto, cuando queramos hacer operaciones sencillas, usaremos tipos atómicos y cuando queramos hacer cosas más complejas, usaremos objetos `mutex`.

# 4. Introducción a los semáforos
Los semáforos son una herramienta usada en programación concurrente con un nivel de abstracción superior al de los cerrojos, aunque encontramos a los monitores (se verán en el siguiente seminario), con un nivel de abstracción mayor.  
  
Los semáforos no utilizan espera ocupada como los cerrojos, sino que directamente bloquean los procesos que se encuentran en espera.  
Resuelven fácilmente la exclusión mutua, así como **cualquier** problema de sincronización. Sin embargo, hay problemas de sincronización que son difíciles de resolver con semáforos. Para ello, tenemos a los monitores.  
  
Los semáforos se implementan mediante una estructura de datos accesible únicamente mediante subprogramas específicos, lo que aumenta la seguridad.  
Un semáforo almacena un conjunto de procesos bloqueados (que empieza inicialmente vacío) y un valor entero no negativo.  
  
Debemos pensar en los semáforos como en una generalización de los cerrojos. Ahora, en vez de tener un sólo proceso en la región que envuelve el cerrojo, podremos tener tantos como queramos.
  
## Funciones
Existen dos funciones relativas a los semáforos, `sem_wait` y `sem_signal`, cuyo código podemos ver a continuación:

```c++
sem_wait(s){
    if(s.valor == 0)
        // Bloquea el proceso
    
    s.valor -= 1;
}

sem_signal(s){
    s.valor += 1;
    if(/*Hay procesos esperando*/)
        // Reanuda un proceso
}
```
El semáforo se iniciará en un valor determinado, entendiendo el valor `0` como que ningún proceso más puede pasar el semáforo (intuitivamente, el semáforo está en rojo).  
  
Cada vez que un proceso quiera pasar un semáforo, usaremos la función `sem_wait`, para que compruebe si el semáforo es mayor que 0 y, en cuyo caso, se meta el proceso y decremente el valor del semáforo.  
Cuando un proceso salga de la zona del semáforo, usaremos la función `sem_signal`, para incrementar el valor del semáforo, dejando pasar a otro proceso en caso de haber procesos esperando.
  
Por la forma en la que están programadas las funciones `sem_wait` y `sem_signal`, el valor del semáforo nunca será negativo.

## Ejemplos de uso de semáforos
### Espera única
Tenemos un proceso $P$ que espera la finalización de una operación de un proceso $Q$:
```pascal
process P;
begin
    {Funcionalidad 1}
end
```

```pascal
process Q;
begin
    {Funcionalidad 2}
end
```
***
Queremos que `Funcionalidad 1` suceda antes que `Funcionalidad 2`.  
  
Para ello, haremos uso de un semáforo, de la siguiente forma:
```pascal
{Variable que comparten P y Q}
var s : semaphore := 0;
```

```pascal
process P;
begin
    {Funcionalidad 1}
    sem_signal(s);  {Pone semáforo a 1}
end
```

```pascal
process Q;
begin
    sem_wait(s);    {Espera a que suceda Funcionalidad 1}
    {Funcionalidad 2}
end
```

### Exclusión mutua
En este caso, tenemos una sección crítica que queremos que se ejecute en exclusión mutua:
```pascal
process Procesos[i : 0..n-1];
begin
    while true do begin
        {Sección crítica}
    end
end
```
***
Lo solucionamos con un semáforo, esta vez en la misma región de código:
```pascal
var s : semaphore := 1;

process Procesos[i : 0..n-1];
begin
    while true do begin
        sem_wait(s) 
        {Sección crítica}
        sem_signal(s)
    end
end
```
Acabamos de simular el funcionamiento de un cerrojo con un semáforo.  
Aunque hemos solucionado el problema con un semáforo, se recomienda resolverlo con cerrojos, por ser más eficiente.

### Productor/Consumidor
Queremos ahora recrear el paradigma del productor/consumidr visto en teoría:
```pascal
var x : integer;
```
```pascal
process Productor; {calcula x}
var a : integer;
begin
    while true do begin
        a := ProducirValor();
        x := a;
    end
end
```
```pascal
process Consumidor; {lee x}
var b : integer;
begin
    while true do begin
        b := x;
        UsarValor(b);
    end
end
```
***
Para ello, usamos 2 semáforos:
```pascal
var x : integer;
    s1 : semaphore = 0;
    s2 : semaphore = 1;
```
```pascal
process Productor; {calcula x}
var a : integer;
begin
    while true do begin
        a := ProducirValor();
        sem_wait(s2)
        x := a;
        sem_signal(s1)
    end
end
```
```pascal
process Consumidor; {lee x}
var b : integer;
begin
    while true do begin
        sem_wait(s1)
        b := x;
        sem_signal(s2)
        UsarValor(b);
    end
end
```

# 5. Usos de semáforos en C++
En este caso, usaremos una clase `Semaphore` creada por los profesores de la asignatura, la cual puede encontrarse en los ficheros `scd.h` y `scd.cpp`. En los mismos, tenemos creadas las funciones `sem_wait` y `sem_signal`.  
Para usarlos, incluimos: `#include "scd.h"`, el espacio de nombres `using namespace scd;` y al compilar, incluir el fichero `scd.cpp`.
  
- La inicialización del valor de un semáforo debe hacerse obligatoriamente en su declaración.
- Las variables de tipo `Semaphore` pueden pasarse como parámetros, pero no se pueden copiar mediante asignaciones. Se destruyen automáticamente.  
  
Para usar semáforos:
```c++
Semaphore s1 = 1;
Semaphore s2(0);

sem_wait(s1);
sem_signal(s1);
```
  
Pueden declararse arrays y vectores de semáforos:
```c++
const int N = 3;
Semaphore s[N] = {1, 2, 3};
```

```c++
vector<Semaphore> s;
s.push_back(Semaphore(0));
```
