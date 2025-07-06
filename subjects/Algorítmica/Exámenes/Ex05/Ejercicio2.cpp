/**
 * @file Ejercicio2.cpp
 * @author Adam Bourbahh Romero
 * @brief Ejercicio 2 del Examen 5 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algoritmica/Examenes/Ex05)
 *
 * *Enunciado:*
 * Se tiene un buque mercante cuya capacidad de carga es de $N$ toneladas y un conjunto de $n$ contenedores cuyos pesos respectivos son
 * $c_1, \ldots, c_n$ (expresados tambien en toneladas). Teniendo en cuenta que la capacidad del buque es posiblemente menor que
 * la suma total de los pesos de los contenedores, disenad un algoritmo de exploracion de grafos que determine que contenedores hay
 * que cargar en el barco con el objetivo de maximizar el numero de toneladas cargadas.
 *
 * _______________________________________________________________________________________________________________________________________________________________
 *
 *
 *
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Anotacion: Quizas se puede hacer con memoizacion pero lo desconozco.
int maxCarga(const vector<int>& c, int N, int i, int pesoActual) {
    // Caso base: si ya hemos considerado todos los contenedores, devolvemos.
    if (i == c.size()) return pesoActual;

    // no cargar el contenedor i
    int sinCargar = maxCarga(c, N, i + 1, pesoActual);

    // cargar el contenedor i, solo si no excede la capacidad
    int conCargar = 0;
    if (pesoActual + c[i] <= N) {
        conCargar = maxCarga(c, N, i + 1, pesoActual + c[i]);
    }

    // Elegimos la opcion que nos da el mayor peso acumulado sin superar la capacidad
    return max(sinCargar, conCargar);
}

int main() {
    // Ejemplo de pesos de contenedores
    vector<int> contenedores = {7, 12, 34, 51, 81};

    // Capacidad maxima del buque
    int capacidad = 1250;

    // Calculamos la maxima carga posible
    int resultado = maxCarga(contenedores, capacidad, 0, 0);

    cout << "La maxima carga posible sin superar la capacidad es: " << resultado << endl;

    return 0;
}