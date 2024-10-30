# Sistemas Concurrentes y Distribuidos. Sesión 1 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** José Miguel Mantas Ruíz.
- **Descripción:** Resúmen de la práctica 1.

Veremos problema del productor/consumidor con relaciones 1-1 y muchos-muchos y el problema de los fumadores.  
  
Para generar un número aleatorio entre `a` y `b`, podemos usar el archivo `scd.h`:
```c++
int num = aleatorio<a, b>();
```
Para hacer que una hebra se bloquee durante un tiempo aleatorio, usamos:
```c++
chrono::milliseconds duracion(aleatorio<a,b>());
thread::sleep_for(duracion);
```

# Problema del productor/consumidor
Es el problema que ya hemos visto en teoría, que ahora pasamos a tratar en las prácticas.  
Este usa como mínimo dos procesos (un productor y un consumidor) y un almacén intermedio. En esta primera parte de la práctica, tendremos sólo un proceso que produzca y un único proceso que consuma.  
  
Hasta ahora sólo hemos visto el problema usando de contendor una variable escalar.  
A continuación, veremos distintos almacenes intermedios que nos dan cada uno una solución distinta al problema.  
Un ejemplo de almacén intermedio alternativo es utilizar un vector. Este lo podemos usar como un almacén FIFO (First In First Out) o LIFO (Last In Last Out).  
  
## Ejemplo con vector FIFO
Un ejemplo de problema productor/consumidor es aquel en el que una hebra productora trata de generar $n$ datos, donde cada uno debe ser consumido una única vez por una hebra consumidora. Para ello, usaremos un vector de tamaño $m$ con $m < n$. Sobre este vector, podremos emplear una estrategia de tipo FIFO o LIFO. Lo usaremos como un FIFO.  
  
El código a programar es el siguiente:
```c++
int num_items = n;
int tam_vec = m;
int array[m];

void productor(){
   int var;
   for(int i = 0; i < num_items; i++){   // Debe producir n valores
      var = ProducirValor();
      // Escribe el valor en array
   }
}

void consumidor(){
   int var;
   for(int i = 0; i < num_items; i++){  // Debe consumir n valores
      // Lee del array
      ConsumirValor(var);
   }
}
```
  
Para realizar el problema, debemos usar dos semáforos, uno para el productor que mida la cantidad de huecos vacíos en el vector y otro para el consumidor, que mida la cantidad de huecos ocupados en el vector.  
  
De esta forma, el código final quedaría como:
```c++
int num_items = n;
int tam_vec = m;
int array[tam_vec];

Semaphore s_productor = tam_vec, s_consumidor = 0;

int incindice(int indice){
   if(indice == tam_vec - 1) return 0;
   else return indice + 1;
}

void productor(){
   int var, indice = 0;
   for(int i = 0; i < num_items; i++){   // Debe producir n valores
      var = ProducirValor();
      
      // Escribe el valor en el array
      sem_wait(s_productor);
      array[indice] = var;
      sem_signal(s_consumidor);
      
      indice = incindice(indice);
   }
}

void consumidor(){
   int var, indice = 0;
   for(int i = 0; i < num_items; i++){  // Debe consumir n valores
      // Lee del array
      sem_wait(s_consumidor);
      var = array[indice];
      sem_signal(s_productor);
      
      ConsumirValor(var);
      indice = incindice(indice);
   }
}
```

## Ejemplo con vector LIFO
En este caso, queremos usar el vector como si fuera una pila. Partimos de la plantilla superior que usamos para el caso FIFO, realizando una sencilla modificación para pasar a LIFO, y es que ahora los índices del productor y consumidor están compartidos en uno, que hace referencia al tope de la pila. Debemos tener en cuenta que esta variable es compartida, de forma que los incrementos de la misma se deben realizar en exclusión mutua.  
  
El código quedaría como el siguiente:
```c++
int num_items = n;
int tam_vec = m;
int array[tam_vec];

Semaphore s_productor = tam_vec, s_consumidor = 0;
int tope_pila = 0;

void productor(){
   int var;
   for(int i = 0; i < num_items; i++){   // Debe producir n valores
      var = ProducirValor();
      
      // Escribe el valor en el array
      sem_wait(s_productor);
      array[tope_pila] = var;
      tope_pila++;
      sem_signal(s_consumidor);
   }
}

void consumidor(){
   int var;
   for(int i = 0; i < num_items; i++){  // Debe consumir n valores
      // Lee del array
      sem_wait(s_consumidor);
      tope_pila--;
      var = array[tope_pila];
      sem_signal(s_productor);
      
      ConsumirValor(var);
   }
}
```
Sin embargo, no hemos tenido en cuenta que el productor puede escribir a la vez que el consumidor lea, lo que produciría un fallo. Por tanto, tenemos que hacer las lecturas y las escrituras en exclusión mutua. De esta forma, ya no nos hace falta el tipo de dato atómico para el tope de la pila.
```c++
int num_items = n;
int tam_vec = m;
int array[tam_vec];

Semaphore s_productor = tam_vec, s_consumidor = 0;
mutex cerrojo;
int tope_pila = 0;

// Implementar las funciones incindice y decindice anteriores

void productor(){
   int var;
   for(int i = 0; i < num_items; i++){   // Debe producir n valores
      var = ProducirValor();
      
      // Escribe el valor en el array
      sem_wait(s_productor);
      cerrojo.lock();
      
      array[tope_pila] = var;
      tope_pila++;
      
      cerrojo.unlock();
      sem_signal(s_consumidor);
   }
}

void consumidor(){
   int var;
   for(int i = 0; i < num_items; i++){  // Debe consumir n valores
      // Lee del array
      sem_wait(s_consumidor);
      cerrojo.lock();
      
      tope_pila--;
      var = array[tope_pila];
      
      cerrojo.unlock();
      sem_signal(s_productor);
      
      ConsumirValor(var);
   }
}
```

# Problema del productor/consumidor con varias hebras
Ahora, manejaremos el mismo problema con varias hebras que funcionen de productoras y varias que funcionen de consumidoras. Para implementar estas versiones a partir de las que ya tenemos, es necesario con resolver pequeños problemas.  
  
Además, trataremos de que cada productor produzca el mismo número de datos y que cada consumidor consuma el mismo número de datos.  
  
Las soluciones a estos problemas dependen de si el vector en el que se escribe queremos manejarlo con planificación FIFO o LIFO.

## Productores/consumidores con vector FIFO
En este caso, los productores comparten índice de escritura y los consumidores comparten índice de lectura. El acceso a estas ha de hacerse dentro de un objeto `mutex`, para evitar condiciones de carrera.

```c++
int num_items = n;
int tam_vec = m;
int array[m];

Semaphore s_productor = tam_vec, s_consumidor = 0;

int indice_cons = 0;
int indice_prod = 0;

mutex em_cons, em_prod;

int incindice(int indice){
   if(indice == tam_vec - 1) return 0;
   else return indice + 1;
}

void productor(){
   int var;
   for(int i = 0; i < num_items; i++){   // Debe producir n valores
      var = ProducirValor();
      
      // Escribe el valor en el array
      sem_wait(s_productor);
      em_prod.lock();
      
      array[indice_prod] = var;
      indice_prod = incindice(indice_prod);
      
      em_prod.unlock();
      sem_signal(s_consumidor);
   }
}

void consumidor(){
   int var;
   for(int i = 0; i < num_items; i++){  // Debe consumir n valores
   
      // Lee del array
      sem_wait(s_consumidor);
      em_cons.lock();
      
      var = array[indice_cons];
      indice_cons = incindice(indice_cons);
      
      em_cons.unlock();
      sem_signal(s_productor);
      
      ConsumirValor(var);
   }
}
```

## Productores/consumidores con vector LIFO
En este caso, el código sería el mismo para el caso de varios productores y consumidores.

# Problema de los fumadores
Tenemos 4 entidades que interactúan y modelan una situación habitual que se presenta en varios procesos a resolver. Tenemos un estanquero y 3 individuos, de forma que el estanquero trabaja de forma exclusiva para los fumadores y produce tres tipos de productos: papel, cerillas o tabaco, de forma que en el mostrador sólo cabe a la vez una unidad de ellas. En cada iteración, el estanquero decide qué tipo de ingrediente va a poner en el mostrador de forma aleatoria y espera a que se quede vacío para volver a poner otro tipo de ingrediente.  
  
Los fumadores son 3 individuos que están continuamente fumando, de forma que:
- Uno tiene papel y cerillas de sobra (infinitos), le falta tabaco.
- Uno tiene papel y tabaco de sobra, le faltan cerillas.
- Uno tiene cerillas y tabaco de sobra, le falta papel.  
  
Tenemos un productor y varios consumidores de forma que cada ítem va dirigido a un consumidor específico.  
  
La resolución al problema es la siguiente, donde:
- El productor espera a que el mostrador esté vacío y avisa al fumador i-ésimo de que su elemento ya está producido.
- El consumidor i-ésimo espera a ser avisado y una vez retira su elemento, avisa al estanquero para que ponga el siguiente.

Suponiendo que la hebra `i` retira el ingrediente `i`:
```c++
int num_cons;

Semaphore sem_cons[num_cons] = {0, 0, 0, ..., 0};
Sempahore sem_prod = 1;

void productor(){
    int a;
    
    while(true){
        a = producir();
        
        sem_wait(sem_prod);
        sem_signal(sem_cons[a]);
    }
}

void consumidor(int i){   // i : Indice del consumidor
    while(true){
        sem_wait(sem_cons[i]);
        sem_signal(sem_prod);
        
        fumar();
    }
}
```
Puede ver todos estos códigos implementados en C++ en esta [carpeta](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/SCD/Prácticas/Práctica1/Código).
