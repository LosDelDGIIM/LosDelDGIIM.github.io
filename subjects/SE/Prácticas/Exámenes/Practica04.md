# Sistemas Empotrados - Test Práctica 4: Subrutinas y Cargador BSP

- **Descripción:** Preguntas Tipo Test de la Práctica 4: Paso de parámetros según ABI, cargador crt0.s, inicialización de pilas y copia de secciones VMA/LMA.

---

1. A la hora de inicializar las pilas de los diferentes modos de ejecución...
    - ( ) Hay que comprobar que previamente se ha inicializado la memoria dedicada a las pilas con el patrón 0xdeadbeef
    - (x) La pila del modo Supervisor (SVC) debe ser la última
    - ( ) La pila del modo Supervisor (SVC) debe ser la primera
    - ( ) El orden en el que se inicialicen las diferentes pilas es irrelevante

2. ¿A qué dirección de memoria está mapeado el cargador de la Econotag?
    - ( ) La placa Econotag no tiene ningún cargador
    - (x) 0x00000000
    - ( ) 0x00400000
    - ( ) 0x80000000

3. El resultado final de la construcción del BSP es...
    - ( ) Un fichero objeto
    - (x) Una biblioteca
    - ( ) Un conjunto de ficheros objeto
    - ( ) El firmware que se ejecutará en el sistema empotrado

4. A la hora de diseñar una aplicación que haga uso del BSP, el linker script...
    - ( ) Sólo es necesario si se escribe la aplicación en ensamblador
    - ( ) Ya no es necesario
    - ( ) Se debe diseñar completamente en función de las características de la aplicación
    - (x) Forma parte del BSP, por lo que simplemente hay que usarlo para enlazar la aplicación con el código del BSP. A lo sumo, sólo será necesario cambiar el tamaño de las pilas en algunos casos muy concretos

5. ¿Para que utilizamos la herramienta bbmc?
    - ( ) Esa herramienta no se usa en esta asignatura
    - (x) Borrar la memoria flash de la placa
    - ( ) Flashear la placa
    - ( ) Cargar una imagen a la placa

6. Indica cuál de las siguientes partes del cargador del BSP desarrollado en las prácticas se podría realizar en C
    - ( ) La carga de la imagen ejecutable en la RAM
    - (x) La inicialización de los dispositivos de E/S
    - ( ) La inicialización de las pilas
    - ( ) La habilitación de interrupciones

7. Indica cuál de las siguientes opciones no es válida para cargar y ejecutar una imagen ejecutable en la RAM de la Econotag
    - ( ) Mandar la imagen por el puerto serie desde el PC a la placa y resetearla
    - (x) Mandar la imagen por el puerto serie desde el PC a la placa
    - ( ) Conectar la placa al PC y subir la imagen a la memoria de la placa y ejecutarla usando órdenes de OpenOCD
    - ( ) Encender la placa después de haber grabado la imagen en su memoria flash

8. Si se usa nuestro cargador para ejecutar una aplicación en la Econotag, ¿Qué ocurrirá si la función main de la aplicación retorna?
    - (x) El sistema se cuelga
    - ( ) La función main nunca retornará
    - ( ) Se provoca una excepción
    - ( ) Se vuelve a cargar todo como al inicio y se ejecuta la aplicación

9. Indica cuál es el único símbolo que es necesario definir en el script de enlazado del BSP de la Econotag
    - ( ) _data_start
    - ( ) _bss_start
    - ( ) _text_start
    - (x) _bss_end

10. Indica cuál de los siguientes componentes del BSP no es necesario para su construcción
    - (x) Un sistema de ficheros en disco
    - ( ) El script de enlazado
    - ( ) El cargador crt0.s
    - ( ) Los manejadores de excepción

11. El fichero que contiene el cargador del BSP es
    - (x) hal/crt0.s
    - ( ) hal/loader.c
    - ( ) bsp/main.s
    - ( ) drivers/boot.s

12. ¿A qué sección emite el compilador las constantes globales de un fichero con código C?
    - (x) .rodata
    - ( ) .data
    - ( ) .bss
    - ( ) .text

13. Indica cual de las siguientes tareas no está soportada por el cargador de la ROM de la Econotag y es necesario implementarla en el del BSP
    - (x) Dar soporte a las excepciones e inicializar las pilas
    - ( ) Cargar el código desde Flash a RAM
    - ( ) Saltar a la dirección de inicio
    - ( ) Comprobar la cabecera binaria

14. A la hora de diseñar el script de enlazado del BSP para la Econotag, para aquellas secciones que se copiarán de la Flash a la RAM...
    - (x) Es necesario indicar tanto las direcciones VMA como las LMA
    - ( ) Solamente es necesario indicar las direcciones VMA
    - ( ) Solamente es necesario indicar las direcciones LMA
    - ( ) No se permite definir secciones copiadas a RAM

15. El cargador de la ROM de la Econotag...
    - (x) No inicializa el puntero de pila de ninguno de los modos de ejecución del procesador
    - ( ) Inicializa las pilas de todos los modos privilegiados
    - ( ) Configura la pila del modo User en RAM
    - ( ) Inhabilita el uso de la memoria RAM

16. De todas estas tareas, indica cual es la primera que debe ejecutar el cargador para que la aplicación se pueda ejecutar correctamente
    - (x) Inicializar las pilas
    - ( ) Inicializar la RAM
    - ( ) Llamar a main()
    - ( ) Habilitar las interrupciones

17. Indica la dirección de memoria a la que estará mapeada la tabla de vectores de excepción que se define en el fichero crt0.s de nuestro BSP
    - (x) 0x00400000
    - ( ) 0x00800000
    - ( ) 0x80000000
    - ( ) 0x00000000

