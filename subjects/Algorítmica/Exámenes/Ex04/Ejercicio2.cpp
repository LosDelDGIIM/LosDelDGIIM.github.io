/**
 * @file Ejercicio2.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 2 del Examen 4 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex04)
 * 
 * *Enunciado:*
 * Una estación de ITV consta de $m$ líneas de inspección de vehículos iguales. Hay un total
 * de $n$ vehículos que necesitan inspección. En función de sus características, cada vehículo tardará
 * en ser inspeccionado un tiempo $t_i$, $i = 1, ... , n$.
 * 
 * Se desea encontrar la manera de atender a los $n$ vehículos y acabar en el menor tiempo posible.
 * 
 * Diseñad un algoritmo de exploración de grafos que determine cómo asignar los vehículos a las líneas.
 * Especificad claramente, además del algoritmo, la representación del problema, la representación de la solución,
 * las restricciones explícitas e implícitas, así como las posibles cotas a utilizar.
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 * Este problema se trata de una variación de asignación de tareas a trabajadores, donde las tareas son los vehículos y los trabajadores son las líneas de inspección.
 * El tiempo acumulado de inspección de los vehículos no va a variar, puesto que todos los vehículos han de ser inspeccionados.
 * No obstante, lo que se busca es minimizar el tiempo que tarda en terminar, es decir, el tiempo que se tarda hasta que todas las líneas de inspección han terminado.
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Linea{
    double tiempo_total=0;  // Tiempo total acumulado que llevamos de los vehículos asignados en la línea
    vector<int> vehiculos;  // Vehículos asignados a la línea
};

struct Nodo{
    vector<Linea> lineas;       // Líneas de inspección
    int vehiculo_a_asignar;     // Vehículo que vamos a asignar en este nodo, primer vehículo que no ha sido aún asignado
    double tiempoEnTerminar;    // Tiempo que tardaremos en terminar de inspeccionar todos los vehículos, el máximo de los tiempos de las líneas

    /**
     * @brief Constructor de la estructura Nodo, con m líneas de inspección
     * 
     * @param m Número de líneas de inspección
     */
    Nodo(int m){
        lineas.resize(m);
        vehiculo_a_asignar = 0;
        tiempoEnTerminar = 0;
    }

    /**
     * @brief Actualiza el tiempo que tardaremos en terminar de inspeccionar todos los vehículos
     * 
     * @return double Tiempo que tardaremos en terminar de inspeccionar todos los vehículos
     * 
     * @note Solo nos interesa actualizar este tiempo cuando hemos asignado todos los vehículos (cuando hemos llegado a una solución),
     *              ya que en caso contrario se seguirá actualizando en cada asignación de vehículo a línea.
     */
    void actualizarTiempoEnTerminar(){
        tiempoEnTerminar = 0;
        for(const Linea &l : lineas){
            tiempoEnTerminar = max(tiempoEnTerminar, l.tiempo_total);
        }
    }

    /**
     * @brief Comprueba si es factible asignar el vehículo i a la fila j
     * 
     * @pre El vehículo i no ha sido aún asignado
     * 
     * @param t Vector con los tiempos de inspección de los vehículos
     * @param i Vehículo que queremos asignar
     * @param j Línea de inspección a la que queremos asignar el vehículo
     * @param mejor_sol Mejor solución encontrada hasta el momento
     * @return true En caso de que sea factible asignar el vehículo i a la línea j
     * @return false En caso contrario
     */
    bool factible(const vector<int> &t, int i, int j, const Nodo &mejor_sol) const{

        // Hacemos uso de una cota inferior.
        // Si el tiempo total acumulado de la línea j más el tiempo que tarda en inspeccionar el vehículo i
        // es mayor que el tiempo que tardaremos en terminar usando otra solución mejor, no es factible asignar el vehículo i a la línea j
        // puesto que no vamos a mejorar la solución.
        if (lineas[j].tiempo_total + t[i] > mejor_sol.tiempoEnTerminar)
            return false;


        return true;
    }



};


/**
 * @brief Función que asigna los vehículos a las líneas de inspección
 * 
 * @param t Vector con los tiempos de inspección de los vehículos
 * @param e_nodo  Nodo actual
 * @param sol  Mejor solución encontrada hasta el momento
 */
void asignarVehiculos(const vector<int> &t, Nodo& e_nodo, Nodo& sol){

    // Si hemos asignado todos los vehículos, hemos llegado a una solución
    if (e_nodo.vehiculo_a_asignar == t.size()){
        e_nodo.actualizarTiempoEnTerminar();
        // Si la solución actual es mejor que la mejor solución encontrada hasta el momento, actualizamos la solución
        if (e_nodo.tiempoEnTerminar < sol.tiempoEnTerminar)
            sol = e_nodo;
    }
    else{

        // Probamos a asignar cada vehículo a cada línea
        for (int j = 0; j < e_nodo.lineas.size(); j++){

            // Si es factible asignar el vehículo i a la línea j, lo asignamos
            if (e_nodo.factible(t, e_nodo.vehiculo_a_asignar, j, sol)){
                e_nodo.lineas[j].vehiculos.push_back(e_nodo.vehiculo_a_asignar);
                e_nodo.lineas[j].tiempo_total += t[e_nodo.vehiculo_a_asignar];
                e_nodo.vehiculo_a_asignar++;
                asignarVehiculos(t, e_nodo, sol);
                e_nodo.vehiculo_a_asignar--;
                e_nodo.lineas[j].tiempo_total -= t[e_nodo.vehiculo_a_asignar];
                e_nodo.lineas[j].vehiculos.pop_back();
            }
        } // for linea
    } 
}



int main(){

    int n_lineas = 4;
    vector<int> t = {2, 5, 7, 10, 3, 4, 6, 8, 9, 1};

    cout << "Numero de lineas: " << n_lineas << endl;
    cout << "Vehiculos: " << endl;
    for (int i = 0; i < t.size(); i++)
        cout << "- Vehiculo " << i << ": " << t[i] << " minutos" << endl;
    

    Nodo e_nodo(n_lineas);
    Nodo sol(n_lineas);

    // Para iniciar con una asignación, asignamos por round-robin los vehículos
    for (int i = 0; i < t.size(); i++){
        sol.lineas[i%n_lineas].vehiculos.push_back(i);
        sol.lineas[i%n_lineas].tiempo_total += t[i];
    }
    // Actualizamos el vehículo a asignar
    sol.vehiculo_a_asignar = t.size();
    // Actualizamos el tiempo que tardaremos en terminar
    sol.actualizarTiempoEnTerminar();

    // Una vez fijada la cota superior, llamamos a la función asignarVehiculos
    asignarVehiculos(t, e_nodo, sol);


    cout << "Coste total de la asignación: " << sol.tiempoEnTerminar << " minutos" << endl;
    for (int i = 0; i < sol.lineas.size(); i++){
        cout << "- Linea " << i << " (" << sol.lineas[i].tiempo_total << " minutos): ";
        for (int j = 0; j < sol.lineas[i].vehiculos.size(); j++){
            cout << sol.lineas[i].vehiculos[j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}