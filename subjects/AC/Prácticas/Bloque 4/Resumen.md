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
  
Los compiladores introducen además varias opciones de compilación con optimización
