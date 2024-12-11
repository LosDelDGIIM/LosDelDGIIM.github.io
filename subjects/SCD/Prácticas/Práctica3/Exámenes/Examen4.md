# SCD. Examen de la Práctica III.

-**Autor**: José Juan Urrutia Milán.
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2024/25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas + ADE.
- **Grupo:** 2.
- **Descripción:** Examen de la práctica 3 de SCD.
- **Profesor**: José Miguel Mantas Ruíz.
- **Fecha:** 11 de diciembre de 2024.
- **Duración:** 50 minutos.

***

# Ejercicio

La plantilla se encuentra en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica3/Exámenes/Examen4_Plantilla.cpp).
  
Puede encontrar la solución al problema en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica3/Exámenes/Examen4.cpp).
***

El archivo `Examen4_Plantilla.cpp` proporcionado contiene una solución básica al problema de los filósofos con camarero. En esta solución, el camarero se encarga de controlar el acceso a la mesa, permitiendo que se sienten a la mesa un máximo de 4 filósofos. Hay 5 filósofos.

Modificar este archivo como sigue:
- El filósofo 4, cuyo rango es $8$, tendrá un comportamiento algo diferente del resto. EL filósofo 4 no pide ni suelta ningun tenedor ya que come con las manos. No obstante, este filosofo sí debe pedir permiso para sentarse y levantarse al camarero.
- Como el filósofo 4 no puede comer si no se siente muy acompañado, el camarero solo permite que se siente cuando hay 4 filosofos sentados en ella.
- El camarero además no permite levantarse a ninguno de ellos mientras está comiendo el filósofo 4, para que se sienta acompañado.
- Como ahora ya no hay interbloqueo, podria haber 5 sentados en la mesa. Han de usarse unas etiquetas especiales para el filósofo 4.

El camarero deberá, en un bucle infinito:
1. Paso 1  (Usar `Iprobe`)
    - `IF` (hay menos de 4 sentados)
    
        Sondeo en un bucle de las peticiones de sentarse o levantarse de cualquier filósofo distinto al 4, hasta detectar una.

        Recibe el primer mensaje detectado.
    
    - `ELSE IF` (hay 4)

        Sondeo en un bucle de las peticiones de levantarse de los filósofos distintos al 4 y de sentarse del 4, hasta detectar una.

        Recibe el primer mensaje detectado.

    - `ELSE`

        Recibe la petición de levantarse del filósofo 4.

2. Paso 2

    Actualiza el numero de sentados (en función de la etiqueta recibida).
