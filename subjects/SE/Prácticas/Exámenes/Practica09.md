# Sistemas Empotrados - Test Práctica 9: Driver UART por Interrupciones (Capa L1)

- **Descripción:** Preguntas Tipo Test de la Práctica 9: Driver UART L1 basado en interrupciones, búferes circulares, funciones callback y regiones críticas.

---

1. La función de inicialización de la uart debe configurar el controlador de interrupciones para asignar las peticiones de interrupción de las uart a las entradas de interrupción de la CPU. ¿A cuál de ellas mapea cada uart?
    - ( ) Las dos uart a la entrada FIQ
    - ( ) La uart1 a la entrada IRQ y la uart2 a la entrada FIQ
    - ( ) La uart1 a la entrada FIQ y la uart2 a la entrada IRQ
    - (x) Las dos uart a la entrada IRQ

2. ¿Cómo sabe la ISR si la petición de interrupción de la uart se debe a la recepción de datos?
    - ( ) Consultando el número de bytes recibidos en la cola HW de recepción del dispositivo (campo Rx_fifo_addr_diff del registro RxCON)
    - ( ) Probando a leer datos de la cola HW del dispositivo
    - (x) Consultando el bit RxRdy del registro USTAT
    - ( ) Consultando el bit TxRdy del registro USTAT

3. En un driver L1, la función de envío bloqueante del driver de la uart...
    - ( ) Funcionará correctamente sin necesidad de modificación
    - ( ) Debe reescribirse para bloquearse si no hay huecos en la cola HW de envío
    - ( ) Debe reescribirse para que escriba el dato en el búfer de envío en lugar de en la cola HW del dispositivo
    - (x) Debe reescribirse para mandar a la cola HW de envío todos los caracteres del búfer circular de envío antes de encolar en la cola HW el carácter

4. En un driver L1, la función de recepción bloqueante del driver de la uart...
    - ( ) Debe ser modificada para mover todos los caracteres recibidos del búfer circular a la cola HW de recepción antes de pasar a bloquearse.
    - (x) Debe ser modificada para consultar si hay datos en el búfer de recepción antes de pasar a bloquearse hasta que llegue un nuevo dato a a la uart
    - ( ) Funcionará correctamente sin necesidad de ser modificada
    - ( ) Debe ser modificada para bloquearse si la cola HW de recepción está vacía

5. Dado que el driver L1 de la uart está basado en sendos búferes circulares de envío y recepción que son compartidos tanto por las funciones send y receive como por la ISR, es necesario que las funciones send y receive accedan a su búfer correspondiente dentro de una sección crítica para evitar condiciones de carrera con la ISR. Por lo tanto...
    - ( ) La uart no podrá interrumpir a la función receive nunca
    - ( ) La uart podrá interrumpir a la función receive si ha recibido nuevos datos
    - ( ) La uart podrá interrumpir a la función receive siempre
    - (x) La uart podrá interrumpir a la función receive si necesita datos para enviar

6. ¿En qué nivel inhibe/restaura interrupciones la función uart_send para acceder de forma segura al búfer de envío del driver de la uart?
    - (x) En la uart, inhibiendo/restaurtando la petición de interrupciones por parte de su transmisor
    - ( ) En el procesador del sistema, inhibiendo/restaurando la recepción de interrupciones en el registro de control
    - ( ) En el controlador de interrupciones, inhibiendo/restaurando las peticiones de interrupción de la uart.
    - ( ) No es necesario inhibir interrupciones para acceder al búfer

7. Una de las funcionalidades que añaden las funciones de nivel 1 de un driver es el chequeo de errores en los parámetros. En el caso de que algún parámetro sea erróneo, la función retornará...
    - ( ) 2
    - (x) -1
    - ( ) 0
    - ( ) 1

8. ¿Cómo sabe la ISR del driver de la uart si la aplicación ha instalado una función callback de recepción en la uart2?
    - ( ) La ISR no debe comprobar nada. El driver debe tener definidas callbacks para todas las uart del sistema
    - (x) Comprobando si el puntero a función almacenado en uart_callbacks[uart_2].rx_callback tiene un valor distinto de NULL
    - ( ) Comprobando si el puntero a función almacenado en uart_2_rx_callback tiene un valor distinto de NULL
    - ( ) Comprobando si el puntero a función almacenado en uart_rx_callbacks[uart_2] tiene un valor distinto de NULL

9. En la aplicación de prueba del driver L1 de la uart que se propone en el ejercicio de la práctica 9, El estado de los leds que deben parpadear se modifica en...
    - ( ) La función callback de envío
    - ( ) La ISR del driver de la uart
    - ( ) La aplicación
    - (x) La función callback de recepción

10. La función callback de recepción del driver de la uart es invocada por...
    - ( ) La uart
    - (x) La ISR del driver
    - ( ) La función uart_receive
    - ( ) Cualquier función de la aplicación

11. 2.Lo primero que debe hacer una ISR es reconocer que está sirviendo la interrupción para que el dispositivo deje de solicitar la atención de la CPU.¿Cómo reconoce la ISR de la uart de la Econotag que está atendiendo una peticion interrupcion causada por una recepcion de datos?
    - (x) Consultando los bits correspondientes en el registro USTAT
    - ( ) Escribiendo un 1 en el registro de control del ARM
    - ( ) Llamando a la función printf
    - ( ) Desactivando la alimentación del periférico

12. ¿Cómo sabe la ISR del driver de la uart si la aplicación ha instalado una función callback de recepción en la uart2?
    - ( ) Comprobando si el puntero a función almacenado en uart_callbacks[uart_2].rx_callback tiene un valor distinto de NULL
    - (x) asasa

13. En la aplicación de prueba del driver L1 de la uart que se propone en el ejercicio de la práctica 9, El estado de los leds que deben parpadear se modifica en...
    - (x) La función callback de recepción
    - ( ) La función main mediante espera activa
    - ( ) La función callback de envío
    - ( ) La rutina de reset

14. En un driver L1, la función de recepción bloqueante del driver de la uart..
    - (x) Debe ser modificada para consultar si hay datos en el búfer de recepción antes de pasar a bloquearse hasta que llegue un dato a la UART
    - ( ) Debe deshabilitar las interrupciones durante toda su ejecución
    - ( ) Debe leer directamente del registro HW sin consultar el búfer
    - ( ) No puede convivir con funciones de recepción no bloqueantes

15. ¿Qué hace la ISR de la uart en el caso de que el dispositivo solicite más datos para enviar pero no haya más datos en el bufer circular de envio del driver?
    - (x) Desactivar la petición de interrupciones del dispositivo debidas a falta de datos que enviar
    - ( ) Enviar caracteres nulos de relleno continuamente
    - ( ) Bloquear la CPU hasta que lleguen nuevos datos
    - ( ) Reiniciar la UART por completo

16. ¿Cuantas ISR hay definidas en el driver de la uart de la Econotag?
    - (x) 2
    - ( ) 1
    - ( ) 4
    - ( ) 5

17. En caso de éxito, ¿qué valor retorna la funcion uart send?
    - (x) El número de bytes que se han podido copiar al búfer circular de envío del driver
    - ( ) Siempre el valor 0
    - ( ) La dirección del búfer circular
    - ( ) Un puntero a la estructura uart_regs_t

18. ¿Cómo sabe la ISR si la petición de interrupción de la uart se debe a la recepción de datos?
    - (x) Consultando el bit RxRdy del registro USTAT.
    - ( ) dsds

19. ¿Cuántas ISR hay definidas en el driver de la uart de la Econotag?
    - (x) 2
    - ( ) 1
    - ( ) 3
    - ( ) 56

20. Indica qué código fijan las funciones del driver de la uart en la variable global errno en el caso de que reciban un identificador de uart no válido en el sistema
    - (x) ENODEV
    - ( ) EINVAL
    - ( ) EBADF
    - ( ) EIO

21. Lo primero que debe hacer una ISR es reconocer que está sirviendo la interrupción para que el dispositivo deje de solicitar la atención de la CPU. ¿Cómo reconoce la ISR de la uart de la Econotag que está atendiendo una petición interrupción causada por una recepción del datos?
    - (x) Leyendo los datos recibidos de la cola HW de la UART
    - ( ) Enviando una trama de confirmación por el puerto serie
    - ( ) Modificando el bit I del registro CPSR
    - ( ) Esperando a que el emisor finalice la transmisión

22. El uso de funciones callback...
    - (x) Mejora las prestaciones de E/S de la aplicación al permitir un desacoplo y notificación asíncrona
    - ( ) Obliga a que la aplicación realice espera activa sobre el dispositivo
    - ( ) Elimina la necesidad de utilizar interrupciones en el sistema
    - ( ) Solo puede emplearse en sistemas operativos de propósito general

23. ¿Cómo sabe la ISR si la petición de interrupción de la uart se debe a la recepción de datos?
    - (x) Consultando el bit RxRdy del registro USTAT
    - ( ) sdsfdgqwqw

24. ¿Qué hace la ISR de la uart en el caso de que el dispositivo solicite más datos para enviar pero no haya más datos en el búfer circular de envío del driver?
    - (x) Desactivar la petición de interrupciones del dispositivo debidas a falta de datos que enviar
    - ( ) tytyt

