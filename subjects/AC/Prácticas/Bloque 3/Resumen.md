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
  
Con prioridad descendente:
- Variables de control internas, tales como `nthreads-var`, `dyn-var`, `nest-var`, `run-sched-var`, `def-sched-var`.
- Variables de entorno, cuyo ámbito son los códigos que se ejecutan a partir de su modificación. Encontramos variables como `OMP_NUM_THREADS`, `OMP_DYNAMIC`, `OMP_NESTED`, `OMP_SCHEDULE`.
- Funciones del entorno de ejecución, cuyo ámbito es el código que las usa. Son funciones como: `omp_get/set_dynamic()`, `omp_get_max_threads()`, `omp_get/set_num_threads()`, `omp_get/set_nested()`, `omp_get_thread_num()`, `omp_get_num_procs()`, `omp_in_parallel()`.
- Cláusulas que no modifican las variables de control, cuyo ámbito es la directiva que las usa: `if`, `schedule`, `num_threads`. Estas se vieron ya en la [Sesión II de prácticas](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/AC/Pr%C3%A1cticas/Bloque%202/Resumen.md).

Con la versión `3.0` de OpenMP, podemos encontrarnos nuevas variables:
- Variables de control internas: `thread-limit-var`.
- Variables de entorno: `OMP_THREAD_LIMIT`.
- Funciones del entorno de ejecución: `omp_get_thread_limit()`, `omp_get_schedule(kind,modifier)`, `omp_set_schedule(kind, modifier)`.

# Variables de control internas
Nos encontramos dos clasificaciones:

## Que afectan a una región parallel
### dyn-var
Cuyo ámbito es el entorno de datos.  
Controla el ajuste dinámico del número de threads. Toma valores booleanos (aunque puede depender de la implementación).

### nthreads-var
Cuyo ámbito es el entorno de datos.  
Controla el número de threads en la siguiente ejecución paralela. Es un número (depende de la implementación).

### thread-limit-var (3.0)
Cuyo ámbito es el entorno de datos.  
Controla el número máximo de threads para todo el programa. Es un número (depende de la implementación).

## Que afectan a regiones DO/for
### run-sched-var
Cuyo ámbito es el entorno de datos.  
Controla la planificación de bucles para `runtime`. Adopta valores `(kind[, chunk])` (depende de la implementación).

### def-sched-var
Cuyo ámbito es el dispositivo.  
Controla la planificación de los bucles por defecto con ámbito de programa. Adopta valores `(kind[, chunk])` (depende de la implementación).

# Variables de entorno
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
| `thread-limit-var`  | `omp_get_thread_limit()`             |                                    |
| `nest-var`          | `omp_get_nested()`                   | `omp_set_nested()`                 |
| `run-sched-var`     | `omp_get_schedule(&kind, &modifier)` | `omp_set_schedule(kind, modifier)` |
| `def-sched-var`     |                                      |                                    |

## omp_get_thread_num()
## omp_get_num_threads()
## omp_get_num_procs()
## omp_in_parallel()

# Cláusulas
