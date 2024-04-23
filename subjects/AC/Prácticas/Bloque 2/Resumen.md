# Arquitectura de Computadores. Sesión II de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Arquitectura de Computadores.  
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen de la Sesión II de Prácticas.

Esta sesión práctica está orientada al manejo de las cláusulas, las cuales nos permiten modfiicar o añadir funcionalidades a las directivas ya vistas en la [Sesión I de Prácticas](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/AC/Pr%C3%A1cticas/Bloque%201/Resumen.md).  
Además, comentaremos el ámbito que por defecto se les da a las variables, ya que nos ayudará a entender la finalidad y uso de ciertas cláusulas.

# Introducción
Las cláusulas nos permiten ajustar el comportamiento de las directivas. Su sintaxis suele ser la siguiente:
```c
#pragma omp [directiva] [cláusula]
```
Son opcionales (es decir, podemos usar directivas sin usar cláusulas). Además, al usar varias cláusulas, podemos elegir separarlas o no con comas. Es decir, las dos figuras de código siguientes son sintácticamente correctas:
```c
#pragma omp parallel num_threads(8) if(N>20)
```
```c
#pragma omp parallel num_threads(8), if(N>20)
```
Como vemos, la sintaxis de una cláusula es similar a la de una función, al recibir parámetros (o condiciones, en el caso de `if`, que no deja de ser un parámetro booleano).  
  
Hay directivas que aceptan cláusulas y directivas que no:

### Directivas que no acepta cláusulas
- `master`.
- Las de sincronización y/o consistencia: `critical`, `barrier`, `atomic` y `flush` (recordamos que no hemos visto `flush`).
- `ordered` (no se ha visto).
- `threadprivate` (tampoco se ha visto).

### Directivas que aceptan cláusulas
- `parallel`.
- Las de trabajo compartido: `DO/for`, `sections`, `single` y `workshare` (aunque no veremos ni `DO` ni `workshare`).
- Las directivas que combinan `parallel` con cualquiera de trabajo compartido.

A continuación, mostramos una tabla resumen de las cláusulas que acepta cada directiva:
| Tipo        | Cláusula            | parallel | DO/for | sections | single | parallel DO/for | parallel sections |
|-------------|---------------------|----------|--------|----------|--------|-----------------|-------------------|
| Control     | **if** (1)          | X        |        |          |        | X               | X                 |
| nº threads  | **num_threads** (1) | X        |        |          |        | X               | X                 |
|             |                     |          |        |          |        |                 |                   |
| Control     | **shared**          | X        |        |          |        | X               | X                 |
| del         | **private**         | X        | X      | X        | X      | X               | X                 |
| ámbito      | **lastprivate**     |          | X      | X        |        | X               | X                 |
| de las      | **firstprivate**    | X        | X      | X        | X      | X               | X                 |
| variables   | **default** (1)     | X        |        |          |        | X               | X                 |
|             | **reduction**       | X        | X      | X        |        | X               | X                 |
|             |                     |          |        |          |        |                 |                   |
| Copia de    | copyin              | X        |        |          |        | X               | X                 |
| valores     | **copyprivate**     |          |        |          | X      |                 |                   |
|             |                     |          |        |          |        |                 |                   |
| Planifica   | schedule (1)        |          | X      |          |        | X               |                   |
| iteraciones | ordered (1)         |          | X      |          |        | X               |                   |
|             |                     |          |        |          |        |                 |                   |
| No espera   | nowait              |          | X      | X        | X      |                 |                   |

- Donde las cláusulas en negrita son las que estudiaremos en esta práctica.  
- Las cláusulas con un '(1)' sólo pueden usarse una vez en la directiva que nos encontremos. Por ejemplo, no podríamos hacer un `parallel num_threads(4) num_threads(9)`, pero sí un `parallel private(x) private(y)`.  
- Notamos ya que las cláusulas dependen de la directiva: hay directivas que no aceptan determinadas cláusulas, por ejemplo, `for` no admite la directiva `num_threads`.  
- `nowait` es una cláusula que no veremos ahora. Sin embargo, es de utilidad saber que su función es quitar la barrera implícita de ciertas directivas. Notemos que no podemos usarla con `parallel`. Es decir, la barrera implícita de `parallel` es inalterable.
Notemos que las cláusulas que adminten las directivas combinadas `parallel DO/for` o `parallel sections` son el resultado de aplicar un `OR` a las cláusulas de `parallel` y `for` o `sections`.

# Ámbito de variables por defecto
Por defecto, las variables creadas fuera de una región afectada por `parallel` (y las dinámicas) son **variables compartidas** por todas las hebras, de forma que pueden llegar a darse condiciones de carrera si el acceso a estas no se realiza de forma adecuada.  
Por otra parte, las declaradas dentro de una región `parallel` son **privadas**. Esto es, cada hilo creará una dirección de memoria distinta para la variable del mismo nombre:
```c
int N = 20;
#pragma omp parallel
{
    int n_hebra = omp_get_thread_num();
    
    #pragma omp parallel for
    for(int i = 0; i < N; i++){
        printf("Soy la hebra %d\n", n_hebra);
    }
}
```
En este ejemplo, `N` es una **variable compartida**: está declarada dentro de la región `parallel`. Por tanto, cuando una hebra acceda a la variable `N`, accederá a la misma variable que cuando otra hebra accede a la variable `N`.  
Por otra parte, la variable `n_hebra` es una **variable privada**: está declarada dentro de la región `parallel`. De esta forma, cuando una hebra acceda o modifique la variable `n_thread`, modificará su propia variable (cada hebra contará con una variable `n_thread` distinta en su pila). De modo que la ejecución de distintas hebras no influye sobre el valor de la variable `n_threads`.  
  
Ante estas dos reglas comentadas aparecen dos excepciones:
- Los índices de los bucles `for` asociados a una directiva `for` se hacen privados (lo hace el compilador) por defecto. 
- Si declaramos una variable dentro de una región afectada por `parallel` que sea `static`, esta será una variable compartida. Notemos que este tipo de variables no se almacena en la pila, luego tiene sentido este funcionamiento.
```c
int i, j;

#pragma omp parallel for
for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
        // ...
    }
}
```
En el ejemplo superior, estamos paralelizando el bucle `for` que itera sobre `i`. Tanto `i` como `j` están declaradas fuera de la región `parallel`, luego podríamos pensar que son ambas variables compartidas por todas las hebras. Sin embargo, debido a la primera excepción, la variable `i` será una variable privada.  
*Nota:* Observemos que la variable `j` sigue siendo una variable pública, ya que su bucle `for` asociado no está siendo paralelizado.  
  
A lo largo de la práctica, observaremos cómo las cláusulas `private`, `firstprivate` y `lastprivate` nos ayudan a modificar el ámbito de las variables. Así mismo, pueden usarse de forma redundante (hacer compartida una variable compartida) para mejorar la legibilidad de los códigos paralelos.  
***
  
Comenzamos ahora con el estudio de todas las cláusulas en negrita de la tabla superior:

# if(expresion)
Si `expresion` se evalúa como `true`, hace que el código de la región afectada por `parallel` se ejecute en paralelo. Si la expresión se evalúa como `false`, la región paralela se ejecutará en serie (por un único subproceso).
```c
int N;
// ...
#pragma omp parallel for if(N>20)
for(int i = 0; i < N; i++){...}
```
De esta forma, el bucle `for` sólo se paralelizará si el valor de la variable `N` es mayor que 20.  
Esta funcionalidad nos permite evitar las sobrecargas que se generan al paralelizar código donde no se aproveche bien la paralelización (por ejemplo, un bucle de pocas iteraciones).  
  
*Sólo puede haber una cláusula `if`*

# num_threads(n)
Tiene la misma funcionalidad que la función `omp_set_num_threads`. Es decir, establece el número de hebras en la región paralela afectada por su `parallel` asociado.
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

# shared(list)
Donde `list` es una lista de variables (puede ser una o varias variables separadas por comas), especifica que una o varias variables deben compartirse entre todas las hebras.  
Debemos tener cuidado al usarlo cuando una hebra vaya a leer de una variable compartida lo que otra hebra escribe en dicha variable. Por ejemplo:
```c
int N = 20;
#pragma omp parallel for shared(N)
for(int i = 0; i < N; i++){...}
```

# private(list)
Donde `list` es una lista de variables, especifica que cada hebra debe tener su propia instancia de cada una de las variables de `list`.  
Podemos usarla por ejemplo, a la hora de calcular la suma de los elementos de un array:
```c
int* a;
int N;
// ...
int suma, sumalocal = 0;
#pragma omp parallel private(sumalocal)
{
    sumalocal = 0;
    
    #pragma single
    suma = 0;

    #pragma omp for
    for(int i = 0; i < N; i++){
        sumalocal += a[i];
    }
    
    #pragma critical
    suma += sumalocal;
}
```
De esta forma, cada hebra tiene su propia variable `sumalocal`, que combinamos al final del bucle en la variable compartida `suma`.  
  
El valor de entrada y de salida está indefinido. Esto es:
- Cada variable privada que se use en una hebra va a ser una nueva posición de memoria. Por tanto, no podemos esperar que cada variable privada se encuentre inicializada al valor que incializamos su variable antes de la región paralela. En este caso, no podemos asumir que `sumalocal` sea 0 al inicio de la región paralela, por lo que inicializamos su valor dentro de esta.  
- Así mismo, tampoco podeos suponer que al final de una región `parallel` la variable que se usó como privada tenga algún valor (ni el que tenía antes de la región ni cualquiera que adopte una variable privada dentro de la región).  
  
Por todo esto las cláusulas `firstprivate` y `lastprivate` son relevantes.  
Podrá parecer que con las cláusulas `firstprivate` y `lastprivate` la cláusula `private` carece de uso. Sin embargo, habrá ocasiones donde nos interese usarla en lugar de las otras dos.

# lastprivate(list)
Realiza la misma funcionalidad que `private`, pero en este caso a la variable declarada antes de la región paralela se le asignará tras la finalización de esta:
- El valor de la variable privada homónima de la última iteración en el caso de una directiva `for`.
- El valor de la variable privada homónima del último `section` en el caso de una directiva `sections`.
Por ejemplo:
```c
int a;
#pragma omp parallel for lastprivate(a)
for(int i = 0; i < N; i++){
    printf("%d\n", v[i]);
    a = v[i];
}
// ...
```
En este caso, tras la región `parallel`, tendremos que `a` valdrá `v[N-1]`.
```c
int a;
#pragma omp parallel sections lastprivate(a)
{
    #pragma omp section
    {
        a = (b+c)/2;
        // ... (no se modifica a)
    }
    
    #pragma omp section
    {
        a = (b-c)/2;
        // ... (no se modifica a)
    }
}
// ...
```
En este caso, tras la región `parallel`, tendremos que `a` valdrá `(b-c)/2`.

# firstprivate(list)
Realiza la misma funcionalidad que `private`, pero en este caso todas las variables privadas homónimas que se creen a partir de la ya declarada antes de la región paralela serán inicializadas al valor de la variable de fuera de la región paralela. Por ejemplo:
```c
int* a;
int N;
// ...
int suma, sumalocal = 0;
#pragma omp parallel firstprivate(sumalocal)
{
    #pragma single
    suma = 0;

    #pragma omp for
    for(int i = 0; i < N; i++){
        sumalocal += a[i];
    }
    
    #pragma critical
    suma += sumalocal;
}
```
Que es una mejora del código de ejemplo de la cláusula `private`.  
  
Esta directiva realiza una *difusión*: desde el hilo `master`, difundimos el valor de la variable compartida a todas las privadas.

# default(shared | none)
Esto es, los únicos parámetros que acepta `default` son `shared` y `none`.
- `shared` (la opción por defecto): cualquier variable de una región paralela se tratará como si se especificara con la cláusula `shared`.
- `none`: las variables usadas en una región paralela deberán verificar una de las siguientes condiciones para no obtener errores en el compilador:
    - Aparecen en alguna cláusula `private`, `shared`, `reduction`, `firstprivate` o `lastprivate`.
    - La variable se declara dentro de la construcción paralela.
    - La variable es `threadprivate`.
    - La variable es `const`.
    - La variable es la variable de contro de un bucle `for` que sigle inmediatamente a una directiva `for` o `parallel for` y la referencia de la variable aparece dentro del bucle.
  
*Sólo puede haber una cláusula `default`*.

# reduction(operator : list)
Donde `operator` indica la operación que se va a realizar a las variable de `list` al final de la región paralela y `list` es una lista de variables.  
`reduction` realiza la operación indicada sobre todas las variables que tengan un nombre igual a alguna de las variables especificadas en `list` (esto es, sobre todas las privadas de cada hebra y sobre la que teníamos antes de la región paralela).  
Lo que hará `reduction` será crear las variables privadas con un valor inicial (ver siguiente tabla), ejecutar el código y posteriormente realizar la operación de combinación sobre las variables indicadas. 
  
| Operador | Valor inicial | Operador | Valor inicial |
|----------|---------------|----------|---------------|
| +        | 0             | \|       | 0             |
| -        | 0             | ^        | 0             |
| *        | 1             | &&       | 1             |
| &        | ¬0 (bits a 1) | \|\|     | 0             |
  
Veamos un ejemplo:
```c
int suma = 4;
#pragma omp parallel for private(suma) reduction(+:suma)
for(int i = 0; i < N; i++){
    suma += v[i];
printf("El valor de la suma es: %d\n", suma);
```
En este caso, si los `N` primeros elementos de `v` suman `m`, se imprimirá en pantalla $m+4$, ya que se obtendrá la suma de todos los `N` primeros elementos de `v` más el valor que la variable `suma` tenía al inicio (4).  
Debemos tener cuidado con esta funcionalidad, sobre todo ante la siguiente casuística:
```c
int mult = 0;
#pragma omp parallel for private(suma) reduction(*:suma)
for(int i = 0; i < N; i++){
    mult *= v[i];
}
printf("El valor de la multiplicacion es: %d\n", mult);
```
En este caso, se imprimirá `0`, ya que también se multiplica por el valor de la variable `mult` de antes de la región paralela.  
  
La cláusula `reduction` es un ejemplo de *comunicación colectiva todos a uno*.

# copyprivate(list)
Donde `list` es una lista de variables, especifica que todas las variables de la lista deben copiarse en todas las variables privadas homónimas al finalizar la región `single` asociada. Se trata de una *difusión* de datos. Resulta últi para la lectura de entradas:
```c
#pragma omp parallel
{
    int a;
    #pragma omp single copyprivate(a)
    {
        printf("Valor de inicializacion: ");
        scanf("%d", &a);
    }
    
    #pragma omp for
    for(int i = 0; i < N; i++){
        v[i] = a;
    }
}
```
De esta forma, todas las componentes del vector `v` se inicializan a la variable privada `a`, que tras la región del `single` queda su valor igual en todas las variables privadas.
