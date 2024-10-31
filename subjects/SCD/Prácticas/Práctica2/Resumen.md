# Sistemas Concurrentes y Distribuidos. Sesión 2 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** José Miguel Mantas Ruíz.
- **Descripción:** Resúmen de la práctica 2.

Veremos el problema de los productores/consumidores, el problema de los fumadores y el problema de los lectores/escritores.  
  
# 1. Problema de los Productores/Consumidores
Para ello, implementaremos el monitor que ya vimos en pseudocódigo en el Seminario 2 en C++11 usando la superclase `HoareMonitor`.  
Podemos además recuperar el código de la Práctica 1 para disponer de múltiples productores y consumidores.  
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
      
   int dato = buffer[indice];
   indice--;
   
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

# 2. Problema de los Fumadores
En este caso, disponemos nuevamente de un proceso estanquero que introduce datos en un mostrador (que tiene capacidad para un único dato). Según el tipo del dato, este debe ser consumidor por uno u otro fumador.  
  
El monitor se usaría de la siguiente forma:
```pascal
process Estanquero;
var ingrediente : integer;
begin
   while true do begin
      ingrediente = Producir();
      Estanco.ponerIngrediente(ingrediente);
      Estanco.esperarRecogida();
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


