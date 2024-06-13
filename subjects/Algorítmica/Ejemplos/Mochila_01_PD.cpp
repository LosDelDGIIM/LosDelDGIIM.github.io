/**
 * @file Mochila_01_PD.cpp
 * @brief Resolución del problema de la mochila 0-1 mediante Programación Dinámica
 * 
 * Dado un conjunto de n elementos, cada uno con un peso w_i y un valor v_i, y una mochila con capacidad P,
 * se desea determinar cuál es la combinación de elementos que maximiza el valor total sin superar la capacidad de la mochila.
 * 
 * W[i] denota el peso del elemento i
 * V[i] denota el valor del elemento i
 * P denota el peso máximo que puede soportar la mochila
 * 
 * T[i][j] denota el valor máximo que se puede obtener con los elementos 0, 1, ..., i y una mochila de capacidad j
 */



#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int NO_ASIGNADO = -1;


/**
 * @brief Imprime la tabla final con los resultados
 * 
 * @param T  Tabla con los resultados
 * @param v  Vector con los valores de los elementos
 */
void imprimirTablaFinal(const vector<vector<int>> &T, const vector<int> &v){

    int anchura = to_string(*(max_element(v.begin(), v.end()))).length() + 1;

    cout << "Tabla final:" << endl;
    cout << setw(anchura) << "|";
    for (int j = 0; j < T[0].size(); j++){
        cout << setw(anchura) << j;
    }
    cout << endl;
    
    // Linea divisoria
    for (int j = 0; j <= T[0].size(); j++){
        cout << setw(anchura) << setfill('-') << "";
    }
    cout << setfill(' ') << endl;

    for (int i = 0; i < v.size(); i++){
        cout << setw(anchura) << (to_string(v[i]) + "|");
        for (int j = 0; j < T[0].size(); j++){
            cout << setw(anchura) << T[i][j];
        }
        cout << endl;
    }
    cout << endl;
}


/**
 * @brief Inicializa la tabla con los valores base
 * 
 * @param v  Vector con los valores de los elementos
 * @param w Vector con los pesos de los elementos
 * @param P  Peso máximo que puede soportar la mochila
 * @return vector<vector<int>>  Tabla con los resultados. T[i][j] = valor máximo que se puede obtener con los elementos 0, 1, ..., i y una mochila de capacidad j
 */
vector<vector<int>> inicializarTabla(const vector<int> &v, const vector<int> &w, int P){
    vector<vector<int>> T(v.size(), vector<int>(P+1, NO_ASIGNADO));

    // Caso base: no obtenemos ningún valor si la mochila no puede soportar ningún peso
    for (int i = 0; i < v.size(); i++){
        T[i][0] = 0;
    }

    // Caso base: si solo tenemos un elemento, lo añadimos si cabe en la mochila
    for (int j = 0; j <= P; j++){
        if (w[0] <= j){
            T[0][j] = v[0];
        }else{
            T[0][j] = 0;
        }
    }

    // Caso recursivo
    // - Si cabe el objeto i en la mochila, calculamos el valor máximo que se puede obtener con y sin él:
    // - Si no cabe, el valor máximo es el mismo que sin él
    for (int i = 1; i < v.size(); i++){
        for (int j = 1; j <= P; j++){

            T[i][j] = T[i-1][j];

            if (w[i] <= j){ // Si cabe el objeto i en la mochila
                
                // Si al incluirlo entero obtenemos un valor mayor, lo incluimos
                if (T[i-1][j-w[i]] + v[i] > T[i][j]){
                    T[i][j] = T[i-1][j-w[i]] + v[i];
                }
            }

        }
    }

    return T;
}


/**
 * @brief Obtiene los elementos que se han incluido en la mochila
 * 
 * @param T  Tabla con los resultados
 * @param w  Vector con los pesos de los elementos
 * @return vector<int>  Vector que indica si el elemento i se ha incluido (1) o no (0)
 */
vector<int> obtenerElementos(const vector<vector<int>> &T, const vector<int> &w){
    vector<int> elementos(T.size(), 0);

    int i = T.size()-1;
    int j = T[0].size()-1;

    while (i > 0 && j > 0){

        // Si el valor de T[i][j] es distinto al de T[i-1][j], hemos incluido el elemento i
        if (T[i][j] != T[i-1][j]){
            elementos[i] = 1;
            j -= w[i];
        }
        i--;
    }

    // Comprobamos el primer elemento
    if (i==0 && j>=0 && T[i][j] != 0){
        elementos[i] = 1;
    }

    return elementos;
}


int main(){
    vector<int> V = {12, 10, 20, 15};
    vector<int> W = {2, 1, 3, 2};
    int P = 5;

    vector<vector<int>> T = inicializarTabla(V, W, P);
    imprimirTablaFinal(T, V);

    vector<int> elementos = obtenerElementos(T, W);

    cout << "Elementos incluidos: ";
    for (int i = 0; i < elementos.size(); i++){
        if (elementos[i] == 1){
            cout << i << " ";
        }
    }

    return 0;
}