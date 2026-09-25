# Sistemas Empotrados - Test Práctica 5: Excepciones y Tabla de Manejadores

- **Descripción:** Preguntas Tipo Test de la Práctica 5: Gestión de excepciones en el BSP, tabla de manejadores de excepción y cambio de modos del procesador ARM.

---

1. Los manejadores de excepción...
    - ( ) Se deben declarar en el fichero excep.c del BSP
    - (x) Forman parte del código de la aplicación
    - ( ) No se pueden cambiar por la aplicación
    - ( ) Forman parte del BSP, pero deben declararse en un fichero aparte

2. Indica qué opción es la que debe usar el desarrollador de aplicaciones para instalar la función my_handler como un manejador personalizado para las excepciones de tipo Undefined Exception
    - ( ) _excep_handlers[excep_undef] = my_handler;
    - ( ) __attribute__ ((interrupt ("UNDEF"))) void my_handler (void)
    - (x) excep_set_handler (excep_undef, my_handler);
    - ( ) excep_set_handler (my_handler);

3. La función excep_disable_ints ()...
    - ( ) Retorna el valor que tenían los bits I y F antes de fijarlos a 0
    - (x) Retorna el valor que tenían los bits I y F antes de fijarlos a 1
    - ( ) Fija los bits I y F a 0 y no retorna nada
    - ( ) Fija los bits I y F a 1 y no retorna nada

4. ¿En qué dirección de memoria RAM estará la tabla de manejadores una vez que se haya cargado la imagen ejecutable en la placa?
    - ( ) 0x00000020
    - ( ) 0x00000000
    - (x) 0x00400020
    - ( ) 0x00400000

5. Indica el fichero del BSP en el que están definidos todos los tipos de excepción de la arquitectura ARM
    - (x) en include/excep.h
    - ( ) en include/system.h
    - ( ) en hal/excep.c
    - ( ) en hal/crt0.s

6. ¿Qué contiene cada una de las entradas de la tabla de manejadores de excepción?
    - ( ) El argumento que se pasará el manejador
    - ( ) Un puntero a una lista de argumentos para el manejador
    - (x) Un puntero a una función
    - ( ) Una instrucción ejecutable

7. Indica qué opción es la correcta para insertar una instrucción no definida en un programa escrito en C
    - ( ) asm(".data.word 0x26889912\n");
    - ( ) asm(".data 0x26889912\n");
    - (x) asm(".word 0x26889912\n");
    - ( ) .word 0x26889912

8. Indica cual de las siguientes opciones declara correctamente en C un manejador para una excepción de tipo Undefined Instruction
    - ( ) __attribute__ ((exception ("UNDEF"))) void my_handler (void)
    - ( ) __attribute__ (exception) void my_handler (void)
    - (x) __attribute__ ((interrupt ("UNDEF"))) void my_handler (void)
    - ( ) void my_handler (void)

9. Si insertamos una instrucción no definida en nuestro programa, pero se nos olvida instalar un manejador para que gestione la excepción cuando se trate de ejecutar dicha excepción...
    - ( ) El procesador no atenderá la excepción al no tener definido un manejador que la gestione
    - (x) Se usará el manejador por defecto definido en el BSP
    - ( ) Provocará un resultado totalmente aleatorio
    - ( ) Se reseteará el procesador

10. La instrucción msr...
    - ( ) Copia el registro cpsr registro de estado en un registro de propósito general
    - (x) Copia un registro de propósito general en un registro de estado
    - ( ) No existe en el repertorio de instrucciones del ARM7TDMI
    - ( ) Copia el registro spsr registro de estado en un registro de propósito general

11. Indica el fichero del BSP en el que está definida la tabla de manejadores
    - (x) hal/crt0.s
    - ( ) drivers/uart.c
    - ( ) system/newlib.c
    - ( ) main.c

