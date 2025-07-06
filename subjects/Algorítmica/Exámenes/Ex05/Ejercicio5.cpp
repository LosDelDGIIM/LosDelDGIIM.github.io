/**
 * @file Ejercicio5.cpp
 * @author Adam Bourbahh Romero
 * @brief Ejercicio 5 del Examen 5 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algoritmica/Examenes/Ex05)
 *
 * *Enunciado:*
 *
 * Un turista neoyorkino quiere recorrer $n$ paises europeos $\{p_1, \ldots, p_n\}$ en un orden prefijado (hay que visitarlos en ese orden) y
 * visitar en cada pais $p_i$ una (y solo una) de entre $m_i$ posibles ciudades prefijadas de ese pais. El criterio para determinar su viaje
 * es que el coste total del viaje sea el menor posible (incluyendo el coste de llegar a la ciudad del primer pais desde Nueva York y el de
 * volver a Nueva York desde la ciudad del ultimo pais). El coste total del viaje es la suma de los costes de viajar de una ciudad a otra.
 * Formalizad el problema y construid un algoritmo que lo resuelva de la forma mas eficiente posible, encontrando la solucion optima.
 *
 * _______________________________________________________________________________________________________________________________________________________________
 *
 * La solucion esta por subirse a la pagina.
 * Si alguien resuelve el ejercicio nos vendria de utilidad para publicarlo.
 *
 * El problema se resuelve mediante el algoritmo de Viterbi, el cual resuelve el problema de encontrar el camino minimo para ir desde una primera etapa
 * hasta la ultima pasando por una instancia de cada etapa. Nuestras etapas seran los distintos paises a visitar, siendo los costes de las aristas del
 * grafo que representa las etapas los costes de viajar entre cada par de ciudades.
 *
 * Deberemos modificar dicho grafo, ya que en la primera etapa, el coste de ir de la ciudad $m$ (de la primera etapa) a la ciudad $n$ (de la segunda)
 * etapa sera igual al coste de ir de $m$ a $n$ mas el coste de ir desde Nueva York hasta la ciudad $m$. Repetiremos dicho procedimiento para cada par
 * de ciudades conformado por una ciudad del primer pais y una ciudad del segundo pais.
 * De forma analoga, tambien debemos modificar las aristas que unen la penultima etapa con la ultima: el coste de ir de la ciudad $m$ (de la penultima
 * etapa) a la ciudad $n$ (de la ultima etapa), sera el coste de ir de la ciudad $m$ a la $n$ mas el coste de ir desde $n$ hasta Nueva York.
 *
 * El problema se resuelve, por tanto, buscando una buena representacion del grafo, realizar las modificaciones anteriormente comentadas y, por ultimo,
 * aplicar a dicho grafo el algoritmo de Viterbi. Tras esto, habremos encontrado el camino que resuelve nuestro problema.
 *
 */
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// Podemos ver facilmente que:
// dp[i][k] = min(dp[i][k], dp[i-1][l] + cost[i-1][l][k]);
// con
// dp[0][k] = coste(NY, c_{0,k}),
// y la solucion es
// min(resultado, dp[n-1][k] + costCityToNY[n-1][k]);

int n; // numero de paises
vector<int> m; // cantidad de ciudades por pais

// cost[i][j][k]: coste de ir de ciudad j en pais i a ciudad k en pais i+1
// costNYtoCity[i][k]: coste de NY a ciudad k en pais i
// costCityToNY[i][k]: coste de ciudad k en pais i a NY

vector<vector<vector<int>>> cost;
vector<vector<int>> costNYtoCity;
vector<vector<int>> costCityToNY;

vector<vector<int>> dp; // dp[i][k]

void calcularCostoMinimo() {
    dp.assign(n, vector<int>());
    // Esto es al gusto del consumidor; equivale a:
    // vector<vector<int>> dp(n, vector<int>()).

    for (int i = 0; i < n; i++)
        dp[i].assign(m[i], INT_MAX);

    for (int k = 0; k < m[0]; k++)
        dp[0][k] = costNYtoCity[0][k];

    for (int i = 1; i < n; i++) {
        for (int k = 0; k < m[i]; k++) {
            for (int l = 0; l < m[i-1]; l++) {
                if (dp[i-1][l] != INT_MAX) {
                    dp[i][k] = min(dp[i][k], dp[i-1][l] + cost[i-1][l][k]);
                }
            }
        }
    }

    int resultado = INT_MAX;
    for (int k = 0; k < m[n-1]; k++) {
        resultado = min(resultado, dp[n-1][k] + costCityToNY[n-1][k]);
    }

    cout << "Coste minimo total: " << resultado << endl;
}

int main() {
    // Ejemplo simple para probar (No he tenido tiempo para pensar en un caso de prueba).
    // Para probar el codigo, necesitarias inicializar las variables globales:
    // n, m, cost, costNYtoCity, costCityToNY.
}