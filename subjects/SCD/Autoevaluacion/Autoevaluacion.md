<br>

# SCD. Preguntas para la autoevaluación del Tema 1.

***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Manuel Isidoro Capel Tuñón.
- **Descripción:** Este documento tiene como objetivo servir para estudiar la asignatura de Sistemas Concurrentes y Distribuidos. En él, se puede encontrar una corta autoevaluación formada por unas 20 preguntas tipo test.
***

1. ¿Qué significa "irrepetibilidad de las secuencias de instrucciones" en la programación concurrente?
    - ( ) La velocidad de ejecución determina la secuencia de instrucciones.
    - (x) Los programas concurrentes generan muchas intercalaciones de instrucciones posibles, por lo que es poco probable que se repitan caminos.
    - ( ) Los programas concurrentes nunca tienen errores.
    - ( ) Dos ejecuciones seguirán probablemente el mismo camino.
    - ( ) Los procesos siguen siempre la misma secuencia de ejecución.

2. ¿Qué reto presentan las trazas de ejecución de los programas concurrentes?
    - (x) Las trazas no pueden utilizarse con fines de depuración.
    - ( ) Las trazas garantizan que se producirán errores.
    - ( ) Generan numerosas secuencias de intercalación posibles, lo que complica la predicción.
    - ( ) Siempre conducen a un punto muerto.
    - ( ) Siguen un patrón predecible y repetible.

3. ¿Qué son los "errores transitorios" en el contexto de los programas concurrentes?
    - ( ) Errores que nunca se producen en los programas concurrentes.
    - (x) Errores que aparecen en algunas ejecuciones pero no en otras, lo que dificulta su detección.
    - ( ) Errores que son fáciles de detectar y solucionar.
    - ( ) Errores que aparecen siempre en la misma ejecución.
    - ( ) Errores que se producen aleatoriamente y no tienen solución.

4. ¿Por qué es difícil depurar programas concurrentes?
    - (x) Debido a la imprevisibilidad de las secuencias de ejecución y a la posibilidad de que haya trazas diferentes en cada ejecución.
    - ( ) Debido a la previsibilidad de las secuencias de ejecución.
    - ( ) Porque los errores transitorios aparecen en cada traza.
    - ( ) Porque los programas concurrentes siempre se ejecutan sin errores.
    - ( ) La depuración de programas concurrentes no difiere de la de los secuenciales.

5. ¿Cuál de las siguientes es una solución para garantizar la corrección de los programas concurrentes?
    - ( ) Ignorar los errores transitorios porque ocurren raramente.
    - ( ) Utilizar la fuerza bruta para reejecutar el programa varias veces.
    - ( ) Se puede garantizar la corrección sin ningún método formal.
    - ( ) Confiar sólo en la comprobación manual de errores.
    - (x) Utilizar métodos formales basados en la lógica matemática para verificar la corrección.

6. ¿Qué es una traza en el contexto de la programación concurrente?
    - ( ) El historial de cómo se modifican las variables durante la compilación.
    - ( )  Una secuencia de operaciones atómicas de un único proceso.
    - (x) Una secuencia de estados del programa producidos por un intercalado específico de instrucciones.
    - ( ) Un registro de todos los errores en la ejecución de un programa.
    - ( ) La ejecución de un único proceso de forma aislada.

7. ¿Por qué es peligroso hacer suposiciones sobre la velocidad de ejecución de los procesos en los programas concurrentes?
    - ( ) Las suposiciones de velocidad siempre aumentan la eficacia del programa.
    - (x) Los procesos pueden no funcionar correctamente en diferentes plataformas si se hacen suposiciones sobre la velocidad de ejecución.
    - ( ) Los procesos más rápidos siempre garantizan mejores resultados del programa.
    - ( ) Siempre conduce a un mejor rendimiento en todas las plataformas.
    - ( ) La velocidad de ejecución es irrelevante para la programación concurrente.

8. ¿Qué es una "condición de carrera" en los programas concurrentes?
    - ( ) Cuando dos procesos se ejecutan siempre en un orden fijo y predecible.
    - (x) Cuando dos procesos acceden a variables compartidas en un orden impredecible en función de la velocidad de ejecución.
    - ( ) Una situación en la que el orden de ejecución de los procesos no afecta a la salida final del programa.
    - ( ) Una situación en la que dos procesos nunca interactúan con recursos compartidos.
    - ( ) Un escenario en el que la velocidad de ejecución es siempre constante.

9. ¿Qué efecto pueden tener las condiciones de carrera en los programas concurrentes?
    - ( ) Facilitan la depuración debido a su comportamiento coherente.
    - ( ) Producen resultados predecibles y correctos.
    - ( ) Reducen el riesgo de errores en el programa.
    - ( ) Garantizan que todos los procesos se ejecuten de forma predecible.
    - (x) Producen resultados impredecibles o incorrectos según el orden de ejecución de los procesos.

10. ¿En qué tipo de sistema es crítica la velocidad y el orden de ejecución de los procesos?
    - ( ) Sistemas operativos de propósito general.
    - (x) En los sistemas en tiempo real, donde la velocidad y el orden de ejecución son críticos.
    - ( ) Sólo sistemas distribuidos.
    - ( ) Sólo en sistemas "multicore"
    - ( ) En cualquier sistema con procesos concurrentes.

11. ¿Qué implica la "independencia de la velocidad del proceso" en la programación concurrente?
    - ( ) La velocidad de ejecución siempre determina la corrección del programa.
    - ( ) Los procesos más lentos garantizan una mayor estabilidad del programa.
    - ( ) La corrección del proceso debe depender de la velocidad relativa de los procesos.
    - ( ) Los procesos deben ejecutarse siempre lo más rápido posible.
    - (x) La corrección del proceso debe ser independiente de la velocidad de ejecución, evitando las condiciones de carrera.

12. ¿Qué importancia tiene la «hipótesis de progreso finito» en los programas concurrentes?
    - ( ) Garantiza que los procesos se completen siempre a la misma velocidad.
    - ( ) Permite que algunos procesos no terminen nunca sus tareas.
    - ( ) Sólo es aplicable a los programas secuenciales.
    - (x) Garantiza que todos los procesos completen la ejecución y progresen, evitando el bloqueo.
    - ( ) Permite que los procesos se detengan indefinidamente sin afectar a la corrección del programa.

13. ¿Qué es el "progreso global" en el contexto de la ejecución concurrente?
    - (x) Garantiza que al menos un proceso listo para ejecutarse llegue a ejecutarse, evitando el bloqueo.
    - ( ) Garantiza que ningún proceso pueda bloquear la ejecución de otro.
    - ( ) Requiere que todos los procesos se ejecuten al mismo tiempo.
    - ( ) Garantiza que todos los procesos terminen la ejecución inmediatamente.
    - ( ) Es específico sólo de los sistemas en tiempo real.

14. ¿Qué significa "progreso local" en la programación concurrente?
    - ( ) Una vez que un proceso comienza a ejecutarse, debe terminar todo el programa.
    - ( ) Una vez que un proceso empieza a ejecutar una sección de código, debe completarla sin interrupción.
    - ( ) Un proceso debe completar siempre todo el programa sin pausa.
    - (x) Un proceso puede detenerse a mitad de ejecución y reanudarse más tarde sin completar la sección actual.
    - ( ) Los procesos deben comunicarse con otros procesos para continuar la ejecución.

15. ¿Cómo evita la hipótesis del progreso finito el bloqueo en los programas concurrentes?
    - ( ) Limitando el número de procesos que pueden ejecutarse simultáneamente.
    - ( ) Garantizando que los procesos puedan detenerse en cualquier momento.
    - ( ) Poniendo en pausa algunos procesos para permitir que otros terminen primero.
    - (x) Garantizando que todos los procesos acaben progresando, evitando que se atasquen.
    - ( ) Imponiendo límites temporales estrictos a la ejecución de los procesos.

16. ¿Cuál es la definición de "propiedad de vivacidad"?
    - ( ) Una propiedad que define cuántos procesos pueden ejecutarse simultáneamente.
    - ( ) Una propiedad que garantiza que los procesos pueden pausarse indefinidamente.
    - ( ) Una condición que sólo se aplica a los programas secuenciales.
    - ( ) Una condición que debe cumplirse en cada instante de la ejecución del programa.
    - (x) Una condición que establece que algo bueno debe suceder eventualmente en el futuro.

17. ¿Qué significa el triple `{P}C{Q}` en el contexto de la lógica de Hoare?
    - ( ) Garantiza que en la ejecución de varios procesos contenidos `C` no existen interferencias.
    - ( ) `P` y `Q` son variables que representan el tiempo de ejecución de `C`.
    - (x) Si el programa `C` comienza en un estado en el que `P` es verdadero, entonces `Q` será verdadero después de que `C` termine de ejecutarse.
    - ( ) Si el programa `C` se ejecuta, siempre terminará.
    - ( ) Si el programa `C` se ejecuta con la máxima velocidad, `P` siempre será igual a `Q`.

18. ¿Cuál es el principal reto de aplicar la lógica de Hoare a los programas concurrentes?
    - (x) La interferencia entre procesos de ejecución concurrente complica el razonamiento.
    - ( ) No puede manejar programas sin memoria compartida.
    - ( ) Es difícil definir precondiciones y postcondiciones para cada proceso.
    - ( ) La lógica de Hoare requiere un número infinito de trazas de ejecución para verificar la corrección.
    - ( ) La lógica de Hoare sólo es aplicable a los programas secuenciales, no a los concurrentes.

19. ¿Cuál es la principal característica de la regla de no interferencia de la lógica de Hoare para programas concurrentes?
    - ( ) Sólo se aplica a los programas secuenciales, no a los concurrentes.
    - (x) Garantiza que dos procesos no interfieran entre sí en sus precondiciones y postcondiciones cuando se ejecutan simultáneamente.
    - ( ) Garantiza que cada proceso termina de ejecutarse antes de que comience el siguiente.
    - ( ) Permite que los procesos se ejecuten sin sincronización y sigue garantizando la corrección.
    - ( ) Garantiza que todos los procesos accedan a los recursos compartidos al mismo tiempo.

20. En la lógica de Hoare, ¿qué se necesita para verificar la corrección de una composición concurrente de procesos?
    - ( ) Los procesos deben ejecutarse secuencialmente, sin solapar instrucciones.
    - (x) Las precondiciones y postcondiciones de los procesos deben combinarse, y ningún proceso debe invalidar las afirmaciones de los demás.
    - ( ) El sistema debe probarse con todas las configuraciones de hardware posibles para garantizar su corrección.
    - ( ) Cada proceso debe tener su propio espacio de memoria independiente.
    - ( ) La composición sólo debe implicar a un único proceso a la vez.
