# SCD. Simulacro III de la Práctica I

**Autor:** Arturo Olivares Martos.<br>
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas + ADE.
- **Grupo:** 1.
- **Profesor:** Ana María Sánchez López.
- **Descripción:** Simulacro III de la práctica 1 de SCD.
<!--- **Fecha:** 23 de octubre de 2024.-->
- **Duración:** 50 minutos.

***
<!--Para ver la solución, dirígase al final del documento.

***-->
Partiendo del programa `fumadores.cpp` de cada estudiante, se debe crear una nueva hebra "sanitaria" (que será un ciclo infinito), que empieza bloqueada y que es desbloqueada por los fumadores en un momento concreto.
- Esta nueva hebra sólo es desbloqueada cada vez que un fumador obtiene su ingrediente después de haber fumado 5 cigarrillos. Es decir, cuando un fumador $X$ es liberado para fumar el siguiente cigarrillo (el sexto), desbloquea a la hebra sanitaria y se bloquea hasta que dicha hebra sanitaria lo libere.
- La hebra sanitaria, cuando es desbloqueada, imprime por pantalla el siguiente mensaje: `FUMAR MATA: ya lo sabes, fumador X`, luego desbloquea a dicho fumador y vuelve al inicio de su ciclo quedando bloqueada hasta que otro fumador la despierte.
- El fumador desbloqueado por la hebra sanitaria informa del aviso recibido por dicha hebra con el siguiente mensaje: `Soy el fumador X y me han llamado vicioso`, y continúa con su ciclo normal retirando el ingrediente, desbloqueando al estanquero y fumando, empezando de nuevo la cuenta de 5 cigarrillos por fumar.

Puede encontrar la solución al problema en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica1/Exámenes/hebraSanitaria.cpp).-->
