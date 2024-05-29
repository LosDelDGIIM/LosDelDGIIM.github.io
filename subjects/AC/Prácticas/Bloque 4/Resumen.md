# Arquitectura de Computadores. Sesión III de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Arquitectura de Computadores.  
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen de la Sesión IV de Prácticas.

# Introducción
En esta sesión aprenderemos a optimizar los códigos de nuestro programas, aprovechando las arquitecturas de los computadores en los que ejecutaremos los códigos. Como normas generales:
- Se recomienda no optimizar los códigos al final, lo que dificulta esta labor, sino ir optimizando conforme se programa.
- Es un error no programar sin tener en cuenta la arquitectura, ya que genera códigos muy ineficientes cuyos tiempos pueden reducirse fácilmente pensando un poco en la arquitectura.
- No se debe reducir el tiempo de ejecución eliminando funcionalidades del programa.
- A la hora de optimizar, debemos fijarnos en la parte del código que más tiempo suponga en la ejecución del programa, eliminando códigos de botella.
- No es necesario bajar a código ensamblaor para optimizar, aunque a veces es la única opción.
  
Hay optimizaciones con las que veremos mejoras en todos los núcleos de procesamiento actuales, por tener características comunes a tener en cuenta (por ejemplo, todas las CPUs actuales tienen varias ALUs).  
Además, hay características propias de implementaciones concretas que si se tienen en cuenta podemos reducir tiempos de ejecución.  
  
### Conocer gcc
Los compiladores introducen además varias opciones de compilación con optimización, que realizan las optimizaciones de forma automática, teniendo en cuenta partes del hardware que suelen ser comunes a todos los procesadores actuales.  
Por ejemplo, `gcc` cuenta con las opciones de optimización `-O0` (no optimiza nada), `-O1`, `-O2` y `-O3` para tiempo (se encuentran en orden creciente de número de actualizaciones), además de `-Os` para espacio, para que el programa a ejecutar ocupe el menor espacio posible.  
  
La opción de compilación con optimización que recomendamos usar es `-O2`, que suele dar los mejores tiempos de ejecución.  
`-O3` cuenta con varias funcionalidades que todavía no están bien depuradas (las cuales pueden provocar errores a la hora de compilar los programas). Cuando una opción está depurada y lleva tiempo en uso, suele pasarse a `-O2`.  
Puede suceder que el tiempo con `-O3` aumente en relación a `-O2`, ya que aunque suele intentar realizar mejores optimizaciones, como ya se ha dicho no está del todo depurado.  
  
Además, la opción `-O3` genera instrucciones vectoriales (las reconoceremos por acabar con el sufijo `p`, o `pd` en el caso de instrucciones vectoriales para `double`). Las instrucciones con el sufijo `sd` son instrucciones escalares.  
Con la opción `-O0` se optimiza poco, por lo que obtendremos códigos largos con grandes tiempos de ejecución.

# Optimizaciones recomendables
A continuación, enumeramos una serie de estrategias a realizar con la finalidad de generar códigos con menores tiempos de ejecución, aprovechando las características de las arquitecturas actuales. Posiblemente se conozcan ya otras estrategias que también consigan este propósito, aquí simplemente describimos los conocimientos que nos aporta esta práctica. Las clasificamos entres categorías:

## Optimización de la ejecución
### Reducción de fuerza
Muchas veces usamos operaciones sobre nuestros datos de forma natural pero que podrían realizarse de formas más rápidas (empleando menos bucles) con otro tipo de operaciones que nos proporcionen el mismo resultado.  
  
Vemos algunos ejemplos en los que se aplica esta técnica:

#### Sustituir divisiones por multiplicaciones
Si por ejemplo en un bucle tenemos el siguiente código:
```c
for(int i = 0; i < n; i++){
    a[i] = i / n;
}
```
En vez de realizar `n` veces una división, podemos realizar primero la división y luego hacer `n` multiplicaciones, con lo que obtendremos unos mejores tiempos:
```c
int a = 1 / n;
for(int i = 0; i < n; i++){
    a[i] = i * a;
}
```

#### Sustituir multiplicaciones por shifts
Si queremos realizar multiplicaciones, siempre será más eficiente realizar operaciones de shift, que ocupan menos ciclos. Por ejemplo, podemos sustituir:
```c
a = b * 10;
```
Podemos aplicar que `b * 10 = b * (2 + 8) = b * 2 + b * 8` y aprovechar las multiplicaciones por potencias de 2 para realizar shifts en vez de multiplicaciones.
