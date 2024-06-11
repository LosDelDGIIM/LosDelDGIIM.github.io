/**
 * @file Sudoku.cpp
 * @author Arturo Olivares Martos
 * 
 * @brief Programa para resolver un sudoku mediante backtracking
 * 
 * El sudoku es un juego de lógica en el que se nos presenta un tablero de 9x9 casillas dividido en 9 subtableros de 3x3 casillas.
 * El objetivo es rellenar el tablero con dígitos (1-9) de tal forma que no haya números repetidos en ninguna fila, columna o subtablero.
 * Resolveremos el sudoku mediante la técnica de backtracking.
 * 
 * Las casillas vacías se representarán con un 0.
 * Las casillas que rellenemos se representarán con un número entre 1 y 9.
 * Las casillas fijas se representarán con un número entre -1 y -9 (para diferenciarlas de las casillas que hemos rellenado).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef vector<vector<int>> Sudoku;

const int CAS_VACIA = 0;      // Valor que indica que una columna está vacía

/**
 * @brief Método que imprime el sudoku
 * 
 * @param sudoku Sudoku que queremos imprimir
 */
void imprimirSudoku(const Sudoku &sudoku){
    for (int i = 0; i < sudoku.size(); i++){
        for (int j = 0; j < sudoku.size(); j++){
            if (sudoku[i][j] == CAS_VACIA){
                cout << ". ";
            } else {
                cout << abs(sudoku[i][j]) << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


bool factible (const Sudoku &sudoku, int fil, int col, int num){

    bool es_factible = 0<= fil && fil < sudoku.size() && 0 <= col && col < sudoku.size();    // Comprobamos que la fila y la columna estén dentro del tablero

    if (es_factible){
        es_factible = sudoku[fil][col] == CAS_VACIA;               // Comprobamos que la casilla esté vacía

        if (es_factible){
            // Comprobamos que el número no esté en la fila
            for (int i = 0; i < sudoku.size() && es_factible; i++)
                es_factible = abs(sudoku[fil][i]) != num;
                

            // Comprobamos que el número no esté en la columna
            for (int i = 0; i < sudoku.size() && es_factible; i++)
                es_factible = abs(sudoku[i][col]) != num;

            // Comprobamos que el número no esté en el subtablero
            int ini_fil = 3*(fil/3);
            int ini_col = 3*(col/3);

            for (int i = ini_fil; (i < ini_fil + 3) && es_factible; i++){
                for (int j = ini_col; (j < ini_col + 3) && es_factible; j++){
                    es_factible = abs(sudoku[i][j]) != num;
                    
                } // For col en subtablero
            } // For fil en subtablero

        } // if casilla vacía
    } // if casilla válida

    return es_factible;
}


/**
 * @brief Método que resuelve el sudoku mediante backtracking
 * 
 * @param sudoku Sudoku que queremos resolver
 * @param k Número de la casilla que queremos rellenar
 */
void resolverSudoku(Sudoku &sudoku, int k){
    
    if (k >= sudoku.size()*sudoku.size()){
        cout << "Sudoku resuelto: " << endl;
        imprimirSudoku(sudoku);
        return;
    }

    int fil = k/sudoku.size();
    int col = k%sudoku.size();

    // Si la casilla ya está fijada, pasamos a la siguiente
    if (sudoku[fil][col] != CAS_VACIA){
        resolverSudoku(sudoku, k+1);
    }

    // Si la casilla está vacía, probamos a rellenarla con un número
    for (int opt = 1; opt <= sudoku.size(); opt++){
        if (factible(sudoku, fil, col, opt)){
            sudoku[fil][col] = opt;
            resolverSudoku(sudoku, k+1);
            sudoku[fil][col] = CAS_VACIA;
        } // if factible
    } // for opt
}


int main(){

    // Sudoku a resolver
    Sudoku sudoku = {
        {0, 1, 3, 0, 8, 0, 0, 0, 0},
        {0, 6, 7, 0, 4, 0, 8, 9, 0},
        {4, 0, 0, 0, 0, 0, 6, 0, 2},
        {0, 0, 0, 8, 2, 7, 1, 0, 0},
        {0, 3, 2, 1, 0, 0, 0, 7, 0},
        {0, 0, 9, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 4, 0, 0, 7, 2, 0},
        {0, 0, 0, 0, 0, 0, 9, 6, 0},
        {0, 4, 0, 2, 6, 9, 3, 0, 1}
    };

    // Convertimos los dígitos fijos en negativos
    for (int i = 0; i < sudoku.size(); i++){
        for (int j = 0; j < sudoku.size(); j++){
            if (sudoku[i][j] != CAS_VACIA){
                sudoku[i][j] = -abs(sudoku[i][j]);
            }
        }
    }

    cout << "Sudoku inicial: " << endl;
    imprimirSudoku(sudoku);
    cout << endl << endl;

    resolverSudoku(sudoku, 0);

    return 0;
}