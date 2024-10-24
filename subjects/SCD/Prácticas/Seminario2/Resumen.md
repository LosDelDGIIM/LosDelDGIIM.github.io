# Seminario 2.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** José Miguel Mantas Ruíz.
- **Descripción:** Resúmen del Seminario 1 de Prácticas.

Para la relación de este seminario, es importante haber leído primero la parte de semántica de señales del Tema 2, y entender especialmente la semántica **Señalar y Espera Urgente**.  
  
En este seminario, aprenderemos cómo crear y usar monitores en C++11, usando los archivos `scd.h` y `scd.cpp` proporcionados por los profesores.  
  
# 1. Introducción
La forma más natural de crear un monitor en C++ es usando clases, de forma que:
- Las variables permanentes sean las variables de instancia no públicas.
- Los procedimientos exportados sean métodos públicos de una clase.
- El procedimiento de inicialización sea un método constructor de la clase.  
  
Sin embargo, para obtener un monitor nos falta:  
- Asegurar la exclusión mutua en las llamadas a los procedimientos (además de implemnetar la cola de entrada al monitor).
- La existencia de las variables de tipo *condición*.  
  
- C++11 no incluye la posibilidad de definir monitores directamente.
- Sin embargo, podemos usar clases o tipos nativos del lenguaje como `mutex`, `lock_guard` y `condition_variable` para implementar un tipo monitor. Sin embargo, este tendría una semántica de *Señalar y Continuar*. Trabajar con dicha semántica es complicado.
- También, se puede implementar de forma no tan directa usando más mecanismos nativos de C++, que ya sí tendrá una semántica deseada, la de *Señalar y Espera Urgente*.
  
Dentro de los archivos `scd.h` y `scd.cpp`, tenemos implementada una clase que nos ayudará a crear monitores, además de un tipo de dato similar al tipo *condición* de teoría, los cuales aprenderemos a usar en el siguiente punto.

# 2. Clase HoareMonitor
Dentro de los ficheros anteriormente comentados, tenemos implementada la clase `HoareMonitor`, usando características nativas de C++11.  
  
Para crear monitores, crearemos clases que hereden de esta, por lo que no tendremos que procuparnos ni por la exclusión mutua de los métodos de la clase ni por no tener implementadas las variable de tipo condición, que ahora será `CondVar`.  
  
Esta clase tiene de semántica de señales SU, luego también tendrá una cola de espera urgente de entrada al monitor.

## Ejemplo de creación y uso
Para mostrar cómo podemos crear y usar monitores, veremos el siguiente ejemplo, en el cual creamos un monitor con la finalidad de almacenar una variable contadora que pueda ser incrementada y consultada por cualquier hebra.  
```c++
class MContador : public HoareMonitor       // Hereda de HoareMonitor
{
  private:
    int cont;
  public:
    MContador( int valor_inicial );
    void incrementa();
    int leer();
};

MContador::MContador( int valor_inicial ){
    cont = valor;
}

MContador::incrementa(){
    cont++;
}

MContador::leer(){
    return cont;
}
```
Ahora, para usar el monitor creado, usaremos:
```c++
void funcion_hebra_1( MRef<MContador> monitor ){
    // ...
    monitor->incrementa();
    // ...
    x = monitor->leer();
    // ...
}

void main(){
    MRef<MContador> monitor = Create<MContador>( 0 );
    
    thread hebra1( funcion_hebra_1, monitor );
    thread hebra2( funcion_hebra_2, monitor );
    
    hebra1.join();
    hebra2.join();

    // ...
}
```
Donde:  
- Para almacenar el monitor, usamos objetos de tipo `MRef<M>`, que referencian al monitor.
- Para crear instancias de un monitor, usaremos la función `Create<M>`.
- Cada hebra que use el monitor debe tener una referencia del mismo.
- Para usar procedimientos del monitor, deberemos usar en las hebras el operador `->`, por estar trabajando con referencias y no con objetos directamente.

# 3. Variables CondVar
En las clases que hereden de `HoareMonitor`, esto es, las clases que creemos para ser usadas como monitores, podremos usar el tipo `CondVar` para las variables condición de nuestro monitores.  
- Estas deben ser variables de instancia privadas de la clase monitor (que no pueden usarse fuera de los métodos de dicha clase).
- En el constructor del monitor, deberemos crear **explícitamente** cada una de dichas variables usando la función **newCondVar**.
- Si alguna variable de este tipo es declarada pero no inicializada en el contructor, al usarla obtendremos un *error que abortará el programa*.
- Recordamos que la planificación de las colas de las variables condición es FIFO.  
  
Las variables de tipo `CondVar` tienen definidas varias operaciones que se invocan desde los siguientes métodos de la misma:
- `wait()`: La hebra que lo invoca espera bloqueada en la cola de la variable condición.
- `signal()`: Si la cola de la variable condición está vacía, no hace nada. Si no está vacía, la hebra que lo invoca se bloqueará en la cola de urgentes del monitor y la primera hebra de la cola de la variable condición se desbloqueará y seguirá ejecutando su procediemiento.
- `get_nwt()`: Devuelve el número de hebras que esperan en la cola de la variable condición.
- `empty()`: Devuelve `true` si no hay hebras esperando en la cola, `false` si no.

