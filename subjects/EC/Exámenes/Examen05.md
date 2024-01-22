<br>

# Estructura de Computadores. Examen 05.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Estructura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
- **Profesor:** Ignacio Rojas Ruiz.
- **Fecha:** 12-12-2023.
- **Descripción:** Examen de Temas 3-6 de Teoría, y prácticas 3 y 4.

Cada persona tenía un examen, por lo que hubo muchas versiones de este examen. De una batería de preguntas del profesor (salía de forma aleatoria); por lo que no hay un único examen, sino muchos. Esta es la primera versión subida.
______


1. Respecto a las unidades de control nanoprogramadas:
    - (x) La anchura de la memoria de nanoprograma es la misma que la de memoria de microprograma en un diseño de la misma unidad de control que no usara nanoprogramación.
    - ( ) Suponiendo una memoria de microprograma con \\(n\\) microinstrucciones de \\(w\\) bits cada una, de las cuales \\(2^m\\) son distintas, el ahorro en bits si se utiliza nanoprogramación es \\((n\cdot w+2^m\cdot w)−n\cdot w\\).
    - ( ) La realización nanoprogramada de una unidad de control es más rápida que la microprogramada.
    - ( ) El diseño de las unidades de control nanoprogramadas siempre tiene que ser vertical.

2. Una posible codificación en microinstrucciones de la instrucción `call X` es:
    - ( ) `PC := X ; SP := SP-1 ; m[SP] := PC`
    - ( ) `SP := SP-1 ; m[SP] := PC ; PC := PC+1`
    - ( ) `SP := PC-1 ; m[SP] := PC ; PC := X`
    - (x) `SP := SP-1 ; m[SP] := PC ; PC := X`

3. Suponga que la micropalabra de una máquina microprogramada tiene 8 bits de ancho y se usan 16 micropalabras diferentes en un microprograma de 32 micropalabras. Si se usa nanoprogramación...
    - ( ) no se ahorran bits pero el funcionamiento es más rápido.
    - ( ) se ahorran bits y además el funcionamiento es más lento.
    - ( ) se ahorran bits y el funcionamiento es más rápido.
    - (x) no se ahorran bits y además el funcionamiento es más lento.

4. La ganancia de velocidad ideal en un cauce de K etapas de igual duración T ejecutando un programa de N instrucciones es:
    - ( ) S=(N*T)/((N+N-1)*T)
    - ( ) S=(K*N)/(K-N+1)
    - ( ) S=(K*N*T)/((K-N+1)*T)
    - (x) S=(K*N)/(K+N-1)

5. Un procesador x86 a 4 GHz dispone de 7 unidades de ejecución en paralelo, con 20 etapas de segmentación, y es capaz de emitir (comenzar a ejecutar) 4 instrucciones en cada ciclo de reloj. ¿Qué velocidad aproximada de ejecución de instrucciones será capaz de alcanzar (MIPS = millones de instrucciones por segundo)?
    - (x) 16000 MIPS
    - ( ) 28000 MIPS
    - ( ) 80000 MIPS
    - ( ) 4000 MIPS

6. La práctica "popcount" debía calcular la suma de bits (peso Hamming) de los elementos de un array. Un estudiante entrega la siguiente versión de popcount5:
<br><code>int popcount5(unsigned* array,int len){<br>int i,j;<br>unsigned x;<br>int result = 0;<br>for(i=0;i<<tmp>len;i++){<br>x=array[i];<br>for(j=0;j<<tmp>8;j++){<br>result += x & 0x01010101;<br>x>>=1;<br>}<br>}<br>result += (result >> 16);<br>result += (result >> 8);<br>return result & 0xFF;<br>}</code><br>
Esta función presenta varias diferencias con la versión recomendada en clase, incluyendo la ausencia de una variable auxiliar `val`. Esta función popcount5:
    - ( ) produce siempre el resultado correcto
    - ( ) fallaría con array={1,2,4,8}
    - (x) no es correcta pero el error no se manifiesta en los ejemplos propuestos, o se manifiesta en ambos
    - ( ) fallaría con array={0,1,2,3}

7. En la práctica de la bomba, el primer ejercicio consiste en ir saltando las "explosiones" mientras se depura el código, para lo cual se puede utilizar...
    - ( ) ddd o hexedit
    - ( ) hexedit u objdump
    - ( ) objdump o gdb
    - (x) gdb o ddd

8. En popcount8, la variable:
<br><code>int SSE_LUTb[] = {0x02010100, 0x03020201, 0x03020201, 0x04030302};</code><br>
se usa:
    - ( ) como máscara para hacer un `and` con un registro `xmm`.
    - ( ) como tabla de direcciones de registros `xmm` (por ej. 02 indica `xmm2`, 01 indica `xmm1`,...)
    - ( ) como máscara para hacer un `xor` con un registro `xmm`.
    - (x) como tabla de consulta para reemplazar secuencias de 4 bits por sus correspondientes popcount de 4 bits.

9. Suponga la expresión:
<br><code>unsigned int val = x & 0x01010101;</code><br>
donde `x` es un `unsigned int`. ¿Cuál de los siguientes valores de `x` da como resultado `val = 0x01010101`?
    - (x) 0x13579bdf
    - ( ) 0x10101010
    - ( ) 0xeeeeeeee
    - ( ) 0xaaaaaaaa

10. Si compilamos con `-Og` la función:
<br><code>unsigned long f (unsigned long val) {<br>return val + (val >> 64);<br>}</code><br>
Obtenemos:
<br><code>movq %rdi, %rax<br>movl $64, %ecx<br>shrq %cl, %rax<br>addq %rdi, %rax<br>ret</code><br>
Teniendo en cuenta que las instrucciones de desplazamiento de números de 64 bits usan sólo los 6 bits menos significativos del número de desplazamientos a realizar, este código:
    - ( ) Devuelve 0
    - (x) Devuelve val * 2
    - ( ) Devuelve val / 2
    - ( ) Devuelve val

11. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx4 y ROM de 8Kx2. La memoria SRAM debe ocupar las direcciones `0x0000` a `0xBFFF` y la ROM `0xC000` a `0xFFFF`. Los módulos necesarios serían, respecto a la ROM, serian:
    - ( ) 8
    - ( ) 12
    - (x) 16
    - ( ) 20

12. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx2 y ROM de 8Kx4. La memoria SRAM debe ocupar las direcciones `0x0000` a `0xBFFF` y la ROM `0xC000` a `0xFFFF`. Los módulos necesarios serían, respecto a la ROM, serian:
    - ( ) 16
    - (x) 24
    - ( ) 32
    - ( ) 8

13. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx4 y ROM de 8Kx2. La memoria SRAM debe ocupar las direcciones `0x0000` a `0xBFFF` y la ROM `0xC000` a `0xFFFF`. Los módulos necesarios serían:
    - ( ) 14 módulos de SRAM y 16 de ROM
    - ( ) 16 módulos de SRAM y 12 de ROM
    - (x) 12 módulos de SRAM y 16 de ROM
    - ( ) Ninguna es correcta

14. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx2 y ROM de 8Kx4. La memoria SRAM debe ocupar las direcciones `0x0000` a `0xBFFF` y la ROM `0xC000` a `0xFFFF`. Los módulos necesarios serían:
    - ( ) 24 módulos de SRAM y 16 de ROM
    - (x) 24 módulos de SRAM y 8 de ROM
    - ( ) 16 módulos de SRAM y 16 de ROM
    - ( ) Ninguna es correcta

15. Diseñe un sistema de memoria de 128 KB direccionable por palabras de 16 bits a partir de módulos SRAM de 16Kx2 y ROM de 8Kx4. La memoria SRAM debe ocupar las direcciones `0x0000` a `0xBFFF` y la ROM `0xC000` a `0xFFFF`. Los módulos necesarios serían, respecto a la ROM, serian:
    - (x) 8
    - ( ) 16
    - ( ) 32
    - ( ) 64

16. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:
<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>
Sobre la memoria cache L3, el campo de etiqueta tiene un tamaño de:
    - (x) 16 bits
    - ( ) 12 bits
    - ( ) 15 bits
    - ( ) 11 bits

17. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:
<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>
Sobre la memoria cache L2, el campo de etiqueta tiene un tamaño de:
    - ( ) 18 bits
    - ( ) 19 bits
    - (x) 20 bits
    - ( ) 16 bits

18. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:
<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>
Sobre la memoria cache L1, el campo de etiqueta tiene un tamaño de:
    - (x) 23 bits
    - ( ) 20 bits
    - ( ) 18 bits
    - ( ) Ninguna respuesta es correcta

19.  Se dispone de un procesador, con la siguiente jerarquía de memoria:
<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>
Sobre la memoria cache L3, el tamaño total que ocupan los datos es:
    - ( ) 16777216 bits
    - ( ) 16777216 B
    - ( ) 1703936 bits
    - (x) 67108864 bits

20. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:
<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>
Sobre la memoria cache L2, el tamaño total que ocupan las etiquetas es:
    - (x) 81920
    - ( ) 42740
    - ( ) 40960
    - ( ) 86016

21.  Se dispone de un procesador, con la siguiente jerarquía de memoria:
<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>
Sobre la memoria cache L1, el campo de etiqueta tiene un tamaño de:
    - ( ) 16 bits
    - (x) 18 bits
    - ( ) 20 bits
    - ( ) 24 bits

22. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:
<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>
Sobre la memoria cache L1, el campo de conjunto tiene un tamaño de:
    - ( ) 12
    - ( ) 10
    - (x) 7
    - ( ) Ninguna respuesta es correcta

23.  Se dispone de un procesador, con la siguiente jerarquía de memoria:
<br>Memoria principal: 1GB<br>Tamaño de línea/bloque: 64B<br>Nivel 1 cache: 32 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 8 MB de 16 vías<br>
Sobre la memoria cache L3, el tamaño total que ocupan las etiquetas es:
    - (x) 1441792 bits
    - ( ) 1K bits
    - ( ) 1703936 bits
    - ( ) Ninguna respuesta es correcta

24. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:
<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>
Sobre la memoria cache L2, el campo de conjunto tiene un tamaño de:
    - ( ) 12
    - ( ) 14
    - (x) 10
    - ( ) 8

25. Se dispone de un procesador, con palabras de 64 bits, con la siguiente jerarquía de memoria:
<br>Memoria principal: 64GB<br>Tamaño de línea/bloque: 8 palabras<br>Nivel 1 cache: 64 KB de 8 vías<br>Nivel 2 cache: 256 KB de 4 vías<br>Nivel 3 cache: 16 MB de 16 vías<br>
Sobre la memoria cache L3, el tamaño total que ocupan las etiquetas es:
    - (x) 4Mbits
    - ( ) 1KB
    - ( ) 16KB
    - ( ) Ninguna respuesta es correcta