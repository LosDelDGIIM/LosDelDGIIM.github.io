<br>

# SCD. Autoevaluación del Tema 2.

***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Manuel Isidoro Capel Tuñón.
- **Descripción:** Este documento tiene como objetivo servir para estudiar la asignatura de Sistemas Concurrentes y Distribuidos. En él, se puede encontrar una corta autoevaluación formada por unas 25 preguntas tipo test.
***

1. ¿Cuál es la principal limitación de los semáforos en sistemas concurrentes?
    - ( ) Solo funcionan con variables estáticas.
    - ( ) Dependen de variables locales.
    - ( ) Requieren mucho espacio de memoria.
    - ( ) Son difíciles de implementar en hardware.
    - (x) No permiten encapsulación de la sincronización.

2. ¿Qué es un monitor en programación concurrente?
    - ( ) Un dispositivo de entrada de datos.
    - ( ) Un controlador de semáforos.
    - (x) Un mecanismo de programación que permite sincronización de procesos.
    - ( ) Un programa antivirus.
    - ( ) Una interfaz gráfica de usuario.

3. ¿Quién introdujo el concepto de monitor y en qué año?
    - (x) C.A.R. Hoare, en 1974.
    - ( ) Donald Knuth, en 1975.
    - ( ) Edsger Dijkstra, en 1972.
    - ( ) John von Neumann, en 1965.
    - ( ) Alan Turing, en 1970.

4. ¿Qué es una variable permanente en un monitor?
    - ( ) Una variable que cambia continuamente.
    - ( ) Una variable local a cada procedimiento del monitor.
    - ( ) Una variable de solo lectura.
    - ( ) Una variable utilizada solo para imprimir.
    - (x) La variable que guarda el estado interno del monitor.

5. ¿Qué garantiza la exclusión mutua en los monitores?
    - ( ) Las interrupciones de hardware.
    - (x) Los procedimientos dentro del monitor.
    - ( ) Los semáforos externos que se usan para implementar los monitores.
    - ( ) El sistema operativo.
    - ( ) Las condiciones de sincronización.

6. ¿Cuál de los siguientes NO es un componente de los monitores? 
    - ( ) Variables permanentes.
    - (x) Variables temporales.
    - ( ) Condiciones de sincronización.
    - ( ) Procedimientos.
    - ( ) Código de inicialización.

7. ¿Qué función cumple la operación `c.wait()` en un monitor?
    - (x) Bloquear al proceso que llama al procedimiento que la ejecuta hasta que se cumpla una condición.
    - ( ) Liberar todos los procesos en la cola.
    - ( ) Permitir la sincronización sin bloquear.
    - ( ) Bloquear el monitor hasta que se libere.
    - ( ) Incrementar el valor de una variable.

8. ¿Qué sucede cuando se ejecuta `c.signal()` y la cola está vacía?
    - ( ) Se libera un recurso de memoria.
    - (x) La operación se descarta sin efecto.
    - ( ) Se bloquea el monitor.
    - ( ) Se activa el primer proceso de la cola.
    - ( ) Cambia el valor de la variable de condición.

9. ¿Qué asegura el "invariante del monitor" en un sistema concurrente?
    - (x) Que el monitor mantenga una propiedad específica siempre que no esté en uso.
    - ( ) La reusabilidad de las variables.
    - ( ) La verificación de sincronización.
    - ( ) La exclusión mutua de procesos.
    - ( ) El acceso constante a las variables.

10. ¿Cuál de las siguientes es una característica de la "señal automática" (SA)?
    - (x) Se ejecuta una señal implícita sin desplazamiento.
    - ( ) Los procesos señaladores esperan en la cola.
    - ( ) El monitor entra en espera forzada.
    - ( ) Se reinicia el monitor automáticamente.
    - ( ) El proceso señalador continúa su ejecución tras signal.

11. ¿Qué significa la semántica de "Señalar y Continuar" (SC)?
    - ( ) Todos los procesos en la cola se desbloquean.
    - (x) El proceso señalador continúa su ejecución después de signal.
    - ( ) La operación signal se omite.
    - ( ) El proceso señalador espera en la cola.
    - ( ) El monitor se reinicia.

12. ¿Qué significa la semántica de "Señalar y Esperar" (SE)?
    - ( ) No se permite el acceso a la exclusión mutua del monitor.
    - ( ) El proceso señalado abandona el monitor.
    - (x) El proceso señalador se bloquea después de signal.
    - ( ) Los procesos en cola no se despiertan.
    - ( ) El proceso señalador sigue ejecutando código del monitor.

13. ¿Para qué tipo de problemas es útil el patrón de Exclusión Mutua (EM)?
    - ( ) Para asignación de memoria dinámica.
    - (x) Para acceso exclusivo a una sección crítica.
    - ( ) Para sincronización de semáforos.
    - ( ) Para desbloquear colas de procesos.
    - ( ) Para almacenamiento de variables compartidas.

14. ¿Cuál es el invariante del monitor de exclusión mutua?
    - ( ) `num_sc >= 2`.
    - ( ) `libre + num_sc == 2`.
    - ( ) `ocupada == false`.
    - ( ) `num_sc > 1`.
    - (x) `ocupada == true` cuando hay un proceso en SC.

15. ¿Qué define la operación `escribir` en un monitor Productor-Consumidor?
    - ( ) Borra el valor compartido.
    - ( ) Inicia una señal de bloqueo.
    - ( ) Desbloquea el monitor.
    - (x) Escribe el valor en una variable compartida.
    - ( ) Lee el valor de la variable compartida.

16. ¿Qué hace la operación `leer()` en el monitor de Productor-Consumidor?
    - ( ) Limpia la cola de procesos.
    - ( ) Elimina el valor de la variable.
    - ( ) Activa al proceso productor.
    - (x) Lee el valor compartido y lo devuelve.
    - ( ) Bloquea al proceso productor.

17. ¿Cuál es el propósito de la variable `pendiente` en el monitor Productor-Consumidor?
    - ( ) Indicar que el valor ha sido leído y no escrito.
    - ( ) Indicar si hay procesos señaladores.
    - ( ) Guardar el número de procesos en cola.
    - ( ) Mostrar si el monitor está activo.
    - (x) Controlar el estado de las operaciones de lectura y escritura.

18. ¿Qué es una cola de prioridad en monitores?
    - ( ) Una lista de operaciones de señal.
    - ( ) Un grupo de semáforos.
    - ( ) Un tipo de variable temporal.
    - (x) Una cola que permite ordenar procesos según prioridad.
    - ( ) Una cola para ejecutar en último lugar.

19. ¿Qué es el Patrón de Espera Única (EU) en programación concurrente?
    - ( ) Un proceso bloquea a otro.
    - ( ) Un proceso finaliza antes de que inicie otro.
    - ( ) Un proceso espera indefinidamente en una cola.
    - (x) Un proceso espera que otro finalice antes de iniciar una acción.
    - ( ) Un proceso se elimina automáticamente.

20. ¿Cuál de las siguientes NO es una operación de sincronización en monitores?
    - ( ) `signal_all()`.
    - ( ) `wait()`.
    - ( ) `signal()`.
    - ( ) `queue()`.
    - (x) `init()`.

21. ¿Qué sucede en la semántica de Señalar y Salir (SS)?
    - (x) El proceso señalador sale del monitor después de `signal`.
    - ( ) El proceso señalado queda en espera.
    - ( ) El proceso señalador continúa ejecutando.
    - ( ) Todos los procesos son liberado.
    - ( ) Se detiene la ejecución del monitor.

22. ¿Cuál es el propósito de `c.signal_all()` en un monitor?
    - (x) Liberar todos los procesos en la cola de condición.
    - ( ) Reiniciar el monitor.
    - ( ) Bloquear todos los procesos.
    - ( ) Cambiar el valor de las variables permanentes.
    - ( ) Liberar sólo el primer proceso en cola.

23. ¿Qué es un Monitor de Barrera Parcial?
    - (x) Un monitor que bloquea procesos hasta que un grupo alcanza un estado.
    - ( ) Un monitor que reduce el tiempo de espera.
    - ( ) Un monitor que libera procesos en intervalos.
    - ( ) Un monitor que libera a todos los procesos al mismo tiempo.
    - ( ) Un monitor que detiene todos los procesos.

24. ¿Cuál es la semántica ideal para el monitor de barrera parcial?
    - (x) SU.
    - ( ) SA.
    - ( ) SE.
    - ( ) SS.
    - ( ) SC.

25. ¿Qué sucede con un proceso en cola cuando se usa `signal` en una semántica SC?
    - ( ) Se ejecuta automáticamente.
    - ( ) Permanece bloqueado indefinidamente.
    - ( ) Se despierta y sale inmediatamente.
    - ( ) Ignora la operación `signal`.
    - (x) Se mueve a la cola de entrada del monitor.
