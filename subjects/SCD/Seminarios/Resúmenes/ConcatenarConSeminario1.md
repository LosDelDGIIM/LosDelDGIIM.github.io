# 3. Sincronización básica

Aprenderemos ahora el uso de dos clases de `C++11` que nos permiten garantizar la exclusión mutua en regiones críticas (vea en los apuntes de teoría qué es la exclusión mutua).  
  
Disponemos de dos clases que nos permiten esta funcionalidad:

## Tipos atómicos
(Incluir la librería `<atomic>`)  
Se trata de un tipo de dato genérico, `atomic<T>` que nos permite crear variables que tienen protegidas operaciones pequeñas, para que estas se hagan de forma atómica.  
  
Si `expr` es un literal simple (no una variable) y `k` es una variable de tipo `atomic<T>>`, podremos hacer las operaciones:  
`k = expr`, `k++`, `k--`, `k += expr` y `k -= expr`  
de forma atómica.  
  
Este tipo de dato aprovecha instrucciones máquina que permiten dichos funcionamientos.

## Objetos mutex
