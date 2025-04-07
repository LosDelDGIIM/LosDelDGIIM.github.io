
# Métodos Numéricos II. Test Primer Parcial.

**Autor:** Lucas Hidalgo Herrera   
**Descripción:** Test de los temas 1 y primera parte del 2.

---



1. Sea \\(g\\) una función real continua en un intervalo \\([a, b]\\).
    - [x] Si \\( g \\) toma valores en \\([ \frac{a+b}{2}, b ]\\), entonces tiene al menos un punto fijo en \\([a, b]\\).
    - [ ] La ecuación \\(x = g(x)\\) tiene una única raíz en \\([a, b]\\).
    - [x] Si \\(g\\) toma valores en \\([a, b]\\) y es contráctil, entonces tiene un único punto fijo en \\([a, b]\\).
    - [ ] Si \\(g\\) toma valores en \\([a, b]\\) y es derivable con derivada menor que 1 en todo punto, entonces el correspondiente método de iteración funcional es convergente partiendo de un punto diferente de \\(s\\) pero suficientemente cercano.
    - [x] Si \\( g \\) toma valores en \\([a, b]\\), entonces tiene al menos un punto fijo en \\([a, b]\\).
    - [ ] La ecuación \\( x = g(x) \\) tiene al menos una raíz en \\([a, b]\\).
    - [ ] Si \\( g \\) toma valores en \\([a, b]\\) y es derivable, entonces el correspondiente método de iteración funcional es convergente partiendo de un punto diferente de \\( s \\) pero suficientemente próximo a \\( s \\).
 
2. Sea \\(f\\) una función continua en \\([a, b]\\) con valores en \\(\mathbb{R}\\), tal que \\(f(a)f(b) < 0\\).
    - [ ] Si \\(f\\) es derivable en \\([a, b]\\) la ecuación \\(f(x) = 0\\) tiene una sola raíz en \\([a, b]\\).
    - [x] Si la derivada de \\(f\\) existe y en todo el intervalo abierto es negativa, entonces hay solo una raíz de \\(f(x) = 0\\) en el intervalo.
    - [x] Tanto el método de bisección como el de Regula Falsi son convergentes, pero pueden converger a dos raíces diferentes de la ecuación \\(f(x) = 0\\).
    - [x] La ecuación \\(f(x) = 0\\) tiene al menos una raíz en el intervalo abierto \\([a, b]\\).
    - [ ] Si la derivada de \\(f\\) existe y en todo el intervalo abierto es negativa, entonces el método de NR converge a la única raíz de \\(f(x) = 0\\), partiendo del centro del intervalo.
    - [x] El método de la secante es aplicable pero no tiene garantía de convergencia a ninguna de las raíces de la ecuación \\(f(x) = 0\\).
    - [x] Si \\(f\\) es suficientemente derivable y en todo el intervalo abierto su primera derivada es negativa, entonces el método de NR converge a la única raíz de \\(f(x) = 0\\), partiendo de cualquier punto de algún subintervalo que contenga a la raíz.


3. Iteraciones

    - [x] El método de Newton-Raphson requiere una semilla.
    - [x] El método de la Secante obtiene cada aproximación a partir de los dos anteriores.
    - [ ] El método de Newton-Raphson tiene siempre convergencia local cuadrática.
    - [ ] El método de la secante requiere una semilla.
    - [x] El método de iteración funcional requiere una semilla.
    - [ ] El método de Bisección requiere una semilla.
    - [x] Si la raíz es simple, entonces el método de Newton-Raphson tiene convergencia local al menos cuadrática.
    - [x] Cuando las aproximaciones están muy próximas a la solución, el método de la Secante puede incurrir en división por cero al computar.

 
5. Si la función \\(f(x)\\) no es derivable, pero es continua y \\(f(a)f(b) < 0\\), entonces puedo aplicar los métodos de:

    - [ ] Sólo los métodos de iteración funcional.
    - [ ] Newton-Raphson y secante.
    - [ ] Bisección y Newton-Raphson.
    - [x] Bisección, Secante y Regula Falsi.
    - [ ] Todos los métodos estudiados.
    - [x] Bisección.
    
  
6. Tiene orden de convergencia local al menos cuadrático...

    - [ ] La iteración funcional cuando \\(|g'(s)| < 1\\).
    - [x] El método de Newton-Raphson cuando la raíz es simple.
    - [ ] El método de la secante cuando la raíz es simple.
    - [x] La iteración funcional cuando \\(g \in \mathcal{C}^2\\) y \\(|g'(s)| = 0\\).
    - [ ] El método de bisección.
    
7. Un algoritmo eficiente y estable para la evaluación de polinomios es:

    - [ ] El producto escalar del vector de coeficientes por el vector de potencias de la variable.
    - [ ] El de Sturm.
    - [ ] El de Newton-Raphson.
    - [ ] El de Bisección seguido del de Newton-Raphson.
    - [x] El de Horner.
    - [ ] El de Bisección.
    

8. Sea \\(f\\) una función real definida en un intervalo cerrado \\([a, b]\\). Entonces:

    - [x] No hay garantía de convergencia del método de la secante a una raíz de la ecuación \\(f(x) = 0\\), partiendo de las semillas \\(a\\) y \\(b\\) como valores iniciales.
    - [ ] Si \\(f(a)f(b) < 0\\) entonces hay al menos un punto \\(s\\) comprendido entre \\(a\\) y \\(b\\) en el cual la función vale cero.
    - [ ] Para que el método de la secante sea aplicable se necesita que \\(f(a)f(b) > 0\\).
    - [ ] La ecuación \\(f(x) = 0\\) tiene un número impar de raíces simples en \\([a, b]\\).
    - [ ] Si la ecuación \\(f(x) = 0\\) tiene una única raíz en \\([a, b]\\) siempre puede aplicarse el método de bisección para aproximarla con un error menor que 0.05.
    
  
10. Si tiene que resolver un sistema no lineal de dos ecuaciones, \\(F(X) = 0\\).

    - [ ] Aplicaría Newton-Raphson a cada una de las dos ecuaciones.
    - [x] Necesitaría dos semillas, una para cada componente.
    - [ ] Aplicaría primero el método de Bisección que es un método lento pero robusto.
    - [x] Si existe la matriz Jacobiana de orden \\(2 \times 2\\), asociada a \\(F\\), con determinante no nulo, aplicaría Newton-Raphson para sistemas.
    - [x] Lo más recomendable sería intentar resolverlo por el método de Newton-Raphson para sistemas, pero también se puede intentar escribir el sistema como \\(X = G(X)\\), que sea equivalente, y analizar si la correspondiente iteración funcional va a ser convergente.
    - [ ] Necesitaría dos semillas si se quiere resolver por el método de la secante.


11. Sucesión de Sturm

    - [x] Permite saber si una ecuación polinómica tiene raíces múltiples.
    - [x] En un cero de la primera función la derivada de dicha función tiene el mismo signo que la siguiente función.
    - [x] Si la sucesión consta de cuatro funciones y la tercera se anula en un punto \\(r\\), la segunda no se anula y su signo es el contrario que el de la cuarta en \\(r\\).
    - [x] Para obtener la tercera función de una sucesión de Sturm correspondiente a un polinomio cuyos ceros reales sean simples debemos dividir el polinomio entre su derivada y quedarnos con el resto cambiado de signo.
    - [ ] A partir de un polinomio cualquiera puede obtenerse una sucesión de Sturm que tiene a dicha función como la primera función de dicha sucesión.
    - [x] Permite separar raíces reales de una ecuación polinómica en intervalos disjuntos.
    - [ ] Para construir una sucesión de Sturm a partir de un polinomio, se pone en primer lugar ese polinomio, en segundo lugar su derivada, y así sucesivamente hasta que se obtenga una función constante.
    - [x] En un cero de la primera función la derivada de esa función es no nula.

 
12. Si \\(s\\) es una raíz de multiplicidad \\(m > 1\\) del polinomio \\(p\\), entonces también es raíz de \\(p'\\) pero con multiplicidad:

    - [ ] \\(m\\)
    - [ ] 1
    - [ ] 2
    - [ ] No se puede saber, depende de otros factores.
    - [ ] \\(m - 2\\)
    - [x] \\(m - 1\\)
    - [ ] No es raíz de \\(p'\\).

 
13. Para poder aplicar el método de la secante, la función \\(f(x)\\) ha de ser necesariamente:

    - [x] Continua.
    - [ ] Derivable \\(1 + \frac{\sqrt{5}}{2}\\) veces.
    - [ ] Creciente.
    - [ ] Derivable dos veces.
    - [ ] Derivable una vez.


14. La sucesión \\(x_n\\) converge a \\(s\\) linealmente con constante asintótica del error \\(L = 1/\sqrt[5]{100}\\) entonces, a largo plazo...

    - [x] se ganan 2 dígitos de precisión cada 5 términos
    - [ ] se ganan 100 dígitos de precisión cada 5 términos
    - [ ] no puede ser convergente
    - [ ] se ganan 5 dígitos de precisión cada 100 términos
    - [ ] se ganan 5 dígitos de precisión cada 2 términos

 
15. Sucesión de Sturm

    - [x] Todas las funciones son continuas, al menos, y la primera debe ser como mínimo derivable.
    - [ ] Basta con que las funciones que la componen sean continuas en el intervalo común de definición.
    - [ ] Sirve exclusivamente para saber cuántas raíces reales tiene una ecuación polinómica.
    - [x] La última función no cambia de signo en el intervalo que estamos considerando.
    - [ ] Todas las funciones que la componen deben ser de clase uno o superior.
    - [x] Permite saber cuántas raíces complejas tiene una ecuación polinómica cuyas raíces reales son simples.
    - [ ] La sucesión de Sturm nos permite saber si un método iterativo converge o diverge.
    - [x] La primera de las funciones debe ser derivable en todo el intervalo que estamos considerando.

  
16. Toda función de iteración \\(g(x)\\) definida en \\([0, 10]\\)...

    - [ ] con valores en el intervalo \\([5, 7]\\) tiene al menos un punto fijo.
    - [ ] continua y con valores en el intervalo \\([5, 7]\\) tiene un único punto fijo.
    - [ ] con valores en el intervalo \\([5, 7]\\) tiene un único punto fijo.
    - [x] con valores en el intervalo \\([5, 7]\\) y derivada en valor absoluto menor que 1 en \\([0, 10]\\) ha de tener un único punto fijo.
    - [x] continua y con valores en el intervalo \\([5, 7]\\) tiene al menos un punto fijo.
    
     
17. Sea \\(f\\) de clase 1, \\(s \in \mathbb{R}\\) es una raíz simple de \\(f\\) si y solo si

    - [x] \\(f(s) = 0 \ y \ f'(s) \neq 0\\)
    - [ ] \\(f(s) \neq 0 \ y \ f'(s) = 0\\)
    - [ ] \\(f(s) \cdot f'(s) = 0\\)
    - [ ] El método de Newton-Raphson converge localmente a \\(s\\)
    - [ ] \\(f(s) = 0 \ y \ f'(s) = 0\\)

 
18. La sucesión \\(x_n\\) converge a \\(s\\) linealmente con constante asintótica del error \\(L = 1/\sqrt{100000}\\). Entonces, a largo plazo...

    - [x] se ganan 5 dígitos de precisión cada 2 términos
    - [x] se ganan al menos 10 dígitos de precisión cada 5 términos
    - [ ] se ganan 2 dígitos de precisión cada 5 términos
    - [ ] se ganan 2 dígitos de precisión cada 100000 términos
    - [ ] no converge
    - [ ] se ganan 1 dígito de precisión cada 5 términos

 
19. Sea la ecuación \\(x = g(x)\\). Entonces, si \\(g\\) aplica el intervalo \\([a, b]\\) en \\([a, b]\\):

    - [ ] Si \\(g\\) es derivable y su derivada es negativa pero mayor que \\(-\frac{1}{2}\\), entonces el método de iteración funcional asociado genera una sucesión de aproximaciones decreciente hacia la raíz de la ecuación \\(x = g(x)\\).
    - [ ] Si \\(g\\) es derivable y su derivada está acotada en valor absoluto por \\(\frac{1}{2}\\) en todo el intervalo, entonces el método de iteración funcional asociado tiene convergencia al menos cuadrática.
    - [x] Si \\(g\\) es de clase 2 y en un punto fijo \\(s\\) verifica \\(g'(s) = 0\\), entonces partiendo de un valor suficientemente próximo a \\(s\\) el método de iteración funcional converge con orden de convergencia al menos cuadrático.
    - [x] Si \\(g\\) es derivable y su derivada está acotada en valor absoluto por \\(\frac{1}{2}\\) en todo el intervalo, entonces el método de iteración funcional asociado comete tras \\(n\\) iteraciones un error menor que \\(\frac{b-a}{2^n}\\).
    - [ ] El método de iteración funcional asociado coincide con el de NR cuando la función \\(g\\) es derivable.
    - [x] El método de iteración funcional asociado es localmente convergente a toda raíz \\(s\\) de dicha ecuación que verifique \\(-1 < g'(s) < 1\\).
    - [x] Si \\(g\\) es derivable y su derivada es positiva pero menor que \\(\frac{1}{2}\\), entonces el método de iteración funcional genera una sucesión de aproximaciones monótona hacia la raíz de la ecuación \\(x = g(x)\\)

  
20. Ecuaciones polinómicas

    - [ ] La ecuación \\(7x^7 - 12x^5 - 3x^3 + 1 = 0\\) no tiene raíces positivas.
    - [x] La ecuación \\(6x^7 - 2x^5 - 3x^3 + 1 = 0\\) tiene sus raíces reales en \\([-1.5, 1.5]\\)
    - [x] \\(7x^7 + 12x^5 + 3x^3 + 1 = 0\\) no tiene raíces positivas.
    - [ ] \\(x^7 - 21x^6 + 3x^3 - 12 = 0\\) no puede tener sus raíces reales fuera del intervalo \\([-13, 13]\\).
    - [ ] La ecuación \\(2x^7 - 12x^5 - 3x^3 + 1 = 0\\) no puede tener raíces con módulo mayor que 1.5
    - [x] La ecuación \\(7x^7 + 2x^5 - 3x^3 + 1 = 0\\) no puede tener raíces con módulo mayor que 1.5.
    - [x] \\(x^7 - 12x^5 + 3x^3 - 1 = 0\\) tiene sus raíces reales en \\([-13, 13]\\)
    - [ ] \\(7x^7 + 12x^5 + 3x^3 + 1 = 0\\) no tiene raíces reales.

 
21. El método de bisección

    - [ ] tiene orden de convergencia local al menos cuadrático
    - [ ] se puede extender a sistemas de ecuaciones no lineales
    - [x] exige las mismas condiciones que el teorema de Bolzano
    - [ ] requiere una semilla
    - [ ] es un método de iteración funcional
    - [x] tiene orden de convergencia lineal

 
22. Marque las afirmaciones que sean ciertas sobre el método de Bisección

    - [ ] Reduce el error a la mitad en cada iteración.
    - [x] La sucesión de cotas de errores en el método de bisección es monótona decreciente.
    - [ ] La sucesión de errores en el método de bisección es monótona decreciente.
    - [x] Permite calcular el número necesario de iteraciones para alcanzar una precisión dada, antes de realizarlas.
    - [ ] Tiene velocidad cuadrática de convergencia.
    - [ ] Ninguna de las demás.


23. Para poder aplicar el método de Newton-Raphson, la función \\(f(x)\\) tiene que ser
    - [ ] Dos veces derivable
    - [ ] Con que sea continua es suficiente
    - [ ] Creciente
    - [x] Derivable


24. La fórmula \\(f'(0)\approx0\\)
    - [x] Es exacta para todo polinomio que sea una función par.
    - [x] Es una fórmula de tipo interpolatorio con un solo nodo, que puede ser el que se quiera.
    - [ ] Es una de las fórmulas más precisas para aproximar el valor de la derivada de una función en cero.
    - [ ] Es exacta para \\(1,x, x^2, x^3, x^4\\).
    - [x] Es exacta para las funciones: \\(1, \cos(x)\\).
    - [x] Es exacta para \\(1,x^2,x^3,x^4\\).


25. Fórmulas de derivación numérica de tipo interpolatorio
    - [x] Una de las fórmulas de derivación numérica para aproximar \\(f'(a)\\) es \\(\frac{f(a+h)-f(a-h)}{2h}\\).
    - [x] Una de las fórmulas de derivación numérica para aproximar es \\(\frac{f(a)-f(a+h)}{-h}\\).
    - [ ] Las fórmulas de derivación numérica más habituales tienen un nodo, dos nodos o tres nodos.
    - [ ]Las fórmulas de derivación numérica son imprescindibles para derivar funciones de las que no se conoce una primitiva expresada en términos elementales.
    - [ ] Las fórmulas de derivación numérica pueden ser simples o compuestas
    - [ ] Una de las fórmulas de derivación numérica para aproximar más recomendable es \\(f(a+h)-f(a-h)/(2h)\\).
    - [x] Al aplicar una fórmula de derivación numérica, basada en los valores de la función en los puntos \\(a\\) y \\(a+h\\), el valor de \\(h\\) no puede ser nulo
    - [ ] Al aplicar una fórmula de derivación numérica, basada en los valores de la función en los puntos \\(a\\) y \\(a+h\\), el valor de \\(h\\) no puede ser negativo


26. Una fórmula de tipo interpolatorio clásico para aproximar la derivada \\(k\\)-ésima de en un punto ...
    - [x] que use \\(n\\) nodos, puede tener como máximo orden de exactitud \\(k+n-1\\).
    - [x] no tiene interés si el número de nodos es menor o igual que \\(k\\) .
    - [ ] que use \\(n\\) nodos, puede tener como máximo orden de exactitud \\(n+k\\).
    - [ ] que use \\(n\\) nodos, puede tener como máximo orden de exactitud \\(k\\).
    - [x] debe tener al menos \\(k+1\\) nodos, para que tenga algún interés.
    - [ ] que use \\(n\\) nodos, puede tener como máximo orden de exactitud \\(n-1\\).


28. Toda fórmula de derivación numérica de tipo interpolatorio clásico para aproximar una derivada \\(k\\)-ésima en \\(a\\) ...
    - [x] tiene al menos un coeficiente positivo y al menos otro negativo.
    - [x] tiene unos coeficientes que pueden obtenerse resolviendo un sistema lineal del mismo orden que el número de nodos.
    - [ ] tiene unos coeficientes que son idénticos.
    - [x] tiene unos coeficientes que son las derivadas \\(k\\)-ésimas, en \\(k\\), de los polinomios de Lagrange correspondientes a los nodos.
    - [x] tiene unos coeficientes que suman cero.
    - [ ] tiene unos coeficientes que son simétricos.


29. Fórmula:
    - [ ] Si la función \\(f\\) es suficientemente regular, siempre es posiblle aproximar el valor \\(f'(a)\\) con un error \\(|R(f)|<0.1\\), tomando un valor de \\(h\\) suficientemente pequeño en una fórmula de tipo interpolatorio clásico que use un nodo.
    - [x] Para aplicar una fórmula de derivación numérica para aproximar \\(f'(a)\\) se necesita poder obtener los valores \\(f\\) de en puntos cercanos al \\(a\\).
    - [ ] Una fórmula de derivación numérica para aproximar \\(f'a\\) con un error \\(|R(f)|<0.1\\),que sea convergente, salvo errores de computación, tiene que ser de tipo interpolatorio.
    - [x] Si la función \\(f\\) es suficientemente regular, siempre es posible aproximar el valor \\(f'(a)\\) con un error \\(|R(f)|<0.1\\), tomando un valor de \\(h\\)suficientemente pequeño en una fórmula de tipo interpolatorio clásico que use dos nodos.
    - [ ] No existe ninguna fórmula de derivación numérica para aproximar \\(f'(a)\\) con un error \\(|R(f)|<0.1\\) que tenga más de cinco nodos.
    - [ ] Para aplicar una fórmula de derivación numérica para aproximar \\(f'(a)\\) se necesita conocer la expresión de en un entorno del punto \\(a\\).


30. La fórmula \\(f'(3) \approx f(-1) + f(0) + f(2)\\)
    - [x] Tiene por término de error \\(R(f) = f'(3) - f(-1) - f(0) - f(2)\\)
    - [ ] Es de tipo interpolatorio clásico.
    - [ ] Es exacta de grado 1.
    - [ ] Es exacta de grado 0.
    - [x] No es de tipo interpolatorio clásico.


31. Grado de exactitud
    - [ ] Dos fórmulas de derivación numérica, de tipo interpolatorio clásico, para aproximar \\(f^{''}(a)\\), con los mismos nodos, pueden tener diferentes pesos.
    - [ ] El grado de exactitud de una fórmula de tipo interpolatorio clásico depende exclusivamente del número de nodos.
    - [ ] El grado de exactitud de una fórmula de tipo interpolatorio clásico no depende de sus nodos sino de los pesos.
    - [x] Dos fórmulas de derivación numérica, para aproximar \\(f^{''}(a)\\), con igual número de nodos, pueden tener diferentes pesos.
    - [x] El grado de exactitud de una fórmula de tipo interpolatorio clásico depende exclusivamente de quiénes sean sus nodos.
    - [ ] Dos fórmulas de derivación numérica, para aproximar \\(f^{''}(a)\\), con igual número de nodos, tienen el mismo grado de exactitud.
    - [x] Dos fórmulas de derivación numérica, para aproximar \\(f^{''}(a)\\), con diferente número de nodos, pueden tener el mismo grado de exactitud.


32. Una fórmula de derivación numérica de tipo interpolatorio clásico para aproximar \\(f'(a)\\)...
    - [ ] con dos nodos, no puede ser exacta en \\(\mathbb{P}_2\\).
    - [ ] con dos nodos, no puede ser exacta en \\(\mathbb{P}_1\\).
    - [ ] con dos nodos, puede ser exacta en \\(\mathbb{P}_3\\).
    - [x] con dos nodos, puede obtenerse imponiendo exactitud para las funciones \\(\{1,x\}\\).
    - [ ] con \\(n\\) nodos, es siempre exacta en \\(\mathbb{P}_n\\).
    - [x] con \\(n\\) nodos, podría ser exacta en \\(\mathbb{P}_n\\).
    - [x] con dos nodos, podría ser exacta en \\(\mathbb{P}_2\\).

 
33. El funcional lineal \\(f'(a)\\) puede aproximarse por la fórmula progresiva \\(P(h) = \frac{f(a+h)-f(a)}{h}\\) de tal forma que si \\(f\\) es suficientemente regular, desarrollando por Taylor se tiene \\(f'(a)=P(h)-\frac{h}{2}f^{''}(a)-\frac{h^2}{6}f^{'''}(a)-...=P(h)+c_1h+c_2h^2+...\\). Si ahora se escribe para \\(\frac{h}{2}\\) resulta \\(f'(a)=P(\frac{h}{2})+c_1\frac{h}{2}+c_2\frac{h^2}{4}+...\\)
    - [ ] No existe una combinación lineal de \\(P(h)\\) y \\(P(\frac{h}{2})\\)que permita obtener una fórmula para aproximar \\(f'(a)\\) con mayor orden de exactitud.
    - [x] No es posible establecer una combinación de \\(P(h)\\) y \\(P(\frac{h}{2})\\) que aumente la exactitud en 2 unidades.
    - [ ] Toda combinación lineal de \\(P(h)\\) y \\(P(\frac{h}{2})\\) mantiene el mismo orden de exactitud.
    - [x] La combinación \\(2P(\frac{h}{2})-P(h)\\) aumenta en una unidad el orden de exactitud.
    - [x] La combinación \\(\frac{1}{3}(2P(\frac{h}{2})+P(h))\\) no aumenta en una unidad el orden de exactitud,pero es convergente a \\(f'(a)\\) cuando \\(h\\) tiende a \\(0\\).
    - [ ] La combinación \\(\frac{1}{3}(2P(\frac{h}{2})+P(h))\\) aumenta en una unidad el orden de exactitud y es convergente a \\(f'(a)\\) cuando \\(h\\) tiende a \\(0\\).


35. Una fórmula de derivación numérica de tipo interpolatorio clásico (en los polinomios), para aproximar \\(f'(a)\\), que tenga dos nodos...
    - [ ] no puede ser exacta en \\(\mathbb{P}_2\\).
    - [x] es exacta en \\(\mathbb{P}_1\\).
    - [ ] puede obtenerse imponiendo exactitud para las funciones \\(x,x^2\\).
    - [ ] puede alcanzar un grado máximo de exactitud 3.


36. Para obtener tres fórmulas para aproximar respectivamente \\(f'(a)\\), \\(f^{''}(a)\\) y \\(f^{'''}(a)\\) se han elegido cinco abscisas diferentes, se ha calculado el polinomio \\(p(x)\\) de grado cuatro que interpola en ellas los valores de la función \\(f\\), y se ha derivando sucesivamente \\(p(x)\\) para obtenerlas.
    - [x] Las tres fórmulas de derivación numérica obtenidas son exactas para las funciones \\(x^3\\) y \\(x^4\\).
    - [x] Si las abscisas de interpolación están igualmente espaciadas con un paso \\(h\\) y uno de los cinco nodos es \\(a\\), la fórmula que aproxima \\(f'(a)\\) tendrá \\(h\\) en el denominador, la que aproxima \\(f^{''}(a)\\) tendrá \\(h^2\\) y la tercera tendrá \\(h^3\\).
    - [ ] Las tres fórmulas de derivación numérica obtenidas contienen el mismo número de nodos con pesos no nulos.
    - [ ] No se pueden obtener tres fórmulas de derivación numérica diferentes partiendo de un mismo polinomio de interpolación.
    - [x] Las tres fórmulas de derivación numérica obtenidas tienen unos pesos que suma cero.
    - [ ] Las tres fórmulas de derivación numérica obtenidas tienen el mismo orden de exactitud.
    - [ ] El procedimiento más simple es obtener la fórmula para \\(f'(a)\\) a partir de \\(p'(a)\\), y después derivar \\(f'(a)\\) un par de veces para obtener \\(f^{''}(a)\\) y \\(f^{'''}(a)\\).

37. El funcional lineal \\(f'(a)\\) puede aproximarse por la fórmula \\(P(h) = \frac{f(a+h)-f(a-h)}{2h}\\) de tal forma que si \\(f\\) es suficientemente regular, desarrollando por Taylor se tiene \\(f'(a)=P(h)+c_2h^2+c_4h^4+...\\), que escrita para \\(\frac{h}{2}\\) es \\(f'(a)=P(\frac{h}{2})+c_2\frac{h^2}{4}+c_4\frac{h^4}{16}+...\\). Este proceso es el de extrapolación de Richardson aplicado a una fórmula de derivación numérica. Entonces:
    - [ ] \\(\frac{1}{3}(4P(\frac{h}{2})+P(h))\\) aumenta la exactitud con respecto a \\(P(h)\\) en 2 unidades.
    - [x] \\(P(h)\\) es la aproximación \\(f'(a)\\) con la fórmula centrada.
    - [x] \\(\frac{1}{3}(4P(\frac{h}{2})-P(h))\\) aumenta la exactitud con respecto a \\(P(h)\\) al menos en una unidad.
    - [ ] No es posible establecer una combinación de \\(P(h)\\) y \\(P(\frac{h}{2})\\) que aumente la exactitud en 2 unidades.
    - [ ] \\(\frac{1}{3}(2P(\frac{h}{2})+P(h))\\) aumenta la exactitud con respecto a \\(P(h)\\) en al menos una unidad.
    - [ ] \\(2P(\frac{h}{2})-P(h)\\) aumenta la exactitud con respecto a \\(P(h)\\) en una unidad.
    - [ ] \\(P(h)\\) tiene orden de exactitud 1.

38. Si \\(g\\) es derivable y aplica \\([a,b]\\) en \\([a,b]\\). Entonces:
    - [x] Si existe la derivada segunda de \\(g\\) y se verifica que \\(g(s)=s\\) y \\(g'(s)=g^{''}(s)=0\\), la convergencia local del método de iteración funcional es al menos cúbica.
    - [x] Si \\(g(s)=s\\) y \\(g'(s)=0\\), existe un entorno de \\(s\\) en cual la convergencia a \\(s\\) del método de iteración funcional asociado a \\(g\\) es al menos cuadrática. 
    - [ ] Si existe la derivada segunda de \\(g\\) y se verifica que \\(g^{''}(s)=0\\), la convergencia del método de iteración funcional es al menos cúbica.
    - [ ] Si \\(g(s)=s\\) y \\(g'(s)=0\\), existe un entorno de \\(s\\) en cual la convergencia a \\(s\\) del método de iteración funcional asociado a es más rápida que si aplicamos el método de NR a \\(f(x)=x-g(x)\\).
    - [ ] Si existe la derivada segunda de \\(g\\) y se verifica que \\(g(s)=s\\) y \\(g'(s)=g^{''}(s)=0\\), la convergencia local del método de iteración funcional es cúbica.
    - [x] Si existe la derivada segunda de \\(g\\) y se verifica que \\(g(s)=s\\) y \\(g'(s)=g^{''}(s)=0\\), la convergencia local del método de iteración funcional es al menos cuadrática.
    - [ ] Si \\(g(s)=s\\) y \\(g'(s)=0\\), existe un entorno de \\(s\\) en cual la convergencia a \\(s\\) del método de iteración funcional asociado a \\(g\\) es exactamente cuadrática.


39. Error:
    - [x] El error de una fórmula de derivación numérica de tipo interpolatorio, para aproximar \\(f'(a)\\), es la derivada del error de interpolación correspondiente, evaluada en \\(a\\).
    - [ ] El error de una fórmula de derivación numérica de tipo interpolatorio, para aproximar \\(f'(a)\\), puede obtenerse derivando \\(f[x_0,x_1,...,x_n,x]\\) y evaluando en \\(a\\).
    - [x] La derivada de \\(f[x_0,x_1,...,x_n,x]\\) es \\(f[x_0,x_1,...,x_n,x,x]\\) y la derivada segunda es \\(2f[x_0,x_1,...,x_n,x,x,x]\\).
    - [ ] La derivada de \\(f[x_0,x_1,...,x_n,x]\\) es \\(f[x_0,x_1,...,x_n,x,x]\\) y la derivada segunda es \\(f[x_0,x_1,...,x_n,x,x,x]\\).
    - [x] El error de una fórmula de derivación numérica de tipo interpolatorio, para aproximar \\(f^{''}(a)\\), es la derivada segunda del error de interpolación correspondiente, evaluada en \\(a\\).
    - [x] El error de una fórmula de derivación numérica de tipo interpolatorio clásico, para aproximar \\(f'(a)\\), puede obtenerse desarrollando por Taylor el valor de en los diferentes nodos en torno al nodo \\(a \\).
    - [x] El error de una fórmula de derivación numérica de tipo interpolatorio clásico, para aproximar \\(f'(a)\\), puede obtenerse derivando \\(f[x_0,x_1,...,x_n,x] (x-x_0) ... (x-x_n) \\) y evaluando en \\(a\\).


40. Las fórmulas de tipo interpolatorio...
    - [ ] son la de Lagrange y la de Newton.
    - [x] algunas de ellas sirven para aproximar la derivada de una función en un punto.
    - [ ] sólo son exactas para polinomios.
    - [x] algunas de ellas sirven para aproximar la ntegral definida de una función en un intervalo.
    - [ ] carecen de término de error.
    - [x] son exactas en un cierto espacio de funciones.
    - [ ] sirven exclusivamente para aproximar la derivada de una función en un punto o su integral definida en un intervalo. 
    - [ ] son fórmulas de interpolacíón.
    - [x] sirven para aproximar un funcional lineal, como cierta derivada de una función en un punto, o el valor de la integral definida de una función en un intervalo.


42. Si se calcula el polinomio \\(p(x)\\) de grado \\(2\\) que interpola a una función \\(f\\) en \\(a\\), \\(a+h\\) y \\(a+2h\\)...
    - [x] A partir de \\(p(x)\\) se puede obtener una fórmula para aproximar \\(f'(a)\\) y otra para aproximar \\(f^{''}(a)\\) y ambas son exactas para \\(1,x,x^2\\).
    - [ ] A partir de \\(p(x)\\) se puede obtener una fórmula para aproximar \\(f'(a)\\) solamente cuando los datos conocidos de \\(f\\) son tres puntos igualmente espaciados, y siendo \\(a\\) el menor de los tres.
    - [x] \\(p'(a)\\) es una aproximación de \\(f'(a)\\), exacta para \\(1,x,x^2\\).
    - [ ] \\(p'(a)\\) es una aproximación de \\(f'(a)\\), exacta para \\(a,a+h,a+2h\\).
    - [x] A partir de \\(p(x)\\) se puede obtener una fórmula para aproximar \\(f'(1)\\) a partir de \\(f(1),f(0.9),f(0.8)\\).


43. Una función periódica de periodo \\(2\pi\\), se aproxima interpolando con funciones de espacios trigonométricas, es decir, generados por: \\(1,\sin(x),\cos(x),\sin(2x),\cos(2x),\sin(3x),...\\) Se quiere aprovechar esos interpolantes para obtener una fórmula de derivación numérica, efectuando la derivada correspondiente del interpolante. En tal caso:
    - [ ] La fórmula correspondiente a los nodos: \\(0,\frac{\pi}{2},\pi\\), sería exacta para \\(1,x,x^2\\).
    - [ ] Sería una fórmula de tipo interpolatorio clásico.
    - [ ] El error de la fórmula se obtendría a partir de desarrollos en serie de Taylor.
    - [x] Para obtener la fórmula que aproxime \\(f'(\frac{\pi}{2})\\) usando como nodos: \\(0,\frac{\pi}{2},\pi\\), se puede exigir exactitud en \\(1,\sin(x),cos(x)\\) y resolver el sistema correspondiente.
    - [ ] Para obtener la fórmula que aproxime \\(f'(\frac{\pi}{2})\\) usando como nodos: \\(0,\frac{\pi}{2},\pi\\), se puede calcular el interpolante trigonométrico con la fórmula de Newton, derivarlo y evaluarlo en \\(\frac{\pi}{2}\\).
    - [ ] No sería una fórmula de tipo interpolatorio.
 

44. Funcionales lineales.
    - [ ] El funcional lineal \\(L(f)=f'(a)2f^{''}(a)\\) es lineal.
    - [x] Las fórmulas de derivación numérica sirven para aproximar el valor de un funcionale lineal, tales como: \\(L(f)=f'(a)\\), \\(L(f)=f^{''}(a)\\), \\(L(f)=f^{'''}(a)\\), etc.
    - [x] Si \\(a>0\\), el funcional \\(L(f)=f(\sqrt{a})\\) es lineal. 
    - [ ] Para funciones mayores que cero \\(L(f)=\sqrt{(f(a))}\\) es lineal.
    - [ ] El funcional \\(L(f)=f'(a)+2f^{''}(a)+3\\) es lineal.
    - [x] El funcional \\(L(f)=f'(a)+2f^{''}(a)\\) es lineal.
 

45. La fórmula \\(\frac{1}{5}(3\frac{f(a+h)-f(a)}{h}+2\frac{f(a)-f(a-h)}{h})\\) para aproximar \\(f'(a)\\)...
    - [ ] es exacta para: \\(1,x,x^2\\), porque usa tres nodos \\(a-h,a,a+h\\).
    - [x] es una combinación de una fórmula progresiva y otra regresiva para aproximar \\(f'(a)\\).
    - [x] puede tener un error de truncatura tan pequeño como se desee, si \\(f\\) es de clase \\(2\\).
    - [ ] no es de derivación numérica.
    - [ ] es de tipo interpolatorio clásico.
    - [x] no es una de las fórmula habituales usadas en la derivación numérica. 


46. Se desea aproximar \\(f^{'''}(0)\\) mediante una fórmula de tipo interpolatorio que use \\(f(-1),f(0),f(1)\\)
    - [ ] Es necesario calcular los pesos de la fórmula y despues aplicarla.
    - [x] La fórmula será \\(f^{'''}(0)\approx0\\)
    - [ ] El término del error será \\(R(f)=\frac{f^{'''}(0)}{3!}\\)
    - [x] El término del error será \\(R(f)=f^{'''}(0)\\)

47. Orden de convergencia
    - [ ] El método de la secante tiene orden de convergencia cuadrático.
    - [x] El método de la secante tiene orden de convergencia \\(\frac{1+\sqrt{5}}{2}\\)
    - [ ] El método de la secante tiene orden de convergencia \\(1 + \frac{\sqrt{5}}{2}\\)
    - [ ] El método de Newton Raphson tiene orden de convergencia al menos cuadrático cuando la raíz es múltiple.
    - [ ] El método de la secante tiene orden de convergencia lineal.
    - [x] El método de Newton Raphson tiene orden de convergencia al menos cuadrático cuando la raíz es simple.
    - [ ] El método de iteración funcional tiene orden de convergencia el intervalo abierto \\(]-1,1[\\).
    - [x] El método de Newton Raphson puede modificarse para que tenga orden de convergencia al menos cuadrático cuando la raíz es múltiple.

48. Sucesión de Sturm
    - [ ] Si al intentar crear una sucesión de Sturm asociada a un polinomio, definida en el intervalo en el que se encuentran todas las raíces reales, el último resto no nulo no cambia de signo, podemos aprovechar la sucesión para separar todas las raíces reales de dicha ecuación.
    - [ ] Si al intentar construir una sucesión de Sturm asociada a un polinomio se obtiene como último resto no nulo \\(2x-5\\) se puede asegurar que dicho polinomio no tiene ningún cero con multiplicidad mayor que 1 en los reales negativos.
    - [x] Si al intentar construir una sucesión de Sturm asociada a un polinomio se obtiene como último resto no nulo \\(2x-5\\) se puede asegurar que dicho polinomio no tiene ningún cero con multiplicidad mayor que 2.
    - [x] Si al intentar crear una sucesión de Sturm asociada a un polinomio no lo conseguimos es porque el último resto no nulo cambia de signo en \\([a,b]\\) que estemos considerando.
    - [x] Si al intentar crear una sucesión de Sturm asociada a un polinomio, definida en el intervalo en el que se encuentran todas sus raíces reales, el último resto no nulo no es una constante, podemos asegurar que tiene ceros múltiples.
    - [x] El número de ceros de la primera función de la sucesión de Sturm en el intervalo \\([a,b]\\) es igual al número de cambios de signo de dicha sucesión al evaluarla en \\(a\\) menor el número de cambios de signo de dicha sucesión evaluada en \\(b\\). 
    - [ ] Si al intentar construir una sucesión de Sturm asociada a un polinomio, definida en el intervalo en el que se encuentran todas sus raíces reales, se obtiene como último resto no nulo \\(2x-5\\) puede asegurar que la sucesión obtenida permite separar las raíces del polinomio inicial.
    - [ ] El número de ceros de la primera función de la sucesión de Sturm en el intervalo \\([a,b]\\) es igual al número de cambios de signo de dicha sucesión al evaluarla en \\(b\\) menor el número de cambios de signo de dicha sucesión evaluada en \\(a\\). 
    - [ ] Si al intentar crear una sucesión de Sturm asociada a un polinomio, definidad en el intervalo en el que se encuentran todas sus raíces reales, el último resto no nulo no es una constante, es porque dicho polinomio tiene todas sus raíces complejas. 
  