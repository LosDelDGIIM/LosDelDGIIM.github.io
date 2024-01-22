<br>

# Estructura de Computadores. Examen 04.

**Autor:** Arturo Olivares Martos
**Autor:** José Juan Urrutia Milán "JJ"
***

- **Asignatura:** Estructura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
- **Profesor:** Ignacio Rojas Ruiz.
- **Fecha:** 7-11-2023.
- **Descripción:** Examen de Temas 1 y 2 de Teoría, y prácticas 1-3.

Cada persona tenía un examen, por lo que hubo muchas versiones de este examen. De una batería de preguntas del profesor (salía de forma aleatoria); por lo que no hay un único examen, sino muchos. Esta es la segunda versión subida.

Cada respuesta correcta suma 1 punto, y cada respuesta incorrecta resta 0.33 puntos. Las preguntas no respondidas no suman ni restan. La puntuación total es sobre 20.
______

1. Se define struct `S1{int i[3], char c[3], double v} p[3]` y union `U1{int i[3], char c[3], double v} q[3];`, indica qué afirmación es correcta:
    - ( ) `q` tiene un tamaño mayor que `p`.
    - ( ) `p` y `q` tienen el mismo tamaño.
    - ( ) `q` no está alineada y `p` si.
    - (x) `p` tiene un tamaño mayor que `q`.

2. Dada la siguiente estructura `struct W{int j[2], char s[8], short a[4], long *j};` Indique el tamaño total de la estructura.
    - ( ) 28.
    - ( ) 30.
    - ( ) 26.
    - (x) 32.

3. Dado un vector `W` de enteros (en `%rdx`), y un índice `j` (en `%rcx`). La expresión `*(W+j-4)` podría traducirse en una sentencia del tipo:

    - ( ) `movl -12(%rdx, %rcx, 4), %eax`
    - (x) `movl -16(%rdx, %rcx, 4), %eax`
    - ( ) `movl (%rdx, %rcx, 4), %eax`
    - ( ) `leaq 4(%rdx, %rdx, 4), %eax`

4. La lectura de un elemento de un array anidado, necesita los siguientets accesos a memoria:

    - ( ) Tres.
    - (x) Uno.
    - ( ) Ninguna respuesta es correcta.
    - ( ) Dos.

5. Para leer un datos de un array multi-nivel, se requieren acceder a memoria:

    - ( ) Tres accesos a memoria.
    - ( ) Ninguna respuesta es correcta.
    - (x) Dos accesos a memoria.
    - ( ) Una sola vez.

6. ¿Cuánto vale `edx` tras ejecutar el siguiente código?.<br>
   `xor %eax, %eax` <br>
   `sub $1, %eax` <br>
   `cltd`

    - ( ) 0x00000000
    - (x) 0xFFFFFFFF
    - ( ) 0xFFFFFFFE
    - ( ) 0x00000001

7. ¿Qué bandera se activará tras la ejecución de la instrucción `cmp` <br>
   `xor %rax, %rax` <br>
   `xor %rbx, %rbx` <br>
   `inc %rbx` <br>
   `cmp %rbx, %rax`

    - ( ) [TF]
    - ( ) [DF]
    - (x) [SF]
    - ( ) [ ]

8. ¿Qué código utilizaría para conseguir que un número entero contenido en el registro `eax` se expanda correctamente a la pareja de registros `edx:eax`?

    - (x) `cltd`
    - ( ) `mov %edx, %eax`<br>`sar $31, %eax`
    - ( ) Ninguna otra respuesta es correcta.
    - ( ) `cltq`

9. ¿Cuál será el código de una función cuya definicion es `int f(int a, int b, int c)` y que se implementa así? <br>
   `mov %esi, %eax` <br>
   `ret` <br>

    - ( ) `return c;`
    - ( ) `return a;`
    - (x) `return b;`
    - ( ) Ninguna otra respuesta es correcta.

10. ¿Qué código cree mejor para copiar en `edx:eax` un valor de 64 bits almacenado en el tope de la pila sin alterarla?

     - ( ) `movw (%rsp), %ax`<br> `movw 4(%rsp), %rdx`
     - (x) `mov (%rsp), %eax`<br> `mov 4(%rsp), %edx`
     - ( ) `mov (%rsp), %rax`<br> `mov %rax, %rdx`<br> `and $0xffffffff, %rax`<br> `shr $32, %rdx`
     - ( ) `pop %rax`<br> `mov %rax, %rdx`<br> `and $0xffffffff, %rax`<br> `shr $32, %rdx`

11. Dado el siguiente fragmento de programa en ensamblador: <br>
    `mov $-18, %eax` <br>
    `sar $0x46, %eax` <br>
    `and $0xFF, %eax` <br>
    ¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?

    - (x) 0xFF.
    - ( ) 0x0.
    - ( ) 0xFFFFFFFF.
    - ( ) Todo el resto de respuestas es incorrecto.

12. Dado el siguiente fragmento de programa en ensamblador: <br>
    `mov $-14, %eax` <br>
    `sar $3, %eax` <br>
    `and $0xFF, %eax` <br>
    ¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?

    - ( ) 0xFFFFFFFF
    - ( ) 0xFF
    - (x) 0xFE
    - ( ) 0x00

13. Dado el siguiente fragmento de programa en ensamblador: <br>
    `mov $-11, %eax` <br>
    `sar $0x83, %eax` <br>
    `and $0xFF, %eax` <br>
    ¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?

    - ( ) 0xFF
    - ( ) 0xF5
    - ( ) 0x00
    - (x) 0xFE

14. Dado el siguiente fragmento de programa en ensamblador: <br>
    `mov $-18, %eax` <br>
    `sar $0x46, %eax` <br>
    `and $0xFF000000, %eax` <br>
    ¿Cuál es el valor del registro `RAX` al finalizar la última instrucción?

    - ( ) 0xFF
    - ( ) 0x00
    - (x) 0xFF000000
    - ( ) Todo el resto de respuestas son incorrectas.

15. Dado el siguiente fragmento de programa en ensamblador: <br>
    `xor %rcx, %rcx` <br>
    `and $5, %ecx` <br>
    `mov $0x12345, %ebx` <br>
    `rcr %cl, %rbx` <br>
    ¿Cuál es el valor del registro `RBX` al finalizar la última instrucción?

    - (x) Todas las restantes respuestas son incorrectas.
    - ( ) 0x00001
    - ( ) 0x0
    - ( ) 0x500000000000091a

16. ¿Qué función codifica el siguiente fragmento de código? <br>
    `0: cmp %esi, %edi` <br>
    `2: mov %esi, %eax` <br>
xor %rcx, %rcx
and $5, %ecx
mov $0x12345, %ebx
rcr %cl, %rbx
    `7: retq`

    - (x) `int min(int a, int b)` <br> `{ if (a<b)` <br> `return a;` <br> `else` <br> `return b;` <br> `}`
    - ( ) `bool igual(int a, int b)` <br> `{ if (a==b)` <br>      `return true;` <br>      `else` <br>      `return false;` <br> `}`
    - ( ) `int max(int a, int b)` <br>      `{ if (a>b)` <br>      `return a;` <br>      `else` <br>      `return b;` <br>      `}`
    - ( ) `bool distinto(int a, int b)` <br>      `{ if (a!=b)` <br>      `return return;` <br>      `else` <br>      `return false;` <br>     `}`

1.   Dado el siguiente fragmento de programa en ensamblador: <br>
    `xor %rcx, %rcx` <br>
    `sub $58, %rcx` <br>
    `mov $0x1, %ebx` <br>
    `rcr %cl, %rbx` <br>
    ¿Cuál es el valor del registro `RBX` al finalizar la última instrucción?

    - ( ) No se puede determinar. Depende del valor inicial que tuviese `%rbx`.
    - ( ) 0x0
    - ( ) 0xFFFFFFFFFFFFFFFF
    - (x) 0x0c00000000000000

2.   ¿Qué contendrá el tope de la pila durante la ejecución de la función `f()` en el siguiente programa? <br>
    `401020 <_start>` <br>
    `401020: e8 08 00 00 00 callq 40102 d <f>` <br>
    `401025: 48 31 ff   xor %rdi, %rdi` <br>
    `401028: e8 e3 ff ff ff callq 401010 <exit@plt>` <br>
    `40102d <f>:` <br>
    `40102d: eb fe  jmp 40102d <f>` <br>
    `40102f: c3 retq`

    - (x) 0x401025
    - ( ) 0x401020
    - ( ) 0x401028
    - ( ) 0x40102d

3.   ¿Qué función codifica el siguiente fragmento de código? <br>
    `0: cmp %esi, %edi` <br>
    `2: setne %al` <br>
    `5: retq`

    - ( ) `bool igual(int a, int b)` <br>      `{ if (a==b)` <br>      `return true;` <br>      `else` <br>      `return false;` <br>      `}`
    - ( ) `int min(int a, int b)` <br>      `{ if (a<b)` <br>      `return a;` <br>      `else` <br>      `return b;` <br>      `}`
    - ( ) `int max(int a, int b)` <br>      `{ if (a>b)` <br>      `return a;` <br>      `else` <br>      `return b;` <br>      `}`
    - (x) `bool distinto(int a, int b)` <br>      `{ if (a!=b)` <br>      `return true;` <br>      `else` <br>      `return false;` <br>      `}`

4.   Dado el siguiente fragmento de programa en ensamblador: <br>
    `xor %rbx, %rbx` <br>
    `xor %rax, %rax` <br>
    `sub $1, %rax` <br>
    `rcr $4, %rbx` <br>
    ¿Cuál es el valor del registro `RBX` al finalizar la última instrucción?

    - (x) 0x1000000000000000
    - ( ) 0x40000000
    - ( ) 0x4
    - ( ) 0x0