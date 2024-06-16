/**
 * @file Ejercicio5.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 5 del Examen 2 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex02)
 * 
 * *Enunciado:*
 * Diseñad un algoritmo que determine si un cierto número natural $N$ puede expresarse o no como producto de tres números naturales consecutivos,
 *          $N = Y \cdot (Y + 1) \cdot (Y + 2)$,
 *      con un orden de eficiencia lo mejor posible.
 * _______________________________________________________________________________________________________________
 * 
 * OPCIÓN INICIAL:
 *    En primer lugar, se nos ocurre directamente despejar $Y$ de la ecuación y comprobar si es un número natural. Esta opción es directa $O(1)$,
 *          pero no usa ninguno de los algoritmos vistos en el temario.
 * 
 *    Para ello, despejamos $Y$ de la ecuación:
 *         $$ N = Y \cdot (Y + 1) \cdot (Y + 2) = Y^3 + 3Y^2 + 2Y $$
 * 
 *    No obstante, implementar de forma directa esta opción no es trivial, ya que se necesitaría resolver una ecuación cúbica. Existen diversos métodos
 *         para resolver ecuaciones cúbicas (como el método de aproximación de Newton), pero no se han visto en el temario y por tanto se descarta esta opción.
 * 
 * OPCIÓN FINAL:
 *    Vamos a optar por un algoritmo similar a la búsqueda binaria (DyV), pero adaptado a este problema.
 */



#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @brief Comprueba si un número N puede expresarse como producto de tres números naturales consecutivos
 * 
 * @param N  Número a comprobar
 * @param ini  Inicio del rango de búsqueda
 * @param fin  Fin del rango de búsqueda
 * @return true  Si N puede expresarse como producto de tres números naturales consecutivos
 * @return false  Si N NO puede expresarse como producto de tres números naturales consecutivos
 */
bool esProductoDeTresConsecutivos(int N, int ini, int fin){
    
    // Caso base: Si no hay candidatos de Y, devolvemos false
    if (ini > fin) return false;

    // Calculamos el candidato intermedio
    int mitad = ini + (fin - ini) / 2;
    int Y = mitad;

    // Calculamos el producto
    int producto = Y * (Y + 1) * (Y + 2);

    // Si el producto es igual a N, devolvemos true
    if (producto == N) return true;

    // Si el producto es menor que N, buscamos en la mitad derecha, ya que Y deberá ser mayor
    else if (producto < N) return esProductoDeTresConsecutivos(N, mitad + 1, fin);

    // Si el producto es mayor que N, buscamos en la mitad izquierda, ya que Y deberá ser menor
    else return esProductoDeTresConsecutivos(N, ini, mitad - 1);
}


/**
 * @brief Comprueba si un número N puede expresarse como producto de tres números naturales consecutivos
 * 
 * @param N  Número a comprobar
 * @return true  Si N puede expresarse como producto de tres números naturales consecutivos
 * @return false  Si N NO puede expresarse como producto de tres números naturales consecutivos
 */
bool esProductoDeTresConsecutivos(int N){
    return esProductoDeTresConsecutivos(N, 1, N);
}


int main(int argc, char const *argv[]) {
    
    // Controlamos el número de argumentos
    if (argc != 2){
        cout << "Error en el número de argumentos. El programa se ejecuta de la siguiente forma:" << endl;
        cout << argv[0] << " <N>" << endl;
        return 1;
    }

    // Obtenemos el número N
    int N = atoi(argv[1]);

    // Comprobamos si es producto de tres números consecutivos
    if (esProductoDeTresConsecutivos(N)) cout << "El numero " << N << " SI es producto de tres numeros consecutivos." << endl;
    else cout << "El numero " << N << " NO es producto de tres numeros consecutivos." << endl;

    return 0;
}