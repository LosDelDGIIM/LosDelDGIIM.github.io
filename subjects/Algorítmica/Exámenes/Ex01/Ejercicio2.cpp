/**
 * @file Ejercicio2.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 2 del Examen 1 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex01)
 * 
 * *Enunciado:*
 * Una empresa de gestión de aguas ha encontrado un nuevo pozo capaz de abastecer a una serie de $N$ pueblos de una comarca.
 * Para diseñar la estrategia de abastecimiento deciden calcular el coste de interconectar (mediante tuberías) cada par de pueblos $x$ e $y$ entre sí, $c(x, y)$,
 *      y cada pueblo directamente con el pozo $p$, $c(x, p)$.
 * Diseñad un algoritmo para que dicha empresa pueda abastecer de agua a los $N$ pueblos usando ese pozo de manera que
 *      el coste de construir toda la infraestructura sea el mínimo.
 * El algoritmo debe encontrar la solución óptima y además hacerlo de forma eficiente.
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 * Aunque en un primer momento podríamos pensar que se trata de un problema de caminos mínimos (aplicar el algoritmo de Floyd), en realidad no se nos pide
 *      encontrar el camino mínimo entre cada par de nodos del grafo, sino que tan solo nos piden que estén todos conectados con un coste mínimo (árbol generador minimal).
 * Los datos iniciales nos indican que el grafo dado es completo, ya que la empresa de gestión de aguas ha calculado el coste de interconectar cada par de pueblos y
 *      cada pueblo con el pozo. Por tanto, podemos aplicar el algoritmo de Kruskal para encontrar el árbol generador minimal del grafo, que sabemos que proporciona
 *      la solución óptima al problema.
 * Supondremos que el grafo es no dirigido, ya que no se nos indica lo contrario.
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
    // Matriz de costes de interconectar cada par de pueblos y cada pueblo con el pozo
    // El pozo viene dado por la última fila/columna de la matriz
    vector<vector<int>> costes = {
        {0, 1, 2, 4, 5},
        {1, 0, 3, 6, 7},
        {2, 3, 0, 8, 9},
        {4, 6, 8, 0, 10},
        {5, 7, 9, 10, 0}
    };
    
    /* OPCIONAL: Lectura de los datos de entrada 
    // En el examen podríamos suponer el grafo dado por su matriz de adyacencia C,
    //      pero en este caso lo leeremos de forma interactiva para poder probar el algoritmo

    int N_pueblos;
    cout << "Introduce el numero de pueblos: ";
    cin >> N_pueblos;

    vector<vector<int>> costes(N_pueblos+1, vector<int>(N_pueblos+1));  // +1 para incluir el pozo
    for (int i=0; i<N_pueblos; ++i){
        for (int j=i+1; j<N_pueblos; ++j){
            cout << "Introduce el coste de interconectar el pueblo " << i << " con el pueblo " << j << ": ";
            cin >> costes[i][j];
            costes[j][i] = costes[i][j];  // El grafo es no dirigido
        }
        cout << "Introduce el coste de interconectar el pueblo " << i << " con el pozo: ";
        cin >> costes[i][N_pueblos];
        costes[N_pueblos][i] = costes[i][N_pueblos];  // El grafo es no dirigido
    }
    */

    GrafoNoDirigido Conexiones(costes);
    int pozo = Conexiones.getNumNodos()-1;
    GrafoNoDirigido infraestructura = Kruskal(Conexiones);


    cout << "Coste total de la infraestructura: " << infraestructura.sumaPesos() << endl;
    cout << "Arcos de la infraestructura:" << endl;
    // Pueblos numerados de 0 a N-1
    for (const Arco &arco : infraestructura.getArcos()){
        if (arco.origen == pozo)
            cout << "Pozo -> " << "Pueblo " << arco.destino << " = " << arco.peso << endl; 
        else if (arco.destino == pozo)
            cout << "Pozo -> " << "Pueblo " << arco.origen << " = " << arco.peso << endl;
        else
            cout << "Pueblo " << arco.origen << " -> " << "Pueblo " << arco.destino << " = " << arco.peso << endl;
    }
}