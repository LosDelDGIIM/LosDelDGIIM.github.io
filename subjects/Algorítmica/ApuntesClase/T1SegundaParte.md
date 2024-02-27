**Autor:** José Juan Urrutia Milán

# Tema 1. Eficiencia de Algoritmos.
## Análisis de algoritmos.
El primer paso es identificar qué parámetro determina el tamaño del problema ($n$).  
Posteriormente, tenemos que tener claro como se analiza cada estructura del código:
1. Operaciones elementales.
2. Secuencias de sentencias.
3. Sentencias condicionales.
4. Sentencias repetitivas.
5. Llamadas a funciones no recursivas.
6. Llamadas a funciones recursivas.

### 1. Sentencias simples u Operaciones elementales.
Son aquellas instrucciones cuya ejecución no depende del tamaño del caso, como por ejemlo:
- Operaciones matemáticas básicas (sumas, multiplicaciones, ...).
- Comparaciones.
- Operaciones booleanas.
- Entradas y salidas.
  
Su tiempo de ejecución está acotado superiormente por una constante.  
Su órden es $O(1)$.

### 2. Secuencias de sentencias.
Constan de la ejecución de secuencias dse bloques de sentencias:
```cpp
Sentencia_1;
Sentencia_2;
// ...
Sentencia_r;
```
Suponiendo que cada sentencia $i$ tiene eficiencia $O(f_i(n))$, la eficiencia de la secuencia se obtiene mediante las reglas de la suma y del máximo:
$$O(f_1(n) + f_2(n) + \ldots + f_r(n)) = \max\left[O(f_1(n)), O(f_2(n)), \ldots, O(f_r(n))\right]$$

### 3. Sentencias condicionales.
Constan de la evaluación de una condición y la ejecución de un bloque de sentencias. Puede ejecutarse la ```Sentencia1``` o la ```Sentencia2```, en función de la veracidad o falsedad de la condición:
```cpp
if(condicion){
    Sentencia1;
}else{
    Sentencia2;
}
```

#### Peor caso.
El órden de eficiencia del peor caso (notación $O$) viene dado por:
$$O(\mbox{estructura condicional}) = \max\left[O(\mbox{condicion}), O(\mbox{Sentencia1}), O(\mbox{Sentencia2})\right]$$
##### Justificación.
Como justificación para la fórmula, démonos cuenta de que la ejecución de la estructura condicional es igual a una de las siguientes secuencias de instrucciones (dependerá de la condición la ejecución de una o de otra):
```cpp
bool a = condicion;
Sentencia1;
```
```cpp
bool a = condicion;
Sentencia2;
```
La notación $O$ trata de buscar el órden del mayor tiempo de ejecución, por lo que buscaremos la secuencia que más tarde de las dos:
$$O(\mbox{estructura condicional}) = \max\left[O(\mbox{Secuencia1}), O(\mbox{Secuencia2})\right]$$
Usando la relga para secuencias de instrucciones vista anteriormente, podemos expresar cada órden como:
$$O(\mbox{Secuencia1}) = \max\left[O(\mbox{condicion}), O(\mbox{Sentencia1})\right]$$
$$O(\mbox{Secuencia2}) = \max\left[O(\mbox{condicion}), O(\mbox{Sentencia2})\right]$$
Por lo que:
$$O(\mbox{estructura condicional}) = \max\left[O(\mbox{Secuencia1}), O(\mbox{Secuencia2})\right] =$$
$$= \max\left[\max\left[O(\mbox{condicion}), O(\mbox{Sentencia1})\right], \max\left[O(\mbox{condicion}), O(\mbox{Sentencia2})\right]\right] =$$
$$= \max\left[O(\mbox{condicion}), O(\mbox{Sentencia1}), O(\mbox{Sentencia2})\right]$$


#### Mejor caso.
El órden de eficiencia del mejor caso (notación $\Omega$) viene dado por:
$$\Omega(\mbox{estructura condicional}) = \Omega(\mbox{condicion}) + \min\left[\Omega(\mbox{Sentencia1}), \Omega(\mbox{Sentencia2})\right]$$
##### Justificación.
Buscamos expresar el órden de ejecución en el mejor caso. Al igual que en la justificación anterior, el bloque condicional es equivalante a seleccionar una de dos secuencias:
```cpp
bool a = condicion;
Sentencia1;
```
```cpp
bool a = condicion;
Sentencia2;
```
Nos damos cuenta de que la condición siempre se ejecuta y luego se ejecuta una sentencia. Como estamos en el mejor caso, seleccionamos la sentencia que tarde menos tiempo en ejecutarse. Por esto, tenemos que el órden de ejecución es la suma del órden de la condición más el mínimo del órden de las dos sentencias.

#### Ejemplo.
Dado el siguiente código, buscamos su órden de ejecución en el peor y mejor casos:
```cpp
if(n%2 == 1){
    cout << "Es impar";
}else{
    // código de órden n
}
```
Aplicamos las fórmulas anteriormente vistas, sabiendo que la condición y la salida son de órden $O(1)$ al ser sentencias simples:
$$O(\mbox{estructura condicional}) = \max\left[O(\mbox{condicion}), O(\mbox{Sentencia1}), O(\mbox{Sentencia2})\right] = \max\left[O(1), O(1), O(n)\right] = O(n)$$
$$\Omega(\mbox{estructura condicional}) = \Omega(\mbox{condicion}) + \min\left[\Omega(\mbox{Sentencia1}), \Omega(\mbox{Sentencia2})\right] = \Omega(1) + \min\left[\Omega(1), \Omega(n)\right] = \Omega(1)$$

### 4. Sentencias repetitivas.
Constan de la evaluación de uan condición y la ejecución de un bloque de sentencias, mientras que dicha condición se cumpla. Tienen la siguiente forma:
```cpp
Mientras(condición){
    BloqueSentencias;
}
```
Suponiendo que:
- El bloque de sentencias tiene eficiencia $f(n)$.
- La evaluación de la condición tiene eficiencia $g(n)$.
- El bucle se ejecuta $h(n)$ veces.
Entonces, la eficiencia será:
$$O(\mbox{estructura repetitiva}) = O(g(n) + h(n) \cdot (g(n)+f(n)))$$

##### Justificación.
La condición se comprueba al menos una vez, por ello se suma.  
Cada iteración tiene un costo de $g(n) + f(n)$.  
El bucle realiza $h(n)$ iteraciones.

##### Ejemplo.
Dado el siguiente código, calcular su eficiencia.
```cpp
while(n > 0){
    cout << n;
    n--;
}
```
Evaluación de la condición: $g(n) = 1$.  
Bloque de sentencias: $f(n) = \max(O(1), O(1)) = 1$.  
Repeticiones: $h(n) = n$.  
$$O(\mbox{estructura repetitiva}) = g(n) + h(n)\cdot (g(n)+f(n)) = 1+n\cdot (1+1) = 2\cdot n+1 \Rightarrow O(2\cdot n+1)$$
Aplicando la relga del máximo: $O(2\cdot n+1) = \max(O(2\cdot n), O(1)) = O(2\cdot n)$.  
Simplificando la constante: La secuencia repetitiva es $O(n)$.

#### 4.1. Bucles for.
Constan de la inicialización de una variable, comprobación de una condición y actualización de la variable. Se ejecutará un bloque de sentencias mientras que la condición se cumpla:
```cpp
for(Inicialización; Condición; Actualización){
    BloqueSentencias;
}
```
Suponiendo que:
- El bloque de sentencias tiene eficiencia $f(n)$.
- La evaluación de la condifición tiene eficiencia $g(n)$.
- El bucle se ejecuta $h(n)$ veces.
- La actualización tiene eficiencia $a(n)$.
- La inicialización tiene eficiencia $i(n)$.

La eficiencia de una estructura de este tipo viene dada por:
$$O(\mbox{for}) = O(i(n)+g(n) + h(n) \cdot (g(n)+f(n)+a(n)))$$

##### Justificación.
La inicialización tiene lugar una vez.
La condición se comprueba al menos una vez, por ello se suma.  
Cada iteración tiene un costo de $g(n) + f(n) + a(n)$.  
El bucle realiza $h(n)$ iteraciones.

##### Ejemplo.
Dado el siguiente código, calcular su eficiencia:
```cpp
while(n > 0){
    for(int i = 1; i <= n; i*=2){
        cout << i;
    }
    n--;
}
```
Comenzamos analizando el bucle interno:
- Inicialización: $O(1)$.
- Condición: $O(1)$.
- Actualización: $O(1)$.
- Bloque de sentencias: $O(1)$.
- Veces que se ejecuta: $O(\log_2(n))$.
  
Eficiencia del bucle:
$$O(1)+O(1)+O(\log_2(n))\cdot (O(1)+O(1)+O(1)) = O(\log_2(n))$$
  
Ahora, analizamos el bucle externo:
- Condición: $O(1)$.
- Bloque de sentencias: $O(\log_2(n)+1)$.
- Veces que se ejecuta: $O(n)$.
  
Eficiencia del bucle:
$$O(1)+O(n)\cdot (O(1)+O(\log_2(n)+1)) = O(n\cdot \log_2(n))$$
Despreciando la base del logaritmo:
$$O(n\log(n))$$

### 5. Funciones no recursivas.
#### 5.1. Eficiencia de la función.
La eficiencia de la función se calcula como una secuencia de sentencias o bloques.
#### 5.2. Eficiencia de la llamada a función.
Depende de si sus parámetros de entrada dependen o no del tamaño del problema.

[Volver al índice](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/Algor%C3%ADtmica/ApuntesClase/Indice.md)
