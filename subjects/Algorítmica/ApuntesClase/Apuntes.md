# Introducción.
## Problemas como motivación.
### Parque de Atracciones.
Disponemos de un conjunto de atracciones $A_1, \ldots, A_n$.  
Para cada atracción tenemos la hora de inicio y la hora de fin.

#### Problema 1.
Seleccionar el mayor número de atracciones que un individuo pueda visitar.

#### Problema 2.
Seleccionar las atraciones que permitan que un visitante esté ocioso el menor tiempo posible.

#### Problema 3.
Conocidas las valoraciones de los usuarios, $val(A_i)$, seleccionar aquellas que garanticen la máxima valoración conjunta en la estancia.

### Optimizar robot.
El robot debe soldar $n$ puntos en un plano. Buscamos el orden en el cual el robot debe soldar los puntos.  
Minimizar el tiempo en realizar la operación (depende de la distancia).

## Nociones de conceptos.
- ```Instancia```: Ejemplo particular de un problema.
- ```Caso```: Instancia de un problema con una dificultad idéntica o muy similar.  
  
Tendremos generalmente tres casos: el mejor caso (instancia con menor número de operaciones/comparaciones), el peor caso (instancia con mayor número de operaciones/comparaciones) y el caso promedio.  
Para notar la eficiencia del peor caso, usaremos $O(\cdot)$, mientras que para el mejor caso, $\Omega(\cdot)$.
Normalmente, el peor caso y el promedio se comportan de forma similar.  
  
- ```Algoritmo estable```: Dado un problema de ordenación, si el criterio de orden es igual en dos casos, el orden de estos vendrá dado por el primero que se introdujo en la entrada.  
Por ejemplo, un algoritmo estable de ordenación de enteros en el que los pares son menores que los impares con la instancia ```1, 2, 3, 4```, la salida será:  
```2, 4, 1, 3```  
  
## Algoritmos de ordenación.
Burbuja es el peor algoritmo de ordenación.  
Cuando se tienen pocos elementos, suele ser más rápido un algoritmo simple como selección o inserción.
Selección hace muchas comparaciones y pocos intercambios, mientras que inserción hace menos comparaciones pero más intercambios.  
Por tanto, ante unos datos pesados con varios registros, selección será mejor que inserción.
  
Cuando se tienen muchos datos, es mejor un algoritmo $n \log(n)$.  

# Tema 1. Eficiencia de Algoritmos.
La asignatura se centrará en eficiencia basada en el tiempo de ejecución (no en la eficiencia en cuanto espacio, memoria usada por el programa).  
  
Para calcular la eficiencia de un algoritmo, tenemos:
- Método empírico: Tiempo real.
- Método teórico: Tiempo esperado.
- Método híbrido: Tiempo teórico sin evitar constantes.
  
## Principio de Invarianza.
Dadas dos implementaciones $I1$, $I2$ de un algoritmo, el tiempo de ejecución para una misma instancia de tamaño $n$, $T_{I1}(n)$ y $T_{I2}(n)$, no diferirá en más de una constante multiplicativa. Es decir, $\exists K > 0$ que verifica: $$T_{I1}(n) \leq K \cdot T_{I2}(n)$$
Por lo que podemos despreciar las constantes.  
  
En un principio, se asumiriá que operaciones básicas como sumas, multiplicaciones, etc. serán de tiempo constante, salvo excepciones (por ejemplo, multiplicaciones de números de 100000 dígitos).  

## Notación O.
Se dice que un algoritmo $A$ es de orden $O(f(n))$, donde $f$ es una función $f:\mathbb{N}\rightarrow \mathbb{R}^{+}$, cuando existe una implementación del mismo tamaño cuyo tiempo de ejecución $T_A(n)$ es menor igual que $K \cdot f(n)$, donde $K$ es una constante real positiva a partir de un tamaño grande $n_0$. Formalmente:
$$A \mbox{ es } O(f(n)) \Leftrightarrow \exists K \in \mathbb{R}^{+}, \exists n_0 \in \mathbb{N} \mid T_A(n) \leq K \cdot f(n)~~\forall n \geq n_0$$
La notación $O$ nos permite conocer cómo se comportará el algoritmo en términos de eficiencia en instancias del caso pero del problema:  
Como mucho, sabemos que el algoritmo no tardará más de $K \cdot f(n)$ en ejecutarse, en el peor de los casos.  
  
Al decir que el algoritmo $A$ es de orden $O(f(n))$, decimos que siempre podemos encontrar una constante positiva $K$ que para valores muy grandes del caso $n$ (a partir de un $n_0$), el tiempo de ejecución del algoritmo siempre será inferior a $K \cdot f(n)$:
$$T_A(n) \leq K \cdot f(n)$$
  
### Órdenes de eficiencia.
Ejemplos de órdenes de eficiencia son:
- Constante, $O(1)$.
- Logarítmico, $O(\log(n))$.
- Lineal, $O(n)$.
- Cuadrático, $O(n^2)$.
- Exponencial, $O(a^n)$.
- $\ldots$

### Equivalencia de órdenes.
Para saber si dos órdenes $O(f(n))$ y $O(g(n))$ son equivalentes o no, aplicamos las siguientes reglas:
$$O(f(n)) \equiv O(g(n)) \Leftrightarrow \lim_{n \to \infty} \dfrac{f(n)}{g(n)} \rightarrow K \in \mathbb{R}^{+}$$
$$O(f(n)) > O(g(n)) \Leftrightarrow \lim_{n \to \infty} \dfrac{f(n)}{g(n)} \rightarrow \infty$$
$$O(f(n)) < O(g(n)) \Leftrightarrow \lim_{n \to \infty} \dfrac{f(n)}{g(n)} \rightarrow 0$$
Entendiendo que un órden es menor que otro si es mejor, es decir, más rápido en el caso asintótico.

#### Ejemplos.
###### Ejemplo 1.
Si tenemos dos algoritmos $A$ y $B$ con órdenes de eficiencia $O(n^2)$ y $O((4n+1)^2+n)$ respectivamente, tratamos de ver qué algoritmos es más eficiente:
$$\lim_{n\to \infty} \dfrac{f(n)}{g(n)} = \lim_{n\to\infty}\dfrac{n^2}{(4n+1)^2+n)} = \lim_{n\to\infty}\dfrac{n^2}{(16n^2 +1+2\cdot 4n\cdot 1)+n} = \lim_{n\to\infty}\dfrac{1}{16}$$
Gracias al criterio de comparación entre órdenes, tenemos que los algoritmos $A$ y $B$ son equivalentes.

##### Ejemplo 2.
En esta ocasión, tenemos a dos algoritmos $A$ y $B$ con órdenes de eficiencia de $O(2^n)$ y $O(3^n)$, respectivamente.
$$\lim_{n\to\infty}\dfrac{f(n)}{g(n)} = \lim_{n\to\infty}\dfrac{2^n}{3^n}=\lim_{n\to\infty}\left(\dfrac{2}{3}\right)^n = 0$$
Por el criterio de comparación entre órdenes, $A$ es más eficiente que $B$.

##### Ejemplo 3.
El algoritmo $A$ tiene una eficiencia $O(n)$ y el algoritmo $B$ tiene una eficiencia de $O(n\log(n))$. Buscamos cuál es más eficiente.
$$\lim_{n\to\infty}\dfrac{f(n)}{g(n)}=\lim_{n\to\infty}\dfrac{n}{n\log(n)}=\lim_{n\to\infty}\dfrac{1}{\log(n)} = 0$$
Por lo que $A$ es más eficiente que $B$, por el criterio de comparación entre órdenes.

##### Ejemplo 4.
Disponemos de dos algoritmos, $A$ y $B$ con órdenes de eficiencia $O((n^2+29)^2)$ y $O(n^3)$ respectivamente. Intuimos que $B$ es más eficiente que $A$ pero queremos probarlo.
$$\lim_{n\to\infty}\dfrac{f(n)}{g(n)} = \lim_{n\to\infty}\dfrac{(n^2+29)^2}{n^3} = \infty$$
Gracias al criterio de comparación entre órdenes, hemos probado lo que esperábamos; $B$ es más eficiente que $A$.

##### Ejemplo 5.
Se quiere probar que $O(\log(n))$ es más eficiente que $O(n)$.
$$\lim_{n\to\infty}\dfrac{f(n)}{g(n)} = \lim_{n\to\infty}\dfrac{n}{\log(n)} = \lim_{n\to\infty}\dfrac{10^n}{n} = \infty$$
Por el criterio de comparación entre órdenes, lo acabamos de probar.

##### Ejemplo 6.
Se quiere dar un ejemplo de que el órden de eficiencia de los logaritmos es equivalente sin importar la base de este. Podemos ver qué sucede con $O(\log_2(n))$ y con $O(\log_3(n))$:
$$\lim_{n\to\infty}\dfrac{\log_3(n)}{\log_2(n)} = \lim_{n\to\infty}\dfrac{\ln(2)}{\ln(3)}$$
Por lo que ambos algoritmos tienen el mismo órden de eficiencia.

## Notación Omega.
Se dice que un algoritmo $A$ es de orden $\Omega(f(n))$, donde $f$ es una función $f:\mathbb{N}\rightarrow \mathbb{R}^{+}$, cuando existe una implementación del mismo tamaño cuyo tiempo de ejecución $T_A(n)$ es mayor igual que $K \cdot f(n)$, donde $K$ es una constante real positiva a partir de un tamaño grande $n_0$. Formalmente:
$$A \mbox{ es } \Omega(f(n)) \Leftrightarrow \exists K \in \mathbb{R}^{+}, \exists n_0 \in \mathbb{N} \mid T_A(n) \geq K \cdot f(n)~~\forall n > n_0$$
La notación $\Omega$ nos permite conocer cómo se comportará el algoritmo en términos de eficiencia en instancias del caso mejor del problema:  
Como poco, sabemos que el algoritmo no t ardará menos de $K\cdot f(n)$ en ejecutarse, en el mejor de los casos.

## Notación theta.
Se dice que un algoritmo $A$ es de orden exacto $\theta(f(n))$, donde $f$ es una función $f:\mathbb{N}\rightarrow \mathbb{R}^{+}$, cuando existe una implementación del mismo tamaño cuyo tiempo de ejecución $T_A(n)$ es igual que $K \cdot f(n)$, donde $K$ es una constante real positiva a partir de un tamaño grande $n_0$. En este caso, el algoritmo es simultáneamente de orden $O(f(n))$ y $\Omega(g(n))$.
$$A \mbox{ es } \theta(f(n)) \Leftrightarrow \exists K \in \mathbb{R}^{+}, \exists n_0 \in \mathbb{N} \mid T_A(n) = K \cdot f(n)~~\forall n > n_0$$

## Propiedades.
Se queda como ejercicio demostrar formalmente las siguientes propiedades:
### Transitividad.
Si $f(n) \in O(g(n))$ y $g(n) \in O(h(n)) \Rightarrow f(n) \in O(h(n))$.  
También para $\Omega$ y $\theta$.

##### Demostración.
$f(n)$ es $O(g(n)) \Rightarrow \exists K_1 \in \mathbb{R}^{+}, \exists n_0 \in \mathbb{N} \mid f(n) \leq K_1 \cdot g(n)$  $\forall n \geq n_0$  
$g(n)$ es $O(h(n)) \Rightarrow \exists K_2 \in \mathbb{R}^{+}, \exists m_0 \in \mathbb{N} \mid g(n) \leq K_2 \cdot h(n)$  $\forall n \geq m_0$  
$$f(n) \leq K_1 \cdot g(n) \leq K_1 \cdot K_2 \cdot h(n)$  $\forall n\geq \max(n_0, m_0)$$
Luego $f(n) \leq (K_1 \cdot K_2) \cdot h(n)$  $\forall n\geq k_0=\max(n_0, m_0) \Rightarrow f(n)$ es $O(h(n))$.

### Reflexiva.
$f(n) \in O(f(n))$  
También para $\Omega$ y $\theta$.

### Simétrica.
$f(n) \in \theta(g(n)) \Leftrightarrow g(n) \in \theta(f(n))$

### Suma.
Si $T_1(n) \in O(f(n))$ y $T_2(n) \in O(g(n))$. Entonces:
$$T_1(n) + T_2(n) \in O(max(f(n), g(n)))$$

### Producto.
Si $T_1(n) \in O(f(n))$ y $T_2(n) \in O(g(n))$. Entonces:
$$T_1(n) \cdot T_2(n) \in O(f(n) \cdot g(n))$$

### Regla del máximo.
$O(f(n)+g(n)) = \max(O(f(n)), O(g(n)))$

### Regla de la suma.
$O(f(n)+g(n)) = O(f(n))+O(g(n))$

### Regla del producto.
$O(f(n)\cdot g(n)) = O(f(n))\cdot O(g(n))$

## Órdenes con varios parámetros.
En ocasiones, el tamaño del problema no dependerá de una única variable $n$, sino que podrá depender de varias.  
  
En estos casos, se analiza de igual forma que en el caso de una variable, pero con una función de varias variables. Conocida una función $f:\mathbb{N}\times\mathbb{N}\rightarrow \mathbb{R}^{+}$:
$$A \mbox{ es } O(f(n,m)) \Leftrightarrow \exists K \in \mathbb{R}^{+} \mid T_A(n,m) \leq K \cdot f(n,m)\mbox{   } \forall n,m\in \mathbb{N}$$

### Ejemplo.
Por ejemplo, el órden de eficiencia del algoritmo canónico (el que todos conocemos) de suma de matrices $n\times m$ es de órden $O(n\cdot m)$.

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

