# Sistemas Empotrados - Test Tema 2: El Procesador ARM

- **Descripción:** Preguntas Tipo Test correspondientes al Tema 2: El Procesador ARM (Arquitectura, registros CPSR/SPSR, modos de ejecución, repertorio ARM/Thumb, ABI y scripts de enlazado).

---

1. ¿Cómo se puede modificar el valor de los flags de estado del procesador?
    - ( ) Solamente mediante el uso de instrucciones de comparación
    - ( ) Añadiendo a cualquier instrucción los sufijos de condición (lt, gt, eq,...)
    - ( ) Ejecutando cualquier instrucción. Los flags se fijarán en función del resultado
    - (x) Añadiendo el sufijo 's' a una instrucción

2. Las instrucciones ldrsb y ldrsh cargan un entero de 8 y 16 bits respectivamente en la parte menos significativa de un registro de 32 bits. ¿Qué hacen dichas instrucciones con la parte más significativa del registro, no ocupada por el dato que se ha cargado?
    - ( ) Se rellenan dichos bits con el valor 0
    - (x) Se extiende el signo del dato
    - ( ) Se dejan inalterados
    - ( ) Se rellenan dichos bits con el valor 1

3. Si la instrucción ldr r0, [pc, #2] está en la dirección 0x00400320 de memoria, ¿a qué dirección se accederá para cargar el dato?
    - ( ) 0x00400330
    - (x) 0x0040032A
    - ( ) 0x00400320
    - ( ) 0x00400322

4. ¿Cuál de las siguientes instrucciones es la mejor opción para multiplicar el contenido del registro r1 por 8?
    - ( ) lsl r1, r1, #3
    - (x) mov r1, r1, lsl #3
    - ( ) mul r1, r1, #8
    - ( ) El procesador ARM7TDMI no tiene multiplicador, por tanto no podemos multiplicar

5. ¿Cuál de las siguientes características es propia de los procesadores ARM?
    - ( ) Las instrucciones pueden operar con operando almacenados en memoria
    - (x) Su cauce está segmentado
    - ( ) El código tiende a ser más compacto
    - ( ) Se deben programar en ensamblador para obtener mejores prestaciones

6. El compilador emitirá a las sección.data...
    - ( ) Todas las variables inicializadas a un valor distinto de cero
    - (x) Todas las variables globales inicializadas a un valor distinto de cero
    - ( ) Todas las variables globales
    - ( ) Todas las variables

7. La instrucción bicles r1, r1, #4...
    - ( ) No es una instrucción válida en la arquitectura ARM
    - (x) Fija los flags de estado en función del resultado de la instrucción
    - ( ) Limpia el bit 4 de r1 sólo si el último resultado con el que se fijaron los flags de estado fue menor o igual que cero
    - ( ) Limpiará el bit 2 del registro r1

8. Cuando se está usando un procesador ARM, ¿cuál es el número máximo de argumentos que puede tener una función para que no se vea penalizada a la hora de invocarla?
    - ( ) El número de parámetros que tenga una función no influye en el tiempo que se invierte en invocarla
    - (x) 4
    - ( ) 8
    - ( ) 2

9. En la arquitectura ARM se pueden ejecutar condicionalmente...
    - ( ) Sólo los saltos (tanto globales como locales)
    - (x) Todas las instrucciones del repertorio
    - ( ) Sólo los saltos globales
    - ( ) Sólo los saltos locales

10. ¿Qué argumentos usa la instrucción bx?
    - ( ) Ninguna de las otras respuestas es correcta
    - (x) Un registro
    - ( ) Una dirección de memoria
    - ( ) Una etiqueta

11. ¿Cuántos registros de control/estado hay en la arquitectura ARM?
    - (x) 2: CPSR y SPSR
    - ( ) 1: Solo CPSR
    - ( ) 4: CPSR, SPSR, PC y LR
    - ( ) 16: Uno por cada registro de propósito general

12. Los procesadores de ARM implementan una arquitectura...
    - (x) Basada en la filosofía RISC, pero con algunas modificaciones
    - ( ) Pura CISC
    - ( ) Pura RISC sin excepciones ni extensiones
    - ( ) VLIW (Very Long Instruction Word)

13. ¿Cuál de las siguientes características es propia de los procesadores ARM?
    - (x) Su cauce está segmentado
    - ( ) QWQWQWQWQWQ

14. En un script de enlazado, las secciones de entrada...
    - (x) Son las que componen los ficheros objeto que se enlazarán para formar el fichero ejecutable final
    - ( ) Son las que se crearán en la memoria RAM tras la ejecución del programa
    - ( ) Son las secciones reservadas exclusivamente para el código del sistema operativo
    - ( ) Son las directivas que indican al enlazador dónde colocar la pila

15. Indica el modo al que cambia el procesador cuando se produce una excepción causada por una violación de acceso a memoria
    - (x) Abort
    - ( ) Undefined
    - ( ) Supervisor
    - ( ) IRQ

16. En la arquitectura ARM se pueden ejecutar condicionalmente...
    - (x) Todas las instrucciones del repertorio
    - ( ) XXXXXX

17. Indica cuál es la opción correcta para generar un inmediato con un valor arbitrario
    - (x) ldr r1, =VALOR
    - ( ) mov r1, #VALOR
    - ( ) add r1, r0, #VALOR
    - ( ) ldm r1, {VALOR}

18. ¿Que modos de ejecución comparten el mismo banco de registros?
    - (x) User y System
    - ( ) User y Supervisor
    - ( ) IRQ y FIQ
    - ( ) Supervisor y Abort

19. La dirección de carga de un símbolo...
    - (x) Apunta a una memoria en la que se almacena dicho símbolo de forma permanente en el sistema (ej. Flash o ROM)
    - ( ) Es la dirección de memoria en la que residirá el símbolo durante la ejecución en RAM
    - ( ) Es siempre idéntica a la dirección VMA para todas las secciones
    - ( ) Es una dirección relativa al registro PC

20. Si se desea acceder al campo edad de una estructura de datos, que está desplazado 16 bytes con respecto a la base de dicha estructura en memoria. Si la dirección base de la estructura está almacenada en el registro r1 además se desea que el registro r1 quede modificado con la direccion del campo accedido para posteriores accesos, ¿ que opcion es la correcta?
    - (x) ldr r0, [r1, #16]!
    - ( ) ldr r0, [r1], #16
    - ( ) ldr r0, [r1, #16]
    - ( ) str r0, [r1, #16]!

21. El ABI...
    - (x) Define la interfaz a bajo nivel entre un programa y el sistema operativo u otro programa
    - ( ) Define el repertorio de instrucciones binarias del procesador
    - ( ) Es el protocolo de comunicación serie síncrono del sistema
    - ( ) Es el cargador que reside en la ROM de arranque

22. ¿Como se puede modificar el valor de los flags de estado del procesador?
    - (x) Añadiendo el sufijo 's' a una instrucción
    - ( ) UHUJH

23. Indica en cuál de las siguientes opciones podrian coincidir las direcciones VMA con las LMA
    - (x) Para las constantes (.rodata) y código que se ejecute directamente desde Flash
    - ( ) Para las variables globales no inicializadas (.bss)
    - ( ) Para la pila (stack)
    - ( ) Para el heap

24. En un sript de enlazado, las secciones de entrada...
    - (x) Son las que componen los ficheros objeto que se enlazarán para formar el fichero ejecutable final.
    - ( ) SASAS

25. ¿Cuál de las siguientes instrucciones es la mejor opción para multiplicar el contenido del registro r1 por 8?
    - (x) mov r1, r1, lsl #3
    - ( ) KJKBJB

26. El compilador emitirá a las sección.data...
    - (x) Todas las variables globales inicializadas a un valor distinto de cero
    - ( ) ASASASASAS

27. La instrucción bicles r1, r1, #4...
    - (x) Fija los flags de estado en función del resultado de la instrucción
    - ( ) YYYY

28. ¿Qué argumentos usa la instrucción bx?
    - (x) Un registro
    - ( ) YGY

29. Cuando se provoca una excepción, el procesador...
    - (x) Copia la dirección de retorno en el registro lr del nuevo modo
    - ( ) Guarda el contador de programa directamente en la pila del modo User
    - ( ) Deshabilita automáticamente las interrupciones FIQ en todas las excepciones
    - ( ) Pone a cero todos los registros de propósito general

30. El repertorio de instrucciones thumb...
    - (x) Permite que el código de un programa ocupe menos memoria RAM (mayor densidad de código)
    - ( ) Ofrece mayor rendimiento de ejecución que las instrucciones ARM de 32 bits
    - ( ) Permite la ejecución condicional de todas sus instrucciones
    - ( ) Añade 16 registros adicionales de propósito general

31. De las siguientes direcciones de memoria,indica en cuál podría alojarse un entero de 32 bits para cumplir con las restricciones impuestas por el ABI de ARM.
    - (x) 0x0040542C
    - ( ) 0x0040542D
    - ( ) 0x0040542E
    - ( ) 0x0040542F

32. El compilador emitirá a las seccion.data
    - (x) Todas las variables globales inicializadas a un valor distinto de cero
    - ( ) SASASASAS

