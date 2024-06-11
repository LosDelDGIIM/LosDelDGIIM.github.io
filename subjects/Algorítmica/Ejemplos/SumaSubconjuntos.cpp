/**
 * @file SumaSubconjuntos.cpp
 * @author Arturo Olivares Martos
 * 
 * @brief Programa para resolver el problema de la suma de subconjuntos mediante backtracking
 * 
 * Dados n números enteros positivos (a_1, a_2, ..., a_n), y un número entero positivo M, determinar
 * los subconjuntos de números a_i cuya suma sea M.
 * 
 * Sol[i] = 1 si el número a_i está en el subconjunto, 0 en caso contrario
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int NO_ESTA = 0;          // Valor que indica que un número no está en el subconjunto
const int SI_ESTA = 1;          // Valor que indica que un número está en el subconjunto
const int NO_ASIGNADO = -1;     // Valor que indica que un número no está asignado


struct Nodo{
    vector<int> sol;            // sol[i] = 1 si el número a_i está en el subconjunto, 0 en caso contrario
    int suma;                   // Suma de los elementos que hemos considerado
};


/**
 * @brief Método que imprime la solución
 * 
 * @param a  Vector con los números enteros positivos
 * @param M Número entero positivo al que queremos llegar con la suma
 * @param nodo Nodo actual que estamos considerando
 */
void imprimirSolucion(const vector<int> &a, int M, const Nodo &nodo){
    cout << "- ";
    for (int i = 0; i < a.size()-1; i++){
        if (nodo.sol[i] == SI_ESTA){
            cout << a[i] << " + ";
        }
    }
    cout << a[a.size()-1] << " = " << M << endl << endl;
}


/**
 * @brief Método que resuelve el problema de la suma de subconjuntos mediante backtracking
 * 
 * @param a Vector con los números enteros positivos
 * @param M Número entero positivo al que queremos llegar con la suma
 * @param nodo Nodo actual que estamos considerando
 */
void SumaSubconjuntos(const vector<int> &a, int M, Nodo &nodo){
    // Caso base: hemos considerado todos los elementos, hemos encontrado una solución
    if (find(nodo.sol.begin(), nodo.sol.end(), NO_ASIGNADO) == nodo.sol.end()){
        
        if (nodo.suma == M) imprimirSolucion(a, M, nodo);   // Tan solo se imprime si la suma es M
        return;
    }
    else{
        // Buscamos el primer elemento no asignado
        auto primera_no_asignado = find(nodo.sol.begin(), nodo.sol.end(), NO_ASIGNADO);
        int i = primera_no_asignado - nodo.sol.begin();

        // Consideramos que NO se elige el elemento
        nodo.sol[i] = NO_ESTA;
        SumaSubconjuntos(a, M, nodo);
        //
        
        // Consideramos que SÍ se elige el elemento
        nodo.sol[i] = SI_ESTA;
        if (nodo.suma + a[i] <= M){     // Si es factible
            nodo.suma += a[i];
            SumaSubconjuntos(a, M, nodo);
            nodo.suma -= a[i];
        }
        //

        // Deshacemos la asignación
        nodo.sol[i] = NO_ASIGNADO;
    }
}


int main(){
    vector<int> a = {11,13,24,7};
    int M = 31;

    // Inicializamos el nodo raíz
    Nodo raiz;
    raiz.sol = vector<int>(a.size(), NO_ASIGNADO);
    raiz.suma = 0;

    SumaSubconjuntos(a, M, raiz);

    return 0;
}