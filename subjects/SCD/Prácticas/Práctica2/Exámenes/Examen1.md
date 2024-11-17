# SCD. Examen de las Prácticas I y II.

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
- Crear una variable `n_producidos`.
- Cuando un productor produzca un dato, deberá incrementar la variable `n_producidos`.
- Crear una hebra impresora, que esperará a que la despierten, imprima en pantalla el valor de `n_producidos` y se duerma.
- En la quinta iteración de cada productor se debe despertar a la hebra impresora.

# Ejercicio 2.
A partir de su solución del problema de los fumadores realizada mediante **monitores**, se pide:
- Crear un cuarto fumador, el cual necesitará el mismo ingrediente que el primer fumador para fumar.
- Cuando el estanquero produzca dicho ingrediente, decidirá aleatoriamente a cual de los dos fumadores despertar.
- Crear una hebra verificadora, cuyo código será un bucle indefinido que llamará al procedimiento `verificacion` del monitor.
- Añada la variable `ini_verif` inicializada a `false`.
- Implemente el procedimiento `verificacion`, que bloqueará a la hebra si `ini_verif = false`, imprimirá el número taotal de impresiones del fumador 1 y del nuevo fumador (que compite con el 1), y poner `ini_verif` a `false`.
- El estanquero debe poner `ini_verif` a `true` después de producir el ingrediente 1 (el ingrediente por el cual tenemos dos fumadores) doce veces, así como desbloquear a la hebra que espera por `ini_verif`.
