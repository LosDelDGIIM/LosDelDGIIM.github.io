# Sistemas Empotrados - Test Tema 4: Excepciones e Interrupciones

- **Descripción:** Preguntas Tipo Test correspondientes al Tema 4: Sistema de Excepciones e Interrupciones (Vectores de excepción, pines nIRQ/nFIQ, manejadores N0/N1, interrupciones anidadas y regiones críticas).

---

1. Cuando se provoca una excepción, el procesador almacena en lr la dirección de retorno antes de pasar a ejecutar su manejador. Por lo tanto, a la hora de escribir un manejador de excepción, para poder retornar a la aplicación...
    - (x) Es necesario ajustar el registro lr en función del tipo de excepción antes de retornar
    - ( ) Sólo es necesario copiar el contenido del registro lr en el registro pc
    - ( ) Siempre hay que restar 4 bytes al registro lr antes de retornar
    - ( ) Se debe usar la instrucción ret, que se encargará de hacer el ajuste de lr y retornar

2. Indica cuál de las siguientes opciones define correctamente un tipo de datos adecuado para poder gestionar en C la instalación de manejadores de excepción en el BSP
    - ( ) typedef void (* excep_handler_t) (int);
    - ( ) typedef int (* excep_handler_t) (void);
    - ( ) typedef int (* excep_handler_t) (int);
    - (x) typedef void (* excep_handler_t) (void);

3. Teniendo en cuenta que la arquitectura del ARM7TDMI tiene 8 vectores de excepción, la dirección del vector FIQ es...
    - ( ) 0x00000028
    - ( ) 0x00000032
    - ( ) 0x00000020
    - (x) 0x0000001C

4. Conforme más dispositivos hay en el sistema, la latencia de las interrupciones...
    - ( ) Aumenta sólo si hay controlador de interrupciones
    - ( ) Siempre aumenta
    - ( ) Siempre disminuye
    - (x) Aumenta sólo si no hay controlador de interruciones

5. Indica qué relación existe entre las excepciones y los modos de ejecución de los procesadores ARM
    - (x) Algunos modos de ejecución privilegiados son compartidos por excepciones similares
    - ( ) Existe un único modo privilegiado para todas las excepciones y un modo user para ejecutar las aplicaciones
    - ( ) Cada tipo de excepción tiene asociado un modo de ejecución privilegiado diferente
    - ( ) Los procesadores ARM no tienen modos privilegiados

6. En el diseño jerárquico del mecanismo de atención de interrupciones de un BSP, la implementación de las ISR depende de...
    - (x) El dispositivo que ha solicitado la interrupción
    - ( ) La arquitectura del procesador del sistema
    - ( ) El controlador de interrupciones del sistema
    - ( ) La tabla de vectores de excepción

7. Cuando llega a la CPU una petición de interrupción FIQ, ¿cómo se identifica la fuente?
    - ( ) Mediante el controlador de interrupciones
    - ( ) Mediante el manejador de nivel 1
    - ( ) Mediante el manejador de nivel 0
    - (x) No es necesario identificar la fuente

8. Si nuestro sistema dispone de un controlador de interrupciones vectorizado...
    - ( ) La priorización de interrupciones se debe implementar en software
    - ( ) La búsqueda de la ISR de la fuente más prioritaria se debe hacer en SW
    - ( ) No es necesario diseñar ISRs para los dispositivos
    - (x) El BSP no necesita de un manejador para buscar la ISR de la fuente de interrupción más prioritaria

9. Cuando se ejecute una aplicación, la existencia de una condición de carrera entre el código de la aplicación y el código del driver de un dispositivo...
    - (x) No siempre provocará resultados incorrectos
    - ( ) Siempre provocará resultados incorrectos
    - ( ) Siempre provocará resultados correctos
    - ( ) Es algo habitual en los sistemas gestionados mediante interrupciones

10. En un sistema con soporte para interrupciones anidadas...
    - (x) El dispositivo más prioritario siempre será atendido por la CPU
    - ( ) Cualquier dispositivo podrá interrumpir el servicio de una interrupción
    - ( ) La ISR del dispositivo más prioritario podrá ser interrumpida por otra fuente de interrupción
    - ( ) Las peticiones de interrupción se atienden según el orden en el que se hayan producido

11. Indica en qué parte del registro cpsr se encuentran los flags de estado (signo, acarreo, overflow y cero)
    - (x) Bits 24-31 (o 28-31 para los flags de condición N, Z, C, V)
    - ( ) Bits 0-7
    - ( ) Bits 8-15
    - ( ) Bits 16-23

12. ¿Qué relación existe entre las excepciones y las interrupciones?
    - (x) Una interrupción es un tipo de excepción producida por un evento hardware externo
    - ( ) Son conceptos totalmente independientes y no relacionados
    - ( ) Todas las excepciones son provocadas por dispositivos externos
    - ( ) Las interrupciones solo ocurren en modo User y las excepciones en modo Supervisor

13. La modificación de los bits I y F del registro de estado de la CPU...
    - (x) Se debe hacer en ensamblador porque las instrucciones de gestión del registro CPSR no se pueden generar en C
    - ( ) Se puede realizar mediante una simple asignación a un puntero en C
    - ( ) No está permitida en ningún modo de ejecución privilegiado
    - ( ) Se produce de forma automática al invocar a cualquier función del BSP

14. Indica cuántos pines dedican los procesadores ARM a la atención de interrupciones de dispositivos externos
    - (x) 2 (nIRQ y nFIQ)
    - ( ) 4
    - ( ) 8
    - ( ) 16

15. En el diseño jerárquico del mecanismo de atención de interrupciones de un BSP, la implementación del manejador de nivel 0 depende de...
    - (x) La arquitectura del procesador del sistema
    - ( ) El controlador de interrupciones del sistema
    - ( ) Los periféricos concretos que se conecten en la placa
    - ( ) La aplicación de usuario

16. Indica cuál de las siguientes excepciones está directamente relacionada con la gestión de dispositivos de E/S
    - (x) Interrupt ReQuest (IRQ)
    - ( ) Undefined Instruction
    - ( ) Prefetch Abort
    - ( ) Software Interrupt (SWI)

17. Cuando el BSP implementa un esquema de gestión de interrupciones anidadas, ¿en qué modo de ejecución estará el procesador cuando ejecute la ISR de un dispositivo?
    - (x) Supervisor (SVC)
    - ( ) IRQ
    - ( ) User
    - ( ) FIQ

18. Si en el script de enlazado del BSP se ha definido el símbolo _excep_handlers para indicar la dirección de memoria en la que estará la tabla de manejadores de excepción del BSP, y en el fichero excep.h se ha definido el tipo _excep_handler_t para poder gestionar los manejadores de excepción, indica cual de las siguientes declaraciones es la que permite acceder correctamente a la tabla de manejadores desde C
    - (x) extern excep_handler_t _excep_handlers[];
    - ( ) extern excep_handler_t * _excep_handlers();
    - ( ) excep_handler_t _excep_handlers;
    - ( ) static excep_handler_t _excep_handlers[];

19. En el diseño jerárquico del mecanismo de atención de interrupciones de un BSP, la implementación del manejador de nivel 0 depende de...
    - (x) La arquitectura del procesador del sistema
    - ( ) SASA

20. Para poder identificar la fuente más prioritaria de una petición de interrupción en un sistema...
    - (x) No es necesario que el sistema disponga de un controlador de interrupciones (puede resolverse mediante sondeo/polling en software)
    - ( ) Es imprescindible contar con un controlador de interrupciones vectorial en hardware
    - ( ) Es necesario que todos los dispositivos compartan la misma línea de interrupción
    - ( ) La CPU debe estar ejecutando siempre en modo FIQ

21. Indica qué fuente de interrupción tendrá la menor latencia en un sistema ARM
    - (x) Aquella fuente que esté conectada al pin nFIQ de la CPU
    - ( ) Aquella conectada a través del controlador de interrupciones al pin nIRQ
    - ( ) Cualquier interrupción generada por software (SWI)
    - ( ) Una interrupción por desbordamiento del temporizador en modo IRQ

22. Para poder gestionar una interrupción IRQ, y si no necesitamos interrupciones anidadas, es necesario escribir en ensamblador...
    - (x) Nada. Todo el tratamiento de interrupciones se puede escribir en C si el compilador soporta atributos de interrupción o el manejador N0 gestiona el contexto
    - ( ) Todo el código del driver y la aplicación en ensamblador
    - ( ) La rutina de servicio completa obligatoriamente en ensamblador
    - ( ) El código de inicialización de la UART obligatoriamente

23. Indica la opción que, evitando que la UART pueda interrumpir a la CPU cuando haya recibido un nuevo dato, implique la mínima degradación de las prestaciones del sistema
    - (x) Configurando el dispositivo para deshabilitar la petición de interrupciones debidas a la recepción de nuevos datos
    - ( ) Deshabilitando globalmente las interrupciones en la CPU con el bit I del CPSR
    - ( ) Desconectando físicamente el pin de la UART
    - ( ) Enmascarando todas las fuentes en el controlador de interrupciones

24. Indica en qué parte del registro cpsr se encuentran los bits de control (modo de ejecución, habilitación de interrupciones y thumb)
    - (x) Bits 0-7
    - ( ) Bits 8-15
    - ( ) Bits 16-23
    - ( ) Bits 24-31

25. La tabla de manejadores de excepción...
    - (x) No es necesaria para poder implementar un sistema que soporte la gestión de excepciones (es una abstracción software del BSP)
    - ( ) Es un componente hardware integrado dentro de la CPU ARM
    - ( ) Debe estar situada obligatoriamente en la dirección 0x00000000 de la ROM
    - ( ) Sustituye por completo a la tabla de vectores de excepción

26. Indica qué relación existe entre las prioridades de las excepciones Software Interrupt y Undefined Instruction
    - (x) Las dos tienen la misma prioridad
    - ( ) Tiene más prioridad la primera
    - ( ) Tiene más prioridad la segunda
    - ( ) Depende de la configuración del registro CPSR

27. Indica cuál de los siguientes eventos no provocará una excepción
    - (x) Que la CPU genere un valor tras una operación aritmética que no quepa en un registro (overflow)
    - ( ) Una instrucción no reconocida por el decodificador
    - ( ) Un acceso a una dirección de memoria no válida
    - ( ) Una petición externa a través de la línea nIRQ

28. El registro spsr...
    - (x) No existe en modo User
    - ( ) No existe en modo Supervisor
    - ( ) Contiene la dirección de retorno tras una llamada a subrutina
    - ( ) Es compartido por todos los modos sin duplicarse

29. El código de salida de una región crítica implementada a nivel de CPU debe...
    - (x) Restaurar el valor de los bits I y F al que tenían antes de entrar en la región crítica
    - ( ) Pone siempre los bits I y F a cero sin importar su estado previo
    - ( ) Cambiar el modo del procesador a modo User
    - ( ) Limpiar todos los flags de estado en el CPSR

30. En el diseño jerárquico del mecanismo de atención de interrupciones de un BSP, la implementación del manejador de nivel 1 depende de...
    - (x) El controlador de interrupciones del sistema
    - ( ) La arquitectura del procesador del sistema
    - ( ) El compilador de C utilizado
    - ( ) La aplicación de usuario

