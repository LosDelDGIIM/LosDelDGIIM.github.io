/* 
 * File:   VectorDinamico.cpp
 * Author: Silvia Acid y Andrés Cano
 * 
 * Created on 28 April 2023, 13:05
 */

#include <iostream>

#include "VectorDinamico.h"

using namespace std;

/**
 * @brief Devuelve true si el robot @p rt se ve afectado "muerto" por 
 * la influencia del robot inhibidor al encontrarse en su radio de acción.
 * @param rt Robot que se comprueba si está afectado o no (parámetro de entrada)
 * @param inhibidor Robot inhibidor (parámetro de entrada)
 * @param radio Radio de acción del robot inhibidor (parámetro de entrada)
 * @return devuelve true si el robot rt está afectado por el robot inhibidor.
 * falso en caso contrario.
 */
bool afectado(const Robot& rt, const Robot& inhibidor, double radio) {
    float dist = rt.distancia(inhibidor);
    return dist <= radio;
}

/**
 * Imprime en la salida estándar los robots contenidos en el vector de 
 * robots proporcionado.
 * @param v Puntero a los robots (parámetro de entrada)
 * @param n Número de robots en el vector de robots (parámetro de entrada)
 */
void imprimirVector(const Robot* v, int n) {
    cout << n << endl;
    for (int i = 0; i < n; i++)
        cout << v[i].toString() << endl;
}

/**
 * @brief Reserva memoria dinámica para alojar n robots en un vector dinámico
 * @param n Número de robots a reservar (parámetro de entrada)
 * @return Dirección de inicio de la memoria dinámica reservada
 */
Robot* reservarM(int n) {
    
    Robot* array = nullptr;
    
    if (n!=0)
        array = new Robot[n];
    
    return array;
}

/**
 * @brief Libera la memoria dinámica usada por el vector dinámico pasado como 
 * argumento
 * @param v Puntero al vector de robots. Debe quedar con el valor nullptr, al 
 * tras ejecutar la función (parámetro de salida).
 */
void liberarM(Robot* &v) {
    delete[] v;
    v = nullptr;
}

/**
 * @brief Añade un robot adicional al vector dinámico @p v. El vector @p v debe 
 * redimensionarse para almacenar el contenido del vector anterior más el nuevo 
 * robot (@p nuevo). La función actualiza convenientemente el número de
 * elementos del vector @p v (@p tam)
 * @param nuevo El nuevo robot a añadir al vector 
 * dinámico @p v (parámetro de entrada)
 * @param v Puntero al vector dinámico de robots (parámetro de salida)
 * @param tam El número de robots almacenados en el vector dinámico de 
 * robots (parámetro de salida).
 */
void agnadeRobot(const Robot& nuevo, Robot* &v, int& tam) {
    
    // Reservo memoria para un dato más
    Robot* aux = reservarM(tam+1);
    
    // Copio los datos en aux
    for (int i=0; i<tam; i++)
        aux[i] = v[i];
    
    // Libero la memoria del vector v y modifico el puntero v
    if (v != nullptr)
        liberarM(v);
    v=aux;
    
    // Añado el nuevo robot
    v[tam]=nuevo;
    tam++;
}

/**
 * @brief Selecciona los robots de v_r2d2 que no se vean afectados 
 * por ninguno de los robots inhibidores. En v_salida se vuelcan los que 
 * sobreviven a todos los robots inhibidores.
 * @param vR2D2 Vector de robots (parámetro de entrada)
 * @param nR2D2 Número de elementos en el vector v_r2d2 (parámetro de entrada)
 * @param vInhibidor vector de robots inhibidores (parámetro de entrada)
 * @param nInhibidor  Número de elementos en el vector v_inhibidor (parámetro de entrada)
 * @param vSalida, vector de robots resultante (parámetro de salida)
 * @param nSalida Número de elementos en el vector v_salida (parámetro de 
 * salida)
 * @param radio Rango de distancia en el que un robot queda afectado (parámetro
 * de entrada).
 * 
 * Algoritmo
 * =========
 * Para cada robot r
 *    Para cada inhibidor i
 *         Comprobar si el robot r está afectado o no por el inhibidor
 *    Añadir r al vector de salida, solo si no se ve afectado POR NINGUN INHIBIDOR
 */
void supervivientes(const Robot* vR2D2, int nR2D2, const Robot* vInhibidor, int nInhibidor, 
        Robot* &vSalida, int&  nSalida, double radio){
    
    
    for(int r=0; r<nR2D2; r++){ // for robot
        
        bool ya_afectado=false; // En primer lugar, no es afectado
        
        for (int i=0; i<nInhibidor && !ya_afectado; i++) // for inhibidor
            // En el momento en el que ya ha sido afectado, pasa al siguiente robot
            ya_afectado = afectado(vR2D2[r], vInhibidor[i], radio);
        
        if (!ya_afectado) // No ha sido afectado por ningún inhibidor
            agnadeRobot(vR2D2[r], vSalida, nSalida);
    }
        
}

/**
 * @brief Realiza la lectura desde teclado de la lista de robots y los almacena 
 * en un vector dinámico, el cual se va redimensionando con cada lectura. 
 * Los datos de cada robot se leen en el orden id, x, y y carga. La lectura de
 * robots finaliza cuando se lee el valor -1 para un id. En ese caso no se 
 * seguirá leyendo el resto de datos de un robot, (x, y y carga).
 * @param v puntero de comienzo del vector de robots (parámetro de salida)
 * @param n Número de elementos del vector. Este dato se modifica cuando se 
 * inserta un nuevo robot (parámetro de salida).
 */
void lectura(Robot* &v, int& n){
    
    v = reservarM(0);
    
    const int TERMINADOR = -1;
   
    long id;
    float x,y;
    double carga;
    
    Robot aux;
    
    cin >> id;
    while (id != TERMINADOR){ // No se ha terminado de leer
        
        cin >> x >> y >> carga;
        
        aux.set(id, x, y, carga);
        agnadeRobot(aux, v, n); // Se añade el nuevo robot
        
        // Lectura adelantada
        cin >> id;
    }
}