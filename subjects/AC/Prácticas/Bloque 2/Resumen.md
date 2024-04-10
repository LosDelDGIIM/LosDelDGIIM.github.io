# Arquitectura de Computadores. Sesión II de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Arquitectura de Computadores.  
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen de la Sesión II de Prácticas.

Esta práctica está orientada al manejo de las cláusulas, las cuales nos permiten modfiicar o añadir funcionalidades a las directivas ya vistas en la [Sesión I de Prácticas](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/AC/Pr%C3%A1cticas/Bloque%201/Resumen.md).  
Además, comentaremos el ámbito que por defecto se les da a las variables, ya que nos ayudará a entender la finalidad y uso de ciertas cláusulas.

## Introducción
Las cláusulas nos permiten ajustar el comportamiento de las directivas. Su sintaxis suele ser la siguiente:
```c
#pragma omp [directiva] [cláusula]
```
Son opcionales (es decir, podemos usar directivas sin usar cláusulas). Además, al usar varias cláusulas, podemos elegir separarlas o no con comas. Es decir, las dos figuras siguientes son sintácticamente correctas:
```c
#pragma omp parallel num_threads(8) if(N>20)
```
```c
#pragma omp parallel num_threads(8), if(N>20)
```
Como vemos, la sintaxis de una cláusula es similar a al de una función, al recibir parámetros (o condiciones, en el caso de `if`, que no deja de ser un parámetro booleano).

#### Directivas que aceptan cláusulas
Son:
- `parallel`.
- Las de trabajo compartido: `DO/for`, `sections`, `single` y `workshare` (aunque no veremos ni `DO` ni `workshare`).
- Las directivas que combinan `parallel` con cualquiera de trabajo compartido.

#### Directivas que no acepta cláusulas
Estas son:
- `master`.
- Las de sincronización y/o consistencia: `critical`, `barrier`, `atomic` y `flush` (recordamos que no hemos visto `flush`).
- `ordered` (no se ha visto).
- `threadprivate` (tampoco se ha visto).

A continuación, mostramos una tabla resumen de las cláusulas que veremos a lo largo de esta práctica:
| Tipo        | Cláusula            | parallel | DO/for | sections | single | parallel DO/for | parallel sections |
|-------------|---------------------|----------|--------|----------|--------|-----------------|-------------------|
| Control     | **if** (1)          | X        |        |          |        | X               | X                 |
| nº threads  | **num_threads** (1) | X        |        |          |        | X               | X                 |
| Control     | **shared**          | X        |        |          |        | X               | X                 |
| del         | **private**         | X        | X      | X        | X      | X               | X                 |
| ámbito      | **lastprivate**     |          | X      | X        |        | X               | X                 |
| de las      | **firstprivate**    | X        | X      | X        | X      | X               | X                 |
| variables   | **default** (1)     | X        |        |          |        | X               | X                 |
|             | **reduction**       | X        | X      | X        |        | X               | X                 |
| Copia de    | copyin              | X        |        |          |        | X               | X                 |
| valores     | **copyprivate**     |          |        |          | X      |                 |                   |
| Planifica   | schedule (1)        |          | X      |          |        | X               |                   |
| iteraciones | ordered (1)         |          | X      |          |        | X               |                   |
| No espera   | nowait              |          | X      | X        | X      |                 |                   |

Donde las cláusulas en negrita son las que estudiaremos en esta práctica.  
Las cláusulas con un '(1)' sólo pueden usarse una vez en la directiva que nos encontremos. Por ejemplo, no podríamos hacer un `parallel num_threads(4) num_threads(9)`, pero sí un `parallel private(x) private(y)`.  
Notamos ya que las cláusulas dependen de la directiva: hay directivas que no aceptan determinadas cláusulas, por ejemplo, `for` no admite la directiva `num_threads`.  
  
`nowait` es una cláusula que no veremos ahora. Sin embargo, es de utilidad saber que su función es quitar la barrera implícita de ciertas directivas. Notemos que no podemos usarla con `parallel`. Es decir, la barrera implícita de `parallel` es inalterable.  
  
Comenzamos ahora con el estudio de todas las cláusulas en negrita de la tabla superior:

# num_threads
