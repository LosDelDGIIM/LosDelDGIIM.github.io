/**
 * @file Ejercicio4.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 4 del Examen 4 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex04)
 * 
 * *Enunciado:*
 * Tenemos que pagar la cuenta en un restaurante por valor de $M$ euros, y disponemos
 *      de una cantidad ilimitada de monedas de $n$ tipos diferentes,
 *      siendo $c[i]$ el valor de cada moneda de tipo $i$, $i = 1, . . . , n$.
 * 
 * Tenemos prisa y no queremos esperar que, en su caso, nos den la vuelta,
 *      pero como no hemos quedado muy satisfechos queremos pagar o la cantidad exacta $M$ o la mı́nima
 *      cantidad posible mayor que $M$ (o sea dejar ninguna propina o la mı́nima propina posible de acuerdo
 *      a las monedas que tenemos).
 * 
 * Diseñar un algoritmo eficiente que determine la cantidad mı́nima que tenemos que pagar y cómo hacerlo.
 * 
 * Aplicadlo para resolver el siguiente caso: hay $n = 3$ tipos de monedas de valores $5$, $7$ y $13$,
 *      y queremos pagar una cantidad de $M = 11$ unidades.* 
 * 
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 * Se trata de una variación del problema del cambio de monedas, en el que se nos pide pagar una cantidad exacta o la mínima cantidad mayor a una cantidad dada.
 * Resolvemos por tanto el problema mediante programación dinámica.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;


/**
 * @brief Calcula la cantidad mínima a pagar usando las monedas dadas, siendo esta mayor que M
 * 
 * @param monedas Vector con los valores de las monedas
 * @param M Cantidad mínima que queremos pagar
 * @param DP Tabla de programación dinámica
 * 
 * @post DP[i][j] = Cantidad mínima a pagar, superior a j, con las monedas de los tipos 0, 1, ..., i
 */
void obtenerTabla(const vector<int> &monedas, const int &M, vector<vector<int>> &DP){
    DP.clear();
    DP.resize(monedas.size(), vector<int>(M+1));

    // Caso base: Tenemos que pagar lo mínimo posible, pero >= 0 (es decir, 0)
    for (int i = 0; i < monedas.size(); i++)
        DP[i][0] = 0;
    

    // Caso base: Solo consideramos la moneda 0.
    //              La cantidad mínima a pagar es el múltiplo de la moneda 0 más cercano a j (por exceso)
    for (int j = 1; j <= M; j++)
        DP[0][j] = (j % monedas[0] == 0) ? j : j+monedas[0] - j%monedas[0];

    // Caso recursivo
    // Fijado i,j>=1, hay distintas opciones:
    //      - No usar la moneda i: La cantidad mínima a pagar (superior a j) es la misma que la cantidad mínima a pagar (superior a j) con las monedas 0, 1, ..., i-1
    //              DP[i][j] = DP[i-1][j]
    //      - Usar la moneda i: La cantidad mínima a pagar (superior a j) es la cantidad mínima a pagar (superior a j-monedas[i]) con las monedas 0, 1, ..., i sumando el valor de la moneda i
    //              DP[i][j] = DP[i][j-monedas[i]] + monedas[i]
    for (int i = 1; i < monedas.size(); i++){
        for (int j = 1; j <= M; j++){
            DP[i][j] = DP[i-1][j];
            
            // Se puede dar que monedas[i] > j.
            // En ese caso, simplemente con usar una de esas monedas ya se cubre j
            int opt2 = monedas[i];
            if (j >= monedas[i])
                opt2 += DP[i][j-monedas[i]];
            
            if (opt2 >= j)
                DP[i][j] = min(DP[i][j], opt2);
        }
    }
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


vector<int> obtenerMonedas(vector<vector<int>> &DP, const vector<int> &monedas){
    vector<int> solucion(monedas.size(), 0);

    int i = monedas.size()-1;
    int j = DP[0].size()-1;

    while (i > 0 && j > 0){
        if (DP[i][j] != DP[i-1][j]){
            solucion[i]++;
            j -= monedas[i];
        }
        else
            i--;
        
    }

    // Falta por comprobar la moneda 0
    if (j > 0)
        solucion[0] = DP[0][j] / monedas[0];

    return solucion;
}


int main(int argc, char const *argv[]){
    vector<int> monedas = {5, 7, 13};
    int M = 15;

    vector<vector<int>> DP;
    obtenerTabla(monedas, M, DP);
    imprimirTabla(DP);
    vector<int> solucion = obtenerMonedas(DP, monedas);

    cout << "Cantidad mínima a pagar: " << DP[monedas.size()-1][M] << endl;
    cout << "Monedas a usar:" << endl;
    for (int i = 0; i < monedas.size(); i++){
        cout << "- " << solucion[i] << " monedas de " << monedas[i] << endl;
    }

    return 0;
}

