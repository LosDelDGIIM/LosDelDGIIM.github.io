# Sistemas Empotrados - Preguntas Tipo Test Parte Práctica

- **Descripción:** Recopilación exhaustiva de preguntas Tipo Test de Prácticas de la asignatura de Sistemas Empotrados (Grado en Ingeniería Informática - Mención en Ingeniería de Computadores, UGR). Abarca las prácticas 1 a 10: Herramientas GNU cross-compiler, Programación Ensamblador ARM, Subrutinas y Cargador BSP, Manejadores de Excepción, UART y Temporizadores L0, Driver UART L1 por Interrupciones e Integración con Newlib.

---

1. Indica a qué pin del GPIO está conectado el led rojo de la placa. Puedes consultar el esquemático de la placa
    - ( ) GPIO52
    - ( ) GPIO59
    - (x) GPIO44
    - ( ) GPIO45

2. ¿Cómo configurarías el GPIO para que se puedan encender y apagar los leds rojo y verde mediante software?
    - ( ) GPIO_PAD_DIR_RESET1 <- 0x00003000
    - (x) GPIO_PAD_DIR_SET1 <- 0x00003000
    - ( ) GPIO_PAD_DIR_RESET0 <- 0x00003000
    - ( ) GPIO_PAD_DIR_SET0 <- 0x00003000

3. Para conectarnos a la interfaz de ordenes de OpenOCD debemos...
    - ( ) Mandar la orden soft_reset_halt
    - ( ) Lanzar el Eclipse y crear una configuración de depuración para que se conecte a OpenOCD
    - (x) Hacer un telnet a localhost:4444
    - ( ) Hacer un telnet a localhost:3333

4. La orden de OpenOCD load_image...
    - ( ) Carga un fichero ELF en la memoria de la placa
    - ( ) Carga un fichero ELF en la memoria de la placa y lo ejecuta
    - (x) Carga una imagen en formato binario en la memoria de la placa
    - ( ) Carga una imagen en formato binario en la memoria de la placa y la ejecuta

5. Asumiendo que los pines a los que están conectados los leds rojo y verde están configurados como de salida, ¿cómo apagarías el led verde?
    - ( ) GPIO_DATA_RESET1 <- 13
    - ( ) GPIO_DATA_SET1 <- 0xffffdfff
    - (x) GPIO_DATA_RESET1 <- 0x00002000
    - ( ) GPIO_DATA_SET1 <- 0x00002000

6. Asumiendo que los pines a los que están conectados los leds rojo y verde están configurados como de salida, ¿cómo encenderías el led verde?
    - ( ) GPIO_DATA_SET1 <- 0x00010000
    - ( ) GPIO_DATA_RESET1 <- 0x00010000
    - (x) GPIO_DATA_SET1 <- 0x00002000
    - ( ) GPIO_DATA_RESET1 <- 0x00002000

7. Indica a qué pin del GPIO está conectado el temporizador 2 (TMR2). Puedes consultar el esquemático de la placa
    - ( ) GPIO9
    - ( ) GPIO11
    - (x) GPIO10
    - ( ) GPIO8

8. Asumiendo que los pines a los que están conectados los leds rojo y verde están configurados como de salida, ¿cómo encenderías el led rojo?
    - ( ) GPIO_DATA1 <- 12
    - ( ) GPIO_DATA1 <- 0xffffefff
    - (x) GPIO_DATA1 <- 0x00001000
    - ( ) GPIO_DATA0 <- 0x00001000

9. OpenOCD...
    - ( ) Permite hacer un telnet a la placa de desarrollo
    - ( ) Es un demonio de depuración que se ejecuta en la placa de desarrollo para permitir la depuración de programas
    - (x) Proporciona una interfaz estándar entre el depurador y casi cualquier placa de desarrollo
    - ( ) Es un depurador de código a bajo nivel

10. Asumiendo que los pines a los que están conectados a los leds rojos y verdes están configurados como de salida,¿Como apagarias los dos leds?
    - (x) GPIO_DATA1 <- 0
    - ( ) 1
    - ( ) 1
    - ( ) 1

11. La orden de OpenOCD mww 0x80000054 0x00002000
    - (x) Apaga el led verde.
    - ( ) 1
    - ( ) 1
    - ( ) 1

12. Indica a que pin de GPIO está conectado el temporizador 2 (TMR2)
    - (x) GPIO10
    - ( ) 1
    - ( ) 1
    - ( ) 1

13. La orden de OpenOCD mww 0x80000054 0x00002000"
    - (x) Apaga el led verde
    - ( ) Fija el pin conectado al led verde como de entrada
    - ( ) Enciende el led rojo
    - ( ) Fija el pin conectado al led rojo como de salida

14. Asumiendo que los pines a los que están conectados los leds rojo y verde están configurados como de salida, ¿cómo apagarías los dos leds? Puedes consultar el esquemático de la placa (https://github.com/malvira/econotag) y el manual de referencia del procesador (http://www.freescale.com/files/rf_if/doc/ref_manual/MC1322xRM.pdf)
    - ( ) GPIO_DATA1 <- 0x00003000
    - ( ) GPIO_DATA0 <- 0xffffcfff
    - (x) GPIO_DATA1 <- 0
    - ( ) GPIO_DATA0 <- 0x00003000

15. ¿Cuál de las siguiente opciones transfiere el contenido de la variable masc al registro r1?
    - ( ) ldr r0, =masc; str r1, [r0]
    - (x) ldr r0, =masc; ldr r1, [r0]
    - ( ) ldr r1, masc
    - ( ) ldr r1, =masc

16. Indica en cual de las siguientes secciones se deben definir las variables globales inicializadas en un fichero ensamblador
    - ( ) .bss
    - ( ) No es necesario indicar la sección, el ensamblador las emitirá automáticamente a la sección.data
    - (x) .data
    - ( ) .rodata

17. ¿Cuál de las siguiente binutils usarías para desensamblar un fichero elf?
    - ( ) Los ficheros elf no se pueden desensamblar
    - (x) objdump
    - ( ) nm
    - ( ) readelf

18. ¿Cuál de las siguientes binutils usarías obtener las tabla de símbolos de un ejecutable?
    - ( ) Solamente objdump
    - (x) Todas las otras respuestas son correctas
    - ( ) Sólamente nm
    - ( ) Sólamente readelf

19. El el SoC MC1322x de Freescale dispone de 96 kBytes de memoria RAM. ¿En cuántos bloques está estructurada dicha memoria?
    - (x) 4
    - ( ) 3
    - ( ) 2
    - ( ) 1

20. ¿Cuál de las binutils se usa para extraer la imagen binaria de un archivo elf?
    - ( ) objdump
    - (x) objcopy
    - ( ) nm
    - ( ) readelf

21. Indica qué opción declara correctamente una variable global de 32 bits en ensamblador:
    - (x) a:.word 8, dentro de la sección.data
    - ( ) a: 8, dentro de la sección.data
    - ( ) .global a
    - ( ) a:.word 8, en cualquier parte del fichero ensamblador

22. Al almacenar las máscaras de los leds en variables en lugar de usar símbolos definidos mediante la directiva.set, la velocidad de ejecución del programa...
    - ( ) No se ve afectada si se trata de variables locales
    - ( ) No se ve afectada si se trata de variables globales
    - ( ) Mejora
    - (x) Empeora

23. Asumiendo que se ha mapeado la sección de código del programa hello al comienzo de la memoria RAM de la Econotag, ¿a qué banco de memoria se debería mapear la sección de datos del programa hello.elf para maximizar el tamaño de la imagen binaria del ejecutable?
    - ( ) RAM2
    - (x) RAM3
    - ( ) RAM1
    - ( ) RAM4

24. En un script de enlazado, ¿cómo obtendrías la dirección virtual en la que comienza la sección de código de un ejecutable?
    - ( ) Insertando la expresión "PROVIDE(dir =.text)" en cualquier parte de la directiva sections
    - (x) Insertando la expresión "dir =.;" al principio de la sección
    - ( ) Insertando la expresión "dir =.text" en cualquier parte de la directiva sections
    - ( ) Insertando la expresión "dir = LOADADDR(.text)" en cualquier parte de la directiva sections

25. ¿Cual de las siguientes opciones transfiere el contenido de la variable masc al resgistro r1?
    - (x) ldr r0, =masc; ldr r1, [r0]
    - ( ) mov r1, =masc
    - ( ) ldr r1, =masc
    - ( ) str r1, [r0]

26. La directiva.global a del ensamblador de la GNU...
    - (x) Permite que el símbolo a sea accesible desde otros módulos del programa
    - ( ) Define una constante global inmutable
    - ( ) Reserva memoria en la sección.bss
    - ( ) Fija la dirección absoluta de a

27. Para definir en el linker script un símbolo que permita acceder a los registros del GPIO, debemos definir el símbolo GPIO_BASE = 0x80000000...
    - (x) Fuera de la definición de cualquier sección de salida
    - ( ) Dentro de la definición de cualquier sección de salida
    - ( ) En el fichero fuente en C
    - ( ) En la cabecera del fichero ensamblador

28. Para consultar la tabla de símbolos de nuestra aplicación podemos usar la binutil nm sobre...
    - (x) El fichero.elf de la aplicación
    - ( ) El fichero binario plano.bin
    - ( ) El fichero fuente.c
    - ( ) El fichero de texto del script de enlazado

29. A la hora de inicializar las pilas de los diferentes modos de ejecución...
    - ( ) Hay que comprobar que previamente se ha inicializado la memoria dedicada a las pilas con el patrón 0xdeadbeef
    - (x) La pila del modo Supervisor (SVC) debe ser la última
    - ( ) La pila del modo Supervisor (SVC) debe ser la primera
    - ( ) El orden en el que se inicialicen las diferentes pilas es irrelevante

30. ¿A qué dirección de memoria está mapeado el cargador de la Econotag?
    - ( ) La placa Econotag no tiene ningún cargador
    - (x) 0x00000000
    - ( ) 0x00400000
    - ( ) 0x80000000

31. El resultado final de la construcción del BSP es...
    - ( ) Un fichero objeto
    - (x) Una biblioteca
    - ( ) Un conjunto de ficheros objeto
    - ( ) El firmware que se ejecutará en el sistema empotrado

32. A la hora de diseñar una aplicación que haga uso del BSP, el linker script...
    - ( ) Sólo es necesario si se escribe la aplicación en ensamblador
    - ( ) Ya no es necesario
    - ( ) Se debe diseñar completamente en función de las características de la aplicación
    - (x) Forma parte del BSP, por lo que simplemente hay que usarlo para enlazar la aplicación con el código del BSP. A lo sumo, sólo será necesario cambiar el tamaño de las pilas en algunos casos muy concretos

33. ¿Para que utilizamos la herramienta bbmc?
    - ( ) Esa herramienta no se usa en esta asignatura
    - (x) Borrar la memoria flash de la placa
    - ( ) Flashear la placa
    - ( ) Cargar una imagen a la placa

34. Indica cuál de las siguientes partes del cargador del BSP desarrollado en las prácticas se podría realizar en C
    - ( ) La carga de la imagen ejecutable en la RAM
    - (x) La inicialización de los dispositivos de E/S
    - ( ) La inicialización de las pilas
    - ( ) La habilitación de interrupciones

35. Indica cuál de las siguientes opciones no es válida para cargar y ejecutar una imagen ejecutable en la RAM de la Econotag
    - ( ) Mandar la imagen por el puerto serie desde el PC a la placa y resetearla
    - (x) Mandar la imagen por el puerto serie desde el PC a la placa
    - ( ) Conectar la placa al PC y subir la imagen a la memoria de la placa y ejecutarla usando órdenes de OpenOCD
    - ( ) Encender la placa después de haber grabado la imagen en su memoria flash

36. Si se usa nuestro cargador para ejecutar una aplicación en la Econotag, ¿Qué ocurrirá si la función main de la aplicación retorna?
    - (x) El sistema se cuelga
    - ( ) La función main nunca retornará
    - ( ) Se provoca una excepción
    - ( ) Se vuelve a cargar todo como al inicio y se ejecuta la aplicación

37. Indica cuál es el único símbolo que es necesario definir en el script de enlazado del BSP de la Econotag
    - ( ) _data_start
    - ( ) _bss_start
    - ( ) _text_start
    - (x) _bss_end

38. Indica cuál de los siguientes componentes del BSP no es necesario para su construcción
    - (x) Un sistema de ficheros en disco
    - ( ) El script de enlazado
    - ( ) El cargador crt0.s
    - ( ) Los manejadores de excepción

39. El fichero que contiene el cargador del BSP es
    - (x) hal/crt0.s
    - ( ) hal/loader.c
    - ( ) bsp/main.s
    - ( ) drivers/boot.s

40. ¿A qué sección emite el compilador las constantes globales de un fichero con código C?
    - (x) .rodata
    - ( ) .data
    - ( ) .bss
    - ( ) .text

41. Indica cual de las siguientes tareas no está soportada por el cargador de la ROM de la Econotag y es necesario implementarla en el del BSP
    - (x) Dar soporte a las excepciones e inicializar las pilas
    - ( ) Cargar el código desde Flash a RAM
    - ( ) Saltar a la dirección de inicio
    - ( ) Comprobar la cabecera binaria

42. A la hora de diseñar el script de enlazado del BSP para la Econotag, para aquellas secciones que se copiarán de la Flash a la RAM...
    - (x) Es necesario indicar tanto las direcciones VMA como las LMA
    - ( ) Solamente es necesario indicar las direcciones VMA
    - ( ) Solamente es necesario indicar las direcciones LMA
    - ( ) No se permite definir secciones copiadas a RAM

43. El cargador de la ROM de la Econotag...
    - (x) No inicializa el puntero de pila de ninguno de los modos de ejecución del procesador
    - ( ) Inicializa las pilas de todos los modos privilegiados
    - ( ) Configura la pila del modo User en RAM
    - ( ) Inhabilita el uso de la memoria RAM

44. De todas estas tareas, indica cual es la primera que debe ejecutar el cargador para que la aplicación se pueda ejecutar correctamente
    - (x) Inicializar las pilas
    - ( ) Inicializar la RAM
    - ( ) Llamar a main()
    - ( ) Habilitar las interrupciones

45. Indica la dirección de memoria a la que estará mapeada la tabla de vectores de excepción que se define en el fichero crt0.s de nuestro BSP
    - (x) 0x00400000
    - ( ) 0x00800000
    - ( ) 0x80000000
    - ( ) 0x00000000

46. Los manejadores de excepción...
    - ( ) Se deben declarar en el fichero excep.c del BSP
    - (x) Forman parte del código de la aplicación
    - ( ) No se pueden cambiar por la aplicación
    - ( ) Forman parte del BSP, pero deben declararse en un fichero aparte

47. Indica qué opción es la que debe usar el desarrollador de aplicaciones para instalar la función my_handler como un manejador personalizado para las excepciones de tipo Undefined Exception
    - ( ) _excep_handlers[excep_undef] = my_handler;
    - ( ) __attribute__ ((interrupt ("UNDEF"))) void my_handler (void)
    - (x) excep_set_handler (excep_undef, my_handler);
    - ( ) excep_set_handler (my_handler);

48. La función excep_disable_ints ()...
    - ( ) Retorna el valor que tenían los bits I y F antes de fijarlos a 0
    - (x) Retorna el valor que tenían los bits I y F antes de fijarlos a 1
    - ( ) Fija los bits I y F a 0 y no retorna nada
    - ( ) Fija los bits I y F a 1 y no retorna nada

49. ¿En qué dirección de memoria RAM estará la tabla de manejadores una vez que se haya cargado la imagen ejecutable en la placa?
    - ( ) 0x00000020
    - ( ) 0x00000000
    - (x) 0x00400020
    - ( ) 0x00400000

50. Indica el fichero del BSP en el que están definidos todos los tipos de excepción de la arquitectura ARM
    - (x) en include/excep.h
    - ( ) en include/system.h
    - ( ) en hal/excep.c
    - ( ) en hal/crt0.s

51. ¿Qué contiene cada una de las entradas de la tabla de manejadores de excepción?
    - ( ) El argumento que se pasará el manejador
    - ( ) Un puntero a una lista de argumentos para el manejador
    - (x) Un puntero a una función
    - ( ) Una instrucción ejecutable

52. Indica qué opción es la correcta para insertar una instrucción no definida en un programa escrito en C
    - ( ) asm(".data.word 0x26889912\n");
    - ( ) asm(".data 0x26889912\n");
    - (x) asm(".word 0x26889912\n");
    - ( ) .word 0x26889912

53. Indica cual de las siguientes opciones declara correctamente en C un manejador para una excepción de tipo Undefined Instruction
    - ( ) __attribute__ ((exception ("UNDEF"))) void my_handler (void)
    - ( ) __attribute__ (exception) void my_handler (void)
    - (x) __attribute__ ((interrupt ("UNDEF"))) void my_handler (void)
    - ( ) void my_handler (void)

54. Si insertamos una instrucción no definida en nuestro programa, pero se nos olvida instalar un manejador para que gestione la excepción cuando se trate de ejecutar dicha excepción...
    - ( ) El procesador no atenderá la excepción al no tener definido un manejador que la gestione
    - (x) Se usará el manejador por defecto definido en el BSP
    - ( ) Provocará un resultado totalmente aleatorio
    - ( ) Se reseteará el procesador

55. La instrucción msr...
    - ( ) Copia el registro cpsr registro de estado en un registro de propósito general
    - (x) Copia un registro de propósito general en un registro de estado
    - ( ) No existe en el repertorio de instrucciones del ARM7TDMI
    - ( ) Copia el registro spsr registro de estado en un registro de propósito general

56. Indica el fichero del BSP en el que está definida la tabla de manejadores
    - (x) hal/crt0.s
    - ( ) drivers/uart.c
    - ( ) system/newlib.c
    - ( ) main.c

57. En el registro UTxCON de las UART de la Econotag, el campo Tx_fifo_addr_diff...
    - ( ) Indica cuántos bytes están actualmente almacenados en la cola FIFO de envío, pendientes de ser enviados
    - (x) Indica el número de huecos libres en la cola FIFO de envío de la UART
    - ( ) Indica el número de huecos libres en la cola FIFO de recepción de la UART
    - ( ) Indica cuántos bytes están actualmente almacenados en la cola FIFO de recepción

58. La aplicación para probar el driver L0 que se propone en la práctica debe cambiar el estado de los leds de la Econotag (de encendido a apagado y viceversa) según los caracteres que se reciban por la UART. Si la placa recibe una 'r' (cambiar el estado del led rojo), ¿cómo sabe la aplicación si el led está encendido o apagado para poder cambiar su estado?
    - ( ) Consultando el estado del botón de la placa que se usa para encender y apagar el led
    - ( ) Consultando el registro de datos del GPIO correspondiente al led
    - (x) Consultando la variable de la aplicación que guarda el estado del led
    - ( ) Consultando el pin del GPIO al que esté conectado el led

59. ¿Qué registro se usa para fijar la frecuencia de las UART de la Econotag?
    - ( ) UBRINC
    - ( ) UBRMOD
    - ( ) UCON
    - (x) UBR

60. Para poder utilizar la UART es necesario fijar la función de sus pines a...
    - ( ) gpio_func_alternate_3
    - ( ) gpio_func_normal
    - ( ) gpio_func_alternate_2
    - (x) gpio_func_alternate_1

61. En la lección de teoría se explica el diseño de la estructura de datos uart_regs_t, que permitirá acceder de forma cómoda a los registros de las UART de la Econotag. Sin embargo, aunque se ofrecen los detalles de la mayoría de los registros, se omiten algunos, de forma que los estudiantes puedan demostrar en la práctica que saben completar la estructura de datos con los registros que faltan. De los siguientes registros, indique cual no se detalla en teoría y es necesario que el estudiante lo añada a la estructura.
    - ( ) UDATA
    - ( ) UBR
    - ( ) UCON
    - (x) USTAT

62. En la función de inicialización de la UART de la Econotag...
    - ( ) La frecuencia de operación de la UART se puede establecer en cualquier punto de la función
    - (x) La frecuencia de operación de la UART se debe establecer con su transmisor y su receptor apagados
    - ( ) La frecuencia de operación de la UART se debe establecer con su transmisor y su receptor encendidos
    - ( ) No se establece la frecuencia de operación de la UART

63. Para mandar un carácter mediante la UART de la Econotag...
    - ( ) Se escribe el carácter directamente en la cola FIFO de envío
    - ( ) Se debe comprobar si hay algún hueco en la cola de envío, y si es así, se escribe el carácter en el primer hueco disponible
    - ( ) Solamente es necesario escribirlo en el registro de datos de la UART
    - (x) Es necesario comprobar que hay algún hueco en la cola FIFO de envío antes de escribirlo en el registro de datos de la UART

64. ¿Cuántas UART tiene la Econotag?
    - ( ) 3
    - ( ) 0
    - ( ) 1
    - (x) 2

65. Si se ha usado OpenOCD para subir una aplicación a la placa Econotag y dicha aplicación usa la UART1 para comunicarse con el PC, ¿qué puerto serie se debe indicar en el emulador de terminal para poder conectar con la UART de la placa?
    - ( ) /dev/ttyUSB2
    - ( ) /dev/ttyUSB3
    - ( ) /dev/ttyUSB0
    - (x) /dev/ttyUSB1

66. Para poder configurar la función de los pines de E/S que se usarán por una UART de la Econotag es necesario que...
    - ( ) Se haya configurado la dirección de los pines
    - ( ) Se haya fijado la frecuencia de operación
    - ( ) La UART esté apagada
    - (x) La UART esté habilitada

67. En el registro URxCON de las UART de la Econotag, el campo Rx_fifo_addr_diff...
    - (x) Indica cuántos bytes han sido recibidos y están actualmente almacenados en la cola FIFO de recepción
    - ( ) Indica la dirección base del búfer de recepción en memoria
    - ( ) Configura la tasa de baudios de recepción
    - ( ) Indica el número de errores de paridad detectados

68. ¿Se puede enviar una cadena de caracteres usando sólo las funciones de la capa L0 del driver de la UART?
    - (x) Sí, con ayuda de un bucle que vaya recorriendo la cadena carácter a carácter llamando a la función de envío de un byte
    - ( ) No, es imprescindible el uso de un driver L1 con interrupciones
    - ( ) No, la capa L0 solo permite recibir datos
    - ( ) Solo si la longitud de la cadena es menor o igual a 4 bytes

69. La función de inicialización de la uart debe configurar el controlador de interrupciones para asignar las peticiones de interrupción de las uart a las entradas de interrupción de la CPU. ¿A cuál de ellas mapea cada uart?
    - ( ) Las dos uart a la entrada FIQ
    - ( ) La uart1 a la entrada IRQ y la uart2 a la entrada FIQ
    - ( ) La uart1 a la entrada FIQ y la uart2 a la entrada IRQ
    - (x) Las dos uart a la entrada IRQ

70. ¿Cómo sabe la ISR si la petición de interrupción de la uart se debe a la recepción de datos?
    - ( ) Consultando el número de bytes recibidos en la cola HW de recepción del dispositivo (campo Rx_fifo_addr_diff del registro RxCON)
    - ( ) Probando a leer datos de la cola HW del dispositivo
    - (x) Consultando el bit RxRdy del registro USTAT
    - ( ) Consultando el bit TxRdy del registro USTAT

71. En un driver L1, la función de envío bloqueante del driver de la uart...
    - ( ) Funcionará correctamente sin necesidad de modificación
    - ( ) Debe reescribirse para bloquearse si no hay huecos en la cola HW de envío
    - ( ) Debe reescribirse para que escriba el dato en el búfer de envío en lugar de en la cola HW del dispositivo
    - (x) Debe reescribirse para mandar a la cola HW de envío todos los caracteres del búfer circular de envío antes de encolar en la cola HW el carácter

72. En un driver L1, la función de recepción bloqueante del driver de la uart...
    - ( ) Debe ser modificada para mover todos los caracteres recibidos del búfer circular a la cola HW de recepción antes de pasar a bloquearse.
    - (x) Debe ser modificada para consultar si hay datos en el búfer de recepción antes de pasar a bloquearse hasta que llegue un nuevo dato a a la uart
    - ( ) Funcionará correctamente sin necesidad de ser modificada
    - ( ) Debe ser modificada para bloquearse si la cola HW de recepción está vacía

73. Dado que el driver L1 de la uart está basado en sendos búferes circulares de envío y recepción que son compartidos tanto por las funciones send y receive como por la ISR, es necesario que las funciones send y receive accedan a su búfer correspondiente dentro de una sección crítica para evitar condiciones de carrera con la ISR. Por lo tanto...
    - ( ) La uart no podrá interrumpir a la función receive nunca
    - ( ) La uart podrá interrumpir a la función receive si ha recibido nuevos datos
    - ( ) La uart podrá interrumpir a la función receive siempre
    - (x) La uart podrá interrumpir a la función receive si necesita datos para enviar

74. ¿En qué nivel inhibe/restaura interrupciones la función uart_send para acceder de forma segura al búfer de envío del driver de la uart?
    - (x) En la uart, inhibiendo/restaurtando la petición de interrupciones por parte de su transmisor
    - ( ) En el procesador del sistema, inhibiendo/restaurando la recepción de interrupciones en el registro de control
    - ( ) En el controlador de interrupciones, inhibiendo/restaurando las peticiones de interrupción de la uart.
    - ( ) No es necesario inhibir interrupciones para acceder al búfer

75. Una de las funcionalidades que añaden las funciones de nivel 1 de un driver es el chequeo de errores en los parámetros. En el caso de que algún parámetro sea erróneo, la función retornará...
    - ( ) 2
    - (x) -1
    - ( ) 0
    - ( ) 1

76. ¿Cómo sabe la ISR del driver de la uart si la aplicación ha instalado una función callback de recepción en la uart2?
    - ( ) La ISR no debe comprobar nada. El driver debe tener definidas callbacks para todas las uart del sistema
    - (x) Comprobando si el puntero a función almacenado en uart_callbacks[uart_2].rx_callback tiene un valor distinto de NULL
    - ( ) Comprobando si el puntero a función almacenado en uart_2_rx_callback tiene un valor distinto de NULL
    - ( ) Comprobando si el puntero a función almacenado en uart_rx_callbacks[uart_2] tiene un valor distinto de NULL

77. En la aplicación de prueba del driver L1 de la uart que se propone en el ejercicio de la práctica 9, El estado de los leds que deben parpadear se modifica en...
    - ( ) La función callback de envío
    - ( ) La ISR del driver de la uart
    - ( ) La aplicación
    - (x) La función callback de recepción

78. La función callback de recepción del driver de la uart es invocada por...
    - ( ) La uart
    - (x) La ISR del driver
    - ( ) La función uart_receive
    - ( ) Cualquier función de la aplicación

79. 2.Lo primero que debe hacer una ISR es reconocer que está sirviendo la interrupción para que el dispositivo deje de solicitar la atención de la CPU.¿Cómo reconoce la ISR de la uart de la Econotag que está atendiendo una peticion interrupcion causada por una recepcion de datos?
    - (x) Consultando los bits correspondientes en el registro USTAT
    - ( ) Escribiendo un 1 en el registro de control del ARM
    - ( ) Llamando a la función printf
    - ( ) Desactivando la alimentación del periférico

80. En un driver L1, la función de recepción bloqueante del driver de la uart..
    - (x) Debe ser modificada para consultar si hay datos en el búfer de recepción antes de pasar a bloquearse hasta que llegue un dato a la UART
    - ( ) Debe deshabilitar las interrupciones durante toda su ejecución
    - ( ) Debe leer directamente del registro HW sin consultar el búfer
    - ( ) No puede convivir con funciones de recepción no bloqueantes

81. ¿Qué hace la ISR de la uart en el caso de que el dispositivo solicite más datos para enviar pero no haya más datos en el bufer circular de envio del driver?
    - (x) Desactivar la petición de interrupciones del dispositivo debidas a falta de datos que enviar
    - ( ) Enviar caracteres nulos de relleno continuamente
    - ( ) Bloquear la CPU hasta que lleguen nuevos datos
    - ( ) Reiniciar la UART por completo

82. ¿Cuantas ISR hay definidas en el driver de la uart de la Econotag?
    - (x) 2
    - ( ) 1
    - ( ) 4
    - ( ) 5

83. En caso de éxito, ¿qué valor retorna la funcion uart send?
    - (x) El número de bytes que se han podido copiar al búfer circular de envío del driver
    - ( ) Siempre el valor 0
    - ( ) La dirección del búfer circular
    - ( ) Un puntero a la estructura uart_regs_t

84. ¿Cuántas ISR hay definidas en el driver de la uart de la Econotag?
    - (x) 2
    - ( ) 1
    - ( ) 3
    - ( ) 56

85. Indica qué código fijan las funciones del driver de la uart en la variable global errno en el caso de que reciban un identificador de uart no válido en el sistema
    - (x) ENODEV
    - ( ) EINVAL
    - ( ) EBADF
    - ( ) EIO

86. Lo primero que debe hacer una ISR es reconocer que está sirviendo la interrupción para que el dispositivo deje de solicitar la atención de la CPU. ¿Cómo reconoce la ISR de la uart de la Econotag que está atendiendo una petición interrupción causada por una recepción del datos?
    - (x) Leyendo los datos recibidos de la cola HW de la UART
    - ( ) Enviando una trama de confirmación por el puerto serie
    - ( ) Modificando el bit I del registro CPSR
    - ( ) Esperando a que el emisor finalice la transmisión

87. El uso de funciones callback...
    - (x) Mejora las prestaciones de E/S de la aplicación al permitir un desacoplo y notificación asíncrona
    - ( ) Obliga a que la aplicación realice espera activa sobre el dispositivo
    - ( ) Elimina la necesidad de utilizar interrupciones en el sistema
    - ( ) Solo puede emplearse en sistemas operativos de propósito general

88. ¿Qué hace la ISR de la uart en el caso de que el dispositivo solicite más datos para enviar pero no haya más datos en el búfer circular de envío del driver?
    - (x) Desactivar la petición de interrupciones del dispositivo debidas a falta de datos que enviar
    - ( ) tytyt

89. La E/S estándar en C consiste en...
    - ( ) Acceder a los dispositivos mediante interrupciones
    - ( ) Facilitar un acceso a los dispositivos basado en búferes
    - (x) Acceder a los dispositivos del sistema como si fueran ficheros
    - ( ) Acceder a los dispositivos de forma transparente

90. Indica cual de las siguientes opciones representa una llamada a sistema en Newlib
    - ( ) _open
    - ( ) memcpy
    - (x) open
    - ( ) _memcpy

91. ¿Sobre qué dispositivo están abiertos los ficheros estándar stdin, stdout y stderr antes de que en el proceso de inicialización se registre la uart1 y se redirijan a este dispositivo?
    - ( ) /dev/console
    - ( ) /dev/zero
    - (x) /dev/null
    - ( ) Inicialmente no están abiertos sobre ningún dispositivo

92. Indica cual de las siguientes opciones no es un fichero de E/S estándar
    - ( ) stdin
    - ( ) stdout
    - (x) stddev
    - ( ) stderr

93. Si un periférico no se ha registrado en el BSP como un dispositivo...
    - ( ) No podrá usarse por la aplicación
    - ( ) Sólo podrá accederse a dicho dispositivo en ensamblador
    - (x) No podrá ser accedido mediante funciones de E/S estándar
    - ( ) Sólo podrá gestionarse mediante el acceso directo de la aplicación a sus registros de control/estado

94. En caso de éxito, la llamada a sistema read retornará...
    - ( ) La función read no retorna ningún valor
    - ( ) -1
    - (x) El número de bytes que se han podido leer del fichero
    - ( ) El número de bytes que la función llamadora quería leer

95. Indica en cual de las siguientes llamadas a sistema no se usa la implementación mínima por defecto para las uart de la Econotag
    - ( ) close
    - ( ) isatty
    - (x) Read
    - ( ) lseek

96. A la hora de registrar un dispositivo en el BSP...
    - ( ) Es necesario indicar explícitamente una implementación para cada una de las llamadas a sistema
    - ( ) Sólo es necesario indicar el nombre que se usará para acceder a dicho dispositivo
    - (x) Sólo hay que indicar aquellas llamadas a sistema que tengan un comportamiento diferente para el dispositivo que el de la implementación mínima por defecto.
    - ( ) Siempre hay que indicar, como mínimo, la implementación explícita para las llamadas a sistema read y write

97. Indica en cual de los siguientes ficheros de Newlib se encuentra la implementación de la función printf
    - ( ) stdio.h
    - ( ) printf.h
    - (x) libc.a
    - ( ) stdlib.h

98. Supongamos que se llama a la función estándar lseek, que posiciona el cursor dentro de un fichero, usando como argumento el fichero stdout, que está definido sobre una uart del sistema. Si las uart del sistema no tienen definida una implementación para la función lseek en la tabla de dispositivos del sistema, ¿qué debe hacer la implementación de la función stub de lseek?
    - ( ) Retornar con error
    - ( ) Todos los dispositivos deben tener definidas implementaciones de todas las llamadas a sistema
    - (x) Ejecutar la implementación mínima por defecto de la función lseek
    - ( ) Generar una excepción y abortar la ejecución de la aplicación

99. ¿Cuántos ficheros se pueden abrir sobre una uart?
    - ( ) Sólo uno
    - ( ) Sólo tres
    - ( ) Ninguno
    - (x) Todos los que queramos

100. Los descriptores de fichero son de tipo...
    - ( ) int *
    - ( ) File
    - ( ) FILE *
    - (x) int

101. En caso de éxito, la llamada a sistema open retornará...
    - ( ) -1
    - ( ) La función open no retorna ningún valor
    - ( ) 0
    - (x) El descriptor de fichero abierto por la función

102. En caso de que una llamada a sistema de Newlib falle su valor de retorno será...
    - ( ) El código de error
    - ( ) Las llamadas a sistema no deben fallar nunca
    - ( ) 0
    - (x) -1

103. ¿Dónde se debe hacer la llamada a la función bsp_register_dev del BSP?
    - ( ) Al principio del código de la aplicación
    - ( ) En el fichero hal/dev.c
    - (x) Al final de su función de inicialización
    - ( ) En la aplicación, justo antes de usar el dispositivo

104. En caso de éxito, la llamada a sistema read retornará
    - ( ) El n.o de bytes que la función llamadora quería leer
    - (x) El n.o de bytes que se han podido leer del fichero
    - ( ) -1
    - ( ) La función read no retornará ningún valor.

105. Indica en cual de las siguientes llamadas a sistema no se usa la implementacion minima por defecto para las uart de la Econotag.
    - ( ) lseek
    - (x) Read
    - ( ) isatty
    - ( ) close

106. En caso de éxito, la llamada a sistema open retornará
    - ( ) La función open no retornará ningún valor
    - (x) El descriptor de fichero abierto por la funcion
    - ( ) -1
    - ( ) 0

107. ¿Sobre qué dispositivo están abiertos los ficheros estándar stdin,stdout y stderr antes de que en el proceso de inicialización se registre la uart1 y se redirijan a este dispositivo?
    - ( ) Inicialmente no están abiertos sobre ningun dispositivo.
    - (x) /dev/null
    - ( ) /dev/zero
    - ( ) /dev/console

108. ¿Donde se debe hacer la llamada a la funcion bsp_register_dev del BSP?
    - ( ) En el fichero hal/dev.c
    - ( ) En la aplicación, justo antes de usar el dispositivo.
    - ( ) Al principio del código de la aplicación
    - (x) Al final de su función de inicialización

109. Indica en cual de los siguientes ficheros de Newlib se encuentra la implementacion de la funcion printf
    - ( ) Stdlib.h
    - (x) Libc.a
    - ( ) Print.h
    - ( ) Stdio.h

110. En caso de que una llamada a sistema de Newlib falle su valor de retorno será
    - ( ) Las llamadas a sistema no deben de fallar nunca
    - (x) -1
    - ( ) El código de error
    - ( ) 0

111. Supongamos que se llama a la función lseek, que posiciona el cursor dentro de un fichero, usando como argumento el fichero stdout, que está definido sobre una uart del sistema. Si las uart del sistema no tienen definida una implementacion para la funcion lseek en la tabla de dispositivos del sistema, ¿qué debe hacer la implementacion de la funcion slub de lseek?
    - ( ) Generar una excepcion y abortar la ejecución de la aplicación
    - (x) Ejecutar la implementación minima por defecto de la funcion lseek
    - ( ) Todos los dispositivos deben tener definidas implementaciones de todas las llamadas a sistema.
    - ( ) Retornar con error.

112. A la hora de registrar un dispositivo en el BSP....
    - ( ) Siempre hay que indicar, como minimo, la implementacion explicita para las llamadas a sistema read y write.
    - (x) tengan un corpontamiento diferente para el dispositivo que el de la implementacion minima por defecto.
    - ( ) Solo es necesario indicar el nombre que se usará para acceder a dicho dispositivo.
    - ( ) Es necesario indicar explicitamente para cada una de las llamadas a sistema.

