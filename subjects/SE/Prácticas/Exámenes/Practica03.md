# Sistemas Empotrados - Test Práctica 3: Ensamblador ARM y Linker Script

- **Descripción:** Preguntas Tipo Test de la Práctica 3: Programación en ensamblador ARM, directivas GNU assembler, mapa de memoria de la Econotag y scripts de enlazado.

---

1. ¿Cuál de las siguiente opciones transfiere el contenido de la variable masc al registro r1?
    - ( ) ldr r0, =masc; str r1, [r0]
    - (x) ldr r0, =masc; ldr r1, [r0]
    - ( ) ldr r1, masc
    - ( ) ldr r1, =masc

2. Indica en cual de las siguientes secciones se deben definir las variables globales inicializadas en un fichero ensamblador
    - ( ) .bss
    - ( ) No es necesario indicar la sección, el ensamblador las emitirá automáticamente a la sección.data
    - (x) .data
    - ( ) .rodata

3. ¿Cuál de las siguiente binutils usarías para desensamblar un fichero elf?
    - ( ) Los ficheros elf no se pueden desensamblar
    - (x) objdump
    - ( ) nm
    - ( ) readelf

4. ¿Cuál de las siguientes binutils usarías obtener las tabla de símbolos de un ejecutable?
    - ( ) Solamente objdump
    - (x) Todas las otras respuestas son correctas
    - ( ) Sólamente nm
    - ( ) Sólamente readelf

5. El el SoC MC1322x de Freescale dispone de 96 kBytes de memoria RAM. ¿En cuántos bloques está estructurada dicha memoria?
    - (x) 4
    - ( ) 3
    - ( ) 2
    - ( ) 1

6. ¿Cuál de las binutils se usa para extraer la imagen binaria de un archivo elf?
    - ( ) objdump
    - (x) objcopy
    - ( ) nm
    - ( ) readelf

7. Indica qué opción declara correctamente una variable global de 32 bits en ensamblador:
    - (x) a:.word 8, dentro de la sección.data
    - ( ) a: 8, dentro de la sección.data
    - ( ) .global a
    - ( ) a:.word 8, en cualquier parte del fichero ensamblador

8. Al almacenar las máscaras de los leds en variables en lugar de usar símbolos definidos mediante la directiva.set, la velocidad de ejecución del programa...
    - ( ) No se ve afectada si se trata de variables locales
    - ( ) No se ve afectada si se trata de variables globales
    - ( ) Mejora
    - (x) Empeora

9. Asumiendo que se ha mapeado la sección de código del programa hello al comienzo de la memoria RAM de la Econotag, ¿a qué banco de memoria se debería mapear la sección de datos del programa hello.elf para maximizar el tamaño de la imagen binaria del ejecutable?
    - ( ) RAM2
    - (x) RAM3
    - ( ) RAM1
    - ( ) RAM4

10. En un script de enlazado, ¿cómo obtendrías la dirección virtual en la que comienza la sección de código de un ejecutable?
    - ( ) Insertando la expresión "PROVIDE(dir =.text)" en cualquier parte de la directiva sections
    - (x) Insertando la expresión "dir =.;" al principio de la sección
    - ( ) Insertando la expresión "dir =.text" en cualquier parte de la directiva sections
    - ( ) Insertando la expresión "dir = LOADADDR(.text)" en cualquier parte de la directiva sections

11. ¿Cual de las siguientes opciones transfiere el contenido de la variable masc al resgistro r1?
    - (x) ldr r0, =masc; ldr r1, [r0]
    - ( ) mov r1, =masc
    - ( ) ldr r1, =masc
    - ( ) str r1, [r0]

12. La directiva.global a del ensamblador de la GNU...
    - (x) Permite que el símbolo a sea accesible desde otros módulos del programa
    - ( ) Define una constante global inmutable
    - ( ) Reserva memoria en la sección.bss
    - ( ) Fija la dirección absoluta de a

13. Para definir en el linker script un símbolo que permita acceder a los registros del GPIO, debemos definir el símbolo GPIO_BASE = 0x80000000...
    - (x) Fuera de la definición de cualquier sección de salida
    - ( ) Dentro de la definición de cualquier sección de salida
    - ( ) En el fichero fuente en C
    - ( ) En la cabecera del fichero ensamblador

14. Para consultar la tabla de símbolos de nuestra aplicación podemos usar la binutil nm sobre...
    - (x) El fichero.elf de la aplicación
    - ( ) El fichero binario plano.bin
    - ( ) El fichero fuente.c
    - ( ) El fichero de texto del script de enlazado

