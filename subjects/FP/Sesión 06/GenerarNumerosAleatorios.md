# Fundamentos de Programación. Sesión VI de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Tutorial de cómo generar números aleatorios dentro de un rango en C++.

Fijadas dos constantes ```MIN``` y ```MAX``` en nuestro programa, necesitaremos incluir las librerías ```ctime``` y ```cstdlib```. Con estas, tendremos acceso a las funciones ```srand```, ```time``` y ```rand```. Usaremos las dos primeras para inicializar el generador de números aleatorios con el reloj del sistema (la hora atual). La segunda nos proporcionará un número aleatorio cada vez que la ejecutemos, el cual deberemos ajustar para que se encuentre en el intervalo apropiado. Cada vez que ejecutemos ```rand```, se nos proporcionará un nuevo número aleatorio.  
  
El siguiente código muestra cómo llevar esto a cabo:  
```cpp
#include <ctime>
#include <cstdlib>

// ...

const int MIN = 1;
const int MAX = 100;
const NUM_VALORES = MAX - MIN + 1; // Número de valores posibles

time_t t;
srand(time(&t));

int aleatorio;
aleatorio = (rand() % NUM_VALORES) + MIN;

// ...

aleatorio = (rand() % NUM_VALORES) + MIN;

```
