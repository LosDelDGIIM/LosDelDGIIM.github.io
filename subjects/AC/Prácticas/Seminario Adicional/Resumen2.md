# Introducción

En esta sesión de prácticas voluntaria se ha trabajado el uso de la GPU para agilizar la ejecución de los programas. Estas son las características de la GPU:

      - Nodo: atcgrid4
      - Modelo: Nvidia Quadro RTX 5000
      - Núcleos de procesamiento paralelo: 3072
      - Número de SIMT:	48
      - Maximo de threads por SM(también llamado CUDA Block): 1024
      - Número de threads en un warp(unidad de planificación): 32
      - Memoria de la GPU en la tarjeta: GDDR6 de 16 GB
      - Bus para conexión con el host: PCI Express 3.0 x 16

# 1.Estructura de la Arquitectura junto a un coprocesador de la GPU

Como se ve en el dibujo del pdf de esta carpeta, cada SM dispone de una cache y un organizador de wraps a parte de una agrupacion de nucleos SP también llamada núcleo CUDA. La caché L1 es compartida por todos los SP y la caché L2 es compartida por todos los SM, agrupaciones de SP. Además, dispone de una memoria principal de GPU conectada a la al coprocesador por un bus de memoria.

La conexion entre Host,en nuestro caso el FrontEnd,se realiza mediante un bus de entrada salida conectado con la memoria del multiprocesador de host.

## 1.1.Uso del coprocesador y un poco de funcionamiento interno

El host o anfitrión es el dispositivo que maneja el cotarro, si este necesita de ayuda creará más flujos de instrucciones que le ayudarán a la ejecución de una región del programa. A aquellos dispositivos usados para acelerar la ejecución de una región de código se les suele llamar coprocesadores o target devices. 

Es importante aclarar que los flujos de instrucciones creados por el host, si se ven sobrepasados y necesitan más potencia tomarán la decisión (realmente la toma el usuario) de crear mas flujos que usaran como target devices y ejecutarán una porción de la región de código asignada al flujo que los crea. Estos flujos que crean otros se llaman initial threads. El primer flujo que se ejecuta en el host es el initial thread del host.

Referente a esto, cada dispositivo solo dispone de un número fijo de flujos de instrucciones a usar, es decir el número de entradas que tiene el procesador, lo que equivale al número de instrucciones que puede procesar de forma simultánea.

En caso de querer ejecutar algo de código en un dispositivo específico, se creará un initial thread asociado a este dispositivo.

Con respecto a la gestión de datos, la memoria no tiene un estado estático sino que puede estar compartida o no dependiendo del momento. Para gestionarlo se usa el mapeo, que denomina qué variables son compartidas y cuáles no. Esto no significa necesariamente que haya tranferencia de datos entre dispositivos.

# 2.Directivas para usar en coprocesadores

Veamos las directivas que se pueden usar en el código para hacer uso de coprocesadores:

## 2.1.Directivas de dispositivos

### pragma omp target

Se encarga de delimitar el código a ejecutar por un dispositivo coprocesador. Para determinar el entorno de datos, se usa la cláusula map que más adelante quedará explicada.

Esta directiva debe ir seguida de un bloque estructurado.

### pragma omp target data

Es la encargade de realizar lo mismo que la directiva anterior añadiendo al tarea de crear un ámbito de datos del dispositivo. Es decir, es la encargada de reservar memoria en el coprocesador para almacenar la svariables que se vayan a usar; normalemente, va seguida del mapeo de variables.

Esta directiva también puede manejar el envío al host de datos de memoria del coprocesador usando la clásula map con el argumento from.

Debe ir seguida de un bloque estructurado
### pragma omp target enter data / target exit data / target update

La **primera** de las opciones es la encargada de realizar la reserva de memoria en la memoria del coprocesador para las variables de la cláusula map.

La **segunda** de ellas es la encargada de desmapear las variables de un ámbito de datos de coprocesador. Por tanto, requiere de que haya un ámbito previamente creado. 

La **última** de ellas es la encargada de actualizar las variables entre la memoria del coprocesador y la memoria del host, haciendo que no haya fallos de coherencia de memoria entre ellos.

Como se puede denotar, deben ir junto a la cláusula _map_, a excepción de la última que sólo va continuada por _to(_variables_)_ y _from(_variables_)_, y  no estan seguidas de ningún tipo de estructura de código típica de OpenMP.

### pragma omp declare target

Usar esta directiva implica crear una zona de declaración de varibles de manera que el coprocesador ya tendrá dichas variables en memoria antes de usar el código; por tanto, estamos continuando con la misma idea de transmitir datos entre host y coprocesador. Esta directiva es *solo* para variable globales y funciones. 

Se encarga de crear versiones en el coprocesador para variables y funciones, asigna almacenamiento en el dispositivo.

La forma de usarlo es la siguiente: 

	    # pragma omp declare target 
	       
	       // Declaración de variables globales o funciones

	    # pragma omp end declare target

Hay más formas de usar esta directiva:

	    # pragma omp declare target (lista de variables y funciones)
	    # pragma omp declare target clause [ [,]clause ... ]

## 2.2.Directivas de equipos

### pragma omp teams

Provoca que se cree una liga de equipos de trabajo, en particular, crea los initial threads de cada equipo. Estos equipos de trabajo serán los encargados de realizar las tareas del código.

### pragma omp distribute

Cuando imponemos esta directiva causamos el reparto de las iteraciones de un bucle entre los equipos que haya creados en la liga de equipos. Por tanto, debe estar seguida de un bucle.

El reparto de iteraciones entre equipos será la siguiente; a la hebra i-ésima, le corresponderán las iteraciones en round-robin nthreads*k+i, donde k=id_team+nteams. Por ejemplo:

	 - 32 hebras por equipo
	 - 1 equipo

Entonces a la hebra 1 del equipo 0 le corresponderán las iteraciones {1,33,65,...}.

# 3.Cláusulas

Se hablarán solo de las cláusulas que he llegado a usar durante la realización del trabajo. Cabe destacar que todas ellas trabajan con variables de control asociadas al elemento que modifican o consultan.

## 3.1.Cláusulas de control de número de hebras

### thread_limit()

Esta clásula que **sólo** se puede usar con la directiva _teams_.

Es la encargada de delimitar el número de hebras posibles a haber en cada equipo de la liga de eqipos, debe ser un número entero.

El valor pasado por argumento debe ser un número natural menor o igual que 1056. No obstante, siempre deberá ser un número múltiplo de 32 luego, en caso de no serlo, se tomará el más cercano que cumpla la condición.De esta manera, si el argumento es menor que 32 siempre se tomará este primer valor y como máximo se tomará 1024, que coincide con el número de hebras por SM.

Por defecto, este último número es el valor que toma.

### num_teams()

Al igual que la anterior, **sólo** se puede usar ocn la directiva _teams_.

Por defecto, toma el valor 48 que coincide con el número de SIMT de la GPU. Si no se usa la directiva de creación de la liga ni la de distribución de iteraciones, se creará un único equipo con 1024 hebras y este realizará todas las iteraciones del bucle.

## 3.2.Cláusulas de comparacion de datos del dispositivo

### map()

Esta clásula se **debe** usar con las directivas _target data_, _target exit data_ y _target enter data_ y puede o no ser usada con la directiva _target_.
La sintáxis es la siguiente:

	    # pragma omp directiva map([map_type:] list item)

donde los diferentes componentes significan lo siguiente:
   - map_type: Por defecto es _tofrom_ pero pueden ser:
      - to: Se encarga de traer las variables pasadas como argumento a la memoria del coprocesador; normalmente suele ser una copia de las mismas, luego hay que tratar de realizar el mínimo número de cargas al coprocesador.
      - from: Se encarga de llevar al host la información de las variables pasadas como argumento, realizando un desmapeo de las variables en el coprocesador.
      - alloc: Reserva memoria en el coprocesador para las variables que pasemos como argumento sin traer el contenido del host, suele ser usado en las directivas _target data_. (NO se ha usado)
      - delete: Desmapea las variables pasadas como argumento sin llevar el contenido al host.(NO se ha usado)
   - list: Lista de variables separadas por comas
   - list item: Pueden ser variables o secciones de vectores o matrices. En el caso de vectores la sintáxis es al siguiente:
	       map(map_type: vector[inicio:fin])
     si no ponemos el inicio, se toma por defecto el comienzo del vector. 

# 4.Rutinas de entorno de ejecución.

En este apartado se hace referencia a una serie de funciones que nos permiten conocer el valor de algunas variables de entorno:

-  omp_get_tem_num(): Devuelve al thread el identificador del equipo al que pertenece.
-  omp_get_num_teams(): Devuelve el total de equipos en una reguión de OpenMP.
-  omp_get_num_devices(): Devuelve el número de coprocesadores disponibles en el nodo.

# 5.Cómo trabajar

Ahora que ya sabemos cómo funcionan las directivas y cláusulas de trabajo con los coprocesadores, estamos en disposición de iniciar nuestro trabajo. Para ello, seguiremos estas pautas.

   - Cada vez que queramos hacer uso del coprocesador, se lo indicaremos con la directiva tardet o sus derivadas dejando claro qué parte del código es la que debe ejecutar.
   - Mapearemos las variables que vayamos a usar con la cláusula map y haciendo uso de los argumentos to y from.
   - Creamos una liga de equipos entre los cuales dividiremos el trabajo con la directiva teams, y en caso de ejecutar un bucle, usaremos la directiva distribute para repartir el trabajo.
   - Desmapear las variables de trabajo, ya sea usando from junto a map si queremos que se "devuelva" el valor al host, o delete con map para que se libere esa zona de memoria del coprocesador sin llevar el dato a la memoria del host.

Todo esto puede llegar a hacerse en una única directiva dando lugar a que tengamos menos control sobre lo que ocurre pues será la herramienta de programación la que realizará más trabajo a medida que juntamos más directivas en una. Por ejemplo: 
      
      # pragma omp target teams distribute parallel for num_teams(nteams) thread_limit(mthreads)\	 map(to:N,alpha,x[:N],y[:n]) map(from:z[:N]

que realiza todo lo anterior y delimita el número de equipos a crear junto con el número límite de hebras a crear por equipo. 
