/**
 * @file Floyd.cpp
 * @brief Resolución del problema caminos mínimos mediante Programación Dinámica y el algoritmo de Floyd
 * 
 * Sea G=(V,A) un grafo dirigido, con arcos ponderados con pesos no negativos.
 * El problema consiste en hallar el camino mínimo (secuencia de arcos que unen un nodo inicial y un nodo destino,
 * cuya suma de pesos es mínima) entre cualquier par de nodos del grafo.
 */



#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "../Exámenes/Includes/Grafo.h"

using namespace std;

const int SIN_PREDECESOR = -2;          // Valor que indica que un nodo no tiene predecesor


/**
 * @brief Algoritmo de Floyd para hallar los caminos mínimos entre cualquier par de nodos de un grafo ponderado
 *        con pesos no negativos
 * @param G  Grafo con el que trabajamos
 * @param D  Matriz de distancias mínimas
 * @param P  Matriz de predecesores
 */
void Floyd(const Grafo &G, vector<vector<int>> &D, vector<vector<int>> &P){
    int n = G.getNumNodos();
    
    // Inicializamos la matriz de distancias y la matriz de predecesores
    D = vector<vector<int>>(n, vector<int>(n, Grafo::charNoConectado()));
    P = vector<vector<int>>(n, vector<int>(n, SIN_PREDECESOR));

    // Inicializamos la matriz de predecesores y la matriz de distancias
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (G.conectados(i, j)){
                D[i][j] = G.getPeso(i, j);
                P[i][j] = i;
            }

    
    // Algoritmo de Floyd
    /*
        En la etapa K, D[i][j] contiene la longitud del camino mínimo entre i y j que considera como vértices intermedios
            a los vértices {0, 1, ..., k-1}.
        Notaremos por D_k la matriz de distancias en la etapa k.

        Entonces:
            D_k[i][j] = min(D_{k-1}[i][j], D_{k-1}[i][k] + D_{k-1}[k][j])

        Notemos que D[i][k] y D[k][j] no cambian en la etapa k, ya que:
            D_k[i][k] = min(D_{k-1}[i][k], D_{k-1}[i][k] + D_{k-1}[k][k]) = D_{k-1}[i][k]
            D_k[k][j] = min(D_{k-1}[k][j], D_{k-1}[k][k] + D_{k-1}[k][j]) = D_{k-1}[k][j]

        Por tanto, tenemos:
            D_k[i][j] = min(D_{k-1}[i][j], D_k[i][k] + D_k[k][j])
        
        Equivalente, cuando partamos de D_{k-1}[i][j], para calcular D_k[i][j] tan solo será necesario actualizar su valor en el caso de que
            D_{k-1}[i][j] > D_{k-1}[i][k] + D_{k-1}[k][j]
        
        De esta forma, evitamos usar k matrices (una por cada etapa k), y tan solo necesitamos una matriz D para almacenar las distancias
            en cada etapa k (actualizándola en cada iteración de k).       
    */
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){

                // Si puedo ir de i a j pasando por k,
                if (D[i][k] != Grafo::charNoConectado() && D[k][j] != Grafo::charNoConectado()){

                    // Si no había camino directo de i a j, o si el camino por k es mejor
                    if ( (D[i][j] == Grafo::charNoConectado()) || (D[i][j] > D[i][k] + D[k][j]) ){
                        D[i][j] = D[i][k] + D[k][j];
                        P[i][j] = k;
                    }
                }

            } // for j
        } // for i
    } // for k
}

/**
 * @brief Recupera el camino mínimo entre dos nodos a partir de la matriz de predecesores
 * 
 * @param P  Matriz de predecesores
 * @param origen  Nodo origen
 * @param destino  Nodo destino
 * @param camino  Vector donde se almacenará el camino
 */
void recuperarCamino(vector<vector<int>> &P, int origen, int destino, vector<int> &camino){
    // Caso base: No hay camino entre origen y destino
    if (P[origen][destino] == SIN_PREDECESOR){
        cerr << "No hay camino entre " << origen << " y " << destino << endl;
        return;
    }
    // Caso base: Origen y destino son el mismo nodo
    else if (origen == destino){
        camino.push_back(origen);
        return;
    }
    // Caso base: Origen y destino están conectados directamente
    else if (P[origen][destino] == origen){
        camino.push_back(origen);
        camino.push_back(destino);
        return;
    }
    // Caso general: Recuperamos el camino entre origen y destino
    else{
        recuperarCamino(P, origen, P[origen][destino], camino);
        camino.pop_back();  // Eliminamos el último nodo (repetido, perteneciente a ambas llamadas recursivas)
        recuperarCamino(P, P[origen][destino], destino, camino);
    }
}


int main(){

    const int NO_CONECTADO = Grafo::charNoConectado();
    vector<vector<int>> G = {
        {0, 5, NO_CONECTADO, NO_CONECTADO},
        {50, 0, 15, 5},
        {30, NO_CONECTADO, 0, 15},
        {15, NO_CONECTADO, 5, 0}
    };

    vector<vector<int>> D, P;
    Floyd(G, D, P);

    cout << "Matriz de distancias minimas:" << endl;
    for (int i = 0; i < D.size(); i++){
        for (int j = 0; j < D[i].size(); j++){
            if (D[i][j] == NO_CONECTADO)
                cout << setw(5) << "X";
            else
                cout << setw(5) << D[i][j];
        }
        cout << endl;
    }
    cout << endl;

    cout << "Matriz de predecesores:" << endl;
    for (int i = 0; i < P.size(); i++){
        for (int j = 0; j < P[i].size(); j++){
            if (P[i][j] == SIN_PREDECESOR)
                cout << setw(5) << "X";
            else
                cout << setw(5) << P[i][j];
        }
        cout << endl;
    }
    cout << endl;


    pair<int, int> arco = {1, 0};
    vector<int> camino;
    recuperarCamino(P, arco.first, arco.second, camino);

    cout << "Camino minimo entre " << arco.first << " y " << arco.second << " de longitud " << D[arco.first][arco.second] << ": ";
    for (int i = 0; i < camino.size(); i++){
        cout << camino[i] << " ";
    }






    return 0;
}