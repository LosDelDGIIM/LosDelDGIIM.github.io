/**
 * @file Mochila_01_BB.cpp
 * @author Arturo Olivares Martos
 * @brief  Resolución del problema de la mochila 0-1 mediante Branch&Bound
 * 
 * Dado un conjunto de n elementos, cada uno con un peso w_i y un valor v_i, se desea determinar cuál es la combinación de elementos que maximiza
 * el valor total sin superar un peso máximo P.
 * 
 * W[i] denota el peso del elemento i
 * V[i] denota el valor del elemento i
 * P denota el peso máximo que puede soportar la mochila
 * 
 * T[i]=1 si el elemento i está en la mochila, T[i]=0 en caso contrario
 *  
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int INVALIDO = -1;
const int INCLUIDO = 1;
const int NO_INCLUIDO = 0;


struct Nodo{
    vector<int> T;
    int valor_acumulado;
    int peso_acumulado;

    bool operator<(const Nodo& n) const{
        return valor_acumulado < n.valor_acumulado;
    }
};


/**
 * @brief Función que calcula la cota superior de un nodo.
 * 
 * Se calcula sumando el valor acumulado del nodo actual con el valor de los elementos que quedan por considerar.
 * 
 * @param V  Vector de valores de los elementos
 * @param W  Vector de pesos de los elementos
 * @param P  Peso máximo que puede soportar la mochila
 * @param e_nodo  Nodo actual cuya cota superior queremos calcular
 * @return int  Cota superior del nodo
 */
int cotaSuperior(const vector<int>& V, const vector<int>& W, int P, Nodo& e_nodo){
    int valor = e_nodo.valor_acumulado;
    int elemento = find(e_nodo.T.begin(), e_nodo.T.end(), INVALIDO) - e_nodo.T.begin();

    for (int i = elemento; i < V.size(); ++i){
        valor += V[i];
    }

    return valor;
}



/**
 * @brief Función que resuelve el problema de la mochila 0-1 mediante Branch&Bound
 * 
 * @param W  Vector de pesos de los elementos
 * @param V  Vector de valores de los elementos
 * @param P  Peso máximo que puede soportar la mochila
 * @return Nodo  Nodo que contiene la solución óptima
 */
Nodo Mochila_01(const vector<int>& W, const vector<int>& V, int P){
    
    // Creamos nodo raíz
    Nodo e_nodo;
    e_nodo.T = vector<int>(W.size(), INVALIDO);
    e_nodo.valor_acumulado = 0;
    e_nodo.peso_acumulado = 0;

    priority_queue<Nodo> Q;
    Q.push(e_nodo);

    // Solución inicial, coger todo por orden hasta que no quepa
    Nodo sol=e_nodo;
    int i=0;
    while (i<W.size() && sol.peso_acumulado+W[i]<=P){
        sol.T[i]=INCLUIDO;
        sol.valor_acumulado+=V[i];
        sol.peso_acumulado+=W[i];
        i++;
    }

    while(!Q.empty()){
        Nodo e_nodo = Q.top();
        Q.pop();

        // Obtenemos el elemento que estamos considerando si meter o no en la mochila
        int elemento = find(e_nodo.T.begin(), e_nodo.T.end(), INVALIDO) - e_nodo.T.begin();

        // Si hemos considerado todos los elementos, hemos terminado
        if(elemento == V.size()){
            if (e_nodo.valor_acumulado > sol.valor_acumulado)
                sol = e_nodo;
            continue;
        }

        // Consideramos no incluirlo
        e_nodo.T[elemento] = NO_INCLUIDO;
        if (cotaSuperior(V, W, P, e_nodo) > sol.valor_acumulado)
            Q.push(e_nodo);

        // Consideramos incluirlo
        if(e_nodo.peso_acumulado + W[elemento] <= P){
            e_nodo.T[elemento] = INCLUIDO;

            e_nodo.valor_acumulado += V[elemento];
            e_nodo.peso_acumulado += W[elemento];
            if (cotaSuperior(V, W, P, e_nodo) > sol.valor_acumulado)
                Q.push(e_nodo);
            e_nodo.valor_acumulado -= V[elemento];
            e_nodo.peso_acumulado -= W[elemento];
        }

        // Deshacemos los cambios realizados
        e_nodo.T[elemento] = INVALIDO;
    }

    return sol;
}



int main(){
    
        vector<int> W = {3,2,4,5,6,3,5};
        vector<int> V = {30,20,36,40,48,6,2};
        int P = 11;
    
        Nodo sol = Mochila_01(W, V, P);
    
        cout << "Valor maximo: " << sol.valor_acumulado << endl;
        cout << "Elementos incluidos: ";
        for(int i = 0; i < sol.T.size(); ++i){
            if(sol.T[i] == INCLUIDO)
                cout << i << " ";
        }
        cout << endl;
    
        return 0;
}