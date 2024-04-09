# Arquitectura de Computadores. Sesión I de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Arquitectura de Computadores.  
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen de la Sesión I de Prácticas.

# OpenMP
OpenMP (también llamada por Open Multi-Processing) es una API para `c`, `c++` y `Fortran` que nos permite convertir código secuencial en paralelo, usando directivas y funciones mediante el uso de variables compartidas (para ejecutar aplicaciones en paralelo en distintos threads).  
Esta API nos provee de directivas de compilador, funciones de biblioteca y variables de entorno.  
Actualmente, está siendo desarrollada por distintas empresas conocidas (entre ellas, AMD e Intel), por lo que podemos decir que es portable, al soportarlo las grandes marcas de procesadores (y por tanto, la mayoría de compiladores). Además, también hay empresas de software que trabajan con ella.   
Podemos consultar la especificación en [https://www.openmp.org](https://www.openmp.org)  
En clase, se trabajará con la versión (y especificación) OpenMP 2.5.  
  
OpenMP nos aporta:
- Directivas: El preprocesador del compilador las sustituye por código (no como las directivas nativas de `c`).
- Funciones: Para fijar (por ejemplo, indicar el número de hilos) y preguntar (consultar el número de hilos) por parámetros en tiempo de ejecución.
- Variables de entorno: Para fijar variables antes de la ejecución del programa. No se modifican en el programa; las establece el usuario que va a ejecutar nuestro programa para cambiar parámetros de ejecución.
  
Se trata de una herramienta no automática. Esto es, no extrae paralelismo implícito, sino que es el programador el que tiene que hacerlo explícito. 
  
Para usar la herramienta, al compilar debemos utilizar:
```bash
gcc [archivo.c] -o [ejecutable] -fopenmp
```
Esta directiva del compilador lo que hace es definir `_OPENMP`.
Si no se compila con dicha opción un programa OpenMP, las directivas de OpenMP se interpretarán como comentarios y no obtendremos ningún error ni warning. Podemos tener programas que queramos que se ejecuten de forma paralela o secuencial. En dicho caso, podremos (o no) especificar `-fopenmp` a la hora de compilar.  
Sin embargo, si usamos funciones y no especificamos `-fopenmp`, sí que obtendremos un error. Para seguir el último comportamiento especificado, debemos hacer (si por ejemplo, usamos la función `omp_get_thread_num()`):
```c
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif
```
  
# Sintaxis de directivas
Todas comiezan por almohadilla (natural de directivas de `c`), seguido de `pragma omp`. Luego, incluimos el nombre de directiva, cláusulas y terminamos con un salto de línea:
```bash
#pragma omp nombre [cláusula[,] ...] 
```
Donde las cláusulas pueden aparecer (o no, que lo indican los corchetes). Además, estas pueden ir separadas por comas o por espacios. Las directivas son case sensitive.
  
### Separar directiva en varias líneas
Para separar una misma directiva en varias líneas, podemos usar '\\':
```c
#pragma omp parallel private (...) \
shared (...)
```
  
# Definiciones
## Directiva ejecutable
Se trata de una directiva que aparece en el código ejecutable.

## Bloque estructurado
Un conjunto de sentencias, usualmente entre llaves. Puede ser sólamente una sentencia.

## Construcción
Engloba la directiva y su código asociado. Puede tener asociada una línea, un bucle o un bloque estructurado. La asociación es algo estático, que podemos ver en el código.

## Región
Aparece en tiempo de ejecución. Asociadas a las construcciones aparecen regiones de código. Una región es el conjunto de todo el código afectado por una directiva de OpenMP, junto con esta misma. Esta puede extenderse entre llamadas a subrutinas.

# Directivas
Usando OpenMP, será común usar directivas, funciones y variables de entorno. Para ello, se recomienda incluir la librería `omp.h` siempre que usemos OpenMP, tal y como se ha indicado arriba. A continuación, vamos a desarrollar las directivas que veremos en esta sesión de prácticas.  
  
Encontramos tres clasificaciones:
| Directiva                      | ejecutable                                | declarativa   |
|--------------------------------|-------------------------------------------|---------------|
| con bloque  estructurado       | **parallel**                              |               |
|                                | **sections**, **worksharing**, **single** |               |
|                                | *master*                                  |               |
|                                | *critical*                                |               |
|                                | ordered                                   |               |
| bucle                          | **DO/for**                                |               |
| simple (una sentencia)         | *atomic*                                  |               |
| autónoma (sin código asociado) | *barrier*, flush                          | threadprivate |
  
Todas (salvo las autónomas) son con sentencias.  
Las directivas en negrita indican que hay una barrera implícita al final de las directivas (esto es, como si hubiera un `barrier` al final de sus regiones).  
Las directivas en cursiva y en negrita son las que se desarrollarán en esta práctica.  
  
- `barrier`: Todos los hilos se esperan entre sí una vez alcanzada esta directiva.
- `flush`: Relacionado con el modelo de consistencia de OpenMP (Tema 3).
- `worksharing` y `DO`: Son directivas de Fortran, no se verán en la asignatura al estar orientada a `c`.

## parallel
La directiva `parallel` se usa para decirle a OpenMP que añada las funciones del SO necesarias para crear hilos, y que después llame al SO para borrar dichos hilos. Es el thread `master` el encargado de crear estos hilos. 
```c
#pragma omp parallel [clause[[,]clause]...]
    bloque estructurado
```
Se puede usar `parallel` de forma anidada (no se verá en esta asignatura).  
*Presenta una barrera de forma implícita al final*.  
*`parallel` no reparte trabajo*, el bloque estructurado asociado será ejecutado por todos los hilos correspondientes. Podemos hacer uso de funciones como `omp_get_thread_num()` para repartir trabajos a hilos con la directiva `parallel`, mandando un trabajo a cada hilo dependiendo de su identificador (de su número). Por defecto, se usan todos los núcleos lógicos del computador. Los hilos se numeran desde 0, siendo el hilo `master` el 0: 
```c
#pragma omp parallel
{
    if(omp_get_thread_num() < thread)
        printf("Thread %d", omp_get_thread_num());
        // ...
    else
        printf("Thread %d", omp_get_thread_num());
        // ...
}
```
Esta no es la forma en la que repartiremos el trabajo entre hebras, en su lugar usaremos directivas dedicadas a ello.

#### private
Todas las variables creadas fuera del bloque de `parallel` la comparten todos los hilos. Podemos hacer que estas variables sean privadas para cada hebra (que cada hebra se cree una instancia de esta) usando la cláusula `private`:
```c
int ID;
#pragma omp parallel private (ID)
{
    bloque estructurado
}
```

## omp_get_thread_num()
Esta función nos devuelve el número de hebra que ejecuta la función. Las numeración de las hebras comienza en 0, siendo esta la hebra `master`.

## omp_get_num_threads()
Función que devuelve el número de hebras que ejecuta la función (usar dentro de una directiva `parallel`).

## OMP_NUM_THREADS
En esta sección nos dedicamos al estudio de las directivas, pero ya nos es de utilidad aprender a manejar variables de entorno, como `OMP_NUM_THREADS`. Esta establece el número de hebras que ejecutarán el siguiente programa. Para su uso, en una terminal:
```bash
export OMP_NUM_THREADS=n
./ejecutable
```
Donde $n$ es el número de hebras que queremos que ejecuten nuestro programa.

## OMP_DYNAMIC
Esta es una variable booleana (`OMP_DYNAMIC=False` o `OMP_DYNAMIC=True`), especifica si el sistema operativo puede (`True`) o no (`False`) coger prestadas hebras de las encargadas para nuestro programa.

## OMP_PROC_BIND
Se verá más adelante en la asignatura, pero podemos usarla ya con el valor `OMP_PROC_BIND=spread` para que se asignen hebras a cores lógicos y no a cores físicos (algo así como la opción `--hint=nomultithread` de slurm).

*Nota:* Para usar las variables de entorno como estas 3 ya mencionadas (aprenderemos a usar más en futuras prácticas), si estamos creando un script deberemos usar `export`:
```bash
export OMP_NUM_THREADS=12
export OMP_DYNAMIC=False
export OMP_PROC_BIND=spread
./ejecutable args...
```

## for
Para decirle a OpenMP que realice las operaciones necesarias para repartir el trabajo del bucle entre los hilos.  
Podremos especificar cómo queremos que se haga la asignación próximamente (cláusula `schedule`). Por defecto, cada hilo realiza un conjunto de iteraciones.  
En caso de tener más iteraciones que hilos, la distribución de las iteraciones se realiza de forma próxima. Es decir, si tenemos 8 iteraciones y 4 hilos, el hilo 0 hará las iteraciones 0 y 1 (este es el funcionamiento por defecto).  
Un ejemplo de uso de la directiva es el siguiente:
```c
#pragma omp for [clause[[,]clause]...]
    for(...){
        // ...
    }
```
La directiva no nos sirve para paralelizar cualquier bucle `for`. El bucle tiene que ser el más sencillo:
```c
for(var = initial-value; var relational-op b; var += incr)
```
Donde `initial-value`, `b` y `incr` son conocidos en tiempo de compilación y no dependen de la iteración del bucle.  
  
```c
#pragma omp parallel
{
    #pragma omp for
    for(int i = 0; i < N; i++){
        printf("Soy el hilo %d con la iteración %d", omp_get_thread_num(), i);
    }
}
```

*Cuenta con una barrera implícita al final*.

## sections
Realiza un reparto de hilos en función de secciones:
```c
#pragma omp parallel
{
    #pragma omp sections
    {
        #pragma omp section
        funcionA();
        
        #pragma omp section
        funcionB();
    }
}
```
En este caso, un hilo ejecutará la función `funcionA()` y otro la función `funcionB()`.  
En caso de tener menos hilos que secciones, habrá hilos que ejecuten más de una sección.  
*Cuenta con una barrera implícita al final.*

## single
El bloque estructurado lo ejecuta sólamente un hilo (el primero que llegue). Nos aseguramos de que el bloque estructurado sólo se ejecute una vez.  
*Cuenta con una barrera implícita al final* (de utilidad al usar `single` para leer datos del usuario, para que el resto de hilos espere a tener el dato antes de usarlo).
```c
#pragma omp single [clause[[,]clause]...]
    structured-block
```
Esto es de utilidad al solicitar datos al usuario, imprimir datos, o realizar operaciones más delicadas, como llamadas al sistema.

```c
#pragma omp parallel
{
    # ...
     
    #pragma omp single
    {
        printf("El valor de la ejecución es: %d", resultado);
    }
}
```
Este es un ejemplo para no imprimir en pantalla el resultado múltiples veces, sólo una.

## master
Es similar a `single` pero no cuenta con barrera implícita y la hebra que ejecuta el bloque asociado es la `master`, la hebra 0.  
Al no contar con barrera implícita, será usual ver `barrier` después de algún `master`.

# Comunicación y sincronización
Contamos con tres directivas:
- barrier.
- critical.
- atomic.
  
## barrier
```c
#pragma omp barrier
```
Establece una marca que deben alcanzar todos los procesos antes de que cualquier proceso del programa continue con su ejecución. Al final de directivas como `parallel` o de trabajo compartido suele haber una barrera implícita, como ya hemos visto.

## critical
```c
#pragma omp critical [(name)]
    structured-block
```
Evita que varios hilos accedan a variables compartidas a la vez (evita condiciones de carrera). En su lugar, los hilos irán estableciendo cerrojos sobre esta sección de código: estableciendo cerrojo, ejecutando el código y liberando el cerrojo para que la siguiente hebra (en caso de haberla) pueda seguir con la ejecución. 
```c
#pragma omp parallel
{
    #pragma omp for
    for(...){
        // cálculos
    }
    
    #pragma omp critical 
    suma = suma + calculos;
}
```

Cada `critical` siempre tiene un nombre (un `name`). Todos los que no tengan nombre explícito tendrán el *mismo* nombre no especificado.  
Si varios `critical` tienen el mismo nombre (recordamos que no tener nombre es un único nombre), entonces a efectos prácticos son el mismo `critical` y si hay un hilo ejecutando una de las dos regiones, ambas se bloquearán.  
Podemos por tanto pensar que `name` es el nombre del cerrojo que se establece sobre la sección correspondiente al `critical`.

## atomic
Es similar a `critical`, pero sólo permite una única instrucción y que sea sencilla. Si tenemos varias sentencias, hay que utilizar `critical`.
```c
#pragma omp atomic
```
Podemos usarlo en el ejemplo anterior de la directiva `critical`:
```c
#pragma omp parallel
{
    #pragma omp for
    for(...){
        // cálculos
    }
    
    #pragma omp atomic 
    suma = suma + calculos;
}
```
Sólo podemos usarlo con los operadores:
```
+, *, -, /, &, ^, |, <<, >>
```
*Notemos* que `+=` no se encuentra en esta lista (ni `-=`, `*=`, `/=`, ...).

# Usar directivas de forma combinada
Podemos combinar dos directivas en una sola, tal y como se muestra en los códigos de debajo, para una mayor legibilidad de estos:
```c
#pragma omp parallel [clauses]
    #pragma omp for [clauses]
        // for-loop
```
Podemos reducirlo a:
```c
#pragma omp parallel for [clauses]
    // for-loop
```
  
Otro ejemplo:
```c
#pragma omp parallel [clauses]
    #pragma omp sections [clauses]
    {
        #pragma omp section
        // structured block
    }
```
Que podemos reducir a:
```c
#pragma omp parallel sections [clauses]
{
    #pragma omp section
    // structured block
}
```
  
Las directivas combinadas admiten las cláusulas de las dos directivas, excepto la cláusula `nowait`.
