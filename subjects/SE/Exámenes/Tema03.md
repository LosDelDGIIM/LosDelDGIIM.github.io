# Sistemas Empotrados - Test Tema 3: Jerarquía de Memoria

- **Descripción:** Preguntas Tipo Test correspondientes al Tema 3: Jerarquía de Memoria (Mapa de memoria, remapeo, secciones VMA/LMA, heap, pila y cargador del sistema).

---

1. ¿Cuántas pilas necesitan los sistemas basados en procesadores ARM?
    - ( ) Solamente una pila
    - ( ) Una para el modo USER, otra para los modos de interrupción y otra para el resto de modos
    - (x) Una para cada modo de ejecución privilegiado
    - ( ) Una para el modo de ejecución USER y otra para los modos privilegiados

2. Las direcciones VMA y LMA podrían coincidir en...
    - (x) El código de la aplicación
    - ( ) Las variables locales
    - ( ) Las variables globales inicializadas
    - ( ) Las variables globales sin inicializar

3. El boot loader
    - (x) No puede escribirse completamente en C
    - ( ) Es una parte opcional del BSP
    - ( ) Debe escribirse en ensamblador
    - ( ) Se auto-copia en la RAM para ejecutarse más rápido

4. En el caso de que el enlazador genere direcciones LMA y VMA diferentes para la aplicación, la aplicación usará...
    - ( ) Tanto direcciones VMA como LMA, pero nunca simultáneamente Incorrecto.
    - (x) Sólo direcciones VMA
    - ( ) Sólo direcciones LMA
    - ( ) Tanto las direcciones VMA como las LMA, de forma simultánea

5. Las variables locales...
    - ( ) Son almacenadas por el linker en la sección.bss
    - (x) Se crean en la pila cada vez que se invoca a la función en la que se han declarado
    - ( ) Son almacenadas por el linker en la sección.data
    - ( ) Ninguna de las otras respuestas es correcta

6. La expresión. = ALIGN(4);
    - ( ) Se usa en los ficheros ensamblador para forzar un alineamiento a la siguiente frontera de 32 bits
    - ( ) Se usa en el linker script para forzar un alineamiento a la siguiente frontera de 4 bits
    - (x) Se usa en el linker script para forzar un alineamiento a la siguiente frontera de 32 bits
    - ( ) Se usa en los ficheros ensamblador para forzar un alineamiento a la siguiente frontera de 4 bits

7. Asumiendo que el código del cargador está en la sección.startup, que el código del resto de la aplicación está en la sección.text, y que el sistema tiene mapeada una memoria flash a la dirección 0x00000000 y una memoria RAM a la dirección 0x03000000, indica cual de las siguientes opciones para la implementación de la directiva SECTIONS del script de enlazado permite cargar la aplicación y ejecutarla desde la RAM
    - ( ) .image: { *(.text); *(.startup); } > ram AT > flash
    - (x) .startup: { *(.startup); } > flash;.text: { *(.text); } > ram AT > flash
    - ( ) .image: { *(.startup); *(.text); } > flash
    - ( ) .image: { *(.startup); *(.text); } > ram AT > flash

8. A la hora de implementar un sistema empotrado, la función main...
    - (x) No debe retornar jamás
    - ( ) Sólo retornará en caso de error
    - ( ) Retornará un cero si se ha ejecutado correctamente
    - ( ) Retornará un valor distinto de cero si se ha ejecutado correctamente

9. Las variables globales no inicializadas por el programador...
    - ( ) Se inicializan siempre a cero en el linker script
    - (x) Son emitidas a la sección COMMON por el compilador
    - ( ) Se inicializan siempre a cero por el compilador
    - ( ) Son emitidas a la sección.bss por el compilador

10. El registro sp se inicializa por...
    - ( ) El compilador
    - ( ) La CPU al arrancar
    - ( ) El linker
    - (x) El cargador de arranque

11. El remapeo de memoria...
    - (x) Permite que la aplicación o el SO puedan modificar los vectores de excepción en cualquier momento remapeando la dirección 0 a la RAM
    - ( ) Solo es útil para aumentar la velocidad de acceso a la memoria Flash
    - ( ) Se realiza exclusivamente por software sin necesidad de soporte hardware
    - ( ) Es obligatorio para poder inicializar la memoria caché de datos

12. La tabla de manejadores de excepción...
    - (x) Contiene punteros a función
    - ( ) Contiene instrucciones de salto directo B o LDR PC
    - ( ) Está implementada en hardware dentro de la CPU ARM
    - ( ) Reside permanentemente en la memoria ROM del fabricante

13. El código de la aplicación no se modificará en tiempo de ejecución.
    - (x) Sin embargo, se puede copiar a la RAM del sistema para que su ejecución sea más rápida
    - ( ) Por tanto, nunca tiene sentido copiarlo a la memoria RAM
    - ( ) Por lo que sus direcciones VMA y LMA siempre deben coincidir obligatoriamente
    - ( ) Lo que impide que pueda llamar a funciones externas del BSP

14. Las direcciones VMA y LMA siempre deben ser diferentes para..
    - (x) Las variables globales inicializadas (.data)
    - ( ) El código del programa (.text) si se ejecuta desde Flash
    - ( ) Las constantes (.rodata) cuando no se copian a RAM
    - ( ) La tabla de vectores fija en ROM

15. Los símbolos _data_start y _data_end
    - (x) Siempre definen direcciones dentro de la RAM del sistema
    - ( ) Definen la posición permanente de los datos en la memoria Flash
    - ( ) Son definidos automáticamente por el hardware de la CPU
    - ( ) Delimitan el espacio reservado para la pila del modo Supervisor

16. Indica el modo de ejecución al que pasa un procesador ARM tras la pulsación del botón Reset
    - (x) Supervisor
    - ( ) User
    - ( ) System
    - ( ) Undefined

17. ¿Qué debe haber siempre en la dirección 0 de memoria en un sistema basado en un procesador ARM?
    - (x) Un salto al cargador del sistema
    - ( ) La función main de la aplicación
    - ( ) La pila del modo User
    - ( ) La tabla de dispositivos del sistema

18. Las direcciones de inicio y fin del heap...
    - (x) Se definen explícitamente en el linker script
    - ( ) Vienen fijadas por el hardware del procesador ARM
    - ( ) Son calculadas dinámicamente por la función malloc en cada llamada
    - ( ) Coinciden siempre con el inicio y fin de la memoria Flash

19. ¿Cual de los siguientes pasos ejecuta antes el boot loader?
    - (x) Inicializar la tabla de vectores de excepción
    - ( ) Ejecutar la función main de la aplicación
    - ( ) Registrar los dispositivos en la tabla de Newlib
    - ( ) Inicializar el driver L1 de la UART

