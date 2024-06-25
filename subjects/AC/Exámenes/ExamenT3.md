# Arquitectura de Computadores. Examen de teoría del Tema 3.

***

- **Asignatura:** Arquitectura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Examen de teoría del Tema 3.
- **Fecha:** 22 de mayo de 2024.
- **Duración:** 40 minutos.

***

### Ejercicio 1.
En un NUMA con 4 nodos de procesamiento (N0-N3) y con protocolo MSI basado en directorios distribuidos SIN difución, si un bloque está en estado modificado en la caché del nodo 2, ¿cuál de los siguientes es el contenido de la entrada del directorio e memoria para este bloque? (formato: `estado-c0c1c2c3`, conde `ci` es el bit de presencia de la caché `i`, `I` nota inválido, `V` Válido, y `M` nota Modificado)

- a) `I-0010`
- b) `M-0010`
- c) `V-0010`
- d) `I-0000`

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'a':  
    Al estar modificado en la caché 2, el bit de válido en dicha caché está activo. Además, las copias del mismo bloque en cualquier otra caché y en memoria deben estar inválidas, luego la respuesta correcta es 'I-0010'.</p>
</details>

### Ejercicio 2.
¿Cuál de los siguientes modelos de consistencia permite mejores tiempos de ejecución?

- a) modelo de consistenia de los procesadores ARMv7.
- b) modelo de consistenia que no garantiza los órdenes `W->W` y `W->R`.
- c) modelo de consistenia secuencial.
- d) modelo de consistenia de los procesadores de la línea x86 de Intel.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'a':  
    El modelo de consistencia de los procesadores ARMv7 es el que permite más relajaciones de los otros tres, tal y como se indica en la Sección 3.3.6. de los apuntes de teoría (ver https://losdeldgiim.github.io/subjects/AC/Temario/Temario.pdf), por lo que permite mejores tienes de ejecución.</p>
</details>

### Ejercicio 3.
Para un multiprocesador NUMA con 8 nodos con 16 GB de memoria por nodo se quiere implementar un protocolo para mantenimiento de coherencia basado en directorio distribuido (sin difusión) para el último nivel de cache y la memoria principal (MP). Suponiendo que un bloque de MP tiene 64 Bytes, ¿cuál es el número de entradas (filas) del subdirectorio de memoria de un nodo (del trozo del directorio de un nodo)?

- a) $2^{32}$.
- b) $2^{28}$.
- c) Ninguna de las otras respuestas es correcta.
- d) $2^6$.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'b':  
    El subdirectorio de memoria de cada nodo tiene tantas entradas por cada bloque de la memoria principal que se hospeda en dicho nodo. Por tanto, el ejercicio se reduce a calcular el número de bloques de memoria hospedados por un nodo. Tenemos una memoria de 16 GB = $2^{34}$ Bytes a repartir en bloques de 64 Bytes = $2^6$ Bytes, luego tenemos ($34 - 6 = 28$) $2^{28}$ bloques de memoria en cada nodo.</p>
</details>

### Ejercicio 4.
En un Numa con protocolo MSI sin difusión, relacionar la secuencia de paquetes de la figura con uno de los siguientes cambios de estado:

![test](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/AC/Exámenes/img/GrafoT3.png)

- a) Ninguna de las otras respuestas es correcta.
- b) Inicialmente el bloque está en estado `I` en la caché del procesador (nodo) solicitante, Válido en el directorio de memoria principal, y `S` en las cachés del resto de procesadores (nodos). Al terminar el acceso el bloque queda en estado `M` en la caché del solicitante, Inválido en el directorio de memoria principal y `I` en el resto de cachés.
- c) Inicialmente el bloque está en estado `S` en la caché del procesador (nodo) solicitante, Válido en el directorio de memoria principal, y `S` en las cachés del resto de procesadores (nodos). Al terminar el acceso el bloque queda en estado `M` en la caché del solicitante, Inválido en el directorio de memoria principal y `I` en el resto de cachés.
- d) Inicialmente el bloque está en estado `M` en la caché del procesador (nodo) solicitante, Inválido en el directorio de memoria principal, y `S` en las cachés del resto de procesadores (nodos). Al terminar el acceso el bloque queda en estado `M` en la caché del solicitante, Inválido en el directorio de memoria principal y `I` en el resto de cachés.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'c':  
    Como el nodo $S$ pide el paquete 'PtEx', sabemos que debe tener el bloque en estado 'S', al tenerlo válido pero no con acceso exclusivo al mismo, por lo que desacartamos las opciones 'b' y 'd'. Finalmente, vemos que la opción 'c' se corresponde con todo lo indicado en la figura.</p>
</details>

### Ejercicio 5.
¿Cuál de los siguientes códigos usaría para implementar un `unlock()` de un cerrojo con etiqueta para ARMv7?

- a)
```c
unlock(int *cl){
    dmb;    // macro que usa la instrucción máquina dmb de ARMv7
    (*cl) = 0;
}
```
- b) 
```c
unlock(int *cl){
    dmb;    // macro que usa la instrucción máquina dmb de ARMv7
    (*cl) = (*cl) + 1;
}
```
- c) 
```c
unlock(int *cl){
    (*cl) = (*cl) + 1;
    dmb;    // macro que usa la instrucción máquina dmb de ARMv7
}
```
- d) 
```c
unlock(int *cl){
    (*cl) = 0;
    dmb;    // macro que usa la instrucción máquina dmb de ARMv7
}
```

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'b':  
    Deseamos implementar un cerrojo con etiqueta, luego debemos incrementar el contador de liberación en vez de ponerlo a 0, descartando las opciones 'a' y 'd'. Ahora, debemos tener en cuenta que antes de abrir el cerrojo, debemos garantizar que se completaron todas las instrucciones de acceso a variables compartidas (ya que si no al abrir el cerrojo otro flujo de instrucciones procedería a acceder a ellas), por lo que debemos incluir la instrucción 'dmb' antes de liberar el cerrojo.</p>
</details>

### Ejercicio 6.
El orden en el que se ven las escrituras en una dirección de memoria en un NUMA con directorio distribuido coincide:

- a) Con el orden en el que llegan a la primera caché con copia del bloque.
- b) Con el orden en el que llegan al nodo origen o 'home' del bloque.
- c) Ninguna de las otras respuestas es correcta.
- d) Con el orden temporal en el que se han generado.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'b':  
    El nodo encargado de controlar las lecturas de dicha dirección de memoria es su nodo origen, por lo que tan pronto como lleguen a este las actualizaciones, este las reflejará en las peticiones de lectura que se hagan al bloque que contiene dicha dirección de memoria. </p>
</details>

### Ejercicio 7.
En un UMA con red bus y protocolo MSI, un controlador de cache al recibir del procesador de su nodo una lectura de una dirección de un bloque $B$ que tiene en estado `M`:

- a) No genera ningún paquete y el bloque continúa en estado `M`.
- b) Genera paquete de `PtLecEx(B)` y el bloque pasa a estado `S`.
- c) Genera paquete de `PtLec(B)` y el bloque pasa a estado `M`.
- d) Genera paquete de `PtLec(B)` y el bloque pasa a estado `S`.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'a':  
    Si el bloque se encuentra en estado 'M', entonces está válido en caché para leerlo, luego las opciones 'c' y 'd' no tienen sentido. Además, la opción 'b' no es ya que no tiene sentido invalidar la copia de $B$ en otras cachés, ya que al estar $B$ en estado 'M', sabemos ya que están invlidadas.</p>
</details>

### Ejercicio 8.
(A1) (se comparte enunciado y código con otra pregunta etiquetada con (A2))  
Se va a ejecutar en paralelo el código que se puede ver debajo. Se han añadido comentarios al código ((1), (2), (a), (b), (c) y (d)) que permiten identificar los accesos de lectura y escritura de los threads a memoria compartida:  
`(1) W(sm), (2) W(s2), (a) R(s2), (b) R(sm), (c) W(sm) y (d) R(sm)`  
```c
s2 = 0;
#pragma omp parallel num_threads(2)
{
    int i, smlocal=0, tid=omp_get_thread_num();
    if(tid == 0){
        for(i = 0; i < mitad; i++) smlocal += a[i];
        sm = smlocal;       // (1) W(sm)
        s2 = 1;             // (2) W(s2)
    }else{
        for(i = mitad; i < n; i++) smlocal += a[i];
        while(s2 == 0) {;}  // (a) R(s2)
        sum += smlocal;     // (b) R(sm)    (c) W(sm)
    }
    
    if(tid == 0) printf("%d \n", sm);   // (d) R(sm)
}
```  
¿Cuál de los siguientes órdenes de ejecución global de los accesos a memoria no será posible suponiendo que el código se ha ejecutado en un multiprocesador que relaja todos los órdenes del programa: `W->R`, `W->W`, `R->R` y `R->W`?

- a) `(a) (a) (2) (1) (a) (b) (c)`
- b) `(a) (2) (a) (c) (b) (1)`
- c) `(1) (2) (a) (b) (c)`
- d) `(a) (2) (b) (a) (c) (1)`

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'b':  
    Independientemente de los órdenes que relaje el programa, sabemos que las instrucciones de acceso a memoria a una variable no pueden adelantar a otra relativa a la misma variable. Por tanto, independientemente de los órdenes que se relajen, la instrucción '(d)' no puede adelantar a '(1)', ni la instrucción '(c)' puede adelantar a '(b)'. Sin embargo, vemos cómo en la opción 'b' la instrucción '(c)' adelanta a '(b)', cosa que no puede suceder.</p>
</details>

### Ejercicio 9.
Indicar cuál de las siguientes afirmaciones es correcta.

- a) Los núcleos SMT conmutan entre threads cada ciclo de reloj.
- b) Los núcleos SMT ejecutan instrucciones de distintos threads concurrentemente.
- c) Los núcleos SMT conmutan entre threads cada varios ciclos de reloj.
- d) Los núcleos SMT ejecutan instrucciones de distintos threads en paralelo.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'd':  
    Los núcleos SMT (Simultaneous Multithreading) no conmutan entre threads, sino que ejecutan dos threads a la vez, es decir, de forma paralela.</p>
</details>

### Ejercicio 10.
(A2) (se comparte enunciado y código con otra pregunta etiquetada con (A1))  
Se va a ejecutar en paralelo el código que se puede ver debajo (inicialmente `n=8`, `mitad=4`, `a[i]=i`). Se han añadido comentarios al código ((1), (2), (a), (b), (c) y (d)) que permiten identificar los accesos de lectura y escritura de los threads a memoria compartida:  
`(1) W(sm), (2) W(s2), (a) R(s2), (b) R(sm), (c) W(sm) y (d) R(sm)`  
```c
s2 = 0;
#pragma omp parallel num_threads(2)
{
    int i, smlocal=0, tid=omp_get_thread_num();
    if(tid == 0){
        for(i = 0; i < mitad; i++) smlocal += a[i];
        sm = smlocal;       // (1) W(sm)
        s2 = 1;             // (2) W(s2)
    }else{
        for(i = mitad; i < n; i++) smlocal += a[i];
        while(s2 == 0) {;}  // (a) R(s2)
        sum += smlocal;     // (b) R(sm)    (c) W(sm)
    }
    
    if(tid == 0) printf("%d \n", sm);   // (d) R(sm)
}
```  
¿Qué puede imprimir el código si se ejecuta en un multiprocesador que garantiza todos los órdenes de acceso a memoria excepto `W->R`? (las distintas posibilidades se han separado con comas)

- a) 28, 6, 0.
- b) 28.
- c) 28, 22, 6, 0.
- d) 28, 6.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'd':  
    Sabemos por el ejercicio 8 que '(d)' no puede adelantar a '(1)', luego lo que se imprima en '(d)' contendrá obligatoriamente la suma de la primera mitad del vector (6), luego las opciones 'a' y 'c' no son posibles, ya que contemplan al 0. Puede suceder que la hebra de tid 0 se ejecute complementamente antes que la otra, imprimiendo 6. Por otra parte, también puede suceder que se ejecute la hebra de tid 0, y que la otra se ejecute de forma que sume su aportación, imprimiendo 28. Descartamos la opción 'b' por ser la opción 'd' posible.</p>
</details>
