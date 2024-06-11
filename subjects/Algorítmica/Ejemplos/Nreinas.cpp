/**
 * @file Nreinas.cpp
 * @author Arturo Olivares Martos
 * 
 * @brief Programa para resolver el problema de las N-Reinas
 * 
 * El problema de las N-Reinas consiste en colocar N reinas en un tablero de ajedrez de NxN de tal forma que ninguna reina pueda atacar a otra.
 * Lo resolveremos mediante la técnica de backtracking. 
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int COL_VACIA = -1;      // Valor que indica que una columna está vacía
int cont_soluciones = 0;            // Contador de soluciones


/**
 * @brief Método que imprime el tablero con las reinas
 * 
 * @param sol Vector con las soluciones
 */
void imprimirTablero(const vector<int> &sol){
    for (int i = 0; i < sol.size(); i++){
        for (int j = 0; j < sol.size(); j++){
            if (sol[j] == i){
                cout << "R ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}



/**
 * @brief Método que comprueba si es factible colocar una reina en la fila fila y columna col
 * 
 * @param sol  Vector con las soluciones parciales
 * @param fil Fila en la que queremos colocar la reina
 * @param col Columna en la que queremos colocar la reina
 * @return true  Si es factible colocar la reina en la fila fila y columna col
 * @return false  Si no es factible colocar la reina en la fila fila y columna col
 */
bool factible (vector<int> &sol, int fil, int col){

    
    bool factible = 0<= fil && fil < sol.size() && 0 <= col && col < sol.size();    // Comprobamos que la fila y la columna estén dentro del tablero

    if (factible){
        factible = sol[col] == COL_VACIA;               // Comprobamos que la columna esté vacía

        if (factible){
            auto it = find(sol.begin(), sol.end(), fil);    // Busca si hay alguna reina en la misma fila
            factible = it == sol.end();                     // Comprobamos que la fila esté vacía
            
            int i = 0;
            while (factible && i < col){             // Comprobamos que no haya ninguna reina en la diagonal
                factible = abs(sol[i] - fil) != abs(i - col);
                i++;
            }
        } // if col vacía
        
    } // if fil y col dentro del tablero

    return factible;
}


/**
 * @brief Método que resuelve el problema de las N-Reinas mediante backtracking
 * 
 * @param sol Vector con las soluciones parciales
 * @param k Columna en la que queremos colocar la reina
 * @return const vector<int> Vector con las soluciones
 */
void NReinas(vector<int> &sol, int k){

    // Sol[k] representa la fila de la reina de la columna k

    if (k == sol.size()){   // Hemos colocado todas las reinas
        cout << "Solucion " << ++cont_soluciones << endl;
        imprimirTablero(sol);
        return;
    }
    
    // Probados a colocar a la reina en la fila i
    for (int i = 0; i < sol.size(); ++i){
        
        if (factible(sol, i, k)){
            
            sol[k] = i;             // Colocamos la reina en la fila i y columna k

            NReinas(sol, k+1);      // Pasamos a la siguiente reina
            sol[k] = COL_VACIA;     // Deshacemos la solución    

        } // if factible

    } // for reina en la fila i
}




int main(int argc, char const *argv[]){

    // argv[1] Número de reinas
    if (argc != 2){
        cout << "Error en los argumentos. Uso: " << argv[0] << " N" << endl;
        return -1;
    }
    int N = atoi(argv[1]);
    

    vector<int> sol(N, COL_VACIA);
    NReinas(sol, 0);

    return 0;
}