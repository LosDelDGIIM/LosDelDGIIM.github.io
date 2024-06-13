/**
 * @file Mochila_01_BT.cpp
 * @author Arturo Olivares Martos
 * @brief  Resolución del problema de la mochila 0-1 mediante backtracking
 * 
 * Dado un conjunto de n elementos, cada uno con un peso w_i y un valor v_i, se desea determinar cuál es la combinación de elementos que maximiza
 * el valor total sin superar un peso máximo P.
 * 
 * W[i] denota el peso del elemento i
 * V[i] denota el valor del elemento i
 * P denota el peso máximo que puede soportar la mochila
 * 
 * T[i]=1 si el elemento i está en la mochila, T[i]=0 en caso contrario
 *  
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INVALIDO = -1;
const int INCLUIDO = 1;
const int NO_INCLUIDO = 0;


struct Nodo{
    vector<int> T;
    int valor_acumulado;
    int peso_acumulado;
};



/**
 * @brief Función recursiva que resuelve el problema de la mochila 0-1 mediante backtracking
 * 
 * @param W  Vector de pesos de los elementos
 * @param V  Vector de valores de los elementos
 * @param P  Peso máximo que puede soportar la mochila
 * @param e_nodo  Nodo actual, en expansión
 * @param sol  Nodo que contiene la solución óptima por el momento
 */
void Mochila_01(const vector<int>& W, const vector<int>& V, int P, Nodo& e_nodo, Nodo& sol){
    
    // Obtenemos el elemento que estamos considerando si meter o no en la mochila
    int elemento = find(e_nodo.T.begin(), e_nodo.T.end(), INVALIDO) - e_nodo.T.begin();

    // Si hemos considerado todos los elementos, hemos terminado
    if(elemento == V.size()){
        if (e_nodo.valor_acumulado > sol.valor_acumulado)
            sol = e_nodo;
        return;
    }

    // Consideramos no incluirlo
    e_nodo.T[elemento] = NO_INCLUIDO;
    Mochila_01(W, V, P, e_nodo, sol);

    // Consideramos incluirlo
    if(e_nodo.peso_acumulado + W[elemento] <= P){
        e_nodo.T[elemento] = INCLUIDO;

        e_nodo.valor_acumulado += V[elemento];
        e_nodo.peso_acumulado += W[elemento];
        Mochila_01(W, V, P, e_nodo, sol);
        e_nodo.valor_acumulado -= V[elemento];
        e_nodo.peso_acumulado -= W[elemento];
    }

    e_nodo.T[elemento] = INVALIDO;
}



int main(){
    
        vector<int> W = {3,2,4,5,6,3,5};
        vector<int> V = {30,20,36,40,48,6,2};
        int P = 11;
    
        Nodo e_nodo;
        e_nodo.T = vector<int>(W.size(), INVALIDO);
        e_nodo.valor_acumulado = 0;
        e_nodo.peso_acumulado = 0;
    
        Nodo sol = e_nodo;
    
        Mochila_01(W, V, P, e_nodo, sol);
    
        cout << "Valor maximo: " << sol.valor_acumulado << endl;
        cout << "Elementos incluidos: ";
        for(int i = 0; i < sol.T.size(); ++i){
            if(sol.T[i] == INCLUIDO)
                cout << i << " ";
        }
        cout << endl;
    
        return 0;
}