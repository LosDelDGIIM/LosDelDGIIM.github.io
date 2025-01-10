<br>

# SCD. Autoevaluación del Tema 4. Sistemas de Tiempo Real.

***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Manuel Isidoro Capel Tuñón.
- **Descripción:** Este documento tiene como objetivo servir para estudiar la asignatura de Sistemas Concurrentes y Distribuidos. En él, se puede encontrar una corta autoevaluación formada por unas 25 preguntas tipo test sobre la parte sistemas de tiempo real.
***
 
1. Una tarea espaciada por "Jitter" o deriva tiene
    - ( ) Holgura máxima constante.
    - ( ) Prioridades dinámicas en cada activación.
    - ( ) Plazos de respuesta arbitrarios.
    - (x) Variaciones en su tiempo de activación.
    - ( ) Activaciones a intervalos exactos.

2. ¿Qué propiedad define el determinismo en los STR?
    - ( ) Interrupciones rápidas y eficientes.
    - (x) Predecir con certeza los tiempos de respuesta.
    - ( ) Asignación dinámica de prioridades.
    - ( ) Acceso a recursos compartidos.
    - ( ) Ejecutar tareas concurrentes.
 
3. El modelo de tareas simples asume
    - (x) Tareas periódicas con plazos iguales a su periodo.
    - ( ) Dependencia entre todas las tareas.
    - ( ) Exclusión mutua en tiempo real.
    - ( ) Acceso concurrente a recursos compartidos.
    - ( ) Activaciones dinámicas no predecibles.

4. ¿Qué factor reduce los bloqueos en sistemas STR?
    - (x) Protocolos de techo de prioridad.
    - ( ) Exclusión mutua en todos los recursos.
    - ( ) Todas las anteriores.
    - ( ) Planificación con servidores diferidos.
    - ( ) Uso de algoritmos dinámicos.

5. La prioridad relativa en un esquema RMS se basa en
    - (x) Periodos más pequeños.
    - ( ) Plazos de respuesta máximos.
    - ( ) Número de recursos compartidos.
    - ( ) Uso eficiente de CPU.
    - ( ) Tiempo de respuesta más corto.

6. El bloqueo indirecto ocurre cuando
    - ( ) Dos tareas tienen igual prioridad.
    - (x) Un recurso compartido interfiere en tareas no relacionadas.
    - ( ) Las tareas tienen restricciones temporales flexibles.
    - ( ) Ninguna de las anteriores.
    - ( ) Una tarea depende de múltiples recursos.

7. ¿Qué ocurre en un STR durante una sobrecarga transitoria?
    - ( ) Las tareas de menor prioridad se descartan.
    - ( ) La planificación dinámica falla.
    - ( ) Todas las tareas se reinician.
    - (x) Los esquemas estáticos son más predecibles.
    - ( ) La prioridad máxima se asigna automáticamente.

8. El análisis de planificabilidad con servidor diferido garantiza
    - (x) Plazos cumplidos para tareas periódicas.
    - ( ) Uso máximo de CPU.
    - ( ) Exclusión de tareas esporádicas.
    - ( ) Mayor flexibilidad en tareas aperiódicas.
    - ( ) Bloqueos mínimos en recursos compartidos.

9. Un sistema operativo de tiempo real garantiza
    - ( ) Máxima utilización de CPU.
    - ( ) Acceso prioritario a memoria.
    - ( ) Multitarea ilimitada.
    - ( ) Exclusión mutua en todos los recursos.
    - (x) Respuesta dentro de un tiempo limitado predefinido.

10. ¿Qué significa STR de misión crítica?
    - (x) Tareas donde la falla puede tener consecuencias graves.
    - ( ) Aplicaciones que solo usan recursos compartidos.
    - ( ) Planificación exclusivamente dinámica.
    - ( ) Tareas con alta tolerancia a fallos.
    - ( ) Tareas con tiempo límite flexible.

11. Un ejemplo de STR permisivo es
    - ( ) Reservas de vuelos.
    - (x) Adquisición de datos meteorológicos.
    - ( ) Monitoreo de redes.
    - ( ) Control de tráfico aéreo.
    - ( ) Planificación de producción.

12. ¿Qué tipo de tiempo NO es usado en los STR?
    - ( ) Relativo.
    - ( ) Absoluto.
    - (x) Incremental.
    - ( ) Atómico.
    - ( ) GPS.

13. ¿Cuál es una característica clave de los relojes de tiempo real?
    - ( ) Baja precisión.
    - (x) Tiempo de desbordamiento definido.
    - ( ) Sincronización con tiempo relativo.
    - ( ) Deriva acumulativa constante.
    - ( ) Granularidad variable.

14. Un temporizador periódico se caracteriza por
    - ( ) Permitir modificaciones dinámicas de los intervalos.
    - ( ) Presentar una deriva acumulativa constante.
    - ( ) Interrumpir la planificación actual.
    - (x) Realizar activaciones repetitivas en intervalos definidos.
    - ( ) Activarse una vez y detenerse.

15. ¿Qué atributo temporal tiene una tarea de tiempo real?
    - ( ) Prioridad dinámica asignada.
    - ( ) Periodo mínimo de activación.
    - (x) Tiempo de cómputo máximo.
    - ( ) Número máximo de interrupciones.
    - ( ) Tiempo de respuesta variable.

16. ¿Cuál es una característica clave de los STR?
    - (x) Respuesta correcta dentro de un tiempo límite.
    - ( ) Alta disponibilidad de memoria.
    - ( ) Uso de sistemas operativos generales.
    - ( ) Uso exclusivo de tareas periódicas.
    - ( ) Exclusión de tareas concurrentes.

17. ¿Qué tipo de tarea se activa en instantes arbitrarios?
    - (x) Aperiódica.
    - ( ) Sincrónica.
    - ( ) Asíncrona.
    - ( ) Periódica.
    - ( ) Esporádica.

18. La planificación cíclica usa
    - (x) Hiperperiodos basados en MCM.
    - ( ) Prioridades dinámicas.
    - ( ) Algoritmos de análisis temporal.
    - ( ) Exclusión de tareas esporádicas.
    - ( ) Acceso a múltiples procesadores.

19. Un algoritmo dinámico como EDF asigna prioridad según
    - ( ) Holgura más alta.
    - ( ) Requerimientos de memoria.
    - (x) Tiempo límite más próximo.
    - ( ) Periodos más cortos.
    - ( ) Uso del procesador más bajo.

20. En qué consiste la inversión de prioridad
    - ( ) Un error en el orden de asignación de prioridades.
    - ( ) La planificación cíclica falla en el análisis de Gantt.
    - ( ) Las tareas menos críticas interrumpen las más importantes.
    - (x) Una tarea prioritaria puede quedar bloqueada indefinidamente.
    - ( ) Ninguna de las anteriores.

21. El protocolo de herencia de prioridad
    - ( ) Desactiva tareas aperiódicas.
    - ( ) Reduce las prioridades de tareas esporádicas.
    - ( ) Asigna prioridad máxima a todas las tareas.
    - (x) Dinamiza prioridades según el bloqueo de recursos.
    - ( ) Garantiza exclusión mutua completa.

22. ¿Qué es el "techo de prioridad" de un recurso?
    - ( ) Un atributo dinámico definido por EDF.
    - ( ) La prioridad mínima que puede acceder al recurso.
    - (x) La prioridad más alta que puede bloquear.
    - ( ) La prioridad promedio de las tareas que lo usan.
    - ( ) La prioridad asignada por el sistema operativo.

23. Un servidor diferido es útil para
    - (x) Gestionar peticiones aperiódicas.
    - ( ) Sustituir el protocolo de herencia.
    - ( ) Sincronizar relojes del sistema.
    - ( ) Optimizar los tiempos de cómputo máximo.
    - ( ) Tareas periódicas críticas.

24. El test de Liu y Layland (RMS) es aplicable a
    - ( ) Tareas aperiódicas con plazos fijos.
    - ( ) Tareas esporádicas con plazos variables.
    - ( ) Sistemas distribuidos concurrentes.
    - (x) Tareas periódicas independientes.
    - ( ) Procesos con múltiples recursos compartidos.

25. ¿Cuál es el límite de utilización de CPU para N tareas según RMS?
    - ( ) U0 × N.
    - ( ) N × 2^(1/N).
    - ( ) N^2 × T.
    - (x) N(2^(1/N) − 1).
    - ( ) N(3^(1/N)).
