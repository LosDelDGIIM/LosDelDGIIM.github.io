# Fundamentos de Programación. Sesión I de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Resolución de problemas de la Sesión I de prácticas.


## 1. Voltaje.cpp
Crear un programar que pida un valor de intensidad y resistencia e imprima el voltaje correspondiente, según la _Ley de Ohm_:
$voltaje = intensidad * resistencia$
```cpp
#include <iostream>

using namespace std;

int main(){

    // Declaración de variables
    double intensidad;
    double resistencia;
    double voltaje;

    // Entrada 
    cout << "Introduzca una intensidad (en amperios): ";
    cin >> intensidad;

    cout << "Introduzca una resistencia (en ohmios): ";
    cin >> resistencia;

    // Cálculos
    voltaje = intensidad * resistencia;

    // Salida
    cout << endl;
    cout << "El voltaje es de " << voltaje << " voltios." << endl;

    return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2001/voltaje.cpp)

## 2. Circunferencia.cpp
Cread un programa que nos pida la longitud del radio, calcule el área del círculo y la longitud de la circunferencia correspondientes, y nos muestre los resultados en pantalla. Recordad que:  
  
$perimetro = 2πr$  
$area = πr²$  
  
  
Nota: usad el literal $3.1416$.
```cpp
#include <iostream>

using namespace std;

int main(){

    // Declaración de variables
    const double PI = 3.1415;
    double radio;
    double area;
    double perimetro;

    // Entrada 
    cout << "Introduzca un radio (en metros): ";
    cin >> radio;

    // Cálculos
    perimetro = 2 * PI * radio;
    area = PI * radio * radio;

    // Salida
    cout << endl;
    cout << "El perimetro es de " << perimetro << " metros." << endl;
    cout << "El área es de " << area << " metros cuadrados." << endl;

    return 0;
}
```
[Ir a la solución](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/FP/Sesi%C3%B3n%2001/circunferencia.cpp)

Debido a que estas sesiones de prácticas son iniciales, la sesión 2 consistió en ver soluciones a ejercicios, por
lo que no hubo problemas planteados. Saltamos directamente a la sesión de prácticas número 3.
