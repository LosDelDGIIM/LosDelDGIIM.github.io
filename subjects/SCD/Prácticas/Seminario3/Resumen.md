# Seminario 3.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** José Miguel Mantas Ruíz.
- **Descripción:** Resumen del Seminario 3 de Prácticas.

Este seminario tiene como objetivo la familiarización con la interfaz MPI, mediante la implementación OpenMPI.  
  
# Introducción.
MPI es un estándar que define una API para programación paralela mediante apso de mensajes, permitiendo crear programas eficientes y portables.  
Proporciona un conjunto de funciones que pueden ser utilizadas en varios lenguajes de programación.  
  
- Trabajaremos con un número estático de procesos (fijado en tiempo de compilación).
- Así mismo, usaremos el modelo SPMD (aunque MPI permite también MPMD), de forma que será necesario solo escribir un programa para toda la aplicación.

### Lanzamiento de procesos
Para crear y lanzar los procesos que ejecutarán nuestro programa:
```
mpirun -oversubscribe -np n -machinefile maquinas ejecutable
```
De esta forma: 
- Crearemos `n` copias del ejecutable `ejecutable`.
- Con la opción `oversubscribe` le indicamos que podemos usar más procesos que procesadores disponibles.
- En el archivo `maquinas`, se define la asignación de los procesos a los ordenadores del sistema distribuido.  
  
En nuestro equipo, usar:
```
mpirun -oversubscribe -np n ejecutable
```

## Aspectos de OpenMPI
- Todas las funciones devuelve un código de error: `MPI_SUCCESS` si todo ha ido bien.
- `MPI_STATUS` nos permite acceder a los metadatos de los mensajes:
    - `status.MPI_SOURCE` nos permite ver el proceso fuente.
    - `status.MPI_TAG` nos nuestra la etiqueta del mensaje (un entero sin signo).
- OpenMPI no acepta los tipos de datos de C y C++, sino que tiene sus propios tipos de datos:
```
MPI_CHAR, MPI_INT, MPI_LONG, MPI_UNSIGNED_CHAR, MPI_UNSIGNED, _MPI_UNSIGNED_LONG, MPI_FLOAT, MPI_DOUBLE, MPI_LONG_DOUBLE
```
- Dentro de MPI, los proceos se comunican mediante comunicadores (grupos y ámbitos de procesos). De esta forma, si queremos comunicar varios procesos entre sí, deberemos usar el mismo comunicador. Haremos un uso muy básico de los comunicadores, ya que solo usaremos uno para englobar a todos los procesos del programa.

### Compilación de programas MPI
Usaremos `mpicxx`, que compila y enlaza programas `c++` con MPI:
```
mpicxx -std=c++11 -o ejecutable fuente.cpp
```

# Funciones MPI
- `MPI_Init`: Inicializa el entorno de ejecución de MPI.
- `MPI_Finalize`: Finaliza el entorno de ejecución de MPI.
- `MPI_Comm_size`: Determina el número de procesos de un comunicador.
- `MPI_Comm_ran`: Determina el identificador del proceso que lo ejecuta en un comunicador.
- `MPI_Send`: Operación básica para envío de mensajes. 
- `MPI_Recv`: Operación básica para recepción de mensajes. 

## MPI_Init y MPI_Finalize
Hay que pasarle por referencia los argumentos del programa principal:
```
int MPI_Init(int *arc, char ***argv)
```
- Necesita ser llamdo antes de cualquier otra función MPI.
- Si se llama más de una vez durante la ejecución da error.

## Comunicadores
Un comunicador es una variable de tipo `MPI_Comm`, que está constituido por:
- Un conjunto de procesos.
- Un contexto de comunicacion: Un ámbito de paso de mensajes en el que se comunican dichos procesos. Un mensaje enviado en un contexto solo puede ser recibido en dicho contexto.  
  
Todas las funciones de `MPI` necesitan como argumento un comunicador.  
Por defecto, existe un comunicador referenciado en la constante `MPI_COMM_WORLD`, que hace referencia al **comunicador universal**, que incluye a todos los procesos lanzados.

## MPI_Comm_size y MPI_Comm_rank
```
MPI_Comm_size(MPI_Comm comm, int *size)
```
Esribe en el entero `size` el número total de procesos que forman el comunicador `comm`.

```
MPI_Comm_rank(MPI_Comm comm, int *rank)
```
Escribe en el entero `rank` el número de proceso que llama dentro del comunicador `comm`.

## Ejemplo de programa simple
De esta forma, todos nuestros programas tendrán la siguiente estructura:
```c++
#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv){
   int id_propio, num_procesos;
   
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procesos);
   MPI_Comm_rank(MPI_COMM_WORLD, &id_propio);
   
   // Código del programa distribuido
   
   MPI_Finalize();
   return 0;
}
```

## MPI_Send
```
int MPI_Send(void* buf_emi, int num, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
```
Donde:
- `num` es el número de items enviados (los bytes de forma consecutiva en memoria).
- `buf_emi` es un puntero que apunta al primer byte.
- `datatype` es el tipo de dato de los datos referenciados.
- `dest` es la id del proceso al que le enviamos el mensaje.
- `tag` entero no negativo que se transfiere con el mensaje y se usa para clasificar los mensajes en distintas categorías o tipos.
- `comm` es el comunicador que estamos usando.  
  
Se trata de un envío asíncrono seguro, de foma que tras acabar `MPI_Send`:
- MPI ya ha leído los datos de `buf_emi` y los ha copiado en otro lugar, con lo que la escritura sobre `buf_emi` se puede realizar sin preocupaciones.
- El receptor no necesariamente ha iniciado ya la recepción del mensaje, con lo que es **asíncrono**.  
En resumen, es un envío **no bloqueante**.

## MPI_Recv
```
int MPI_Recv(void* buf_rec, int num, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
```
Donde:
- `num` es el número de ítems a recibir (los bytes de forma consecutiva en memoria). Si es menor que el número de ítems en el emisor, dará error.
- `buf_rec` es un puntero que apunta al primer byte donde almacenar el dato.
- `datatype` es el tipo de dato de los datos referenciados.
- `source` es la id del proceso emisor.
- `tag` entero no negativo que se transfiere con el mensaje y se usa para clasificar los mensajes en distintas categorías o tipos.
- `comm` es el comunicador que estamos usando.  
- `status` contiene metadatos relativos al mensaje.  
  
A tener en cuenta:
- Es una llamada **bloqueante**.
- Podemos enviar un pensaje con un tipo de datos distinto al que se recibe, así como un número de elementos distinto, aunque no es lo normal.
- Si `source` es `MPI_ANY_SOURCE`, se puede recibir un mensaje de cualquier proceso en el comunicador. Con `status` podremos consultar el proceso emisor.
- Si `tag` es `MPI_ANY_TAG`, se puede recibir un mensaje con cualquier etiqueta. Con `status` podremos consultar la etiqueta.  
  
### MPI_Get_count
Dado un `status` y un tipo de dato, devuelve el número de ítems que se espera recibir:
```
int MPI_Get_count(MPI_Status* status, MPI_Datatype dtype, int* num)
```
Escribe en `num` el número de ítems recibidos en una llamada `MPI_Recv` previa. El receptor debe conocer y proporcionar el tipo de los datos.

## Ejemplo de envío y recepción
Como un primer programa simple en el que hacemos que un proceso mande un dato a otro:
```c++
#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv){
   int id_propio, num_procesos;
   int id_emisor = 0;
   int id_receptor = 1;
   
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procesos);
   MPI_Comm_rank(MPI_COMM_WORLD, &id_propio);
   
   if( id_propio == id_emisor ){
   
      int valor_enviar = 100;
      MPI_Send(&valor_enviar, 1, MPI_INT, id_receptor, 0, MPI_COMM_WORLD);

   }else{   // Soy receptor

      int valor_recibir;
      MPI_Status estado;
      MPI_Recv(&valor_recibir, 1, MPI_INT, id_emisor, 0, MPI_COMM_WORLD, &estado);

   }
   
   MPI_Finalize();
   return 0;
}
```

# Envío en modo síncrono, MPI_Ssend
Cuenta con los mismos argumentos que `MPI_Send`.  
Se trata de una semántica bloqueante, tras acabar `MPI_Ssend`:
- ya se ha iniciado en el receptor una operación de recepción.
- Los datos ya se han leído de `buf_emi` y se han copiado en otro lugar, luego podemos modificarlos de forma segura.  
  
Debemos tener cuidado con esta instrucción, ya que como ya sabemos de los apuntes de teoría, las instrucciones síncronas pueden dar lugar a interbloqueo.

# Sondeo de mensajes
Funciones que permiten al proceso receptor averiguar si hay mensajes pendientes de recibir, pudiendo consultar los metadatos de dicho mensaje:
- No supone la recepción del mensaje.
- Se puede restringir a mensajes de un emisor o de una etiqueta.
- Cuando hay mensaje, se permite consultar los metadatos.
- Contamos con una versión bloqueante y con una no bloqueante.

## MPI_Probe
Espera bloqueado hasta que haya al menos un mensaje.
```
int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status)
```
El proceso queda bloqueado hasta que haya al menos un mensaje enviado a dicho proceso (cuando se desbloquee la instrucción, se dice de forma implícita que hay un mensaje con dichas características).  
  
### Usos
Permite hacer recepción de fuentes desconocidas con un tamaño de mensaje desconocido, junto con la función `MPI_Get_count`:
```c++
int num_char;
MPI_Status estado;

MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
MPI_Get_count(&estado, MPI_CHAR, &num_char);

char * buffer = new char[num_char+1];
MPI_Recv(buffer, num_char, MPI_CHAR, estado.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
buffer[num_char] = 0;   // Añade caracter de finalizacion

cout << buffer << endl;
delete[] buffer;
```

## MPI_Iprobe (I de inmediata)
Consulta si hay o no algún mensaje pendiente (mismos parámetros que `MPI_Probe` mas el `flag`).
```
int MPI_Iprobe(int source, int tag, MPI_Comm comm, int* flag, MPI_Status* status)
```
Al terminar, `flag` será mayor que 0 solo si hay algún mensaje enviado al proceso que llama y que encaje con los argumentos `tag` y `source` en el comunicador `comm`. Si no, `flag` valdrá 0.
