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
El enunciado de cada problema se encuentra en el mismo `cpp`, en forma de comentario.


En la presente carpeta no se incluye el ejercicio 1, por no tratarse de un programa a implementar. Su enunciado se muestra a
continuación:

1. Calcular el orden de eficiencia en notación $O(\cdot)$ del procedimiento `proc(v,0,n-1)`, donde `v` es un vector de $n$ números naturales enteros, y el procedimiento `proc` es:
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
