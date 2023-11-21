/**
 * @file no_interseccion.cpp
 * @author Arturo Olivares Martos
 * @date 21/11/2023
 * @doc
 * 		- **Asignatura:** Estrucutras de Datos.
 * 		- **Curso Académico:** 2023-24.
 * 		- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
 * 		- **Grupo:** B.
 * 		- **Profesor:** Ignacio Aguilera Martos.
 * 		- **Descripción:** Examen de Prácticas II de la asignatura de Estructuras de Datos.
 * 		- **Duración:** 60 minutos
 * 
 * @brief Programa que calcula la no intersección de tres conjuntos.
 *
 * Esta está explicada en la función no_interseccion().
 * Dados tres conjuntos a,b,c; la no interseccion de ellos es la unión menos la intersección.
 * Es decir, la unión de los siguientes conjuntos:
 *  - los elementos de a que no estén incluidos en b ni en c,
 *  - los elementos de b que no estén incluidos en a ni en c,
 *  - los elementos de c que no estén incluidos en a ni en b.
 * 
 * Tan solo se pide implementar la función no_interseccion, el resto del código se proporciona.
 *
 * Ejemplos de uso:
 * @code{.sh}
 * $ ./no_interseccion 1 2 3 - 2 3 7 - 3 4 5
 * Conjunto A: 1, 2, 3
 * Conjunto B: 2, 3, 7
 * Conjunto C: 3, 4, 5
 * Resultado: 1, 4, 5, 7
 * @endcode
 *
 * @code{.sh}
 * $ ./no_interseccion 1 2 3 - 2 3 4 - 3 4 5
 * Conjunto A: 1, 2, 3
 * Conjunto B: 2, 3, 4
 * Conjunto C: 3, 4, 5
 * Resultado: 1, 5
 * @endcode
 *
 * @code{.sh}
 * $ ./no_interseccion 1 2 3 4 5 6 - 2 4 5 - 5 6
 * Conjunto A: 1, 2, 3, 4, 5, 6
 * Conjunto B: 2, 4, 5
 * Conjunto C: 5, 6
 * Resultado: 1, 3
 * @endcode
 *
 * @code{.sh}
 * $ ./no_interseccion 1 2 3 - 1 2 3 - 1 2 3
 * Conjunto A: 1, 2, 3
 * Conjunto B: 1, 2, 3
 * Conjunto C: 1, 2, 3
 * Resultado:
 * @endcode
*/


#include <iostream>
#include <stdlib.h>
#include <set>
#include <string>

using namespace std;

/**
 * @brief Función que calcula la no intersección de tres conjuntos
 * @param a primer conjunto
 * @param b segundo conjunto
 * @param c tercer conjunto
 * @return conjunto con la unión de los siguientes conjuntos:
 *  - los elementos de a que no estén incluidos en b ni en c,
 *  - los elementos de b que no estén incluidos en a ni en c,
 *  - los elementos de c que no estén incluidos en a ni en b.
 *
*/
set<int> no_interseccion(set<int> a, set<int> b, set<int> c){

    set<int> result;

    // Elementos de A que no están ni en B ni en C
    for (set<int>::iterator it=a.begin(); it!=a.end(); ++it)
        if ((b.count(*it)==0) && (c.count(*it)==0))     // Implícito que (a.count(*it)!=0) && 
            result.insert(*it);

    // Elementos de B que no están ni en A ni en C
    for (set<int>::iterator it=b.begin(); it!=b.end(); ++it)
        if ((a.count(*it)==0) && (c.count(*it)==0))     // Implícito que (b.count(*it)!=0) && 
            result.insert(*it);

    // Elementos de C que no están ni en A ni en B
    for (set<int>::iterator it=c.begin(); it!=c.end(); ++it)
        if ((a.count(*it)==0) && (b.count(*it)==0))     // Implícito que (c.count(*it)!=0) && 
            result.insert(*it);


    /* // Otra solución con multiset:

    multiset<int> union_aux;


    // Calcular la unión de los tres conjuntos
    for (set<int>::iterator it=a.begin(); it!=a.end(); ++it)
        union_aux.insert(*it);

    for (set<int>::iterator it=b.begin(); it!=b.end(); ++it)
        unuion.insert(*it);

    for (set<int>::iterator it=c.begin(); it!=c.end(); ++it)
        union_aux.insert(*it);

    // Comprobar que cada elemento solo está una vez
    for (multiset<int>::interator it=union_aux.begin(); it!=union_aux.end(); ){

        if (union_aux.count(*it)==1) // El elemento está solo una vez. Lo añado.
            result.insert(*it);

        // Salto al siguiente elemento distinto
        it = union_aux.upper_bound(*it);
    }
    */


    return result;
}

/**
 * @brief Función que imprime un conjunto
 * @param s conjunto a imprimir
*/
void printSet(set<int> s){
    for(set<int>::iterator it = s.begin(); it!=s.end(); ++it)
        if (it == --s.end())
            cout << *it;
        else
            cout << *it << ", ";
    cout << endl;
}

int main(int argc, char* argv[]){

    // Conjuntos con los que se va a operar
    set<int> a,b,c;

    //Entero para gestionar la entrada de conjuntos
    int conjunto = 0;

    // Ejemplo de entrada 1 2 3 4 5 - 3 4 5 6 7 - 9 10
    // Se puede introducir el conjunto vacío introduciendo una "e" en la entrada
    // Ejemplo e - e - 1 2 3 => a = {}, b = {}, c = {1,2,3}
    for(int i = 1; i<argc; ++i){

        // si nos encontramos un - en la entrada es que cambiamos al siguiente conjunto
        if(argv[i][0]=='-')
            ++conjunto;

        else{ // No cambiamos de conjunto

            if (argv[i][0]=='e') // El conjunto es vacío
                continue;
            else{ // El conjunto no es vacío. Insertamos.
                if(conjunto==0)
                    a.insert(atoi(argv[i]));
                else if(conjunto==1)
                    b.insert(atoi(argv[i]));
                else if(conjunto==2)
                    c.insert(atoi(argv[i]));
            }  // El conjunto no es vacío. Insertamos.

        } // No cambiamos de conjunto

    } // for argc


    // Imprimimos los conjuntos
    cout << "Conjunto A: ";
    printSet(a);
    cout << "Conjunto B: ";
    printSet(b);
    cout << "Conjunto C: ";
    printSet(c);


    // Imprimimos el resultado de la operación
    cout << "Resultado: ";
    printSet(no_interseccion(a,b,c));

    return 0;
}
