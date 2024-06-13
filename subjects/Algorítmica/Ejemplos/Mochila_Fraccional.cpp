/**
 * @file Mochila_Fraccional.cpp
 * @brief Resolución del problema de la mochila fraccional mediante Greedy
 * 
 * Dado un conjunto de n elementos, cada uno con un peso w_i y un valor v_i, y una mochila con capacidad P,
 * se desea determinar cuál es la combinación de elementos que maximiza el valor total sin superar la capacidad de la mochila.
 * De cada elemento se puede coger una fracción de su peso, denotada por x_i, con 0 <= x_i <= 1.
 * 
 * 
 * P denota el peso máximo que puede soportar la mochila
 * 
 * 
 * - Conjunto de candidatos: Todos los elementos
 * - Conjunto de seleccionados: Elementos seleccionados, inicialmente vacío
 * - Función solución: Conjunto de candidatos vacío
 * - Función de factibilidad: La suma de la parte proporcional de los pesos de los elementos seleccionados no supera P
 * - Función de selección: Elemento con mayor relación valor/peso
 * - Función objetivo: Valor total de la parte proporcional de los elementos seleccionados
 */



#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Estructura para representar un elemento
struct Elemento{
    double valor;
    double peso;
    double porcentaje=0;
    
    double RelacionValorPeso() const{
        return valor / peso;
    }

    // Un elemento es menor que otro si su relación valor/peso es mayor (es decir, si es más rentable)
    bool operator<(const Elemento &e) const{
        return RelacionValorPeso() > e.RelacionValorPeso();
    }
};


/**
 * @brief Calcula el valor total de los elementos de la mochila
 *  
 * @param elementos  Vector con los elementos
 * @return double  Valor total de los elementos
 */
double ValorMochila(const vector<Elemento> &elementos){
    double valor_total = 0;
    for (const Elemento &e : elementos){
        valor_total += e.valor * e.porcentaje;
    }
    return valor_total;
}


/**
 * @brief Imprime los elementos de la mochila
 * 
 * @param elementos  Vector con los elementos
 */
void imprimirMochila(const vector<Elemento> &elementos){
    cout << "Elemento\tPeso\tValor\tPorcentaje" << endl;
    for (int i = 0; i < elementos.size(); i++){
        cout << i << "\t\t" << elementos[i].peso << "\t" << elementos[i].valor << "\t" << elementos[i].porcentaje << endl;
    }
}


/**
 * @brief Resuelve el problema de la mochila fraccional mediante Greedy
 * 
 * @param elementos  Vector con los elementos
 * @param P  Peso máximo que puede soportar la mochila
 */
void MochilaFraccional(vector<Elemento> &elementos, double P){

    double peso_actual = 0;
    
    // Ordenamos los elementos por la relación valor/peso
    sort(elementos.begin(), elementos.end());

    for (int i = 0; i < elementos.size() && peso_actual < P; i++){
        if (peso_actual + elementos[i].peso <= P){  // Si cabe el elemento entero
            elementos[i].porcentaje = 1;
            peso_actual += elementos[i].peso;
        }
        else{       // Si no cabe el elemento entero, cogemos una fracción
            elementos[i].porcentaje = (P - peso_actual) / elementos[i].peso;
            peso_actual = P;
        }
    }
}


int main(){
    // {valor, peso}
    vector<Elemento> elementos = {{20,10}, {30,20}, {65,30}, {40,40}, {60,50}};
    double P = 100;

    MochilaFraccional(elementos, P);

    cout << "Valor total de la mochila: " << ValorMochila(elementos) << endl;
    imprimirMochila(elementos);

    return 0;
}