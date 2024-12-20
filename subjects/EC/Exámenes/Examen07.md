<br>

# Estructura de Computadores. Examen 07.

**Autor:** Miguel Angel De la Vega Rodríguez
***

- **Asignatura:** Estructura de Computadores.
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Ignacio Rojas Ruiz.
- **Fecha:** 16-12-2024.
- **Descripción:** Examen de Temas 3,4,5 y 6 de Teoría, y prácticas 4-6.

Cada persona tenía un examen, por lo que hubo muchas versiones de este examen. De una batería de preguntas del profesor (salía de forma aleatoria); por lo que no hay un único examen, sino muchos. Esta es la segunda versión subida.

Cada respuesta correcta suma 1 punto, y cada respuesta incorrecta resta 0.33 puntos. Las preguntas no respondidas no suman ni restan. La puntuación total es sobre 20.
______
1. Una posible codificación en microinstrucciones de la instrucción call X es:
    - ( ) PC := X ; SP := SP-1 ; m[SP] := PC
    - ( ) SP := SP-1 ; m[SP] := PC ; PC := PC+1
    - (x) SP := SP-1 ; m[SP] := PC ; PC := X
    - ( ) SP := PC-1 ; m[SP] := PC ; PC := X

2. En un camino de datos con un único bus, para realizar la operación de copia de un registro r1 en un registro r2, es decir `r2 <- r1`, es necesario:
    - ( ) Habilitar las salidas triestado de los registros r1 y r2 y activar la carga del registro r2
    - ( ) Activar la carga del registro r1 y habilitar la salida triestado del registro r2
    - (x) Habilitar la salida triestado del registro r1 y activar la carga del registro r2
    - ( ) Habilitar la salida triestado del registro r2 y activar la carga de los registros r1 y r2

3. La ganancia de velocidad ideal en un cauce de K etapas de igual duración T ejecutando un programa de N instrucciones es:
    - ( ) \\(S=(K\cdot N\cdot T)/((K-N+1)\cdot T)\\)
    - ( ) \\(S=(N\cdot T)/((N+N-1)\cdot T)\\)
    - (x) \\(S=(K\cdot N)/(K+N-1)\\)
    - ( ) \\(S=(K\cdot N)/(K-N+1)\\)

4. En la secuencia de instrucciones siguiente, siendo el primer registro el destino, ¿cuántos riesgos se dan? <br><code>sub r4, r1, r3<br>or r8, r6, r4</code><br>
    - ( ) Dos riesgos por dependencia de datos y uno de control
    - ( ) Un riesgo estructural
    - (x) Un riesgo por dependencia de datos
    - ( ) Un riesgo estructural y dos por dependencia de datos

5. La técnica de "adelanto de registros" (register forwarding) en un cauce segmentado se usa para limitar el impacto de los riesgos...
    - ( ) estructurales
    - ( ) organizativos
    - ( ) de control
    - (x) de datos

6. Un procesador x86 a 4 GHz dispone de 7 unidades de ejecución en paralelo, con 20 etapas de segmentación, y es capaz de emitir (comenzar a ejecutar) 4 instrucciones en cada ciclo de reloj. ¿Qué velocidad aproximada de ejecución de instrucciones será capaz de alcanzar (MIPS = millones de instrucciones por segundo)?
    - ( ) 80000 MIPS
    - ( ) 28000 MIPS
    - ( ) 4000 MIPS
    - (x) 16000 MIPS

7. Suponga que la micropalabra de una máquina microprogramada tiene 8 bits de ancho y se usan 16 micropalabras diferentes en un microprograma de 32 micropalabras. Si se usa nanoprogramación...
    - ( ) no se ahorran bits pero el funcionamiento es más rápido.
    - ( ) se ahorran bits pero el funcionamiento es más lento.
    - ( ) se ahorran bits y el funcionamiento es más rápido.
    - (x) no se ahorran bits y además el funcionamiento es más lento.

8. En popcount8, la variable:<br><code>int SSE_LUTb[] = {0x02010100, 0x03020201, 0x03020201, 0x04030302};</code><br>se usa:
    - ( ) como tabla de direcciones de registros xmm (por ej. 02 indica xmm2, 01 indica xmm1,...)
    - ( ) como máscara para hacer un and con un registro xmm.
    - (x) como tabla de consulta para reemplazar secuencias de 4 bits por sus correspondientes popcount de 4 bits.
    - ( ) como máscara para hacer un xor con un registro xmm.

9. La siguiente función calcula el factorial:<br><code>fact:<br> pushq   <reg>    # preservar registro<br>movl    %edi, %ebx<br>movl    $1, %eax<br>testl   %edi, %edi<br>je      .L4<br>leal    -1(%rbx), %edi<br>call    fact<br>imull   %ebx, %eax<br>.L4:<br>popq   <reg>    # restaurar registro<br>        ret</code><br>¿Cuál es el registro <reg> que tiene que guardarse en la pila?
    - (x) `%rbx`
    - ( ) `%rax`
    - ( ) `%rsp`
    - ( ) `%rdi`

10. ¿Cuál de las siguientes funciones NO calcula el factorial de un unsigned long?
    - (x) <code>fact: movl $1, %eax<br>cmpq $1, %rdi<br>ja .L8<br>ret<br>.L8: pushq %rbx<br>movq %rdi, %rbx<br>call fact<br>subq $1, %rbx<br>imulq %rbx, %rax<br>popq %rbx<br>ret</code>
    - ( ) <code>fact: movl $1, %eax<br>ja .L8<br>ret<br>.L8: pushq %rbx<br>movq %rdi, %rbx<br>leaq -1(%rdi), %rdi<br>call fact<br>imulq %rbx, %rax<br>popq %rbx<br>ret</code>
    - ( ) <code>fact: movl $1, %eax<br>.L3: cmpq $1, %rdi<br>jbe .L1<br>imulq %rdi, %rax<br>decq %rdi<br>jmp .L3<br>.L1: ret</code>
    - ( ) <code>fact: cmpq $1, %rdi<br>ja .L8<br>movl $1, %eax<br>ret<br>.L8: pushq %rbx<br>movq %rdi, %rbx<br>leaq -1(%rdi), %rdi<br>call fact<br>imulq %rbx, %rax<br>popq %rbx<br>ret</code>

11. Tras dividir 0x00000000 00040000 (en EDX:EAX) entre 0x00008000 (ECX), el resultado será:
    - ( ) 0x8 en AX y 0x8 en DX
    - ( ) 0x0 en AX y 0x8 en DX
    - ( ) 0x0 en EAX y 0x8 en EDX
    - (x) 0x8 en EAX y 0x0 en EDX

12. ¿Cuál de las siguientes parejas de nemotécnicos de ensamblador corresponden a la misma instrucción máquina?
    - ( ) `SAR` (desplazamiento aritmético a la derecha) / `SHR` (desplazamiento lógico a la derecha).
    - ( ) `CMP` (comparar), `SUB` (restar).
    - (x) `JZ` (saltar si cero), `JE` (saltar si igual).
    - ( ) `JC` (saltar si acarreo), `JL` (saltar si menor, para números con signo).

13. ¿Cuál de las siguientes funciones en C NO puede traducirse al siguiente código en ensamblador?<br><code>movslq  %esi, %rsi<br>movq    (%rdi,%rsi,8), %rax<br>ret</code>
    - ( ) `unsigned *elem (unsigned *v[],int i) { return v[i]; }`
    - ( ) `unsigned long elem (unsigned long v[], int i) { return v[i]; }`
    - (x) `unsigned long elem (unsigned long v[],int *i) { return v[*i]; }`
    - ( ) `unsigned long *elem (unsigned long *v[],int i) { return v[i]; }`

14. Una función C devuelve el valor de un elemento de un array mediante el siguiente código ensamblador:<br><code>leaq    (%rdi,%rdi,4), %rax<br>addq    %rsi, %rax<br>movl    var(,%rax,4), %eax<br>retq</code><br>¿Cuál de las siguientes afirmaciones es correcta?
    - ( ) `var` es un array multi-nivel (punteros a enteros) y no se puede adivinar ninguna de sus dimensiones.
    - (x) `var` es un array bidimensional de enteros con cinco columnas.
    - ( ) `var` es un array bidimensional de enteros y no se puede adivinar ninguna de sus dimensiones.
    - ( ) `var` es un array multi-nivel (punteros a enteros) con cinco filas.

15. Para crear espacio en la pila para variables locales sin inicializar suele realizarse la siguiente operación:
    - (x) Restar una cantidad positiva a `RSP`.
    - ( ) Sumar una cantidad positiva a `RSP`.
    - ( ) Restar una cantidad positiva a `RBP`.
    - ( ) Sumar una cantidad positiva a `RBP`.

16. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx2 y ROM de 8Kx4. La memoria SRAM debe ocupar las direcciones 0x0000 a 0xBFFF y la ROM 0xC000 a 0xFFFF.
    - (x) 8
    - ( ) 16
    - ( ) 32
    - ( ) 64

17. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L1, el campo de conjunto tiene un tamaño de:
    - ( ) 4
    - ( ) 5
    - (x) 6
    - ( ) 8

18. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>Sobre la memoria cache L1, el campo de conjunto tiene un tamaño de:
    - ( ) 12
    - ( ) 10
    - (x) 7
    - ( ) Ninguna respuesta es correcta

19. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>Sobre la memoria cache L1, el campo de etiqueta tiene un tamaño de:
    - (x) 23
    - ( ) 20
    - ( ) 18
    - ( ) Ninguna respuesta es correcta

20. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L3, el campo de etiqueta tiene un tamaño de:
    - ( ) 13
    - (x) 11
    - ( ) 14
    - ( ) 17

21. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx4 y ROM de 8Kx2. La memoria SRAM debe ocupar las direcciones 0x0000 a 0xBFFF y la ROM 0xC000 a 0xFFFF.
    - ( ) 8
    - (x) 12
    - ( ) 14
    - ( ) 16

22. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L2, el tamaño total que ocupan los datos es:
    - ( ) \\((2^19)\cdot (2^6)\\) bits
    - ( ) \\((2^11)\cdot(2^6)\\) B
    - ( ) \\((2^10)\cdot(2^6)\\) B
    - (x) \\((2^15)\cdot(2^6)\\) bits

23. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>Sobre la memoria cache L1, el tamaño total que ocupan las etiquetas es:
    - ( ) 16384
    - (x) 23552
    - ( ) 65536
    - ( ) Ninguna respuesta es correcta

24. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L1, el tamaño total que ocupan las etiquetas es:
    - ( ) 8192 bits
    - ( ) 8704 bits
    - (x) 9216 bits
    - ( ) 1024 bits

25. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L3, el tamaño total que ocupan las etiquetas es:
    - (x) 1441792 bits
    - ( ) 1K bits
    - ( ) 1703936 bits
    - ( ) Ninguna respuesta es correcta

26. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L2, el tamaño total que ocupan las etiquetas es:
    - ( ) 49152 bits
    - ( ) 1K bits
    - (x) 57344 bits
    - ( ) Ninguna respuesta es correcta

27. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>Sobre la memoria cache L2, el campo de etiqueta tiene un tamaño de:
    - ( ) 18
    - ( ) 19
    - (x) 20
    - ( ) 16

28. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L3, el tamaño total que ocupan los datos es:
    - (x) 16777216 bits
    - ( ) 16777216 B
    - ( ) 1703936 bits
    - ( ) 67108864 bits

29. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L2, el campo de conjunto tiene un tamaño de:
    - (x) 10
    - ( ) 11
    - ( ) 14
    - ( ) 17

30. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L1, el campo de etiqueta tiene un tamaño de:
    - ( ) 16 bits
    - (x) 18 bits
    - ( ) 20 bits
    - ( ) 24 bits
