# Sistemas Empotrados - Test Tema 5: Entrada/Salida, Drivers y BSP

- **Descripción:** Preguntas Tipo Test correspondientes al Tema 5: Entrada/Salida, Drivers y BSP (Estructuras de registros, drivers L0/L1, búferes circulares, integración con Newlib y llamadas al sistema).

---

1. Indica la forma correcta de portar a una placa como la Econotag las llamadas a sistema de la biblioteca Newlib necesarias para hacer E/S mediante el estándar POSIX
    - (x) Implementando las funciones stub _open, _close, _read, _write, _lseek, _isatty y _fstat
    - ( ) No es posible hacer uso de funciones Posix en una plataforma con tan pocos recursos
    - ( ) Implementando las funciones de E/S estándar printf y scanf
    - ( ) Implementando las llamadas a sistema open, close, read, write,lseek, isatty y fstat

2. Asumiendo que gpio_regs_t es un tipo de datos definido en el BSP para facilitar el acceso a los registros de control/estado del GPIO y que GPIO_BASE es un símbolo que contiene la dirección base de los registros del GPIO en el mapa de memoria de la placa, ¿cual de las siguientes declaraciones permite acceder correctamente en C a los registros del GPIO?
    - ( ) static volatile const gpio_regs_t* gpio_regs =GPIO_BASE;
    - ( ) static const gpio_regs_t* gpio_regs = GPIO_BASE;
    - ( ) static gpio_regs_t* const gpio_regs = GPIO_BASE;
    - (x) static volatile gpio_regs_t* const gpio_regs =GPIO_BASE;

3. ¿Se pueden modificar simultáneamente varios bits en un registro de control de un dispositivo?
    - ( ) Sí, mediante el uso de máscaras de bits para escribir en un campo de una estructura bitfields
    - ( ) No se puede
    - (x) Sí, mediante el uso de máscaras de bits para escribir en el registro
    - ( ) Sí, mediante la definición del registro como una estructura con bitfields

4. Indica cuál de las siguientes características no es propia de un driver L0
    - ( ) Configuración por defecto del dispositivo
    - ( ) Envío y recepción bloqueantes
    - ( ) E/S controlada por el programa
    - (x) Chequeo de errores

5. En el caso de que nuestro sistema tenga varias instancias de un tipo de dispositivo (por ejemplo dos UART), y los registros del mismo tipo (control, datos, etc.) de cada una de las instancias de dispositivo estén agrupadas en el mapa de memoria, ¿qué estructura es la más adecuada para gestionar los registros de los dispositivos?
    - (x) Una estructura de arrays
    - ( ) Un array de estructuras
    - ( ) Un array de punteros a estructuras
    - ( ) Una estructura de estructuras

6. Indica qué palabra clave es imprescindible a la hora de definir un puntero para poder acceder a los registros de configuración de un dispositivo
    - (x) volatile
    - ( ) register
    - ( ) static
    - ( ) static

7. Las operaciones de E/S de los drivers de nivel 1...
    - (x) Se apoyan en dos búferes circulares, uno para lectura y otro para escritura
    - ( ) Están basadas en el uso de ficheros estándarv
    - ( ) Usan un único búfer para almacenar las transferencias pendientes
    - ( ) Mandan y reciben los datos directamente hacia o desde el dispositivo

8. Indica cuál de las siguientes partes del BSP hace posible que se puedan usar las funciones C estándar fprintf o fscanf para hacer E/S formateada sobre la UART de un sistema empotrado
    - (x) El driver L2 de la UART
    - ( ) El driver del GPIO
    - ( ) El driver L1 de la UART
    - ( ) El driver L0 de la UART

9. Dado que los búferes circulares de un driver L1 se acceden concurrentemente por la ISR del driver y por las funciones de envío y recepción, es necesario gestionar su acceso mediante regiones críticas para evitar condiciones de carrera. Indica cual de las siguientes opciones define correctamente una región crítica para el acceso al búfer de recepción de un driver
    - (x) En la función receive. Se debe anular la generación de interrupciones de recepción antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso
    - ( ) En la función receive. Se debe enmascarar la atención de interrupciones en los bits I/F del registro de control de la CPU antes de acceder al búfer y restaurarla una vez que se ha terminado el acceso
    - ( ) En la ISR del dispositivo. Se debe anular la generación de interrupciones de recepción antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso
    - ( ) En la función receive. Se debe anular la generación de interrupciones por parte del dispositivo en el controlador de interrupciones antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso

10. En el caso de que nuestro sistema tenga varias instancias de un tipo de dispositivo (por ejemplo tres temporizadores), y cada uno de las instancias tenga sus propios registros agrupados a partir de una dirección base en el mapa de memoria, ¿qué estructura es la más adecuada para gestionar los registros de los dispositivos?
    - (x) Un array de punteros a estructuras
    - ( ) Un array de estructuras
    - ( ) Una estructura de arrays
    - ( ) Una estructura de estructuras

11. Indica cual de las siguientes funciones lee datos del búfer de envío de un driver L1
    - (x) La ISR del driver
    - ( ) La función de inicialización del driver
    - ( ) La función send del driver
    - ( ) La función receive del driver

12. Indica la forma correcta de portar a una placa como la Econotag las llamadas a sistema de la biblioteca Newlib necesarias para hacer E/S mediante el estándar POSIX
    - ( ) No es posible hacer uso de funciones Posix en una plataforma con tan pocos recursos
    - (x) Implementando las funciones stub _open, _close, _read, _write, _lseek, _isatty y _fstat
    - ( ) Implementando las llamadas a sistema open, close, read, write, lseek, isatty y fstat
    - ( ) Implementando las funciones de E/S estándar printf y scanf

13. En el mapa de memoria de un dispositivo se han dejado 32 bytes reservados. Indica la opción correcta rellenar dicho espacio en la estructura de datos que debe gestionar los registros de E/S de dicho dispositivo
    - (x) uint32_t padding [4]
    - ( ) uint32_t padding
    - ( ) uint32_t padding [32]
    - ( ) uint4_t padding [32]

14. Indica cuál de las siguientes opciones describe la forma correcta en la que se puede usar el BSP desarrollado en la asignatura para que una aplicación pueda hacer E/S concurrente mientras se está ejecutando
    - ( ) Haciendo uso de las funciones de envío y recepción basadas en búferes
    - (x) Desarrollando funciones callback de envío y recepción y registrándolas en el driver de la UART
    - ( ) Haciendo uso de las funciones de envío y recepción bloqueantes del driver
    - ( ) Escribiendo una ISR para la UART a la medida de la aplicación

15. En el caso de que nuestro sistema tenga varias instancias de un tipo de dispositivo (por ejemplo tres temporizadores), y cada uno de las instancias tenga sus propios registros agrupados a partir de una dirección base en el mapa de memoria, ¿qué estructura es la más adecuada para gestionar los registros de los dispositivos?
    - ( ) Un array de estructuras
    - (x) Un array de punteros a estructuras
    - ( ) Una estructura de estructuras
    - ( ) Una estructura de arrays

16. Indica cual de las siguientes funciones lee datos del búfer de envío de un driver L1
    - ( ) La función de inicialización del driver
    - (x) La ISR del driver
    - ( ) La función receive del driver
    - ( ) La función send del driver

17. Indica qué opción es más adecuada para acceder cómodamente en C a los registros de E/S de un dispositivo, suponiendo que sólo hay una instancia del dispositivo y que sus registros están mapeados a la memoria del sistema
    - ( ) Definiendo una estructura con campos de un tamaño adecuado para que se ajuste al mapa de registros del dispositivo
    - (x) Definiendo una estructura de datos que se ajuste al mapa de memoria de los registros del dispositivo y creando un puntero a dicha estructura que apunte a la base de los registros en el mapa de memoria
    - ( ) Mediante un puntero que apunte a la base de los registros de E/S del dispositivo
    - ( ) Mediante una colección de punteros que apunten a los diferentes registros del dispositivo

18. Indica cuál de las siguientes características no es propia de un driver L0
    - ( ) E/S controlada por el programa
    - (x) Chequeo de errores
    - ( ) Configuración por defecto del dispositivo
    - ( ) Envío y recepción bloqueantes

19. Si se invoca a una syscall de Newlib con descriptor de fichero no válido o bien con un descriptor de fichero abierto sobre un dispositivo que no tiene implementada dicha función...
    - ( ) Se abortará la ejecución de la aplicación
    - (x) Se ejecutará la implementación por defecto para dicha syscall
    - ( ) Este caso no es posible. Todos los dispositivos deben implementar todas las syscalls
    - ( ) Se retornará -1 y se fijará la variable global errno al valor adecuado

20. La lista de dispositivos del BSP...
    - ( ) Debe ser inicializada por la aplicación, en función de los dispositivos que necesite
    - (x) Almacena todos los dispositivos del sistema que se pueden tratar como ficheros junto con punteros a las funciones que implementan la interfaz POSIX de tratamiento de ficheros para cada dispositivo
    - ( ) Forma parte de la implementación del driver de nivel 1 de un dispositivo
    - ( ) Asocia descriptores de fichero a los diferentes dispositivos del sistema

21. Asumiendo que gpio_regs_t es un tipo de datos definido en el BSP para facilitar el acceso a los registros de control/estado del GPIO y que GPIO_BASE es un símbolo que contiene la dirección base de los registros del GPIO en el mapa de memoria de la placa, ¿cual de las siguientes declaraciones permite acceder correctamente en C a los registros del GPIO?
    - ( ) static const gpio_regs_t* gpio_regs = GPIO_BASE;
    - ( ) static volatile const gpio_regs_t* gpio_regs = GPIO_BASE;
    - (x) static volatile gpio_regs_t* const gpio_regs = GPIO_BASE;
    - ( ) static gpio_regs_t* const gpio_regs = GPIO_BASE;

22. Indica la opción correcta para diseñar una estructura de datos que permita acceder directamente tanto a un registro de control completo mediante máscaras de bits como a cada uno de sus campos de forma individual
    - ( ) Definiendo una unión de un campo de bits (bitfield) y un uint32_t
    - ( ) Definiendo una unión anónima de un campo de bits (bitfield) y un uint32_t
    - ( ) No es posible diseñar una estructura de datos que permita acceder a los registros de control de esta forma
    - (x) Definiendo una unión anónima de un campo de bits anónimo (bitfield) y un uint32_t

23. Dado que los búferes circulares de un driver L1 se acceden concurrentemente por la ISR del driver y por las funciones de envío y recepción, es necesario gestionar su acceso mediante regiones críticas para evitar condiciones de carrera. Indica cuál de las siguientes opciones define correctamente una región crítica para el acceso al búfer de recepción de un driver
    - ( ) En la función receive. Se debe anular la generación de interrupciones por parte del dispositivo en el controlador de interrupciones antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso
    - ( ) En la ISR del dispositivo. Se debe anular la generación de interrupciones de recepción antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso
    - ( ) En la función receive. Se debe enmascarar la atención de interrupciones en los bits I/F del registro de control de la CPU antes de acceder al búfer y restaurarla una vez que se ha terminado el acceso
    - (x) En la función receive. Se debe anular la generación de interrupciones de recepción antes de acceder al búfer y restaurarlas una vez que se ha terminado el acceso

24. Indica cuál de las siguientes opciones describe la forma correcta en la que se puede usar el BSP desarrollado en la asignatura para que una aplicación pueda hacer E/S concurrente mientras se está ejecutando
    - ( ) Haciendo uso de las funciones de envío y recepción bloqueantes del driver
    - ( ) Escribiendo una ISR para la UART a la medida de la aplicación
    - ( ) Haciendo uso de las funciones de envío y recepción basadas en búferes
    - (x) Desarrollando funciones callback de envío y recepción y registrándolas en el driver de la UART

25. El uso de los pines de E/S un SoC...
    - ( ) Se configura automáticamente en función de los periféricos que se conecten al SoC
    - ( ) Es único. Cada pin tiene una única función, que dependerá del dispositivo al que esté conectado
    - ( ) Viene configurado de fábrica y no se puede cambiar por la aplicación
    - (x) Está multiplexado, por lo que es necesario el uso del GPIO para configurarlos correctamente

26. La lista de ficheros abiertos del BSP...
    - ( ) Sólo estará presente en aquellos sistemas que dispongan de dispositivos de almacenamiento (ej. discos duros, memorias flash, etc.).
    - ( ) Almacena todos los dispositivos que se pueden tratar como ficheros en el BSP
    - ( ) Asocia un único fichero a cada dispositivo del sistema
    - (x) Asocia descriptores de fichero a dispositivos

27. Si se invoca a una syscall de Newlib con descriptor de fichero no válido o bien con un descriptor de fichero abierto sobre un dispositivo que no tiene implementada dicha función...
    - ( ) Este caso no es posible. Todos los dispositivos deben implementar todas las syscalls
    - ( ) Se retornará -1 y se fijará la variable global errno al valor adecuado
    - ( ) Se abortará la ejecución de la aplicación
    - (x) Se ejecutará la implementación por defecto para dicha syscall

28. Indica cual de estas características NO es propia de un driver L1
    - ( ) Permiten la definición de funciones callback
    - ( ) Proporciona un API abstracta e independiente del dispositivo
    - ( ) Permiten una configuración total del dispositivo
    - (x) Las operaciones de E/S son bloqueantes

29. En el caso de que nuestro sistema tenga varias instancias de un tipo de dispositivo (por ejemplo tres temporizadores), y cada uno de las instancias tenga sus propios registros agrupados a partir de una dirección base en el mapa de memoria, ¿qué estructura es la más adecuada para gestionar los registros de los dispositivos?
    - ( ) Una estructura de estructuras
    - ( ) Una estructura de arrays
    - ( ) Un array de estructuras
    - (x) Un array de punteros a estructuras

