# Arquitectura de Computadores. Examen del Bloque Práctico II.

***

- **Asignatura:** Arquitectura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
<!--- **Grupo:** .-->
- **Profesor:** Mancia Anguita López.
- **Descripción:** Examen del bloque práctico 2.
<!--- **Fecha:** 22 de mayo de 2024.-->
- **Duración:** 30 minutos.

***

### Ejercicio 5.
¿Con qué directiva se debe usar la cláusula `copyprivate`?

- a) `single`.
- b) `atomic`.
- c) Con cualquier directiva.
- d) `master`.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'a':  
    La cláusula 'copyprivate' sólo puede usarse con la directiva 'single'.</p>
</details>

### Ejercicio 6.
¿Cuál de las siguientes cláusulas implementa una función de comunicación colectiva?

- a) `reduction`.
- b) Todas las respuestas son correctas.
- c) `copyprivate`.
- d) `firstprivate`.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'b':  
    'reduction' realiza una comunicación todos-a-uno, 'copyprivate' y 'firstprivate' realizan uno-a-todos, la primera desde la hebra que ejecuta el 'single' asociado y la segunda desde la hebra master.</p>
</details>

### Ejercicio 7.
Dado el siguiente fragmento de programa, ¿cuál es el valor de la variable `b` al salir de la región paralela?
```c
int i, a, b;
a = 2;
b = 2;
#pragma omp parallel for firstprivate(a,b) lastprivate(b)
for(i = a; i<12; i++)
    b = i;
return b;
```

- a) 12.
- b) Indeterminado.
- c) 2.
- d) Ninguno de los anteriores.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'd':  
    Debido a la cláusula 'lastprivate', el valor de la variable 'b' al final de la región paralela se corresponde con el valor que adquiere en la última iteración del bucle 'for'. En esta, la variable 'i' adopta el valor $11$, luego tendremos que 'b' vale $11$.</p>
</details>

// TODO: Hacer el 8

### Ejercicio 9.
En el siguiente código:
```c
int i, b[5];
for(i=0; i < 5; i++)
    b[i] = 0;
    
#pragma omp parallel
{
    int j = 2;
    #pragma omp for default(shared)
    for(i=0; i < 5; i++)
        b[i] = i + j;
}
```
- a) Habría un error de compilación porque el ámbito de las variables `i` y `b` no está definido.
- b) Habría un error de compilación porque la cláusula `default` no es válida para `#pragma omp for`.
- c) Habria que cambiar `default(shared)` por `default(none)` para que se pudiese compilar.
- d) No habría errores de compilación.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'b':  
    La cláusula 'default' sólo es válida para '#pragma omp parallel' o cualquier directiva combinada con esta. Suponiendo que compila bien, la opción 'a' es falsa, ya que las variables 'i' y 'b' por defecto son compartidas. La opción 'c' también es falsa, suponiendo que compila bien, habría que especificar si las variables 'i' o 'b' son privadas o compartidas.</p>
</details>

### Ejercicio 10.
Dada la siguiente porción de código:
```c
int i, j;
double **M, *v1, *v2;
// Inicializaciones M y v1 ...
for(i=0; i < N; i++){
    #pragma omp parallel for
    for(j=0; j < N; j++)
        #pragma omp atomic
        v2[i] += M[i][j] * v1[j];
}
```
Suponiendo que todas las posiciones de `M` y `v1` se inicializan a 1, debes responder a dos cuestiones, la primera es si este código paralelo es eficiente y la segunda qué contendrá el vector `v2` al terminar la ejecución.

- a) El código **no es eficiente** y el vector `v2` contiene el resultado **correcto** de multiplicar la matriz `M` ($N\times N$) por el vector `v1` ($N\times 1$).
- b) El código **es eficiente** y el vector `v2` contiene el resultado **correcto** de multiplicar la matriz `M` ($N\times N$) por el vector `v1` ($N\times 1$).
- c) El código **es eficiente** y el vector `v2` contiene un resultado **indefinido**.
- d) El código **no es eficiente** y el vector `v2` contiene un resultado **indefinido**.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'a':  
    El código no es eficiente, ya que en cada iteración del bucle exterior, OpenMP crea y destruye las hebras para la ejecución del bucle interior. Además, produce un resultado correcto, ya que el acceso a variables compartidas (como 'v2' o 'i') se hace o bien con el uso de la directiva 'atomic' o bien fuera de la región paralela.</p>
</details>

