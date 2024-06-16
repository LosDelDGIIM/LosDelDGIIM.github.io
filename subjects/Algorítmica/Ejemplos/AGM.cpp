/**
 * @file Kruskal.cpp
 * @brief Resolución del problema del árbol de expansión mínima
 * 
 * Dado un grafo conexo y no dirigido, con arcos ponderados con pesos no negativos, el problema consiste en hallar un árbol de expansión mínima
 * (subgrafo que contiene todos los vértices del grafo inicial y es un árbol) cuya suma de pesos de los arcos es mínima.
 * 
 * 
 * KRUSKAL:
 * - Conjunto de candidatos: Todos los arcos del grafo
 * - Conjunto de seleccionados: Arcos seleccionados (hayan sido añadidos al árbol de expansión mínima o no)
 * - Función solución: Conjunto de candidatos vacío
 * - Función de factibilidad: No formar ciclos al añadir un arco al conjunto de seleccionados (al seleccionar tosos los arcos, el grafo resultante es un árbol)
 * - Función de selección: Arco de menor peso
 * - Función objetivo: Suma de los pesos de los arcos seleccionados
 * 
 * PRIM:
 * - Conjunto de candidatos: Todos los vértices del grafo
 * - Conjunto de seleccionados: Vértices seleccionados
 * - Función solución: Conjunto de candidatos vacío
 * - Función de factibilidad: No formar ciclos al añadir un vértice al conjunto de seleccionados (al seleccionar tosos los vértices, el grafo resultante es un árbol)
 * - Función de selección: Vértice más cercano a los seleccionados
 * - Función objetivo: Suma de los pesos de los arcos seleccionados
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "./UnionFind.h"
#include <climits>

using namespace std;

#define PRIM
// #define KRUSKAL


typedef vector<vector<int>> Grafo;
const int NO_CONECTADO = -1;

// Estructura para representar un arco
struct Arco{
    int u, v;       // Vértices que une el arco
    int peso;       // Peso del arco

    // Un arco es menor que otro si su peso es menor
    bool operator<(const Arco &a) const{
        return peso < a.peso;
    }
};




/**
 * @brief Lee un grafo no dirigido a partir de su matriz de adyacencia
 * 
 * @param G  Matriz de adyacencia del grafo
 * @return vector<Arco>  Vector con los arcos del grafo
 */
vector<Arco> LeerGrafoNoDirigido(const Grafo &G){
    vector<Arco> arcos;

    for (int i = 0; i < G.size(); i++){
        // Como es no dirigido, solo recorremos la mitad de la matriz
        for (int j = i+1; j < G[i].size(); j++){
            if (G[i][j] != NO_CONECTADO){
                arcos.push_back({i, j, G[i][j]});
            }
        }
    }

    return arcos;
}



/**
 * @brief Dado un Grafo no dirigido, modifica la matriz de adyacencia para que solo contenga los arcos dados
 * 
 * @param G  Grafo no dirigido a modificar
 * @param arcos  Vector con los arcos a añadir al grafo
 * @return Grafo  Grafo no dirigido modificado
 */
Grafo ModificarGrafoNoDirigido(const Grafo &G, const vector<Arco> &arcos){
    Grafo G_arbol(G.size(), vector<int>(G.size(), NO_CONECTADO));

    for (const Arco &arco : arcos){
        G_arbol[arco.u][arco.v] = arco.peso;
        G_arbol[arco.v][arco.u] = arco.peso;
    }

    return G_arbol;
}


/**
 * @brief Calcula la suma de los pesos de los arcos de un árbol
 * 
 * @param arbol_exp_minima  Vector con los arcos del árbol
 * @return double  Suma de los pesos de los arcos
 */
double sumaPesos(const vector<Arco> &arbol_exp_minima){
    double suma = 0;
    for (const Arco &arco : arbol_exp_minima){
        suma += arco.peso;
    }
    return suma;
}


/**
 * @brief Resuelve el problema del árbol de expansión mínima mediante el algoritmo de Kruskal
 * 
 * @param G  Grafo no dirigido
 * @return vector<Arco>  Vector con los arcos del árbol de expansión mínima
 */
vector<Arco> Kruskal(const Grafo &G){

    vector<Arco> arbol_exp_minima;

    // Leemos los arcos del grafo
    vector<Arco> arcos = LeerGrafoNoDirigido(G);

    // Ordenamos los arcos por peso
    sort(arcos.begin(), arcos.end());

    // Inicializamos la estructura Union-Find
    UnionFind uf(G.size());

    // Recorremos los arcos en orden creciente de peso
    for (auto it = arcos.begin(); it != arcos.end() && arbol_exp_minima.size() < G.size()-1; it++){
        // Si los extremos del arco no están en la misma componente conexa, añadimos el arco al árbol de expansión mínima
        if (!uf.mismoConjunto(it->u, it->v)){ // Función de factibilidad
            arbol_exp_minima.push_back(*it);
            uf.union_(it->u, it->v); // Función de selección
        }
    }

    return arbol_exp_minima;
}


/**
 * @brief Resuelve el problema del árbol de expansión mínima mediante el algoritmo de Prim
 * 
 * @param G  Grafo no dirigido
 * @return vector<Arco>  Vector con los arcos del árbol de expansión mínima
 */
vector<Arco> Prim(const Grafo &G){

    vector<Arco> arbol_exp_minima;
    vector<int> candidatos, seleccionados;

    // Inicializamos los conjuntos de candidatos
    for (int i = 0; i < G.size(); i++)
        candidatos.push_back(i);


    // Añadimos un nodo inicial a los seleccionados
    seleccionados.push_back(*candidatos.begin());
    candidatos.erase(candidatos.begin());
    while (seleccionados.size() < G.size()){
        
        // Buscamos el nodo de los candidatos más cercano a los seleccionados
        Arco arco_minimo = {-1, -1, INT_MAX};
        auto it_seleccionado = candidatos.end();

        for (auto it_selec = seleccionados.begin(); it_selec != seleccionados.end(); it_selec++){
            for (auto it_cand = candidatos.begin(); it_cand != candidatos.end(); it_cand++){
                if ( (G[*it_selec][*it_cand] != NO_CONECTADO) && (G[*it_selec][*it_cand] < arco_minimo.peso) ){
                    arco_minimo = { *it_selec, *it_cand, G[*it_selec][*it_cand] };
                    it_seleccionado = it_cand;
                }
            }
        }
        
        // Añadimos el arco
        arbol_exp_minima.push_back(arco_minimo);

        // Añadimos el nodo seleccionado a los seleccionados y lo eliminamos de los candidatos
        seleccionados.push_back(*it_seleccionado);
        candidatos.erase(it_seleccionado);
    }

    return arbol_exp_minima;
}



ostream &operator<<(ostream &os, const Grafo &G){
    for (const vector<int> &fila : G){
        for (int peso : fila){
            if (peso == NO_CONECTADO){
                os << setw(3) << "X";
            } else {
                os << setw(3) << peso;
            }
        }
        os << endl;
    }
    return os;
}




int main(){
    
    Grafo G = {
        {NO_CONECTADO, 1, NO_CONECTADO, 4, NO_CONECTADO, NO_CONECTADO, NO_CONECTADO},
        {1, NO_CONECTADO, 2, 6, 4, NO_CONECTADO, NO_CONECTADO},
        {NO_CONECTADO, 2, NO_CONECTADO, NO_CONECTADO, 5, 6, NO_CONECTADO},
        {4, 6, NO_CONECTADO, NO_CONECTADO, 3, NO_CONECTADO, 4},
        {NO_CONECTADO, 4, 5, 3, NO_CONECTADO, 8, 7},
        {NO_CONECTADO, NO_CONECTADO, 6, NO_CONECTADO, 8, NO_CONECTADO, 3},
        {NO_CONECTADO, NO_CONECTADO, NO_CONECTADO, 4, 7, 3, NO_CONECTADO}
    };

    cout << "Grafo original:" << endl;
    cout << G << endl;

    vector<Arco> arbol_exp_minima;
    #ifdef PRIM
    arbol_exp_minima = Prim(G);
    cout << "Árbol de expansión mínima mediante Prim:" << endl;
    #endif
    #ifdef KRUSKAL
    arbol_exp_minima = Kruskal(G);
    cout << "Árbol de expansión mínima mediante Kruskal:" << endl;
    #endif

    cout << ModificarGrafoNoDirigido(G, arbol_exp_minima) << endl;

    cout << "Suma de los pesos de los arcos del árbol de expansión mínima: " << sumaPesos(arbol_exp_minima) << endl;

    cout << "Arcos del árbol de expansión mínima:" << endl;
    for (const Arco &arco : arbol_exp_minima){
        cout << arco.u << " - " << arco.v << " (" << arco.peso << ")" << endl;
    }


    return 0;
}