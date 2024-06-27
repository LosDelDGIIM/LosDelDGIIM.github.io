# Algorítmica. Examen V

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:**  Algorítmica.
- **Curso Académico:** 2023-24
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Juan Francisco Huete Guadix (aunque el examen lo pone el departamento).
- **Descripción:** Convocatoria Ordinaria.
- **Fecha:** 17 de junio de 2024.
- **Duración:** 2 horas y 30 minutos.
- **Observaciones:** En todos los problemas se debe emplear alguna de las técnicas de diseño o análisis de algoritmos estudiadas en esta asignatura.

## Ejercicio 1
Calcular el orden de eficiencia en notación $O(\cdot)$ del procedimiento `proc(v,0,n-1)`, donde `v` es un vector de $n$ números naturales enteros, y el procedimiento `proc` es:
```cpp
double proc(const int *v, const int i, const int j) {
    if (i >= j){
        return v[i];
    }else{
        int m = (i+j)/2;
        double rm = proc(v,i,m);
        int md = (m+j)/2;
        double rmd1 = proc(v, m+1, md);
        double rmd2 = proc(v, md+1, j);
        double s = 0;
        for(int k=i; k <= j; k++) s += v[k];
        return s + rm + rmd1 + rmd2;
    }
}
```

<details>
  <summary>Solución</summary>
  <p>El examen todavía no se ha resuelto, si alguien resuelve el examen nos sería de utilidad para subir la solución. Recordamos que la solución era $O(n\log n)$.</p>
</details>

## Ejercicio 2
Se tiene un buque mercante cuya capacidad de carga es de $N$ toneladas y un conjunto de $n$ contenedores cuyos pesos respectivos son $c_1, \ldots, c_n$ (expresados también en toneladas). 

Teniendo en cuenta que la capacidad del buque es posiblemente menor que la suma total de los pesos de los contenedores, diseñad un algoritmo de exploración de grafos que determine qué contenedores hay que cargar en el barco con el objetivo de maximizar el número de toneladas cargadas.

## Ejercicio 3
Una empresa quiere comprar un conjunto de parcelas en primera línea de playa para edificar una urbanización. Para ello, tras consultar al ayuntamiento, dispone de un array $P$ de tamaño $n$ representando la línea de parcelas. Para una parcela dada, $i$, $P[i]$ tendrá un valor 0 si no es posible construir en ella y 1 cuando sí es posible construir. 

Utilizad la técnica Divide y Vencerás para determinar el mayor número de parcelas consecutivas sobre las que le está permitido realizar el proyecto.

## Ejercicio 4
En un almacén tenemos guardados sacos de $n$ tipos distintos de fertilizantes. Tenemos muchos sacos (cantidad ilimitada a efectos prácticos) de cada tipo de fertilizante. Cada saco del fertilizante $i$ pesa $p[i]$ kilogramos (un número entero) y su venta supone un beneficio de $b[i]$ euros (no se vende a granel, sino sacos enteros). Disponemos de un camión cuya capacidad máxima de carga es de $M$ kilogramos, y queremos decidir cómo cargar el camión para maximizar los beneficios tras vender su cargamento. 

Diseñad un algoritmo de programación dinámica para resolver el problema. 

Aplicadlo para el caso en que hay 3 tipos de fertilizantes, con pesos $p = (3, 4, 6)$, beneficios $b = (7, 8, 11)$ y capacidad de carga $M = 10$.

## Ejercicio 5
Un turista neoyorkino quiere recorrer $n$ países europeos $\{p_1, \ldots, p_n\}$ en un orden prefijado (hay que visitarlos en ese orden) y visitar en cada país $p_i$ una (y sólo una) de entre $m_i$ posibles ciudades prefijadas de ese país. El criterio para determinar su viaje es que el coste total del viaje sea el menor posible (incluyendo el coste de llegar a la ciudad del primer país desde Nueva York y el de volver a Nueva York desde la ciudad del último país). El coste total del viaje es la suma de los costes de viajar de una ciudad a otra. 

Formalizad el problema y construid un algoritmo que lo resuelva de la forma más eficiente posible, encontrando la solución óptima.
