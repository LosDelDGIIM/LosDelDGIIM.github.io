# Sistemas Concurrentes y Distribuidos. Sesión 3 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** José Miguel Mantas Ruíz.
- **Descripción:** Resumen de la práctica 3.

Veremos varias soluciones al problema de los productores/consumidores y el problema de los filósofos.
  
# Productor/Consumidor
En el caso distribuido, necesitaremos tener tres roles de procesos:
- **Productor**: Que produce una secuencia de datos y los envía al proceso **buffer**.
- **Consumidor**: Que realiza peticiones al proceso **buffer** y como respuesta recibe y consume los enteros.
- **Buffer:** Recibe (de forma alterna) enteros del proceso productor y peticiones del consumidor. Responde al consumidor enviándole los enteros recibidos. Cuenta con una estructura de datos para almacenar los datos pendientes de consumir.  
  
De esta forma, el productor y el consumidor necesitarán enviar mensajes al proceso buffer para que este bien introduzca el dato del productor en su estructura de datos, o bien sirva la petición del consumidor con el dato a leer.  
Así, los códigos del productor y del consumidor serían los siguientes:
```c++
int num_datos;
// Productor
int dato;

for(int i = 0; i < num_datos; i++){
    dato = Producir();
    MPI_Ssend(&dato, 1, MPI_INT, buffer, 0, MPI_COMM_WORLD);
}

// ...

// Consumidor
int dato, peticion;
MPI_Status status;

for(int i = 0; i < num_datos; i++){
    MPI_Ssend(&peticion, 1, MPI_INT, buffer, 0, MPI_COMM_WORLD);
    MPI_Recv(&dato, 1, MPI_INT, buffer, 0, MPI_COMM_WORLD, &status);
    Consumir(dato);
}
```
Y el código del proceso buffer será (si nos decantamos por prioridad FIFO):
```c++
int buffer[tam];
int primera_libre = 0, primera_ocupada = 0, ocupadas = 0;   // Controlar el buffer
int valor, id_emisor;                           // Controlar los mensajes

MPI_Status status;

for(int i = 0; i < 2*num_datos; i++){
    // Determinar quien puede acceder
    if(ocupadas == 0){
        id_emisor = id_productor;
    }else if(ocupadas == tam){
        id_emisor = id_consumidor;
    }else{
        id_emisor = MPI_ANY_SOURCE;
    }
    
    // Recibe el mensaje
    MPI_Recv(&valor, 1, MPI_INT, id_emisor, 0, MPI_COMM_WORLD, &status);
    
    // Procesa el mensaje
    switch(status.MPI_SOURCE){
        case id_productor:
            buffer[primera_libre] = valor;
            primera_libre = (primera_libre + 1) % tam;
            ocupadas++;
            break;
            
        case id_consumidor;
            valor = buffer[primera_ocupada];
            primera_ocupada = (primera_ocupada + 1) % tam;
            ocupadas--;
            MPI_Ssend(&valor, 1, MPI_INT, id_consumidor, 0, MPI_COMM_WORLD);
            break;
    }
}
```

# Productores/Consumidores
Si ahora estamos en un escenario con `np` productores y `nc` consumidores de forma que `num_items` sea múltiplo de `np` y de `nc`.  
Para identificar a cada proceso, supondremos que los identificadores de los productores van de `0` a `np-1`, el buffer tendrá identificador `np` y los consumidores tendrán identificadores desde `np+1` hasta `np+nc`.  
De esta forma, el código de los productores y de los consumidores no cambiaría (salvo el límite en el bucle for y que ahora los consumidores envían por el tag `TAG_CONS` y los productores por el tag `TAG_PROD`), pero en el buffer tendríamos que realizar una modificación:
```c++
int buffer[tam];
int primera_libre = 0, primera_ocupada = 0, ocupadas = 0;
int valor, tag;

MPI_Status status;

for(int i = 0; i < 2*num_items; i++){
    // Vemos de qué tag recibimos
    if(ocupadas == 0){
        tag = TAG_CONS;
    }else if(ocupadas == tam){
        tag = TAG_PROD;
    }else{
        tag = MPI_ANY_TAG;
    }
    
    // Recibimos el mensaje
    MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
    
    // Procesamos el mensaje
    switch(status.MPI_TAG){
        case TAG_PROD:
            buffer[primera_libre] = valor;
            primera_libre = (primera_libre + 1) % tam;
            ocupadas++;
            break;
        
        case TAG_CONS:
            valor = buffer[primera_ocupada];
            primera_ocupada = (primera_ocupada + 1) % tam;
            ocupadas--;
            MPI_Ssend(&valor, 1, MPI_INT, status.MPI_SOURCE, TAG_CONS, MPI_COMM_WORLD);
            break;
    }
}
```

# Problema de los Filósofos
Recuperamos el problema de los filósofos ya visto en la teoría.  
Tenemos 5 filósofos (procesos) y 5 tenedores (otros procesos), de forma que un mismo tenedor da servicio a dos filósofos distintos (a los dos de sus lados). El objetivo del problema es garantizar la comunicación entre los filósofos y los tenedores.
Numeraremos a los procesos desde 0 hasta 9, siendo los procesos pares los filósofos y los impares los tenedores.  
  
Los procesos filósofos realizarán las acciones:
1. Cogen dos tenedores (primero el izquierdo y luego el derecho).
2. Comer (bloqueo de duración aleatoria).
3. Soltar los dos tenedores (da igual el orden).
4. Pensar (bloqueo de duración aleatoria).
De esta forma, su código será:
```c++
void funcion_filosofos(int id){
    int id_ten_izqda = (id + 1) % num_filosofos;
    int id_ten_dcha = (id-1) % num_filosofos;
    
    int x;
    
    while(true){
        // Coge tenedor izquierda
        Ssend(&x, 1, MPI_INT, id_ten_izqda, 0, MPI_COMM_WORLD);
        cout << "Filosofo " << id << " coge tenedor " << id_ten_izqda << endl;
        // Coge tenedor derecha
        Ssend(&x, 1, MPI_INT, id_ten_dcha, 0, MPI_COMM_WORLD);
        cout << "Filosofo " << id << " coge tenedor " << id_ten_dcha << endl;
        
        // Come
        sleep_for(milliseconds( aleatorio<10,100>() ));
        
        // Suelta tenedor izquierda
        Ssend(&x, 1, MPI_INT, id_ten_izqda, 0, MPI_COMM_WORLD);
        cout << "Filosofo " << id << " suelta tenedor " << id_ten_izqda << endl;
        // Suelta tenedor derecha
        Ssend(&x, 1, MPI_INT, id_ten_dcha, 0, MPI_COMM_WORLD);
        cout << "Filosofo " << id << " suelta tenedor " << id_ten_dcha << endl;
        
        // Piensa
        sleep_for(milliseconds( aleatorio<10,100>() ));
    }
}
```
Y el código de los tenedores:
```c++
void funcion_tenedores(int id){
    int x;
    MPI_Status status;
    
    while(true){
        // El tenedor es cogido
        MPI_Recv(&x, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        cout << "Tenedor " << id << " cogido por " << status.MPI_SOURCE << endl;
        
        // El tenedor es liberado
        MPI_Recv(&x, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        cout << "Tenedor " << id << " liberado por " << status.MPI_SOURCE << endl;
    }
}
```

## Libre de interbloqueo
Como hemos visto anteriormente en teoría, la solución anterior lleva a interbloqueo. Una forma de solucionarla es modificar el código de los filósofos:
```c++
void funcion_filosofos(int id){
    int id_ten_izqda = (id + 1) % num_filosofos;
    int id_ten_dcha = (id-1) % num_filosofos;
    
    int x;
    
    while(true){
    
        if(id == 0) {
            // Coge tenedor derecha
            Ssend(&x, 1, MPI_INT, id_ten_dcha, 0, MPI_COMM_WORLD);
            cout << "Filosofo " << id << " coge tenedor " << id_ten_dcha << endl;
            // Coge tenedor izquierda
            Ssend(&x, 1, MPI_INT, id_ten_izqda, 0, MPI_COMM_WORLD);
            cout << "Filosofo " << id << " coge tenedor " << id_ten_izqda << endl;
        } else {
            // Coge tenedor izquierda
            Ssend(&x, 1, MPI_INT, id_ten_izqda, 0, MPI_COMM_WORLD);
            cout << "Filosofo " << id << " coge tenedor " << id_ten_izqda << endl;
            // Coge tenedor derecha
            Ssend(&x, 1, MPI_INT, id_ten_dcha, 0, MPI_COMM_WORLD);
            cout << "Filosofo " << id << " coge tenedor " << id_ten_dcha << endl;
        }
        
        // Come
        sleep_for(milliseconds( aleatorio<10,100>() ));
        
        // Suelta tenedor izquierda
        Ssend(&x, 1, MPI_INT, id_ten_izqda, 0, MPI_COMM_WORLD);
        cout << "Filosofo " << id << " suelta tenedor " << id_ten_izqda << endl;
        // Suelta tenedor derecha
        Ssend(&x, 1, MPI_INT, id_ten_dcha, 0, MPI_COMM_WORLD);
        cout << "Filosofo " << id << " suelta tenedor " << id_ten_dcha << endl;
        
        // Piensa
        sleep_for(milliseconds( aleatorio<10,100>() ));
    }
}
```

## Filósofos con camarero
Una forma más elegante de resolver el problema es introducir un décimo proceso *camarero*, de forma que los filósofos solicitan acceso al proceso camerero, para sentarse a la mesa así como para levantarse de esta.  
El camarero llevará la cuenta de los filósofos sentados y cuando haya 4 sentados, no permitirá sentarse al quinto, con el fin de evitar interbloqueos.
