# Sistemas Concurrentes y Distribuidos. Sesión 2 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** José Miguel Mantas Ruíz.
- **Descripción:** Resumen de la práctica 2.

Veremos el problema de los productores/consumidores, el problema de los fumadores y el problema de los lectores/escritores.  
  
# 1. Problema de los Productores/Consumidores
Para ello, implementaremos el monitor que ya vimos en pseudocódigo en el Seminario 2 en C++11 usando la superclase `HoareMonitor`.
Podemos además recuperar el código de la Práctica 1 para disponer de múltiples productores y consumidores, aunque veremos que el uso de monitores hace que la sincronización no tenga diferencias ningunas.

De esta forma, el monitor sobre código quedaría de las dos siguientes formas:
### Versión LIFO
```c++
class ProdConsLIFO : public HoareMonitor
{
  private:
   static const int num_celdas_totales = 10;
   int buffer[num_celdas_totales],
       indice;
   CondVar buffer_lleno, buffer_vacio;
   
  public:
   ProdConsLIFO();
   int leer();
   int escribir(int valor);
}

ProdConsLIFO::ProdConsLIFO(){
   indice = 0;
   buffer_lleno = newCondVar();
   buffer_vacio = newCondVar();
}

void ProdConsLIFO::escribir(int dato){
   if(indice == num_celdas_totales)
      buffer_lleno.wait();
      
   buffer[indice] = dato;
   indice++;
   
   buffer_vacio.signal();
}

int ProdConsLIFO::leer(){
   if(indice == 0)
      buffer_vacio.wait();
      
   indice--;
   int dato = buffer[indice];
   
   buffer_lleno.signal();
   
   return dato;
}
```

### Versión FIFO
```c++
class ProdConsFIFO : public HoareMonitor
{
  private:
   static const int num_celdas_totales = 10;
   int buffer[num_celdas_totales],
       indice_lectura, indice_escritura, ocupadas;
   CondVar buffer_lleno, buffer_vacio;
   
  public:
   ProdConsFIFO();
   int leer();
   int escribir(int valor);
}

ProdConsFIFO::ProdConsFIFO(){
   indice_lectura = 0;
   indice_escritura = 0;
   ocupadas = 0;
   buffer_lleno = newCondVar();
   buffer_vacio = newCondVar();
}

void ProdConsFIFO::escribir(int dato){
   if(ocupadas == num_celdas_totales)
      buffer_lleno.wait();
      
   buffer[indice_escritura] = dato;
   indice_escritura = (indice_escritura + 1) % num_celdas_totales;
   ocupadas++;
   
   buffer_vacio.signal();
}

int ProdConsFIFO::leer(){
   if(ocupadas == 0)
      buffer_vacio.wait();
      
   int dato = buffer[indice_lectura];
   indice_lectura = (indice_lectura + 1) % num_celdas_totales;
   ocupadas--;
   
   buffer_lleno.signal();
   
   return dato;
}
```

La implementación en C++11 se encuentra en el archivo [prodcons_su.cpp](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Pr%C3%A1cticas/Seminario2/C%C3%B3digos/prodcons_su.cpp), en el que se puede elegir entre FIFO y LIFO. Además, también se pueden especificar el número de productores y consumidores, así como el número de elementos a producir.

# 2. Problema de los Fumadores
En este caso, disponemos nuevamente de un proceso estanquero que introduce datos en un mostrador (que tiene capacidad para un único dato). Según el tipo del dato, este debe ser consumidor por uno u otro fumador.  
  
El monitor se usaría de la siguiente forma:
```pascal
process Estanquero;
var ingrediente : integer;
begin
   while true do begin
      ingrediente = Producir();
      Estanco.esperarRecogida();
      Estanco.ponerIngrediente(ingrediente);
   end
end

process Fumador[i: 0..n-1];
begin
   while true do begin
      Estanco.obtenerIngrediente(i);
      Fumar(i);
   end
end
```
Donde el método del estanquero lo hemos dividido en dos más sencillos, uno para colocar el ingrediente en el mostrador y otro que esperará a que un fumador coja un ingrediente, con vistas a introducir más código entre los dos métodos.  
La implementación del monitor sería la siguiente:
```pascal
Monitor Estanco;
   var mostrador : integer;  {-1 indica vacio}
       mostrador_lleno, ingrediente_invalido[0..n-1] : condition; 
       
   begin
      mostrador = -1;
   end
   
   procedure ponerIngrediente(ingrediente : integer);
   begin
      mostrador := ingrediente;
      ingrediente_invalido[ingrediente].signal();
   end
   
   procedure esperarRecogidaIngrediente();
   begin
      if mostrador != -1
         mostrador_lleno.wait();
   end
   
   procedure obtenerIngrediente(i : integer);
   begin
      if mostrador != i then
         ingrediente_invalido[i].wait();
      end
      
      mostrador = -1;
      mostrador_lleno.signal();
   end
end
```

La implementación se encuentra en el archivo [fumadores.cpp](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica2/Códigos/fumadores.cpp)

# 3. Problema de los Lectores/Escritores
Tenemos dos tipos de procesos que acceden de forma concurrente a un recurso compartido similar a una estructura de datos. Contamos con dos tipos de procesos:
- Procesos lectores, que no modifican la estrucutra de datos.
- Procesos escritores, que modifican la estructura de datos, por lo que necesitan un acceso exclusivo al rescurso.  
  
Por tanto, las situaciones que se pueden dar son:
- El recurso compartido no está siendo usado por nadie.
- Hay un solo escritor usando el recurso.
- Hay uno o varios lectores usando el recurso.  
  
Para resolver el problema, no podemos encapsular la estructura de datos en el monitor, ya que los lectores no podrían hacer uso del recurso de forma simultánea (ya que los procedimientos del monitor se ejecutan en exclusión mutua).  
De esta forma, lo que tendremos serán dos procedimientos (uno de entrada y otro de salida) por cada tipo de proceso en el problema, de forma que el código de estos procesos se asemeje a:
```pascal
process Lector[i: 1..n];
begin
   while true do begin
      LecEsc.inicia_lectura();
      LecEsc.termina_lectura();
   end
end

process Escritor[i: 1..m];
begin
   while true do begin
      LecEsc.inicia_escritura();
      LecEsc.termina_escritura();
   end
end
```
  
Además, para que el problema esté bien definido, hay que definir una prioridad de entrada, ya que tenemos que dejar claro qué ocurre cuando un escritor abandona el recurso compartido: no habrá nadie leyendo de la estructura de datos, por lo que tendremos que dar prioridad bien a los lectores, bien a los escritores o a quien primero llegue (o cualquier otra prioridad).  
En el problema que resolveremos, asumiremos que la prioridad es para los lectores.  
  
Mostramos ahora la implementación del monitor en pseudo-código:
```pascal
Monitor LecEsc;
begin
   var lec_dentro : integer;
       esc_dentro : boolean;
       cola_lec, cola_esc : condition;
       
   procedure inicia_lectura();
   begin
      if esc_dentro then
         cola_lec.wait();
      end
      
      lec_dentro++;
      cola_lec.signal();
   end
   
   procedure termina_lectura();
   begin
      lec_dentro--;
      
      if lec_dentro = 0 then
         cola_esc.signal();
      end
   end
   
   procedure inicia_escritura();
   begin
      if esc_dentro OR lec_dentro > 0 then
         cola_esc.wait();
      end
      
      esc_dentro = true;
   end
   
   procedure termina_escritura();
   begin
      esc_dentro = false;
      
      if cola_lec.queue() then
         cola_lec.signal();
      else then
         cola_esc.signal();
      end
   end
   
   begin
      lec_dentro = 0;
      esc_dentro = false;
   end
end
```
Sin embargo, esta solución plantea una gran inanición a los escritores, ya que puede haber un flujo constante de lectores que no dejen entrar a los escritores. Para solucionar esto, introducimos una variable llamada `cuanto_leo`, que controla que si han pasado ya `MAX_LEC` lectores mientras haya escritores esperando, que no entren más lectores, sino que pase un escritor.  
Para ello, haríamos las siguientes modificaciones:
```pascal
Monitor LecEsc;
begin
   var lec_dentro : integer;
       esc_dentro : boolean;
       cuanto_leo : integer;
       cola_lec, cola_esc : condition;
       
   procedure inicia_lectura();
   begin
      if esc_dentro OR cuanto_leo = 0 then
         cola_lec.wait();
      end
      
      lec_dentro++;
      if cola_esc.queue() then
         cuanto_leo--;
      end
      
      if cuanto_leo > 0 then 
         cola_lec.signal();
      end
   end
   
   procedure inicia_escritura();
   begin
      if esc_dentro OR lec_dentro > 0 then
         cola_esc.wait();
      end
      
      esc_dentro = true;
      cuanto_leo = MAX_LEC;
   end
   
   {los procedimientos de terminar lectura y/o escritura no son modificados}
   
   begin
      lec_dentro = 0;
      esc_dentro = false;
      cuanto_leo = MAX_LEC;
   end
end
```
Donde la variable `cuanto_leo` la hemos reseteado tras la instrucción `esc_dentro = true;`. Sin embargo, también podríamos hacerlo en el procedimiento `termina_lectura`, tras la instrucción `cola_esc.signal();`.  
  
Puede encontrar los códigos de este último problema en el fichero [lectores_escritores.cpp](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/SCD/Prácticas/Práctica2/Códigos/lectores_escritores.cpp), donde pueden definir o no la variable `NO_INANICION` para ver la diferencia entre ambos códigos. Para ejecutar los códigos, será necesario disponer de los ficheros `scd.cpp` y `scd.h`.
  
Para practicar, se recomienda resolver el problema del [Examen 1 de prácticas](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Pr%C3%A1cticas/Pr%C3%A1ctica1/Ex%C3%A1menes/contrabandista.md), usando ahora para ello monitores en vez de semáforos.
