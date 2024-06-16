/**
 * @file Ejercicio5.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 5 del Examen 4 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex04)
 * 
 * *Enunciado:*
 * Un aficionado al póker juega una partida cada dı́a, y anota los euros que gana o pierde.
 * 
 * Por ejemplo, la siguiente tabla muestra los resultados del último mes.
 *      L   M   X   J   V   S   D
 *      __________________________
 *                          29  -7
 *      14  21  30  -47  1  7   -39
 *      23  -20 -36 -41  27 -34 7
 *      48  35  -46 -16  32 18  5
 *      -33 27  28  -22  1  -20 -42
 * 
 * Podemos ver que empezó el mes con una ganancia de $29$ euros, y terminó con una pérdida de $42$.
 * El beneficio total obtenido en el mes (la suma de todas las ganancias y pérdidas) es $−50$ euros.
 * Analizando la información, el jugador se podrı́a dar cuenta de que si hubiera empezado a jugar el
 * dı́a $16$ y terminado el dı́a $26$, habrı́a maximizado sus ganancias, obteniendo $105$ euros.
 * 
 * En general, dado un vector de ganancias/pérdidas de longitud $n$, se desea encontrar el subvector
 * sobre el cual se consigue el beneficio total máximo. Diseñad un algoritmo que realice esta tarea de
 * forma lo más eficiente posible.
 * 
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 * Se trata del problema de la subsecuencia de suma máxima, que se puede resolver mediante DyV.
 * 
 * Para resolverlo, se divide el vector en dos partes iguales, y se calcula:
 *      - La subsecuencia de suma máxima que termina antes o en el medio
 *      - La subsecuencia de suma máxima que empieza en el medio o después
 *      - La subsecuencia de suma máxima que cruza el medio
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <utility>

using namespace std;


/**
 * @brief Funcion que calcula la suma de los elementos de un vector en un rango determinado.
 * 
 * @param v  Vector de enteros
 * @param init Posicion inicial
 * @param fin  Posicion final
 * @return int Suma de los elementos del vector en el rango [init,fin]
 */
int suma(const vector<int> & v, int init, int fin){
    int result=0;

    bool index_ok = 0<=init && init<=fin && fin<v.size();

    // Tan solo se calcula la suma si los indices son correctos
    // Evitamos así las subsecuencias vacias
    if(index_ok)
        for(int i=init; i<=fin; ++i)
            result+=v[i];
    
    return result;
}

pair<int, int> subsecMax_DyV(const vector<int> &v, int init, int fin){
    
    pair<int,int> bounds_max;
    int  suma_max;

    // Caso base: solo hay un elemento
    if (init==fin){
        bounds_max = {init, fin};
    }
    else{
        int middle = init + (fin-init)/2;

        pair<int,int> bounds_max_izq  = subsecMax_DyV(v,init,middle);   // Subsecuencia maxima de la izquierda
        pair<int,int> bounds_max_dcha = subsecMax_DyV(v,middle+1,fin);  // Subsecuencia maxima de la derecha

        int suma_max_izq  = suma(v,bounds_max_izq.first,bounds_max_izq.second);
        int suma_max_dcha = suma(v,bounds_max_dcha.first,bounds_max_dcha.second);


        // Combinacion del centro
		// Bucamos la subsecMax_DyV que contenga a middle y a middle+1
        pair <int,int> bounds_max_central (middle,middle+1);
		int suma_max_central = suma(v, bounds_max_central.first, bounds_max_central.second);

		int suma_central_tmp = suma_max_central;

        // Si hay subsencuencia máxima a la izq, actualizo el borde por la izquierda
        if (bounds_max_izq.second >= init){
            // Actualizo el borde por la izquierda.
            // Voy desplazandome a la izquierda (hasta encontrarme con bounds_max_izq) y actualizando la suma
            int lim_izq_tmp = bounds_max_central.first;

            while (lim_izq_tmp>bounds_max_izq.second){
                lim_izq_tmp--;
                suma_central_tmp += v[lim_izq_tmp];
                if (suma_central_tmp>=suma_max_central){
                    bounds_max_central.first = lim_izq_tmp;
                    suma_max_central = suma_central_tmp;
                }
            }

            // Si se ha llegado a bounds_max_izq, se aprovecha que sabemos que la suma de bounds_max_izq es la mayor
            // por lo que se contabiliza de golpe.
            // Se resta el valor de v[bounds_max_izq.second] porque ha sido el último que ya se ha sumado antes
            if (lim_izq_tmp==bounds_max_izq.second){
                suma_central_tmp += suma_max_izq - v[lim_izq_tmp];

                if (suma_central_tmp>=suma_max_central){
                    bounds_max_central.first = bounds_max_izq.first;
                    suma_max_central = suma_central_tmp;
                }
            }
    
        } // Fin de la actualización del borde por la izquierda

        	

        // Si hay subsencuencia máxima a la dcha, actualizo el borde por la dcha
        if (bounds_max_dcha.first >= middle+1){
            // Actualizo el borde por la dcha.
            // Voy desplazandome a la dcha (hasta encontrarme con bounds_max_dcha) y actualizando la suma
            suma_central_tmp = suma_max_central;
            int lim_dcha_tmp = bounds_max_central.second;

            while (lim_dcha_tmp<bounds_max_dcha.first){
                lim_dcha_tmp++;
                suma_central_tmp += v[lim_dcha_tmp];
                if (suma_central_tmp>=suma_max_central){
                    bounds_max_central.second = lim_dcha_tmp;
                    suma_max_central = suma_central_tmp;
                }
            }

            // Si se ha llegado a bounds_max_dcha, se aprovecha que sabemos que la suma de bounds_max_dcha es la mayor
            // por lo que se contabiliza de golpe.
            // Se resta el valor de v[bounds_max_dcha.first] porque ha sido el último que ya se ha sumado antes
            if (lim_dcha_tmp==bounds_max_dcha.first){
                suma_central_tmp += suma_max_dcha - v[lim_dcha_tmp];

                if (suma_central_tmp>=suma_max_central){
                    bounds_max_central.second = bounds_max_dcha.second;
                    suma_max_central = suma_central_tmp;
                }
            }
        } // Fin de la actualización del borde por la dcha
		
		
		


        //Combinacion de casos. Me quedo con el caso mejor.
        if(suma_max_izq>=suma_max_dcha){
            bounds_max = bounds_max_izq;
            suma_max = suma_max_izq;
        }
        else{
            bounds_max = bounds_max_dcha;
            suma_max = suma_max_dcha;
        }

        if(suma_max_central>= suma_max){
            bounds_max = bounds_max_central;
            suma_max = suma_max_central;
        }

        #ifdef DEBUG
        // Imprimo los resultados parciales, para comprobar que el algoritmo funciona correctamente
        cout << "Init: " << init << " Fin: " << fin << endl;
        cout << "Secuencia: ";
        for(int i=init; i<=fin; ++i)
            cout << v[i] << " ";
        cout << endl;
        cout << "Izq: " << bounds_max_izq.first << " " << bounds_max_izq.second << " " << suma_max_izq << endl;
        cout << "Dcha: " << bounds_max_dcha.first << " " << bounds_max_dcha.second << " " << suma_max_dcha << endl;
        cout << "Central: " << bounds_max_central.first << " " << bounds_max_central.second << " " << suma_max_central << endl;
        cout << "Mejor: " << bounds_max.first << " " << bounds_max.second << " " <<  suma_max << endl;
        cout << endl;
        #endif
    }

    return bounds_max;

}



int main(int argc, char const *argv[]) {
    
    vector<int> v = {29, -7, 14, 21, 30, -47, 1, 7, -39, 23, -20, -36, -41, 27, -34, 7, 48, 35, -46, -16, 32, 18, 5, -33, 27, 28, -22, 1, -20, -42};

    pair<int,int> bounds_max = subsecMax_DyV(v,0,v.size()-1);
    int suma_max = suma(v,bounds_max.first,bounds_max.second);

    cout << "Límites de la subsecuencia de suma máxima: [" << bounds_max.first << ", " << bounds_max.second << "]" << endl;
    cout << "Suma de la subsecuencia de suma máxima: " << suma_max << endl;

    return 0;
}