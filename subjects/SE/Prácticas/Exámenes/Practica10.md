# Sistemas Empotrados - Test Práctica 10: Drivers de Dispositivo e Integración con Newlib

- **Descripción:** Preguntas Tipo Test de la Práctica 10: Integración con la biblioteca Newlib, redirección de E/S estándar (stdin, stdout, stderr), descriptores y llamadas a sistema (open, close, read, write, lseek).

---

1. La E/S estándar en C consiste en...
    - ( ) Acceder a los dispositivos mediante interrupciones
    - ( ) Facilitar un acceso a los dispositivos basado en búferes
    - (x) Acceder a los dispositivos del sistema como si fueran ficheros
    - ( ) Acceder a los dispositivos de forma transparente

2. Indica cual de las siguientes opciones representa una llamada a sistema en Newlib
    - ( ) _open
    - ( ) memcpy
    - (x) open
    - ( ) _memcpy

3. ¿Sobre qué dispositivo están abiertos los ficheros estándar stdin, stdout y stderr antes de que en el proceso de inicialización se registre la uart1 y se redirijan a este dispositivo?
    - ( ) /dev/console
    - ( ) /dev/zero
    - (x) /dev/null
    - ( ) Inicialmente no están abiertos sobre ningún dispositivo

4. Indica cual de las siguientes opciones no es un fichero de E/S estándar
    - ( ) stdin
    - ( ) stdout
    - (x) stddev
    - ( ) stderr

5. Si un periférico no se ha registrado en el BSP como un dispositivo...
    - ( ) No podrá usarse por la aplicación
    - ( ) Sólo podrá accederse a dicho dispositivo en ensamblador
    - (x) No podrá ser accedido mediante funciones de E/S estándar
    - ( ) Sólo podrá gestionarse mediante el acceso directo de la aplicación a sus registros de control/estado

6. En caso de éxito, la llamada a sistema read retornará...
    - ( ) La función read no retorna ningún valor
    - ( ) -1
    - (x) El número de bytes que se han podido leer del fichero
    - ( ) El número de bytes que la función llamadora quería leer

7. Indica en cual de las siguientes llamadas a sistema no se usa la implementación mínima por defecto para las uart de la Econotag
    - ( ) close
    - ( ) isatty
    - (x) Read
    - ( ) lseek

8. A la hora de registrar un dispositivo en el BSP...
    - ( ) Es necesario indicar explícitamente una implementación para cada una de las llamadas a sistema
    - ( ) Sólo es necesario indicar el nombre que se usará para acceder a dicho dispositivo
    - (x) Sólo hay que indicar aquellas llamadas a sistema que tengan un comportamiento diferente para el dispositivo que el de la implementación mínima por defecto.
    - ( ) Siempre hay que indicar, como mínimo, la implementación explícita para las llamadas a sistema read y write

9. Indica en cual de los siguientes ficheros de Newlib se encuentra la implementación de la función printf
    - ( ) stdio.h
    - ( ) printf.h
    - (x) libc.a
    - ( ) stdlib.h

10. Supongamos que se llama a la función estándar lseek, que posiciona el cursor dentro de un fichero, usando como argumento el fichero stdout, que está definido sobre una uart del sistema. Si las uart del sistema no tienen definida una implementación para la función lseek en la tabla de dispositivos del sistema, ¿qué debe hacer la implementación de la función stub de lseek?
    - ( ) Retornar con error
    - ( ) Todos los dispositivos deben tener definidas implementaciones de todas las llamadas a sistema
    - (x) Ejecutar la implementación mínima por defecto de la función lseek
    - ( ) Generar una excepción y abortar la ejecución de la aplicación

11. ¿Cuántos ficheros se pueden abrir sobre una uart?
    - ( ) Sólo uno
    - ( ) Sólo tres
    - ( ) Ninguno
    - (x) Todos los que queramos

12. A la hora de registrar un dispositivo en el BSP...
    - ( ) Sólo es necesario indicar el nombre que se usará para acceder a dicho dispositivo
    - ( ) Siempre hay que indicar, como mínimo, la implementación explícita para las llamadas a sistema read y write
    - ( ) Es necesario indicar explícitamente una implementación para cada una de las llamadas a sistema
    - (x) Sólo hay que indicar aquellas llamadas a sistema que tengan un comportamiento diferente para el dispositivo que el de la implementación mínima por defecto.

13. Los descriptores de fichero son de tipo...
    - ( ) int *
    - ( ) File
    - ( ) FILE *
    - (x) int

14. Indica cual de las siguientes opciones no es un fichero de E/S estándar
    - ( ) stdout
    - ( ) stderr
    - ( ) stdin
    - (x) stddev

15. Si un periférico no se ha registrado en el BSP como un dispositivo...
    - ( ) Sólo podrá accederse a dicho dispositivo en ensamblador
    - ( ) Sólo podrá gestionarse mediante el acceso directo de la aplicación a sus registros de control/estado
    - ( ) No podrá usarse por la aplicación
    - (x) No podrá ser accedido mediante funciones de E/S estándar

16. En caso de éxito, la llamada a sistema open retornará...
    - ( ) -1
    - ( ) La función open no retorna ningún valor
    - ( ) 0
    - (x) El descriptor de fichero abierto por la función

17. Supongamos que se llama a la función estándar lseek, que posiciona el cursor dentro de un fichero, usando como argumento el fichero stdout, que está definido sobre una uart del sistema. Si las uart del sistema no tienen definida una implementación para la función lseek en la tabla de dispositivos del sistema, ¿qué debe hacer la implementación de la función stub de lseek?
    - ( ) Todos los dispositivos deben tener definidas implementaciones de todas las llamadas a sistema
    - ( ) Generar una excepción y abortar la ejecución de la aplicación
    - ( ) Retornar con error
    - (x) Ejecutar la implementación mínima por defecto de la función lseek

18. En caso de que una llamada a sistema de Newlib falle su valor de retorno será...
    - ( ) El código de error
    - ( ) Las llamadas a sistema no deben fallar nunca
    - ( ) 0
    - (x) -1

19. ¿Dónde se debe hacer la llamada a la función bsp_register_dev del BSP?
    - ( ) Al principio del código de la aplicación
    - ( ) En el fichero hal/dev.c
    - (x) Al final de su función de inicialización
    - ( ) En la aplicación, justo antes de usar el dispositivo

20. En caso de éxito, la llamada a sistema read retornará
    - ( ) El n.o de bytes que la función llamadora quería leer
    - (x) El n.o de bytes que se han podido leer del fichero
    - ( ) -1
    - ( ) La función read no retornará ningún valor.

21. Indica en cual de las siguientes llamadas a sistema no se usa la implementacion minima por defecto para las uart de la Econotag.
    - ( ) lseek
    - (x) Read
    - ( ) isatty
    - ( ) close

22. En caso de éxito, la llamada a sistema open retornará
    - ( ) La función open no retornará ningún valor
    - (x) El descriptor de fichero abierto por la funcion
    - ( ) -1
    - ( ) 0

23. Los descriptores de fichero son de tipo...
    - ( ) File
    - (x) int
    - ( ) Int *
    - ( ) FILE *

24. ¿Sobre qué dispositivo están abiertos los ficheros estándar stdin,stdout y stderr antes de que en el proceso de inicialización se registre la uart1 y se redirijan a este dispositivo?
    - ( ) Inicialmente no están abiertos sobre ningun dispositivo.
    - (x) /dev/null
    - ( ) /dev/zero
    - ( ) /dev/console

25. ¿Donde se debe hacer la llamada a la funcion bsp_register_dev del BSP?
    - ( ) En el fichero hal/dev.c
    - ( ) En la aplicación, justo antes de usar el dispositivo.
    - ( ) Al principio del código de la aplicación
    - (x) Al final de su función de inicialización

26. Indica en cual de los siguientes ficheros de Newlib se encuentra la implementacion de la funcion printf
    - ( ) Stdlib.h
    - (x) Libc.a
    - ( ) Print.h
    - ( ) Stdio.h

27. En caso de que una llamada a sistema de Newlib falle su valor de retorno será
    - ( ) Las llamadas a sistema no deben de fallar nunca
    - (x) -1
    - ( ) El código de error
    - ( ) 0

28. Supongamos que se llama a la función lseek, que posiciona el cursor dentro de un fichero, usando como argumento el fichero stdout, que está definido sobre una uart del sistema. Si las uart del sistema no tienen definida una implementacion para la funcion lseek en la tabla de dispositivos del sistema, ¿qué debe hacer la implementacion de la funcion slub de lseek?
    - ( ) Generar una excepcion y abortar la ejecución de la aplicación
    - (x) Ejecutar la implementación minima por defecto de la funcion lseek
    - ( ) Todos los dispositivos deben tener definidas implementaciones de todas las llamadas a sistema.
    - ( ) Retornar con error.

29. A la hora de registrar un dispositivo en el BSP....
    - ( ) Siempre hay que indicar, como minimo, la implementacion explicita para las llamadas a sistema read y write.
    - (x) tengan un corpontamiento diferente para el dispositivo que el de la implementacion minima por defecto.
    - ( ) Solo es necesario indicar el nombre que se usará para acceder a dicho dispositivo.
    - ( ) Es necesario indicar explicitamente para cada una de las llamadas a sistema.

