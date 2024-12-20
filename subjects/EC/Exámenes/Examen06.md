<br>

# Estructura de Computadores. Examen 06.

**Autor:** Roberto
***

- **Asignatura:** Estructura de Computadores.
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Ignacio Rojas Ruiz.
<!--- **Fecha:** 12-12-2023.-->
<!--- **Descripción:** Examen de Temas 3-6 de Teoría, y prácticas 3 y 4.-->

Cada persona tenía un examen, por lo que hubo muchas versiones de este examen. De una batería de preguntas del profesor (salía de forma aleatoria); por lo que no hay un único examen, sino muchos. No se daban las preguntas corregidas, por lo que no sabemos las resupuestas correctas.
______

1. Suponga que la micropalabra de una máquina microprogramada tiene 8 bits de ancho y se usan 16 micropalabras diferentes en un microprograma de 32 micropalabras. Si se usa nanoprogramación...
    - ( ) no se ahorran bits pero el funcionamiento es más rápido.
    - ( ) se ahorran bits pero el funcionamiento es más lento.
    - ( ) se ahorran bits y el funcionamiento es más rápido.
    - (x) no se ahorran bits y además el funcionamiento es más lento.

2. La técnica de "adelanto de registros" (register forwarding) en un cauce segmentado se usa para limitar el impacto de los riesgos...
    - (x) de datos
    - ( ) de control
    - ( ) estructurales
    - ( ) organizativos

3. Respecto a las unidades de control nanoprogramadas:
    - ( ) La anchura de la memoria de nanoprograma es la misma que la de memoria de microprograma en un diseño de la misma unidad de control que no usara nanoprogramación.
    - ( ) El diseño de las unidades de control nanoprogramadas siempre tiene que ser vertical.
    - ( ) La realización nanoprogramada de una unidad de control es más rápida que la microprogramada.
    - ( ) Suponiendo una memoria de microprograma con `n` microinstrucciones de `w` bits cada una, de las cuales \\(2^m\\) son distintas, el ahorro en bits si se utiliza nanoprogramación es \\((nw+2^mw)−n*w\\).

4. La ganancia de velocidad ideal en un cauce de `K` etapas de igual duración `T` ejecutando un programa de `N` instrucciones es:
    - (x) \\(S=(KN)/(K+N-1)\\)
    - ( ) \\(S=(KN*T)/((K-N+1)T)\\)
    - ( ) \\(S=(NT)/((N+N-1)T)\\)
    - ( ) \\(S=(KN)/(K-N+1)\\)

5. Una posible codificación en microinstrucciones de la instrucción `call X` es:
    - ( ) `SP := SP-1 ; m[SP] := PC ; PC := PC+1`
    - ( ) `SP := PC-1 ; m[SP] := PC ; PC := X`
    - (x) `SP := SP-1 ; m[SP] := PC ; PC := X`
    - ( ) `PC := X ; SP := SP-1 ; m[SP] := PC`

6. En un camino de datos con un único bus, para realizar la operación de copia de un registro r1 en un registro r2, es decir `r2 <- r1`, es necesario:
    - ( ) Habilitar la salida triestado del registro r2 y activar la carga de los registros r1 y r2
    - ( ) Activar la carga del registro r1 y habilitar la salida triestado del registro r2
    - ( ) Habilitar las salidas triestado de los registros r1 y r2 y activar la carga del registro r2
    - (x) Habilitar la salida triestado del registro r1 y activar la carga del registro r2

7. En la secuencia de instrucciones siguiente, siendo el primer registro el destino, ¿cuántos riesgos se dan?<br><code>sub r4,r1,r3<br>or r8,r6,r4</code><br>
    - ( ) Un riesgo estructural y dos por dependencia de datos
    - ( ) Dos riesgos por dependencia de datos y uno de control
    - ( ) Un riesgo estructural
    - (x) Un riesgo por dependencia de datos

8. En la realización de la práctica de la bomba digital compilada en 32 bits, una parte del código máquina es el siguiente:<br><code>0x080486e8 <main+120>: call 0x8048524 <strncmp><br>0x080486ed <main+125>: test %eax,%eax<br>0x080486ef <main+127>: je 0x80486f6 <main+134><br>0x080486f1 <main+129>: call 0x8048604 <boom></code><br>
¿Cuál de los siguientes comandos de gdb cambiaría el salto condicional por un salto incondicional?
    - ( ) `set $0x080486ef=0xeb`
    - ( ) `set %0x080486ef=0xeb`
    - ( ) `set (char)0x080486f6=jmp`
    - ( ) `set (char)0x080486ef=0xeb`

9. Tras dividir `0x00000000 00040000` (en EDX:EAX) entre `0x00008000` (ECX), el resultado será:
    - ( ) 0x0 en AX y 0x8 en DX
    - ( ) 0x0 en EAX y 0x8 en EDX
    - (x) 0x8 en EAX y 0x0 en EDX
    - ( ) 0x8 en AX y 0x8 en DX

10. En la práctica de la bomba, el primer ejercicio consiste en ir saltando las "explosiones" mientras se depura el código, para lo cual se puede utilizar…
    - ( ) ddd o hexedit
    - ( ) objdump o gdb
    - (x) gdb o ddd
    - ( ) hexedit u objdump

11. Una función C devuelve el valor de un elemento de un array mediante el siguiente código ensamblador:<br><code>leaq (%rdi,%rdi,4), %rax<br>addq %rsi, %rax<br>movl var(,%rax,4), %eax<br>retq</code><br>Se puede adivinar que:
    - ( ) var es un array multi-nivel (punteros a enteros) con cinco filas
    - ( ) var es un array bidimensional de enteros y no se puede adivinar ninguna de sus dimensiones
    - (x) var es un array bidimensional de enteros con cinco columnas
    - ( ) var es un array multi-nivel (punteros a enteros) y no se puede adivinar ninguna de sus dimensiones

12. Si compilamos con `-Og` la función:<br><code>unsigned long f (unsigned long val) {<br>return val + (val >> 64);<br>}</code><br>Obtenemos:<br><code>movq %rdi, %rax<br>movl $64, %ecx<br>shrq %cl, %rax<br>addq %rdi, %rax<br>ret</code><br>Teniendo en cuenta que las instrucciones de desplazamiento de números de 64 bits usan sólo los 6 bits menos significativos del número de desplazamientos a realizar, este código:
    - ( ) Devuelve val / 2
    - ( ) Devuelve 0
    - ( ) Devuelve val
    - (x) Devuelve val * 2

13. Respecto a la inicialización de los elementos del array:<br><code>#define SIZE (1<<16)<br>for (i=0; i<SIZE; i++)<br>lista[i]=i;</code><br>
    - ( ) Las tres funciones suma del programa suma_09_Casm irán igual de rápido con esta inicialización que con números aleatorios.
    - ( ) Cualquiera de las tres funciones suma del programa suma_09_Casm irá más rápido con esta inicialización que con números aleatorios.
    - ( ) popcount2 (bucle interno while) irá más lento con esta inicialización que con números aleatorios.
    - ( ) popcount1 (bucle interno for) irá más rápido con esta inicialización que con números aleatorios

14. En x86-64, una función con 10 parámetros de tipo long que devuelve el valor del 8º parámetro y no modifica el puntero de pila puede traducirse a ensamblador como:
    - ( ) `movq 16(%rsp), %ra- x ret`
    - ( ) `movq %r10, %rax ret`
    - ( ) `movq %r8, %rax ret`
    - ( ) `movq 8(%rsp), %rax ret`

15. En una bomba como las estudiadas en prácticas, del tipo...<br><code>0x080486e8 <main+120>: call 0x8048524 <strncmp><br>0x080486ed <main+125>: test %eax,%eax<br>0x080486ef <main+127>: je 0x80486f6 <main+134><br>0x080486f1 <main+129>: call 0x8048604 <boom></code><br>la contraseña es...
    - ( ) el string almacenado a partir de 0x8048524
    - ( ) ninguna de las otras opciones
    - ( ) el string almacenado a partir de 0x80486f6
    - ( ) el string almacenado a partir de 0x8048604

16. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L3, el tamaño total que ocupan las etiquetas es:
    - (x) 1441792 bits
    - ( ) 1K bits
    - ( ) 1703936 bits
    - ( ) Ninguna respuesta es correcta

17. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx2 y ROM de 8Kx4. La memoria SRAM debe ocupar las direcciones 0x0000 a 0xBFFF y la ROM 0xC000 a 0xFFFF. Los módulos necesarios serían:
    - ( ) 24 módulos de SRAM y 16 de ROM
    - ( ) 24 módulos de SRAM y 8 de ROM
    - ( ) 16 módulos de SRAM y 16 de ROM
    - ( ) Ninguna es correcta

18. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>Sobre la memoria cache L2, el tamaño total que ocupan las etiquetas es:
    - ( ) 81920
    - ( ) 42740
    - ( ) 40960
    - ( ) 86016

19. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>Sobre la memoria cache L2, el campo de etiqueta tiene un tamaño de:
    - ( ) 18
    - ( ) 19
    - (x) 20
    - ( ) 16

20. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx4 y ROM de 8Kx2. La memoria SRAM debe ocupar las direcciones 0x0000 a 0xBFFF y la ROM 0xC000 a 0xFFFF. Los módulos necesarios serían:
    - ( ) 14 módulos de SRAM y 16 de ROM
    - ( ) 16 módulos de SRAM y 12 de ROM
    - ( ) 12 módulos de SRAM y 16 de ROM
    - ( ) Ninguna es correcta

21. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>Sobre la memoria cache L3, el tamaño total que ocupan las etiquetas es:
    - ( ) 4Mbits
    - ( ) 1KB
    - ( ) 16KB
    - ( ) Ninguna respuesta es correcta

22. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx2 y ROM de 8Kx4. La memoria SRAM debe ocupar las direcciones 0x0000 a 0xBFFF y la ROM 0xC000 a 0xFFFF. Los módulos necesarios serían, respecto a la RAM, serían:
    - ( ) 16
    - ( ) 24
    - ( ) 32
    - (x) 8

23. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L2, el campo de conjunto tiene un tamaño de:
    - (x) 10
    - ( ) 11
    - ( ) 14
    - ( ) 17

24. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L3, tamaño total que ocupan los datos es:
    - (x) 16777216 bits
    - ( ) 16777216 B
    - ( ) 1703936 bits
    - ( ) 67108864 bits

25. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L1, el campo de conjunto tiene un tamaño de:
    - ( ) 12
    - ( ) 10
    - ( ) 7
    - ( ) 8

26. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx4 y ROM de 8Kx2. La memoria SRAM debe ocupar las direcciones 0x0000 a 0xBFFF y la ROM 0xC000 a 0xFFFF. Los módulos necesarios serían, respecto a la SRAM, serían:
    - ( ) 8
    - (x) 12
    - ( ) 14
    - ( ) 16

27. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L3, el campo de conjunto tiene un tamaño de:
    - ( ) 13
    - (x) 11
    - ( ) 14
    - ( ) 17

28. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L2, el tamaño total que ocupan las etiquetas es:
    - ( ) 49152 bits
    - ( ) 1K bits
    - (x) 57344 bits
    - ( ) Ninguna respuesta es correcta

29. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>Sobre la memoria cache L1, el campo de conjunto tiene un tamaño de:
    - ( ) 12
    - ( ) 10
    - (x) 7
    - ( ) Ninguna respuesta es correcta

30. Se dispone de un procesador, con la siguiente jerarquía de memoria:<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>Sobre la memoria cache L2, el tamaño total que ocupan los datos es:
    - ( ) \\((2^19)(2^6)\\) bits
    - ( ) \\((2^11)(2^6)\\) B
    - ( ) \\((2^10)(2^6)\\) B
    - (x) \\((2^15)(2^6)\\) bits
