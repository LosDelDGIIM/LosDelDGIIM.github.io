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
