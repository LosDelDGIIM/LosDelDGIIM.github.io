/**
 * @file LCS.cpp
 * @brief Resolución del problema de LCS (Longest Common Subsequence) mediante Programación Dinámica
 * 
 * Dadas dos cadenas de caracteres, se trata de encontrar la subsecuencia común más larga entre ambas.
 * 
 * X[i] denota el i-ésimo carácter de la cadena X
 * Y[j] denota el j-ésimo carácter de la cadena Y
 * L[i][j] denota la longitud de la subsecuencia común más larga entre X[0..i] e Y[0..j]
 */



#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

/**
 * @brief Algoritmo de LCS (Longest Common Subsequence) para hallar la longitud de la subsecuencia común más larga
 * 
 * @param X  Cadena X
 * @param Y  Cadena Y
 * @param L  Matriz L con las longitudes de las subsecuencias comunes
 */
void LCS(const string &X, const string &Y, vector<vector<int>> &L){
        
    // Inicializamos la matriz L
    L = vector<vector<int>>(X.length(), vector<int>(Y.length(), 0));

    // Caso base: Col 0.
    if (X[0] == Y[0]) L[0][0] = 1;
    for (int i = 1; i < X.length(); i++){
        L[i][0] = L[i-1][0];
        if (X[i] == Y[0]) L[i][0] = 1;
    }
    
    // Caso base: Fila 0.
    for (int j = 1; j < Y.length(); j++){
        L[0][j] = L[0][j-1];
        if (X[0] == Y[j]) L[0][j] = 1;
    }
        
    // Algoritmo de LCS
    // Si X[i] == Y[j], entonces L[i][j] = L[i-1][j-1] + 1            (coiniciden los caracteres, por lo que se añade uno a la subsecuencia común)
    // Si X[i] != Y[j], entonces L[i][j] = max(L[i-1][j], L[i][j-1])  (no coinciden los caracteres, por lo que se toma el máximo de las subsecuencias)
    for (int i = 1; i < X.length(); i++){
        for (int j = 1; j < Y.length(); j++){
            if (X[i] == Y[j])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }
}



/**
 * @brief Imprime la matriz L
 * 
 * @param L  Matriz L
 * @param X  Cadena X
 * @param Y  Cadena Y
 */
void imprimirMatriz(const vector<vector<int>> &L, const string &X, const string &Y){
    
    int anchura = 3;
    
    cout << setw(anchura) << "|";
    for (int j = 0; j < L[0].size(); j++){
        cout << setw(anchura) << Y[j];
    }
    cout << endl;
    
    // Linea divisoria
    for (int j = 0; j <= L[0].size(); j++){
        cout << setw(anchura) << setfill('-') << "";
    }
    cout << setfill(' ') << endl;

    for (int i = 0; i < L.size(); i++){
        cout << setw(anchura-2) << X[i] << " |";
        for (int j = 0; j < L[0].size(); j++){
            cout << setw(anchura) << L[i][j];
        }
        cout << endl;
    }
    cout << endl;
}


/**
 * @brief Recupera la subsecuencia común más larga a partir de la matriz L
 * 
 * @param X  Cadena X
 * @param Y  Cadena Y
 * @param L  Matriz L con las longitudes de las subsecuencias comunes
 * @return string  Subsecuencia común más larga
 */
string recuperarLCS(const string &X, const string &Y, const vector<vector<int>> &L){
    
    string subsecuencia = "";
    int i = X.length()-1;
    int j = Y.length()-1;
    
    while (i > 0 && j > 0){
        if ( (L[i][j] == L[i-1][j-1] + 1) && (X[i] == Y[j]) ){
            // Coinciden los caracteres
            subsecuencia = X[i] + subsecuencia;
            i--;
            j--;
        } else if (L[i][j] == L[i-1][j]){
            // No coinciden los caracteres, se retrocede en X
            i--;
        } else if (L[i][j] == L[i][j-1]){
            // No coinciden los caracteres, se retrocede en Y
            j--;
        }
    }

    // Caso especial: Analizamos la primera fila y la primera columna
    if (i == 0){
        while (j >= 0){
            if (X[i] == Y[j])
                subsecuencia = X[i] + subsecuencia;
            
            j--;
        }
    } else if (j == 0){
        while (i >= 0){
            if (X[i] == Y[j])
                subsecuencia = X[i] + subsecuencia;
            
            i--;
        }
    }
    
    return subsecuencia;
}


int main(){
    
    string X = "ABCB";
    string Y = "BDCAB";
    
    vector<vector<int>> L;
    LCS(X, Y, L);
    
    imprimirMatriz(L, X, Y);
    
    cout << "Cadena X: " << X << endl;
    cout << "Cadena Y: " << Y << endl;
    cout << "Longitud de la subsecuencia comun mas larga: " << L[X.length()-1][Y.length()-1] << endl;
    cout << "Subsecuencia comun mas larga: " << recuperarLCS(X, Y, L) << endl;
    
    return 0;
}