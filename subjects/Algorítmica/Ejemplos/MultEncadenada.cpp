/**
 * @file MultEncadenada.cpp
 * @brief Resolución óptima del problema de la multiplicación encadenada de matrices mediante Programación Dinámica.
 * 
 * Dadas dos matrices A\in R^{n x m} y B\in R^{m x p}, el producto de ambas matrices es una matriz C\in R^{n x p} cuyo elemento
 * en la posición (i,j) es el resultado de multiplicar la fila i de A por la columna j de B, es decir:
 * C_{ij} = \sum_{k=1}^{m} A_{ik} * B_{kj}      --------------->  m multiplicaciones
 * 
 * Por tanto, el número total de multiplicaciones necesarias para calcular A*B es n*m*p.
 * 
 * El objetivo de este problema es encontrar el orden óptimo de multiplicación de una secuencia de matrices, de forma que se minimice
 * el número total de multiplicaciones necesarias. Es decir, dada una secuencia de matrices M0, M2, ..., Mn, se busca encontrar dónde se
 * deben colocar los paréntesis para minimizar el número total de multiplicaciones.
 * 
 * Notaremos el tamaño de la matriz Mi como p_{i} x p_{i+1}, donde p_0 es el número de filas de la primera matriz y p_{n+1} es el número de columnas
 * de la última matriz.
 * 
 * N[i][j] = número mínimo de multiplicaciones necesarias para calcular el producto de las matrices Mi, Mi+1, ..., Mj.
 * MejorK[i][j] = k indica que la multiplicación óptima de las matrices Mi, ..., Mj es (Mi * ... * Mk) * (M_{k+1} * ... * Mj). 
 */



#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int NO_ASIGNADO = -1;



/**
 * @brief Función que calcula el número mínimo de multiplicaciones necesarias para calcular el producto de una secuencia de matrices.
 *      Además, calcula la mejor agrupación de matrices para minimizar el número de multiplicaciones.
 * @param p  Vector que contiene las dimensiones de las matrices. La matriz Mi tiene tamaño p_i x p_{i+1}.
 * @param N  Matriz de Programación Dinámica que almacena el número mínimo de multiplicaciones necesarias para calcular el producto de las matrices Mi, Mi+1, ..., Mj.
 *              N[i][j] = número mínimo de multiplicaciones necesarias para calcular el producto de las matrices Mi, Mi+1, ..., Mj.
 * @param MejorK  Matriz de Programación Dinámica que almacena la mejor agrupación de matrices para minimizar el número de multiplicaciones.
 *             MejorK[i][j] = k indica que la multiplicación óptima de las matrices Mi, ..., Mj es (Mi * ... * Mk) * (M_{k+1} * ... * Mj).
 */
void multiplicacionEncadenada(const vector<int>& p, vector<vector<int>>& N, vector<vector<int>>& MejorK) {
    
    // Caso base: no hay multiplicaciones
    for (int i = 0; i < N[0].size(); i++) {
        N[i][i] = 0;
    }

    // Caso general: calcular el número mínimo de multiplicaciones necesarias para calcular el producto de las matrices Mi, Mi+1, ..., Mj
    // Diff indica la diferencia entre j e i, el número de matrices que estamos multiplicando
    for (int diff=1; diff < N.size(); diff++) {
        for (int i=0; i < N.size()-diff; i++) {
            int j = i + diff;

            // Buscamos el valor de k que minimiza el número de multiplicaciones
            N[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {

                // El número de multiplicaciones necesarias para calcular el producto de las matrices agrupando en k,
                // (Mi * ... * Mk) * (M_{k+1} * ... * Mj),  es:
                // - Número de multiplicaciones necesarias para calcular el producto de las matrices Mi*...*Mk \in R^{p_i x p_{k+1}}: N[i][k]
                // - Número de multiplicaciones necesarias para calcular el producto de las matrices M_{k+1}*...*Mj \in R^{p_{k+1} x p_{j+1}}: N[k+1][j]
                // - Número de multiplicaciones necesarias para multiplicar una matriz de tamaño p_i x p_{k+1} por una matriz de tamaño p_{k+1} x p_{j+1}: p_i*p_{k+1}*p_{j+1}
                int num_agrup_k = N[i][k] + N[k+1][j] + p[i]*p[k+1]*p[j+1];

                // Actualizamos el número mínimo de multiplicaciones necesarias si encontramos un valor menor
                if (num_agrup_k < N[i][j]) {
                    N[i][j] = num_agrup_k;
                    MejorK[i][j] = k;
                }

            } // for k

        } // for j
    } // for i
}



/**
 * @brief Función que formatea un número entero i como un subíndice, es decir, lo devuelve entre llaves si tiene más de un dígito.
 * 
 * @param i  Número entero a formatear
 * @return string  Formato de subíndice de i
 */
string subindice(int i) {
    string res = to_string(i);

    if (res.length() > 1) 
        res = "{" + res + "}";
    
    return "_" + res;
}

/**
 * @brief Función que devuelve la secuencia óptima de multiplicaciones de matrices en forma de string, con paréntesis.
 * 
 * @param MejorK  Matriz de Programación Dinámica que indica la mejor agrupación de matrices para minimizar el número de multiplicaciones
 * @param i  Índice de la primera matriz de la secuencia
 * @param j  Índice de la última matriz de la secuencia
 * @return string  Secuencia óptima de multiplicaciones de matrices
 */
string dibujaParentesisOptimos(const vector<vector<int>>& MejorK, int i, int j) {
    const char letra = 'A';

    string resultado = "";

    // Caso base: solo hay una matriz
    if (i == j) {
        resultado += letra + subindice(i);
    } else {
        // Caso general: hay más de una matriz

        int k = MejorK[i][j];
        bool primera_sola = (i == k);
        bool ultima_sola = (k+1 == j);

        if (!primera_sola) resultado += "(";
        resultado += dibujaParentesisOptimos(MejorK, i, MejorK[i][j]);
        if (!primera_sola) resultado += ")";
        resultado += "*";
        if (!ultima_sola) resultado += "(";
        resultado += dibujaParentesisOptimos(MejorK, MejorK[i][j]+1, j);
        if (!ultima_sola) resultado += ")";
    }

    return resultado;
}



int main() {
    // Dimensiones de las matrices
    vector<int> p = {10, 20, 50, 1, 100};

    // Número de matrices
    int n = p.size() - 1;

    // Inicializar las matrices de Programación Dinámica
    vector<vector<int>> N(n, vector<int>(n, NO_ASIGNADO));
    vector<vector<int>> MejorK(n, vector<int>(n, NO_ASIGNADO));

    // Calcular el número mínimo de multiplicaciones necesarias
    multiplicacionEncadenada(p, N, MejorK);

    // Mostrar el número mínimo de multiplicaciones necesarias
    cout << "Numero minimo de multiplicaciones necesarias: " << N[0][n-1] << endl;

    // Mostrar la secuencia óptima de multiplicaciones
    cout << "Secuencia optima de multiplicaciones: " << dibujaParentesisOptimos(MejorK, 0, n-1) << endl;

    return 0;
}