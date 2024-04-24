# Arquitectura de Computadores. Sesión III de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Arquitectura de Computadores.  
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen de la Sesión III de Prácticas.

# Introducción
Esta sesión práctica está orientada a familiarizarnos con el entorno OpenMP, de forma que conozcamos cómo consultar las configuraciones por defecto y que sepamos influir sobre la herramienta de programación paralela.  
  
Nos encontramos con 4 niveles de abstracción a la hora de influir sobre la ejecución de nuestro programa paralelo: **variables de control internas**, **variables de entorno**, **funciones del entorno** y **cláusulas**. Listadas en orden ascendente de prioridad (es decir, las cláusulas son las más prioritarias).  
  
El ámbito de cada elemento no forma parte de esta práctica, pero puede ser útil revisar esta práctica a la hora de realizar la práctica opcional sobre coprocesadores.

## Variables de control internas
Son ciertas variables de las que dispone OpenMP de forma interna, las cuales permiten establecer funcionalidades que nuestro código seguirá. No pueden accederse de forma directa desde código, sino que debemos hacerlo mediante variables de entorno y funciones. Algunas de estas son:
```
nthreads-var dyn-var nest-var run-sched-var def-sched-var thread-limit-var ...
```

## Variables de entorno
Son variables a las que podemos acceder desde el entorno de `bash`. Nos permiten modificar variables de control internas, de forma previa a la ejecución de nuestro programa paralelo. Influyen sobre los códigos que se ejecuten tras la modificación de la variable. Algunas son:
```
OMP_NUM_THREADS OMP_DYNAMIC, OMP_NESTED OMP_SCHEDULE OMP_THREAD_LIMIT ...
```

## Funciones del entorno de ejecución
Son funciones que nos proporciona la librería `omp.h` de OpenMP. Nos permiten consultar y modificar variables de control internas mediante funciones *getters* y *estters*. Encontramos:
```
omp_set/get_dynamic() omp_get_max_threads() omp_set/get_num_threads() omp_set/get_nested() omp_get_thread_num() omp_get_num_procs() omp_in_parallel() omp_get_thread_limit() omp_set/get_schedule(kind, modifier) ...
```

## Cláusulas
Estas no modifican las variables de control. Sin embargo, contamos con las claúsulas `if` y `num_threads` que nos permite influir sobre la ejecución de la región paralela; y con `schedule`, que nos permite influir sobre la asignación de iteraciones de un bucle a hebras.
***

# Variables de control internas y cómo modficarlas
Existen dos tipos de variables de control internas (sus valores por defecto dependen de la implementación):

## Afectan a región parallel
Las que modifican la ejecución de una región afectada por `parallel`. Su ámbito en todas ellas es el entorno de datos.

### dyn-var
Es una variable booleana que controla el ajuste dinámico del número de hilos de nuestro programa paralelo. Si la ponemos a `false`, el sistema operativo no podrá modificar el número de hilos del programa de forma dinámica, en caso de necesitarlos.  
  
| `dyn-var`           | Modificable              | Consultable         |
|----------------------|--------------------------|---------------------|
| Variable de entorno  | `OMP_DYNAMIC`            | X                   |
| Funciones de entorno | `omp_set_dynamic(value)` | `omp_get_dynamic()` |

### nthreads-var
Es una variable numérica que controla el número de hilos a usar en la próxima región `parallel`. Hemos podido experimentar que `gcc` lo inicializa por defecto al número de cores lógicos del computador.  
  
| `nthreads-var`       | Modificable                  | Consultable             |
|----------------------|------------------------------|-------------------------|
| Variable de entorno  | `OMP_NUM_THREADS`            | X                       |
| Funciones de entorno | `omp_set_num_threads(value)` | `omp_get_max_threads()` |

### thread-limit-var
Pertence a la versión 3.0 de OpenMP.  
Es una variable numérica que controla el número máximo de hilos para todo el programa. Por defecto, hemos comprobado que se trata de un número exageradamente elevado.  
  
| `thread-limit-var`   | Modificable        | Consultable              |
|----------------------|--------------------|--------------------------|
| Variable de entorno  | `OMP_THREAD_LIMIT` | X                        |
| Funciones de entorno | X                  | `omp_get_thread_limit()` |

## Afectan a región DO/for
Aunque sólo nos interesa la directiva `for`, también funcionan con `DO`.

### run-sched-var
Su ámbito es el entorno de datos.  
Se trata de una variable que puede adoptar un valor `kind[, chunk]`. Es decir, se le puede especificar simplemente un tipo a adoptar aunque puede ir acompañado (o no) de un valor numérico que representa un `chunk`.  
Controla la planificación de bucles para `runtime`.  
  
| `run-sched-var`      | Modificable                     | Consultable                       |
|----------------------|---------------------------------|-----------------------------------|
| Variable de entorno  | `OMP_SCHEDULE`                  | X                                 |
| Funciones de entorno | `omp_set_schedule(kind, chunk)` | `omp_get_schedule(&kind, &chunk)` |
  
Ejemplos de su modificación mediante variables de entorno son:
```bash
export OMP_SCHEDULE="static,4"
export OMP_SCHEDULE="nonmonotonic:static,4"
export OMP_SCHEDULE="dynamic,4"
export OMP_SCHEDULE="monotonic:dynamic,4"
```
  
Mientras que podemos modificar la variable de control también desde código, gracias a la función:
```c
void omp_set_schedule(omp_sched_t kind, int chunk_size);
```
Que necesita del tipo:

```c
typedef enum omp_sched_t {
    // schedule kinds
    omp_sched_static = 0x1,
    omp_sched_dynamic = 0x2,
    omp_sched_guided = 0x3,
    omp_sched_auto = 0x4,
    
    // schedule modifier
    omp_sched_monotonic = 0x80000000u
} omp_sched_t;
```
  
Ampliaremos la información en la cláusula `schedule`, donde todo quedará más claro.

### def-sched-var
Cuyo ámbito es de dispositivo, se trata de la planificación por defecto de los bucles. Hemos comprobado que la planificación por defecto en `gcc` es la asignación estática de forma que interacciones consecutivas se asignan a un mismo hilo.  
  
No puede consultarse ni modificarse.

# Funciones del entorno de ejecución
A parte de las funciones del entorno que modifican variables de control internas, disponemos de otras rutinas del entorno que nos son útiles:

## omp_get_thread_num()
Devuelve a la hebra su identificador dentro de su grupo. Si estamos usando $N$ hebras, nos devolverá un número entero en el intervalo $[0, N[$, siendo 0 la hebra `master`.

## omp_get_num_threads()
Devuelve el número de hebras que se están usando en una región paralela. Llamada en un código secuencial, devolverá `1`.

## omp_get_num_procs()
Devuelve el número de núcleos lógicos disponibles para el programa en el momento de la ejecución.

## omp_in_parallel()
Devuelve `true` si se llama a la función dentro de una región `parallel` activa (si está dentro de varios `parallel` anidados, basta con que uno de ellos lo esté). Devuelve `false` en el caso contrario.

# Cláusulas
Recuperamos la famosa tabla de cláusulas de la [Sesión II de prácticas](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/AC/Pr%C3%A1cticas/Bloque%202/Resumen.md)

| Tipo        | Cláusula            | parallel | DO/for | sections | single | parallel DO/for | parallel sections |
|-------------|---------------------|----------|--------|----------|--------|-----------------|-------------------|
| Control     | **if** (1)          | X        |        |          |        | X               | X                 |
| nº threads  | **num_threads** (1) | X        |        |          |        | X               | X                 |
|             |                     |          |        |          |        |                 |                   |
| Control     | shared              | X        |        |          |        | X               | X                 |
| del         | private             | X        | X      | X        | X      | X               | X                 |
| ámbito      | lastprivate         |          | X      | X        |        | X               | X                 |
| de las      | firstprivate        | X        | X      | X        | X      | X               | X                 |
| variables   | default (1)         | X        |        |          |        | X               | X                 |
|             | reduction           | X        | X      | X        |        | X               | X                 |
|             |                     |          |        |          |        |                 |                   |
| Copia de    | copyin              | X        |        |          |        | X               | X                 |
| valores     | copyprivate         |          |        |          | X      |                 |                   |
|             |                     |          |        |          |        |                 |                   |
| Planifica   | **schedule** (1)    |          | X      |          |        | X               |                   |
| iteraciones | ordered (1)         |          | X      |          |        | X               |                   |
|             |                     |          |        |          |        |                 |                   |
| No espera   | nowait              |          | X      | X        | X      |                 |                   |

Donde los '(1)' indicaban que la cláusula sólo podía aparecer una vez en la directiva. 
Nos centramos ahora en las cláusulas que aparecen en negrita:

## if(expresion)
Sólo puede aparecer en las directivas `parallel`, `parallel DO/for` o `parallel sections`.  
  
Si `expresion` se evalúa como `true`, hace que el código de la región afectada por `parallel` se ejecute en paralelo. Si la expresión se evalúa como `false`, la región paralela se ejecutará en serie (por una única hebra).
```c
int N;
// ...
#pragma omp parallel for if(N>20)
for(int i = 0; i < N; i++){...}
```
De esta forma, el bucle `for` sólo se paralelizará si el valor de la variable `N` es mayor que 20.  
Esta funcionalidad nos permite evitar las sobrecargas que se generan al paralelizar código donde no se aproveche bien la paralelización (por ejemplo, un bucle de pocas iteraciones).  
  
*Sólo puede haber una cláusula `if`*

#### Ejemplo de prioridad
Al inicio de la sesión de prácticas habíamos comentado la prioridad de las distintas formas que tenemos de modificar una variable de control interna. Resaltamos ahora las diversas formas que tenemos de fijar el número de hebras de una región paralela, en prioridad decreciente:  
  
- Cláusula `if`: Establece si la región se paralelizará o no.
- Cláusula `num_threads`: Establece el número de hilos de la próxima región paralela.
- Función `omp_set_num_threads()`: Establece el número de hilos de la próxima región paralela.
- Variable de entorno `OMP_NUM_THREADS`: Establece el número de hilos de la próxima región paralela.
  
Donde la cláusula `num_threads` tiene prioridad sobre la función `omp_set_num_threads()`, que tiene prioridad sobre la función `OMP_NUM_THREADS`; todas ellas dependen de que la condición de la cláusula `if` sea cierta para poder llevarse a cabo.

## num_threads(n)
Sólo puede aparecer en las directivas `parallel`, `parallel DO/for` o `parallel sections`.  
  
Tiene la misma funcionalidad que la función `omp_set_num_threads`. Es decir, establece el número de hebras a $n$ en la región paralela afectada por su `parallel` asociado.
```c
#pragma omp parallel sections num_threads(2)
{
    #pragma omp section
    funcionA();

    #pragma omp section
    funcionB();
}
```
Notemos que el número de hebras que se crearán dentro de una directiva `parallel` con `num_threads(n)` será de $n-1$ hebras (ya que la hebra `master` o 0 ya se encuentra creada y estará disponible en el conjunto de hebras disponibles para la región afectada por `parallel`).  
  
*Sólo puede haber una cláusula `num_threads`*.

## schedule
Sólo puede aparecer en las directivas `DO/for` o `parallel DO/for`.  
  

