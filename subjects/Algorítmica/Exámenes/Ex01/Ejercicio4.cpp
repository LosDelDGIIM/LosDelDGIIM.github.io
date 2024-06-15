/**
 * @file Ejercicio4.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 4 del Examen 1 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex01)
 * 
 * *Enunciado:*
 * Se desea conocer si, dado un número natural $n$, éste es o no un número combinatorio del tipo $k$ sobre $2$,
 *      $\binom{k}{2}$, para algún número $k$ natural.
 * 
 * Por ejemplo, $36 = \binom{9}{2}$, o $499500 = \binom{1000}{2}$.
 * 
 * Especificad un algoritmo lo más eficiente posible para resolver este problema.
 * 
 * Nota: $\binom{k}{2} = k \cdot (k-1) / 2$.
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 * En este caso, la primera versión que se os ocurre es despejar $k$ de la fórmula $\binom{k}{2} = n$ y comprobar si $k$ es un número entero:
 *          $$n = \frac{k \cdot (k-1)}{2} \Rightarrow 2n = k^2 - k \Rightarrow k^2 - k - 2n = 0$$
 *      Comprobamos si alguna de las dos soluciones de la ecuación cuadrática es un número natural, y si lo es, devolvemos true.
 * 
 * Sin embargo, este algoritmo no usa ninguna técnica vista en el curso, por lo que no es válido en el examen de Algorítmica.
 * Usaremos por tanto una técnica DyV, similar a la búsqueda binaria, para resolver el problema.
 */

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * @brief Función que resuelve el problema de si un número n es de la forma k sobre 2, es decir, $n = \binom{k}{2}$.
 * 
 * @param n Número natural a comprobar
 * @return true  Si n es de la forma k sobre 2
 * @return false  Si n no es de la forma k sobre 2
 * 
 * @note Eficiencia: Constante, O(1)
 */
bool esKSobre2_Directo(int n){

    // Resolvemos la ecuación k^2 - k - 2n = 0
    // k = (1 \pm sqrt(1 + 8n)) / 2
    // La raíz sabemos que existe porque n es un número natural, y sabemos que es mayor que 1 por ser 1+8n>1, por lo que tan solo consideramos la raíz que va sumando
    double k = (1 + sqrt(1 + 8*n)) / 2;

    // Comprobamos si k es un número natural
    return k == (int)k;
}


/**
 * @brief Función que resuelve el problema de si un número n es de la forma k sobre 2, es decir, $n = \binom{k}{2}$,
 *              par algún k entre ini y fin.
 * 
 * @param n Número natural a comprobar
 * @param ini Inicio del rango de búsqueda
 * @param fin Fin del rango de búsqueda
 * @return true Si n es de la forma k sobre 2
 * @return false Si n no es de la forma k sobre 2
 * 
 * @note Eficiencia: Logarítmica en el tamaño del rango de búsqueda (fin-ini+1)
 */
bool esKSobre2_DyV(int n, int ini, int fin){

    // Caso base: si ini > fin, no hay valores de k que cumplan la condición, por lo que devolvemos false
    if(ini > fin) return false;

    int mitad = (ini + fin) / 2;
    int mitad_sobre_2 = mitad * (mitad - 1) / 2;


    // Si n=\binom{mitad}{2}, devolvemos true
    if(mitad_sobre_2 == n)
        return true;

    // Si n < \binom{mitad}{2}, buscamos en la mitad inferior
    else if(n < mitad_sobre_2)
        return esKSobre2_DyV(n, ini, mitad - 1);

    // Si n > \binom{mitad}{2}, buscamos en la mitad superior
    else
        return esKSobre2_DyV(n, ini+1, fin);
}

/**
 * @brief Función que resuelve el problema de si un número n es de la forma k sobre 2, es decir, $n = \binom{k}{2}$.
 * 
 * @param n Número natural a comprobar
 * @return true  Si n es de la forma k sobre 2
 * @return false  Si n no es de la forma k sobre 2
 * 
 * @note Eficiencia: Logarítmica en n, O(log(n))
 */
bool esKSobre2_DyV(int n){
    return esKSobre2_DyV(n, 1, n);
}


int main(int argc, char const *argv[]){

    // Comprobamos el número de argumentos
    if(argc != 2){
        cout << "El programa debe recibir un unico argumento, el numero n a comprobar." << endl;
        return 1;
    }

    // Leemos el número n
    int n = atoi(argv[1]);

    // Comprobamos si n es de la forma k sobre 2
    if(esKSobre2_DyV(n))
        cout << "El numero " << n << " SI es de la forma k sobre 2." << endl;
    else
        cout << "El numero " << n << " NO es de la forma k sobre 2." << endl;

    return 0;
}