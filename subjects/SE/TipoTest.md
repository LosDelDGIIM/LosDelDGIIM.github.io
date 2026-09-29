# Sistemas Empotrados - Preguntas Tipo Test

- **Descripción:** Recopilación exhaustiva de preguntas Tipo Test de Teoría de la asignatura de Sistemas Empotrados (Grado en Ingeniería Informática - Mención en Ingeniería de Computadores, UGR). Abarca los temas 1 al 5: Introducción a Sistemas Empotrados, Procesador ARM, Jerarquía de Memoria, Excepciones e Interrupciones, y Entrada/Salida, Drivers y BSP.

---

1. Para mejorar las prestaciones del sistema, se pueden usar circuitos específicos (co-procesadores o aceleradores) que implementen ciertas funciones clave
    - (x) Los co-procesadores se gestionan mediante instrucciones específicas de la CPU y los aceleradores mediante instrucciones load/store
    - ( ) No hay diferencia. Ambos se gestionan mediante instrucciones load/store
    - ( ) Los aceleradores se gestionan mediante instrucciones específicas de la CPU y los co-procesadores mediante instrucciones load/store
    - ( ) No hay diferencia. Ambos se gestionan mediante instrucciones específicas

2. Una tableta...
    - ( ) Es un sistema empotrado porque está basada en un SoC
    - ( ) Es un sistema empotrado porque su diseño minimiza su consumo energético
    - (x) No es un sistema empotrado porque se le pueden instalar aplicaciones para múltiples fines
    - ( ) No es un sistema empotrado porque usa un SO de propósito general

3. La partición HW/SW...
    - (x) Se lleva a cabo en cualquier metodología de diseño
    - ( ) No forma parte del proceso de co-diseño de un sistema empotrado
    - ( ) No forma parte del proceso de diseño basado en plataformas
    - ( ) Sólo se lleva a cabo en la metodología clásica de diseño de sistemas empotrados

4. Un entorno inteligente es...
    - (x) Un entorno físico dotado de sensores y actuadores conectados a un servidor que los gestiona de forma inteligente
    - ( ) Un entorno en el que se ha desplegado una red de sensores
    - ( ) Un entorno en el que hay desplegados dispositivos inteligentes
    - ( ) Ninguna de las otras respuestas es correcta

5. Se desea implementar un robot aspirador con posibilidad de configuración mediante una interfaz Web. ¿Cuál de las siguientes opciones sería las más adecuada para el software de sistema?
    - (x) Portar un GPOS para nuestra plataforma que haga uso de nuestro BSP, y diseñar la aplicación de forma que haga uso de los servicios del GPOS
    - ( ) Desarrollar la aplicación haciendo uso directamente de los servicios proporcionados por nuestro BSP
    - ( ) Usar un middleware de comunicaciones que implemente un servidor Web
    - ( ) Portar un RTOS para nuestra plataforma que haga uso de nuestro BSP, y diseñar la aplicación de forma que haga uso de los servicios del RTOS

6. Un smart device es...
    - ( ) Un dispositivo móvil con GPS y pantalla
    - ( ) Un dispositivo que ejecuta algoritmos de inteligencia artificial
    - ( ) Un dispositivo con multitud de sensores
    - (x) Un dispositivo que transmite información contextual del usuario a la nube

7. Con un editor de textos...
    - ( ) No se podría desarrollar la parte HW de un sistema empotrado
    - ( ) Sólo se podría desarrollar la parte SW de un sistema empotrado
    - ( ) Sólo se podría desarrollar la parte HW de un sistema empotrado
    - (x) Se podría desarrollar un sistema empotrado completo

8. Dentro de los componentes HW de un sistema, los controladores de sistema..
    - (x) Coordinan los componentes importantes del sistema
    - ( ) Ejecutan funciones complejas mediante hardware específico
    - ( ) Proporcionan las capacidades de E/S del sistema
    - ( ) Ejecutan el software de la aplicación

9. Un core IP soft..
    - ( ) Un core IP no puede ser soft, ya que describe un diseño HW
    - ( ) Contiene el diseño de una función software que nos viene bien para nuestro sistema
    - ( ) Contiene el diseño de una parte HW de nuestro sistema, por lo que no podemos modificarla
    - (x) Contiene el diseño de una parte HW que puede modificarse y adaptarse a nuestro diseño y a nuestra tecnología de implementación

10. A la hora de implementar un SoC..
    - ( ) Es mejor fabricarlo mediante una FPGA
    - ( ) Es necesario mandarlo a una fundición para que fabrique el chip
    - ( ) Es mejor fabricarlo mediante un ASIC
    - (x) Ninguna de las otras respuestas es correcta

11. Al tener parte de las funciones implementadas en software, los sistemas empotrados permiten
    - (x) Implementar sistemas actualizables
    - ( ) Implementación del software y hardware
    - ( ) mejorar al hardware
    - ( ) mejorar el software

12. El middleware.....
    - (x) Proporciona interoperabilidad en los sistemas empotrados distribuidos.
    - ( ) mejora el hardware
    - ( ) mejora el software
    - ( ) todas son falsas

13. A la hora de seleccionar el procesador más adecuado para un sistema empotrado.
    - ( ) Selecionar siempre aquel que obtenga mejores prestaciones para la aplicacion.
    - ( ) Se debe escoger siempre el que menos energia consuma.
    - ( ) Se debe escoger el mas barato para no penalizar el coste total.
    - (x) Ninguna de las anteriores es correcta.

14. ¿Que es Dhrystone?
    - (x) Es un programa escrito en c con instruciones generadas de forma arbitraria.
    - ( ) está escrito en c++
    - ( ) son todas falsas
    - ( ) Es un programa escrito en emsamblador

15. Dentro de los componentes de HW de un sistema,los controladores e sistema..
    - ( ) mejora la cpu
    - ( ) se encarga de la cpu
    - (x) Coordinan los componentes importantes del sistema.
    - ( ) Todas son falsas

16. Para mejorar las prestaciones del sistema,se pueden usar circuitos específicos (Co-procesadores o aceleradores) que implemente ciertas funciones clave
    - ( ) Hacen uso de un acelerador
    - ( ) Hacen uso de procesador para llevar a cabo la mejora de las prestaciones
    - (x) Los co-procesadores se gestionan mediante instrucciones específicas de la cpu y los aceleradores mediente instrucciones load/store.
    - ( ) Todas son falsas

17. ¿Cómo se puede modificar el valor de los flags de estado del procesador?
    - ( ) Solamente mediante el uso de instrucciones de comparación
    - ( ) Añadiendo a cualquier instrucción los sufijos de condición (lt, gt, eq,...)
    - ( ) Ejecutando cualquier instrucción. Los flags se fijarán en función del resultado
    - (x) Añadiendo el sufijo 's' a una instrucción

18. Las instrucciones ldrsb y ldrsh cargan un entero de 8 y 16 bits respectivamente en la parte menos significativa de un registro de 32 bits. ¿Qué hacen dichas instrucciones con la parte más significativa del registro, no ocupada por el dato que se ha cargado?
    - ( ) Se rellenan dichos bits con el valor 0
    - (x) Se extiende el signo del dato
    - ( ) Se dejan inalterados
    - ( ) Se rellenan dichos bits con el valor 1

19. Si la instrucción ldr r0, [pc, #2] está en la dirección 0x00400320 de memoria, ¿a qué dirección se accederá para cargar el dato?
    - ( ) 0x00400330
    - (x) 0x0040032A
    - ( ) 0x00400320
    - ( ) 0x00400322

20. ¿Cuál de las siguientes instrucciones es la mejor opción para multiplicar el contenido del registro r1 por 8?
    - ( ) lsl r1, r1, #3
    - (x) mov r1, r1, lsl #3
    - ( ) mul r1, r1, #8
    - ( ) El procesador ARM7TDMI no tiene multiplicador, por tanto no podemos multiplicar

21. ¿Cuál de las siguientes características es propia de los procesadores ARM?
    - ( ) Las instrucciones pueden operar con operando almacenados en memoria
    - (x) Su cauce está segmentado
    - ( ) El código tiende a ser más compacto
    - ( ) Se deben programar en ensamblador para obtener mejores prestaciones

22. El compilador emitirá a las sección.data...
    - ( ) Todas las variables inicializadas a un valor distinto de cero
    - (x) Todas las variables globales inicializadas a un valor distinto de cero
    - ( ) Todas las variables globales
    - ( ) Todas las variables

23. La instrucción bicles r1, r1, #4...
    - ( ) No es una instrucción válida en la arquitectura ARM
    - (x) Fija los flags de estado en función del resultado de la instrucción
    - ( ) Limpia el bit 4 de r1 sólo si el último resultado con el que se fijaron los flags de estado fue menor o igual que cero
    - ( ) Limpiará el bit 2 del registro r1

24. Cuando se está usando un procesador ARM, ¿cuál es el número máximo de argumentos que puede tener una función para que no se vea penalizada a la hora de invocarla?
    - ( ) El número de parámetros que tenga una función no influye en el tiempo que se invierte en invocarla
    - (x) 4
    - ( ) 8
    - ( ) 2

25. En la arquitectura ARM se pueden ejecutar condicionalmente...
    - ( ) Sólo los saltos (tanto globales como locales)
    - (x) Todas las instrucciones del repertorio
    - ( ) Sólo los saltos globales
    - ( ) Sólo los saltos locales

26. ¿Qué argumentos usa la instrucción bx?
    - ( ) Ninguna de las otras respuestas es correcta
    - (x) Un registro
    - ( ) Una dirección de memoria
    - ( ) Una etiqueta

27. ¿Cuántos registros de control/estado hay en la arquitectura ARM?
    - (x) 2: CPSR y SPSR
    - ( ) 1: Solo CPSR
    - ( ) 4: CPSR, SPSR, PC y LR
    - ( ) 16: Uno por cada registro de propósito general

28. Los procesadores de ARM implementan una arquitectura...
    - (x) Basada en la filosofía RISC, pero con algunas modificaciones
    - ( ) Pura CISC
    - ( ) Pura RISC sin excepciones ni extensiones
    - ( ) VLIW (Very Long Instruction Word)

29. En un script de enlazado, las secciones de entrada...
    - (x) Son las que componen los ficheros objeto que se enlazarán para formar el fichero ejecutable final
    - ( ) Son las que se crearán en la memoria RAM tras la ejecución del programa
    - ( ) Son las secciones reservadas exclusivamente para el código del sistema operativo
    - ( ) Son las directivas que indican al enlazador dónde colocar la pila

30. Indica el modo al que cambia el procesador cuando se produce una excepción causada por una violación de acceso a memoria
    - (x) Abort
    - ( ) Undefined
    - ( ) Supervisor
    - ( ) IRQ

31. Indica cuál es la opción correcta para generar un inmediato con un valor arbitrario
    - (x) ldr r1, =VALOR
    - ( ) mov r1, #VALOR
    - ( ) add r1, r0, #VALOR
    - ( ) ldm r1, {VALOR}

32. ¿Que modos de ejecución comparten el mismo banco de registros?
    - (x) User y System
    - ( ) User y Supervisor
    - ( ) IRQ y FIQ
    - ( ) Supervisor y Abort

33. La dirección de carga de un símbolo...
    - (x) Apunta a una memoria en la que se almacena dicho símbolo de forma permanente en el sistema (ej. Flash o ROM)
    - ( ) Es la dirección de memoria en la que residirá el símbolo durante la ejecución en RAM
    - ( ) Es siempre idéntica a la dirección VMA para todas las secciones
    - ( ) Es una dirección relativa al registro PC

34. Si se desea acceder al campo edad de una estructura de datos, que está desplazado 16 bytes con respecto a la base de dicha estructura en memoria. Si la dirección base de la estructura está almacenada en el registro r1 además se desea que el registro r1 quede modificado con la direccion del campo accedido para posteriores accesos, ¿ que opcion es la correcta?
    - (x) ldr r0, [r1, #16]!
    - ( ) ldr r0, [r1], #16
    - ( ) ldr r0, [r1, #16]
    - ( ) str r0, [r1, #16]!

35. El ABI...
    - (x) Define la interfaz a bajo nivel entre un programa y el sistema operativo u otro programa
    - ( ) Define el repertorio de instrucciones binarias del procesador
    - ( ) Es el protocolo de comunicación serie síncrono del sistema
    - ( ) Es el cargador que reside en la ROM de arranque

36. ¿Como se puede modificar el valor de los flags de estado del procesador?
    - (x) Añadiendo el sufijo 's' a una instrucción
    - ( ) UHUJH

37. Indica en cuál de las siguientes opciones podrian coincidir las direcciones VMA con las LMA
    - (x) Para las constantes (.rodata) y código que se ejecute directamente desde Flash
    - ( ) Para las variables globales no inicializadas (.bss)
    - ( ) Para la pila (stack)
    - ( ) Para el heap

38. En un sript de enlazado, las secciones de entrada...
    - (x) Son las que componen los ficheros objeto que se enlazarán para formar el fichero ejecutable final.
    - ( ) SASAS

39. Cuando se provoca una excepción, el procesador...
    - (x) Copia la dirección de retorno en el registro lr del nuevo modo
    - ( ) Guarda el contador de programa directamente en la pila del modo User
    - ( ) Deshabilita automáticamente las interrupciones FIQ en todas las excepciones
    - ( ) Pone a cero todos los registros de propósito general

40. El repertorio de instrucciones thumb...
    - (x) Permite que el código de un programa ocupe menos memoria RAM (mayor densidad de código)
    - ( ) Ofrece mayor rendimiento de ejecución que las instrucciones ARM de 32 bits
    - ( ) Permite la ejecución condicional de todas sus instrucciones
    - ( ) Añade 16 registros adicionales de propósito general

41. De las siguientes direcciones de memoria,indica en cuál podría alojarse un entero de 32 bits para cumplir con las restricciones impuestas por el ABI de ARM.
    - (x) 0x0040542C
    - ( ) 0x0040542D
    - ( ) 0x0040542E
    - ( ) 0x0040542F

42. El compilador emitirá a las seccion.data
    - (x) Todas las variables globales inicializadas a un valor distinto de cero
    - ( ) SASASASAS

43. ¿Cuántas pilas necesitan los sistemas basados en procesadores ARM?
    - ( ) Solamente una pila
    - ( ) Una para el modo USER, otra para los modos de interrupción y otra para el resto de modos
    - (x) Una para cada modo de ejecución privilegiado
    - ( ) Una para el modo de ejecución USER y otra para los modos privilegiados

44. Las direcciones VMA y LMA podrían coincidir en...
    - (x) El código de la aplicación
    - ( ) Las variables locales
    - ( ) Las variables globales inicializadas
    - ( ) Las variables globales sin inicializar

45. El boot loader
    - (x) No puede escribirse completamente en C
    - ( ) Es una parte opcional del BSP
    - ( ) Debe escribirse en ensamblador
    - ( ) Se auto-copia en la RAM para ejecutarse más rápido

46. En el caso de que el enlazador genere direcciones LMA y VMA diferentes para la aplicación, la aplicación usará...
    - ( ) Tanto direcciones VMA como LMA, pero nunca simultáneamente Incorrecto.
    - (x) Sólo direcciones VMA
    - ( ) Sólo direcciones LMA
    - ( ) Tanto las direcciones VMA como las LMA, de forma simultánea

47. Las variables locales...
    - ( ) Son almacenadas por el linker en la sección.bss
    - (x) Se crean en la pila cada vez que se invoca a la función en la que se han declarado
    - ( ) Son almacenadas por el linker en la sección.data
    - ( ) Ninguna de las otras respuestas es correcta

48. La expresión. = ALIGN(4);
    - ( ) Se usa en los ficheros ensamblador para forzar un alineamiento a la siguiente frontera de 32 bits
    - ( ) Se usa en el linker script para forzar un alineamiento a la siguiente frontera de 4 bits
    - (x) Se usa en el linker script para forzar un alineamiento a la siguiente frontera de 32 bits
    - ( ) Se usa en los ficheros ensamblador para forzar un alineamiento a la siguiente frontera de 4 bits

49. Asumiendo que el código del cargador está en la sección.startup, que el código del resto de la aplicación está en la sección.text, y que el sistema tiene mapeada una memoria flash a la dirección 0x00000000 y una memoria RAM a la dirección 0x03000000, indica cual de las siguientes opciones para la implementación de la directiva SECTIONS del script de enlazado permite cargar la aplicación y ejecutarla desde la RAM
    - ( ) .image: { *(.text); *(.startup); } > ram AT > flash
    - (x) .startup: { *(.startup); } > flash;.text: { *(.text); } > ram AT > flash
    - ( ) .image: { *(.startup); *(.text); } > flash
    - ( ) .image: { *(.startup); *(.text); } > ram AT > flash

50. A la hora de implementar un sistema empotrado, la función main...
    - (x) No debe retornar jamás
    - ( ) Sólo retornará en caso de error
    - ( ) Retornará un cero si se ha ejecutado correctamente
    - ( ) Retornará un valor distinto de cero si se ha ejecutado correctamente

51. Las variables globales no inicializadas por el programador...
    - ( ) Se inicializan siempre a cero en el linker script
    - (x) Son emitidas a la sección COMMON por el compilador
    - ( ) Se inicializan siempre a cero por el compilador
    - ( ) Son emitidas a la sección.bss por el compilador

52. El registro sp se inicializa por...
    - ( ) El compilador
    - ( ) La CPU al arrancar
    - ( ) El linker
    - (x) El cargador de arranque

53. El remapeo de memoria...
    - (x) Permite que la aplicación o el SO puedan modificar los vectores de excepción en cualquier momento remapeando la dirección 0 a la RAM
    - ( ) Solo es útil para aumentar la velocidad de acceso a la memoria Flash
    - ( ) Se realiza exclusivamente por software sin necesidad de soporte hardware
    - ( ) Es obligatorio para poder inicializar la memoria caché de datos

54. La tabla de manejadores de excepción...
    - (x) Contiene punteros a función
    - ( ) Contiene instrucciones de salto directo B o LDR PC
    - ( ) Está implementada en hardware dentro de la CPU ARM
    - ( ) Reside permanentemente en la memoria ROM del fabricante

55. El código de la aplicación no se modificará en tiempo de ejecución.
    - (x) Sin embargo, se puede copiar a la RAM del sistema para que su ejecución sea más rápida
    - ( ) Por tanto, nunca tiene sentido copiarlo a la memoria RAM
    - ( ) Por lo que sus direcciones VMA y LMA siempre deben coincidir obligatoriamente
    - ( ) Lo que impide que pueda llamar a funciones externas del BSP

56. Las direcciones VMA y LMA siempre deben ser diferentes para..
    - (x) Las variables globales inicializadas (.data)
    - ( ) El código del programa (.text) si se ejecuta desde Flash
    - ( ) Las constantes (.rodata) cuando no se copian a RAM
    - ( ) La tabla de vectores fija en ROM

57. Los símbolos _data_start y _data_end
    - (x) Siempre definen direcciones dentro de la RAM del sistema
    - ( ) Definen la posición permanente de los datos en la memoria Flash
    - ( ) Son definidos automáticamente por el hardware de la CPU
    - ( ) Delimitan el espacio reservado para la pila del modo Supervisor

58. Indica el modo de ejecución al que pasa un procesador ARM tras la pulsación del botón Reset
    - (x) Supervisor
    - ( ) User
    - ( ) System
    - ( ) Undefined

59. ¿Qué debe haber siempre en la dirección 0 de memoria en un sistema basado en un procesador ARM?
    - (x) Un salto al cargador del sistema
    - ( ) La función main de la aplicación
    - ( ) La pila del modo User
    - ( ) La tabla de dispositivos del sistema

60. Las direcciones de inicio y fin del heap...
    - (x) Se definen explícitamente en el linker script
    - ( ) Vienen fijadas por el hardware del procesador ARM
    - ( ) Son calculadas dinámicamente por la función malloc en cada llamada
    - ( ) Coinciden siempre con el inicio y fin de la memoria Flash

61. ¿Cual de los siguientes pasos ejecuta antes el boot loader?
    - (x) Inicializar la tabla de vectores de excepción
    - ( ) Ejecutar la función main de la aplicación
    - ( ) Registrar los dispositivos en la tabla de Newlib
    - ( ) Inicializar el driver L1 de la UART

62. Cuando se provoca una excepción, el procesador almacena en lr la dirección de retorno antes de pasar a ejecutar su manejador. Por lo tanto, a la hora de escribir un manejador de excepción, para poder retornar a la aplicación...
    - (x) Es necesario ajustar el registro lr en función del tipo de excepción antes de retornar
    - ( ) Sólo es necesario copiar el contenido del registro lr en el registro pc
    - ( ) Siempre hay que restar 4 bytes al registro lr antes de retornar
    - ( ) Se debe usar la instrucción ret, que se encargará de hacer el ajuste de lr y retornar

63. Indica cuál de las siguientes opciones define correctamente un tipo de datos adecuado para poder gestionar en C la instalación de manejadores de excepción en el BSP
    - ( ) typedef void (* excep_handler_t) (int);
    - ( ) typedef int (* excep_handler_t) (void);
    - ( ) typedef int (* excep_handler_t) (int);
    - (x) typedef void (* excep_handler_t) (void);

64. Teniendo en cuenta que la arquitectura del ARM7TDMI tiene 8 vectores de excepción, la dirección del vector FIQ es...
    - ( ) 0x00000028
    - ( ) 0x00000032
    - ( ) 0x00000020
    - (x) 0x0000001C

65. Conforme más dispositivos hay en el sistema, la latencia de las interrupciones...
    - ( ) Aumenta sólo si hay controlador de interrupciones
    - ( ) Siempre aumenta
    - ( ) Siempre disminuye
    - (x) Aumenta sólo si no hay controlador de interruciones

66. Indica qué relación existe entre las excepciones y los modos de ejecución de los procesadores ARM
    - (x) Algunos modos de ejecución privilegiados son compartidos por excepciones similares
    - ( ) Existe un único modo privilegiado para todas las excepciones y un modo user para ejecutar las aplicaciones
    - ( ) Cada tipo de excepción tiene asociado un modo de ejecución privilegiado diferente
    - ( ) Los procesadores ARM no tienen modos privilegiados

67. En el diseño jerárquico del mecanismo de atención de interrupciones de un BSP, la implementación de las ISR depende de...
    - (x) El dispositivo que ha solicitado la interrupción
    - ( ) La arquitectura del procesador del sistema
    - ( ) El controlador de interrupciones del sistema
    - ( ) La tabla de vectores de excepción

68. Cuando llega a la CPU una petición de interrupción FIQ, ¿cómo se identifica la fuente?
    - ( ) Mediante el controlador de interrupciones
    - ( ) Mediante el manejador de nivel 1
    - ( ) Mediante el manejador de nivel 0
    - (x) No es necesario identificar la fuente

69. Si nuestro sistema dispone de un controlador de interrupciones vectorizado...
    - ( ) La priorización de interrupciones se debe implementar en software
    - ( ) La búsqueda de la ISR de la fuente más prioritaria se debe hacer en SW
    - ( ) No es necesario diseñar ISRs para los dispositivos
    - (x) El BSP no necesita de un manejador para buscar la ISR de la fuente de interrupción más prioritaria

70. Cuando se ejecute una aplicación, la existencia de una condición de carrera entre el código de la aplicación y el código del driver de un dispositivo...
    - (x) No siempre provocará resultados incorrectos
    - ( ) Siempre provocará resultados incorrectos
    - ( ) Siempre provocará resultados correctos
    - ( ) Es algo habitual en los sistemas gestionados mediante interrupciones

71. En un sistema con soporte para interrupciones anidadas...
    - (x) El dispositivo más prioritario siempre será atendido por la CPU
    - ( ) Cualquier dispositivo podrá interrumpir el servicio de una interrupción
    - ( ) La ISR del dispositivo más prioritario podrá ser interrumpida por otra fuente de interrupción
    - ( ) Las peticiones de interrupción se atienden según el orden en el que se hayan producido

72. Indica en qué parte del registro cpsr se encuentran los flags de estado (signo, acarreo, overflow y cero)
    - (x) Bits 24-31 (o 28-31 para los flags de condición N, Z, C, V)
    - ( ) Bits 0-7
    - ( ) Bits 8-15
    - ( ) Bits 16-23

73. ¿Qué relación existe entre las excepciones y las interrupciones?
    - (x) Una interrupción es un tipo de excepción producida por un evento hardware externo
    - ( ) Son conceptos totalmente independientes y no relacionados
    - ( ) Todas las excepciones son provocadas por dispositivos externos
    - ( ) Las interrupciones solo ocurren en modo User y las excepciones en modo Supervisor

74. La modificación de los bits I y F del registro de estado de la CPU...
    - (x) Se debe hacer en ensamblador porque las instrucciones de gestión del registro CPSR no se pueden generar en C
    - ( ) Se puede realizar mediante una simple asignación a un puntero en C
    - ( ) No está permitida en ningún modo de ejecución privilegiado
    - ( ) Se produce de forma automática al invocar a cualquier función del BSP

75. Indica cuántos pines dedican los procesadores ARM a la atención de interrupciones de dispositivos externos
    - (x) 2 (nIRQ y nFIQ)
    - ( ) 4
    - ( ) 8
    - ( ) 16

76. En el diseño jerárquico del mecanismo de atención de interrupciones de un BSP, la implementación del manejador de nivel 0 depende de...
    - (x) La arquitectura del procesador del sistema
    - ( ) El controlador de interrupciones del sistema
    - ( ) Los periféricos concretos que se conecten en la placa
    - ( ) La aplicación de usuario

77. Indica cuál de las siguientes excepciones está directamente relacionada con la gestión de dispositivos de E/S
    - (x) Interrupt ReQuest (IRQ)
    - ( ) Undefined Instruction
    - ( ) Prefetch Abort
    - ( ) Software Interrupt (SWI)

78. Cuando el BSP implementa un esquema de gestión de interrupciones anidadas, ¿en qué modo de ejecución estará el procesador cuando ejecute la ISR de un dispositivo?
    - (x) Supervisor (SVC)
    - ( ) IRQ
    - ( ) User
    - ( ) FIQ

79. Si en el script de enlazado del BSP se ha definido el símbolo _excep_handlers para indicar la dirección de memoria en la que estará la tabla de manejadores de excepción del BSP, y en el fichero excep.h se ha definido el tipo _excep_handler_t para poder gestionar los manejadores de excepción, indica cual de las siguientes declaraciones es la que permite acceder correctamente a la tabla de manejadores desde C
    - (x) extern excep_handler_t _excep_handlers[];
    - ( ) extern excep_handler_t * _excep_handlers();
    - ( ) excep_handler_t _excep_handlers;
    - ( ) static excep_handler_t _excep_handlers[];

80. Para poder identificar la fuente más prioritaria de una petición de interrupción en un sistema...
    - (x) No es necesario que el sistema disponga de un controlador de interrupciones (puede resolverse mediante sondeo/polling en software)
    - ( ) Es imprescindible contar con un controlador de interrupciones vectorial en hardware
    - ( ) Es necesario que todos los dispositivos compartan la misma línea de interrupción
    - ( ) La CPU debe estar ejecutando siempre en modo FIQ

81. Indica qué fuente de interrupción tendrá la menor latencia en un sistema ARM
    - (x) Aquella fuente que esté conectada al pin nFIQ de la CPU
    - ( ) Aquella conectada a través del controlador de interrupciones al pin nIRQ
    - ( ) Cualquier interrupción generada por software (SWI)
    - ( ) Una interrupción por desbordamiento del temporizador en modo IRQ

82. Para poder gestionar una interrupción IRQ, y si no necesitamos interrupciones anidadas, es necesario escribir en ensamblador...
    - (x) Nada. Todo el tratamiento de interrupciones se puede escribir en C si el compilador soporta atributos de interrupción o el manejador N0 gestiona el contexto
    - ( ) Todo el código del driver y la aplicación en ensamblador
    - ( ) La rutina de servicio completa obligatoriamente en ensamblador
    - ( ) El código de inicialización de la UART obligatoriamente

83. Indica la opción que, evitando que la UART pueda interrumpir a la CPU cuando haya recibido un nuevo dato, implique la mínima degradación de las prestaciones del sistema
    - (x) Configurando el dispositivo para deshabilitar la petición de interrupciones debidas a la recepción de nuevos datos
    - ( ) Deshabilitando globalmente las interrupciones en la CPU con el bit I del CPSR
    - ( ) Desconectando físicamente el pin de la UART
    - ( ) Enmascarando todas las fuentes en el controlador de interrupciones

84. Indica en qué parte del registro cpsr se encuentran los bits de control (modo de ejecución, habilitación de interrupciones y thumb)
    - (x) Bits 0-7
    - ( ) Bits 8-15
    - ( ) Bits 16-23
    - ( ) Bits 24-31

85. Indica qué relación existe entre las prioridades de las excepciones Software Interrupt y Undefined Instruction
    - (x) Las dos tienen la misma prioridad
    - ( ) Tiene más prioridad la primera
    - ( ) Tiene más prioridad la segunda
    - ( ) Depende de la configuración del registro CPSR

86. Indica cuál de los siguientes eventos no provocará una excepción
    - (x) Que la CPU genere un valor tras una operación aritmética que no quepa en un registro (overflow)
    - ( ) Una instrucción no reconocida por el decodificador
    - ( ) Un acceso a una dirección de memoria no válida
    - ( ) Una petición externa a través de la línea nIRQ

87. El registro spsr...
    - (x) No existe en modo User
    - ( ) No existe en modo Supervisor
    - ( ) Contiene la dirección de retorno tras una llamada a subrutina
    - ( ) Es compartido por todos los modos sin duplicarse

88. El código de salida de una región crítica implementada a nivel de CPU debe...
    - (x) Restaurar el valor de los bits I y F al que tenían antes de entrar en la región crítica
    - ( ) Pone siempre los bits I y F a cero sin importar su estado previo
    - ( ) Cambiar el modo del procesador a modo User
    - ( ) Limpiar todos los flags de estado en el CPSR

89. En el diseño jerárquico del mecanismo de atención de interrupciones de un BSP, la implementación del manejador de nivel 1 depende de...
    - (x) El controlador de interrupciones del sistema
    - ( ) La arquitectura del procesador del sistema
    - ( ) El compilador de C utilizado
    - ( ) La aplicación de usuario

90. Indica la forma correcta de portar a una placa como la Econotag las llamadas a sistema de la biblioteca Newlib necesarias para hacer E/S mediante el estándar POSIX
    - (x) Implementando las funciones stub _open, _close, _read, _write, _lseek, _isatty y _fstat
    - ( ) No es posible hacer uso de funciones Posix en una plataforma con tan pocos recursos
    - ( ) Implementando las funciones de E/S estándar printf y scanf
    - ( ) Implementando las llamadas a sistema open, close, read, write,lseek, isatty y fstat

91. Asumiendo que gpio_regs_t es un tipo de datos definido en el BSP para facilitar el acceso a los registros de control/estado del GPIO y que GPIO_BASE es un símbolo que contiene la dirección base de los registros del GPIO en el mapa de memoria de la placa, ¿cual de las siguientes declaraciones permite acceder correctamente en C a los registros del GPIO?
    - ( ) static volatile const gpio_regs_t* gpio_regs =GPIO_BASE;
    - ( ) static const gpio_regs_t* gpio_regs = GPIO_BASE;
    - ( ) static gpio_regs_t* const gpio_regs = GPIO_BASE;
    - (x) static volatile gpio_regs_t* const gpio_regs =GPIO_BASE;

92. ¿Se pueden modificar simultáneamente varios bits en un registro de control de un dispositivo?
    - ( ) Sí, mediante el uso de máscaras de bits para escribir en un campo de una estructura bitfields
    - ( ) No se puede
    - (x) Sí, mediante el uso de máscaras de bits para escribir en el registro
    - ( ) Sí, mediante la definición del registro como una estructura con bitfields

93. Indica cuál de las siguientes características no es propia de un driver L0
    - ( ) Configuración por defecto del dispositivo
    - ( ) Envío y recepción bloqueantes
    - ( ) E/S controlada por el programa
    - (x) Chequeo de errores

94. En el caso de que nuestro sistema tenga varias instancias de un tipo de dispositivo (por ejemplo dos UART), y los registros del mismo tipo (control, datos, etc.) de cada una de las instancias de dispositivo estén agrupadas en el mapa de memoria, ¿qué estructura es la más adecuada para gestionar los registros de los dispositivos?
    - (x) Una estructura de arrays
    - ( ) Un array de estructuras
    - ( ) Un array de punteros a estructuras
    - ( ) Una estructura de estructuras

95. Indica qué palabra clave es imprescindible a la hora de definir un puntero para poder acceder a los registros de configuración de un dispositivo
    - (x) volatile
    - ( ) register
    - ( ) static
    - ( ) static

96. Las operaciones de E/S de los drivers de nivel 1...
    - (x) Se apoyan en dos búferes circulares, uno para lectura y otro para escritura
    - ( ) Están basadas en el uso de ficheros estándarv
    - ( ) Usan un único búfer para almacenar las transferencias pendientes
    - ( ) Mandan y reciben los datos directamente hacia o desde el dispositivo

97. Indica cuál de las siguientes partes del BSP hace posible que se puedan usar las funciones C estándar fprintf o fscanf para hacer E/S formateada sobre la UART de un sistema empotrado
    - (x) El driver L2 de la UART
    - ( ) El driver del GPIO
    - ( ) El driver L1 de la UART
    - ( ) El driver L0 de la UART

98. Dado que los búferes circulares de un driver L1 se acceden concurrentemente por la ISR del driver y por las funciones de envío y recepción, es necesario gestionar su acceso mediante regiones críticas para evitar condiciones de carrera. Indica cual de las siguientes opciones define correctamente una región crítica para el acceso al búfer de recepción de un driver
    - (x) En la función receive. Se debe anular la generación de interrupciones de recepción antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso
    - ( ) En la función receive. Se debe enmascarar la atención de interrupciones en los bits I/F del registro de control de la CPU antes de acceder al búfer y restaurarla una vez que se ha terminado el acceso
    - ( ) En la ISR del dispositivo. Se debe anular la generación de interrupciones de recepción antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso
    - ( ) En la función receive. Se debe anular la generación de interrupciones por parte del dispositivo en el controlador de interrupciones antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso

99. En el caso de que nuestro sistema tenga varias instancias de un tipo de dispositivo (por ejemplo tres temporizadores), y cada uno de las instancias tenga sus propios registros agrupados a partir de una dirección base en el mapa de memoria, ¿qué estructura es la más adecuada para gestionar los registros de los dispositivos?
    - (x) Un array de punteros a estructuras
    - ( ) Un array de estructuras
    - ( ) Una estructura de arrays
    - ( ) Una estructura de estructuras

100. Indica cual de las siguientes funciones lee datos del búfer de envío de un driver L1
    - (x) La ISR del driver
    - ( ) La función de inicialización del driver
    - ( ) La función send del driver
    - ( ) La función receive del driver

101. En el mapa de memoria de un dispositivo se han dejado 32 bytes reservados. Indica la opción correcta rellenar dicho espacio en la estructura de datos que debe gestionar los registros de E/S de dicho dispositivo
    - (x) uint32_t padding [4]
    - ( ) uint32_t padding
    - ( ) uint32_t padding [32]
    - ( ) uint4_t padding [32]

102. Indica cuál de las siguientes opciones describe la forma correcta en la que se puede usar el BSP desarrollado en la asignatura para que una aplicación pueda hacer E/S concurrente mientras se está ejecutando
    - ( ) Haciendo uso de las funciones de envío y recepción basadas en búferes
    - (x) Desarrollando funciones callback de envío y recepción y registrándolas en el driver de la UART
    - ( ) Haciendo uso de las funciones de envío y recepción bloqueantes del driver
    - ( ) Escribiendo una ISR para la UART a la medida de la aplicación

103. Indica qué opción es más adecuada para acceder cómodamente en C a los registros de E/S de un dispositivo, suponiendo que sólo hay una instancia del dispositivo y que sus registros están mapeados a la memoria del sistema
    - ( ) Definiendo una estructura con campos de un tamaño adecuado para que se ajuste al mapa de registros del dispositivo
    - (x) Definiendo una estructura de datos que se ajuste al mapa de memoria de los registros del dispositivo y creando un puntero a dicha estructura que apunte a la base de los registros en el mapa de memoria
    - ( ) Mediante un puntero que apunte a la base de los registros de E/S del dispositivo
    - ( ) Mediante una colección de punteros que apunten a los diferentes registros del dispositivo

104. Si se invoca a una syscall de Newlib con descriptor de fichero no válido o bien con un descriptor de fichero abierto sobre un dispositivo que no tiene implementada dicha función...
    - ( ) Se abortará la ejecución de la aplicación
    - (x) Se ejecutará la implementación por defecto para dicha syscall
    - ( ) Este caso no es posible. Todos los dispositivos deben implementar todas las syscalls
    - ( ) Se retornará -1 y se fijará la variable global errno al valor adecuado

105. La lista de dispositivos del BSP...
    - ( ) Debe ser inicializada por la aplicación, en función de los dispositivos que necesite
    - (x) Almacena todos los dispositivos del sistema que se pueden tratar como ficheros junto con punteros a las funciones que implementan la interfaz POSIX de tratamiento de ficheros para cada dispositivo
    - ( ) Forma parte de la implementación del driver de nivel 1 de un dispositivo
    - ( ) Asocia descriptores de fichero a los diferentes dispositivos del sistema

106. Indica la opción correcta para diseñar una estructura de datos que permita acceder directamente tanto a un registro de control completo mediante máscaras de bits como a cada uno de sus campos de forma individual
    - ( ) Definiendo una unión de un campo de bits (bitfield) y un uint32_t
    - ( ) Definiendo una unión anónima de un campo de bits (bitfield) y un uint32_t
    - ( ) No es posible diseñar una estructura de datos que permita acceder a los registros de control de esta forma
    - (x) Definiendo una unión anónima de un campo de bits anónimo (bitfield) y un uint32_t

107. Dado que los búferes circulares de un driver L1 se acceden concurrentemente por la ISR del driver y por las funciones de envío y recepción, es necesario gestionar su acceso mediante regiones críticas para evitar condiciones de carrera. Indica cuál de las siguientes opciones define correctamente una región crítica para el acceso al búfer de recepción de un driver
    - ( ) En la función receive. Se debe anular la generación de interrupciones por parte del dispositivo en el controlador de interrupciones antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso
    - ( ) En la ISR del dispositivo. Se debe anular la generación de interrupciones de recepción antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso
    - ( ) En la función receive. Se debe enmascarar la atención de interrupciones en los bits I/F del registro de control de la CPU antes de acceder al búfer y restaurarla una vez que se ha terminado el acceso
    - (x) En la función receive. Se debe anular la generación de interrupciones de recepción antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso

108. El uso de los pines de E/S un SoC...
    - ( ) Se configura automáticamente en función de los periféricos que se conecten al SoC
    - ( ) Es único. Cada pin tiene una única función, que dependerá del dispositivo al que esté conectado
    - ( ) Viene configurado de fábrica y no se puede cambiar por la aplicación
    - (x) Está multiplexado, por lo que es necesario el uso del GPIO para configurarlos correctamente

109. La lista de ficheros abiertos del BSP...
    - ( ) Sólo estará presente en aquellos sistemas que dispongan de dispositivos de almacenamiento (ej. discos duros, memorias flash, etc.).
    - ( ) Almacena todos los dispositivos que se pueden tratar como ficheros en el BSP
    - ( ) Asocia un único fichero a cada dispositivo del sistema
    - (x) Asocia descriptores de fichero a dispositivos

110. Indica cual de estas características NO es propia de un driver L1
    - ( ) Permiten la definición de funciones callback
    - ( ) Proporciona un API abstracta e independiente del dispositivo
    - ( ) Permiten una configuración total del dispositivo
    - (x) Las operaciones de E/S son bloqueantes

