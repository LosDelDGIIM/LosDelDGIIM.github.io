# Sistemas Empotrados - Test Práctica 8: UART y Temporizadores (Capa L0)

- **Descripción:** Preguntas Tipo Test de la Práctica 8: Controladores de periféricos, registros de la UART, temporizadores y driver básico de capa L0.

---

1. En el registro UTxCON de las UART de la Econotag, el campo Tx_fifo_addr_diff...
    - ( ) Indica cuántos bytes están actualmente almacenados en la cola FIFO de envío, pendientes de ser enviados
    - (x) Indica el número de huecos libres en la cola FIFO de envío de la UART
    - ( ) Indica el número de huecos libres en la cola FIFO de recepción de la UART
    - ( ) Indica cuántos bytes están actualmente almacenados en la cola FIFO de recepción

2. La aplicación para probar el driver L0 que se propone en la práctica debe cambiar el estado de los leds de la Econotag (de encendido a apagado y viceversa) según los caracteres que se reciban por la UART. Si la placa recibe una 'r' (cambiar el estado del led rojo), ¿cómo sabe la aplicación si el led está encendido o apagado para poder cambiar su estado?
    - ( ) Consultando el estado del botón de la placa que se usa para encender y apagar el led
    - ( ) Consultando el registro de datos del GPIO correspondiente al led
    - (x) Consultando la variable de la aplicación que guarda el estado del led
    - ( ) Consultando el pin del GPIO al que esté conectado el led

3. ¿Qué registro se usa para fijar la frecuencia de las UART de la Econotag?
    - ( ) UBRINC
    - ( ) UBRMOD
    - ( ) UCON
    - (x) UBR

4. Para poder utilizar la UART es necesario fijar la función de sus pines a...
    - ( ) gpio_func_alternate_3
    - ( ) gpio_func_normal
    - ( ) gpio_func_alternate_2
    - (x) gpio_func_alternate_1

5. En la lección de teoría se explica el diseño de la estructura de datos uart_regs_t, que permitirá acceder de forma cómoda a los registros de las UART de la Econotag. Sin embargo, aunque se ofrecen los detalles de la mayoría de los registros, se omiten algunos, de forma que los estudiantes puedan demostrar en la práctica que saben completar la estructura de datos con los registros que faltan. De los siguientes registros, indique cual no se detalla en teoría y es necesario que el estudiante lo añada a la estructura.
    - ( ) UDATA
    - ( ) UBR
    - ( ) UCON
    - (x) USTAT

6. En la función de inicialización de la UART de la Econotag...
    - ( ) La frecuencia de operación de la UART se puede establecer en cualquier punto de la función
    - (x) La frecuencia de operación de la UART se debe establecer con su transmisor y su receptor apagados
    - ( ) La frecuencia de operación de la UART se debe establecer con su transmisor y su receptor encendidos
    - ( ) No se establece la frecuencia de operación de la UART

7. Para mandar un carácter mediante la UART de la Econotag...
    - ( ) Se escribe el carácter directamente en la cola FIFO de envío
    - ( ) Se debe comprobar si hay algún hueco en la cola de envío, y si es así, se escribe el carácter en el primer hueco disponible
    - ( ) Solamente es necesario escribirlo en el registro de datos de la UART
    - (x) Es necesario comprobar que hay algún hueco en la cola FIFO de envío antes de escribirlo en el registro de datos de la UART

8. ¿Cuántas UART tiene la Econotag?
    - ( ) 3
    - ( ) 0
    - ( ) 1
    - (x) 2

9. Si se ha usado OpenOCD para subir una aplicación a la placa Econotag y dicha aplicación usa la UART1 para comunicarse con el PC, ¿qué puerto serie se debe indicar en el emulador de terminal para poder conectar con la UART de la placa?
    - ( ) /dev/ttyUSB2
    - ( ) /dev/ttyUSB3
    - ( ) /dev/ttyUSB0
    - (x) /dev/ttyUSB1

10. Para poder configurar la función de los pines de E/S que se usarán por una UART de la Econotag es necesario que...
    - ( ) Se haya configurado la dirección de los pines
    - ( ) Se haya fijado la frecuencia de operación
    - ( ) La UART esté apagada
    - (x) La UART esté habilitada

11. En el registro URxCON de las UART de la Econotag, el campo Rx_fifo_addr_diff...
    - (x) Indica cuántos bytes han sido recibidos y están actualmente almacenados en la cola FIFO de recepción
    - ( ) Indica la dirección base del búfer de recepción en memoria
    - ( ) Configura la tasa de baudios de recepción
    - ( ) Indica el número de errores de paridad detectados

12. ¿Se puede enviar una cadena de caracteres usando sólo las funciones de la capa L0 del driver de la UART?
    - (x) Sí, con ayuda de un bucle que vaya recorriendo la cadena carácter a carácter llamando a la función de envío de un byte
    - ( ) No, es imprescindible el uso de un driver L1 con interrupciones
    - ( ) No, la capa L0 solo permite recibir datos
    - ( ) Solo si la longitud de la cadena es menor o igual a 4 bytes

