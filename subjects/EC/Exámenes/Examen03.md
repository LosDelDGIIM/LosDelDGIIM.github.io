<br>

# Estructura de Computadores. Examen 03.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Estructura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
- **Profesor:** Ignacio Rojas Ruiz.
- **Fecha:** 20-11-2023.
- **Descripción:** Repetición del examen de Temas 1 y 2 de Teoría, y prácticas 1-3.

El primer parcial se invalidó y se repetió por ser muy complicado y entrar materia que no habíamos dado.

Cada persona tenía un examen, por lo que hubo muchas versiones de este examen. De una batería de preguntas del profesor (salía de forma aleatoria); por lo que no hay un único examen, sino muchos. Esta es la primera versión subida.

Cada respuesta correcta suma 1 punto, y cada respuesta incorrecta resta 0.33 puntos. Las preguntas no respondidas no suman ni restan. La puntuación total es sobre 18.
______

1. Dado el siguiente fragmento de programa en ensamblador:
<br><code>xor %rbx,%rbx<br>xor %rcx,%rcx<br>sub $56,%rcx<br>mov $0x1,%ebx<br>rcr %cl,%rbx</code><br>
¿Cuál es el valor del registro `RBX` al finalizar la última instrucción?
    - ( ) `0xFF`
    - ( ) `0xFFFFFFFFFFFFFFFF`
    - ( ) `0x0`
    - (x) `0x0300000000000000`

2. Dado el siguiente fragmento de programa en ensamblador:
<br><code>xor %rbx,%rbx<br>xor %rax,%rax<br>sub $1, %rax<br>rcr $4,%rbx</code><br>
¿Cuál es el valor del registro `RBX` al finalizar la última instrucción?
    - ( ) `0x0`
    - ( ) `0x4`
    - (x) `0x1000000000000000`
    - ( ) `0x40000000`

3. Dado el siguiente fragmento de programa en ensamblador:
<br><code>mov $-18,%eax<br>sar $0x46,%eax<br>and $0xFF,%eax</code><br>
¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?
    - ( ) `0x0`
    - ( ) `0xFFFFFFFF`
    - ( ) Todo el resto de respuestas es incorrecto
    - (x) `0xFF`

4. Dado el siguiente fragmento de programa en ensamblador:
<br><code>mov $-18,%eax<br>sar $0x46,%eax<br>and $0xFF000000,%eax</code><br>
¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?
    - (x) `0xFF000000`
    - ( ) `0x00`
    - ( ) `0xFF`
    - ( ) Todo el resto de respuestas son incorrectas.

5. Dado el siguiente fragmento de programa en ensamblador:
<br><code>mov $-14,%eax<br>sar $3,%eax<br>and $0xFF,%eax</code><br>
¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?
    - ( ) `0xFFFFFFFF`
    - ( ) `0x00`
    - ( ) `0xFF`
    - (x) `0xFE`

6. Dado el siguiente fragmento de programa en ensamblador:
<br><code>xor %rcx,%rcx<br>add $7,%rcx<br>mov $0x1234,%ebx<br>rcr %cl,%rbx</code><br>
¿Cuál es el valor del registro `RBX` al finalizar la última instrucción?
    - (x) `0xd000000000000024`
    - ( ) `0x24`
    - ( ) `0x0`
    - ( ) `0x00000001234`

7. ¿Cuál de las siguientes parejas de nemotécnicos de ensamblador corresponden a la misma instrucción máquina?
    - ( ) `JC` (saltar si acarreo), `JL` (saltar si menor, para  números con signo).
    - ( ) `CMP` (comparar), `SUB` (restar).
    - (x) `JZ` (saltar si cero), `JE` (saltar si igual).
    - ( ) `SAR` (desplazamiento aritmético a la derecha) / `SHR` (desplazamiento lógico a la derecha).

8. Suponga la siguiente sentencia asm en un programa:
<br><code>asm(" add (%[a],%[i],4),%[r]"<br>:[r] "+r" (result)<br>:[i] "r" (i),<br>[a] "r" (array)<br>);</code><br>
¿Cuál de las siguientes afirmaciones es incorrecta?
    - ( ) Se desea que el valor calculado por la instrucción ensamblador quede almacenado en la variable `result`.
    - ( ) `i` es un registro de salida.
    - (x) `a` es un registro de entrada.
    - ( ) `r` es un registro de entrada/salida.

9. ¿Cuál de las siguientes funciones en C NO puede traducirse al siguiente código en ensamblador?
<br><code>movslq %esi,%rsi<br>movq (%rdi,%rsi,8), %rax<br>ret</code><br>
    - ( ) <code>unsigned long elem (unsigned long v[], int i) {<br>return v[i];<br>}</code>
    - ( ) <code>unsigned *elem (unsigned *v[], int i) {<br>return v[i];<br>}</code>
    - ( ) <code>unsigned long *elem (unsigned long *v[], int i) {<br>return v[i];<br>}</code>
    - (x) <code>unsigned long elem (unsigned long v[], int *i) {<br>return v[*i];<br>}</code>

10. Dado el código de una función
<br><code>funcion: movq %rdi, %rax<br>movl $64, %ecx<br>shrq %cl, %rax<br>addq %rdi, %rax<br>ret</code><br>
este código:
    - ( ) Todas las respuestas son erroneas
    - ( ) Devuelve 0
    - ( ) Devuelve val.
    - (x) Devuelve val * 2

11. Si en la práctica "media" se programa la suma de una lista de 16 enteros de 4B para producir un resultado de 8 B, primero sin signo y luego con signo, y la lista se rellena con el valor `0x0400 0000`, ¿en qué se diferencian los resultados de ambos programas?
    - ( ) En uno ocupa 32 bits, en otro 64 bits.
    - ( ) En uno se interpreta como negativo, en otro como positivo.
    - ( ) En uno los 32 bits superiores son `0xFFFF FFFF`, en el otro no.
    - (x) No se diferencian.

12. Para crear espacio en la pila para variables locales sin inicializar suele realizarse la siguiente operación:
    - ( ) Sumar una cantidad positiva a `RBP`
    - (x) Restar una cantidad positiva a `RSP`
    - ( ) Sumar una cantidad positiva a `RSP`
    - ( ) Restar una cantidad positiva a `RBP`.

13. En la secuencia de programa siguiente:
<br><code>628: e8 cd ff ff ff callq 5fa suma<br>62d: 48 83 c4 20 add $0x20,%rsp</code><br>
¿cuál es el valor que introduce en la pila la instrucción `callq`?
    - ( ) 0x628
    - ( ) 0xffffffcd
    - ( ) 0x5fa
    - (x) 0x62d

14. En x86-64, una función con 10 parámetros de tipo long que devuelve el valor del 8º parámetro y no modifica el puntero de pila puede traducirse a ensamblador como:
    - ( ) <code>movq %r10, %rax<br>ret</code>
    - ( ) <code>movq %r8, %rax<br>ret</code>
    - ( ) <code>movq 8(%rsp), %rax<br>ret</code>
    - ( ) <code>movq 16(%rsp), %rax<br>ret</code>

15. Respecto a la inicialización de los elementos del array:
<br><code>#define SIZE (1<<16)<br>for (i=0; i<<tmp>SIZE; i++)<br>lista[i]=i;</code><br>
    - ( ) popcount2 (bucle interno `while`) irá más lento con esta inicialización que con números aleatorios.
    - ( ) popcount1 irá (bucle interno `for`) irá más rápido con esta inicialización que con números aleatorios
    - (x) Las tres funciones suma del programa `suma_09_Casm` irán igual de rápido con esta inicialización que con números aleatorios.
    - ( ) Cualquiera de las tres funciones suma del programa `suma_09_Casm` irá más rápido con esta inicialización que con números aleatorios.

16. La siguiente función calcula el factorial:
<br><code>fact:<br>pushq reg # preservar registro<br>movl %edi, %ebx<br>movl $1, %eax<br>testl %edi, %edi<br>je .L4<br>leal -1(%rbx), %edi<br>call fact<br>imull %ebx, %eax<br>.L4:<br>popq reg # restaurar registro<br>ret</code><br>
¿Cuál es el registro `<reg>` que tiene que guardarse en la pila?
    - ( ) %rax
    - (x) %rbx
    - ( ) %rsp
    - ( ) %rdi

17. Al traducir la sentencia C <br><code>r->i = val;</code><br>gcc genera el código ASM:<br><code>movl %edx, 8(%rax)</code><br>Se puede deducir que:
    - (x) el desplazamiento de `i` en `*r` es 8
    - ( ) `r` es un puntero que apunta a la posición de memoria 8
    - ( ) `val` es un entero que vale 8
    - ( ) `i` es un entero que vale 8

18. Si el registro `r12b` contiene la variable booleana `cond`, y `rax` la variable `valor`, la secuencia de instrucciones:
<br><code>testb %r12b, %r12b<br>movq $13, %rax<br>cmove $17, %rax</code><br>
realiza la operación:
    - (x) valor = cond ? 13 : 17;
    - ( ) valor = 17;
    - ( ) valor = cond ? 17 : 13;
    - ( ) valor = 13;