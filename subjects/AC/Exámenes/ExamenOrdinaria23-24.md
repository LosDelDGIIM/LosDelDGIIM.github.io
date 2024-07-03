# Arquitectura de Computadores. Examen Final del Bloque Práctico.

***

- **Asignatura:** Arquitectura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único (Modelo F).
- **Profesor:** Mancia Anguita López (El examen lo pone el departamento).
- **Descripción:** Examen Final del Bloque de Prácticas.
- **Fecha:** 21 de junio de 2024.
- **Duración:** 60 minutos.

***

### Ejercicio 1.
Indique qué reparto de iteraciones a hebras es correcto suponiendo **5** hebras y la cláusula `schedule(monotonic:static,2)`. 

- a) &nbsp; iter &nbsp;
    &nbsp;&nbsp;&nbsp; 0
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 4
    &nbsp;&nbsp;&nbsp; 5
    &nbsp;&nbsp;&nbsp; 6
    &nbsp;&nbsp;&nbsp; 7
    &nbsp;&nbsp;&nbsp; 8<br>
    &nbsp; &nbsp; &nbsp; hebra
    &nbsp; 0
    &nbsp;&nbsp;&nbsp; 0
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 0
- b) &nbsp; iter &nbsp;
    &nbsp;&nbsp;&nbsp; 0
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 4
    &nbsp;&nbsp;&nbsp; 5
    &nbsp;&nbsp;&nbsp; 6
    &nbsp;&nbsp;&nbsp; 7
    &nbsp;&nbsp;&nbsp; 8<br>
    &nbsp; &nbsp; &nbsp; hebra
    &nbsp; 0
    &nbsp;&nbsp;&nbsp; 0
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 4
- c) &nbsp; iter &nbsp;
    &nbsp;&nbsp;&nbsp; 0
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 4
    &nbsp;&nbsp;&nbsp; 5
    &nbsp;&nbsp;&nbsp; 6
    &nbsp;&nbsp;&nbsp; 7
    &nbsp;&nbsp;&nbsp; 8<br>
    &nbsp; &nbsp; &nbsp; hebra
    &nbsp; 0
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 4
    &nbsp;&nbsp;&nbsp; 0
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 3
- d) &nbsp; iter &nbsp;
    &nbsp;&nbsp;&nbsp; 0
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 4
    &nbsp;&nbsp;&nbsp; 5
    &nbsp;&nbsp;&nbsp; 6
    &nbsp;&nbsp;&nbsp; 7
    &nbsp;&nbsp;&nbsp; 8<br>
    &nbsp; &nbsp; &nbsp; hebra
    &nbsp; 4
    &nbsp;&nbsp;&nbsp; 4
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 3
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 2
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 1
    &nbsp;&nbsp;&nbsp; 1

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'b':
  Hay 5 hebras y la planificación 'static' reparte las iteraciones en bloques de tamaño 'chunk' en round-robin, por lo que se no puede ser la 'a' (ya que se salta la hebra 4 en la distribución round-robin), ni la 'c' (ya que el chunk es de tamaño 2), ni la 'd' (ya que no se empieza a repartir en la hebra 0 y tampoco sigue round-robin).
    .</p>
</details>

### Ejercicio 2.
¿Qué devuelve la función `omp_get_wtime()` de OpenMP?

- a) El tiempo transcurrido del reloj en segundos.
- b) Tiempo transcurrido en segundos desde la anterior llamada a la misma función.
- c) La marca de tiempo (timestamp) del instante en que se llama a la función.
- d) Ninguna otra respuesta es correcta.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'c'.
    </p>
</details>

### Ejercicio 3.
Dada la siguiente sección de código:
```c
int i,j;
double **M, *v1, *v2;
// Inicializaciones M y v1 ...
#pragma omp parallel private(j)
for(i=0; i < N; i++)
{
    #pragma omp for
    for (j=0; j < N; j++)
        #pragma omp atomic
            v2[i] += M[i][j] * v1[j];
}
```
Suponiendo que todas las posiciones de `M` y `v1` se inicializan a 1, responda dos cuestiones: la primera es si este código paralelo es eficiente y la segunda qué contendrá el vector `v2` al terminar la ejecución.

- a) El código es **eficiente** y el vector `v2` contiene el resultado **correcto** de multiplicar la matriz `M` (NxN) por el vector `v1` (Nx1).
- b) El código es **no es eficiente** y el vector `v2` contiene el resultado **correcto** de multiplicar la matriz `M` (NxN) por el vector `v1` (Nx1).
- c) El código es **eficiente** y el vector `v2` contiene un resultado **indefinido**.
- d) El código es **no es eficiente** y el vector `v2` contiene un resultado **indefinido**.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'd':  
    Al tener la directiva '#pragma omp atomic' solo puede entrar una hebra a esa sección de código cada vez por lo que no es eficiente. Además la variable 'i' es compartida por todas las hebras por lo que se pueden producir condiciones de carrera y el resultado será indefinido.</p>
</details>

### Ejercicio 4.

Dado el siguiente código, ¿qué habría que cambiar para que el acceso a los elementos del struct `d` se realizara de manera óptima?
```c
struct position {
    int x;
    int y;
};

struct data {
    int acceleration [1000];
    int velocity [1000];
    position pos[500];
} d;

...

for (i=0; i<1000; ++i){
    d.velocity[i] = get_velocity();
    d.acceleration[i] = get_acceleration();
    d.pos[i].x = get_x();
    d.pos[i].y = get_y();
}
```

- a) Se deberían crear 4 bucles, uno por cada elemento al que se está accediendo.
- b) El acceso a los arrays `velocity` y `acceleration` se debería hacer en dos bucles diferentes.
- c) Se deberían crear tres bucles: uno para acceder al array `acceleration`, otro para el array `velocity` y otro para el array de structs `position`.
- d) el acceso a los elementos `x` e `y` del struct `position` debería hacerse en un bucle diferente.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'c'.
  Dado que los arrays 'acceleration' y 'velocity' están en bloques contiguos de memoria (los arrays completos de forma concurrente respectivamente), lo mejor será tener un bucle distinto para cada uno para aprovechar la localidad. El array 'position' sin embargo no tiene contiguas todas las 'x' primero y luego todas las 'y' sino que están intercaladas (ya que el struct 'position' así lo determina), por lo que lo mejor será utilizar un único bucle para la misma posición ('d.pos[i]') y rellenar en este bucle ambas componentes </p>
</details>

### Ejercicio 5.
Dado el siguiente código, ¿qué pasaría si `n` tuvuese un valor **menor** al de la variable **n_threads**?
```c
float sumalocal=0;
int n_threads = omp_get_max_threads();

#pragma omp parallel firstprivate(sumalocal) if (n<n_threads) num_threads(8)
{
    #pragma omp for schedule(static)
        for (i=0; i<64; i++)
            sumalocal += v[i];
    
    #pragma atomic
        suma += sumalocal;
}
```

- a) Ninguna de las anteriores
- b) Habría un error de compilación ya que hay que especificar el número de hebras de la región paralela.
- c) La región paralela se ejecutaría creando 8 hebras.
- d) La región paralela se ejecutaría creando tantas hebras como valor tenga `n`.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'c':  
    El condicional 'if (n&lt;n_threads)' se verifica y por tanto se ejecuta el código de forma paralela. Sin embargo, un apunte de esta respuesta es que no se crean 8 hebras sino 7 (ya que la hebra 'main' o 0 ya estaba creada). (En el examen esto se consideró un error de la respuesta pero se siguió considerando correcta).</p>
</details>

### Ejercicio 6.
A continuación se muestra el código del programa hebras.c. ¿Cuál de las siguientes afirmaciones es **verdadera**?
```c
#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_num_threads() 1
    #degine omp_set_num_threads(n_threads) 3
#endif

void main()
{
    int n_threads = 3;
    omp_set_num_threads(n_threads);
    #pragma omp parallel
        #pragma omp single
            printf("%d hebra/s", omp_get_num_threads());
}
```
- a) Ninguna respuesta es la correcta
- b) Tras el compilado `gcc hebras.c -o hebras`, no sale nada porque la directiva `single` es como si no existiera.
- c) Tras el compilado `gcc hebras.c -o hebras`, la salida al ejecutar el programa es "3 hebra/s".
- d) Tras el compilado `gcc -fopenmp hebras.c -o hebras`, la salida al ejecutar el programa es "3 hebra/s".

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'd':  
    La opción 'b' no puede ser ya que al no haber especificado '-fopenmp' en la compilación se ignoran las directivas de OpenMP y se toman las definiciones alternativas dadas en la cabecera por lo que sí habrá salida (aunque no paralelismo). La opción 'c' tampoco puede ser ya que la definición alternativa de la función 'omp_get_num_threads()' es que devuelva uno por lo que la salida sería "1 hebra/s". Finalmente la opción 'd' sí ejecuta el código de forma paralela con 3 hebras por lo que la salida será "3 hebra/s" (asi que tampoco es la 'a'). </p>
</details>

### Ejercicio 7.
¿Cuángo valdrá `n` al terminar la región paralela?
```c
int n = 2;
#pragma omp parallel for reduction(*n)
for(int i = 1; i < 4; i++)
    n *= i;
```

- a) 12
- b) 6
- c) 2
- d) 4

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'a':  
    Recordemos que la cláusula 'reduction(*n)' inicializa 'n' a 1 en cada hebra y multiplica el resultado final de 'n' de cada hebra y ese resultado lo multiplica también por el valor inicial de 'n' (que es 2). El bucle va de 1 a 3 por lo que la operación será: 1 x 2 x 3 x 2 = 12</p>
</details>

### Ejercicio 8.
En el código adjunto el valor de `Xinit` puede no estar correctamente disponible para otras hebras. ¿Qué directiva añadiría para que funcionase correctamente?
```c
int Xinit, Xlocal;
#pragma omp parallel private (Xlocal)
{
    #pragma omp master
    {
        Xinit=10;
    }
    Xlocal=Xinit;
}
```
- a) No insertaría nada, el código funciona bien siempre.
- b) Añadiría la directiva `#pragma omp barrier` antes de la línea 8.
- c) Añadiría la directiva `#pragma omp barrier` después de la línea 8.
- d) Añadiría la directiva `#pragma omp single` después de la línea 8.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'b':  
    El problema que presenta el código es que alguna hebra puede llegar a la asignación 'Xlocal=Xinit' antes de que la hebra master inicialice 'Xinit' a 10. Por tanto al poner una barrera antes de la asignación que comentábamos obligamos a que 'master' haya terminado la inicialización evitando la condición de carrera.</p>
</details>

### Ejercicio 9.
Dada la siguiente multiplicación de matrices, ¿Cuál sería el orden correcto de los bucles para mejorar la localidad de los accesos?
```c
for(i=0; i<100; ++i)
    for(j=0; j<100; ++j)
        for(k=0; k<100; ++k)
            a[i][j] += b[i][k] * c[k][j];
```

- a) No hace falta permutar ningún bucle. Tal y como está se accede de la forma más óptima posible.
- b) i, k, j.
- c) k, j, i.
- d) k, i, j.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'b':
    Recordemos que, por cómo se almacenan los arrays en memoria, las filas de las matrices (el primer índice que se especifica en los accesos) están en posiciones concurrentes en memoria. Es por esto que se prioriza fijar este primer índice y desplazar el segundo para explotar la localidad. En este caso, la sentencia 'a[ <strong>i</strong> ][ j ] += b[ <strong>i</strong> ][ k ] * c[ <strong>k</strong> ][ j ];' tiene en los primeros índices las variables 'i', 'i' y 'k' respectivamente (marcados en negrita). Por ello el orden será i, k, j. ('i' aparece 2 veces como primer índice, 'k' una vez y 'j' ninguna).</p>
</details>

### Ejercicio 10.
¿A cuál de las siguientes variables no se le puede asignar su valor en tiempo de compilación debido a la ambigüedad de código?
```c
float r, c;
float pi = 3.1416;
void circunferencia(float *v) {
    r = 3.0;
    *v = 15;
    c = 2 * pi * r;
}
```
- a) c=18.8496 (resultado de 2\*3.1416\*3)
- b) pi=3.1416
- c) r=3.0
- d) Ninguna de las variables puede ser asignada.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'a':  
    El compilador puede asignar todas las variables excepto la 'c' ya que '*v' es un puntero y podría apuntar a 'r' o a 'pi' modificando su valor y por tanto el resultado de la operación 2*pi*r.</p>
</details>

### Ejercicio 11.
Supongamos el siguiente bucle que debe ser desenrollado para optimizar el código. Se sabe que `N` es múltiplo de 4. Indique cuántos saltos contendrá el código desenrollado si el contador del bucle queremos que se incremente de 2 en 2 en la mayor parte del bucle. Considere `a`, `b` y `c` vectores ya incializados con valores reales.
```c
for(int i = 0; i<N/2; i++)
    a[i] += b[i] * c[i];
```
- a) (N/2)-1
- b) N/2
- c) (N/4)-1
- d) N/4

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'c':  
    Al incrementar de 2 en 2 en índice 'i' se reducirán a la mitad las iteraciones, por lo que ahora serán N/4. Además, en la implementación del bucle 'for' se salta en todas las iteraciones excepto en la última (si está implementado con salto hacia atrás) o en la primera (si está implementado con salto hacia adelante). En cualquier caso, el número de saltos será el número de iteraciones menos uno, es decir, (N/4) - 1.</p>
</details>

### Ejercicio 12.
¿Cuántos **cores físicos** tienes un **único zócalo** de CPU (socket) en **un único equipo de la partición ac** (la formada por tres equipos: atcgrid[1-3]).
- a) 2.
- b) 8.
- c) 6.
- d) 36.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'c'. (Aparece en los <a href="https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/AC/Pr%C3%A1cticas/Bloque%200/Resumen.md#atcgrid1-3">resúmenes</a>)</p>
</details>

### Ejercicio 13.
Indique cuál de las siguientes afirmaciones sobre el **chunk** utilizado con la cláusula `schedule` es cierta:
- a) Sólo se puede fijar su valor a través de las variables de entorno.
- b) Indica la granularidad de la distribución de las iteraciones.
- c) Su valor por defecto cuando se utiliza con `dynamic` es 2.
- d) Únicamente se puede utilizar para las formas de asignación de `static` y `dynamic`

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'b':
    La opción 'a' no puede ser ya que se puede especificar también con cláusulas. La opción 'c' tampoco porque por defecto con 'dynamic' vale 1. Tampoco puede ser la 'd' porque se puede utilizar también para 'guided'. Por último la opción 'b' da una descripción bastante acertada.</p>
</details>

### Ejercicio 14.
¿Qué valores imprimiría el siguiente código tanto dentro como fuera del bloque estructurado si previamente se ha modificado la variable de entorno como `export OMP_NUM_THREADS=4`?
```c
#pragma omp parallel num_threads(3)
{
    #pragma omp single
    printf("DENTRO: %d\n", omp_get_max_threads());
}
printf("FUERA: %d\n", omp_get_max_threads());
```

- a) "DENTRO: 3" y "FUERA: 1".
- b) "DENTRO: 4" y "FUERA: 1".
- c) "DENTRO: 4" y "FUERA: 4".
- d) "DENTRO: 1" y "FUERA: 1".

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'c'.
    </p>
</details>

### Ejercicio 15.
Teniendo en cuenta las líneas de caché, ¿qué afirmación es correcta sobre la velocidad de acceso a un dato almacenado en memoria?

- a) Disminuye la velocidad de acceso cuando está repartido entre varias líneas.
- b) Disminuye la velocidad de acceso cuando está contenido al final de una línea.
- c) Aumenta la velocidad de acceso cuando está repartido entre varias líneas.
- d) Disminuye la velocidad de acceso cuando está contenido al principio de una línea.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'a':  
    Por el funcionamiento de la caché las líneas se tienen que cargar una a una por lo que si está en varias habrá que cargar todas y se tardará más. La opción 'b' no puede ser porque como se cargan líneas enteras da igual la posición que ocupe dentro de la línea el dato a leer. La 'c' es lo opuesto a la 'a' por lo que tampoco es y la 'd' no puede ser por el mismo motivo que no podía ser la 'b'.</p>
</details>

### Ejercicio 16.
¿Qué ocurre si llegan 4 hebras a una directiva `sections` que contiene solo 2 secciones de código diferentes (`section`)?

- a) Cada sección es ejecutada por 2 hebras pero no a la vez. 
- b) Cada sección es ejecutada por las 4 hebras.
- c) Cada sección es ejecutada por 2 hebras a la vez.
- d) Cada sección es ejecutada por solo una de las hebras.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'd'.</p>
</details>

### Ejercicio 17.
Indique cuales son los principales componentes del lenguaje OpenMP.

- a) Funciones, directivas y variables de entorno.
- b) Directivas, variables compartidas y barreras.
- c) Ninguna otra respuesta es correcta.
- d) Variables de entorno, funciones e instrucciones al compilador.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'a'.(Aparece en los <a href="https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/AC/Pr%C3%A1cticas/Bloque%201/Resumen.md#openmp">resúmenes</a>)</p>
</details>

### Ejercicio 18.
Indique cuantas veces aparecerá el mensaje "Hola mundo X" en el código siguiente al compilar con la orden `gcc -fopenmp ejemplo.c -o ejemplo`. Teniendo en cuenta que "X" representará un número entero cualquiera y se ejecuta con 8 hebras.
```c
#include "stdio.h"
#include "omp.h"
void main()
{
    int i=0; n=100;
    #pragma omp parallel
    {
        #pragma omp single
        printf("Hola mundo %d\n", i++);
        #pragma omp for
        for(i=0; i<n; i++){
            printf("Hola mundo %d", i);
        }
    }
}
```

- a) 18 veces.
- b) 11 veces.
- c) 108 veces.
- d) 101 veces.


<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'd':  
    Aunque se creen 8 hebras, la región bajo la directiva 'single' solo la ejecuta una hebra. Después el bucle hace las 100 iteraciones (independientemente de qué hebra ejecute qué iteraciones). Por tanto 100 + 1 = 101</p>
</details>

### Ejercicio 19.
¿Qué afirmación sobre las cláusulas es correcta?

- a) Por defecto, si no utilizamos cláusulas, las variables declaradas fuera de una región paralela son compartidas por las hebras de la región.
- b) Todas las directivas aceptan algún tipo de cláusula.
- c) La cláusula `shared` puede ser utilizada con la directiva `single`.
- d) OpenMP obliga a la utilización de al menos una cláusula con la directiva `parallel`.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'a'.</p>
</details>

### Ejercicio 20.
Dado el siguiente fragmento de código:
```c
int i=0, a=5;
#pragma omp parallel for firstprivate(a)
for(i=0; i < 5; i++)
{
    a += i;
}
```

¿Cuál sería el valor de la variable `a` inicial de cada hebra al comenzar la región paralela y el valor de `a` justo después de la región paralela?

- a) 5 al comienzo de las hebras e indefinido después de la región paralela.
- b) 5 al comienzo de las hebras y 15 después de la región paralela.
- c) Indefinido tanto al comienzo de las hebras como fuera de la región paralela.
- d) 5 al comienzo de las hebras y 5 después de la región paralela.

<details>
  <summary>Respuesta</summary>
  <p>La respuesta correcta es la opción 'd':  
    Gracias a la cláusula 'firstprivate' se produce una difusión del valor de 'a' a cada hebra y por tanto tienen un valor inicial 'a=5'. Además, como no se ha especificado ninguna cláusula que actualice el valor de 'a' fuera de la región paralela (como 'reduction'), fuera de la región paralela mantiene el valor inicial, 5..</p>
</details>