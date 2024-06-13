/**
 * @file AsignacionTareas.cpp
 * @author Arturo Olivares Martos
 * 
 * @brief Programa para resolver el problema de la asignación de tareas mediante Branch&Bound
 * 
 * Sean n tareas a repartir entre n personas. Suponiendo que el coste de que la persona i se asigne a la
 * tarea j es C[i][j]. Asignar las tareas a las personas de modo que el coste total sea mínimo.
 * 
 * Sol[i] representa la tarea asignada a la persona i
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

const int NO_ASIGNADO = -1;


struct Nodo{
    vector<int> asig; // asig[i] es la tarea asignada a la persona i
    double coste;

    // Operador para comparar nodos
    bool operator<(const Nodo &n) const{
        return coste < n.coste;
    }
};


/**
 * @brief Cota Inferior para el problema de la asignación de tareas.
 * 
 * Esta es la suma del coste que ya llevamos
 * más el coste de asignar a las personas restantes la tarea con menor coste para ellos.
 * 
 * @param C Matriz de costes
 * @param nodo Nodo actual cuya cota inferior queremos calcular
 * @return double Cota Inferior del nodo
 */
double cotaInferior(const vector<vector<double>> &C, const Nodo &nodo){

    // Inicialmente, se contabiliza el coste actual
    double cota = nodo.coste;

    // Se añade el coste de asignar a las personas restantes la tarea con menor coste
    // Se busca la primera persona sin tarea asignada
    auto primera_no_asignada = find(nodo.asig.begin(), nodo.asig.end(), NO_ASIGNADO);
    for (int i = primera_no_asignada - nodo.asig.begin(); i<C.size(); ++i){
        cota += *(min_element(C[i].begin(), C[i].end()));
    }
    return cota;
}


/**
 * @brief Asigna las tareas a las personas de modo que el coste total sea mínimo.
 * 
 * @param C Matriz de costes
 * @return Nodo con la solución al problema
 */
Nodo asignarTareas(const vector<vector<double>> &C){
    priority_queue<Nodo> Q; // Cola de prioridad para almacenar los nodos vivos

    // Solución inicial, en este caso asignar la tarea i a la persona i (Criterio trivial)
    Nodo sol;
    for (int i = 0; i < C.size(); ++i){
        sol.asig.push_back(i);
        sol.coste += C[i][sol.asig[i]];
    }

    Nodo raiz;
    raiz.asig = vector<int>(C.size(), NO_ASIGNADO);
    raiz.coste = 0;

    Q.push(raiz);
    while (!Q.empty()){
        Nodo e_nodo = Q.top();
        Q.pop();

        // Buscamos la primera persona sin tarea asignada
        auto a_asignar = find(e_nodo.asig.begin(), e_nodo.asig.end(), NO_ASIGNADO);
        int n_persona_asignar = a_asignar - e_nodo.asig.begin();

        // Si hemos asignado todas las tareas, hemos encontrado una solución
        if ( a_asignar == e_nodo.asig.end()){
            // Comprobamos si es mejor que la buscada
            if (e_nodo.coste < sol.coste)
                sol = e_nodo;
        }
        else{
            
            // Buscamos asignar una tarea a la persona sin tarea asignada
            for (int i=0; i < C.size(); ++i){

                // Comprobamos si la tarea i está ya asignada
                if (find(e_nodo.asig.begin(), e_nodo.asig.end(), i) != e_nodo.asig.end())
                    continue;
                
                Nodo hijo = e_nodo;
                hijo.asig[n_persona_asignar] = i;
                hijo.coste += C[n_persona_asignar][i];

                // Si la cota inferior es menor que el coste de la mejor solución encontrada,
                // añadimos el nodo a la cola de prioridad
                if (cotaInferior(C, hijo) < sol.coste)
                    Q.push(hijo);
                
            } // Creamos los nodos hijos

        }

    } // Mientras haya nodos en la cola de prioridad

    return sol;
}


int main(){
    vector<vector<double>> C =
    {
        {11, 12, 18, 40},
        {14, 15, 13, 22},
        {11, 17, 19, 23},
        {17, 14, 20, 28}
    };

    Nodo sol = asignarTareas(C);
    cout << "Coste: " << sol.coste << endl;
    for (int i = 0; i < sol.asig.size(); ++i){
        cout << "Persona " << i+1 << " -> Tarea " << sol.asig[i]+1 << endl;
    }
}
    

