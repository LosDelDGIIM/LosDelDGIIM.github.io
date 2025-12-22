<br>

# Sistemas Concurrentes y Distribuidos. Examen II.

**Autor:** Ángel Caro Montalbán
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2025-26.
- **Grado:** GII-ADE-M.
- **Grupo:** Único.
- **Profesor:** Manuel Isidoro Capel Tuñón.
- **Fecha:** 03-12-2025.
- **Descripción:** Examen Parcial 1 (anulado).

______

1. ¿Cuál de las siguientes es una solución para garantizar la corrección de los programas concurrentes?
    - (x) Utilizar métodos formales basados en la lógica matemática para verificar la corrección.
    - ( ) Confiar sólo en la comprobación manual de errores.
    - ( ) Ignorar los errores transitorios porque ocurren raramente.
    - ( ) Utilizar la fuerza bruta para reejecutar el programa varias veces.
    - ( ) Se puede garantizar la corrección sin ningún método formal.

2. ¿Qué es un Monitor de Barrera Parcial?
    - ( ) Un monitor que detiene todos los procesos.
    - ( ) Un monitor que libera procesos en intervalos.
    - (x) Un monitor que bloquea procesos hasta que un grupo alcanza un estado.
    - ( ) Un monitor que reduce el tiempo de espera.
    - ( ) Un monitor que libera a todos los procesos al mismo tiempo.

3. ¿Qué es la exclusión mutua en concurrencia?
    - (x) Garantizar que solo un proceso acceda a una sección crítica a la vez.
    - ( ) Permitir que múltiples procesos accedan simultáneamente a la memoria.
    - ( ) Sincronizar dos procesos sin que uno bloquee al otro.
    - ( ) Ejecutar procesos en paralelo sin control de acceso.
    - ( ) Ninguna de las anteriores.

4. ¿Qué significa irrepetibilidad de las secuencias de instrucciones en la programación concurrente?
    - ( ) Los procesos siguen siempre la misma secuencia de ejecución.
    - ( ) Los programas concurrentes nunca tienen errores.
    - ( ) Dos ejecuciones seguirán probablemente el mismo camino.
    - (x) Los programas concurrentes generan muchos entrelazamientos de instrucciones posibles, por lo que es poco probable que se repitan caminos.
    - ( ) La velocidad de ejecución determina la secuencia de instrucciones.

5. En la versión preferencia a chicas del problema 60 (relación 2-1), si un chico espera y llega una chica:
    - ( ) pasa el chico.
    - ( ) pasan los dos si hay aforo.
    - (x) la chica tiene prioridad al siguiente hueco.
    - ( ) nadie pasa.
    - ( ) se atiende por orden de llegada.

6. ¿Qué función cumple la operación c.wait() en un monitor?
    - ( ) Bloquear el monitor hasta que se libere.
    - ( ) Disminuir el valor de la variable protegida.
    - (x) Bloquear al proceso que llama al procedimiento que la ejecuta hasta que se cumpla una condición.
    - ( ) Liberar procesos en la cola de entrada al monitor.
    - ( ) A veces, puede permitir la sincronización sin bloquear.

7. ¿Qué define el término cliente en un modelo cliente/servidor?
    - ( ) Un proceso pasivo que recibe datos.
    - ( ) Un proceso que almacena mensajes.
    - (x) Un proceso activo que solicita servicios.
    - ( ) Un proceso intermedio entre servidor y base de datos.
    - ( ) Un controlador centralizado.

8. ¿Qué es el progreso global en el contexto de la ejecución concurrente?
    - ( ) Garantiza que todos los procesos terminen la ejecución inmediatamente.
    - (x) Garantiza que al menos un proceso listo para ejecutarse llegue a ejecutarse, evitando el bloqueo.
    - ( ) Requiere que todos los procesos se ejecuten al mismo tiempo.
    - ( ) Garantiza que ningún proceso pueda bloquear la ejecución de otro.
    - ( ) Es específico sólo de los sistemas en tiempo real.

9. Para evitar interbloqueo en MonFilo (problema 69 (a), relación 2-1) sin árbitro basta con:
    - ( ) permitir 5 intentos concurrentes.
    - ( ) prohibir la actividad "pensar" de los filósofos.
    - (x) limitar a 4 filósofos intentando coger su primer tenedor.
    - ( ) que todos cojan primero el izquierdo.
    - ( ) que todos suelten al terminar de pensar.

10. En la lógica de Hoare, ¿qué se necesita para verificar la corrección de una composición concurrente de procesos?
    - ( ) Cada proceso debe tener su propio espacio de memoria independiente.
    - ( ) La composición sólo debe implicar a un único proceso a la vez.
    - (x) Las precondiciones y postcondiciones de los procesos deben de poder combinarse, y ningún proceso debe invalidar las afirmaciones de los demás.
    - ( ) Los procesos deben ejecutarse secuencialmente, sin solapar instrucciones.
    - ( ) El sistema debe probarse con todas las configuraciones de hardware posibles.

11. En el algoritmo de tickets (problema 75, relación 2-2), la ausencia de inanición se apoya en...
    - ( ) prioridad fija a P1.
    - (x) numeración creciente y orden lexicográfico (ticket, id).
    - ( ) azar del planificador.
    - ( ) cálculo de prioridad de los procesos en cada iteración del protocolo de entrada.
    - ( ) incremento secuencial en los valores de las variables.

12. ¿Qué sucede en la semántica de Señalar y Salir (SS)?
    - ( ) El proceso señalador continúa ejecutando.
    - ( ) El proceso señalado queda en espera.
    - (x) El proceso señalador sale del monitor después de signal.
    - ( ) Se detiene la ejecución del monitor.
    - ( ) El siguiente proceso esperando es liberado inmediatamente.

13. ¿Qué efecto pueden tener las condiciones de carrera en los programas concurrentes?
    - ( ) Garantizan que todos los procesos se ejecuten de forma predecible.
    - ( ) Producen resultados predecibles y correctos.
    - (x) Producen resultados impredecibles o incorrectos según el orden de ejecución.
    - ( ) Reducen el riesgo de errores en el programa.
    - ( ) Facilitan la depuración debido a su comportamiento coherente.

14. Si en Dijkstra se cambia (6) por if $flag[turno]!=enSC$ el algoritmo... (algoritmo, página 10):
    - ( ) mejora equidad.
    - (x) pierde corrección (seguridad).
    - ( ) mantiene EM pero pierde progreso.
    - ( ) mantiene todo.
    - ( ) sólo afecta rendimiento.

15. ¿Cuál de las siguientes no es una estrategia para evitar el interbloqueo?
    - ( ) Evitar la espera circular.
    - ( ) Asignación ordenada de recursos.
    - ( ) Suspensión de procesos en espera.
    - (x) Mantener la CPU libre de cargas excesivas.
    - ( ) Utilizar algoritmos de detección y recuperación.

16. ¿Cuál es la principal desventaja de usar espera ocupada para la sincronización entre procesos?
    - (x) Alto consumo de CPU mientras espera.
    - ( ) No garantiza exclusión mutua.
    - ( ) No son compatibles con sistemas de tiempo real.
    - ( ) Bloquean completamente la ejecución del sistema.
    - ( ) Son incompatibles con los semáforos.

17. ¿Qué reto presentan las trazas de ejecución de los programas concurrentes?
    - ( ) Siempre conducen a un punto muerto.
    - ( ) Siguen un patrón predecible y repetible.
    - ( ) Generan numerosas secuencias de intercalación posibles, lo que complica la predicción.
    - (x) Las trazas no pueden utilizarse con fines de depuración.
    - ( ) Las trazas garantizan que se producirán errores.

18. ¿Qué propiedad define el determinismo en los STR?
    - ( ) Ejecutar tareas concurrentes.
    - ( ) Predecir con certeza los tiempos de respuesta.
    - (x) Garantizar ejecuciones idénticas incluso con concurrencia.
    - ( ) Requerir planificación en tiempo real.
    - ( ) Propagar errores transitorios de forma controlada.

19. En el esquema s[i] (problema 74, relación 2-2), la estructura implementa...
    - (x) un anillo token que garantiza equidad por rotación.
    - ( ) prioridad fija del proceso 0.
    - ( ) acceso aleatorio.
    - ( ) bloqueo del resto de los procesos que no acceden a SC en la ronda actual.
    - ( ) dos tokens simultáneos.

20. ¿Qué son los errores transitorios en el contexto de los programas concurrentes?
    - ( ) Errores que aparecen siempre en la misma ejecución.
    - ( ) Errores que se producen aleatoriamente y no tienen solución.
    - ( ) Errores que son fáciles de detectar y solucionar.
    - (x) Errores que aparecen en algunas ejecuciones pero no en otras, lo que dificulta su detección.
    - ( ) Errores que nunca se producen en los programas concurrentes.

21. ¿Qué problema ocurre cuando múltiples procesos intentan modificar una variable compartida al mismo tiempo?
    - ( ) Fragmentación de memoria.
    - (x) Condiciones de carrera.
    - ( ) Overhead de comunicación.
    - ( ) Pérdida de coherencia en caché.
    - ( ) Errores de compilación.

22. ¿Qué condición de Dijkstra no es esencial para la exclusión mutua?
    - ( ) Mayor escalabilidad.
    - ( ) Menor latencia en comunicación.
    - ( ) Tolerancia a fallos.
    - ( ) Distribución de carga.
    - ( ) Independencia de ubicación.

23. ¿Qué proceso controla la sincronización en un sistema productor-consumidor?
    - ( ) Productor.
    - ( ) Consumidor.
    - (x) Búfer intermedio.
    - ( ) Coordinador externo.
    - ( ) Cliente.

24. ¿Qué es una traza en el contexto de la programación concurrente?
    - ( ) Una secuencia de operaciones atómicas de un único proceso.
    - (x) Una secuencia de estados del programa producidos por un intercalado específico de instrucciones.
    - ( ) La ejecución de un único proceso de forma aislada.
    - ( ) El historial de cómo se modifican las variables durante la compilación.
    - ( ) Un registro de todos los errores en la ejecución de un programa.

25. ¿Cuál de las siguientes soluciones no es una técnica eficaz para exclusión mutua en memoria compartida?
    - ( ) Semáforos.
    - ( ) Monitores.
    - ( ) Algoritmo de Lamport.
    - ( ) Cerrojos.
    - (x) Espera ocupada.

26. En el algoritmo de Dijkstra, ¿qué ocurre si varios procesos intentan entrar a la sección crítica al mismo tiempo?
    - ( ) Solo uno entra y los demás esperan.
    - ( ) Todos entran simultáneamente.
    - ( ) Se produce una condición de carrera.
    - (x) Se usa un mecanismo de prioridad para decidir.
    - ( ) Se activa un interbloqueo.

27. ¿Cuál es la principal desventaja de usar espera ocupada para la sincronización entre procesos?
    - (x) Alto consumo de CPU mientras espera.
    - ( ) No garantizan exclusión mutua.
    - ( ) No son compatibles con sistemas de tiempo real.
    - ( ) Bloquean completamente la ejecución del sistema.
    - ( ) Son incompatibles con los semáforos.

28. ¿Qué es un monitor en programación concurrente?
    - ( ) Un dispositivo de entrada de datos.
    - (x) Un mecanismo de programación que permite sincronización de procesos.
    - ( ) Un programa antivirus.
    - ( ) Una interfaz gráfica de usuario.
    - ( ) Un controlador de semáforos.

29. ¿Qué implica la independencia de la velocidad del proceso en la programación concurrente?
    - ( ) La corrección del proceso debe depender de la velocidad relativa de los procesos.
    - (x) La corrección del proceso debe ser independiente de la velocidad de ejecución, evitando las condiciones de carrera.
    - ( ) Los procesos deben ejecutarse siempre lo más rápido posible.
    - ( ) Los procesos más lentos garantizan una mayor estabilidad del programa.
    - ( ) La velocidad de ejecución siempre determina la corrección del programa.

30. ¿En qué situación es preferible usar monitores en vez de semáforos?
    - (x) Cuando se requiere encapsulación de los mecanismos de sincronización.
    - ( ) Cuando se manejan múltiples hilos con prioridad variable.
    - ( ) Cuando se necesita garantizar exclusión mutua sin ocupación innecesaria de CPU.
    - ( ) Cuando los procesos deben ejecutarse en sistemas distribuidos.
    - ( ) Solo en sistemas de tiempo real.

31. En Filósofos comensales con monitor MonFilo (problema 69, relación 2-1), una solución clásica que sí puede interbloquear es:
    - ( ) coger siempre primero el tenedor de menor índice.
    - (x) permitir que los 5 cojan su primer tenedor simultáneamente.
    - ( ) permitir que 4 filósofos o más intenten coger su primer tenedor.
    - ( ) usar un árbitro que concede permisos y cuenta los tenedores que queda libres.
    - ( ) asimetría en el orden de tomar tenedores.

32. ¿Qué condición de Dijkstra no es esencial para la exclusión mutua?
    - ( ) No hacer suposiciones sobre la velocidad de los procesos.
    - ( ) Cada proceso debe tener un identificador único.
    - ( ) Si un proceso está fuera de la sección crítica, no impide a otros entrar.
    - ( ) Algún proceso en espera debe entrar en la sección crítica.
    - ( ) La concurrencia es siempre determinista.

33. ¿Cuál de los siguientes no es un problema asociado a la concurrencia?
    - ( ) Interbloqueo (Deadlock).
    - ( ) Inanición (Starvation).
    - ( ) Condiciones de carrera.
    - (x) Fragmentación de memoria.
    - ( ) Indeterminismo.

34. ¿Cuál es la principal característica de la regla de no interferencia de la lógica de Hoare para programas concurrentes?
    - ( ) Garantiza que cada proceso termina de ejecutarse antes de que comience el siguiente.
    - (x) Garantiza que dos procesos no interfieran entre sí en sus precondiciones y postcondiciones cuando se ejecutan simultáneamente.
    - ( ) Permite que los procesos se ejecuten sin sincronización y sigue garantizando la corrección.
    - ( ) Garantiza que las precondiciones y poscondiciones de las instrucciones no se vean modificadas por otros procesos.
    - ( ) Garantiza que todos los procesos accedan a los recursos compartidos al mismo tiempo.

35. En la versión (b): por orden de llegada al banco del problema 66 (relación 2-1), si el primero pide 300 y saldo = 200:
    - ( ) se atiende al segundo si pide $\le 200$.
    - (x) todos esperan hasta que el primero pueda cobrar.
    - ( ) se divide el saldo entre los dos.
    - ( ) se atiende al segundo y se mantiene al primero esperando.
    - ( ) cancela la petición del primero.

36. En un monitor, aunque la exclusión mutua está garantizada, se exige que los procedimientos sean reentrantes porque:
    - ( ) la semántica SU prohíbe signal() dentro del monitor.
    - (x) los procesos pueden bloquearse y reentrar al monitor tras un wait()/signal().
    - ( ) la entrada al monitor es no determinista.
    - ( ) se permite invocar el mismo procedimiento desde llamadas asíncronas.
    - ( ) reentrancia evita el interbloqueo por definición.

37. ¿Qué significa progreso local en la programación concurrente?
    - ( ) Una vez que un proceso empieza a ejecutar una sección de código, debe completarla sin interrupción.
    - (x) Un proceso puede detenerse a mitad de ejecución y reanudarse más tarde sin completar la sección actual.
    - ( ) Un proceso debe completar siempre todo el programa sin pausa.
    - ( ) Los procesos deben comunicarse con otros procesos para continuar la ejecución.
    - ( ) Una vez que un proceso comienza a ejecutarse, debe terminar todo el programa.

38. El algoritmo de Knuth N procesos cumple...
    - ( ) no garantiza EM.
    - (x) EM, alcanzabilidad, vivacidad y equidad.
    - ( ) requiere que se cumpla la propiedad de equidad (fairness) fuerte.
    - ( ) sólo EM y alcanzabilidad.
    - ( ) la vivacidad, que no cumplía el algoritmo de Dijkstra.

39. La extensión del protocolo de la exclusión mutua con "como mucho n procesos en SC", una solución correcta se basa en:
    - ( ) un ticket lock clásico.
    - (x) un semáforo contador inicializado a n.
    - ( ) una variable booleana turn.
    - ( ) dos flags por proceso.
    - ( ) un árbol binario de Peterson.

40. En Dijkstra N procesos, la proposición sobre quien asigna turno en último lugar es:
    - ( ) verdadera.
    - (x) falsa.
    - ( ) verdadera si FIFO.
    - ( ) verdadera si SU.
    - ( ) depende de N.

41. La solución de Hyman (1966) a EM para 2 procesos (problema 73, relación 2-2) es:
    - ( ) correcta.
    - (x) incorrecta.
    - ( ) correcta sólo si se cumple equidad (fairness) fuerte.
    - ( ) correcta si $c_0, c_1$ boolean.
    - ( ) correcta si turno = -1.

42. ¿Qué sucede con un proceso en cola cuando se usa signal en una semántica SC?
    - ( ) Se despierta y sale inmediatamente.
    - ( ) Permanece bloqueado indefinidamente.
    - (x) Se mueve a la cola de entrada del monitor.
    - ( ) Compite por entrar a la cola del monitor.
    - ( ) Ignora la operación signal.

43. ¿Qué significa el triple $\{P\}C\{Q\}$ en el contexto de la lógica de Hoare?
    - ( ) Si el programa C se ejecuta, siempre terminará.
    - (x) Si el programa C comienza en un estado en el que P es verdadero, entonces Q será verdadero después de que C termine de ejecutarse.
    - ( ) P y Q son variables que representan el estado antes y después de C.
    - ( ) Garantiza que en la ejecución de varios procesos contenidos en C no existen interferencias.
    - ( ) Si el programa C se ejecuta con la máxima velocidad, P siempre será igual a Q.

44. En el algoritmo de tickets $n1/n2$ (problema 75, relación 2-2) con desempate a favor de P1, garantiza...
    - (x) EM, ausencia de interbloqueo y equidad.
    - ( ) sólo EM y vivacidad.
    - ( ) sólo ausencia de interbloqueo.
    - ( ) ausencia de inanición y alcanzabilidad.
    - ( ) ninguna.

45. ¿Qué es una cola de prioridad en monitores?
    - ( ) Una cola para ejecutar en último lugar.
    - ( ) Una cola que permite ordenar procesos según su menor índice.
    - ( ) Una lista de operaciones de señal.
    - (x) Una cola ordenada de procesos suspendidos según un valor estático de una variable.
    - ( ) Un tipo de cola prioritaria que reordena los procesos según los valores de una variable permanente del monitor.

46. ¿Cuál de las siguientes es la definición de propiedad de vivacidad?
    - ( ) Una condición que debe cumplirse en cada instante de la ejecución del programa.
    - ( ) Una propiedad que garantiza que los procesos pueden pausarse indefinidamente.
    - (x) Una condición que establece que algo bueno debe suceder eventualmente en el futuro.
    - ( ) Una propiedad que define cuántos procesos pueden ejecutarse simultáneamente.
    - ( ) Una condición que establece que nada malo va a pasar en el futuro.

47. En el ejercicio del baño (preferencia a chicos), problema 60 (relación 2-1) si una chica espera y llega un chico:
    - ( ) pasa la chica.
    - ( ) pasan ambos.
    - (x) pasa el chico antes.
    - ( ) se alternan.
    - ( ) nadie pasa hasta que se vacíe, pero pasa antes el chico que espera.

48. Por qué no se puede demostrar la corrección del siguiente fragmento concurrente a menos que se cumpla $\{x==0 \wedge y==0 \wedge z==0\} <x=z+a> || <y=x+b> \{x==a \wedge (y==b \vee y==a+b) \wedge z==0\}$:
    - ( ) $b=0 \vee a=0$.
    - ( ) $b=0 \wedge a=0$.
    - (x) $a=0$.
    - ( ) para cualquier valor de las variables.
    - ( ) es siempre indemostrable.

49. Seleccionar el valor correcto de las 2 variables (x e y) tras: int x=5, y=2; cobegin <x=x+y>; <y=x*y>; <x=x-y>; coend;
    - [ ] $x==7, y==14$.
    - [x] $x==5, y==10$.
    - [x] $x==-7, y==14$.
    - [ ] $x==-3, y==10$.

50. ¿Por qué el código $\{x==0\}$ cobegin <x=x+a>; <x=x+a> coend; $\{x==2*a\}$ no puede ser demostrado directamente con LP?
    - ( ) Porque la poscondición propuesta $(x==2*a)$ es falsa.
    - ( ) Porque falta incluir la posibilidad de que el valor final sea $\{x==a\}$.
    - (x) Porque al aplicar la regla de inferencia utilizo pre y post-condiciones demasiado débiles.
    - ( ) Porque tengo que incluir en los asertos el valor del contador de programa.