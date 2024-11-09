# Seminario 2.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** José Miguel Mantas Ruíz.
- **Descripción:** Resumen del Seminario 1 de Prácticas.

Para la relación de este seminario, es importante haber leído primero la parte de semántica de señales del Tema 2, y entender especialmente la semántica **Señalar y Espera Urgente**.  
  
En este seminario, aprenderemos cómo crear y usar monitores en C++11, usando los archivos `scd.h` y `scd.cpp` proporcionados por los profesores.  
  
# 1. Introducción
La forma más natural de crear un monitor en C++ es usando clases, de forma que:
- Las variables permanentes sean las variables de instancia no públicas.
- Los procedimientos exportados sean métodos públicos de una clase.
- El procedimiento de inicialización sea un método constructor de la clase.  
  
Sin embargo, para obtener un monitor nos falta:  
- Asegurar la exclusión mutua en las llamadas a los procedimientos (además de implementar la cola de entrada al monitor).
- La existencia de las variables de tipo *condición*.  
  
- C++11 no incluye la posibilidad de definir monitores directamente.
- Sin embargo, podemos usar clases o tipos nativos del lenguaje como `mutex`, `lock_guard` y `condition_variable` para implementar un tipo monitor. Sin embargo, este tendría una semántica de *Señalar y Continuar*. Trabajar con dicha semántica es complicado.
- También, se puede implementar de forma no tan directa usando más mecanismos nativos de C++, que ya sí tendrá una semántica deseada, la de *Señalar y Espera Urgente*.
  
Dentro de los archivos `scd.h` y `scd.cpp`, tenemos implementada una clase que nos ayudará a crear monitores, además de un tipo de dato similar al tipo *condición* de teoría, los cuales aprenderemos a usar en el siguiente punto.

En el programa [monitor_em.cpp](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Pr%C3%A1cticas/Seminario2/C%C3%B3digos/monitor_em.cpp) se puede observar este hecho, dejando claro que es necesario usar la clase `HoareMonitor` para crear monitores, que a continuación se explicará.

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
 
# 4. Problema de productor/consumidor con monitores
Volvemos sobre el problema del productor consumidor, con un proceso que produce varios datos (supondremos que son números enteros), y un proceso que actúa como consumidor (necesita los números enteros que el productor genera).  
  
El recurso compartido que será encapsulado por el monitor en este caso será el buffer intermedio que usan para comunicarse, con dos procedimientos `leer` y `escribir`.  
Suponiendo que el tamaño del buffer es $k$ y que queremos tratar $m$ datos (preferiblamente $k<m$), el esquema de uso del monitor será:
```pascal
Process Productor;
   var dato : integer;
begin
   for i := 1 to m do begin
      dat := ProducirDato();
      ProdCons.insertar(dato);
   end
end

Process Consumidor;
   var dato : integer;
begin
   for i := 1 to m do begin
      dat := ProdCons.extraer();
      ConsumidrDato(dato);
   end
end
```
A continuación, procedemos a implementar dicho monitor, por ejemplo con disciplina LIFO, usando el pseudocódigo en pascal que venimos usando en la teoría.  
Para el monitor, como debemos bloquear los procesos por dos razones, contamos con dos variables de tipo condición:
- `buffer_lleno`, que bloquearía a un proceso productor si `primera_libre = k` y lo desbloquearía en el momento en el que `primera_libre < k`.
- `buffer_vacio`, que bloquearía a un proceso consumidor si `primera_libre = 0` y lo desbloquearía en el momento en el que `primera_libre > 0`.
```pascal
Monitor ProdCons;
   var buffer : array[0..k-1] of integer;
       primera_libre : integer;
       buffer_lleno, buffer_vacio : condition;
       
    begin
       primera_libre := 0;
    end
    
    procedure insertar(dato : integer);
    begin
       if primera_libre = k then
          buffer_lleno.wait();
       end
       
       {En este punto, primera_libre < k}
       
       buffer[primera_libre] := dato;
       primera_libre++;
       
       {En este punto, primera_libre > 0}
       
       buffer_vacio.signal();
    end
    
    procedure leer() : integer;
    begin
       if primera_libre = 0 then
          buffer_vacio.wait();
       end
       
       {En este punto, primera_libre > 0}
       
       result := buffer[primera_libre];
       primera_libre--;
       
       {En este punto, primera_libre < k}
       
       buffer_lleno.signal();
    end
end
``` 
La ventaja en monitores es que una vez que tenemos un monitor para un proceso productor y otro consumidor, tenemos un monitor que nos sirve para este problema para cualquier número de productores y de consumidores. La implementación en C++11 se encuentra en el archivo [prodcons1_su.cpp](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Pr%C3%A1cticas/Seminario2/C%C3%B3digos/prodcons1_su.cpp).
  
Es un buen ejercicio implementar ahora un monitor para productores y consumidores con semántica FIFO. Notemos que ha sido necesario emplear una variable `ocupados` para llevar la cuenta de los elementos que hay en el buffer, ya que en el caso de `ind_lectura == ind_escritura` no podemos saber si el buffer está lleno o vacío.
La solución es la siguiente:
```pascal
Monitor ProdCons;
   var buffer : array[0..k-1] of integer;
       ind_esctitura : integer;
       ind_lectura : integer;
       ocupados : integer;
       buffer_lleno, buffer_vacio : condition;
       
    begin
       ind_esctitura := 0;
       ind_lectura := 0;
       ocupados := 0;
    end
    
    procedure insertar(dato : integer);
    begin
       if ocupados = k then
          buffer_lleno.wait();
       end
       
       {En este punto, ocupados < k}
       
       buffer[ind_esctitura] := dato;
       ind_esctitura := (ind_esctitura + 1) mod k;
       ocupados++;
       
       {En este punto, ocupados > 0}
       
       buffer_vacio.signal();
    end
    
    procedure leer() : integer;
    begin
       if ocupados = 0 then
          buffer_vacio.wait();
       end
       
       {En este punto, ocupados > 0}
       
       return := buffer[ind_lectura];
       ind_lectura = (ind_lectura + 1) mod k;
       ocupados--;
       
       {En este punto, ocupados < k}
       
       buffer_lleno.signal();
    end
end
``` 
