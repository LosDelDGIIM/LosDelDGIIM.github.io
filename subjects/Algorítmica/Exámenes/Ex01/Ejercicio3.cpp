/**
 * @file Ejercicio3.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 3 del Examen 1 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex01)
 * 
 * *Enunciado:*
 * Sea $T$ un conjunto de $n$ programas, cada uno con un tamaño $t_1, t_2, \ldots, t_n$ (los números $t_i$ son enteros positivos),
 *      y disponemos de un dispositivo de almacenamiento de capacidad máxima $C$ (también un número entero positivo).
 * 
 * Se pretende encontrar la manera de decidir qué programas (completos) almacenar en el dispositivo de manera que se maximice el espacio ocupado del dispositivo.
 * 
 * Diseñad un algoritmo de programación dinámica para resolver este problema.
 * 
 * Aplicadlo para el caso en que $n = 4$, el vector de tamaños es $t(1) = 3$, $t(2) = 7$, $t(3) = 11$ y $t(4) = 8$, con capacidad del dispositivo $C = 12$.
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 * En este caso, tenemos que se trata del problema de la mochila 0-1, donde cada elemento es un programa con un tamaño y un valor asociado.
 * Este problema sabemos que se puede resolver mediante programación dinámica o algoritmos de exploración de grafos, aunque en este caso se pide un algoritmo de programación dinámica.
 * 
 * Aunque en el enunciado los programas se numeren desde 1 hasta n, en el código se numerarán desde 0 hasta n-1,
 * de forma que el programa i tendrá un tamaño t[i].
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

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
        cout << setw(anchura) << (to_string(i) + "|");
        for (int j = 0; j < T[0].size(); j++){
            cout << setw(anchura) << T[i][j];
        }
        cout << endl;
    }
    cout << endl;
}


/**
 * @brief Obtiene la tabla con los resultados de la programación dinámica, conocida como DP
 * 
 * @param DP Tabla con los resultados
 * @param t Vector con los tamaños de los programas
 * @param C Capacidad máxima del dispositivo
 * 
 * @post DP[i][j] = Máximo espacio ocupado con los programas 0, 1, ..., i y capacidad j
 */
void obtenerTabla(vector<vector<int>> &DP, const vector<int> &t, const int C){

    DP.clear();
    DP.resize(t.size(), vector<int>(C + 1));
    
    // Rellenamos columna 0. Si la capacidad es 0, no podemos almacenar nada
    for (int i = 0; i < t.size(); i++){
        DP[i][0] = 0;
    }

    // Rellenamos fila 0.
    // - Si el programa 0 cabe en la capacidad, lo almacenamos.
    // - Si no cabe, no almacenamos nada
    for (int j = 0; j <= C; j++){
        if (t[0] <= j) DP[0][j] = t[0];
        else DP[0][j] = 0;
    }

    // Caso recursivo. Fijados i,j, i,j>=1, tenemos dos opciones:
    // - Si el programa i NO cabe en la capacidad j, como no podremos almacenarlo, el máximo espacio ocupado será el mismo que si no lo consideramos.
    //      DP[i][j] = DP[i-1][j]
    //
    // - Si el programa i cabe en la capacidad j, tenemos dos opciones:
    //      - No almacenarlo. En ese caso, el máximo espacio ocupado será el mismo que si no lo consideramos.
    //                          DP[i][j] = DP[i-1][j]
    //      - Almacenarlo. En ese caso, el máximo espacio ocupado será su tamaño más el máximo espacio ocupado con los programas 0, 1, ..., i-1 y capacidad j-t[i].
    //                          DP[i][j] = t[i] + DP[i-1][j-t[i]]
    //      Como queremos maximizar el espacio ocupado, nos quedamos con la opción que más espacio ocupe.
    //      DP[i][j] = max(DP[i-1][j], t[i] + DP[i-1][j-t[i]])
    for (int i = 1; i < t.size(); i++){
        for (int j = 1; j <= C; j++){
            if (t[i] <= j) // Si cabe el programa i en la capacidad j
                DP[i][j] = max(DP[i-1][j], t[i] + DP[i-1][j-t[i]]);
            else
                DP[i][j] = DP[i-1][j];
        }
    }



    /* EJEMPLO PEDIDO EN EL ENUNCIADO

    Damos un ejemplo para entender cómo se rellena la tabla DP. Sea t = {3, 7, 11, 8} y C = 12. Con los dos bucles for iniciales, DP quedaría de la siguiente forma:
            0   1   2   3   4   5   6   7   8   9   10  11  12
    _____________________________________________________________
    0   |   0   0   0   3   3   3   3   3   3   3   3   3   3
    1   |   0   X   X   X   X   X   X   X   X   X   X   X   X
    2   |   0   X   X   X   X   X   X   X   X   X   X   X   X
    3   |   0   X   X   X   X   X   X   X   X   X   X   X   X

    Donde X indica que no se ha calculado el valor. Posteriormente, se rellena la tabla con los valores correspondientes.
    Para i=1, el programa 1 tiene tamaño 7.
        - Si j=1,2,3,4,5,6, el programa 1 no cabe. DP[1][j] = DP[0][j].
            - Si j=1,2,     DP[1][1] = DP[0][1] = 0
            - Si j=3,4,5,6, DP[1][j] = DP[0][j] = 3

        - Si j=7,8,9,10,11,12, el programa 1 cabe. DP[1][j] = max(DP[0][j], t[1] + DP[0][j-t[1]]) = max(DP[0][j], 7 + DP[0][j-7])
            - Si j=7,8,9.   DP[0][j] = 3,   DP[0][j-7] = 0.   DP[1][j] = max(3, 7 + 0) = 7
            - Si j=10,11,12 DP[0][j] = 3,   DP[0][j-7] = 3.   DP[1][j] = max(3, 7 + 3) = 10
    
    La tabla DP quedaría de la siguiente forma:
            0   1   2   3   4   5   6   7   8   9   10  11  12
    _____________________________________________________________
    0   |   0   0   0   3   3   3   3   3   3   3   3   3   3
    1   |   0   0   0   3   3   3   3   7   7   7   10  10  10
    2   |   0   X   X   X   X   X   X   X   X   X   X   X   X
    3   |   0   X   X   X   X   X   X   X   X   X   X   X   X

    Para i=2, el programa 2 tiene tamaño 11.
        - Si j=1,2,3,4,5,6,7,8,9,10, el programa 2 no cabe. DP[2][j] = DP[1][j].
            - Si j=0,1,2,   DP[2][j] = DP[1][j] = 0
            - Si j=3,4,5,6, DP[2][j] = DP[1][j] = 3
            - Si j=7,8,9,   DP[2][j] = DP[1][j] = 7
            - Si j=10,      DP[2][j] = DP[1][j] = 10

        - Si j=11,12, el programa 2 cabe. DP[2][j] = max(DP[1][j], t[2] + DP[1][j-t[2]]) = max(DP[1][j], 11 + DP[1][j-11])
            - Si j=11, DP[1][j] = 10,   DP[1][j-11] = 0.   DP[2][j] = max(10, 11 + 0) = 11
            - Si j=12, DP[1][j] = 10,   DP[1][j-11] = 0.   DP[2][j] = max(10, 11 + 0) = 11
    
    La tabla DP quedaría de la siguiente forma:
            0   1   2   3   4   5   6   7   8   9   10  11  12
    _____________________________________________________________
    0   |   0   0   0   3   3   3   3   3   3   3   3   3   3
    1   |   0   0   0   3   3   3   3   7   7   7   10  10  10
    2   |   0   0   0   3   3   3   3   7   7   7   10  11  11
    3   |   X   X   X   X   X   X   X   X   X   X   X   X   X

    Para i=3, el programa 3 tiene tamaño 8.
        - Si j=1,2,3,4,5,6,7, el programa 3 no cabe. DP[3][j] = DP[2][j].
            - Si j=0,1,2,   DP[3][j] = DP[2][j] = 0
            - Si j=3,4,5,6, DP[3][j] = DP[2][j] = 3
            - Si j=7,       DP[3][j] = DP[2][j] = 7
        
        - Si j=8,9,10,11,12, el programa 3 cabe. DP[3][j] = max(DP[2][j], t[3] + DP[2][j-t[3]]) = max(DP[2][j], 8 + DP[2][j-8])
            - Si j=8,9,     DP[2][j] = 7,   DP[2][j-8] = 0.     DP[3][j] = max(7, 8 + 0) = 8
            - Si j=10       DP[2][j] = 10,  DP[2][j-8] = 0.     DP[3][j] = max(10, 8 + 0) = 10
            - Si j=11,12    DP[2][j] = 11,  DP[2][j-8] = 3.     DP[3][j] = max(11, 8 + 3) = 11

    La tabla DP finalmente quedaría de la siguiente forma:
            0   1   2   3   4   5   6   7   8   9   10  11  12
    _____________________________________________________________
    0   |   0   0   0   3   3   3   3   3   3   3   3   3   3
    1   |   0   0   0   3   3   3   3   7   7   7   10  10  10
    2   |   0   0   0   3   3   3   3   7   7   7   10  11  11
    3   |   0   0   0   3   3   3   3   7   8   8   10  11  11

    */
}

/**
 * @brief Obtiene los programas que se han almacenado en el dispositivo
 * 
 * @param DP Tabla con los resultados de la programación dinámica
 * @param t Vector con los tamaños de los programas
 * @return vector<bool>  Vector de booleanos que indica si cada programa se ha almacenado o no.
 */
vector<bool> obtenerProgramas(const vector<vector<int>> &DP, const vector<int> &t){
    vector<bool> programas(t.size(), false);

    // Partimos del resultado final, DP[t.size()-1][DP[0].size()-1], y vamos hacia atrás estudiando qué decisiones hemos tomado
    // Fijado i>=1, caben dos opciones:
    // - Si DP[i][j] != DP[i-1][j], hemos almacenado el programa i. Ponemos programas[i] = true y restamos t[i] a j. Estudiamos el programa i-1.
    // - Si DP[i][j] == DP[i-1][j], no hemos almacenado el programa i. Estudiamos el programa i-1.

    int i = t.size()-1, j = DP[0].size()-1;
    while (i >=1 && DP[i][j] >= 1){
        // La condición DP[i][j] >= 1 es porque si con los i primeros programas no se ha almacenado nada,
        //      no se almacenará nada con menos programas o menos capacidad
        if (DP[i][j] != DP[i-1][j]){
            programas[i] = true;
            j -= t[i];
        }
        i--;
    }

    // El programa 0 se estudia por separado. Si sigue habiendo capacidad, se almacena.
    if (t[0] <= j) programas[0] = true;

    return programas;

    /* EJEMPLO PEDIDO EN EL ENUNCIADO

    Damos un ejemplo para entender cómo se obtienen los programas almacenados. Sea t = {3, 7, 11, 8} y C = 12.
    La tabla DP obtenida en ese caro sería:
            0   1   2   3   4   5   6   7   8   9   10  11  12
    _____________________________________________________________
    0   |   0   0   0   3   3   3   3   3   3   3   3   3   3
    1   |   0   0   0   3   3   3   3   7   7   7   10  10  10
    2   |   0   0   0   3   3   3   3   7   7   7   10  11  11
    3   |   0   0   0   3   3   3   3   7   8   8   10  11  11

    Partimos de i=3, j=12.
    - Como DP[3][12] == DP[2][12], no hemos almacenado el programa 3. Estudiamos el programa 2 (i=2).
                Es cierto que tal y como se rellena la tabla DP, también se podría haber almacenado, ya que DP[3][12]=t[3] + DP[2][12-11]=11.
                    Por tanto, se puede llegar a la máxima capacidad almacenando el programa 3 y NO almaceándolo.
                    Tal y como está programada la función, obtenerProgramas, se ha escogido NO almacenarlo.

    - Como DP[2][12] != DP[1][12], sí hemos almacenado el programa 2. Restamos t[2] a j (j=12-11=1). Estudiamos el programa 1 (i=1).
    - Como DP[1][1] == 0 < 1, nos salimos del bucle. No almacenamos los programas 0 y 1.
    */
}




int main(int argc, char const *argv[]){

    vector<int> t = {3, 7, 11, 8};
    int C = 12;

    cout << "Capacidad maxima del dispositivo: " << C << endl;
    cout << "Tamanios de los programas: " << endl;
    for (int i = 0; i < t.size(); i++){
        cout << "- Programa " << i << ": " << t[i] << endl;
    }
    cout << endl << endl;

    vector<vector<int>> DP;
    obtenerTabla(DP, t, C);

    // Para comprobar el ejemplo del enunciado, y desarrollado en la función obtenerTabla, descomentar las siguientes líneas
    // cout << "Tabla final con los resultados de la programacion dinamica:" << endl;
    // imprimirTablaFinal(DP, t);
    // cout << endl;

    vector<bool> programas = obtenerProgramas(DP, t);

    cout << "Maximo espacio ocupado: " << DP[t.size()-1][C] << endl;
    for (int i = 0; i < programas.size(); i++){
        cout << "- Programa " << i << ": " << (programas[i] ? "Almacenado" : "No almacenado") << endl;
    }
    cout << endl;

    return 0;
}


