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
#include <climits>

using namespace std;

// Valor que representa que no se puede devolver la cantidad exacta con las monedas consideradas
const int IMPOSIBLE = INT_MAX;
const int SIN_ASIGNAR = -1;


/**
 * @brief Obtiene la tabla de programación dinámica necesaria para resolver el problema, conocida como DP
 * 
 * @param DP Tabla de programación dinámica
 * @param monedas_unicas Vector con los índices de las monedas únicas
 * @param M Cantidad a devolver
 * @param v Vector con los valores de las monedas
 * 
 * @post DP[i][j] = Número de monedas necesarias para devolver EXACTAMENTE j con las monedas de los tipos 0, 1, ..., i.
 *                      Si no se puede devolver exactamente j, DP[i][j] = IMPOSIBLE
 */
void obtenerTabla(vector<vector<int>> &DP, const vector<int> &monedas_unicas, int M, const vector<int> &v){
    
    DP.clear();
    DP.resize(monedas_unicas.size(), vector<int>(M+1, SIN_ASIGNAR));

    // Caso base: Si la cantidad a devolver es 0, no se necesitan monedas
    for (int i = 0; i < DP.size(); ++i)
        DP[i][0] = 0;

    // Caso base: Si solo tenemos la moneda 0, solo se puede devolver si la cantidad coincide con su valor
    //                  Recordemos que esta moneda es única, es como si su cantidad fuese 1
    for (int j = 1; j <= M; j++){
        if (j == v[monedas_unicas[0]])
            DP[0][j] = 1;
        else
            DP[0][j] = IMPOSIBLE;
    }

    // Caso recursivo
    //
    // Fijado i, j>=1, para devolver j con las monedas 0, 1, ..., i, tenemos dos opciones:
    //      - No usar la moneda i:
    //              En este caso, el número de monedas necesarias es el mismo que devolver j con las monedas 0, 1, ..., i-1, por lo que:
    //              DP[i][j] = DP[i-1][j]
    //
    //      - Usar la moneda i (siempre que j >= v[i])
    //              En este caso, el número de monedas necesarias es el mismo que devolver j-v[i] con las monedas 0, 1, ..., i-1, más una moneda (la que estamos considerando)
    //              DP[i][j] = DP[i-1][j-v[i]] + 1
    //
    // Como queremos minimizar el número de monedas, nos quedamos con el mínimo de ambas opciones
    // Nota: Estamos suponiendo que ambas opciones son válidas, es decir, que los valores a los que accedemos de la tabla no son IMPOSIBLE
    //          En el caso de que lo sea, no nos quedamos con el mínimo, sino que nos quedamos con el valor válido (si lo hay)
    //       Este último hecho complicará la legibilidad de implementación, puesto que no queremos considerar los valores IMPOSIBLE
    for (int i = 1; i < DP.size(); i++){
        for (int j = 1; j <= M; j++){
            
            // Suponemos inicialmente que no se puede usar la moneda i
            DP[i][j] = DP[i-1][j];

            // Si j >= v[monedas_unicas[i]], podemos usar la moneda i
            if (j >= v[monedas_unicas[i]]){

                // Si no se puede devolver j-v[monedas_unicas[i]], no podremos usar la moneda i
                if (DP[i-1][j-v[monedas_unicas[i]]] != IMPOSIBLE){
                    DP[i][j] = DP[i-1][j-v[monedas_unicas[i]]] + 1;

                    // Si ambas opciones son válidas, nos quedamos con el mínimo
                    if (DP[i-1][j] != IMPOSIBLE)
                        DP[i][j] = min(DP[i][j], DP[i-1][j]);
                } // Fin if (puedo devolver j-v[monedas_unicas[i]])
                
            } // Fin if (j >= v[monedas_unicas[i]])

        } // for j
    } // for i
}

/**
 * @brief Obtiene las monedas usadas para devolver la cantidad exacta M
 * 
 * @param DP Tabla de programación dinámica
 * @param monedas_unicas Vector con las monedas representadas como objetos únicos 
 * @param M Cantidad a devolver
 * @param v Vector con los valores de los tipos de monedas
 * @return vector<int> Vector con el número de monedas usadas de cada tipo
 * 
 * @pre DP[DP.size()-1][M] != IMPOSIBLE, es decir, se puede devolver la cantidad exacta M con las monedas consideradas
 */
vector<int> obtenerMonedas(const vector<vector<int>> &DP, const vector<int> &monedas_unicas, int M, const vector<int> &v){
    // Inicialmente usamos 0 monedas de cada tipo
    vector<int> monedas_usadas(v.size(), 0);

    int i = DP.size()-1;
    int j = M;

    while (i > 0 && j > 0){

        // Si el valor de la moneda que estamos considerando es mayor que j, no la hemos podido usar
        if (j<v[monedas_unicas[i]])
            i--;
    
        // Si el número de monedas necesarias para devolver j es el mismo que devolver j con las monedas 0, 1, ..., i-1, no hemos usado la moneda i
        else if (DP[i][j] == DP[i-1][j])
            i--;
            
        // Si el número de monedas necesarias para devolver j es el mismo que devolver j-v[monedas_unicas[i]] con las monedas 0, 1, ..., i-1, más una moneda (la que estamos considerando), hemos usado la moneda i
        else if (DP[i][j] == DP[i-1][j-v[monedas_unicas[i]]] +1){
            monedas_usadas[monedas_unicas[i]]++;
            j -= v[monedas_unicas[i]];
        }
        
        else {
            cout << "Error en la obtención de monedas" << endl;
            exit(1);
        }
    
    }

    // Si hemos llegado a la moneda 0, comprobamos si la hemos usado o no
    if (j > 0){
        if (DP[0][j] == 1)
            monedas_usadas[monedas_unicas[0]]++;
        else {
            cout << "Error en la obtención de monedas" << endl;
            exit(1);
        }
    }

    return monedas_usadas;
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
            cout << setw(anchura) << (T[i][j] == IMPOSIBLE ? "X" : to_string(T[i][j]));
        }
        cout << endl;
    }
    cout << endl;
}



int main(int argc, char const *argv[])
{
    vector<int> v = {2,4,6};
    vector<int> c = {3,1,2};
    int M = 8;

    cout << "Monedas disponibles:" << endl;
    for (int i = 0; i < v.size(); i++){
        cout << "- " << c[i] << " monedas de valor " << v[i] << endl;
    }

    // Se introducen las monedas en un vector de monedas únicas, es decir, si hay c[i] monedas de valor v[i], se introducen c[i] veces el índice i
    vector<int> monedas_unicas;
    for (int i = 0; i < v.size(); i++)
        monedas_unicas.insert(monedas_unicas.end(), c[i], i);

    vector<vector<int>> DP;
    obtenerTabla(DP, monedas_unicas, M, v);
    imprimirTabla(DP);

    if (DP[DP.size()-1][M] == IMPOSIBLE){
        cout << "No se puede devolver " << M << " con las monedas disponibles" << endl;
        return 0;
    }

    vector<int> monedas = obtenerMonedas(DP, monedas_unicas, M, v);
    cout << "Cambio a devolver: " << M << endl;
    cout << "Monedas a devolver:"<< endl;
    for (int i = 0; i < monedas.size(); i++){
        cout << "- " << monedas[i] << " monedas de valor " << v[i] << endl;
    }

    return 0;
}