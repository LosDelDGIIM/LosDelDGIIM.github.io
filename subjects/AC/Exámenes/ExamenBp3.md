# Arquitectura de Computadores. Examen del Bloque Práctico III.

***

- **Asignatura:** Arquitectura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
<!--- **Grupo:** .-->
- **Profesor:** Mancia Anguita López.
- **Descripción:** Examen del bloque práctico 3.
- **Fecha:** 22 de mayo de 2024.
- **Duración:** 30 minutos.

***

### Ejercicio 1.
Indica cómo se establecería el valor de la variable de control `thread_limit_var` a un valor de 8 utilizando una variable de entorno:

- a) `export OMP_THREAD_LIMIT=8`.
- b) `export THREAD_LIMIT_VAR=8`.
- c) `export NTHREADS_VAR=8`.
- d) `export OMP_NUM_THREADS=8`.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'a':  
    Las variables de entorno de la API OpenMP comienzan todas por 'OMP_'. Además, la opción 'd' se corresponde con la variable de entorno asociada a la variable de control 'nthreads_var'.</p>
</details>

### Ejercicio 2.
¿Qué función de OpenMP permite obtener el tiempo transcurrido del reloj en segundos?

- a) `clock_gettime()`.
- b) `omp_get_time()`.
- c) `omp_get_wtick()`.
- d) `omp_get_wtime()`.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'd':  
    La opción 'a' no es una función de OpenMP y la opción 'b' no existe. Nos quedamos con la opción 'd' y con la opción 'c'. La opción 'd' hace lo que nos pide la pregunta según la documentación, mientras que la opción 'c' nos devuelve el tiempo transcurrido del reloj en ticks.</p>
</details>

### Ejercicio 3.
Indique cuál de las siguientes afirmaciones sobre el número de threads que se utilizan en una región paralela OpenMP es cierta:

- a) Si el resultado de evaluar la cláusula `if` es positivo se utiliza una única thread, independientemente de lo fijado por la cláusula `num_threads()`.
- b) El número de threads que fija la cláusula `num_threads` prevalece ante lo fijado por la función de entorno de ejecución `omp_set_num_threads()`.
- c) El número de threads que fija la función de entorno de ejecución `omp_set_num_threads()` prevalece ante cualquiera que sea el resultado de evaluar la cláusula `if`.
- d) En número de threads solo se puede fijar mediante la utilización de cláusulas y variables de entorno.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'b':  
    La opción 'a' es terriblemente falsa, si el resultado de evaluzar la cláusulas 'if' es positivo, se utiliza el número de hebras fijado por la cláusula 'num_threads()' o en su defecto por la variable de entorno 'nthreads_var'. La opción 'd' también es falsa, el número de threads puede fijarse también mediante la función 'omp_set_num_threads()'. Respecto a las opciones 'b' y 'c', el orden de preferencia para fijar el número de hebras es (de mayor a menor): la cláusula 'if', la cláusula 'num_threads()', la función 'omp_set_num_threads()' y la variable de entorno 'OMP_NUM_THREADS'.</p>
</details>

### Ejercicio 4.
Indique el tipo de reparto que se realiza en el siguiente código. Asuma inicialización de las variables `a` y `b` a valores estocásticos y `c` a valor cero.
```c
#pragma omp parallel for schedule(runtime) private(i,j)
for(i=0; i<2000; i++){
    if(i==0)
        omp_get_schedule(&kind, &chunk);
    for(j=0; j<2000; j++)
        c[i] = a[i][j] * b[j]
}
```

- a) El que indique la variable de control interno 'def-sched-var'.
- b) El que indique la variable de control interno 'run-sched-var'.
- c) El que indique la función de entorno 'omp_set_dynamic()'.
- d) El que indique la variable de control interno 'dyn-sched-var'.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'b':  
    Las opciones 'c' y 'd' no tienen nada que ver con el reparto de iteraciones en un bucle, sino con el ajuste dinámico de hebras que ejecutarán nuestro programa. Como tenemos la cláusula 'schedule' con el valor 'runtime', el reparto que se realizará será el de la opción 'b'. Para que la respuesta correcta hubiera sido la opción 'a', no se tendría que haber especificado la cláusula 'schedule'.</p>
</details>

### Ejercicio 5.
¿Cuál de las siguientes afirmaciones es verdadera?

- a) La cláusula `dynamic` siempre reparte iteraciones en bloques de 1.
- b) La cláusula `dynamic` no añade ninguna sobrecarga.
- c) La cláusula `dynamic` se suele usar cuando se desconoce el tiempo de cada iteración pero sí se conoce el número de hebras que ejecutan el bucle.
- d) La cláusula `dynamic` se suele usar cuando se desconoce el tiempo de cada iteración y no se sabe cuántas hebras ejecutan el bucle.

<details>
  <summary>Respueta</summary>
  <p>
    Las opciones 'a' y 'b' son trivialmente falsas, la cláusula 'dynamic' reparte iteraciones en bloques de tamaño variable, e introduce sobrecarga al tener que determinar en tiempo de ejecución la mejor forma de repartir las iteraciones entre las hebras.</p>
</details>

### Ejercicio 10.
¿Cuál de las siguientes funciones se utiliza en OpenMP para obtener el número de hebras que se están usando en ese momento en una región paralela?

- a) `omp_get_max_threads()`.
- b) `omp_set_num_threads()`.
- c) `omp_get_thread_num()`.
- d) `omp_get_num_threads()`.

<details>
  <summary>Respueta</summary>
  <p>La respuesta correcta es la opción 'd':  
    La opción 'b' no tiene sentido, la opción 'c' devuelve el identificador de la hebra que ejecuta la función, y la opción 'a' devuelve el número de hebras que ejecutarán la siguiente región paralela como máximo. La opción 'd' nos devuelve exactamente lo que pide la pregunta.</p>
</details>

