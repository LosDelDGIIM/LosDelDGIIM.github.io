<br>

# Estructura de Computadores. Examen 02.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Estructura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
- **Profesor:** Ignacio Rojas Ruiz.
- **Fecha:** 07-11-2023.
- **Descripción:** Examen de Temas 1 y 2 de Teoría, y prácticas 1-3.

Cada persona tenía un examen, por lo que hubo muchas versiones de este examen. De una batería de preguntas del profesor (salía de forma aleatoria); por lo que no hay un único examen, sino muchos. Esta es la segunda versión subida.

Cada respuesta correcta suma 1 punto, y cada respuesta incorrecta resta 0.33 puntos. Las preguntas no respondidas no suman ni restan. La puntuación total es sobre 20.
______

1. Dado un vector `W` de enteros (en `%rdx`), y un índice `j` (en `%rcx`). La expresión `*(W+j-4)` podría traducirse en una sentencias de ensamblador, del tipo:
    - (x) `movl -16(%rdx,%rcx,4), %eax`
    - ( ) `movl -12(%rdx,%rcx,4), %eax`
    - ( ) `leaq 4(%rdx,%rdx,4), %rax`
    - ( ) `movl (%rdx,%rcx,4),%eax`


2. Se define struct `S1{ int i[3]; char c[3]; double v} p[3];` y `union U1{ int i[3]; char c[3]; double v} q[3];`. Indica que afirmación es correcta.
    - ( ) `q` tiene un tamaño mayor que `p`.
    - (x) `p` tiene un tamaño mayor que `q`.
    - ( ) `q` no está alineada y `p` si.
    - ( ) `p` y `q` tienen el mismo tamaño.

3. Para leer un dato de un array multi-nivel, se requieren acceder a memoria:
    - ( ) Ninguna respuesta es correcta.
    - ( ) 3 accesos a memoria.
    - (x) 2 accesos a memoria.
    - ( ) Una sola vez.


4. Dada la siguiente estructura: <br>`struct W {int j[2]; char s[8]; short a[4]; long *j;};` <br> Indique el tamaño total de la estructura.
    - ( ) 26.
    - (x) 32.
    - ( ) 38.
    - ( ) 30.

5.  Dadas las siguientes estructuras: <br><code>struct W2 {char w[16]; char *c[2]};<br>struct W1 {short i; int c; int *j; short *d};<br><br>struct W {struct W2 q[2]; struct W1 z};</code> <br> Calcule el tamaño necesario para almacenar `W`:
    - (x) Todas las respuestas restantes son erróneas.
    - ( ) 36.
    - ( ) 38.

6. ¿Cuál será el código de una función cuya definición es `int f(int a, int b, int c)` y que se implementa así? <br><code> mov %edi , %eax<br>ret</code><br>
    - ( ) `return c`.
    - (x) `return a`.
    - ( ) `return b`.
    - ( ) Ninguna otra respuesta es correcta.

7. ¿Qué bandera se activará tras la ejecución de la instrucción `cmp`?<br><code>xor %rax, %rax<br>xor %rbx, %rbx<br>inc %rbx<br>cmp %rbx, %rax</code><br>
    - ( ) [TF].
    - ( ) [DF].
    - (x) [SF].
    - ( ) [].

8. ¿Qué registros podemos modificar a nuestro antojo en el interior de una función que sigua el protocolo "System V AMD64 ABI", también llamados salva invocante?
    - ( ) RBX, RBP, R12, R13, R14 y R15.
    - ( ) Ninguna otra respuesta es correcta.
    - (x) RAX, RCX, RDX, RDI, RSI, R8, R9, R10 y R11.
    - ( ) RSP.

9. ¿Qué código se utilizaría para conseguir que un número entero contenido en el registro `%eax` se extieenda correctamente a la pareja de registros `edx:eax`?
    - (x) `cltd`.
    - ( ) <code>mov %edx, %eax<br> sar $31, %eax</code>.
    - ( ) Ninguna otra respuesta es correcta.
    - ( ) `cltq`.

10. ¿Qué se obtiene al intentar observar en memoria un objeto de 8 bytes declarado "`resultado .quad 0 x8877665544332211`" mediante la orden de `gdb`: "`x /4hx &resultado`"? Nota: la dirección de memoria puede variar.
    - ( ) `0x403020: 0x7788 0x5566 0x3344 0x1122`.
    - (x) `0x403020: 0x2211 0x4433 0x6655 0x8877`.
    - ( ) `0x403020: 0x8877 0x6655 0x4433 0x2211`.
    - ( ) `0x403020: 0x1122 0x3344 0x5566 0x7788`.

11. Dado el siguiente fragmento de programa en ensamblador: <br><code> mov $-11,%eax<br>sar $0x83,%eax<br>and $0xFF,%eax</code><br> ¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?
    - ( ) 0x0.
    - ( ) 0xFF.
    - (x) 0xFE.
    - ( ) 0xF5.

12. ¿Qué función codifica el siguiente fragmento de código? <br><code> 0: cmp %esi , %edi<br>2: setne %al<br>5: retq</code><br>
    - ( ) <code>bool igual(int a, int b)<br>{<br>if (a == b)<br>return true;<br>else<br>return false;<br>}</code>.
    - ( ) <code>int min(int a, int b)<br>{<br>if (a < b)<br>return a;<br>else<br>return b;<br>}</code>.
    - ( ) <code>int max(int a, int b)<br>{<br>if (a > b)<br>return a;<br>else<br>return b;<br>}</code>.
    - (x) <code>bool distinto(int a, int b)<br>{<br>if (a != b)<br>return true;<br>else<br>return false;<br>}</code>.

13. ¿Qué contendrá el tope de la pila durante la ejecución de la función `f()` en el siguiente programa? <br><code>401020 <_start >:<br>401020: e8 08 00 00 00 callq 40102 d f<br>401025: 48 31 ff<br>xor %rdi , %rdi<br>401028: e8 e3 ff ff ff<br>callq 401010 exit@plt <br>40102 d f :<br>40102 d: eb fe<br>jmp 40102d f<br>40102 f: c3<br>retq</code><br>
    - (x) 0x401025.
    - ( ) 0x401020.
    - ( ) 0x401028.
    - ( ) 0x40102d.

14. Dado el siguiente fragmento de programa en ensamblador: <br><code> xor %rcx, %rcx<br>sub $58, %rcx<br>mov $0x1, %ebx<br>rcr %cl,%rbx</code><br> ¿Cuál es el valor del registro `RBX` al finalizar la última instrucción?
    - ( ) No se puede determinar. Depende del valor inicial que tuviese `%rbx`.
    - ( ) 0x0.
    - ( ) 0xFFFFFFFFFFFFFFFF.
    - (x) 0x0c00000000000000.

15. Dado el siguiente fragmento de programa en ensamblador: <br><code> mov $-18,%eax<br>sar $0x46,%eax<br>and $0xFF,%eax</code><br> ¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?
    - (x) 0xFF.
    - ( ) 0x0.
    - ( ) 0xFFFFFFFF.
    - ( ) Todo el resto de respuestas es incorrecto.

16. Dado el siguiente fragmento de programa en ensamblador: <br><code> mov $0, %rbx<br>mov %rbx, %rax<br>sub $1, %rax<br>rcr $6,%rbx</code><br> ¿Cuál es el valor del registro `RBX` al finalizar la última instrucción?
    - ( ) 0x6.
    - ( ) 0x0.
    - ( ) 0xFFFFFFFF.
    - (x) 0x400000000000000.

17. ¿Cuanto vale `rax` tras ejecutar el programa dentro de `gdb` mediante las órdenes que aparecen como comentarios?<br><code>. text # break bucle<br>_start : . globl _start # run<br>xor %rax , %rax # continue<br> bucle : inc %rax # continue<br> jmp bucle # print $rax</code><br>
    - ( ) 1.
    - ( ) 3.
    - (x) 2.
    - ( ) 0.

18. Dado el siguiente fragmento de programa en ensamblador: <br><code> mov $-14,%eax<br>sar $0x3,%eax<br>and $0xFF,%eax</code><br> ¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?
    - (x) 0xFE.
    - ( ) 0xFF.
    - ( ) 0xFFFFFFFF.
    - ( ) 0x00.

19. Dado el siguiente fragmento de programa en ensamblador: <br><code> mov $-14,%eax<br>sar $0x3,%eax<br>and $0xFF000000,%eax</code><br> ¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?
    - ( ) Todas las respuestas anteriores son incorrectas.
    - (x) 0xFF000000.
    - ( ) 0x3FFFFFFF.
    - ( ) 0xFFFFFFFF.

20. ¿A qué función puede corresponder el siguiente código ensamblador? <br><code> cmp %esi , %edi<br>mov %esi , %eax<br>cmovge %edi , %eax<br>ret</code><br>
    - (x) <code>int f(int a, int b)<br>{<br>if (a > b)<br>return a;<br>else<br>return b;<br>}</code>.
    - ( ) <code>int f(int a, int b)<br>{<br>if (a == b)<br>return a;<br>else<br>return b;<br>}</code>.
    - ( ) <code>int f(int a, int b)<br>{<br>if (a < b)<br>return a;<br>else<br>return b;<br>}</code>.
    - ( ) <code>int f(int a, int b)<br>{<br>if (a > b)<br>return b;<br>else<br>return a;<br>}</code>.