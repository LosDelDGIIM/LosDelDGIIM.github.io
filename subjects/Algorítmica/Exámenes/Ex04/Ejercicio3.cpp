/**
 * @file Ejercicio3.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 3 del Examen 4 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex04)
 * 
 * *Enunciado:*
 * La empresa X ha decidido instalar una red de fibra óptica para interconectar sus seis
 * centros de trabajo. El coste (positivo) del tendido de cable entre ellos aparece en la figura siguiente.
 * 
 * (En el examen se aportaba un grafo, pero por simplicidad aquí aportaremos la matriz de adyacencia)
 * M = {
 *      {0, 3, X, 7, X, 3},
 *      {3, 0, 4, 8, X, 6},
 *      {X, 4, 0, 9, X, 5},
 *      {7, 8, 9, 0, 8, X},
 *      {X, X, X, 8, 0, 6},
 *      {3, 6, 5, X, 6, 0}
 * }
 * 
 * 
 * Especificad un algoritmo que sea capaz de encontrar la forma de interconectar todos los centros con
 * un coste mı́nimo, y aplicadlo para resolver el problema de la figura, describiendo el proceso paso a
 * paso.
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 * Este problema se trata de encontrar el AGM (Árbol Generador Mínimo) de un grafo no dirigido y conexo.
 * Para ello, podemos utilizar el algoritmo de Prim o el algoritmo de Kruskal, optando por el algoritmo de Kruskal en este caso.
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "GrafoNoDirigido.h"
#include "UnionFind.h"

using namespace std;


/**
 * @brief Calcula el Árbol Generador Mínimo de un grafo no dirigido mediante el algoritmo de Kruskal
 * 
 * @param G  Grafo no dirigido a partir del cual se quiere calcular el AGM
 * @return GrafoNoDirigido Árbol Generador Mínimo del grafo
 */
GrafoNoDirigido Kruskal(const GrafoNoDirigido &G){

    GrafoNoDirigido arbol_exp_minima(G.getNumNodos());

    // Leemos los arcos del grafo
    vector<Arco> arcos = G.getArcos();

    // Ordenamos los arcos por peso
    sort(arcos.begin(), arcos.end());

    // Inicializamos la estructura Union-Find
    UnionFind uf(G.getNumNodos());

    // Recorremos los arcos en orden creciente de peso
    int aristas_seleccionadas = 0;
    for (auto it = arcos.begin(); it != arcos.end() && aristas_seleccionadas < G.getNumNodos()-1; it++){
        // Si los extremos del arco no están en la misma componente conexa, añadimos el arco al árbol de expansión mínima
        if (!uf.mismoConjunto(it->origen, it->destino)){ // Función de factibilidad
            arbol_exp_minima.setArco(*it);
            ++aristas_seleccionadas;
            uf.union_(it->origen, it->destino); // Función de selección
        }
    }

    return arbol_exp_minima;
}


int main(int argc, char const *argv[]){
    const int NO_CONECTADO = GrafoNoDirigido::charNoConectado();
    // Matriz de costes de interconectar cada par de pueblos y cada pueblo con el pozo
    vector<vector<int>> M = {
        {0, 3, NO_CONECTADO, 7, NO_CONECTADO, 3},
        {3, 0, 4, 8, NO_CONECTADO, 6},
        {NO_CONECTADO, 4, 0, 9, NO_CONECTADO, 5},
        {7, 8, 9, 0, 8, NO_CONECTADO},
        {NO_CONECTADO, NO_CONECTADO, NO_CONECTADO, 8, 0, 6},
        {3, 6, 5, NO_CONECTADO, 6, 0}
    };

    // Creamos el grafo no dirigido
    GrafoNoDirigido G(M);

    // Calculamos el Árbol Generador Mínimo
    GrafoNoDirigido AGM = Kruskal(G);

    // Mostramos el Árbol Generador Mínimo
    cout << "Árbol Generador Mínimo:" << endl;
    cout << AGM << endl;

    // Mostramos el coste total del Árbol Generador Mínimo
    cout << "Coste total del Árbol Generador Mínimo: " << AGM.sumaPesos() << endl;

    // Aristas del AGM
    cout << "Aristas del Árbol Generador Mínimo:" << endl;
    for (const Arco &arco : AGM.getArcos()){
        cout << "- " << arco << endl;
    }
    

    return 0;
}