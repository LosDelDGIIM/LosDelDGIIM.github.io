<br>

# EC. Preguntas Tipo Test de Teoría.

**Autor:** Jose Juan Urrutia Milán 'JJ'.<br>
**Autor:** Lucas Hidalgo Herrera.<br>
**Autor:** Arturo Olivares Martos.
***

- **Asignatura:** Estructura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
- **Profesor:** Ignacio Rojas Ruiz.
- **Descripción:** Este documento tiene como objetivo servir para estudiar la asignatura de Estructura de Computadores. En él, se pueden encontrar una gran variedad de preguntas de EC de los últimos años.

Las preguntas se encuentran en <a href=https://losdeldgiim.github.io/subjects/EC/Ex%C3%A1menes/Examenes_Generados/TipoTest.html>esta web</a>.

Las explicaciones de cada pregunta se pueden encontrar en el archivo Markdown correspondiente, que se encuentra pinchando <a href=https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/EC/Ex%C3%A1menes/TipoTest.md>aquí</a>.
______

1. Respecto a direccionamiento a memoria en ensamblador IA32 (sintaxis AT&T), de la forma `D(Rb, Ri, S)`, sólo una de las siguientes afirmaciones es FALSA. ¿Cuál?
    - ( )  El desplazamiento D puede ser una constante lineal (1, 2 ó 4 bytes).
    - (x) `EBP` no se puede usar como registro base.
    - ( )  `ESP` no se puede usar como registro índice.
    - ( )  El factor de escala `S` puede ser 1, 2, 4, 8.

2. La extensión de signo a m bits de un número original N de n bits, con m > n, consiste en:
    - ( )  Realizar la operación \\(2^{m– N}\\)
    - ( )  Realizar la operación \\(2^{m– N-1}\\)
    - (x) Incrementar la cantidad de bits a m preservando el signo y el valor del número.
    - ( )  Incrementar la cantidad de bits a m rellenando con unos por la izquierda.

3. En IA32, ¿cuál de los siguientes fragmentos de programa tiene un efecto sobre los flags distinto al resto?
    - ( )  `sub %edi,%edi` <br> `adc $0xFFFFFFFF, %edi`
    - (x) `mov $-1, %edi`
    - ( )  `mov$-1,%edi` <br> `add $0, %edi`
    - ( )  `mov $0, %edi` <br> `sub $1, %edi`

4. Si `%rsp` vale `0xdeadbeefdeadd0d0`, ¿cuál será su nuevo valor después de que se ejecute `pushq %rbx?`
    - ( )  `0xdeadbeefdeadd0d4`
    - ( )  `0xdeadbeefdeadd0d8`
    - ( )  `0xdeadbeefdeadd0cc`
    - (x) `0xdeadbeefdeadd0c8`

5. ¿Cómo se devuelve en ensamblador x86-64 Linux gcc el valor de retorno de una función long int al terminar esta?
    - ( )  La instrucción `RET` lo almacena en un registro especial de retorno.
    - ( )  Por convención se guarda en `%eax`.
    - ( )  Se almacena en pila justo encima de los argumentos de la función.
    - (x) Ninguna de esas formas es correcta.

6. Comparando las convenciones de llamada de gcc Linux IA32 con x86-64 respecto a registros.
    - ( )  En IA32 `%ebx` es salva-invocante, pero en x86-64 `%rbx` es salva-invocado.
    - (x) En IA32 `%ecs` es salva-invocante, y en x86-64 `%rcd` es salva-invocante también.
    - ( )  En IA32 `%esi` es salva-invocado, y en x86-64 `%rsi` es salva-invocado también.
    - ( )  En IA32 `%ebp` es especial (marco de pila1), y en x86-64 `%rbp` también.

7. Son funciones de la unidad de control:
    - ( )  La codificación de las instrucciones máquina.
    - ( )  La lectura de memoria principal de la instrucción apuntada por el PC.
    - (x) El secuenciamiento de las instrucciones máquina.
    - ( )  Todas las respuestas son ciertas.

8. Respecto a `MBR` y `MAR`
    - ( )  Ambos son accesibles por el programador.
    - ( )  `MAR` contiene el dato/instrucción que se leerá o escribirá en memoria.
    - (x) `MAR` requiere menos señales de control que `MBR`.
    - ( )  Ambos permiten guardar información sobre el marco de pila.

9. Una instrucción máquina puede desglosarse en las siguientes operaciones elementales:<br>
`sp := ps-1; m[sp] := pc; pc:= x`<br>
Probablemente se trate de una instrucción de:
    - ( )  Apilamiento.
    - (x) Llamada a subrutina.
    - ( )  Carga total.
    - ( )  Almacenamiento local.

1.  En una unidad de control microprogramada con formato de microinstrucciones vertical, un subcampo que debe especificar 16 señales de control codificadas de tal forma que pueda activarse sólo una o ninguna harbá de tener una anchura mínima de:
    - ( )  4 bits.
    - (x) 5 bits.
    - ( )  16 bits.
    - ( )  17 bits.



11. Dado un camino de datos concreto, un posible formato de microprogramación se caracteriza como horizontal o vertical según tenga más o menos (señalar la respuesta falsa)
    - ( ) codificación
    - ( ) solapamiento
    - (x) micro bifurcaciones
    - ( ) longitud relativa de microinstrucción

12. El control residual se utiliza para:
    - ( ) reducir el tiempo de ejecución de las instrucciones máquina
    - ( ) eliminarlos bits residuales de la ejecución de las microinstrucciones
    - (x) reducir el tamaño de la memoria de control
    - ( ) ninguna de las anteriores es cierta

13. Un procesador está segmentado en las etapas F, D, E, M y W. Cada una de  ellas consume un tiempo t. La aceleración ideal (si no hay riesgos) al ejecutar n instrucciones respecto a un procesador no segmentado será:
    - (x) 5n/(4+n)_
    - ( ) (4+n)/5t
    - ( ) 4n/(5+n)
    - ( ) (5+n)/4t

14. En un procesador con segmentación de cauce, aumentar el número de etapas (p.ej. de 2 a 4, o de 4 a 8), tiene en general como consecuencia:
    - (x) Un Incremendo De Las Prestaciones.
    - ( )  Un mayor retraso en la ejecución de los programas debido al incremento del número de etapas.
    - ( ) Una disminución en la posible dependencia de datos.
    - ( ) Una disminución de la máxima frecuencia de reloj a la que puede operar el cauce.

15. En la secuencia de instrucciones siguiente, siendo el primer registro el destino, ¿cuántos riesgos se dan?<br>
`sub r2,r1,r3 or r8,r6,r2`
    - ( ) Un riesgo estructural.
    - (x) Un riesgo por dependencia de datos.
    - ( ) Un Riesgo Estructural Dos Po dependencia de datos.
    - ( ) Dos riesgos por dependencia de datos y uno de control.

16. La precaptación(cola de instrucciones) está relacionada con...
    - (x) Los riesgos estructurales(intenta evitar el efecto de un fallo de cache)
    - ( ) Los riesgos de (dependencia de) datos (intenta que el dato esté disponible anticipadamente)
    - ( ) Los riesgos control(intenta determinar de antemano el flujo de control)
    - ( ) Los riesgos de transferencia(intenta agrupar las posibles transferencias de un conjunto de instrucciones).

17. Respecto a la segmentación, ¿cuál de las siguientes afirmaciones es falsa?
    - ( ) La técnica de register forwarding habilita una serie de cambios(buses) que se añaden al cauce para permitir que los resultados de una etapa pasen como entradas a la etapa donde son necesarias.
    - ( ) La reorganizacion del código y la introducción de instrucciones no permite evitar dependencias de datos.
    - (x) Retrasar la fase de decisión saltar/no saltar de las instrucciones de salto condicional contribuye a mejorar el rendimiento del procesador.
    - ( ) Cuantas más etapas tenga un cauce, más instrucciones se estarán ejecutando en distintas fases y más posibilidades se presentan de que existan riesgos entre ellas.

18. ¿Cuál de los siguientes modos de direccionamento es menos preferible para un procesador de 32 bits y con tamaño de instrucción de 32 bits?
    - ( ) registro.
    - ( ) indexado.
    - ( ) indirecto a través de registro.
    - (x) directo (o absoluto)

19. La conexión entre un dispositivo de E/S y el procesador mediante bus:
    - ( ) Es difícil de expandir.
    - (x) Permite conectar en paralelo varios dispositivos.
    - ( ) Requiere mucha circuitería.
    - ( ) Requiere multiplexores y demultiplexores para las señales de datos.


20. El fragmento de código ensamblador de un microprocesador de 8 bits:<br><code>lds IOBuf	; Apuntar puntero pila a ...área mem.intermedia<br>ldx Count	; Inicializar x-contador<br>poll lda a Status; Leer estado en A<br>bpl poll	; Signo (A) != 1 => repetir<br>lda a Data	; Leer dato en A<br>psh a		; transferir dato a pila<br>dex 		; decrementar contador x<br>bne poll	; Seguir leyendo si x!=0<br></code><br> Corresponde a:<br>
    - (x) Entrada programada con consulta de estado.
    - ( ) Salida programada sin consulta de estado. 
    - ( ) Entrada programada sin consulta de estado.
    - ( ) Salida programada con consulta de estado.




31. ¿Cuál de las siguientes afirmaciones sobre el benchmark SPEC CPU es falsa?

    - ( ) La última versión es SPEC CPU2006 V1.2 de 2011.
    - ( ) Se cronometran unos 12 tests de enteros (CINT2006) y unos 17 tests de punto flotante (CFP2006).
    - ( ) Se usa como referencia un computador UltraSPARC II 300MHz, y para cada test se calcula el cociente entre el tiempo de ejecución en el computador a testear y en el de referencia.
    - (x) El resultado final es la media aritmética de las (12 ó 17) velocidades, bien sea de enteros ó de punto flotante (SPECint2006 ó SPECfp2006).

32. ¿En qué generación, dentro de la historia de los computadores digitales, aparecieron la microprogramación, la segmentación de cauce, la memoria cache, los S.O. multiusuario y la memoria virtual?

    - ( ) 2a generación (1955-65).
    - (x) 3a generación (1965-75).
    - ( ) 4a generación (1975-85).
    - ( ) Esas innovaciones se repartieron a lo largo de varias generaciones, no sólo una.

33. Respecto a tamaños de tipos integrales en x86 y x86-64, la excepción es que:

    - ( ) `int` pasa de 4 B (x86) a 8 B (x86-64).
    - (x) `long int` pasa de 4 B a 8 B.
    - ( ) `long long` pasa de 4 B a 8 B.
    - ( ) Ninguna de las anteriores.

34. Con el repertorio IA32, para sumar `%eax` y `%ebx` dejando el resultado en `%ecx` se podría hacer lo siguiente:

    - ( ) `lea %eax, %ebx, %ecx`
    - (x) `lea (%eax, %ebx, 1), %ecx`
    - ( ) `lea %ecx, [%eax, %ebx]`
    - ( ) `lea %ecx, %ebx, %eax`

35. Cuál de las instrucciones máquina siguientes es incorrecta en x86-64:

    - ( ) `testl %edx, %edx`
    - (x) `movl %r8, %eax`
    - ( ) `movl (%rdi, %rcx, 4), %edx`
    - ( ) `addq $1, %rcx`

36. Si la variable `val` está almacenada en `ebx` y la variable `x` está almacenada en `eax`, la sentencia `val ^= x;` se puede traducir a ensamblador como:

    - ( ) `xorl %ebx, %eax`
    - (x) `xorl %eax, %ebx`
    - ( ) `andl %ebx, %eax`
    - ( ) `testl %eax, %ebx`

37. Para poner a 1 el bit 5 del registro `%edx` sin cambiar el resto de bits podemos usar la instrucción máquina:

    - ( ) `and $32, %edx`
    - ( ) `and $0x5, %edx`
    - ( ) `or $0b101, %edx`
    - (x) `or $0x20, %edx`

38. Si tenemos un número `n`, de 64 bits, almacenado en la pareja de registros `EDX:EAX` (`EDX` contiene los 32 bits más significativos y `EAX` los 32 bits menos significativos y queremos realizar la división `n / 232` entonces:

    - ( ) Podemos quedarnos con `EDX`, pero sólo en el caso de que `n` sea un número sin signo.
    - (x) Podemos quedarnos con `EDX` tanto si `n` es un número con signo como sin signo.
    - ( ) Podemos usar las instrucciones siguientes, pero sólo en el caso de que `n` sea un número con signo: <br><code>mov $0x100000000, %ecx<br>div %ecx</code>
    - ( ) Podemos usar las instrucciones siguientes, tanto si `n` es un número con signo como sin signo: <br><code>mov $0x100000000, %ecx<br>div %ecx</code>

39. ¿Dónde está ubicado el primer argumento a una función (suponer código ensamblador cdecl generado por gcc para Linux/x86) inmediatamente después de ejecutar la instrucción call?

    - ( ) `%ebp + 0x4`
    - ( ) `%ebp - 0x4`
    - (x) `%esp + 0x4`
    - ( ) `%esp - 0x4`

40. Dado el código C siguiente:<br><code>struct data {<br> char str[16];<br>};<br>char *f(struct data *ptr) {<br> return &(ptr->str[2]);<br>}</code><br>La función se traducirá a ensamblador de x86-64 como:

    - (x) `leaq 2(%rdi), %rax` <br>`ret`
    - ( ) `movq (,%rdi,2), %rax` <br>`ret`
    - ( ) `movq 2(%rdi), %rax` <br>`ret`
    - ( ) `leaq (,%rdi,2), %rax` <br>`ret`

41. Respecto a requisitos de alineamiento de structs en gcc/IA32 x86 y x86-64, alguna de las siguientes afirmaciones es falsa:

    - (x) En x86 Linux alinea `double` a 4x (Windows no).
    - ( ) En x86 Linux alinea `long double` a 4x (Windows también).
    - ( ) En x86-64 Linux alinea `double` a 8x (Windows también).
    - ( ) En x86-64 Linux alinea `float` a 8x (Windows también).

42. Si la estructura struct `a` ocupa un espacio de 28 bytes en memoria, ¿cuántos bytes ocupa la siguiente estructura struct `b` cuando se compila en 64 bits? <br><code>struct b {<br> struct a a1;<br> int i;<br> struct a a2;<br>};</code>

    - ( ) 24 bytes.
    - ( ) 60 bytes.
    - ( ) 64 bytes.
    - (x) 84 bytes.

43. Respecto a los términos microinstrucción y microcódigo:

    - ( ) Son equivalentes, llamamos microcódigo o microinstrucción a una palabra de la memoria de control.
    - ( ) Una microinstrucción está programada en microcódigo, que es un lenguaje para programar señales de control.
    - ( ) Un microcódigo controla una serie de señales de control relacionadas (por ejemplo, el código `000` para que la ALU realice la suma), y varios microcódigos juntos forman una microinstrucción.
    - (x) Microcódigo es el contenido de la memoria de control, y una microinstrucción es una palabra de dicha memoria.

44. ¿Cuál de las siguientes afirmaciones es verdadera?

    - (x) La unidad de control necesita como entrada el registro de estado para poder controlar la ejecución de las instrucciones de salto condicional.
    - ( ) El registro de instrucción es un registro de propósito específico que contiene la dirección de la siguiente instrucción a ejecutar.
    - ( ) Las únicas instrucciones en las que algunas de sus fases de ejecución conllevan un acceso a memoria son las instrucciones load y store.
    - ( ) El registro puntero de pila es un registro de propósito general que suele contener tanto direcciones como datos.

45. Un procesador con una unidad de control microprogramada tiene una memoria de control de 300 palabras de 100 bits, de las que 200 son diferentes. Si se rediseñara como unidad de control nanoprogramada, ¿qué tamaño ocuparía la nanomemoria que contiene las microinstrucciones completas sin repeticiones?

    - (x) 20000 bits.
    - ( ) 21600 bits.
    - ( ) 22400 bits.
    - ( ) 30000 bits.

46. En el pseudocódigo usado para representar las microinstrucciones, la expresión `goto f(IR)`:

    - ( ) Se utiliza para realizar un microsalto condicional en función del registro de estado.
    - ( ) Realiza una llamada a una microsubrutina.
    - (x) Salta a una dirección de memoria de control que depende de la instrucción máquina actual.
    - ( ) Permite saltar a la dirección de memoria de control del principio de un microbucle.

47. Respecto a la predicción de saltos, alguna de las siguientes afirmaciones es falsa:

    - ( ) Si se toma la misma decisión para cada tipo de instrucción, se trata de "predicción estática".
    - ( ) Si la predicción cambia según la historia de ejecución del programa, se trata de "predicción dinámica".
    - (x) Para predicción estática, es conveniente decidir que los saltos hacia adelante siempre se cumplen, y hacia atrás no.
    - ( ) Para predicción dinámica, existen, entre otros, algoritmos de dos o cuatro estados, que requieren 1 o 2 bits por instrucción.

48. Respecto a los conceptos de procesamiento segmentado y superescalar, una de las siguientes afirmaciones es falsa:

    - ( ) Idealmente, con el segmentado se intenta ejecutar una instrucción por ciclo, y con el superescalar más de una por ciclo (al combinarlo con segmentado).
    - (x) En cualquier procesador resulta ventajoso usar una cola de instrucciones, pero es más importante para uno segmentado (fundamental) que para uno superescalar (conveniente).
    - ( ) Por definición, un procesador superescalar debe tener varias unidades funcionales (más de una).
    - ( ) Implícitamente, se presupone que un procesador superescalar emitirá más de una instrucción por ciclo.

49. Respecto a los conceptos de interfaz de dispositivo, controlador(a), puerto de E/S:

    - (x) La controladora o interfaz contiene los puetos necesarios para utilizar el dispositivo.
    - ( ) Cada puerto o interfaz es una línea de comunicación con el procesador. El conjunto de ellos forma el controlador.
    - ( ) El puerto, o interfaz, contiene los controladores necesarios para comunicar el dispositivo con el procesador.
    - ( ) El interfaz contiene las controladoras necesarias para conectar los puertos con el procesador.

50. Respecto a los conceptos de procesador de E/S, canal de E/S, dispositivos de E/S:

    - (x) Un procesador o canal tiene un repertorio de instrucciones específico para manejar los dispositivos de E/S.
    - ( ) Cada canal es una línea de comunicación entre el procesador y un dispositivo de E/S.
    - ( ) Al conjunto de conexiones entre el procesador y los dispositivos se le denomina canal de E/S (de ese ordenador).
    - ( ) La pregunta es capciosa, el procesador no es E/S, son otros dos componentes von Neumann distintos (ALU+UC).

51. La E/S programada:

    - ( ) Mejora las prestaciones globales del sistema respecto a la E/S por interrupciones porque la CPU tiene el control de toda la operación.
    - ( ) Mejora las prestaciones globales del sistema respecto a la E/S por interrupciones porque la CPU es más rápida que el controlador de interrupciones y la interfaz del periférico.
    - ( ) Empeora las prestaciones globales del sistema respecto a la E/S por interrupciones porque una .instrucción de transferencia individual de datos con la interfaz del periférico (por ej. IN, OUT) es más lenta en E/S programada que en E/S por interrupciones.
    - (x) Empeora las prestaciones globales del sistema respecto a la E/S por interrupciones porque la CPU debe encargarse de la sincronización con la interfaz del periférico haciendo una espera activa.

52. Una puerta `AND` con 16 entradas conectada a un bus de direcciones de 16 bits, con todos los bits negados excepto `A10` y `A6`, permite seleccionar un dispositivo (con CS activa en alta) en la dirección:

    - ( ) `0xFDDF`
    - ( ) `0xFBBF`
    - ( ) `0x0220`
    - (x) `0x0440`

53. Un computador con 15 líneas de direcciones tiene 3 módulos de memoria de 213 palabras y utiliza E/S mapeada en memoria. ¿Cuál es el número máximo de periféricos que pueden conectarse, si cada uno de ellos utiliza 8 direcciones?

    - (x) 210.
    - ( ) 212.
    - ( ) 211.
    - ( ) 213.

54. Un procesador accede en el instante de tiempo `t` a una posición de memoria `d(t)`. Poco tiempo después (en el instante de tiempo `t+k`) accede a la posición anterior `d(t)-1`. Esos dos accesos son un ejemplo de:

    - (x) Localidad espacial.
    - ( ) Localidad temporal.
    - ( ) No tiene nombre, ese tipo de localidad con incremento negativo (`d(t)-1`) no se ha estudiado en clase.
    - ( ) No es una localidad, esa condición no guarda relación con el concepto de localidad.

55. Una jerarquía de memoria consta de una cache de con una tasa de aciertos del 92% y 4 ns de tiempo de acceso y una memoria principal con una tasa de aciertos del 100% y 100 ns de tiempo de acceso. ¿Cuál es el tiempo promedio estimado de acceso a memoria?

    - ( ) 6 ns.
    - ( ) 8 ns.
    - ( ) 10 ns.
    - (x) 12 ns.

56. Una SRAM de `1Mx4bit` (4Mbit) puede venir organizada en 2048 filas, dedicando por tanto al decodificador de columnas:

    - ( ) 6 bits.
    - ( ) 7 bits.
    - ( ) 8 bits.
    - (x) 9 bits.

57. Un sistema basado en un microprocesador con un bus de datos de `n` bits y un bus de direcciones de 16 bits direcciona la memoria por palabras de `n` bits y dispone de una memoria SRAM formada por dos módulos de `16 K x n` cada uno. ¿Qué porcentaje del mapa de memoria está ocupado por la SRAM?

    - ( ) 12.5%
    - ( ) 25%
    - (x) 50%
    - ( ) 100%

58. Un módulo de memoria de 16 GB está formado por varios chips DRAM de `1024Mx4`. ¿Cuántos chips DRAM necesita el módulo?

    - ( ) 4.
    - ( ) 8.
    - ( ) 16.
    - (x) 32.

59. Una cache de 256 B asociativa por conjuntos de 4-vías con líneas de 16 B tendría:

    - (x) 4 conjuntos.
    - ( ) 16 conjuntos.
    - ( ) 64 conjuntos.
    - ( ) Ningún conjunto.

60. En un sistema con memoria de bytes, ¿cuál sería el tamaño de una línea de cache, si la cache del procesador fuera de 4MB, asociativa por conjuntos de 16-vías, y contuviera 4096 conjuntos?

    - ( ) 16 B.
    - ( ) 32 B.
    - (x) 64 B.
    - ( ) 128 B.

61. El conjunto de todos los atributos de un sistema que son visibles para el programador y son necesarios para programar en lenguaje máquina se denomina:

    - (x) Arquitectura del computador.
    - ( ) Conjunto de componentes físicos del computador.
    - ( ) Organización del computador.
    - ( ) Repertorio de instrucciones máquina.

62. ¿Cuál de las siguientes afirmaciones es cierta?

    - ( ) La arquitectura Von Neumann de los computadores tradicionales consiste en tener almacenados los datos separados de las instrucciones en memorias distintas.
    - (x) El registro de estado (flags) es un registro de propósito específico cuyo contenido puede ser visto directa o indirectamente por el usuario mediante el uso de ciertas instrucciones específicas.
    - ( ) La unidad de control necesita como entrada el registro contador de programa para saber cuál es la instrucción que debe ejecutar a continuación.
    - ( ) El registro de direcciones de memoria es un registro de propósito general que puede contener tanto direcciones como datos.

63. En una máquina little-endian con memoria de bytes y representación en complemento a dos que permite accesos a memoria de tamaño byte (1 B), media palabra (2 B) y palabra (4 B), se almacenan a partir de la posición `0xCAFEBAB0` cuatro palabras con valores -1, -2, -3, -4. ¿Qué se obtendría al consultar la media palabra de la posición `0xCAFEBABE`?

    - (x) -1.
    - ( ) -4.
    - ( ) No se puede saber, faltan datos.
    - ( ) Ninguna de las anteriores.

64. Se pretende almacenar una palabra de 4 B en una memoria de bytes a partir de una dirección determinada. ¿Cuál de las siguientes es válida, si la palabra debe quedar alineada?

    - (x) `0xFACEB00C`
    - ( ) `0xDEADBEEF`
    - ( ) `0xCAFEBABE`
    - ( ) `0xABADF00D`

65. En una arquitectura de acumulador, la instrucción `LOAD X`:

    - ( ) Transfiere el contenido del registro `X`a la memoria.
    - ( ) Suma `M(x)` al acumulador.
    - ( ) Transfiere el contenido del acumulador a la posición de memoria `X`.
    - (x) Transfiere el contenido a la posición de memoria `X` al acumulador.

66. Una instrucción máquina del tipo `Add M,R` podría formar parte del repertorio de:

    - ( ) Una máquina pila.
    - ( ) Una máquina de acumulador.
    - ( ) Una máquina con arquitectura R/R.
    - (x) Una máquina con arquitectura M/M.

67. ¿Cuál de los siguientes no es un modo de direccionamiento IA-32?

    - ( ) Registro.
    - ( ) Memoria.
    - (x) Cache.
    - ( ) Inmediato.

68. Un bus se compone de:

    - ( ) Líneas de datos y líneas de dirección.
    - ( ) Líneas de alimentación.
    - ( ) Líneas de estado y líneas de control.
    - (x) Líneas de control/estado, líneas de dirección y líneas de datos.

69. ¿Cuál de los siguientes no es un tipo de bus?

    - (x) Secuencial.
    - ( ) Paralelo.
    - ( ) E/S.
    - ( ) Sistema.

70. Si en un bus de direcciones de 32 bits se decodifica parcialmente la dirección de un dispositivo de 32 posiciones usando 22 bits, ¿cuántas veces aparecerá repetido en el mapa de memoria?

    - ( ) 10.
    - ( ) 16.
    - (x) 32.
    - ( ) 1024.

71. Para obtener una única velocidad comparativa final, el benchmark SPEC CPU combina las velocidades de ejecución de una serie de tests, respecto a un ordenador de referencia, usando la media:

    - ( ) Aritmética.
    - (x) Geométrica.
    - ( ) Armónica.
    - ( ) Ponderada.

72. El primer computador electrónico basaba su funcionamiento en:

    - (x) Tubos de vacío.
    - ( ) Circuitos integrados LSI.
    - ( ) Amplifficadores operacionales.
    - ( ) Núcleos de ferrita.

73. En Linux IA-32, si gcc usa la instrucción `leave` se puede asegurar que en ese punto del programa:

    - ( ) Correspondería emitir la secuencia de salida `pop/ret`, pero `leave` hace lo mismo y ocupa menos espacio
    - (x) Ya no hay registros salva-invocado que recuperar.
    - ( ) Ya no hay variables locales que destruir.
    - ( ) Ya no se hacen llamadas anidadas y por tanto no hay parámetros que ocupen espacio en pila.

74. Usando el repertorio IA-32, para intercambiar el valor de 2 variables (por ejemplo `A: .int 1` y `B: .int 2`) se pueden usar:

    - ( ) Dos instrucciones `mov`.
    - ( ) Una instrucción `mov` y una instrucción `lea`.
    - ( ) 3 `mov`, no menos (se le llama "intercambio circular").
    - (x) 4 `mov`, no menos (debido a la arquitectura R/M).

75. Respecto a registros base e índice en IA-32, la excepción es que:

    - ( ) `EBP` no puede ser registro base.
    - ( ) `EBP` no puede ser registro índice.
    - ( ) `ESP` no puede ser registro base.
    - (x) `ESP` no puede ser registro índice.

76. El registro `SP / ESP / RSP`:

    - ( ) Es un registro transparente al suuario y contiene la instrucción que se está ejecutando.
    - (x) Es un registro de propósito específico y contiene la dirección de la cima de la pila.
    - ( ) Es un registro transparente al usuario y contiene la dirección de memoria a la que se está accediendo.
    - ( ) Es un registro de propósito específico y contiene la dirección de la siguiente instrucción a ejecutar.

77. Diferencias gcc Linux IA-32/x86-64: marcar la respuesta falsa:

    - ( ) Los enteros largos (`long`) pasan de 32 a 64 bits.
    - ( ) Los punteros (`void*`) pasan de 32 a 64 bits.
    - (x) El tipo `double` pasa de 4 B a 8 B.
    - ( ) `long double` pasa de 10/12 B a 16 B.

78. ¿Cuál de los siguientes fragmentos de código deja en `%eax`un resultado distinto a los otros tres fragmentos?

    - (x) `mov $-1, %edx`<br>`sub %eax, %edx`<br>`mov %edx, %eax`
    - ( ) `not %eax`<br>`add $1, %eax`
    - ( ) `xor %edx, %edx`<br>`sub %eax, %edx`<br>`mov %edx, %eax`
    - ( ) `neg %eax`

79. Si `A` y `B` son dos enteros almacenados respectivamente en `%eax` y `%ebx`, ¿cuál de las siguientes implementaciones de:<br>`if(!A && !B){... then part ...}` es incorrecta?

    - ( ) ` or %ebx, %eax`<br>` jne not_true`<br>`  ...then part...`<br>`not_true:`<br>`    ...`
    - ( ) ` cmp $0, %eax`<br>`  jne not_true`<br>`  cmp $0, %ebx`<br>`  jne not_true`<br>`  ...then part...`<br>`not_true`<br>` ...`
    - (x) ` test %ebx, %eax`<br>`   jne not_true`<br>`  ...then part...`<br>`not_true`<br>` ...`
    - ( ) ` test %eax, %%eax`<br>`  jne not_true`<br>`  test %ebx, %ebx`<br>`   jne not_true`<br>`  ...then part...`<br>`not_true`<br>` ...`

80. Dada la siguiente declaración en lenguaje C, una estructura de este tipo podría ocupar en un sistema Linux IA-32 o bien en uno x86- 64 un total de:<br><code>struct a {<br> int i;<br> double d;<br> char c;<br> short s;<br>};</code>

    - ( ) 18 B.
    - ( ) 20 B.
    - ( ) 22 B.
    - (x) 24 B.

81. En un sistema Linux x86-64, ¿cuál de las siguientes expresiones es equivalente a la expresión `C (x[2] + 4)[3]`? Suponer que previamente se ha declarado `int **x`.

    - ( ) `*((*(x + 16)) + 28)`
    - ( ) `*(((*x) + 2) + 7)`
    - ( ) `(*(*(x + 2) + 4) + 3)`
    - (x) `*((*(x + 2) + 4) + 3)`

82. Una unidad de control microprogramada se denomina "con secuenciamiento de microinstrucciones explícito" según tenga o no tenga:

    - ( ) ROM/PLA para traducir el codop en dirección de inicio de microprograma (`goto f(IR)`).
    - ( ) Un multiplexor para seleccionar la fuente de la dirección de la memoria de control.
    - (x) Un micro-contador de programa atacando a las líneas de dirección de la memoria de control.
    - ( ) Microcódigo de decodificación que analice el codop bit a bit de izquierda a derecha.

83. Dado un camino de datos concreto, un posible formato de microprogramación se caracteriza como horizontal o vertical según tenga más o menos (señalar la respuesta falsa):

    - ( ) Codificación.
    - ( ) Solapamiento.
    - (x) Microbifurcaciones.
    - ( ) Longitud relativa de microinstrucción.

84. Motivos que impiden que la ganancia (aceleración) de un cauce
    segmentado sea ideal (señalar la respuesta falsa): - ( ) Registros de acoplo (coste de la segmentación). - ( ) Fragmentación desigual (duración desigual de etapas). - ( ) Riegos (hazards). - (x) Cola de instrucciones (precaptación).

85. La técnica de "adelanto de registros" (register forwarding) en un cauce segmentado se usa para limitar el impacto de los riesgos:

    - ( ) Estructurales.
    - ( ) Organizativos.
    - ( ) De control.
    - (x) (Por dependencias) de datos.

86. Las técnicas principales de E/S son (señalar la respuesta falsa):

    - ( ) DMA (por acceso directo).
    - ( ) E/S programada.
    - ( ) E/S cableada (hardwired).
    - ( ) IRQ (por interrupciones).

87. Para determinar la causa de una interrupción se pueden usar las siguientes técnicas: (señalar la respuesta falsa):

    - ( ) Múltiples líneas de interrupción: `INT1#, INT2#, ...`.
    - (x) Línea de reconocimiento `INTA#`.
    - ( ) Consulta de estado, o polling.
    - ( ) Interreupciones vectorizadas.

88. Utilizar una cache en el mismo chip del procesador:

    - ( ) Aumenta el tamaño de los bloques enviados entre cache y procesador.
    - (x) Reduce los tiempos de ejecución.
    - ( ) Reduce el tamaño del bus.
    - ( ) Aumenta la tasa de aciertos.

89. En un sistema Linux IA-32, ¿cuántos enteros se podrían almacenar en una línea de cache, si la cache del procesador fuera de 4 KB, asociativa por conjuntos de 4-vías, y contuviera 4 conjuntos?

    - ( ) 16.
    - ( ) 32.
    - (x) 64.
    - ( ) 128.

90. La cache con correspondencia directa se puede considerar como un caso límite de la asociativa por conjuntos, en donde:
    - (x) Sólo hay 1 línea por conjunto.
    - ( ) Sólo hay 1 palabra por bloque.
    - ( ) Sólo hay 1 conjunto por cache.
    - ( ) Ninguna de las anteriores.

91. Si almacenamos según el criterio little-endian la palabra de 64 bits `0xFACEB00C` a partir de la dirección `0xCAFEBABE`, el byte `0xCE` quedará almacenado en la dirección:

    - ( ) `0xCAFEBAC1`
    - (x) `0xCAFEBAC0`
    - ( ) `0xCAFEBABF`
    - ( ) `0xCAFEBABE`

92. ¿Qué novedad se desarrolló en la tercera generación de computadores?

    - (x) Los circuitos integrados.
    - ( ) Los primeros lenguajes de programación de alto nivel.
    - ( ) Los microprocesadores CISC.
    - ( ) Los microprocesadores RISC.

93. En x86-64, el registro contrador de programa se denomina:

    - (x) `RIP`
    - ( ) `EIP`
    - ( ) `IP`
    - ( ) `R15`

94. La primera letra (`l`) de la instruccion `lea`:

    - ( ) Indica que la instrucción usa ordenación de bytes little-endian.
    - ( ) Indica que la instrucción trabaja con un operando destino de 32 bits (`long word`).
    - ( ) Indica indica que la instrucción afecta a los 16 bits menos significativos del operando destino (`long word`).
    - (x) Forma parte del nemotécnico de la instrucción.

95. ¿Cuál es la diferencia entre las instrucciones `mov` y `lea`?

    - ( ) `lea` accede a la posición indicada, mientras que `mov` no lo hace.
    - (x) `mov` accede a la posición indicada, mientras que `lea` no lo hace.
    - ( ) `lea` puede usarse para copiar un registro a otro, mientras que `mov` no.
    - ( ) `mov` puede usarse para copiar un registro a otro, mientras que `lea` no.

96. La instrucción `not`:

    - ( ) Realiza el complemento a dos.
    - (x) Realiza el complemento a uno (cambiar unos por ceros y ceros por unos).
    - ( ) Realiza la operación `no-or` (or negada).
    - ( ) Realiza un salto condicional si negativo.

97. La instrucción `JGE / JNL` provoca un salto si:

    - ( ) `SF = 1`
    - ( ) `CF = 1`
    - ( ) `SF = 0`
    - (x) `OF = SF`

98. Un overflow nunca puede ocurrir cuando:

    - ( ) Se suman dos números positivos.
    - ( ) Se suman dos números negativos.
    - (x) Se suma un número positivo a un número negativo.
    - ( ) Se resta un número positivo de un número negativo.

99. Después de ejecutar una instrucción de suma sobre dos números con signo de la que sabemos que no provocará overflow (los dos números son pequeños en valor absoluto), queremos comprobar si el resultado de la suma es menor que 0. ¿Qué flag necesita comprobar la instrucción de salto condicional equivalente a `if (resultado<0) then goto label`?

    - ( ) `CF`
    - ( ) `OF`
    - (x) `SF`
    - ( ) `ZF`

100.  La instrucción `cmovb %edx, %eax`:- (x) Copia en `%eax` el contenido de `%edx` si el indicador de acarreo es 1.
    - ( ) Copia el byte bajo de `%edx` en el byte bajo de `%eax`.
    - ( ) Copia en `%eax` el byte de memoria apuntado por la dirección contenida en `%edx`.
    - ( ) Copia en `%eax` el contenido de `%edx` si `%eax` es menor que `%edx`.

101. ¿Cuál de las siguientes afirmaciones sobre la instrucción `leave` es cierta?
    - ( ) Se ejecuta justo después de retornar de un procedimiento.
    - ( ) Equivale a `pop %ebp` seguida de `mov %ebp, %esp`.
    - ( ) Equivale a `mov %esp, %ebp` seguida de `pop %ebp`.
    - (x) No es obligatorio usarla. En su lugar puede realizarse una secuencia explícita de operaciones `mov` y `pop`.

102. Para crear espacio en la pila para variables locales sin inicializar suele realizarse la siguiente operación:
    - ( ) Restar una cantidad positiva a `EBP`.
    - ( ) Sumar una cantidad positiva a `EBP`.
    - (x) Restar una cantidad positiva a `ESP`.
    - ( ) Sumar una cantidad positiva a `ESP`.

103. ¿Cuál de los siguientes lenguajes no permite el paso de parámetros por referencia?
    - ( ) Pascal.
    - (x) C.
    - ( ) C++.
    - ( ) FORTRAN.

104. En la secuencia de programa siguiente:<br><code>804854e:e8 3d 06 00 00 call 8048b90 (main)<br>8048553:50 pushl %eax</code><br>¿Cuál es el valor que introduce en la pila la instrucción call?
    - ( ) `804854e`
    - ( ) `804854f`
    - ( ) `8048b90`
    - (x) `8048553`

105. En el fragmento de código:<br><code>804854e:e8 3d 06 00 00 call 8048b90 (main)<br>8048553:50 pushl %eax</code><br>La instrucción `call` suma al contador de programa la cantidad:
    - (x) `0000063d`
    - ( ) `08048553`
    - ( ) `0804854e`
    - ( ) `50`

106. Es responsabilidad del procedimiento llamado salvaguardar los registros:
    - (x) `%ebx, %esi, %edi`
    - ( ) `%eax, %edx, %ecx`
    - ( ) `%eax, %ebx, %ecx, %edx`
    - ( ) `%esi, %edi`

107. Al llamar a una función de 2 argumentos `foo(arg1, arg2)`, ¿cuál es el orden correcto en el que se ejecutan las instrucciones? (suponiendo convención de llamada x86 cdecl, y que `foo` requiere ajustar marco de pila, esto es, salvar `%ebp`).
    - ( ) `push arg1, push arg2, call foo, push %ebp`
    - ( ) `push arg1, push arg2, push %ebp, call foo`
    - (x) `push arg2, push arg1, call foo, push %ebp`
    - ( ) `push arg2, push arg1, push %ebp, call foo`

108. Cuando se ejecuta la instrucción `ret` al final de una subrutina:
    - ( ) La dirección de comienzo de la pila se transfiere al puntero de pila.
    - ( ) La dirección de memoria de la instrucción `ret` se transfiere al contador de programa.
    - (x) La dirección almacenada en la cima de la pila se transfiere al contador de programa.
    - ( ) La direción almacenada en la cima de la pila se transfiere al puntero de pila.

109. En IA-32 la pila es:
    - ( ) Un registro de 16 bits en el microprocesador.
    - ( ) Un registro de 32 bits en el microprocesador.
    - ( ) Una dirección de memoria de 32 bits almaenada en el contador de programa.
    - (x) Un conjunto de posiciones de memoria usadas para almacenar información temporal durante la ejecución del programa.

110. En IA-32 el puntero de pila es:
    - ( ) Un registro de 16 bits en el microprocesador.
    - (x) Un registro de 32 bits en el microprocesador.
    - ( ) Una dirección de memoria de 32 bits almacenada en el contador de programa.
    - ( ) Un conjunto de posiciones de memoria usadas para almacenar información temporal durante la ejecución del programa.

111. ¿Cuál de las siguientes afirmaciones _NO_ es cierta? (entender que x86=IA-32)
    - ( ) x86-64 proporciona un espacio de memoria virtual mayor que x68.
    - ( ) Las disciplinas pilas para x86 y x86-64 son diferentes.
    - ( ) x86 usa `%ebp` como puntero base para el marco de pila.
    - (x) x86-64 usa `%rbp` como puntero base para el marco de pila.

112. Alguna de las siguientes _NO_ es una operación básica de la unidad de control:
    - ( ) Transferir un registro a otro.
    - ( ) (Leer/escribir) un registro (de/a) memoria.
    - (x) (Guardar/recuperar) registro (en/de) la pila.
    - ( ) Realizar una operación de la ALU y guardar el resultado en un registro.

113. Un computador tiene una memoria de control de 16000 palabras de 250 bits, de las que 447 son diferentes. ¿Cuántos bits ahorramos usando nanoprogramación en lugar de microprogramación?
    - (x) 3744250
    - ( ) 259206
    - ( ) 287935
    - ( ) Ninguno de los resultados anteriores es exacto.

114. Un sistema no segmentado tarda 20 ns en procesar una tarea. La misma tarea puede ser procesada en un cauce (pipeline) de 4 segmentos con un ciclo de reloj de 5 ns. Cuando se procesan muchas tareas, la ganancia máxima de velocidad que se obtiene se aproxima a:
    - ( ) 5.
    - (x) 4.
    - ( ) 0.25.
    - ( ) 20.

115. En la técnica de salto retardado:
    - (x) El compilador puede reorganizar el código para rellenar los huecos de retardo con instrucciones útiles.
    - ( ) El compilador no puede insertar operaciones `NOP` en los huecos de retardo.
    - ( ) El slto se realiza varios ciclos antes de la instrucción de salto.
    - ( ) Las instrucciones en los huecos de retardo se ejecutan unas veces y otras no.

116. Al método de interacción con los periféricos, en los que el procesador vigila periódicamente el estado de los dispositivos mediante una encuesta activa se le denomina:
    - ( ) daisy-chain.
    - ( ) interrupción.
    - (x) polling.
    - ( ) DMA.

117. ¿Cuántas señales de control se necesitan como mínimo para implementar un sistema de gestión de interrupciones?
    - ( ) 1.
    - (x) 2.
    - ( ) 3.
    - ( ) 4.

118. Se dispone de un procesador con una frecuencia de reloj de 1 GHz. Se le conecta un dispositivo que genera 100.000 interrupciones por segundo. La rutina de servicio de interrupción ejecuta 500 instrucciones. El número medio de ciclos por instrucción es 2. ¿Qué porcentaje del tiempo dedica el procesador al dispositivo?
    - ( ) 1%.
    - (x) 10%.
    - ( ) 50%.
    - ( ) 90%.

119. ¿Cuál de las siguientes afirmaciones acerca de las memorias es _FALSA_?
    - ( ) La memoria dinámica usa señales de control `RAS#` y `CAS#`.
    - ( ) Las celdas de memoria dinámica están constituidas por un transistor y un condensador.
    - (x) Las celdas de memoria estática tienen que ser constantemente refrescadas.
    - ( ) La memoria estática se emplea en las cachés L1 y L2.

120. ¿Cuál de las siguientes afirmaciones acerca de la jerarquía de memoria es _FALSA_?
    - ( ) Acceder a los discos es órdenes de magnitud más lento que acceder a la RAM.
    - ( ) Una memoria principal constituida por la tecnología más rápida es órdenes de magnitud más cara que la DRAM.
    - (x) La velocidad de acceso Lamemoria principal ha crecido proporcionalmente a la velocidad del procesador.
    - ( ) Un computador puede tener una pequeña cantidad de memoria rápida además de una gran cantidad de memoria más lenta.

121. En una máquina little-endian con memoria de bytes y representación en complemento a dos que permite accesos a memoria de tamaño byte (1B), media palabra (2B) y palabra (4B), si se almacena en la posición `0xBABC` una palabra de valor -2, ¿qué se obtendría al consultar la media palabra en la posición `0xBABE`?
    - ( ) 0.
    - ( ) 1.
    - (x) -1.
    - ( ) 2.

122. Según la clasificación `m/n`, las máquinas de acumulador son de tipo:
    - ( ) `0/0`.
    - (x) `1/1`.
    - ( ) `1/2`.
    - ( ) `2/2` ó `2/3`.

123. Según la clasificación `m/n` las máquinas con arquitectura `R/R` son de tipo:
    - ( ) `0/0`.
    - (x) `0/x` con `x=2,3`.
    - ( ) `x/0` con `x=2,3`.
    - ( ) `x/x` con `x=2,3`.
