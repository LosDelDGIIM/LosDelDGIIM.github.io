# Arquitectura de Computadores. Sesión III de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Arquitectura de Computadores.  
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen de la Sesión III de Prácticas.

Esta sesión práctica está orientada a familiarizarnos con el entorno OpenMP, de forma que conozcamos cómo consultar las configuraciones por defecto y que sepamos influir sobre la herramienta de programación paralela.

# Introducción
OpenMP cuenta con **variables de control internas** (a las que nos podemos acceder directamente desde código) que deben tenerse en cuenta a la hora de determinar ciertas funcionalidades por defecto de OpenMP. Podemos modificar estas variables mediante **variables de entorno** o **funciones**, y consultarlas mediante **funciones**. Además, ciertas **cláusulas** pueden ayudarnos a modificar funcionalidades de OpenMP.

## Variables de control internas
Son ciertas variables que tiene OpenMP internamente, las cuales permiten establecer funcionalidades que nuestro código seguirá. No pueden accederse de forma directa desde código, sino que debemos hacerlo mediante variables de entorno y funciones. Algunas de estas son:
```
nthreads-var dyn-var nest-var run-sched-var def-sched-var
```

## Variables de entorno

