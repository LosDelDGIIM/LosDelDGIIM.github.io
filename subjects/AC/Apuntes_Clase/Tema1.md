# Tema 1. Arquitecturas Paralelas. Clasificación y Prestaciones.
# Lección 1.1 Clasificación de paralelismo implícito en una aplicación.
## Dependencias de datos
### RAW
Lectura después de escritura:
```cpp
a = b*c;
// ...
d = a+c;
```
  
Si ejecutamos las dos operaciones en paralelo, puede suceder que la segunda se ejecute antes que la primera, luego no se podrían ejecutar en paralelo.

### WAW
Escritura después de escritura:
```cpp
a = b*c;
// Se lee a
a = d+e;
// Se lee a
```
Podemos resolver este programa cambiando en la segunda instrucción  ```a``` por otra variable. Renombrado de variables.  
El problema aquí es que al leer ```a``` por segunda vez, el valor de ```a``` podría venir determinado por la instrucción ```a = b * c;```

### WAR
Escitura después de lectura:
```cpp
b = a+1;
// ...
a = d+e
// se lee a
```
  
Si ejecutamos las dos operaciones en paralelo, puede suceder que la segunda se ejecute antes que la primera, luego no se podrían ejecutar en paralelo.

## Niveles de paralelismo

Hay distintas capas sobre las que podemos implementar paralelismo:
- Programas.
- Funciones.
- Bucles.
- Operaciones.
  
Para ver si un bucle lo podemos ejecutar en paralelo, debemos comprobar si una iteración de este utiliza iteraciones anteriores. Si no, si disponemos de suficientes núcleos, podríamos ejecutar todas las iteraciones al mismo tiempo.  
Si entre dos bucles distintos no hay RAW, podríamos ejecutarlos en paralelo.  
El mismo razonamiento se aplica a funciones y programas.

### Unidades para cada tipo de paralelismo
- Paralelismo a nivel de intruccioens para procesadores segmentados.
- Paralelismo a nivel de bucles para unidades GPU.
- Paralelismo a nivel de funciones y programas para multiprocesadores.

- Dentro de Procesos podemos meter paralelismo de programas, funciones y bucles.
- Dentro de hilos, paralelismo de funciones y bucles.
- Dentro de instrucciones vectoriales, sólo paralelismo de bucles.
- Es la misma arquitectura del computador la que implementa paralelismo a nivel de operaciones, seleccionando las instrucciones más eficientes y que admiten un mayor grado de paralelismo para se ejecución.

### Granularidad
Tamaño de la secuencia de instrucciones que podemos ejecutar en paralelo antes de toparnos con un RAW entre ellas. Encontramos:
- Grano Grueso (Programas).
- Grano Medio (Funciones).
- Grano Medio-Fino (Bucles).
- Grano Fino (Operaciones).
  
A nivel de función, no hay compiladores que generen paralelismo.  
A nivel de bucle, se pueden generar instrucciones vectoriales.

## Paralelismo implícito en una aplicación
El programa puede paralelizarse pero no es visible para la máquina. Para realizar el paralelismo, hay compiladores que detectan el paralelismo (en este caso, a nivel de operaciones y bucles) y lo indican a la máquina.  
Por otra parte, el paralelismo explícito, son las directivas del programador, que indican al computador que dichas instrucciones deben realizarser en paralelo.  
El programador puede influir en el SO que introduzca cada estructura a paralelizar en distintos núcleos.
### Paralelismo de tareas
Por ejemplo, un decodificador de formato JPEG a RGB que para procesar una foto requiere 4 programas:  
Podemos pasar una primera foto por el primer programa y cuando lo libere, meter la siguiente foto. Por ejemplo, si representamos las fotos por ```A```, ```B``` y ```C```:
| Programa 1 | Programa 2 | Programa 3 | Programa 4 |
|------------|------------|------------|------------|
| A          |            |            |            |
| B          | A          |            |            |
| C          | B          | A          |            |
|            | C          | B          | A          |
|            |            | C          | B          |
|            |            |            | C          |
El paralelismo a nivel de tareas es similar al paralelismo a nivel de función.
  
### Paralelismo de datos
Podemos extraer paralelismo buscando una representación en forma matemática. Las operaciones como sumas vectoriales o productos de matrices pueden paralelizarse.  
Por ejemplo, usando instrucciones vectoriales (como ```addps```) o con varios bucles.  
```cpp
for(int i = 0; i < N; i++) c[i] = a[i] + b[i];
```
Si tenemos un código que resuelve la aplicación, podemos resolverlo mirando los bucles de este código.  
Comenzaríamos cambiando los bucles que ocupan más tiempo en la ejecución del programa.
  
### OpenMP
Con él podemos añadir paralelismo a nuestros programas, dictando al compilador qué esructuras (funciones, bucles, ...) puede ejecutar de forma paralela.
  
## Procesos e hilos
Cuando un proceso se crea, el SO tarda un tiempo en ello, porque tiene que crear espacio en memoria para almacenar código, espacio para variables locales (en pila), espacio para guardar el contenido de los registros del núcleo cuando este esté suspendido, espacio para las variables dinámicas (heap), espacio para globales y estáticas; tabla de ficheros abiertos y tabla de páginas.  
Al matar un proceso también hay un tiempo para liberar todo.  
Para conmutar de un proceso a otro, también hay un tiempo para guardar y cargar datos en la CPU.  
  
Cuando se arranca un proceso se crea un hilo. Al arrancar un nuevo hilo, hay un tiempo para crear un hilo:
- Guardar variables locales.
- Guardar información de CPU cuando se suspende.
  
Tanto el tiempo de creación, muerte y conmutación de un hilo es menor frecente al tiempo de un proceso.  
El coste de la comunicación entre hilos también es importante.  
El tiempo de procesamiento es el tiempo de computación más el tiempo de comunicación y sincronización.  
  
El tiempo de comunicación entre hilos es menor entre procesos, ya que los hilos comparten memoria gracias al proceso.  
Si podemos usar hilos, es recomendable su uso. Cuando ya no podamos, es necesario crear procesos.  
  
# Lección 1.2 Clasificación de arquitecturas paralelas.
## Computación paralela y Computación distribuida.
## Clasificación de computadores
Clasificación que surgen en educación. Clasifica en 4 grupos a las arquitecturas en función de procesar un único flujo de instrucciones o varios y un único o varios flujos de datos:
- SISD: Un único flujo de datos e instrucciones. Un núcleo procesador.
- MISD: Varios flujos de instrucciones y un único de datos. Similar a un pipeline.
- SIMD: Varios flujos de datos y un único de instrucciones. Tenemos múltiples unidades de procesamiento. Cada instrucción que se decodifica se aplica a múltiples datos. Operaciones con vectores. Las GPU cuentan con SIMD y núcleos con multithread temporal.
- MIMD: Varios flujos de datos e instrucciones. Para cada flujo de instrucciones una unidad de control que las vaya decodficando. Multiprocesadores y multicomputadores.

### Clasificación de computadores MIMD según el sistema de memoria
Todos estos conectados por una red de interconexión.
#### Multiprocesadores
Arquitectura UMA.
Comparten el mismo espacio de direcciones. Acceso a memoria uniforme.  
El programador no necesita conocer dónde están almacenados los datos.  
Una placa base con un puerte norte, varios sockets y distintos slots de RAM.  
  
En este caso, es sencillo comunicar los procesadores, ya que un procesador puede escribir en su memoria y que otro procesador lea dicha información.  
Sin embargo, tenemos problemas de sincronización (no leer antes de escribir). Necesitamos código para sincronizar los procesadores (como semáforos o cerrojos).

#### Multicomputadores
Todos los procesadores tienen su espacio de direcciones propio.  
El programador necesita conocer dónde están almacenados los datos.  
Varias placas base de forma que cada procesador tiene su única memoria y módulo de entrada y salida.  
  
Problema de comunicación entre procesadores: un procesador no puede acceder a la memoria de otro procesador.  
El sistema operativo tiene implementadas funciones para copiar y pegar información de la memoria de un procesador a otro. Estas funciones son las de envío y recibimiento de datos (```send``` y ```receive```). Estas funciones son necesarias tenerlas implementadas.  
  
#### Comparativa
La programación de los multicomputadores es generalmente más difícil.  
La ventaja de los multicomputadores es la escalabilidad: al añadir más recursos (más procesadores), se mejora más tiempo que en multiprocesadores.  
Además, el tiempo de acceso a memoria es mayor en multiprocesadores que en multicomputadores. Este tiempo aumenta en multiprocesadores conforme más memoria se añada. Más latencia.
  
En los 90 se hizo una mejora a los multiprocesadores para que estos fueran más independientes, asemejándolos a los multicomputadores. Arquitectura NUMA.  
Acceso a memoria no uniforme: se tarda menos en acceder a la memoria del procesador que a la memoria de otro procesador.

# Lección 1.3 Evaluación de prestaciones.
