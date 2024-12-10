# SCD. Examen de la Práctica III.

**Autor**: Arturo Olivares Martos
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas + ADE.
- **Grupo:** 1.
- **Descripción:** Examen de las prácticas 1 y 2 de SCD.
<!--- **Fecha:** 15 de noviembre de 2024.
- **Profesor:** Ana María Sánchez López.--->

***

# Ejercicio

Se pide resolver el siguiente ejercicio utilizando directivas MPI vistas en clase. El juego consiste en comer tantas tartas como sea posible. El que más kg de tartas haya comido, gana. Contaremos con las siguientes restricciones:
1. Habrá solamente dos jugadores, Mario y Peach.
2. Habrá un NPC, Yoshi, que será el árbitro.
3. El proceso Yoshi se encargará:
    - Por un lado, de proveer tartas a cada equipo. Repondrá un máximo de $x$ veces.
        - Cada vez que repone, decide si provee de 1 o 2 tartas a la vez. *Creará un vector con 1 o 2 elementos.*
        - Cada tarta tendrá un peso asociado que será también aleatorio entre 1 y 10 kg. *Un vector [1,10] indicará el peso mínimo y máximo de las tartas.*
        - Mostrará cuántas tartas va a reponer y a qué equipo.
    - Por otro lado, recibirá la suma de los kg que cada equipo se ha comido en cada tanda. Para cada tanda servida:
        - Comparará quién ha comido más kg de tarta en dicha tanda.
        - Sumará 1 punto al equipo que más kg haya comido.
    - Finalmente, comparará los puntos de ambos equipos y proclamará vencedor al que más kg de tarta comió.
4. Los procesos Mario y  Peach realizarán las siguientes operaciones:
    - Recibirán las tartas que se van a comer.
    - Mostrarán las tartas que han recibido y sus pesos.
    - Sumarán el peso de cada tarta y aleatoriamente se comerán una porción.
    - La cantidad que se han comido se la notificarán a Yoshi.
5. Mientras haya envíos que hacer, se han de poder realizar, evitando que haya ningún tipo de bloqueo. Es decir, Yoshi podrá reponer tartas sin tener que sufrir ningún tipo de bloqueo por otras operaciones (a excepción de retrasos aleatorios).
6. Se han de incluir retrasos aleatorios.


***

Puede encontrar la solución al problema en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica3/Exámenes/Examen1.cpp).
