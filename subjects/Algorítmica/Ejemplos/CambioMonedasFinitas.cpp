/**
 * @file CambioMonedas.cpp
 * @author Arturo Olivares Martos
 * @brief Programa para resolver el problema del cambio de monedas mediante Programación Dinámica.
 *          En este caso, se supone que hay un número finito de monedas de cada valor.
 * 
 * Dado un conjunto de monedas de valor d_0, d_1, ..., d_{n-1}, y una cantidad N, determinar el número mínimo de monedas
 * necesarias para devolver el cambio de N.
 * 
 * N denota la cantidad a devolver
 * v[i] denota el valor de la moneda i, con v[i] < v[j] si i < j
 * 
 * NO Suponemos que hay infinitas monedas de cada valor !!!!!!!!!!!!!!!!!!
 * c[i] denota el número de monedas de valor v[i] que se pueden emplear
 * 
 * T[i][j] denota el número mínimo de monedas necesarias para devolver el cambio de j con monedas de valor v[0], v[1], ..., v[i]
 * El objetivo es calcular T[n-1][N]
 * 
 * Las monedas empleadas se obtendrán en el vector solucion.
 * Monedas[i]=k indica que se han empleado k monedas de valor v[i]
 */



#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>

using namespace std;

const int NO_ASIGNADO = -1;
const int IMPOSIBLE = -2;


/**
 * @brief Imprime la tabla final con los resultados
 * 
 * @param T  Tabla con los resultados
 * @param v  Vector con los valores de las monedas
 */
void imprimirTablaFinal(const vector<vector<pair<int, int>>> &T, const vector<int> &v){
    
    int anchura = to_string(T[0].size()).length() + 1;

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
        cout << setw(anchura) << (to_string(v[i]) + " |");
        for (int j = 0; j < T[0].size(); j++){
            if (T[i][j].first == IMPOSIBLE){
                cout << setw(anchura) << "X";
            } else {
                cout << setw(anchura) << T[i][j].first;
            }
        }
        cout << endl;
    }
    cout << endl;
}


/**
 * @brief Inicializa la tabla con los valores base
 * 
 * @param v  Vector con los valores de las monedas
 * @param N  Cantidad a devolver
 * @return vector<vector<pair<int, int>>>  Tabla con los resultados.
 *              T[i][j].first = num. de monedas necesarias para devolver j con monedas de valor v[0], v[1], ..., v[i]
 *              T[i][j].second = num. de monedas de valor v[i] que quedan disponibles
 */
vector<vector<pair<int, int>>> inicializarTabla(const vector<int> &v, const vector<int> &c, int N){
    
    vector<vector<pair<int, int>>> T(v.size(), vector<pair<int, int>>(N+1, {NO_ASIGNADO, NO_ASIGNADO}));

    // Caso base: no necesitamos monedas para devolver 0
    for (int i = 0; i < v.size(); i++){
        T[i][0] = {0, c[i]};
    }

    // Rellenamos la primera fila (usaremos solo monedas de tipo v[0])
    for (int j = 1; j <= N; j++){
        if (j < v[0]){  // No es posible devolver algo menor que v[0]
            T[0][j].first = IMPOSIBLE;
        }
        else if (T[0][j-v[0]].first != IMPOSIBLE && T[0][j-v[0]].second > 0){   // Si quedan monedas, se usa una
            T[0][j].first = 1 + T[0][j-v[0]].first;
            T[0][j].second = T[0][j-v[0]].second - 1;
        }
        else {          // No es posible porque lo que quedaría no se puede devolver
            T[0][j].first = IMPOSIBLE;
        }
    }

    // Caso recursivo
    // T[i][j] = min(T[i-1][j], 1 + T[i][j-v[i]])   // Hablamos de .first
    for (int i = 1; i < v.size(); i++){
        for (int j = 1; j <= N; j++){

            T[i][j] = T[i-1][j];

            if (T[i-1][j].first != IMPOSIBLE){
                if (j >= v[i] && T[i][j-v[i]].first != IMPOSIBLE){
                    if ( (1 + T[i][j-v[i]].first < T[i-1][j].first) && (T[i][j-v[i]].second > 0) ){
                        T[i][j].first = 1 + T[i][j-v[i]].first;
                        T[i][j].second = T[i][j-v[i]].second - 1;
                    }
                }
            }
            else{
                if (j >= v[i] && T[i][j-v[i]].first != IMPOSIBLE){
                    if (T[i][j-v[i]].second > 0){
                        T[i][j].first = 1 + T[i][j-v[i]].first;
                        T[i][j].second = T[i][j-v[i]].second - 1;
                    }
                }
            }

        }
    }

    return T;
}


/**
 * @brief Obtiene las monedas empleadas para devolver el cambio de N
 * 
 * @param T  Tabla con los resultados
 * @param v  Vector con los valores de las monedas
 * @param N  Cantidad a devolver
 * @return vector<int>  Vector con la cantidad de monedas empleadas de cada tipo
 */
vector<int> obtenerMonedas(const vector<vector<pair<int, int>>> &T, const vector<int> &v, int N){
    vector<int> monedas(v.size(), 0);

    int i = v.size()-1;
    int j = N;

    if (T[i][j].first == IMPOSIBLE){  // No es posible devolver N
        return monedas;
    }

    while (j > 0){
        
        if ( (i > 0) && (T[i-1][j].first != IMPOSIBLE) && (T[i][j].first == T[i-1][j].first) ){    // No se usa la moneda v[i]
            i--;
        }
        else if ( (j >= v[i]) && (T[i][j-v[i]].first != IMPOSIBLE) && (T[i][j].first == 1 + T[i][j-v[i]].first) ){    // Se usa la moneda v[i]
            monedas[i]++;
            j -= v[i];
        }
        else{
            cout << "Error en la tabla." << endl;
            return monedas;
        }
    }

    return monedas;
}


int main(){
    vector<int> v = {1,4,6};
    vector<int> c = {500, 10, 5};
    int N = 36;

    vector<vector<pair<int, int>>> T = inicializarTabla(v, c, N);
    imprimirTablaFinal(T, v);
    vector<int> monedas = obtenerMonedas(T, v, N);

    if (T[v.size()-1][N].first == IMPOSIBLE){
        cout << "No es posible devolver " << N << " con las monedas dadas." << endl;
        return -1;
    }

    cout << "Num. de monedas empleadas para devolver " << N << ": " << T[v.size()-1][N].first << endl;
    cout << "\tValor\tCant. init\tCantidad Empleada" << endl;
    for (int i = 0; i < monedas.size(); i++){
        cout << "\t" << v[i] << "\t" << c[i] << "\t\t" << monedas[i] << endl;
    }

    return 0;
}