/**
 * @file Ejercicio2.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 2 del Examen 2 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex02)
 * 
 * *Enunciado:*
 * Dado un conjunto de $n$ números enteros positivos $C = \{c_1, c_2, \ldots, c_n\}$ y dado un entero positivo $N$,
 *      se quiere encontrar un subconjunto de $C = \{y_1, \ldots, y_m\}$ que maximice $\prod_{i=1}^{m} y_i$ (se maximice el producto de los números del subconjunto),
 *      sujeto a la restricción $\prod_{i=1}^{m} y_i \leq N$.
 * 
 * Nota: $m$ NO es un parámetro de entrada.
 * 
 * Diseñad un algoritmo de vuelta atrás (backtraking) para resolver este problema.
 * 
 * Por ejemplo, para $n = 4$, $N = 37$ y $C = \{4, 4, 12, 3\}$, la solución es emplear el subconjunto $\{12, 3\}$ con un valor de producto igual a $36$.
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Nodo que representa una solución parcial del problema
 * 
 * @param sol sol[i] = true si el número c_i está en el subconjunto, false en caso contrario
 * @param producto Producto de los elementos que hemos considerado
 * @param a_asignar a_asignar = i si el siguiente elemento a considerar es c_i. Es decir, si el primer elemento NO_ASIGNADO está en la posición i
 * 
 */
struct Nodo{
    vector<bool> sol;
    int producto;
    int a_asignar;
};


/**
 * @brief Método que devuelve la solución en formato string
 * 
 * @param c  Vector con los números enteros positivos
 * @param nodo Nodo solución
 */
string sol_toString(const vector<int> &c, const Nodo &sol){
    string separator = " * ";
    string res = "- ";
    for (int i = 0; i < c.size(); i++){
        if (sol.sol[i])
            res += to_string(c[i]) + separator;
    }

    // Eliminamos el último separador
    res = res.substr(0, res.size()-separator.size());

    res += " = " + to_string(sol.producto);
    return res;
}



void ProductoSubconjuntos(const vector<int> &c, int N, Nodo &nodo, Nodo &sol){
    // Si hemos considerado todos los elementos, ya hemos llegado a una solución
    if (nodo.a_asignar == c.size()){

        // Si la solución actual es mejor que la mejor solución encontrada hasta ahora, actualizamos la mejor solución
        if (nodo.producto > sol.producto){
            sol = nodo;
        }
    }
    else{
        
        // Consideramos que NO elegimos el elemento actual
        nodo.sol[nodo.a_asignar] = false;
        nodo.a_asignar++;
        ProductoSubconjuntos(c, N, nodo, sol);
        nodo.a_asignar--;

        // ---------------------------- //

        // Consideramos que SÍ elegimos el elemento actual
        nodo.sol[nodo.a_asignar] = true;
        
        // Si el producto actual es menor que N, seguimos explorando
        if (nodo.producto * c[nodo.a_asignar] <= N){
            nodo.producto *= c[nodo.a_asignar];
            nodo.a_asignar++;
            ProductoSubconjuntos(c, N, nodo, sol);
            nodo.a_asignar--;
            nodo.producto /= c[nodo.a_asignar];
        }

    }
}


int main(){
    int N = 37;
    vector<int> c = {4, 4, 12, 3};

    // Inicialización de la solución
    Nodo nodo;
    nodo.sol = vector<bool>(c.size(), false);
    nodo.producto = 1;
    nodo.a_asignar = 0;
    Nodo sol;
    sol.producto = *max_element(c.begin(), c.end());


    // Resolución del problema
    ProductoSubconjuntos(c, N, nodo, sol);

    // Impresión de la solución
    cout << sol_toString(c, sol) << endl;

    return 0;
}