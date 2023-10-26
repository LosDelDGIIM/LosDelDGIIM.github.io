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

Las preguntas se encuentran en [esta web](https://losdeldgiim.github.io/subjects/EC/Ex%C3%A1menes/Examenes_Generados/TipoTest.html).

Las explicaciones de cada pregunta se pueden encontrar en el archivo Markdown correspondiente, que se encuentra pinchando [aquí](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/EC/Ex%C3%A1menes/TipoTest.md).
______

1. Respecto a direccionamiento a memoria en ensamblador IA32 (sintaxis AT&T), de la forma `D(Rb, Ri, S)`, sólo una de las siguientes afirmaciones es FALSA. ¿Cuál?
    - ( )  El desplazamiento D puede ser una constante lineal (1, 2 ó 4 bytes).
    - (x) `EBP` no se puede usar como registro base.
    - ( )  `ESP` no se puede usar como registro índice.
    - ( )  El factor de escala S pued

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
