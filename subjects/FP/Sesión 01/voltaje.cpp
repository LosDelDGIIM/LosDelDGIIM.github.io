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
