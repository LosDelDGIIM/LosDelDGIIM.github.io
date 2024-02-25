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
$f(n)$ es $O(g(n)) \Rightarrow \exists K_1 \in \mathbb{R}^{+}, \exists n_0 \in \mathbb{N} \mid f(n) \leq K_1 \cdot g(n)~~\forall n \geq n_0$  
$g(n)$ es $O(h(n)) \Rightarrow \exists K_2 \in \mathbb{R}^{+}, \exists m_0 \in \mathbb{N} \mid g(n) \leq K_2 \cdot h(n)~~\forall n \geq m_0$  
$$f(n) \leq K_1 \cdot g(n) \leq K_1 \cdot K_2 \cdot h(n)~~\forall n\geq \max(n_0, m_0)$$
Luego $f(n) \leq (K_1 \cdot K_2) \cdot h(n)~~\forall n\geq k_0=\max(n_0, m_0) \Rightarrow f(n)$ es $O(h(n))$.

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

## Órdenes con varios parámetros.
% TODO: copiar de apuntes

## Análisis de algoritmos.
El primer paso es identificar qué parámetro determina el tamaño del problema ($n$).  
Posteriormente, tenemos que tener claro como se analiza cada estructura del código.

### Sentencias simples.
Su ejecución está acotado superiormente por una constante.  
Su tiempo de ejecución no depende del tamaño del problema.  
Asumimos que todas las operaciones básicas son de orden constante.  

### Sentencias condicionales.
El tiempo de la estructura condicional es el máximo de la eficiencia entre los bloques del ```if``` y del ```else```.  
Además, debemos tener en cuenta sumarle la eficiencia de la operación de comparación.  
%TODO: completar con apuntes, mejor y peor caso.
