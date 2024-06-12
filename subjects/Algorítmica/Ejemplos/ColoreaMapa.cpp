/**
 * @file ColoreaMapa.cpp
 * @author Arturo Olivares Martos
 * 
 * @brief Programa para resolver el problema de colorear un mapa con el menor número de colores posibles.
 * 
 * El mapa se guardará en una matriz de enteros, Mapa[i][j]
 * - Mapa[i][j] = 1 si la región i está conectada con la región j
 * - Mapa[i][j] = 0 si la región i no está conectada con la región j
 * 
 * Colores[k] = c indica que la región k está pintada con el color c
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INVALIDO = -1;
const int CONECTADO = 1;
const int NO_CONECTADO = 0;

struct Nodo{
    int nColores;
    vector<int> colores;
};


/**
 * @brief Comprueba si es factible pintar una región con un color determinado
 * 
 * @param mapa  Matriz de adyacencia del mapa
 * @param e_nodo  Nodo actual
 * @param color  Color a pintar
 * @return true  Si es factible pintar la región con el color
 * @return false  Si no es factible pintar la región con el color
 */
bool factible(const vector<vector<int>>& mapa, Nodo& e_nodo, int color){
    
    // Obtenemos la región que estamos pintando
    int a_pintar = find(e_nodo.colores.begin(), e_nodo.colores.end(), INVALIDO) - e_nodo.colores.begin();

    bool es_factible = true;

    // Entre los adyacentes a a_pintar, buscamos si hay alguno pintado con el color que queremos pintar
    for(int i = 0; (i < mapa.size()) && es_factible; ++i){
        if(mapa[a_pintar][i] == CONECTADO)
            es_factible = e_nodo.colores[i] != color;
        
    }

    return es_factible;
}


/**
 * @brief Función recursiva que resuelve el problema de colorear un mapa con el menor número de colores posibles
 * 
 * @param mapa  Matriz de adyacencia del mapa
 * @param e_nodo Nodo actual en exploración
 * @param sol  Nodo solución
 */
void colorearMapa(const vector<vector<int>>& mapa, Nodo& e_nodo, Nodo& sol){

    // Si ya hemos coloreado todas las regiones, comprobamos si es una solución mejor
    if(find(e_nodo.colores.begin(), e_nodo.colores.end(), INVALIDO) == e_nodo.colores.end()){
        if (e_nodo.nColores < sol.nColores){
            sol = e_nodo;
        }
        return;
    }
    
    // Obtenemos el primer nodo sin colorear
    int a_pintar = find(e_nodo.colores.begin(), e_nodo.colores.end(), INVALIDO) - e_nodo.colores.begin();

    // Coloreamos el nodo con todos los colores posibles.
    // Como ya sabemos que hay una sol con nColores, limitamos el número de colores a nColores
    for(int color = 0; color < sol.nColores; color++){

        // Indica si el color es nuevo
        bool nuevo_color = find(e_nodo.colores.begin(), e_nodo.colores.end(), color) == e_nodo.colores.end();

        // Si el color es factible, lo pintamos y seguimos explorando
        if(factible(mapa, e_nodo, color)){
            e_nodo.colores[a_pintar] = color;
            if (nuevo_color) e_nodo.nColores++;
            colorearMapa(mapa, e_nodo, sol);
            if (nuevo_color) e_nodo.nColores--;
            e_nodo.colores[a_pintar] = INVALIDO;
        }

    }

}

int main(){

    // Matriz de adyacencia del mapa
    vector<vector<int>> mapa = {
        {INVALIDO, 1, 1, 0, 1, 1, 0},
        {1, INVALIDO, 0, 0, 1, 0, 1},
        {1, 0, INVALIDO, 1, 1, 1, 1},
        {0, 0, 1, INVALIDO, 1, 0, 1},
        {1, 1, 1, 1, INVALIDO, 0, 1},
        {1, 0, 1, 0, 0, INVALIDO, 1},
        {0, 1, 1, 1, 1, 1, INVALIDO}
    };


    // Nodo raiz
    Nodo raiz;
    raiz.nColores = 0;
    raiz.colores = vector<int>(mapa.size(), INVALIDO);


    // Nodo solución. Inicialmente, se asume un color para cada región (trivial)
    Nodo sol;
    sol.nColores = mapa.size();
    for (int i = 0; i < mapa.size(); i++)
        sol.colores.push_back(i);

    colorearMapa(mapa, raiz, sol);

    cout << "Numero de colores: " << sol.nColores << endl;
    cout << "Colores: ";
    for(auto color : sol.colores)
        cout << color << " ";
    cout << endl;

    return 0;
}