/**
 * @file Ejercicio4.cpp
 * @author Adam Bourbahh Romero
 * @brief Ejercicio 4 del Examen 5 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algoritmica/Examenes/Ex05)
 *
 * *Enunciado:*
 *
 * En un almacen tenemos guardados sacos de n tipos distintos de fertilizantes. Tenemos muchos sacos (cantidad ilimitada a efectos practicos)
 * de cada tipo de fertilizante. Cada saco del fertilizante i pesa p[i] kilogramos (un numero entero) y su venta supone un beneficio de
 * b[i] euros (no se vende a granel, sino sacos enteros). Disponemos de un camion cuya capacidad maxima de carga es de M kilogramos, y
 * queremos decidir como cargar el camion para maximizar los beneficios tras vender su cargamento. Disenad un algoritmo de programacion dinamica
 * para resolver el problema.
 *
 * Aplicadlo para el caso en que hay 3 tipos de fertilizantes, con pesos p = (3, 4, 6), beneficios b = (7, 8, 11) y capacidad de carga M = 10.
 *
 * _______________________________________________________________________________________________________________________________________________________________
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Personalmente recomiendo entender el 0/1 knapsack antes de afrontar este
// problema, y si sigues sin entender el tipo unbounded:
//
// https://www.youtube.com/watch?v=jlCJqgSgXI4&t=26s
// Se usa programacion dinamica con:
//
// dp[w] = max_{i: p_i <= w} { dp[w - p_i] + b_i }, dp[0] = 0.
//
// Para el caso:
//
// p = (3,4,6), b = (7,8,11), M = 10.

int infkanpsack(vector<int>& pesos, vector<int>& beneficios, int M) {
    vector<int> dp(M + 1, 0);
    int n = (int)pesos.size();

    for (int w = 1; w <= M; w++) {
        for (int i = 0; i < n; i++) {
            if (pesos[i] <= w)
                dp[w] = max(dp[w], dp[w - pesos[i]] + beneficios[i]);
        }
    }
    return dp[M];
}

int main() {
    vector<int> pesos = {3, 4, 6};
    vector<int> beneficios = {7, 8, 11};
    int M = 10;

    int resultado = infkanpsack(pesos, beneficios, M);
    cout << "El maximo beneficio posible con capacidad " << M << " es: " << resultado
         << endl;

    return 0;
}