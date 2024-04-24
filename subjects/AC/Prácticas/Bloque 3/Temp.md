# Arquitectura de Computadores. Sesión III de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Arquitectura de Computadores.  
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen de la Sesión III de Prácticas.

Esta sesión práctica está orientada a la interacción con el entorno OpenMP:
- Saber obtener información del entorno.
- Saber influir en la ejecución de nuestro programa paralelo.

# Introducción
Relacionado con el entorno de ejecución en el que nos encontremos, tenemos distintas clasificaciones de utilidades que nos proporciona OpenMP:
  
Con prioridad ascendente:
## Variables de control internas
Son variables a las que no podemos acceder directamente desde código y modificarlas. La única forma de acceder a ellas es mediantes variables de entorno o funciones.  
  
Tales como `nthreads-var`, `dyn-var`, `nest-var`, `run-sched-var`, `def-sched-var`.


- Variables de entorno, cuyo ámbito son los códigos que se ejecutan a partir de su modificación. Encontramos variables como `OMP_NUM_THREADS`, `OMP_DYNAMIC`, `OMP_NESTED`, `OMP_SCHEDULE`.
- Funciones del entorno de ejecución, cuyo ámbito es el código que las usa. Son funciones como: `omp_get/set_dynamic()`, `omp_get_max_threads()`, `omp_get/set_num_threads()`, `omp_get/set_nested()`, `omp_get_thread_num()`, `omp_get_num_procs()`, `omp_in_parallel()`.
- Cláusulas que no modifican las variables de control, cuyo ámbito es la directiva que las usa: `if`, `schedule`, `num_threads`. Estas se vieron ya en la [Sesión II de prácticas](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/AC/Pr%C3%A1cticas/Bloque%202/Resumen.md).

## Cláusulas
No modifican variables de control.

Con la versión `3.0` de OpenMP, podemos encontrarnos nuevas variables:
- Variables de control internas: `thread-limit-var`.
- Variables de entorno: `OMP_THREAD_LIMIT`.
- Funciones del entorno de ejecución: `omp_get_thread_limit()`, `omp_get_schedule(kind,modifier)`, `omp_set_schedule(kind, modifier)`.

# Variables de control internas
Nos encontramos dos clasificaciones:

## Que afectan a una región parallel
### dyn-var
Cuyo ámbito es el entorno de datos.  
Controla el ajuste dinámico del número de hilos. Toma valores booleanos (su valor inicial depende de la implementación).  
Si lo ponemos a `False`, el sistema operativo no va a modificar el número de hilos del programa de forma dinámica.  
Se puede consultar mediante funciones y modificar mediante variables de entorno y funciones.

### nthreads-var
Cuyo ámbito es el entorno de datos.  
Controla el número de hilos que se van a usar en la siguiente ejecución paralela. Es un valor numérico (su valor inicial depende de la implementación. Hemos visto que `gcc` lo inicializa al número de cores lógicos del computador).  
Se puede consultar mediante funciones y modificar mediante variables de entorno y funciones.

### thread-limit-var (3.0)
Cuyo ámbito es el entorno de datos.  
Controla el número máximo de hilos para todo el programa. Es un número (su valor inicial depende de la implementación, suele ser exageradamente elevado).  
Se puede consultar mediante funciones y modificar mediante variables de entorno y funciones.

## Que afectan a regiones DO/for
Relacionadas en cómo se asignan las iteraciones de un bucle a los hilos.

### run-sched-var
Cuyo ámbito es el entorno de datos.  
Controla la planificación de bucles para `runtime`. Adopta valores `(kind[, chunk])` (depende de la implementación).

### def-sched-var
Planificación de bucles por defecto de `gcc`, asignación estática de forma que interacciones consecutivas se asignan a un mismo hilo.  
Podemos cambiar dicha asignación mediante una cláusula de asignación, cambiando la asignación a la que haya en `run-sched-var`.  
Cuyo ámbito es el dispositivo.  
Controla la planificación de los bucles por defecto con ámbito de programa. Adopta valores `(kind[, chunk])` (depende de la implementación).  
No puede modificarse ni consultarse.

# Variables de entorno
Sirven para modificar las variables de control ya vistas.  
Cada variable de entorno lleva asociada una variable de control:

## OMP_DYNAMIC
Asociada con `dyn-var`:
```bash
export OMP_DYNAMIC=FALSE
export OMP_DYNAMIC=TRUE
```

## OMP_NUM_THREADS
Asociada con `nthreads-var`:
```bash
export OMP_NUM_THREADS=8
```

## OMP_THREAD_LIMIT
Asociada con `thread-limit-var`:
```bash
export OMP_THREAD_LIMIT=8
```

## OMP_SCHEDULE
Asociada con `run-sched-var`:
```bash
export OMP_SCHEDULE="static,4"
export OMP_SCHEDULE="nonmonotonic:static,4"
export OMP_SCHEDULE="dynamic"
export OMP_SCHEDULE="monotonic:dynamic,4"
```

# Funciones del entorno de ejecución
Cada una para modificar o consultar una variable de control interna:

| Variable de control | Rutina para consultar                | Rutina para modificar              |
|---------------------|--------------------------------------|------------------------------------|
| `dyn-var`           | `omp_get_dynamic()`                  | `omp_set_dynamic()`                |
| `nthreads-var`      | `omp_get_max_threads()`              | `omp_set_num_threads()`            |
| `thread-limit-var`  | `omp_get_thread_limit()`             | No es modificable, sólo con ve     |
| `nest-var`          | `omp_get_nested()`                   | `omp_set_nested()`                 |
| `run-sched-var`     | `omp_get_schedule(&kind, &modifier)` | `omp_set_schedule(kind, modifier)` |
| `def-sched-var`     |                                      |                                    |

```c
omp_set_schedule(omp_ched_t kind, int chunk_size);
omp_get_schedule(&kind, &chunk_size);
```

monotonic con chunk de 1: Si asignamos la iteracion `i` a un hilo, la siguiente a asignar es la `i+1`. Se asignan de forma creaciente.
`nomonotonic`: Se asignan en cualquier orden.

Podemos combinar omp_monotonic con el resto.
En dígito hexadecimal menos significativo se pone el tipo y en el bit de signo si es monotonic o no.

Mas funciones pero que no modifican las variables de control

## omp_get_thread_num()
Devuelve identificador de hebra.

## omp_get_num_threads()
Devuelve el número de hilos que hay en la región en la que se ejecuta. Si se ejecuta en una secuciencial, devolverá un 1.

## omp_get_num_procs()
Devuelve el número de núcleos lógicos de la máquina.

## omp_in_parallel()
true si se ejecuta la función en una zona paralela y false si no.

# Cláusulas
## if 
No hay ejecución si no se cumple la condición.

## num_threads 


## schedule 
Cláusula de planificación, cambiar el valor por defecto de asignación que usa `gcc`.
- static. Por defecto, monotonic.
- dynamic
- guided
- auto
- runtime

chunk: tamaño de unidades de trabajo que se asignan a los hilos. El tamaño es el número de iteraciones del bucle que tienen las unidades. Cuando asignamos un chunk a todos los hilos, sigue de forma rotatoria.

static con chunk de 1: se asigna de forma rotatoria.

En la estática la sobrecarga se reduce bastante. Siempre que podamos utilizar una asignación estática lo haremos.  
La asignación de forma dinámica nos permite realizar repartos más equitativos, útil en repartos complejos.

Con chunks más grandes tenemos un menor overhead (sobrecarga). Podemos comenzar añadiendo unidades de trabajo grandes y disminuir su tamaño progresivamente de forma que el tamaño más pequeño va a ser el especificado (guided).

#### runtime
La planificación que nosotros pongamos en la variable de control `run-sched-var`, que podemos cambiar su valor mediante ve o función.  
Copiar diagrama de flujo.

# Funciones 
Para sincronización con cerrojos o para obtener tiempos de ejecución.

## Cerrojos
Con ellas podemos implementar un `atomic`. Podemos sustituir estas funciones por código, necesariamente en ASM.

MPI usa procesos en lugar de hebras: sobrecarga enorme. En resumen, evitar usar procesos.
