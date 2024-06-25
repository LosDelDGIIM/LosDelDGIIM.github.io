# Arquitectura de Computadores. Examen de teoría del Tema 2.

***

- **Asignatura:** Arquitectura de Computadores.
- **Curso Académico:** Desconocido.
- **Grado:** Desconocido.
<!--- **Grupo:** Único.-->
- **Profesor:** Mancia Anguita López.
- **Descripción:** Examen de teoría del Tema 2.
<!--- **Fecha:** 17 de abril de 2024.-->
- **Duración:** 40 minutos.

***

### Ejercicio 1.
¿Qué tipo de herramientas de programación paralela requieren, en general, un menor esfuerzo por parte del programador?

- a) Compiladores paralelos.
- b) Lenguajes paralelos.
- c) APIs basadas en funciones y directivas del compilador.
- d) APIs basadas en funciones.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'a':  
    Los compiladores paralelos convierten directamente los códigos secuenciales en códigos paralelos, por lo que no requieren nada de esfuerzo por parte del programador, a diferencia del resto de opciones.</p>
</details>

### Ejercicio 3.
Después de analizar un programa se han obtenido las 6 tareas cuyo grafo de dependencias muestra la figura. Si el tiempo de ejecución secuencial es de 5 segundos y se quiere ejecutar en un multiprocesador de 4 núcleos en el que podemos despreciar el tiempo de sobrecarga, ¿cuál sería su tiempo de ejecución paralelo?

![test](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/AC/Exámenes/img/GrafoT2.png)
 
- a) 3.75 s.
- b) 3.85 s.
- c) 4 s.
- d) 4.25 s.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'c':  
    Si ejecutamos el programa en paralelo, primero tenemos que ejecutar en un procesador la tarea del 20%, luego ejecutamos en dos procesadores de forma paralela las tareas del 25% y 10%. Tras esto, podemos ejecutar las dos tareas del 10% en dos procesadores y por último, la tarea final del 25%. Esto nos da un tiempo de CPU del $20 + max\{10,25\} + 10 + 25 = 80$ %. Mediante una sencilla regla de 3, si para el 100% del programa se tardaban 5 segundos, para el 80% del programa se tardan 4 segundos, luego la respuesta correcta es la opción 'c'.</p>
</details>

### Ejercicio 5.
Se pude generar una imagen fractal calculando el color que debe tener cada uno de los píxeles que la componen. El cálculo del color de cada píxel depende de la posición `(i,j)` del píxel dentro de la imagen, pero conlleva una carga computacional alta y variable para cada uno. ¿Qué estructura de algoritmo paralelo sería la más acertada para repartir el cálculo de todos los píxeles de la imagen entre los nodos de un multicomputador?

- a) Segmentación o flujo de datos.
- b) Maestro-esclavo.
- c) MPMD.
- d) Divide y Vencerás.

<details>
  <summary>Respueta</summary>
  <p>
    La opción 'c' no es una estructura de algoritmo paralelo. Por lo que nos dice el enunciado, no es posible realizar una estrategia Divide y Vencerás como propone la opción 'd'.</p>
</details>

### Ejercicio 6.
Indique en el siguiente supuesto cuál de las respuestas representa la solución al problema. Suponga un bucle en el que no se conoce el número de iteraciones a ejecutar y se sabe que la carga de cada iteración depende de datos de entrada que provocarán que el cómputo para cada iteración sea más o menos intenso. Indique qué mecanismos deberá implementar el programa para adaptarse al problema conociendo que el número de procesadores disponibles es conocido y son heterogéneos.

- a) Equilibrio de carga y asignación dinámica.
- b) Asignación dinámica explícita sin balanceo de carga.
- c) Asignación estática y descomposición uniforme sin equilibrio de carga.
- d) Equilibrado de carga y una asignación estática.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'a':
    Necesitamos asignación dinámica porque no sabemos cuánto se tarda en cada caso, y siempre tiene que haber equilibrio de carga para un buen reparto entre las unidades de cómputo.</p>
</details>

### Ejercicio 9.
Se desea reapartir los datos de una matriz entre los diferentes procesadores que forman parte de un multiprocesador que ejecuta una aplicación paralela, asignando partes de igual tamaño a cada procesador. El tamaño de la matriz es divisible entre el número de procesadores. ¿Qué operación de comunicación colectiva se debería implementar para que al final la matriz esté distribuida?

- a) Todos difunden.
- b) Reducción.
- c) Dispersión.
- d) Todos combinan.

<details>
  <summary>Respueta</summary>
    <p>La respuesta correcta es la opción 'c'. Es la única que realiza una comunicación uno-a-todos, que es lo que necesitamos.</p>
</details>

### Ejercicio 10.
En el proceso de paralelización de un programa, la fase de descomposición en tareas incluye:

- a) Buscar tareas que sean independientes y establcer un diagrama de dependencias entre ellas donde se establezca el orden de ejecución entre ellas.
- b) La implementación de la solución paralela que mejor se ajuste a nuestro problema y a la máquina paralela donde se vaya a ejecutar.
- c) La asignación de tareas a hebras o procesos y su mapeo a núcleos de procesamiento.
- d) Ninguna otra respuesta es correcta.

<details>
  <summary>Respueta</summary>
    <p>La respuesta correcta es la opción 'a'.</p>
</details>


