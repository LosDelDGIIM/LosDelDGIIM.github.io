/* 
 * File:   main.cpp
 * Author: 
 * 
 * Created on 28 April 2023, 13:05
 */

/**
 * Se trata de gestionar la información de unos robots que se mueven en el 
 * espacio 2D. Concretamente se dispone de un conjunto de robots r2d2 y de 
 * un conjunto de robots inhibidores, cada uno almacenado en un vector de 
 * robots en memoria dinámica.  
 * 
 * Un robot tiene un id único (long), coordenadas x e y (float), y una 
 * carga (double).
 * 
 * Un robot r r2d2 no se ve afectado (sobrevive) a un inhibidor cuando la distancia 
 * entre r y el inhibidor es superior al radio de alcance (parámetro del main).
 * Un robot r2d2 sobrevivirá a todos los robots inhibidores si no está dentro 
 * del radio de alcance de ningún robot inhibidor.
 * 
 * El objetivo de este programa es obtener un vector con los robots r2d2 que 
 * sobreviven a todos los inhibidores. 

 * Con la ayuda de la clase Robot COMPLETAMENTE DEFINIDA 
 * y unos argumentos opcionales [ -r num ] de main(), donde num es un 
 * radio (número real), la función main() debe realizar los siguientes
 * pasos:
 * 
 * 1. Cargar datos desde la entrada estándar a un vector de Robot r2d2, y al 
 * vector de Robot inhibidores.
 * Ambos vectores deben alojarse con el tamaño adecuado, para contener los 
 * robots en memoria dinámica.  
 * Para la lectura de los robots desde la entrada, se leen los 
 * robots mientras el id sea distinto de -1, que es la condición de parada. 
 *
 * 2. Mostrar el contenido de los vectores r2d2 e inhibidores leídos.
 *
 * 3. Elaborar un vector (tambien dinámico) con los robots r2d2, 
 * que sobreviven a todos los inhibidores. 
 * 
 * 
  Se ha preparado el fichero data/prueba1.txt con los datos siguientes: 
 

1 9.1 9.1 1.5 
2 10.5 10.5 1.0
3 11.0 11.0 1.7
4 3.5 1.2 2.3
5 2.7 10.3 2.9
6 4.5 6.7 2.1
7 19.9 10.10 3
8 1.1 2.4 3.9
9 10.0 9.0 3.3
10 0.0 0.0 1.2
-1
100 8.5 9.0 12.0
200 1.0 1.0 10
300 2.0 2.0 15
-1 

Para el valor de radio = 2.0
La salida del programa sería:

5
2->(10.5,10.5,1),
3->(11,11,1.7),
5->(2.7,10.3,2.9),
6->(4.5,6.7,2.1),
7->(19.9,10.1,3),

Si quieres utilizar valgrind
 valgrind --leak-check=full      

Especificación de las TAREAS A REALIZAR:

0. Rellenar nombre y apellidos tras el token Author. 

1. Revisar las cabeceras de las funciones externas. 
   Se han de respectar tanto el número como los tipos de los parámetros. 
 
bool afectado()
void imprimirVector()
Robot *reservarM()
void liberarM()
void agnadeRobot()
void supervivientes()

void lectura()
 
Se han de respectar tanto el número de parámetros como sus tipos. 
La forma de pasar los argumentos (por valor, referencia etc.) lo decides tú.

2. Completar las funciones:
bool afectado()
Robot *reservarM()
void liberarM()
void agnadeRobot()
void supervivientes()
void lectura()

3. Completar el main, que puede recibir un argumento opcional -r <num>;  
   donde num es el radio que se debe de considerar para establecer el alcance 
   de un inhibidor. Si no se da un nuevo valor, el radio por defecto es 2.0;

*/

#include <iostream>
#include <cstring>
#include "Robot.h"
#include "VectorDinamico.h"

using namespace std;


/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char* args[]) {
    double radio = 2.0; // Radio por defecto

    Robot *vR2d2;  // vector de robots r2d2
    Robot *vInhibidores;  // vector de robots inhibidores
    Robot *vResultado;  // vector de robots resultante
    int nR2d2, nResultado, nInhibidores; // longitudes respectivas
    
    // radio = atof("7.3"); ejemplo de como transformar un cstring en un float
    
    // Inicialización variables locales
    vR2d2 = vInhibidores = vResultado = nullptr;
    nR2d2=nResultado=nInhibidores=0;
    
    // Lectura de la opción
    if (nargs != 3 && nargs != 1){ // Número de parámetros erróneo
        cout << "Número de Parámetros erróneo" << endl;
        return 1;
    }
    else if (nargs == 3){ // Se ha dado opción
        if (strcmp(args[1], "-r") != 0){ // Opción incorrecta
            cout << "Opción incorrecta" << endl;
            return 1;
        }
        
        else{  // args[1]=="-r" // Opción correcta
            radio = atof(args[2]);
            
            if (radio < 0){
                cout << "El radio debe ser positivo" << endl;
                return 1;
            }
        }
        
    }
    // En caso contrario, no se ha dado opción. Se usa el radio por defecto
    
    
    // leer e imprimir Robots vR2d2
    lectura(vR2d2, nR2d2);
    cout << "Vector de robots r2d2es " << endl;
    imprimirVector(vR2d2, nR2d2);
    
    // leer  e imprimir Robots vInhibidores 
    lectura(vInhibidores, nInhibidores);
    cout << "Vector de robots inhibidores" << endl;
    imprimirVector(vInhibidores, nInhibidores);
    
    // hallar los supervivientes
    supervivientes(vR2d2, nR2d2, vInhibidores, nInhibidores, 
                    vResultado, nResultado, radio);
   
    cout << "Se filtra el vector resultado" << endl;
    imprimirVector(vResultado, nResultado);
    
    
    // Se libera la memoria de los tres arrays dinámicos
    liberarM(vR2d2);
    liberarM(vInhibidores);
    liberarM(vResultado);

    return 0;
}
