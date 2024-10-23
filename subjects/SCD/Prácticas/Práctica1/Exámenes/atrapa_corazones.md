# SCD. Simulacro II de la Práctica I

**Autor:** Arturo Olivares Martos.
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas + ADE.
- **Grupo:** 3.
- **Profesor:** Luis Gonzaga Baca Ruiz.
- **Descripción:** Simulacro II de la práctica 1 de SCD.
- **Fecha:** 17 de octubre de 2024.
- **Duración:** 50 minutos.
- **Observaciones:** El enunciado no es literalmente el descrito en el simulacro, ya que es el que se ha recordado tras la finalización del examen.

***
Para ver la solución, dirígase al final del documento.

***
Programar un jugeo de atrapar corazones:
 
4 jugadores buscan acceder a un corazón, se pelean por ello y debe gestionarse su pelea.
- 1 generador produce el corazón y lo pone visible.
- Se juega por rondas y hay como mucho $k$ rondas (supóngase $k=10$ para el simulacro).
- Cuando un jugador toma el corazón, se muestra qué jugador lo hace y se muestra que gana 5 puntos.
- Al terminar, deben mostrarse los resultados finales.

- La salida de cada ronda debe ser:
    ```txt
    Generador: Corazón visible
    Jugador i: Corazón robado. Gana 5 puntos.
    --- Fin Ronda ---
    Puntos: p1 p2 p3 p4
    ```

- La salida final debe ser:
    ```txt
    --- FIN ---
    Puntos: p1 p2 p3 p4
    ```
***
  
Puede encontrar la solución al problema en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica1/Exámenes/atrapa_corazones.cpp).
