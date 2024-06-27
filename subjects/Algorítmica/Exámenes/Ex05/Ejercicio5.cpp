/**
 * @file Ejercicio5.cpp
 * @author José Juan Urrutia Milán
 * @brief Ejericio 5 del Examen 5 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex05)
 * 
 * *Enunciado:*
 * 
 * Un turista neoyorkino quiere recorrer $n$ países europeos $\{p_1, \ldots, p_n\}$ en un orden prefijado (hay que visitarlos en ese orden) y 
 * visitar en cada país $p_i$ una (y sólo una) de entre $m_i$ posibles ciudades prefijadas de ese país. El criterio para determinar su viaje
 * es que el coste total del viaje sea el menor posible (incluyendo el coste de llegar a la ciudad del primer país desde Nueva York y el de
 * volver a Nueva York desde la ciudad del último país). El coste total del viaje es la suma de los costes de viajar de una ciudad a otra. 
 * Formalizad el problema y construid un algoritmo que lo resuelva de la forma más eficiente posible, encontrando la solución óptima.
 * 
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 * La solución está por subirse a la página.
 * Si alguien resuelve el ejercicio nos vendría de utilidad para publicarlo.
 * 
 * El problema se resuelve mediante el algoritmo de Viterbi, el cual resuelve el problema de encontrar el camino mínimo para ir desde una primera etapa
 * hasta la última pasando por una instancia de cada etapa. Nuestras etapas serán los distintos países a visitar, siendo los costes de las aristas del
 * grafo que representa las etapas los costes de viajar entre cada par de ciudades.
 * 
 * Deberemos modificar dicho grafo, ya que en la primera etapa, el coste de ir de la ciudad $m$ (de la primera etapa) a la ciudad $n$ (de la segunda)
 * etapa será igual al coste de ir de $m$ a $n$ más el coste de ir desde Nueva York hasta la ciudad $m$. Repetiremos dicho procedimiento para cada par
 * de ciudades conformado por una ciudad del primer país y una ciudad del segundo país.
 * De forma análoga, también debemos modificar las aristas que unen la penúltima etapa con la última: el coste de ir de la ciudad $m$ (de la penúltima
 * etapa) a la ciudad $n$ (de la última etapa), será el coste de ir de la ciudad $m$ a la $n$ más el coste de ir desde $n$ hasta Nueva York.
 * 
 * El problema se resuelve, por tanto, buscando una buena representación del grafo, realizar las modificaciones anteriormente comentadas y, por último,
 * aplicar a dicho grafo el algoritmo de Viterbi. Tras esto, habremos encontrado el camino que resuelve nuestro problema.
 * 
 */


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){

    return 0;
}
