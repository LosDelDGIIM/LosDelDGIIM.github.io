<br>

# EC. Preguntas Tipo Test de Teoría + Prácticas.

**Autor:** Jose Juan Urrutia Milán 'JJ'.<br>
**Autor:** Lucas Hidalgo Herrera.<br>
**Autor:** Lucas Hidalgo Herrera.<br>
**Autor:** Roberto González Lugo.<br>
**Autor:** Elías Monge Sánchez.<br>
**Autor:** Jesús Muñoz Velasco.<br>
**Autor:** Arturo Olivares Martos.
***

- **Asignatura:** Estructura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
- **Profesor:** Ignacio Rojas Ruiz.
- **Descripción:** Este documento tiene como objetivo servir para estudiar la asignatura de Estructura de Computadores. En él, se pueden encontrar una gran variedad de preguntas de EC de los últimos años.

Es importante destacar que hay preguntas de todos los temas de la asignatura. Además, algunas preguntas podrán ser sobre IA32, que actualmente ya no entra prácticamente en la asignatura.
Por último, puede ser que haya preguntas repetidas. En tal caso, se ruega nos lo comuniquen.

Las preguntas se encuentran en <a href=https://losdeldgiim.github.io/subjects/EC/Ex%C3%A1menes/Examenes_Generados/TipoTest.html>esta web</a>.

Las explicaciones de cada pregunta se pueden encontrar en el archivo Markdown correspondiente, que se encuentra pinchando <a href=https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/EC/Ex%C3%A1menes/TipoTest.md>aquí</a>.
______

1. Respecto a direccionamiento a memoria en ensamblador x86-64, de la forma `D(Rb, Ri, S)`, sólo una de las siguientes afirmaciones es FALSA. ¿Cuál?
    - ( )  El desplazamiento D puede ser una constante lineal (1, 2 ó 4 bytes).
    - (x)  `EBP` no se puede usar como registro base.
    - ( )  `ESP` no se puede usar como registro índice.
    - ( )  El factor de escala `S` puede ser 1, 2, 4, 8.

Explicacion: `EBP` sí puede usarse como base, ya que es un registro más. No obstante, `ESP` no puede usarse como índice, ya que es el puntero de pila y y, por tanto, su modificación provocaría graves errores en la ejecución del programa.

2. La extensión de signo a m bits de un número original N de n bits, con m > n, consiste en:
    - ( )  Realizar la operación \\(2^{m– N}\\)
    - ( )  Realizar la operación \\(2^{m– N-1}\\)
    - (x)  Incrementar la cantidad de bits a m preservando el signo y el valor del número.
    - ( )  Incrementar la cantidad de bits a m rellenando con unos por la izquierda.

Explicacion: No siempre tiene que rellenar con unos, ya que el número original puede ser positivo.

3. En x86-64, ¿cuál de los siguientes fragmentos de programa tiene un efecto sobre los flags distinto al resto?
    - ( )  `sub %edi,%edi` <br> `adc $0xFFFFFFFF, %edi`
    - (x)  `mov $-1, %edi`
    - ( )  `mov$-1,%edi` <br> `add $0, %edi`
    - ( )  `mov $0, %edi` <br> `sub $1, %edi`

Explicacion: Todas las órdenes descritas ponen a 1 el valor de `SF` excepto la segunda, ya que la orden `mov` tan solo mueve datos, no modifica las banderas.

4. Si `%rsp` vale `0xdeadbeefdeadd0d0`, ¿cuál será su nuevo valor después de que se ejecute `pushq %rbx?`
    - ( )  `0xdeadbeefdeadd0d4`
    - ( )  `0xdeadbeefdeadd0d8`
    - ( )  `0xdeadbeefdeadd0cc`
    - (x)  `0xdeadbeefdeadd0c8`

Explicacion: La pila crece hacia posiciones decrecientes. Por tanto, en este caso, el puntero se actualiza a `-8(%rsp)`.

5. ¿Cómo se devuelve en ensamblador x86-64 Linux `gcc` el valor de retorno de una función `long int` al terminar esta?
    - ( )  La instrucción `RET` lo almacena en un registro especial de retorno.
    - ( )  Por convención se guarda en `%eax`.
    - ( )  Se almacena en pila justo encima de los argumentos de la función.
    - (x)  Ninguna de esas formas es correcta.

Explicacion: Por convención, y al ser datos de tipo `long`, se guarda en el registro `%rax`.

6. Comparando las convenciones de llamada de gcc Linux IA32 con x86-64 respecto a registros **(IA32 ya no entra)**.
    - ( )  En IA32 `%ebx` es salva-invocante, pero en x86-64 `%rbx` es salva-invocado.
    - (x) En IA32 `%ecx` es salva-invocante, y en x86-64 `%rcx` es salva-invocante también.
    - ( )  En IA32 `%esi` es salva-invocado, y en x86-64 `%rsi` es salva-invocado también.
    - ( )  En IA32 `%ebp` es especial (marco de pila), y en x86-64 `%rbp` también.

Explicacion: El IA32 actualmente no entra en la asignatura EC.

7. Son funciones de la unidad de control:
    - ( )  La codificación de las instrucciones máquina.
    - ( )  La lectura de memoria principal de la instrucción apuntada por el PC.
    - (x)  El secuenciamiento de las instrucciones máquina.
    - ( )  Todas las respuestas son ciertas.

Explicacion: La EC es la que se encarga de las señales de reloj, etc.

8. Respecto a `MBR` y `MAR`
    - ( )  Ambos son accesibles por el programador.
    - ( )  `MAR` contiene el dato/instrucción que se leerá o escribirá en memoria.
    - (x) `MAR` requiere menos señales de control que `MBR`.
    - ( )  Ambos permiten guardar información sobre el marco de pila.

9. Una instrucción máquina puede desglosarse en las siguientes operaciones elementales:<br>
`sp := sp-1; m[sp] := pc; pc:= x`<br>
Probablemente se trate de una instrucción de:
    - ( )  Apilamiento.
    - (x)  Llamada a subrutina.
    - ( )  Carga total.
    - ( )  Almacenamiento local.

Explicacion: Se está llamando a una subrutina, ya la pila crece guardándose el valor de retorno de `pc`, y el `pc` se actualiza a donde tiene que saltar.

10.  En una unidad de control microprogramada con formato de microinstrucciones vertical, un subcampo que debe especificar 16 señales de control codificadas de tal forma que pueda activarse sólo una o ninguna harbá de tener una anchura mínima de:
    - ( )  4 bits.
    - (x)  5 bits.
    - ( )  16 bits.
    - ( )  17 bits.

Explicacion: Son 16 señales más el 0; por lo que son 17. Para codificar 17 posibilidades en binario, en necesiario tener en cuenta que se necesitan $log_2(17)$ redondeados hacia arriba bits. Es decir, nos hacen falta 5 bits.


11. Dado un camino de datos concreto, un posible formato de microprogramación se caracteriza como horizontal o vertical según tenga más o menos (señalar la respuesta falsa)
    - ( ) codificación
    - ( ) solapamiento
    - (x) micro bifurcaciones
    - ( ) longitud relativa de microinstrucción.

12. El control residual se utiliza para:
    - ( ) reducir el tiempo de ejecución de las instrucciones máquina
    - ( ) eliminarlos bits residuales de la ejecución de las microinstrucciones
    - (x) reducir el tamaño de la memoria de control
    - ( ) ninguna de las anteriores es cierta.

13. Un procesador está segmentado en las etapas F, D, E, M y W. Cada una de  ellas consume un tiempo t. La aceleración ideal (si no hay riesgos) al ejecutar n instrucciones respecto a un procesador no segmentado será:
    - (x) 5n/(4+n)
    - ( ) (4+n)/5t
    - ( ) 4n/(5+n)
    - ( ) (5+n)/4t

Explicacion: El número de operaciones en un procesador no segmentado sería 5 por el número de instrucciones. No obstante, 

14. En un procesador con segmentación de cauce, aumentar el número de etapas (p.ej. de 2 a 4, o de 4 a 8), tiene en general como consecuencia:
    - (x) Un Incremendo De Las Prestaciones.
    - ( ) Un mayor retraso en la ejecución de los programas debido al incremento del número de etapas.
    - ( ) Una disminución en la posible dependencia de datos.
    - ( ) Una disminución de la máxima frecuencia de reloj a la que puede operar el cauce.
    
Explicacion: Se pueden ejecutar más instrucciones simultáneamente, ya que en cada ciclo de reloj podrá entrar una nueva instrucción al cauce.

15. En la secuencia de instrucciones siguiente, siendo el primer registro el destino, ¿cuántos riesgos se dan?<br>
<code>sub r2,r1,r3<br>or r8,r6,r2</code><br>
    - ( ) Un riesgo estructural.
    - (x) Un riesgo por dependencia de datos.
    - ( ) Un Riesgo Estructural Dos Por dependencia de datos.
    - ( ) Dos riesgos por dependencia de datos y uno de control.

16. La precaptación (cola de instrucciones) está relacionada con...
    - (x) Los riesgos estructurales (intenta evitar el efecto de un fallo de cache)
    - ( ) Los riesgos de (dependencia de) datos (intenta que el dato esté disponible anticipadamente)
    - ( ) Los riesgos control (intenta determinar de antemano el flujo de control)
    - ( ) Los riesgos de transferencia (intenta agrupar las posibles transferencias de un conjunto de instrucciones).

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

Explicacion: Son referentes al IA32, que actualmente no entra en la asignatura EC.

19. La conexión entre un dispositivo de E/S y el procesador mediante bus:
    - ( ) Es difícil de expandir.
    - (x) Permite conectar en paralelo varios dispositivos.
    - ( ) Requiere mucha circuitería.
    - ( ) Requiere multiplexores y demultiplexores para las señales de datos.

Explicacion: Se pueden incluir más dispositivos, y mediante puertas lógicas podemos evitar cortocircuitos.


20. El fragmento de código ensamblador de un microprocesador de 8 bits:<br><code>lds IOBuf	; Apuntar puntero pila a ...área mem.intermedia<br>ldx Count	; Inicializar x-contador<br>poll lda a Status; Leer estado en A<br>bpl poll	; Signo (A) != 1 => repetir<br>lda a Data	; Leer dato en A<br>psh a		; transferir dato a pila<br>dex 		; decrementar contador x<br>bne poll	; Seguir leyendo si x!=0<br></code><br> Corresponde a:<br>
    - (x) Entrada programada con consulta de estado.
    - ( ) Salida programada sin consulta de estado. 
    - ( ) Entrada programada sin consulta de estado.
    - ( ) Salida programada con consulta de estado.

Explicacion: Vemos que se consulta el estado y, si se da la condición, se sigue leyendo.

21. En la E/S controlada por interrupciones:
    - (x) Entrada programada con consulta de estado
    - ( ) Salida programada sin consulta de estado
    - ( ) Entrada programada sin consulta de estado
    - ( ) Salida programada con consulta de estado

22. La instrucción máquina DI (Disable Interrupts), conocida como CLI (Clear Interrupt Flag) en x86, se utiliza para desactivar:
    - (x) Todas Las Interrupciones Enmascarables
    - ( ) Las interrupciones de inferior o igual prioridad a una dada
    - ( ) Determinados niveles de interrupción de forma selectiva
    - ( ) Las interrupciones software

23. Con nueve controladores de interrupciones 8259 se pueden manejar
exactamente:
    - ( ) 8 niveles de prioridad
    - ( ) 16 niveles de prioridad
    - ( ) 24 niveles de prioridad
    - (x) Ninguna de las anteriores es cierta

24. ¿Cuál de los siguientes es un registro de un controlador de DMA?
    - ( ) `IR` (Instruction Register)
    - ( ) `PC` (Program Counter)
    - ( ) `SP` (StackPointer)
    - (x) `WC` (Word Count)

25. Respecto al refresco de memorias DRAM, ¿cuál de las siguientes afirmaciones es falsa?
    - (x) Una operación de refresco consiste en dar un impulso /CAS junto con una dirección de columna.
    - ( ) Los chips DRAM refrescan automáticamente la fila accedida en cualquier ciclo de lectura o escritura.
    - ( ) Se precisa una circuitería auxiliar, externa al chip DRAM o integrada en él, que produzca ciclos de refresco.
    - ( ) Los ciclos de refresco deben producirse cada pocos ms (milisegundos).

26. La tasa de aciertos \\(A_i\\) del nivel i de una jerarquía de memoria no depende de:
    - ( ) La capacidad (tamaño) ni del nivel i.
    - ( ) La estrategia de administración de memoria.
    - ( ) La unidad de la transferencia de información \\(x_i\\) entre el nivel i y el  \\(i+1\\).
    - (x) El ancho de banda  \\(b_i\\) del nivel i.

27. La política de correspondencia de una memoria cache con 1 único conjunto es:
    - ( ) Directa
    - (x) Totalmente asociativa
    - ( ) Asociativa por conjuntos con una única línea
    - ( ) Asociativa por conjuntos de una única vía

28. La política de correspondencia de una memoria cache con la mitad de conjuntos que líneas es:
    - (x) Asociativa por conjuntos de 2 vías
    - ( ) Totalmente asociativa de media vía
    - ( ) Asociativa por conjuntos con 2 líneas
    - ( ) Directa con 2 líneas

29. Para construir una DRAM de 4GB con pastillas de 512Mx4bit hacen falta
    - ( ) 8 pastillas
    - (x) 16 pastillas
    - ( ) 32 pastillas
    - ( ) 64 pastillas

30. Para diseñar una memoria con ancho de palabra  \\(k\times m\\) (y mismo no palabras que los módulos) a partir de módulos con ancho de palabra m, se utilizan k módulos
    - ( ) repartiendo las líneas de datos entre los k módulos: el primero se conecta a D0...Dk-1, el segundo a Dk...D2k-1, etc
    - ( ) repartiendo las líneas de dirección: el 1o se conecta a A0...Ak-1, el 2o a Ak...A2k-1, etc
    - (x) repartiendo líneas datos:el 1o se conecta a D0...Dm-1, el 2o a Dm...D2m-1, etc
    - ( ) repartiendo líneas dirección: el 1o se conecta a A0...Am-1, el 2o a Am...A2m-1, etc

31. ¿Cuál de las siguientes afirmaciones sobre el benchmark SPEC CPU es falsa?

    - ( ) La última versión es SPEC CPU2006 V1.2 de 2011.
    - ( ) Se cronometran unos 12 tests de enteros (CINT2006) y unos 17 tests de punto flotante (CFP2006).
    - ( ) Se usa como referencia un computador UltraSPARC II 300MHz, y para cada test se calcula el cociente entre el tiempo de ejecución en el computador a testear y en el de referencia.
    - (x) El resultado final es la media aritmética de las (12 ó 17) velocidades, bien sea de enteros ó de punto flotante (SPECint2006 ó SPECfp2006).

Explicacion: No es la media aritmética, es la geométrica.

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

34. Con el repertorio x86-64, para sumar `%eax` y `%ebx` dejando el resultado en `%ecx` se podría hacer lo siguiente:

    - ( ) `lea %eax, %ebx, %ecx`
    - (x) `lea (%eax, %ebx, 1), %ecx`
    - ( ) `lea %ecx, [%eax, %ebx]`
    - ( ) `lea %ecx, %ebx, %eax`

35. Cuál de las instrucciones máquina siguientes es incorrecta en x86-64:

    - ( ) `testl %edx, %edx`
    - (x) `movl %r8, %eax`
    - ( ) `movl (%rdi, %rcx, 4), %edx`
    - ( ) `addq $1, %rcx`

Explicacion: TERMINAR

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

Explicacion: En binario, tenemos que `0x20=0b10 0000`. Notemos que se empieza a contar desde 0.

38. Si tenemos un número `n`, de 64 bits, almacenado en la pareja de registros `EDX:EAX` (`EDX` contiene los 32 bits más significativos y `EAX` los 32 bits menos significativos) y queremos realizar la división \\(n/2^{32}\\) entonces:

    - ( ) Podemos quedarnos con `EDX`, pero sólo en el caso de que `n` sea un número sin signo.
    - (x) Podemos quedarnos con `EDX` tanto si `n` es un número con signo como sin signo.
    - ( ) Podemos usar las instrucciones siguientes, pero sólo en el caso de que `n` sea un número con signo: <br><code>mov $0x100000000, %ecx<br>div %ecx</code>
    - ( ) Podemos usar las instrucciones siguientes, tanto si `n` es un número con signo como sin signo: <br><code>mov $0x100000000, %ecx<br>div %ecx</code>

Explicacion: Al dividir entre $2^{32}$, es como desplazar hacia la derecha 32 bits. Los 32 LSB se perderán, quedando tan solo `EDX`. Además, el signo se mantiene, ya que el `MSB` de `n` sigue siendo el `MSB` de `EDX`. No obstante, el cociente ya está en 32 bits, no en 64.

39. ¿Dónde está ubicado el séptimo argumento a una función (suponer código ensamblador generado por gcc para x86-64) inmediatamente después de ejecutar la instrucción `call`?

    - ( ) `%rbp + 0x8`
    - ( ) `%rbp - 0x8`
    - (x) `%rsp + 0x8`
    - ( ) `%rsp - 0x8`

Explicacion: Los 6 primeros son registros. El séptimo es el primero en la pila. Como el puntero de pila es `%rsp`, y la pila crece en direcciones decrecientes, tenemos que ha de sumársele 8 para acceder al último valor guardado.

40. Dado el código C siguiente:<br><code>struct data {<br> char str[16];<br>};<br>char *f(struct data *ptr) {<br> return &(ptr->str[2]);<br>}</code><br>La función se traducirá a ensamblador de x86-64 como:

    - (x) `leaq 2(%rdi), %rax` <br>`ret`
    - ( ) `movq (,%rdi,2), %rax` <br>`ret`
    - ( ) `movq 2(%rdi), %rax` <br>`ret`
    - ( ) `leaq (,%rdi,2), %rax` <br>`ret`

Explicacion: A la dirección de memoria de `ptr` (que está en `%rdi`), ha de sumársele 2, ya que los `char` se codifican con un byte. Por tanto, es `2(%rdi)`. Además, como no se quiere obtener el contenido, sino tan solo la dirección (`&`), no usa `movq` sino `leaq`.

41. Respecto a requisitos de alineamiento de structs en gcc/IA32 x86 y x86-64, alguna de las siguientes afirmaciones es falsa:

    - (x) En x86 Linux alinea `double` a 4x (Windows no).
    - ( ) En x86 Linux alinea `long double` a 4x (Windows también).
    - ( ) En x86-64 Linux alinea `double` a 8x (Windows también).
    - ( ) En x86-64 Linux alinea `float` a 8x (Windows también).

Explicacion: Windows también lo alinea a `4x`.

42. Si la estructura struct `a` ocupa un espacio de 28 bytes en memoria, ¿cuántos bytes ocupa la siguiente estructura struct `b` cuando se compila en 64 bits? <br><code>struct b {<br> struct a a1;<br> int i;<br> struct a a2;<br>};</code>

    - ( ) 24 bytes.
    - ( ) 60 bytes.
    - ( ) 64 bytes.
    - (x) 84 bytes.

Explicacion: El offset de `a1` es 0, el de `i` es 28, y el de `a2` ha se ser múltiplo de 28, por lo que es 56. Por tanto, aunque un `int` solo ocupe 4, el resto de bits hasta ocupar 28 no se usan.

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

Explicacion: El registro de estado contiene todas las banderas, como `ZF, CF, OF, SF` .

45. Un procesador con una unidad de control microprogramada tiene una memoria de control de 300 palabras de 100 bits, de las que 200 son diferentes. Si se rediseñara como unidad de control nanoprogramada, ¿qué tamaño ocuparía la nanomemoria que contiene las microinstrucciones completas sin repeticiones?

    - (x) 20000 bits.
    - ( ) 21600 bits.
    - ( ) 22400 bits.
    - ( ) 30000 bits.

Explicacion: La nanomemoria tendría 200 palabras, y cada una sería una dirección, por lo que ocuparía 100 bits.

46. En el pseudocódigo usado para representar las microinstrucciones, la expresión `goto f(IR)`:

    - ( ) Se utiliza para realizar un microsalto condicional en función del registro de estado.
    - ( ) Realiza una llamada a una microsubrutina.
    - (x) Salta a una dirección de memoria de control que depende de la instrucción máquina actual.
    - ( ) Permite saltar a la dirección de memoria de control del principio de un microbucle.

Explicacion: `IR` contiene la instrucción máquina actual, y `f` se supone que es una función que devolverá a qué dirección de memoria ha de saltar.

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

Explicacion: En ambos es fundamental.

49. Respecto a los conceptos de interfaz de dispositivo, controlador(a), puerto de E/S:

    - (x) La controladora o interfaz contiene los puertos necesarios para utilizar el dispositivo.
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

52. Una puerta `AND` con 16 entradas conectada a un bus de direcciones de 16 bits, con todos los bits negados excepto `A10` y `A6`, permite seleccionar un dispositivo (con `CS` activa en alta) en la dirección:

    - ( ) `0xFDDF`
    - ( ) `0xFBBF`
    - ( ) `0x0220`
    - (x) `0x0440`

Explicacion: `CS` activa en alta implica que, cuando recibe un `1`, se ha seleccionado dicho dispositivo. Para que una puerta `AND` emita un 1, todas sus entradas han de ser 1. Para los bits negados, ha de ser un 0 el bit correspondiente de la dirección, pero para el 6º y 10º (empezando desde el 0) han de estar a 1. Por tanto, ha de ser `0b 0000 0100 0100 0000 = 0x0440`.

53. Un computador con 15 líneas de direcciones tiene 3 módulos de memoria de \\(2^{13}\\) palabras y utiliza E/S mapeada en memoria. ¿Cuál es el número máximo de periféricos que pueden conectarse, si cada uno de ellos utiliza 8 direcciones?

    - (x) \\(2^{10}\\).
    - ( ) \\(2^{12}\\).
    - ( ) \\(2^{11}\\).
    - ( ) \\(2^{13}\\).

Explicacion: Si hay 3 módulos de $2^{13}$ palabras, como cada palabra ocupa una dirección, estos ocupan $3\cdot 2^{13}$ direcciones. Por tanto, quedan libre $2^{13}$ direcciones. Como cada periférico ocupa $8=2^3$ direcciones, tenemos espacio para $2^{10}$ periféricos. De esta forma, tendremos: $$3\cdot 2^{13} + 2^{10}\cdot 2^{3}=3\cdot 2^{13} + 2^{13}=(3+1)\cdot 2^{13}=2^{15}$$

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

Explicacion: Tenemos que el $92%$ de las veces se usa la caché, y el $8%$ restante la memoria principal. Para los casos de la caché, se tarda 4ns, y para los de la MP se tardan 104ns (los 100 de la MP y los 4 de la caché fallida). Por tanto, en total son: $$4\cdot 0.92 + 104\cdot 0.08=12$$

56. Una SRAM de `1Mx4bit` (4Mbit) puede venir organizada en 2048 filas, dedicando por tanto al decodificador de columnas:

    - ( ) 6 bits.
    - ( ) 7 bits.
    - ( ) 8 bits.
    - (x) 9 bits.

Explicacion: El tamaño de la memoria especificado así implica que hay $1M = 2^{20}$ casillas y cada una ocupa 4 bits (esto último no nos es relevante). Como en total hay $2048=2^{11}$ filas, en total hay $2^{9}$ columnas, por lo que se emplean 9 bits.

57. Un sistema basado en un microprocesador con un bus de datos de `n` bits y un bus de direcciones de 16 bits direcciona la memoria por palabras de `n` bits y dispone de una memoria SRAM formada por dos módulos de `16 K x n` cada uno. ¿Qué porcentaje del mapa de memoria está ocupado por la SRAM?

    - ( ) 12.5%
    - ( ) 25%
    - (x) 50%
    - ( ) 100%

Explicacion: Veamos el tamaño de memoria de cada uno de los dos módulos: $$16K\cdot n = 2^4\cdot 2^{10}\cdot n=2^{14}\cdot n$$ Como hay dos módulos, tenemos que la SRAM ocupa $2^{15}\cdot n$ bits. Como el bus de direcciones es de 16 bits, implica que en total el espacio de memoria es de $2^{16}$ direcciones, cada una de $n$ bits. Por tanto, la SRAM ocupa la mitad.

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

Explicacion: La arquitectura Von Neumman consiste en la separación de ALU, UC, E/S, MP, por lo que no es lo descrito. La UC no necesita saber la siguiente instruccón, tan solo activará la señal de reloj cuando toque captarla. El MAR tan solo contiene direcciones, no datos. Por tanto, la correcta es la segunda.

63. En una máquina little-endian con memoria de bytes y representación en complemento a dos que permite accesos a memoria de tamaño byte (1 B), media palabra (2 B) y palabra (4 B), se almacenan a partir de la posición `0xCAFEBAB0` cuatro palabras con valores -1, -2, -3, -4. ¿Qué se obtendría al consultar la media palabra de la posición `0xCAFEBABE`?

    - (x) -1.
    - ( ) -4.
    - ( ) No se puede saber, faltan datos.
    - ( ) Ninguna de las anteriores.

Explicacion: Cada palabra guardada ocupa 4 Bytes, por lo que el -4 empieza en la dirección `0xCAFEBABC`. El -4 tenemos que es `-4=0xFFFB`, por lo que en la dirección `0xCAFEBABC` se encuentra la B, y en las tres direcciones siguientes una F. Por tanto, la media palabra que empieza en `0xCAFEBABE` y, por tanto, cupa también `0xCAFEBABF`, es `0xFF=-1`.

64. Se pretende almacenar una palabra de 4 B en una memoria de bytes a partir de una dirección determinada. ¿Cuál de las siguientes es válida, si la palabra debe quedar alineada?

    - (x) `0xFACEB00C`
    - ( ) `0xDEADBEEF`
    - ( ) `0xCAFEBABE`
    - ( ) `0xABADF00D`

Explicacion: Las palabras han de empezar en múltiplos de 4, por lo que los dos últimos bits de la dirección han de ser 0. Esto tan solo ocurre si los últimos 4 bits son `0b0000=0x0`, `0b0100=0x4`, `0b1000=0x8` o `0b=1100=0xC`. Por tanto, la única dirección que está alineada es la que termina en `C`.

65. En una arquitectura de acumulador, la instrucción `LOAD X`:

    - ( ) Transfiere el contenido del registro `X` a la memoria.
    - ( ) Suma `M(x)` al acumulador.
    - ( ) Transfiere el contenido del acumulador a la posición de memoria `X`.
    - (x) Transfiere el contenido de la posición de memoria `X` al acumulador.

Explicacion: Esta arquitectura es del tipo `1/1`, por lo que todas las instrucciones reciben 1 operando, y es una dirección de memoria. Todo se controla con el acumulador, por lo que cargar la dirección de memoria `X` se ha de hacer en el acumulador.

66. Una instrucción máquina del tipo `Add M,R` podría formar parte del repertorio de:

    - ( ) Una máquina pila.
    - ( ) Una máquina de acumulador.
    - ( ) Una máquina con arquitectura R/R.
    - (x) Una máquina con arquitectura M/M.

Explicacion: Al admitir dos operandos, tenemos que se trata de una tipo `R/R` o `M/M`. Como al menos uno de los dos es una dirección de memoria (`M`), tenemos que no puede ser `R/R`.

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
    - ( ) Amplificadores operacionales.
    - ( ) Núcleos de ferrita.

73. En Linux IA-32, si gcc usa la instrucción `leave` se puede asegurar que en ese punto del programa:

    - ( ) Correspondería emitir la secuencia de salida `pop/ret`, pero `leave` hace lo mismo y ocupa menos espacio
    - (x) Ya no hay registros salva-invocado que recuperar.
    - ( ) Ya no hay variables locales que destruir.
    - ( ) Ya no se hacen llamadas anidadas y por tanto no hay parámetros que ocupen espacio en pila.

Explicacion: Al hacer el `leave`, vas a hacer mover el puntero de pila al antiguo valor de `rbp` y vas a hacer `pop %rbp`. Este es el primer valor que has introducido, por lo que ya has tenido que recuperar los otros registros salva invocados.

74. Usando el repertorio IA-32, para intercambiar el valor de 2 variables (por ejemplo `A: .int 1` y `B: .int 2`) se pueden usar:

    - ( ) Dos instrucciones `mov`.
    - ( ) Una instrucción `mov` y una instrucción `lea`.
    - ( ) 3 `mov`, no menos (se le llama "intercambio circular").
    - (x) 4 `mov`, no menos (debido a la arquitectura R/M).

Explicacion: Tienes que usar 4, ya que no puedes mover entre dos posiciones de memoria sin pasar por registros.

75. Respecto a registros base e índice en IA-32, la excepción es que:

    - ( ) `RBP` no puede ser registro base.
    - ( ) `RBP` no puede ser registro índice.
    - ( ) `RSP` no puede ser registro base.
    - (x) `RSP` no puede ser registro índice.

Explicacion: `RSP` es el puntero de pila. Puede ser usado como registro base, pero no como registro índice.

76. El registro `SP / ESP / RSP`:

    - ( ) Es un registro transparente al usuario y contiene la instrucción que se está ejecutando.
    - (x) Es un registro de propósito específico y contiene la dirección de la cima de la pila.
    - ( ) Es un registro transparente al usuario y contiene la dirección de memoria a la que se está accediendo.
    - ( ) Es un registro de propósito específico y contiene la dirección de la siguiente instrucción a ejecutar.

77. Diferencias gcc Linux IA-32/x86-64: marcar la respuesta falsa:

    - ( ) Los enteros largos (`long`) pasan de 32 a 64 bits.
    - ( ) Los punteros (`void*`) pasan de 32 a 64 bits.
    - (x) El tipo `double` pasa de 4 B a 8 B.
    - ( ) `long double` pasa de 10/12 B a 16 B.

78. ¿Cuál de los siguientes fragmentos de código deja en `%eax` un resultado distinto a los otros tres fragmentos?

    - (x) `mov $-1, %edx`<br>`sub %eax, %edx`<br>`mov %edx, %eax`
    - ( ) `not %eax`<br>`add $1, %eax`
    - ( ) `xor %edx, %edx`<br>`sub %eax, %edx`<br>`mov %edx, %eax`
    - ( ) `neg %eax`

Explicacion: `neg` hace una negación aritmética, por lo que aplica el complemento a 2. Esto es hacer el complemento a 1 (negar el valor, `not`), y sumarle 1. Por tanto, tenemos que la negunda y la cuarta opción son equivalentes, ambas guardan en `%eax` su opuesto, es decir `-%eax`. La tercera también hace lo mismo, ya que guarda en `eax` el valor `$0-%eax`. No obstante, la primera opción guarda `-1-%eax`, que es distinto.

79. Si `A` y `B` son dos enteros almacenados respectivamente en `%eax` y `%ebx`, ¿cuál de las siguientes implementaciones de:<br>`if(!A && !B){... then part ...}` es incorrecta?

    - ( ) ` or %ebx, %eax`<br>` jne not_true`<br>`  ...then part...`<br>`not_true:`<br>`    ...`
    - ( ) ` cmp $0, %eax`<br>`  jne not_true`<br>`  cmp $0, %ebx`<br>`  jne not_true`<br>`  ...then part...`<br>`not_true`<br>` ...`
    - (x) ` test %ebx, %eax`<br>`   jne not_true`<br>`  ...then part...`<br>`not_true`<br>` ...`
    - ( ) ` test %eax, %eax`<br>`  jne not_true`<br>`  test %ebx, %ebx`<br>`   jne not_true`<br>`  ...then part...`<br>`not_true`<br>` ...`

Explicacion: Para la primera, hemos de notar que `(!A && !B)=!(A || B)`. Si `A || B` no es nulo, entonces su valor booleano será `true`, por lo que al negarlo será `false`, por lo que habrá que ejecutar esa parte.
Explicacion: Para la segunda, si `%eax` no es nulo, entonces es `true`. Al negarlo será `false`, por lo que la puerta `AND` llevará a la parte del `false`. Equivalente ocurre con `%ebx`.
Explicacion: Para la tercera, es incorrecto. Ahí, el `if` que se está ejecutando es `if (A==B)`.
Explicacion: Para la cuarta, tenemos que es igual que en la segunda; ya que es la forma eficiente de comparar si un registro es nulo.

80. Dada la siguiente declaración en lenguaje C, una estructura de este tipo podría ocupar en un sistema Linux IA-32 o bien en uno x86- 64 un total de:<br><code>struct a {<br> int i;<br> double d;<br> char c;<br> short s;<br>};</code>

    - ( ) 18 B.
    - ( ) 20 B.
    - ( ) 22 B.
    - (x) 24 B.

Explicacion: Se podría pensar que, por el alineamiento, ocupa 32 B. No obstante, tras el `char` no hay 7 Bytes sin usar, ya que el `short` ocupa 4 B, por lo que puede comenzar en el offset `20`.

81. En un sistema Linux x86-64, ¿cuál de las siguientes expresiones es equivalente a la expresión C `(x[2] + 4)[3]`? Suponer que previamente se ha declarado `int **x`.

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
    segmentado sea ideal (señalar la respuesta falsa):
    
    - ( ) Registros de acoplo (coste de la segmentación).
    - ( ) Fragmentación desigual (duración desigual de etapas).
    - ( ) Riegos (hazards)
    - (x) Cola de instrucciones (precaptación).

85. La técnica de "adelanto de registros" (register forwarding) en un cauce segmentado se usa para limitar el impacto de los riesgos:

    - ( ) Estructurales.
    - ( ) Organizativos.
    - ( ) De control.
    - (x) (Por dependencias) de datos.

86. Las técnicas principales de E/S son (señalar la respuesta falsa):

    - ( ) DMA (por acceso directo).
    - ( ) E/S programada.
    - (x) E/S cableada (hardwired).
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

Explicacion: Al usar la cache, de velocidad bastante más rápida, se reduce el tiempo de ejecución.

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

91. Si almacenamos según el criterio little-endian la palabra de 32 bits `0xFACEB00C` a partir de la dirección `0xCAFEBABE`, el byte `0xCE` quedará almacenado en la dirección:

    - ( ) `0xCAFEBAC1`
    - (x) `0xCAFEBAC0`
    - ( ) `0xCAFEBABF`
    - ( ) `0xCAFEBABE`

Explicacion: Contando desde la izquierda, es el tercer byte. Por tanto, ocupará la tercera dirección de memoria.

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

Explicacion: Se debe a que si ambos se pueden representar en memoria, entonces un número menor en valor absoluto también se puede representar.

99. Después de ejecutar una instrucción de suma sobre dos números con signo de la que sabemos que no provocará overflow (los dos números son pequeños en valor absoluto), queremos comprobar si el resultado de la suma es menor que 0. ¿Qué flag necesita comprobar la instrucción de salto condicional equivalente a `if (resultado<0) then goto label`?

    - ( ) `CF`
    - ( ) `OF`
    - (x) `SF`
    - ( ) `ZF`

100.  La instrucción `cmovb %edx, %eax`:
    - (x) Copia en `%eax` el contenido de `%edx` si el indicador de acarreo es 1.
    - ( ) Copia el byte bajo de `%edx` en el byte bajo de `%eax`.
    - ( ) Copia en `%eax` el byte de memoria apuntado por la dirección contenida en `%edx`.
    - ( ) Copia en `%eax` el contenido de `%edx` si `%eax` es menor que `%edx`.

101. ¿Cuál de las siguientes afirmaciones sobre la instrucción `leave` es cierta?
    - ( ) Se ejecuta justo después de retornar de un procedimiento.
    - ( ) Equivale a `pop %rbp` seguida de `mov %rbp, %rsp`.
    - ( ) Equivale a `mov %rsp, %rbp` seguida de `pop %rbp`.
    - (x) No es obligatorio usarla. En su lugar puede realizarse una secuencia explícita de operaciones `mov` y `pop`.

Explicacion: `leave` equivale a `mov %rbp, %rsp`, `pop %rbp`, pero no es necesario usarla.

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

Explicacion: Vemos que la siguiente instrucción, `pushl`, está en la dirección `8048553`. por tanto, se introduce en la pila para poder volver a ella tras el `ret`.

105. En el fragmento de código:<br><code>804854e:e8 3d 06 00 00 call 8048b90 (main)<br>8048553:50 pushl %eax</code><br>La instrucción `call` suma al contador de programa la cantidad:
    - (x) `0000063d`
    - ( ) `08048553`
    - ( ) `0804854e`
    - ( ) `50`

Explicacion: En la fase de captación, `PC` se habrá situado en `8048553`, que es a priori la siguiente instrucción que iba a captar. No obstante, la operación `call` loha modificado, y la difereencia es `8048b90-8048553`, que corresponde a la primera opción.

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


124. El bus del sistema es 
	- ( ) el que conecta las distintas partes del sistema:UC,ALU,E/S,M
	- ( ) en un sistema con bus único, todo el bus salvo la parte relacionada con E/S (SATA, GPU, USB, Ethernet, etc) 
	- ( ) en un sistema con buses separados,el que conecta el sistema E/S con el resto 
	- (x) el que conecta CPU-M, ya sea un sistema con bus único o con múltiples buses 

125. Un sistema con direcciones de 8 bits utiliza una puerta NAND conectada a las líneas A7...A5 para atacar la entrada `CS#` (activa baja) de un módulo de memoria. En el mapa de memoria las siguientes posiciones corresponderán a dicho módulo 
	- ( ) 0x00 a 0x0f y 0x80 a 0x8f 
	- ( ) 0x00a0x1f 
	- ( ) 0x70 a 0x7f y 0xf0 a 0xff 
 	- (x) 0xe0a0xff 

126. La ecuación básica de rendimiento calcula 
	- (x) cuánto tiempo tarda en ejecutarse un programa concreto conociendo su número de instrucciones y el número de etapas (promedio) y la frecuencia del procesado 
	- ( ) cómo de mejor es un procesador frente a otro, conociendo las prestaciones de las respectivas UC, ALU, E/S y M 
	- ( ) el promedio de las ganancias obtenidas con una serie de programas de punto entero 
	- ( ) la media geométrica de los cocientes entre los tiempos de ejecución de una serie de programas predeterminados 

127. Por x86-64 se entiende la misma arquitectura de repertorio (ISA) que  
	- ( ) x86 
	- ( ) IA-32 
	- ( ) IA-64 
	- (x) AMD64

128. ¿Qué combinación de flags aritmético- lógicos corresponde al código de condición b (below)? 
	- (x) CF 
	- ( ) OF 
	- ( ) CFxorOF 
	- ( ) OFxorSF 

129. En los modos de direccionamiento del tipo Desplazamiento(Base,Indice,Factor Escala), puede usarse como 
	- (x) desplazamiento,cualquierconstantede1, 2 o 4 bytes (incluso el nombre de una variable,porsudirección) 
	- ( ) base, cualquiera de los 8 registros enteros salvo %esp 
	- ( ) índice,tambiéncualquierasalvo%ebp 
	- ( ) factor de escala, cualquier constante de 1, 2, 4 u 8 bytes 
    
130. La diferencia entre las instrucciones test y cmp consiste en que 
	- ( ) test realiza una operación and lógico, mientras que cmp realiza una resta
	- ( ) test modifica sólo los flags lógicos (ZF,SF) mientras que cmp modifica los aritmético-lógicos (ZF,SF,CF,OF) 
	- (x) ambas respuestas son correctas 
	- ( ) ambas respuestas son incorrectas 

131. Para traducir una construcción if-then- else de lenguaje C a lenguaje ensamblador, gcc utiliza generalmente 
	- ( ) un salto condicional,según la condición expresada en el código C 
	- (x) un salto condicional, según la condición opuesta a la del código C, y otro salto incondicional 
	- ( ) dos saltos condicionales (uno para la parte if y otro para la parte else)
	- ( ) dos saltos condicionales y dos saltos incondicionales 

132. Para traducir una construcción do-while de lenguaje C a lenguaje ensamblador, gcc utiliza generalmente
	- ( ) un salto condicional hacia adelante, según la misma condición que en lenguaje C  
	- (x) un salto condicional hacia atrás, según la misma condición que en lenguaje 
	- ( ) un salto condicional hacia adelante, según la condición opuesta a la de lenguaje C 
 	- ( ) un salto condicional hacia atrás, según la condición opuesta a la de lenguaje C 

133. Alguna de las siguientes señales no sirve de entrada a la unidad de control. ¿Cuál? 
	- ( ) señal de reloj(CLK) 
	- ( ) estado de la unidad de proceso (flags Z, S, C, O...) 
	- ( ) instrucción actual(bitsdelregistroIR) 
	- (x) contador de programa (bits del registro PC) 

134. Alguna de las siguientes señales no es salida de la unidad de control. ¿Cuál?
	 - ( ) señales decarga,habilitacióny/o desplazamiento de registros ( Load, Enable, ShiftL, ShiftR) 
	- ( ) códigos de selección en multiplexores, decodificadores, ALU, etc (00, 01, 10, 11...) 
	- ( ) señales de lectura y escritura en memoria (RD, WR) 
	- (x) dirección de la siguiente microinstrucción (bits del campo DIR o Memoria B de Wilkes) 

135. Alguna de las siguientes no es una operación básica de la unidad de control 
	- ( ) transferir un registro a otro 
	- ( ) (leer o escribir) un registro (de / a) memoria 
	- (x) (guardar recuperar)un registro(en/de) la pila 
	- ( ) realizar operación ALU y guardar resultado en registro

136. Tipos de riesgos que hemos estudiado en cauces segmentados (señalar la opción incorrecta) 
	- ( ) riesgos estructurales 
	- ( ) riesgos de (dependencia de) datos 
	- ( ) riesgos control 
	- (x) riesgos de transferencia 

137. ¿Cuál de los siguientes modos de direccionamiento es menos preferible para un procesador con segmentación de cauce? 
	- ( ) registro 
	- (x) directo 
	- ( ) indirectoatravésderegistro 
	- ( ) indexado (o relativo a base, o base+índice) 

138. La ganancia en velocidad ideal de un cauce de K etapas de igual duración T ejecutando un programa de N instrucciones es 
	- ( ) S=KN/(K-N+1) 
	- ( ) S = NKT/(N-K+1)T 
	- (x) S=KN/(K+N-1) 
 	- ( ) S = NT/(N+K-1)T 

139. Respecto al salto retardado y al salto anulante, ¿cuál permite que se ejecute la siguiente instrucción, y cuál no? 
	- ( ) el retardado ejecuta la siguiente instrucción (con el correspondiente retraso), el anulante no la ejecuta (de hecho la anula) 
	- ( ) el retardado la ejecuta sólo si se cumple la condición de salto, el anulante sólo si no se cumple 
	- ( )el retardado la ejecuta sólo si no se cumple la condición de salto, el anulante no la ejecuta nunca 
	- (x) el retardado la ejecuta siempre, el anulante la ejecuta sólo si se cumple la condición de salto 

140. Respecto a las técnicas de direccionamiento por selección lineal, decodificación centralizada y distribuida
	- ( ) todas ellas impiden que haya cortocircuito en el bus de datos  
	- ( ) todas ellas impiden que haya cortocircuito en el bus de direcciones  
	- (x) la selección lineal permitiría escribir un mismo dato a varios puertos E/S 
	- ( ) usando decodificación centralizada es más fácil realizar expansiones al sistema de E/S 

141. Ventajas de la E/S independiente (separada, aislada) (señalar la opción incorrecta) 
	- (x) diseño del procesador más sencillo(E/S mapeada añade complejidad al diseño) 
	- ( ) protección de E/S más fácil (E/S mapeada añade dificultad a la protección de E/S) 
	- ( ) mayor aprovechamiento del espacio de memoria (E/S mapeada resta espacio a la memoria) 
	- ( ) decodificación de memoria más elegante, limpia, sencilla (E/S mapeada añade complejidad a la decodificación) 

142. Parecidos y diferencias entre los métodos de E/S (señalar la opción incorrecta) 
	- ( ) la consulta del estado del dispositivo por parte de la CPU se suele/puede hacer con E/S programada y con E/S por IRQ 
	- ( ) se suele avisar a la CPU (con una IRQ) de que debe realizar alguna tarea, tanto en E/S por IRQ como en E/S por DMA 
	- (x) sólo E/S por DMA libera a la CPU de realizar la consulta de estado del dispositivo 
	- ( ) sólo E/S por DMA libera a la CPU de realizar la transferencia de los datos de E/S 

143. Tipos de interrupción que suelen contemplar las CPUs comerciales actuales (señalar la opción incorrecta) 
	- ( ) internas (excepciones o traps): generadas internamente por la CPU para indicar una condición que requiere atención (división por cero, codop inválido, etc)
	- ( ) externas (IRQs hardware): generadas por un dispositivo externo a la CPU, activan la línea INTR# (o equivalente) 
	- ( ) software:generadas al ejecutar la instrucción INT (o equivalente) 
	- (x) firmware (faults): generadas por el microcódigo de la CPU ( segmentation fault, page fault, etc) 

144. Técnicas que se pueden usar para determinar la causa de una interrupción (señalar la opción incorrecta) 
	- ( ) múltiples líneas de interrupción INT1#, INT2#... 
	- (x) línea de reconocimiento INTA# 
	- ( ) consulta de estado,o polling 
	- ( ) interrupciones vectorizadas 

145. Respecto a salvaguardar los registros de la CPU al inicio de una rutina de servicio de interrupción (ISR) 
	- ( ) no es necesario salvar ninguno más,si el contador de programa y los flags de estado ya los salva la propia CPU como parte del mecanismo de interrupción 
	- (x) se deben guardar los registros que se modifiquen en la propia ISR. Eso es posible hacerlo porque el propio programador de la ISR conoce qué registros va a modificar 
	- ( ) se deben guardar los registros salva- invocado (p.ej. EBX, ESI, EDI en el caso de una CPU IA-32), los registros salva- invocante ya los guarda el programa interrumpido 
	- ( ) se deben guardar todos los registros, para restaurarlos a la salida y así garantizar que el programa interrumpido no sufre ninguna modificación (salvo el inevitable retraso temporal) debido a la interrupción 

146. En EC podemos usar la palabra directo para referirnos a... (señalar la opción incorrecta) 
	- (x) dispositivo de almacenamiento secuencial directo (DASD) 
	- ( ) cache con correspondencia directa 
	- ( ) acceso directo a memoria 
	- ( ) modo de direccionamiento directo

147. Variación de los parámetros de los distintos niveles en una jerarquía de memoria (señalar la opción incorrecta) 
	- (x) unidad de transferencia: xi xi+1 
	- ( ) ancho de banda: bi bi+1 
	- ( ) tamaño del nivel: si si+1 
	- ( ) tiempo de acceso: ti ti+1 

148. Las técnicas write-through y write-back están relacionadas con 
	- (x) coherencia cache 
	- ( ) métodos de E/S 
 	- ( ) arbitraje de buses 
	- ( ) etapas de la unidad de control 

149. Para diseñar una memoria con ancho de palabra k·m (y mismo no palabras que los módulos) a partir de módulos con ancho de palabra m, se utilizan k módulos 
	- ( ) repartiendo las líneas de datos entre los k módulos: el primero se conecta a D0...Dk-1, el segundo a Dk...D2k-1, etc 
	- ( ) repartiendo las líneas de dirección: el 1o se conecta a A0...Ak-1, el 2o a Ak...A2k-1, etc 
	- (x) repartiendolíneasdatos:el1oseconecta a D0...Dm-1, el 2o a Dm...D2m-1, etc 
	- ( ) d.repartiendo líneas dirección: el 1o a A0...Am-1, el 2o a Am...A2m-1, etc 

150. En un sistema con direcciones de 32bits, memoria de bytes, cache de 1MB asociativa por conjuntos de 4 vías y líneas de 64B, el campo etiqueta en el formato de dirección cache es de 
	- ( ) 16bits 
	- (x) 15bits 
	- ( ) 12bits
	- ( ) 10bits 

151. ¿Por qué se impusieron las arquitecturas de registros de propósito general a las arquitecturas basadas en pila? 
	- ( ) Porque no se puede programar una arquitectura de pila en un lenguaje de alto nivel. 
	- (x) Porque las basadas en registros son capaces de lograr un mejor rendimiento cuando se asignan variables a registros. 
	- ( ) Porque la memoria es más cara que los registros. 
	- ( ) Porque las basadas en registros permiten reducir el tamaño del programa 

152. ¿Cuál de las siguientes afirmaciones es incorrecta? 
	- ( ) El direccionamiento indexado es útil para manejo de vectores. 
	- (x) El direccionamiento indirecto indica la dirección del operando. 
	- ( ) En el direccionamiento implícito no se indica la ubicación del operando 
	- ( ) En el direccionamiento inmediato el dato se encuentra en la propia instrucción 

153. ¿Cuál de las siguientes afirmaciones sobre el direccionamiento absoluto es falsa? 
	- ( ) La instrucción contiene la dirección de memoria en la que se encuentra el objeto. 
	- ( ) El objeto está en una posición de la memoria 
	- ( ) El rango de posiciones direccionables queda limitado por el tamaño del campo de direccionamiento. 
	- (x) El tamaño del operando direccionado queda limitado por el no de bits del campo de direccionamiento. 

154. ¿Cuál es la diferencia entre los desplazamientos a la derecha lógico y aritmético? 
	- ( ) El lógico inserta siempre ceros en el bit más a la derecha 
	- ( ) El aritmético inserta en el bit más a la derecha una copia del bit de signo 
	- (x) Insertan de forma distinta el bit más a la izquierda
	- ( ) Ninguna, la diferencia es entre los desplazamientos a la izquierda 

155. La instrucción seta %al (seta significa set if above): 
	- (x) Pone AL a 1 si CF=0 y ZF=0 
	- ( ) Pone AL a 1 si CF=0 o ZF=0 
	- ( ) Pone AL a 1 si CF=1 y ZF=0 
	- ( ) Pone AL a 1 si CF=1 o ZF=1 

156. Los arrays bidimensionales en lenguaje C se almacenan en orden... 
	- ( ) "mayor-de-columna" (column-major) 
	- (x) "mayor-de-fila" (row-major) 
	- ( ) "de mayor a menor" (major-to-minor) 
	- ( ) "de fila a columna" (file-to-column) 

157. ¿Cuál sería el "equivalente x86-64" del "pseudo-código C" rcx = ((int*)rax)[rcx]? 
	- (x) mov (%rax,%rcx,4),%rcx 
	- ( ) lea (%rax,%rcx,4),%rcx 
	- ( ) lea (%rax,4,%rcx),%rcx 
	- ( ) mov (%rax,4,%rcx),%rcx 

158. El direccionamiento directo a memoria utiliza 
	- ( ) un registro. 
	- ( ) dos desplazamientos contenidos en la propia instrucción. 
	- ( ) un registro y un desplazamiento contenidos en la propia instrucción.
	- (x) un desplazamiento. 

159. ¿Cuál de las siguientes afirmaciones es falsa? 
	- ( ) Los programas necesitan una forma de pasar parámetros a las subrutinas y de recibir las salidas de vuelta.
	- ( ) Las subrutinas necesitan ser capaces de reservar espacio en memoria para las variables locales sin sobrescribir ningún dato usado por el programa que hace la llamada 
	- (x) Las subrutinas necesitan recibir parámetros desde el programa que hace la llamada que indiquen qué registros pueden alterar y cuáles no. 
	- ( ) Las subrutinas necesitan algún modo de saber desde dónde han sido llamadas para poder volver al programa que realizó la llamada cuando se completa la subrutina 

160. Respecto a la segmentación: 
	- ( ) Cuanto más parecidos sean el tiempo de ejecución de una instrucción sin segmentar y el tiempo de una etapa en el procesador segmentado, mayor será la ganancia máxima que se puede obtener. 
	- ( ) Cuando el número de instrucciones ejecutadas tiende al número de etapas de un procesador segmentado, la ganancia máxima que se puede obtener tiende a infinito. 
	- (x) Cuanto mayor sea la relación entre el tiempo de ejecución de una instrucción sin segmentar y el tiempo de una etapa en el procesador segmentado, mayor será la ganancia máxima que se puede obtener 
	- ( ) Cuando el número de instrucciones ejecutadas en un procesador segmentado crece, la ganancia máxima que se puede obtener tiende a 1 

161. Respecto a la segmentación, ¿cuál de las siguientes afirmaciones es falsa? 
	 - ( ) La técnica de register forwarding habilita una serie de caminos (buses) que se añaden al cauce para permitir que los resultados de una etapa pasen como entradas a la etapa donde son necesarias. 
	- ( ) La reorganización del código y la introducción de instrucciones nop permite evitar dependencias de datos. 
	- (x) Retrasar la fase de decisión saltar/no saltar de las instrucciones de salto condicional contribuye a mejorar el rendimiento del procesador. 
	- ( ) Cuantas más etapas tenga un cauce, más instrucciones se estarán ejecutando en distintas fases y más posibilidades se presentan de que existan riesgos entre ellas.

Explicacion: <!-- 162 Repetida.--> 

163. La predicción de saltos está relacionada con... 
	- ( ) Los riesgos estructurales (intenta evitar el efecto de un fallo de cache) 
	- ( ) Los riesgos de (dependencia de) datos (intenta que el dato esté disponible anticipadamente) 
	- (x) Los riesgos de control (intenta determinar de antemano el flujo de control) 
	- ( ) Los riesgos de transferencia (intenta agrupar las posibles transferencias de un conjunto de instrucciones) 

164. ¿Cuál de los siguientes modos de direccionamiento es *menos* preferible para un procesador con segmentación de cauce? 
	- ( ) Registro 
	- (x) Indirecto a través de memoria 
	- ( ) Indirecto a través de registro 
	- ( ) Indexado (o relativo a base, o base+índice) 

165. Si se dice que en un sistema computador cada dirección especifica uno o dos puertos de E/S, se refiere a que: 
	- ( ) La misma dirección (por ejemplo 0x0210) puede ser una posición de memoria o un puerto de E/S, según IO/M# 
	- ( ) La misma dirección puede usarse para transferir un byte o una palabra de mayor tamaño (ese byte y el siguiente) 
	- (x) Un puerto será de sólo lectura, otro de sólo escritura, y ambos se decodifican en la misma dirección 
	- ( ) La pregunta es capciosa, una dirección puede especificar un puerto, no dos 

166. Respecto a si un computador dispone de E/S independiente (separada) o usa E/S mapeada a memoria:
	- ( ) Si el encapsulado (chip) del procesador tiene patilla (pin) IO/M# (o patillas equivalentes), eso evidencia que el computador usa E/S mapeada a memoria 
	- (x) Si el repertorio del procesador tiene instrucciones del tipo IN y OUT, es que el computador dispone de E/S separada 
	- ( ) Si el encapsulado del procesador no dispone de patilla IO/M# (ni equivalentes), el computador sólo dispone de E/S separada 
	- ( ) Si el repertorio del procesador tiene instrucciones del tipo LOAD y STORE, el computador sólo dispone de E/S mapeada a memoria 

167. Supongamos dos procesadores con bus de direcciones con idéntico número de líneas. Si uno de ellos emplea E/S mapeada en memoria y el otro E/S independiente, ¿cuál podrá acceder a una mayor cantidad de memoria? 
	- (x) El que tiene E/S independiente. 
	- ( ) El que tiene E/S mapeada en memoria 
	- ( ) Depende del tamaño del bus de direcciones. 
	- ( ) Ambos podrán acceder a la misma cantidad de memoria.

168. ¿Cuál de las siguientes afirmaciones es incorrecta? 
	- ( ) La consulta del estado del dispositivo por parte de la CPU se suele hacer con E/S programada (salvo con dispositivos que siempre están listos para transferir) y con E/S por IRQ (cuando se usa polling para determinar el origen de la IRQ) 
	- ( ) Se suele avisar a la CPU (mediante una IRQ) de que debe realizar alguna tarea, tanto en E/S por IRQ (obligatoriamente, la tarea es la transferencia) como en E/S por DMA (optativamente, el controlador DMA puede avisar de que acabó) 
	- (x) Sólo E/S por DMA libera a la CPU de realizar la consulta de estado del dispositivo de E/S 
	- ( ) Sólo E/S por DMA libera a la CPU de realizar la transferencia de los datos de E/S 

169. El fragmento de código:<br>
<code>poll: in a, 0x20 <br>cmp a, $0 <br>jnz poll <br>load a, 0x11 <br>out 0x21, a <br></code> corresponde a: 
	- ( ) E/S programada sin consulta de estado 
	- (x) E/S programada con consulta de estado 
	- ( ) E/S por interrupciones 
	- ( ) E/S por DMA 

170. Un procesador con E/S en el mapa de memoria tiene un bus de direcciones de 10 líneas y uno de datos de 8. El mapa de memoria tiene 512 posiciones para instrucciones, 256 para datos y 256 para E/S, en ese orden. Los rangos de direcciones para esas tres zonas serán: 
	- (x) 000a1FF,200a2FFy300a3FF. 
	- ( ) 000a5FF,600a7FFy800a9FF. 
	- ( ) 000 a 7FF, 800 a BFF y C00 a FFF. 
	- ( ) 000a9FF,A00aCFFyD00aFFF. 

171. El instrumento GIADA de la sonda espacial ROSETTA (diseñado en Granada) está basado en un microprocesador 8086 y el siguiente mapa de memoria: 
RAM volátil: 00000 - 0FFFF 
RAM no volátil: 10000 - 1FFFF 
ROM: F0000 - FFFFF 
¿Cuál es el tamaño total de la memoria? 
	- ( ) 48KB 
	- (x) 192KB 
	- ( ) 2MB
	- ( ) 3MB 

172. Una memoria que está estructurada en palabras de 8 bits tiene una capacidad de 64 Kbits. ¿Cuántas líneas de dirección tiene dicha memoria? 
	- ( ) 8 
	- ( ) 12 
	- (x) 13 
	- ( ) 24 

173. ¿Cuál de los siguientes es el ejemplo más acertado de localidad espacial? 
	- (x) Referenciar elementos de un array sucesivamente 
	- ( ) Iterar repetidamente el cuerpo de un bucle 
	- ( ) Reservar dinámicamente (malloc) espacio para una estructura o union 
	- ( ) Referenciar continuamente la misma variable local 

174. ¿Cuál de las siguientes es una idea fundamental de la jerarquía de memoria? 
	- ( ) Crear una gran cantidad de almacenamiento que sea caro y rápido
    - ( ) Crear una pequeña cantidad de almacenamiento que sea caro y lento 
	- (x) Que dispositivos más pequeños y rápidos sirvan de cache para dispositivos más grandes y lentos 
	- ( ) Que dispositivos más grandes y lentos sirvan de cache para dispositivos más pequeños y rápidos 

175. ¿Cuál de las siguientes afirmaciones acerca de las memorias SRAM es falsa? 
	- ( ) Los datos almacenados se mantienen por un tiempo indefinido mientras se mantenga la alimentación. 
	- ( ) El número de transistores necesario para implementar cada celda es mayor que en las memorias RAM dinámicas 
	- (x) Las operaciones de lectura son destructivas 
	- ( ) Son más veloces que las memorias RAM dinámicas

176. Se dispone de un circuito integrado que actúa como módulo básico de memoria de 8K × 4. ¿Qué circuitos necesitamos para construir una memoria de 17K × 8? 
	- ( ) 2 módulos de memoria 
	- ( ) 2 módulos de memoria y un decodificador. 
	- ( ) 4 módulos de memoria.
	- (x) 4 módulos de memoria y un inversor. 

177. En la cache L1 de instrucciones, la tasa de fallos: 
	- ( ) Siempre tiende a crecer si el tamaño total de L1 crece. 
	- (x) Siempre tiende a disminuir si el tamaño total de L1 crece. 
	- ( ) Siempre tiende a crecer si el número de vías crece. 
	- ( ) Siempre tiende a disminuir si el número de vías disminuye. 

178. Supongamos que una memoria cache de tamaño 512B con política LRU está inicialmente vacía. Si para la siguiente secuencia de direcciones enviadas a la cache: 0, 2, 4, 8, 16, 32, la tasa de acierto es 0.33, ¿cuál es entonces el tamaño de bloque de la cache? 
	- ( ) 4B 
	- (x) 8B 
	- ( ) 16B 
	- ( ) Ninguno de los anteriores 

179. Un sistema tiene una cache asociativa por conjuntos de 2-vias con 16 conjuntos y líneas de 64. ¿A qué conjunto le corresponde el byte con dirección 0xdeadbeef? 
	- ( ) 7 
	- (x) 11 
	- ( ) 13 
	- ( ) 14

170. ¿Cuál es el tamaño de la etiqueta de caché en un ordenador capaz de direccionar por bytes 1 MB de memoria principal y 32 KB de memoria caché y correspondencia asociativa por conjuntos con 32 bytes por línea y 16 líneas por conjunto? 
	- ( ) 6 bits 
	- ( ) 7 bits 
	- ( ) 8 bits 
	- (x) 9 bits 

181. En el direccionamiento inmediato el operando reside en: 
	- ( ) en un registro del procesador 
	- (x) en la instrucción tras el código de operación 
	- ( ) en memoria, en la dirección indicada 
	- ( ) en la pila 

182. Una instrucción máquina del tipo "Add M,R" podría formar parte del repertorio de 
	- ( ) una máquina pila 
	- ( ) una máquina de acumulador 
	- ( ) una máquina con arquitectura R/R 
	- (x) una máquina con arquitectura M/M

183. La traducción a ASM de una función C con prototipo `void fun(<tipo> arg1, <tipo> arg2)`; por parte de gcc empieza con el siguiente texto:<br>
<code>fun: <br>movl (%rdi), %eax <br>movl (%rsi), %edx ... </code>
¿Cuál es el posible <tipo> mencionado en el prototipo? 
	- ( ) `long *`
	- (x) `unsigned int *`
	- ( ) `short *`
	- ( ) `unsigned char *` 

184. Se puede describir paso a paso la ejecución de la instrucción add (%rbx, %rdx,4), %eax; de la siguiente manera (marcar la opción FALSA): 
	- ( ) primero: se calcula la dirección efectiva EA=RBX+RDX*4a 
	- (x) segundo: se leen ocho bytes a partir de dicha dirección de memoria 
	- ( ) tercero: se yuxtaponen los bytes leídos de forma que el de dirección más baja ("el primero leído") sea el menos significativo y el de dirección más alta ("el último leído") sea el más significativo 
	- ( ) cuarto: se suma el valor obtenido con el registro EAX 
185. ¿Qué valor contendrá el registro rdx tras ejecutar las dos instrucciones siguientes? 
movq $-1, %rdx 
movl $1, %edx 
	- ( ) 0xFFFF FFFF FFFF 0001 
	- ( ) 0xFFFF FFFF 0000 0001 
	- ( ) 0xFFFF 0000 0000 0001 
	- (x) 0x0000 0000 0000 0001
186. En el fragmento de código <br><code>400544:e807000000 callq 400550 f <br> 400549:488903 mov %rax,(%rbx) </code><br> la instrucción `call` suma al contador de programa la cantidad: 
	- (x) 0x00000007 
	- ( ) 0x00400549 
	- ( ) 0x400544 
	- ( ) 0x48 

187. Una función C declarada como `int get_var_digit(size_t index, size_t digit)` genera como código ensamblador <br><code> movq var(,%rdi,8), %rax <br> movl (%rax,%rsi,4), %eax <br> ret </code><br>
Se puede adivinar que: 
	- ( ) var es un array multi-nivel (punteros a enteros) de cuatro filas  
	- (x) var es un array multi-nivel pero no se pueden adivinar las dimensiones  
	- ( ) var es un array bidimensional de enteros, con ocho columnas  
	- ( ) var es un array bidimensional de enteros, con cinco columnas 

188. En el contexto de microprogramación, el control residual... 
	- ( ) intenta disminuir la cantidad de "bits residuales", usando las técnicas de codificación y/o solapamiento de campos, como opuestas a la microprogramación directa o "inmediata". 
	- ( ) se refiere a que cuanto más codificación y/o solapamiento se use, menos capacidad para expresar paralelismo se tiene, siendo ese menor control un "residuo" o consecuencia no deseada de dichas técnicas no "inmediatas" 
	- ( ) clasifica las microinstrucciones del microcódigo según formen parte de microprogramas ("microinstr. inmediatas") o no ("microinstr. residuales") 
	- (x) consiste en almacenar señales de control en un "registro de control residual" para usarlas en ciclos posteriores, a diferencia del "control inmediato", en donde los bits se utilizan inmediatamente 
189. Suponer que un procesador ideal que ejecuta cada instrucción en `T` segundos se segmenta en cuatro etapas ideales de duración `T/4`. ¿Cuál razonamiento es correcto? 
	- ( ) Se espera una reducción de prestaciones porque además de ejecutar las instrucciones hay que segmentarlas (coste de la segmentación) 
	- ( ) Se espera una reducción de prestaciones porque la duración del ciclo de reloj vendrá impuesta por la etapa más lenta 
	- ( ) Se espera un aumento de prestaciones debido al efecto de los riesgos (hazards) sobre el avance de las instrucciones en el cauce 
	- (x) Se espera un aumento de prestaciones debido a que las cuatro etapas solapan su funcionamiento, con una aceleración ideal de 4x 
190. Un salto condicional del tipo "delayed branch", o salto retardado, ejecuta la(s) instrucción(es) siguiente(s)... 
	- ( ) sólo si el salto se produce (las ignora si NO se produce), de manera que instrucción(es) en el destino del salto podrían adelantarse tras la propia instrucción de salto 
	- ( ) sólo si el salto NO se produce (las ignora si se produce), de manera que instrucción(es) en el destino del salto podrían adelantarse tras la propia instrucción de salto 
	- (x) siempre, de manera que instrucción(es) anterior(es) al salto podrían colocarse tras la propia instrucción de salto
	- ( ) nunca, de manera que instrucción(es) anterior(es) al salto no podrían colocarse tras la propia instrucción de salto 
191. Un computador con 20 líneas de dirección y memoria de bytes tiene 640KB de RAM, 128KB de ROM, y utiliza E/S mapeada en memoria. ¿Cuál es el número máximo de periféricos que pueden conectarse, si cada uno de ellos utiliza 32 direcciones? 
	- ( ) \\(2^{10}\\)
	- ( ) \\(2^{11}\\)
	- ( ) \\(2^{12}\\) 
	- (x) \\(2^{13}\\) 
192. La consulta de estado que se puede llevar a cabo en una operación de salida mediante E/S programada sirve para… 
	- ( ) consultar si el dispositivo tiene algún dato de salida disponible 
	- (x) consultar si el dispositivo está aún ocupado, por ejemplo con alguna operación de salida 	anterior 
	- ( ) consultar si el dispositivo funciona correctamente 
	- ( ) ninguna de las respuestas anteriores es correcta 
193. ¿Qué conjunto de componentes permite construir una memoria 256Mx32? (sin que sobren componentes) 
	- ( ) 16 chips 64Mx4 
	- (x) 32 chips 64Mx4 (256*32==64*4*32) 
	- ( ) 16 chips 64Mx16 
	- ( ) Ninguna de las anteriores 
194. ¿Cuántas líneas de dirección (patillas) son necesarias para direccionar un chip de memoria DRAM de 256K x 4? 
	- (x) 9 
	- ( ) 13 
	- ( ) 19
	- ( ) 22 
195. ¿Qué arquitectura es típica en procesadores RISC? 
	- (x) registro-registro 
	- ( ) registro-memoria 
	- ( ) memoria-registro 
	- ( ) memoria-memoria 
196. ¿Cuál de las siguientes características es posterior a la segunda generación de computadores? 
	- ( ) Memoria de núcleos de ferrita 
	- ( ) Compilador 
	- (x) Memoria cache 
	- ( ) Lenguaje ensamblador 
197. Si el registro rax contiene x, la sentencia en C x &= 0x1; se traducirá a ensamblador como: 
	- (x) andq $1, %rax 
	- ( ) orq $0x1, %rax 
	- ( ) shrq %rax 
	- ( ) sarq %rax 
198. Para crear espacio en la pila para variables locales sin inicializar suele realizarse la siguiente operación 
	- ( ) Restar una cantidad positiva a `rbp`. 
	- ( ) Sumar una cantidad positiva a `rbp`. 
	- (x) Restar una cantidad positiva a `rsp`. 
	- ( ) Sumar una cantidad positiva a `rsp`.

199. Si la estructura struct a ocupa un espacio de 26 bytes en memoria, ¿cuántos bytes ocupa la siguiente estructura struct b cuando se compila en 64 bits? <br><code>struct b{<br> struct a a1; <br> int i; <br> struct a a2; <br> }; </code><br>
	- ( ) 24 
	- ( ) 58 
	- (x) 60 (entero ocupa 8) 
	- ( ) 64 
200. En la secuencia de programa siguiente:<br>
<code> 628: e8 cd ff ff ff 	callq	5fa suma   <br> 62d: 48 83 c4 20 	add 	$0x20, %rsp </code> <br>
¿Cuál es el valor que introduce en la pila la instrucción `callq`? 
	- ( ) `0xffffffcd` 
	- ( ) `0x5fa` 
	- ( ) `0x628` 
	- (x) `0x62d` 

201. Un archivo `.o` que contiene código objeto reubicable: 
	- (x) Contiene instrucciones máquina binarias. 
	- ( ) Contiene instrucciones máquina y directivas en ensamblador.  
	- ( ) Puede ejecutarse directamente. 
	- ( ) Contiene las direcciones definitivas de las variables globales. 

202. ¿Cuál de las siguientes sentencias sobre la unidad de control es FALSA? 
	- ( ) Cuanto más horizontal es la microprogramación, más largas son las microinstrucciones 
	- ( ) Debido al pequeño número de operaciones simples, la sección de control de un procesador RISC puede ser cableada en lugar de microprogramada
	- (x) El programador de lenguaje ensamblador necesita conocer la microarquitectura del ordenador 
	- ( ) Es posible realizar el diseño físico de una unidad de control cableada de manera semiautomática 

203. En una unidad de control microprogramada con formato de microinstrucciones vertical, un subcampo que deba especificar 16 señales de control, codificadas de tal forma que pueda activarse sólo una o ninguna señal de control, habrá de tener una anchura mínima de: 
	- ( ) 4 bits 
	- (x) 5 bits (2^4+1bit de control) 
	- ( ) 16 bits 
	- ( ) 17 bits 

204. La técnica de "adelanto de registros" (register forwarding) en un cauce segmentado se usa para limitar el impacto de los riesgos... 
	- ( ) estructurales 
	- ( ) organizativos 
	- ( ) de control 
	- (x) de datos 

205. Un sistema no segmentado tarda 10 ns en procesar una tarea. La misma tarea puede ser procesada en un cauce (pipeline) de 4 segmentos con un ciclo de reloj de 4 ns. Cuando se procesan muchas tareas, la ganancia máxima de velocidad que se obtiene se acerca a: 
	- ( ) 10 
	- ( ) 4 
	- ( ) 40 
	- (x) 2,5(10/4) 

206. ¿Cuál de las siguientes afirmaciones es cierta? 
	- ( ) La E/S en memoria emplea la patilla IO/M#.
	- (x) En E/S independiente, las instrucciones de acceso a memoria suelen ser más largas que las de E/S. 
	- ( ) La E/S en memoria facilita la protección. 
	- ( ) En la E/S en memoria las instrucciones de E/S son fácilmente reconocibles.

208. ¿Cuál de las siguientes afirmaciones sobre la jerarquía de memoria es cierta?  
	- (x) Para aumentar la eficiencia se transfieren bloques completos.  
	- ( ) Toda la información que el procesador necesita está en el nivel 1. 
	- ( ) Si una palabra no se encuentra en el tercer nivel entonces se busca en el segundo nivel. 
	- ( ) A medida que nos alejamos del procesador, el tamaño de memoria disminuye. 

209. ¿Cuántas líneas de dirección (patillas) son necesarias para direccionar un chip de memoria DRAM de 4096 x 4? 
	- (x) 6 \\(2^{12}\\) 
	- ( ) 10 
	- ( ) 11 
	- ( ) 12



210. ¿Cuál de las siguientes instrucciones máquina copia en `EAX` la dirección efectiva resultante de la operación EDX*4 + EBX?
    - ( ) `leal 4(%edx, %edx), %eax`
    - (x) `leal (%ebx, %edx, 4), %eax`
    - ( ) `movl 4(%edx, %edx), %eax`
    - ( ) `movl (%ebx, %edx, 4), %eax`

211. ¿Cuál de las siguientes instrucciones máquina copia en `EAX` el entero almacenado en la posición de memoria cuya dirección efectiva es el resultado de la operación `EDX*4 + EBX`?
    - ( ) `leal 4(%edx, %edx), %eax`
    - ( ) `leal (%ebx, %edx, 4), %eax`
    - ( ) `movl 4(%edx, %edx), %eax`
    - (x) `movl (%ebx, %edx, 4), %eax`

212. Los switches `–m elf_i386` y `–m elf_x86_64` para trabajar en 32 bits / 64 bits corresponden a la herramienta...
    - ( ) `gcc`
    - ( ) `as`
    - (x) `ld`
    - ( ) `nm`

213. Si `ECX` vale 0, la instrucción `adc $0,%ecx`
    - ( ) Pone `CF=1`
    - (x) Pone `CF=0`
    - ( ) Cambia `CF`
    - ( ) No cambia `CF`

214. Dada la siguiente definición de datos:<br>
     <code>
     lista:	.int	0x10000000, 0x50000000, <br>
             0x10000000, 0x20000000  <br>
     longlista:	.int	(.-lista)/4			<br>
     resultado:	.quad	0x123456789ABCDEF	<br>
     formato:	.ascii	"suma=%llu=%llx hex\n\0"	<br>
     </code><br>
    La instrucción para copiar la dirección de memoria donde comienza lista en el registro EBX es:
    - ( ) `movl lista, %ebx`
    - (x) `movl $lista, %ebx`
    - ( ) `movl (lista), %ebx`
    - ( ) `movl $lista, (%ebx)`.

215. Dada la siguiente definición de datos:<br>
     <code>
     lista:	.int	0x10000000, 0x50000000, <br>
             0x10000000, 0x20000000  <br>
     longlista:	.int	(.-lista)/4			<br>
     resultado:	.quad	0x123456789ABCDEF	<br>
     formato:	.ascii	"suma=%llu=%llx hex\n\0"	<br>
     </code><br> La instrucción `movl longlista, %ecx` copia el siguiente valor:
    - (x) 4
    - ( ) 8
    - ( ) 16
    - ( ) 32	

216. Dada la siguiente definición de datos:<br>
     <code>
     lista:	.int	0x10000000, 0x50000000, <br>
             0x10000000, 0x20000000  <br>
     longlista:	.int	(.-lista)/4			<br>
     resultado:	.quad	0x123456789ABCDEF	<br>
     formato:	.ascii	"suma=%llu=%llx hex\n\0"	<br>
     </code><br> 
     y suponiendo que hemos llamado a una función *suma* que devuelve un número de 64 bits en la pareja 
     `EDX:EAX`, las instrucciones que copian ese número en *resultado*
     son:
     - (x) <code> movl %eax, resultado <br> movl %edx, resultado+4</code>
     - ( ) <code>movl (%eax), resultado <br>movl (%edx), resultado+4</code>
     - ( ) <code>movl %eax, resultado+4 <br>movl %edx, resultado</code>
     - ( ) <code>movl (%eax), resultado+4</code>

217. Dada la siguiente definición de datos:<br>
     <code>
     lista:	.int	0x10000000, 0x50000000, <br>
             0x10000000, 0x20000000  <br>
     longlista:	.int	(.-lista)/4			<br>
     resultado:	.quad	0x123456789ABCDEF	<br>
     formato:	.ascii	"suma=%llu=%llx hex\n\0"	<br>
     </code><br>
     La llamada correcta a `printf` será:
    - ( ) <code> push resultado+4    <br>               push resultado      <br>               push $formato       <br>               call printf         <br>               add $12, %esp       <br> </code>
    - (x) <code> push resultado+4    <br>                 push resultado      <br>                 push resultado+4    <br>                 push resultado      <br>                 push $formato       <br>                 call printf         <br>                 add $20, %esp       <br> </code>
    - ( ) <code> push resultado      <br>                 push resultado+4    <br>                 push $formato       <br>                 call printf <br>add $12, %esp <br> </code>
    - ( ) <code> push resultado       <br>                 push resultado+4     <br>                  push resultado       <br>                 push resultado+4     <br>                 push $formato        <br>                 call printf          <br>                 add $20,%esp           <br> </code>

218. En la práctica "media" se pide sumar una lista de enteros **con** signo de 32 bits en una plataforma de 32 bits sin perder precisión, esto es, evitando overflow. ¿Cuál es el menor valor positivo que repetido en los **dos** primeros elementos de la lista causaría overflow con 32 bits al realizar la suma de **esos dos** primeros elementos de la lista? (Entendemos que la lista contiene 4 números, y se va a realizar la suma de la lista 4 veces).
    - ( ) `0x0400 0000`
    - ( ) `0x0800 0000`
    - (x) `0x4000 0000`
    - ( ) `0x8000 0000`

219. ¿Cuál de las siguientes afirmaciones es cierta respecto al lenguaje C?
     - (x) En lenguaje C, al llamar a una subrutina o función se introducen los parámetros en la pila y después se realiza una llamada a la subrutina
     - ( ) Los parámetros se introducen en la pila en el orden en el que aparecen en la llamada de C, es decir, empezando por el primero y acabando por el último
     - ( )  Antes de volver de la rutina llamada, el programa en C se encarga de quitar de la pila los parámetros de llamada realizando varios pop
     - ( )  Pasar a una función un puntero a una variable se traduce en introducir en la pila el valor de la variable

220. ¿Cuál de los siguientes registros tiene que ser salvaguardado (si va a
    modificarse) dentro de una subrutina según la convención cdecl para IA32?
     - ( ) `eax`
     - (x) `ebx`
     - ( ) `ecx`
     - ( ) `edx`	

221. ¿En qué registro se pasa el primer argumento a una función en Linux gcc
    x86-64?
     - ( ) `ecx`
     - ( ) `edx`
     - ( ) `esi`
     - (x) `edi`

222. La práctica "popcount" debía calcular la suma de bits (peso Hamming) de
    los elementos de un array. Un estudiante entrega la siguiente versión de
    popcount3:
    <code>                                          
    int popconut3 (unsigned* array, int len) {      <br>
        int , res = 0;                              <br>
        unsigned x;                                 <br>
        for ( i=0; i &lt; len; i++ ) {                   <br>
            x = array\[i];                           <br>
            asm("ini3:        \n"                   <br>
            "shr %\[x]         \n"                   <br>
            "adc $0, %\[r]     \n"                   <br>
            "add $0, %\[x]     \n"                   <br>
            "jne ini3         \n"                   <br>
                                                    <br>
            : \[r] "+r" (res)                        <br>
            : \[x] "r" (x) );                        <br>
        }                                           <br>
        return res;                                 <br>
    }                                               <br>
    </code>

     Esta función produce siempre el resultado correcto, a pesar de que una instrucción
     máquina en la sección asm() es distinta a la que se esperaba después de haber
     estudiado pcount_r en teoría. La instrucción distinta también se podría haber
     cambiado por...
 
     - ( ) `sar %[x]`
     - ( ) `adc $0, %[x]`
     - (x) `test %[x], %[x]`
     - ( ) `cmp %[x], %[r]`

223. En la práctica de la bomba necesitamos estudiar el código máquina de la
    bomba del compañero. A veces dicho código no se visualiza directamente en
    el depurador ddd, y algunas de las técnicas que se pueden probar para
    conseguir visualizarlo son... (marcar la opción **falsa**)
     - ( ) comprobar que está activado el panel <br> *View → Machine Code Window*
     - ( ) escribir info line main en el panel de línea de comandos gdb
     - (x) recompilar con información de depuración, por si se nos había olvidado, ya que sin `–g` el ejecutable no contiene información de depuración
     - ( ) asegurarse de que se ha escrito correctamente el nombre del ejecutable

224. En la práctica de la bomba, el primer ejercicio consistía en "saltarse" las
    "explosiones", para lo cual se puede utilizar...
     - ( ) objdump o gdb
     - (x) gdb o ddd
     - ( ) ddd o hexedit
     - ( ) hexedit u objdump

225. En la práctica de la bomba, el segundo ejercicio consistía en crear un
    ejecutable sin "explosiones", para lo cual se puede utilizar...
     - ( ) objdump o gdb
     - (x) gdb o ddd
     - ( ) ddd o hexedit
     - ( ) hexedit u objdump

226. En la práctica de la bomba, el tercer ejercicio consistía en usar un editor
    hexadecimal para crear un ejecutable sin "explosiones". Para saber qué
    contenidos del fichero hay que modificar, se puede utilizar... (marcar la opción
    falsa)
     - ( ) objdump
     - ( ) gdb
     - ( ) ddd
     - (x) hexedit

227. Suponer una memoria cache con las siguientes propiedades: Tamaño: 512
    bytes. Política de reemplazo: LRU. Estado inicial: vacía (todas las líneas
    inválidas). Suponer que para la siguiente secuencia de direcciones enviadas a
    la cache: 0, 2, 4, 8, 16, 32, la tasa de acierto es 0,33. ¿Cuál es el tamaño de
    bloque de la cache?
     - ( ) 4 bytes
     - (x) 8 bytes
     - ( ) 16 bytes
     - ( ) Ninguno de los anteriores	

228. Abajo se ofrece el listado de una función para multiplicar matrices C = A x
    B.<br>
    <code>
    void mult_matr(float A\[N]\[N]   <br>
    float B\[N]\[N], float C\[N]\[N]) { <br>
    /\*Assume val.ini. C=(0,0...)\*/ <br>
    int i,j,k; <br>
    for (i=0; i<N; i++) <br>
        for (j=0; j<N; i++) <br>
            for (k=0; k<N; i++) <br>
                C\[i]\[j] += A\[i]\[k]*B\[k]\[j]; <br>
    }
    </code> <br>
    Suponer que:<br>
    <ul>
        <li> El computador tiene una cache de datos de 8 MB, 16-vías, líneas de 64 bytes.</li>
        <li> N es grande, una fila o columna no cabe completa en cache.</li>
        <li> El tamaño de los tipos de datos es como en IA32.</li>
        <li> El compilador optimiza el acceso a C\[i]\[j] en un registro.</li>
    </ul>
    Aproximadamente, ¿qué tasa de fallos se podría esperar de esta función para
    valores grandes de N?
    - (x) 1/2
    - ( ) 1/4
    - ( ) 1/8
    - ( ) 1/16

229. Sea un computador de 32 bits con una memoria cache L1 para datos de 32
     KB y líneas de 64 bytes asociativa por conjuntos de 2 vías. Dado el siguiente
     fragmento de código:<br>
     <code>
     int v[262144];<br>
     for (i=0; i<262144; i+=8) <br>
         v[i]=9; <br>
     </code><br> 
     ¿Cuál será la tasa de fallos aproximada que se obtiene en la ejecución del bucle
     anterior?
     - ( ) 0 (ningún fallo)
     - (x) 1/2 (mitad aciertos, mitad fallos)
     - ( ) 1/8 (un fallo por cada 8 accesos)
     - ( ) 1 (todo son fallos)	

230. ¿Qué hace `gcc -O0`?
     - (x) Compilar sin optimización
     - ( ) Compilar .c -> .o (fuente C a objeto)
     - ( ) Compilar .s -> .o (fuente ASM a objeto)
     - ( ) Compilar .c -> .s (C→ASM sin generar objeto)

231. ¿Qué modificador (switch) de gcc hace falta para compilar una aplicación de
    32 bits en un sistema de 64 bits?
     - (x) `-m32`
     - ( ) `-m64`
     - ( ) `-march32`
     - ( ) `-march64`

232. La etiqueta del punto de entrada a un programa ensamblador en el entorno
   de las prácticas 1 a 4 (GNU/as Linux x86) es:
     - ( ) `_main`
     - ( ) `L0`
     - (x) `_start`
     - ( ) `_init`

Explicacion: No es x86-64, que con gcc el punto de entrada es `main`. 

233. La siguiente línea en la sección de datos de un programa en ensamblador de
IA32<br>
    `result: .int 0,0`
     - ( ) Reserva espacio para un único entero, inicializado a 0,0
     - ( ) Reserva espacio para un entero, inicializado a 0, seguido de un dato de tamaño indefinido, también inicializado a 0
     - (x) Reserva espacio para dos enteros, inicializados ambos a 0
     - ( ) Reserva espacio para un único entero, inicializado a 0, en la posición de memoria 0

234. El volcado mostrado abajo se ha obtenido con el comando...<br> <code>
    00000000 main: <br>
     0: 55             push %ebp <br>
     1: 89 e5          mov %esp, %ebp   <br>
     3: 83 e4 f0       and $-16, %esp<br>
     6: 83 ec 10       sub  $0x10, %esp<br>
     9: c7 44 24 04 03 movl $3, 4(%esp)<br>
     e: 00 00 00<br>
    11: c7 04 24 01 00 movl $0x1, (%esp)<br>
    16: 00 00<br>
    18: e8 fc ff ff ff call \<main+0x19><br>
    1d: c9             leave<br>
    1e: c3             ret<br>
    </code>
     - ( ) `objdump -h p`
     - ( ) `objdump -d p`
     - (x) `objdump -d p2.o`
     - ( ) `objdump -t p2.olibC`

235. En la práctica "media" se desea invocar desde lenguaje ensamblador la
     función printf() de libC. Eso implica que este programa, como todo programa
     que use libC,
     - ( ) es obligatorio que contenga `main` (y entonces es más cómodo usar gcc para enlazar)
     - ( ) es obligatorio enlazarlo usando gcc (y entonces es más cómodo que contenga `main`)
     - ( ) es ventajoso para ensamblarlo que contenga `main`, y entonces es conveniente enlazarlo usando gcc (aunque ambas cosas son opcionales)
     - (x) es ventajoso para enlazarlo usar gcc, y entonces es conveniente que contenga `main` (aunque ambas cosas son opcionales)

236. En la práctica "media" se pide sumar una lista de 32 enteros SIN signo de 32
     bits en una plataforma de 32 bits sin perder precisión, esto es, evitando perder
     acarreos. Un estudiante entrega la siguiente versión <br>
    <code>
    # $lista en EBX, longlista en ECX <br>
    suma:<br>
        mov $0, %eax<br>
        mov $0, %edx<br>
        mov $0, %esi<br>
    bucle:<br>
        add (%ebx, %edx, 4), %eax<br>
        jnc seguir<br>
        inc %edx<br>
    seguir:<br>
        inc %esi<br>
        cmp %esi, %ecx<br>
        jne bucle<br>
        ret
    </code><br>
    Esta función presenta una única diferencia frente a la solución recomendada en
    clase, relativa al indexado en el array.
    Esta función suma:
     - ( ) Produce siempre el resultado correcto
     - ( ) allaría con `lista: .int 1,1,1,1, 1,1,1,1, ...`
     - (x) Fallaría con `lista: .int 1,2,3,4, 1,2,3,4, ...`
     - ( ) No es correcta pero el error no se manifiesta en los ejemplos propuestos, o se manifiesta en ambos

Explicacion: El problema es que como registro índice usa en la operación suma `%edx`, que es el correspondiente al acarreo. Por tanto, como en el segundo caso los valores de la lista varían, no funcionaría.

237. En la práctica "media" se pide sumar una lista de 32 enteros SIN signo de 32
   bits en una plataforma de 32 bits sin perder precisión, esto es, evitando perder
   acarreos. De entre los siguientes, ¿cuál es el mínimo valor entero que repetido
   en toda la lista causaría acarreo con 32 bits (sin signo)? Se usa notación
   decimal y espacios como separadores de millares/millones/etc.
     - ( ) 10 000 000
     - ( ) 100 000 000
     - (x) 1 000 000 000
     - ( ) 10 000 000 000

238. En la práctica "media" se pide sumar una lista de 32 enteros CON signo de
    32 bits en una plataforma de 32 bits sin perder precisión, esto es, evitando
    desbordamiento. De entre los siguientes, ¿cuál es el valor negativo más pequeño (en valor absoluto) que
    repetido en toda la lista causaría desbordamiento con 32 bits (en
    complemento a 2)? Se usa notación decimal y espacios como separadores de
    millares/millones/etc.
     - ( ) -10 000 000
     - (x) -100 000 000
     - ( ) -1 000 000 000
     - ( ) -10 000 000 000

239. ¿Cuál es el popcount (peso Hamming, número de bits activados) del número 19?
     - ( ) 2
     - (x) 3
     - ( ) 4
     - ( ) 5
    
240. La práctica "popcount" debía calcular la suma de bits (peso Hamming) de
    los elementos de un array. Un estudiante entrega la siguiente versión de
    popcount3:<br>
     <code>                                          
     int popconut3 (unsigned* array, int len) {      <br>
         int , res = 0;                              <br>
         unsigned x;                                 <br>
         for ( i=0; i &lt len; i++ ) {               <br>
             x = array[i];                           <br>
             asm("ini3:        \n"                   <br>
             "shr %[x]         \n"                   <br>
             "adc $0, %[r]     \n"                   <br>
             "add $0, %[x]     \n"                   <br>
             "jne ini3         \n"                   <br>
                                                    <br>
             : [r] "+r" (res)                        <br>
             : [x] "r" (x) );                        <br>
         }                                           <br>
         return res;                                 <br>
     }                                               <br>
     </code><br>
     Esta función solo tiene una diferencia con la versión "oficial" recomendada en clase. En concreto, una instrucción máquina en la sección **asm()** es distinta. Esta función `popcount3`:
     - (x) produce siempre el resultado correcto
     - ( ) fallaría con **array={0,1,2,3}**
     - ( ) fallaría con **array={1,2,4,8}**
     - ( ) no es correcta pero el error no se manifiesta en los ejemplos propuestos, o se manifiesta en ambos
    
Explicacion: La orden distinta es `add $0, %[x]`, que se usa en la versión "oficial" `test %[x], %[x]`.

241. La práctica "popcount" debía calcular la suma de bits (peso Hamming) de
    los elementos de un array. Un estudiante entrega la siguiente versión de
    popcount3:<br>
     <code>                                          
     int popconut3 (unsigned* array, int len) {      <br>
         long val = 0;                               <br>
         int , res = 0;                              <br>
         unsigned x;                                 <br>
         for ( i=0; i &lt len; i++ ) {               <br>
             x = array[i];                           <br>
                                                     <br>
             do {                                    <br>
                val = x & 0x1;                       <br>
                x >>= 1;                             <br>
             } while (x);                            <br>
             val += (val >> 16);                     <br>
             val += (val >> 8);                      <br>
         }                                           <br>
                                                     <br>
         return val & 0xFF;                          <br>
     }                                               <br>
     </code> <br>
     Esta función es una mezcla inexplicada de las versiones "oficiales" de **popcount2** y **popcount4**, incluyendo diferencias en 2 tipos de datos, la ausencia de la variable **res** y la diferente posición de la máscara **0xFF**.<br> Esta función popcount3:
    - ( ) produce siempre el resultado correcto
    - ( ) fallaría con **array={0,1,2,3}**
    - ( ) fallaría con **array={1,2,4,8}**
    - (x) no es correcta pero el error no se manifiesta en los ejemplos propuestos, o se manifiesta en ambos.

242. La práctica "popcount" debía calcular la suma de bits (peso Hamming) de
    los elementos de un array. Un estudiante entrega la siguiente versión de
    popcount4:<br>
     <code>                                          
     int popconut3 (unsigned* array, int len) {      <br>
         int , res = 0;                              <br>
         unsigned x;                                 <br>
         for ( i=0; i &lt len; i++ ) {               <br>
             x = array[i];                           <br>
             asm("ini3:        \n"                   <br>
             "shr %[x]         \n"                   <br>
             "adc $0, %[r]     \n"                   <br>
             "add $0, %[x]     \n"                   <br>
             "jne ini3         \n"                   <br>
                                                    <br>
             : [r] "+r" (res)                        <br>
             : [x] "r" (x) );                        <br>
         }                                           <br>
         return res;                                 <br>
     }                                               <br>
     </code><br>Esta función presenta varias diferencias con la versión "oficial" recomendada en clase, incluyendo la ausencia de una variable auxiliar **val** y la diferente posición de los desplazamientos **>>** y máscara **0xFF**. Esta función popcount4:
     - ( ) produce siempre el resultado correcto
     - ( ) fallaría con **array={0,1,2,3}**
     - ( ) fallaría con **array={1,2,4,8}**
     - (x) no es correcta pero el error no se manifiesta en los ejemplos propuestos, o se manifiesta en ambos

243. La práctica "parity" debía calcular la suma de paridades impar (XOR de
    todos los bits) de los elementos de un array. Un estudiante entrega la
    siguiente versión de `parity5`:<br>
     <code>
     int parity5 (unsigned * array, int len) { <br>
         int i, j, result=0;<br>
         unsigned x;<br>
         for (i=0; i &lt; len; i++) {<br>
             x ^= x >> j;<br>
             result += x & 0x1;<br>
         }<br>
         return result;<br>
     }<br>
     </code><br>Esta función solo se diferencia de la versión "oficial" recomendada en clase, en las condiciones del bucle **for** interno. Esta función `parity5`:
     - ( ) Produce siempre el resultado correcto
     - ( ) Fallaría con array={0,1,2,3}
     - (x) Fallaría con array={1,2,4,8}
     - ( ) No es correcta pero el error no se manifiesta en los ejemplos propuestos, o se manifiesta en ambos

244. La función `gettimeofday()` en la práctica de la "bomba digital" se utiliza para
     - ( ) Para comparar las duraciones de las distintas soluciones del programa
     - ( ) Para imprimir la fecha y hora
     - ( ) Para cifrar la contraseña en función de la hora actual
     - (x) Para cronometrar lo que tarda el usuario en introducir la contraseña

245. Un fragmento de una "bomba" desensamblada es:<br>
     <code>
     0x0804873f: call 0x8048504 &lt;scanf> <br>
     0x08048744: mov 0x24 (%esp), %edx <br>
     0x08048748: mov 0x804a044, %eax <br>
     0x0804874d: cmp %eax, %edx <br> 
     0x0804874f: je 0x8048756 &lt;main+230> <br>
     0x08048751: call 0x8048604 &lt;boom> <br>
     0x08048756: ... <br>
     </code><br>La contraseña/clave en este caso es...
     - ( ) el string almacenado a partir de la posición de memoria `0x804a044`
     - ( ) el string almacenado a partir de la posición de memoria `0x24(%esp)`
     - (x) el entero almacenado a partir de la posición de memoria `0x804a044`
     - ( ) el entero `0x804a044`

246. Una de las "bombas" utiliza el siguiente bucle para cifrar la cadena con la
    contraseña introducida por el usuario:<br>
     <code>
     80485bb: rolb $0x4, (eax) <br>
     80485be: add $0x1, %eax <br>
     80485c1: cmp %edx, %eax <br>
     80485c3: jne 80485bb &lt; encrypt+0x20>  <br>
     </code><br>
     La intrucción **rolb** rota el byte destino hacia la izquierda tantos bits como indica el operando fuente. Si inicialmente `eax` apunta a la cadena del usuario, que se compara con otra cadena `\x16\x26\x27\x16\x36\x16\x46\x16\x26\x27\x16`, almacenada en el código, la contraseña es:
     - (x) `\x61\x62\x72\x61\x63\x61\x64\x61\x62\x72\x61` (`abracadabra`)
     - ( ) `\x61\x72\x62\x61\x64\x61\x63\x61\x72\x62\x61` (`arbadacarba`)
     - ( ) `\x63\x61\x64\x61\x62\x72\x61\x61\x62\x72\x61` (`cadabraabra`)
     - ( ) `\x61\x62\x72\x61\x61\x62\x72\x61\x63\x61\x64` (`abraabracad`)

247. Una de las "bombas" utiliza el siguiente código para cifrar la clave
    numérica introducida por el usuario y ahora almacenada en `eax`:<br>
     <code>
     804870d: xor $0xfff, %eax <br>
     8048712: mov $0x2, %ecx <br>
     8048717: cltd <br>
     8048718: idiv %ecx <br>
     804871a: cmp %eax, 0x804a034 <br>
     </code> <br>Si el entero almacenado a partir de 0x804a034 es 0x7ff, la clave numérica puede ser:
     - ( ) `0x10094F97 (269045655)`
     - ( ) `0xfff (4095)`
     - ( ) `0x7ff (2047)`
     - (x) `1`

248. En el programa line.cc de la práctica 5, si para cada tamaño de línea (line)
    recorremos una única vez el vector, la gráfica resultante es decreciente
    porque:
     - ( ) Cada vez que line aumenta al doble, el número de aciertos por localidad temporal aumenta, porque ya habíamos accedido a cada posición i del vector cuando lo recorrimos en el punto anterior del eje X.
     - ( ) Cada vez que line aumenta al doble, el número de aciertos por localidad espacial aumenta, porque ya habíamos accedido a cada posición i-1 del vector cuando lo recorrimos en el punto anterior del eje X.
     - ( ) Cada vez que line aumenta al doble, se accede con éxito a más posiciones del vector en niveles de la jerarquía de memoria más rápidos.
     - (x) Cada vez que line aumenta al doble, realizamos la mitad de accesos al vector que para el valor anterior.

249. ¿Cuál de las siguientes afirmaciones sobre el programa size.cc de la
    práctica 5 es cierta?
     - ( ) La diferencia de velocidades entre L2 y L3 es mayor que la diferencia de velocidades entre L1 y L2.
     - ( ) Si continuáramos multiplicando por 2 el tamaño del vector en el eje X obteniendo más puntos de la gráfica, esta continuaría horizontal para cualquier valor más allá de 64 MB.
     - (x) La gráfica tiene escalones hacia arriba porque en cada punto del eje X accedemos al mismo número de elementos del vector y el número de aciertos por localidad temporal disminuye bruscamente en ciertos puntos al aumentar el tamaño del vector.
    - ( ) La gráfica tiene tramos horizontales porque el hecho de realizar la mitad de accesos al vector en cada punto de un tramo horizontal respecto al anterior punto de ese mismo tramo horizontal es compensado por el número de fallos creciente en ese mismo tramo horizontal.