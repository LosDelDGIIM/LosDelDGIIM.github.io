# SCD. Examen de las Prácticas I y II.

**Autor**: Arturo Olivares Martos
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas + ADE.
- **Grupo:** 1.
- **Descripción:** Examen de las prácticas 1 y 2 de SCD.
- **Fecha:** 15 de noviembre de 2024.

***

# Ejercicio 1.
A partir de su solución de múltiples productores y consumidores con planificación FIFO realizada mediante **semáforos**, se pide:
- Cambiar las condiciones iniciales, para que tengamos:
    - 5 productores.
    - 3 consumidores.
    - El tamaño del buffer intermedio tenga 4 espacios.
    - Se produzcan un total de 45 datos.
- Se deberá contabilizar en todo momento (en una variable compartida `n_producidos`) el número de elementos total que se han producido hasta ese momento (por todas las hebras productoras).
- Se debe crear una nueva hebra `impresora`, que inicialmente estará bloqueada, y que es liberada una vez por cada hebra productora cuando produzca su quinto dato.
- Cuando un productor produce su quinto dato, después de añadir el elemento al vector, debe desbloquear a la hebra impresora y luego debe bloquearse hasta que lo libere la hebra impresora.
- La hebra impresora, una vez desbloqueada, imprime por pantalla el número de elementos producidos hasta ese momento (variable `n_producidos`), desbloquea al productor que la ha liberado y vuelve al principio de su ciclo a esperar ser liberada por otro productor.
- La hebra impresora debe finalizar correctamente.


***

Puede encontrar la solución al problema en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica2/Exámenes/Examen1Ej1.cpp).

# Ejercicio 2.
A partir de su solución del problema de los fumadores realizada mediante **monitores**, se pide:
- Crear un cuarto fumador (fumador 3), el cual necesitará el ingrediente 1 para fumar. Cuando el estanquero produzca dicho ingrediente, decidirá aleatoriamente a cual de los dos fumadores liberar.
- Crear una hebra `verificadora`, que será también un ciclo infinito y cuyo código solamente será un nuevo procedimiento del monitor llamado `verificacion`.
- El monitor tendrá una variable permanente `ini_verif` (booleada, inicializada a `false`).
- En el procedimiento `verificacion` se comprueba inicialmente el valor de `ini_verif`. Si es `false`, se bloquea la hebra verificadora. Si es `true` (o cuando es desbloqueada), se muestra por pantalla el número total de veces que han fumado los fumadores que comparten el ingrediente 1 (número de veces del fumador 1 y número de veces del fumador 3) y se pone `ini_verif` a `false`.
- Cada vez que el estanquero genera 12 veces el ingrediente 1, pone `ini_verif` a `true` y desbloquea a la hebra verificadora.

***

Puede encontrar la solución al problema en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica2/Exámenes/Examen1Ej2.cpp).