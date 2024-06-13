/**
 * @file SeleccionActividades.cpp
 * @author Arturo Olivares Martos
 * 
 * @brief Programa para resolver el problema de la selección de actividades mediante Greedy
 * 
 * Dadas n actividades con sus tiempos de inicio y fin, se trata de seleccionar el máximo número de actividades
 * que no se solapen.
 * 
 * 
 * - Conjunto de candidatos: Todas las actividades
 * - Conjunto de seleccionados: Actividades seleccionadas, inicialmente vacío
 * - Función solución: Conjunto de candidatos vacío
 * - Función de factibilidad: La actividad seleccionada no se solapa con las seleccionadas
 * - Función de selección: Actividad con menor tiempo de fin
 * - Función objetivo: Número de actividades seleccionadas 
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include <chrono>
/**
 * @brief Estructura para representar una hora 
 */
struct Hora {
    std::chrono::hours horas;
    std::chrono::minutes minutos;

    Hora(int h, int m) : horas(h), minutos(m % 60) {
        if (h < 0 || h > 23 || m < 0 || m > 59) {
            throw std::invalid_argument("Hora o minutos inválidos");
        }
    }

    // Operador para comparar horas
    bool operator<(const Hora &h) const {
        return horas < h.horas || (horas == h.horas && minutos < h.minutos);
    }
    bool operator>=(const Hora &h) const {
        return !(*this < h);
    }
};

/**
 * @brief Estructura para representar una actividad 
 */
struct Actividad{
    Hora inicio;
    Hora fin;

    // Operador para comparar actividades
    bool operator<(const Actividad &a) const{
        return fin < a.fin;
    }
};



/**
 * @brief Función para seleccionar el máximo número de actividades que no se solapen
 * 
 * @param actividades Vector de actividades candidatas
 * @return vector<Actividad> Vector con las actividades seleccionadas
 */
vector<Actividad> SeleccionActividades(vector<Actividad> &actividades){

    // Se ordenan las actividades por tiempo de fin
    sort(actividades.begin(), actividades.end());

    vector<Actividad> seleccionadas;
    seleccionadas.push_back(actividades[0]);

    for (int i = 1; i < actividades.size(); i++){
        if (actividades[i].inicio >= seleccionadas.back().fin)     // Función de factibilidad
            seleccionadas.push_back(actividades[i]);
    }

    return seleccionadas;
}
