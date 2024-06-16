/**
 * @file Dijkstra.cpp
 * @brief Resolución del problema caminos mínimos mediante Greedy y el algoritmo de Dijkstra
 * 
 * Sea G=(V,A) un grafo dirigido, con arcos ponderados con pesos no negativos,
 * y sea s un nodo origen.
 * El problema consiste en hallar el camino mínimo desde s a cualquier otro nodo del grafo.
 * 
 * - Conjunto de candidatos: Todos los nodos del grafo
 * - Conjunto de seleccionados: Nodos seleccionados
 * - Función solución: Todos los nodos han sido seleccionados
 * - Función de factibilidad: No hay
 * - Función de selección: Nodo con menor distancia al origen pasado por nodos seleccionados
 * - Función objetivo: Distancia mínima desde el origen
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "../Exámenes/Includes/Grafo.h"

using namespace std;

const int SIN_PREDECESOR = -2;          // Valor que indica que un nodo no tiene predecesor


/**
 * @brief Algoritmo de Dijkstra para hallar el camino mínimo desde un nodo origen a cualquier otro nodo del grafo
 * 
 * @param G  Grafo con el que trabajamos
 * @param origen  Nodo origen
 * @param D  Vector donde se almacenarán las distancias mínimas
 * @param P  Vector donde se almacenarán los predecesores
 */
void Dijkstra(const Grafo &G, int origen, vector<int> &D, vector<int> &P){
    
    // D[i] almacena la distancia mínima desde el nodo origen hasta el nodo i pasando solo por nodos seleccionados
    // P[i] almacena el nodo predecesor de i en el camino mínimo desde origen hasta i

    vector <int> C; // Conjunto de candidatos, nodos no seleccionados
    for (int i = 0; i < G.getNumNodos(); i++)
        if (i != origen)
            C.push_back(i);    

    // Inicializamos D y P
    D.clear();
    P.clear();
    for (int i = 0; i < G.getNumNodos(); i++){
        D.push_back(G.getPeso(origen, i));
        
        // Si el nodo i es adyacente al origen, su predecesor es el origen
        if (G.conectados(origen, i))
            P.push_back(origen);
        else
            P.push_back(SIN_PREDECESOR);
    }

    // Buscamos el camino mínimo a cada nodo
    while (!C.empty()){

        // Seleccionamos el nodo it_seleccionado con la distancia mínima al origen
        auto it_seleccionado = C.begin();
        for (auto it = C.begin(); it != C.end(); it++){
            if (D[*it] < D[*it_seleccionado])
                it_seleccionado = it;
        }
        
        // Eliminamos it_seleccionado de C
        int seleccionado = *it_seleccionado;
        C.erase(it_seleccionado);

        // Actualizamos las distancias y predecesores de los nodos no seleccionados
        for (int no_seleccionado : C){
            if (G.conectados(seleccionado, no_seleccionado)){ // Solo actualizamos los nodos adyacentes a seleccionado

                // Si es más corto pasar por seleccionado, actualizamos la distancia y el predecesor
                if (D[seleccionado] + G.getPeso(seleccionado, no_seleccionado) < D[no_seleccionado]){
                    D[no_seleccionado] = D[seleccionado] + G.getPeso(seleccionado, no_seleccionado);
                    P[no_seleccionado] = seleccionado;
                }
            }
        } // for no_seleccionado
        
    } // while !C.empty()

    
}

/**
 * @brief Recupera el camino mínimo del nodo origen al nodo destino
 * 
 * @param P  Vector de predecesores
 * @param origen  Nodo origen
 * @param destino  Nodo destino
 * @param camino  Vector donde se almacenará el camino
 */
void recuperarCamino(vector<int> &P, int origen, int destino, vector<int> &camino){
    // Caso base: Origen y destino son el mismo nodo
    if (origen == destino){
        camino.push_back(origen);
        return;
    }

    // Caso base: No hay camino entre origen y destino
    else if (P[destino] == SIN_PREDECESOR){
        cerr << "No hay camino entre " << origen << " y " << destino << endl;
        return;
    }
    
    // Caso base: Origen y destino están conectados directamente
    else if (P[destino] == origen){
        camino.push_back(origen);
        camino.push_back(destino);
        return;
    }
    // Caso general: Recuperamos el camino entre origen y destino
    else{
        recuperarCamino(P, origen, P[destino], camino);
        camino.pop_back();  // Eliminamos el último nodo (repetido, perteneciente a ambas llamadas recursivas)
        recuperarCamino(P, P[destino], destino, camino);
    }
}


int main(){

    const int NO_CONECTADO = Grafo::charNoConectado();

    vector<vector<int>> G = {
        {0, 50, 30, 100, 10},
        {NO_CONECTADO, 0, NO_CONECTADO, NO_CONECTADO, NO_CONECTADO},
        {NO_CONECTADO, 5, 0, NO_CONECTADO, NO_CONECTADO},
        {NO_CONECTADO, 20, 50, 0, NO_CONECTADO},
        {NO_CONECTADO, NO_CONECTADO, NO_CONECTADO, 10, 0}
    };
    int origen = 0;

    vector<int> D, P;
    Dijkstra(G, origen, D, P);
    
    // Imprimimos los caminos mínimos
    int coste_total = 0;
    for (int i = 0; i < G.size(); i++){
        coste_total += D[i];

        vector<int> camino;
        recuperarCamino(P, origen, i, camino);
        cout << "Camino minimo desde " << origen << " hasta " << i << ". Coste: " << D[i] << endl;
        for (int j = 0; j < camino.size(); j++){
            cout << camino[j];
            if (j != camino.size()-1)
                cout << " -> ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Coste total de los caminos minimos: " << coste_total << endl;

    return 0;
}