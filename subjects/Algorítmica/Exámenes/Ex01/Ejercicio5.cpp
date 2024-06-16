/**
 * @file Ejercicio5.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 5 del Examen 1 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex01)
 * 
 * *Enunciado:*
 * Dados $n$ números positivos $w_i; 1 \leq i \leq n$, y un entero más $M$, se trata de encontrar todos
 *         los subconjuntos de números $w_i$ cuya suma valga exactamente $M$.
 * 
 * Por ejemplo, si $n = 4$; $(w_1 = 11; w_2 = 13; w_3 = 24; w_4 = 7)$ y $M = 31$, entonces los subconjuntos buscados son
 *      $(11, 13, 7)$ y $(24, 7)$.
 * 
 * Se pide realizar un algoritmo de exploración en grafos para solucionar el problema.
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 * Para resolver este problema, usaremos un algoritmo de backtracking, que consiste en ir explorando todas las posibles soluciones
 *     y descartando aquellas que no sean válidas.
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * @brief Estructura que representa un nodo del árbol de soluciones
 * 
 * @param sol sol[i] = true si el número w_i está en el subconjunto, false en caso contrario
 * @param suma Suma de los elementos que hemos considerado
 * @param a_asignar a_asignar = i si el siguiente elemento a considerar es w_i. Es decir, si el primer elemento NO_ASIGNADO está en la posición i
 * 
 */
struct Nodo{
    vector<bool> sol;
    int suma;
    int a_asignar;
};


/**
 * @brief Método que devuelve la solución en formato string
 * 
 * @param w  Vector con los números enteros positivos
 * @param M Número entero positivo al que queremos llegar con la suma
 * @param nodo Nodo solución
 */
string sol_toString(const vector<int> &w, int M, const Nodo &sol){
    string separator = " + ";
    string res = "- ";
    for (int i = 0; i < w.size(); i++){
        if (sol.sol[i])
            res += to_string(w[i]) + separator;
    }

    // Eliminamos el último separador
    res = res.substr(0, res.size()-separator.size());

    res += " = " + to_string(M);
    return res;
}


/**
 * @brief Método que resuelve el problema de la suma de subconjuntos mediante backtracking
 * 
 * @param w Vector con los números enteros positivos
 * @param M Número entero positivo al que queremos llegar con la suma
 * @param nodo Nodo actual que estamos considerando
 */
void SumaSubconjuntos(const vector<int> &w, int M, Nodo &nodo){
    // Caso base: hemos considerado todos los elementos, hemos encontrado una solución
    if (nodo.a_asignar == w.size()){        
        if (nodo.suma == M) // Tan solo se imprime si la suma es M
            cout << sol_toString(w, M, nodo) << endl;
    }
    else{
        
        // Consideramos que NO se elige el elemento
        nodo.sol[nodo.a_asignar] = false;
        ++nodo.a_asignar;   // Indicamos que lo hemos asignado
        SumaSubconjuntos(w, M, nodo);
        --nodo.a_asignar;   // Deshacemos la asignación
        
        // -------------------------//

        // Consideramos que SÍ se elige el elemento
        nodo.sol[nodo.a_asignar] = true;
        
        // Tan solo seguiremos exporando el grafo si la suma no supera M, ya que en caso contrario sabemos que no es solución
        if (nodo.suma + w[nodo.a_asignar] <= M){
            nodo.suma += w[nodo.a_asignar];
            ++nodo.a_asignar;   // Indicamos que lo hemos asignado
            SumaSubconjuntos(w, M, nodo);
            --nodo.a_asignar;   // Deshacemos la asignación
            nodo.suma -= w[nodo.a_asignar];
        }
    }
}


int main(){
    vector<int> w = {11,13,24,7};
    int M = 31;

    cout << "Conjunto de numeros: ";
    for (int i = 0; i < w.size(); i++){
        cout << w[i] << " ";
    }

    cout << endl << "Numero al que queremos llegar: " << M << endl << endl;

    cout << "Soluciones:" << endl;

    // Inicializamos el nodo raíz
    Nodo raiz;
    raiz.sol = vector<bool>(w.size(), false);
    raiz.suma = 0;
    raiz.a_asignar = 0;

    SumaSubconjuntos(w, M, raiz);

    return 0;
}