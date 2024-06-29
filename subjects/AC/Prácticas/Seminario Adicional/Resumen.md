# Arquitectura de Computadores. Seminario Adicional.

**Autor:** Luchas Hidalgo Herrera.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Arquitectura de Computadores.  
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen del seminario adicional.

# Introducción
En esta sesión de prácticas voluntaria se ha trabajado el uso de la GPU para agilizar la ejecución de los programas, aprovechando los múltiples cores de las que estas disponen.  
Usaremos la GPU del nodo de cómputo `atcgrid4`, cuyas características son las siguientes:
- Modelo: Nvidia Quadro RTX 5000
- Núcleos de procesamiento paralelo: 3072
- Número de SIMT: 48
- Maximo de threads por SM (también llamado CUDA Block): 1024
- Número de threads en un warp (unidad de planificación): 32
- Memoria de la GPU en la tarjeta: 16 GB GDDR6
- Bus para conexión con el host: PCI Express 3.0 x 16

## Arquitectura de una GPU
Cada SM dispone de una caché y de un organizador de wraps, junto con una agrupación de núcleos SP.  
La caché L1 es compartida por todos los SP, mientras que la caché L2 es compartida por todos los SM.  
La GPU dispone de una propia memoria principal.

## Funcionamiento de un coprocesador mediante OpenMP
El dispositivo denominado como *host* o *anfitrión* es quien controla el programa a ejecutar. Si este necesita de ayuda para tal tarea, creará más flujos de instrucciones (hebras) que le ayhudarán a la ejecución de una región paralela del programa. Los dispositivos usados para acelerar la ejecución de una región de código reciben el nombre de *coprocesadores* o *target devices*.  
  
Cuando se comienza a usar un coprocesador, a este se le asigna un flujo de instrucción especial. Este flujo tiene la peculiaridad de poder crear otros flujos de trabajo que se ejecutarán en paralelo con este. Reciben el nombre de *initial threads*. El flujo principal o *master* del programa es el *initial thread* del dispositivo host.  
Cuando queramos ejecutar una región de código en un dispositivo específico, se creará un *initial thread* asociado al mismo.
  
Cada dispositivo solo dispone de un número fijo de flujos de instrucciones a usar, correspondiente con el número de instrucciones que puede procesar de forma simultánea.  
  
Recordamos que la GPU tiene su propia memoria RAM. Los datos pueden o no estar compartidos entre CPU o GPU. Para gestionar esto y el intercambio de variables entre dispositivos se utiliza el mapeo de memoria.

***

# Directivas
A continuación, pasaremos a mostrar las directivas que podemos utilizar en nuestro código paralelo para hacer uso de coprocesadores.

### target
Debe ir seguida de un bloque estructurado.  
  
Se encarga de delimitar el código a ejecutar por un dispositivo coprocesador. 
Para determinar el entorno de los datos, se usa la cláusula `map` que desarrollaremos a continuación. 

### target data
Debe ir seguida de un bloque estructurado.  
  
También se encarga de delimitar el código a ejecutar por un dispositivo coprocesador, pero también crea un ámbito de datos del dispositivo. Esto es, la directiva es la encargada de reservar memoria en el coprocesador para almacenar las variables que se vayan a usar.  
  
Suele ir seguida de la cláusula `map`, que se encarga de realizar el mapeo de variables.

### target enter data
Debe ir seguida de la cláusla `map`.  
  
Se encarga de realizar la reserva e memoria en la memoria del coprocesador para las variables de su cláusla `map`.

### target exit data
Debe ir seguida de la cláusla `map`.  
  
Se encarga de desmapear las variables de un ámbito de datos del coprocesador. Por tanto, requiere que haya un ámbito creado anteriormente.

### target update
Debe ir seguida de la cláusula `to` o `from`.  
  
Es la encargada de actualizar las variables entre la memoria del dispositivo anfitrión y la memoria del coprocesador.

### declare target
Usar esta directiva implica crear una zona de declaración de variables de manera que el coprocesador tendrá dichas variables en memoria antes de usar el código. Esta directiva es solo para variables globales y funciones.  
  
Se encarga, por tanto, de crear versiones en el coprocesador para variables y funciones.  
Se usa de la siguiente forma:
```c
#pragma omp declare target

// Declaración de variables globales o funciones

#pragma omp end declare target
```
Aunque también se puede usar como:
```c
#pragma omp declare target (l)
```
donde `l` es una lista de variables y funciones (sus nombres separados por `,`).

### teams
Provoca que se cree una liga de equipos de trabajo. Crea los *initial thread* de cada equipo. Dichos equipos de trabajo serán los encargados de realizar las tareas a paralelizar.

### distribute
Debe ir seguida de un bucle.  
  
Causa el reparto de las iteraciones de un bucle entre los equipos que haya creados en la liga de equipos.  
El reparto por defecto de las iteraciones del bucle se hace de forma *round-robin*.

# Cláusulas
Podemos clasificar las distintas cláusulas según su funcionalidad.

## De control del número de hebras
### thread_limit
Sólo puede usarse con la directiva `teams`.  
  
Es la encargada de delimitar el número de hebras de cada equipo de la liga de equipos.  
El valor pasado a la cláusula debe ser un múltiplo de 32. En caso de no serlo, se tomará el más cercano que cumpla la condición. Su valor máximo es el número de hebras por SM.

### num_teams
Sólo puede usarse con la directiva `teams`.  
  
Por defecto toma el valor el número de SIMT de la GPU. Establece el número de equipos a utilizar.

## De control de memoria del coprocesador
### map
**Debe** ser usada con las directivas `target data`, `target exit data` y `target enter data`.  
Puede usarse con la directiva `target`.  
  
Su sintaxis es la siguiente:
```c
#pragma omp directiva map([map_type:] list item)
```
Donde `list item` puede ser o bien una lista de variables separadas por comas o bien secciones de vectores o matrices.  
Podemos indicar que tome las posiciones $[i,j]$ de un vector mediante la sintaxis:
```c
#pragma omp directiva map([map_type:] v[i:j])
```
Omitir la `i` significa empezar desde el comienzo del vector.

##### Tipos de mapeos
Por defecto, se usa el valor `tofrom`. Podemos adoptar:
- `to`: Se encarga de **traer** las variables pasadas como argumentos a la memoria del coprocesador.
- `from`: Se encarga de **llevar al host** la información de las variables pasadas como argumentos, realizando un desmapeo de las variables en el coprocesador.
- `alloc`: Reserva memoria en el coprocesador para las variables que pasemos con argumentos. Suele ser usado en las directivas `target data`.
- `delete`: Desmapea las variables pasadas como argumento.

# Rutinas del entorno
Disponemos además de ciertas funciones que nos permiten conocer el valor de algunas variables de control:
### omp_get_team_num
Devuelve al thread el identificador del equipo al que pertenece.
### omp_get_num_teams
Devuelve el total de equipos en una región paralela.
### omp_get_num_devices
Devuelve el número de coprocesadores disponibles en el nodo.

# Cómo trabajar
Ahora que tenemos claras las herramientas que OpenMP nos provee para el trabajo con coprocesadores, procedemos a explicar cómo suele ser este trabajo:
- Cada vez que queramos hacer uso del coprocesador, se lo indicaremos al compilador con la directiva `target` o sus derivadas.
- Mapearemos las variables que vayamos a usar con la cláusula `map` y haciendo uso de `to` o `from`.
- Crearemos una liga de equipos entre los cuales dividiremos el trabajo con la directiva `teams`, o bien `distribute` si nos disponemos a paralelizar un bucle.
- Desmapearemos las variables utilizadas, ya sea usando `from` en la cláusula `map` o simplemente un `delete`.  
  
Podemos destacar que todos este trabajo puede hacerse en una única línea, tal y como pasamos a mencionar:
```c
#pragma omp target teams distribute parallel for num_teams(nteams) thread_limit(mthreads)\ 
    map(to:N,alpha,x[:N],y[:N]) map(from:z[:N])
    for(int i = 0; i < N; i++){
        z[i] = alpha * x[i] + y[i];
    }
```
