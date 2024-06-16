/**
 * @file Ejercicio4.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 4 del Examen 2 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex02)
 * 
 * *Enunciado:*
 * Disponemos de $n$ tipos de monedas, las monedas de tipo $i$ tienen un valor de $v[i]$.
 *      La cantidad de monedas disponibles de tipo $i$ es igual a $c[i]$.
 * 
 * Se quiere devolver una cantidad exacta $M$ utilizando el menor número posible de monedas.
 * 
 * Diseñad un algoritmo de programación dinámica que determine el número óptimo de monedas a usar.
 * 
 * Aplicadlo para resolver el siguiente caso del problema, con $n = 3$, construyendo la tabla correspondiente:
 *      $$ v = [2, 4, 6] \qquad c = [3,1,2] \qquad M = 8 $$
 * _______________________________________________________________________________________________________________
 * 
 * Es conocida por el lector la técnica de programación dinámica para resolver el problema del cambio de monedas usando infinitas monedas de cada tipo.
 *      No obstante, esta versión no se puede resolver adaptando dicha técnica directamente, ya que el número de monedas de cada tipo es limitado.
 * 
 * Por tanto, resolveremos este problema adaptándolo al problema de la mochila 01, donde cada objeto es una moneda. Somos conscientes de que esto es muy ineficiente,
 *      especialmente si el número de monedas es muy grande, pero es la única forma de resolverlo con los conocimientos adquiridos en la asignatura.
 * 
 * Para adaptarlo a la mochila 01, consideramos dos monedas del mismo tipo como dos objetos diferentes, con el mismo valor.
 *      De esta forma, si tenemos $c[i]$ monedas de tipo $i$, tendremos $c[i]$ objetos de tipo $i$ con el mismo valor.
 */



#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>

using namespace std;

// Valor que representa que no se puede devolver la cantidad exacta con las monedas consideradas
const int IMPOSIBLE = -1;



/**
 * @brief Obtiene la tabla de programación dinámica necesaria para resolver el problema, conocida como DP
 * 
 * @param DP Tabla de programación dinámica
 * @param monedas_unicas Vector con los índices de las monedas únicas
 * @param M Cantidad a devolver
 * @param v Vector con los valores de las monedas
 * 
 * @post DP[i][j] = Cantidad máxima devuelta con las monedas 0, 1, ..., i y una cantidad a devolver de j
 *          Recordemos que la moneda i es del tipo monedas_unicas[i], que no es necesariamente i
 */
void obtenerTabla(vector<vector<int>> &DP, const vector<int> &monedas_unicas, int M, const vector<int> &v){
    
    DP.clear();
    DP.resize(monedas_unicas.size(), vector<int>(M+1, 0));

    // Caso base: Si la cantidad a devolver es 0, no se necesitan monedas
    for (int i = 0; i < DP.size(); ++i)
        DP[i][0] = 0;

    // Caso base: Si solo tenemos la moneda 0, 
    for (int j = 1; j <= M; j++){
        if (v[monedas_unicas[0]] <= j)
            DP[0][j] = v[monedas_unicas[0]];
        else
            DP[0][j] = 0;
    }

    // Caso recursivo
    for (int i = 1; i < DP.size(); i++){
        for (int j = 1; j <= M; j++){
            if (v[monedas_unicas[i]] <= j){
                DP[i][j] = max(DP[i-1][j], DP[i-1][j-v[monedas_unicas[i]]] + v[monedas_unicas[i]]);
            }else{
                DP[i][j] = DP[i-1][j];
            }
        }
    }
}


vector<int> obtenerMonedas(const vector<vector<int>> &DP, const vector<int> &monedas_unicas, int M, const vector<int> &v){
    vector<int> monedas(v.size(), 0);

    int i = DP.size()-1;
    int j = M;

    while (i > 0 && j > 0){
        if (DP[i][j] == v[monedas_unicas[i]] + DP[i-1][j-v[monedas_unicas[i]]]){
            monedas[monedas_unicas[i]]++;
            j -= v[monedas_unicas[i]];
        }else{
            i--;
        }
    
    }

    if (j > 0 && DP[i][j] == v[monedas_unicas[i]]){
        monedas[monedas_unicas[i]]++;
    }

    return monedas;
}

/**
 * @brief Imprime la tabla final con los resultados
 * 
 * @param T  Tabla con los resultados
 * @param v  Vector con los valores de los elementos
 */
void imprimirTabla(const vector<vector<int>> &T){

    int anchura = 3;

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

    for (int i = 0; i < T.size(); i++){
        cout << setw(anchura) << (to_string(i) + "|");
        for (int j = 0; j < T[0].size(); j++){
            cout << setw(anchura) << T[i][j];
        }
        cout << endl;
    }
    cout << endl;
}



int main(int argc, char const *argv[])
{
    vector<int> v = {1,4,6};
    vector<int> c = {500,10,5};
    int M = 36;


    vector<int> monedas_unicas;
    for (int i = 0; i < v.size(); i++)
        monedas_unicas.insert(monedas_unicas.end(), c[i], i);
    


    vector<vector<int>> DP;
    obtenerTabla(DP, monedas_unicas, M, v);
    imprimirTabla(DP);

    vector<int> monedas = obtenerMonedas(DP, monedas_unicas, M, v);
    cout << "Cambio a devolver: " << DP[DP.size()-1][M] << endl;
    cout << "Monedas a devolver: ";
    for (int i = 0; i < monedas.size(); i++){
        cout << monedas[i] << " monedas de valor " << v[i] << ", ";
    }

    return 0;
}