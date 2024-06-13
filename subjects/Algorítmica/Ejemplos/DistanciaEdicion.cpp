/**
 * @file DistanciaEdicion.cpp
 * @brief  Resolución del problema de la distancia de edición mediante Programación Dinámica
 * 
 * Dadas dos cadenas de caracteres, se trata de encontrar la distancia de edición entre ambas.
 * Esta distancia se define como el número mínimo de operaciones necesarias para transformar una cadena en la otra.
 * Estas operaciones pueden ser:
 *      - Inserción de un carácter
 *      - Eliminación de un carácter
 *      - Sustitución de un carácter
 * 
 * X[i] denota el i-ésimo carácter de la cadena X
 * Y[j] denota el j-ésimo carácter de la cadena Y
 * D[i][j] denota la distancia de edición entre X[0..i] e Y[0..j]
 */



#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;


/**
 * @brief Algoritmo de Distancia de Edición para hallar la distancia de edición entre dos cadenas
 * 
 * @param X  Cadena X
 * @param Y  Cadena Y
 * @param D  Matriz D con las distancias de edición
 */
void DistanciaEdicion(const string &X, const string &Y, vector<vector<int>> &D){
        
    // Inicializamos la matriz D
    D = vector<vector<int>>(X.length(), vector<int>(Y.length(), 0));

    // Caso base: Col 0.
    if (X[0] != Y[0]) D[0][0] = 1;
    for (int i = 1; i < X.length(); i++){
        D[i][0] = D[i-1][0];
        if (X[i] != Y[0]) D[i][0]++;
    }
    
    // Caso base: Fila 0.
    for (int j = 1; j < Y.length(); j++){
        D[0][j] = D[0][j-1];
        if (X[0] != Y[j]) D[0][j]++;
    }

        
    // Algoritmo de Distancia de Edición
    // Si X[i] == Y[j], entonces D[i][j] = D[i-1][j-1]            (coiniciden los caracteres, por lo que no se añade ninguna operación)
    // Si X[i] != Y[j], entonces D[i][j] = 1 + min(CosteInsercion, CosteEliminacion, CosteSustitucion), donde:
    //      - CosteInsercion = D[i][j-1],       ya que se inserta un carácter en X[i] para que coincida con Y[j]
    //      - CosteEliminacion = D[i-1][j],     ya que se elimina un carácter de X[i] para que coincida con Y[j]
    //      - CosteSustitucion = D[i-1][j-1],   ya que se sustituye el carácter X[i] por Y[j]
    for (int i = 1; i < X.length(); i++){
        for (int j = 1; j < Y.length(); j++){
            if (X[i] == Y[j])
                D[i][j] = D[i-1][j-1];
            else
                D[i][j] = 1+min({D[i-1][j], D[i][j-1], D[i-1][j-1]});
        }
    }
}

/**
 * @brief Imprime la matriz D con las distancias de edición
 * 
 * @param D  Matriz D con las distancias de edición
 * @param X  Cadena X
 * @param Y  Cadena Y
 */
void imprimirMatriz(const vector<vector<int>> &D, const string &X, const string &Y){
    
    int anchura = 3;
    
    cout << setw(anchura) << "|";
    for (int j = 0; j < D[0].size(); j++){
        cout << setw(anchura) << Y[j];
    }
    cout << endl;
    
    // Linea divisoria
    for (int j = 0; j <= D[0].size(); j++){
        cout << setw(anchura) << setfill('-') << "";
    }
    cout << setfill(' ') << endl;

    for (int i = 0; i < D.size(); i++){
        cout << setw(anchura-2) << X[i] << " |";
        for (int j = 0; j < D[0].size(); j++){
            cout << setw(anchura) << D[i][j];
        }
        cout << endl;
    }
    cout << endl;
}


int main(){
    string X = "nacht";
    string Y = "natch";
    vector<vector<int>> D;

    DistanciaEdicion(X, Y, D);
    imprimirMatriz(D, X, Y);

    cout << "Distancia de edicion entre " << X << " y " << Y << ": " << D[X.length()-1][Y.length()-1] << endl;

    return 0;
}