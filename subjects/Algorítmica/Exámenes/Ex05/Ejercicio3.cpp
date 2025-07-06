/**
 * @file Ejercicio3.cpp
 * @author Adam Bourbahh Romero
 * @brief Ejercicio 3 del Examen 5 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algoritmica/Examenes/Ex05)
 *
 * *Enunciado:*
 *
 * Una empresa quiere comprar un conjunto de parcelas en primera linea de playa para edificar una urbanizacion. Para ello, tras consultar
 * al ayuntamiento, dispone de un array $P$ de tamano $n$ representando la linea de parcelas. Para una parcela dada, $i$, $P[i]$ tendra
 * un valor 0 si no es posible construir en ella y 1 cuando si es posible construir. Utilizad la tecnica Divide y Venceras para determinar
 * el mayor numero de parcelas consecutivas sobre las que le esta permitido realizar el proyecto.
 * ______________________________________________________________________________________________________________________________________________________________
 *
 *
 */

#include <iostream>
#include <vector>
#include <algorithm> // para std::max y std::max initializer list

using namespace std;

// El planteamiento del problema basicamente es tratar la parcela como dos, una a
// la izquierda y otra a la derecha. Por ejemplo:
// P=[1,1,0,0,1,1,1,0,1]
// Izquierda:
// [1,1,0,0,1]
// Derecha:
// [1,1,0,1]
// Nuestro algoritmo escogeria m=4, separando el vector original en los anteriores,
// tras ello se calcularia de forma recursiva el maximo izquierdo como el maximo derecho.
// Ademas, hay que tener especial cuidado con si existe un segmento que atrevesase estos dos segmentos (como es el caso del ejemplo),
//por ello se hace una nueva funcion que recorre los dos lados y devuelva el maximo segmento cruzado (de ahi el nombre de la funcion, original, lo se).
//Por ultimo, devolvemos el maximo de los segmentos.

int maxSegmentoCruzado(vector<int>& P, int i, int m, int j) {
    int countIzq = 0;
    for (int x = m; x >= i && P[x] == 1; x--) countIzq++;
    int countDer = 0;
    for (int x = m + 1; x <= j && P[x] == 1; x++) countDer++;
    return countIzq + countDer;
}

int maxSegmento(const vector<int>& P, int i, int j) {
    if (i == j) return P[i];
    int m = (i + j) / 2;
    int maxIzq = maxSegmento(P, i, m);
    int maxDer = maxSegmento(P, m + 1, j);
    // hacemos cast const_cast porque solo leemos valores (puedes eliminar si haces P no const)
    int maxCruz = maxSegmentoCruzado(const_cast<vector<int>&>(P), i, m, j);
    return max({maxIzq, maxDer, maxCruz});
}

int main() {
    vector<int> P = {1, 1, 1, 0, 0, 1, 1, 0, 1};

    int resultado = maxSegmento(P, 0, P.size() - 1);

    cout << "El maximo segmento de 1s consecutivos es: " << resultado << endl;

    return 0;
}