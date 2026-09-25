# Sistemas Empotrados - Test Práctica 1: Entorno de Desarrollo y Herramientas

- **Descripción:** Preguntas Tipo Test de la Práctica 1: Cadena de herramientas de compilación cruzada GNU (arm-none-eabi), binutils y placa RedBee Econotag.

---

1. Indica a qué pin del GPIO está conectado el led rojo de la placa. Puedes consultar el esquemático de la placa
    - ( ) GPIO52
    - ( ) GPIO59
    - (x) GPIO44
    - ( ) GPIO45

2. ¿Cómo configurarías el GPIO para que se puedan encender y apagar los leds rojo y verde mediante software?
    - ( ) GPIO_PAD_DIR_RESET1 <- 0x00003000
    - (x) GPIO_PAD_DIR_SET1 <- 0x00003000
    - ( ) GPIO_PAD_DIR_RESET0 <- 0x00003000
    - ( ) GPIO_PAD_DIR_SET0 <- 0x00003000

3. Para conectarnos a la interfaz de ordenes de OpenOCD debemos...
    - ( ) Mandar la orden soft_reset_halt
    - ( ) Lanzar el Eclipse y crear una configuración de depuración para que se conecte a OpenOCD
    - (x) Hacer un telnet a localhost:4444
    - ( ) Hacer un telnet a localhost:3333

4. La orden de OpenOCD load_image...
    - ( ) Carga un fichero ELF en la memoria de la placa
    - ( ) Carga un fichero ELF en la memoria de la placa y lo ejecuta
    - (x) Carga una imagen en formato binario en la memoria de la placa
    - ( ) Carga una imagen en formato binario en la memoria de la placa y la ejecuta

5. Asumiendo que los pines a los que están conectados los leds rojo y verde están configurados como de salida, ¿cómo apagarías el led verde?
    - ( ) GPIO_DATA_RESET1 <- 13
    - ( ) GPIO_DATA_SET1 <- 0xffffdfff
    - (x) GPIO_DATA_RESET1 <- 0x00002000
    - ( ) GPIO_DATA_SET1 <- 0x00002000

6. Asumiendo que los pines a los que están conectados los leds rojo y verde están configurados como de salida, ¿cómo encenderías el led verde?
    - ( ) GPIO_DATA_SET1 <- 0x00010000
    - ( ) GPIO_DATA_RESET1 <- 0x00010000
    - (x) GPIO_DATA_SET1 <- 0x00002000
    - ( ) GPIO_DATA_RESET1 <- 0x00002000

7. Indica a qué pin del GPIO está conectado el temporizador 2 (TMR2). Puedes consultar el esquemático de la placa
    - ( ) GPIO9
    - ( ) GPIO11
    - (x) GPIO10
    - ( ) GPIO8

8. Asumiendo que los pines a los que están conectados los leds rojo y verde están configurados como de salida, ¿cómo encenderías el led rojo?
    - ( ) GPIO_DATA1 <- 12
    - ( ) GPIO_DATA1 <- 0xffffefff
    - (x) GPIO_DATA1 <- 0x00001000
    - ( ) GPIO_DATA0 <- 0x00001000

9. OpenOCD...
    - ( ) Permite hacer un telnet a la placa de desarrollo
    - ( ) Es un demonio de depuración que se ejecuta en la placa de desarrollo para permitir la depuración de programas
    - (x) Proporciona una interfaz estándar entre el depurador y casi cualquier placa de desarrollo
    - ( ) Es un depurador de código a bajo nivel

10. Asumiendo que los pines a los que están conectados a los leds rojos y verdes están configurados como de salida,¿Como apagarias los dos leds?
    - (x) GPIO_DATA1 <- 0
    - ( ) 1
    - ( ) 1
    - ( ) 1

11. La orden de OpenOCD mww 0x80000054 0x00002000
    - (x) Apaga el led verde.
    - ( ) 1
    - ( ) 1
    - ( ) 1

12. Indica a que pin de GPIO está conectado el temporizador 2 (TMR2)
    - (x) GPIO10
    - ( ) 1
    - ( ) 1
    - ( ) 1

13. La orden de OpenOCD mww 0x80000054 0x00002000"
    - (x) Apaga el led verde
    - ( ) Fija el pin conectado al led verde como de entrada
    - ( ) Enciende el led rojo
    - ( ) Fija el pin conectado al led rojo como de salida

14. Asumiendo que los pines a los que están conectados los leds rojo y verde están configurados como de salida, ¿cómo apagarías los dos leds? Puedes consultar el esquemático de la placa (https://github.com/malvira/econotag) y el manual de referencia del procesador (http://www.freescale.com/files/rf_if/doc/ref_manual/MC1322xRM.pdf)
    - ( ) GPIO_DATA1 <- 0x00003000
    - ( ) GPIO_DATA0 <- 0xffffcfff
    - (x) GPIO_DATA1 <- 0
    - ( ) GPIO_DATA0 <- 0x00003000

