/**
 * @file 2023_Enero_Ej4.cpp
 *
 * @brief Resolución del ejercicio 4 de la Convocatoria Oridinaria
 * 	  de Enero de 2023 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2022-23.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 4 - Convocatoria Ordinaria de Enero de 2023.
 *
 * @details Enunciado:  (1 punto)
 *
 * Dado un árbol binario de enteros A y un nivel en el árbol level, implementar una función:
 * @code
 * vector_sec nivel_caminos_creciente (bintree<int> A, int level);
 * @endcode
 *
 * que encuentre los caminos de longitud mayor o igual que uno desde cualquier nodo de
 * ese nivel a una hoja en el árbol que tengan una secuencia creciente de valores de
 * etiquetas. Devolver la solución en un vector de listas.
 *
 * Ejemplo:					A
 * 					  1
 * 				    /   \
 * 	level 2---->   4     7
 *				  / \   / \
 *				 8  9  11 10
 *				   /	\   \
 *				  6     13  15
 *						/ \
 *					   14 12
 *
 * 	@code
 * 	V=nivel_caminos_creciente (A, 2)
 *	V={ {11,13,14 }, {10, 15} }
 *	@endcode
 *
*/

#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <utility>
#include "bintree/bintree.h"
using namespace std;

typedef vector<list<int>> vector_sec;

/**
 * @brief Encuentra las secuencias crecientes de un nodo.
 * @param n Nodo del que se quiere encontrar las secuencias crecientes.
 * @return Vector de listas de enteros que contiene las secuencias crecientes del nodo.
 */
vector_sec secuencia_crecientes (const bintree<int>::node & n){

	vector_sec vsol;

	if (!n.null()) { // No es un nodo nulo

		if (n.left().null() && n.right().null()) {  // Es una hoja
			list<int> tmp;
			tmp.push_back(*n);
			vsol.push_back(tmp);
		} // Es una hoja


		else{   // Es un nodo normal

			vector_sec v_hi, v_hd;


			// Encuentro las secuencias de los hijos izq y dcha
			if(!n.left().null() && ( *n < *(n.left()) ) )
				v_hi = secuencia_crecientes(n.left());
			if(!n.right().null() && ( *n < *(n.right()) ) )
				v_hd = secuencia_crecientes(n.right());

			// Añado el nodo *n y los añado a vsol
			for (auto it=v_hi.begin(); it!=v_hi.end(); it++) {
				it->push_back(*n);
				vsol.push_back(*it);
			}
			for (auto it=v_hd.begin(); it!=v_hd.end(); it++) {
				it->push_back(*n);
				vsol.push_back(*it);
			}

		} // Es un nodo normal

	} // No es un nodo nulo


	return vsol;
}


/**
 * @brief Encuentra los caminos crecientes de un nivel de un árbol binario.
 * @param A  Árbol binario.
 * @param level  Nivel del árbol binario.
 * @return  Vector de listas de enteros que contiene los caminos crecientes del nivel del árbol binario.
 */
vector_sec nivel_caminos_creciente (const bintree<int> & A, int level){

	typedef pair<bintree<int>::node, int> nodo_nivel;

	queue<nodo_nivel> cola_nodos;
	nodo_nivel a(A.root(), 0);
	cola_nodos.push(a);

	vector_sec vsol;
	bool seguir = true;


	while(!cola_nodos.empty() && seguir){
		nodo_nivel n = cola_nodos.front();
		cola_nodos.pop();

		if (n.second < level){ // Si el nivel es menor que el buscado (está por encima)
			if(!n.first.left().null()){ // Si tiene hijo izquierda, se añade
				nodo_nivel izq(n.first.left(), n.second + 1);
				cola_nodos.push(izq);
			}
			if(!n.first.right().null()){ // Si tiene hijo derecha, se añade
				nodo_nivel der(n.first.right(), n.second + 1);
				cola_nodos.push(der);
			}
		} // n.second < level

		else if(n.second == level){      // Si el nodo está en el nivel buscado
			vector_sec sec = secuencia_crecientes(n.first);

			for (auto it = sec.begin(); it != sec.end(); it++){
				if (it->size() >= 2) { // Longitud mayor que 1. Tendrá que tener, como mínimo, 2 elementos.
					it->reverse();
					vsol.push_back(*it);
				}
			}
		} // n.second == level

		else{ // n.second > level    // Si el nivel es mayor que el buscado (está por debajo)
			seguir = false;
		}
	} // while(!cola_nodos.empty() && seguir)

	return vsol;

}





/**
 * @brief Programa principal para probar la función @c nivel_caminos_creciente.
 *
 * **No es necesario**. Solo está hecho para poder probar el iterador en una función main().
 * En el examen, no se haría.
 *
 */
int main(){
	//
	//
	// Ejemplo:                A
	//                   1
	//                  / \
	// level 1---->    4   7        V= nivel_caminos_creciente (A, 1)
	//                / \
	//               8   3          V={ {4,8} }
	//
	bintree<int> a(1);
	a.insert_left(a.root(), 4);
	a.insert_right(a.root(), 7);
	a.insert_right(a.root().left(), 3);
	a.insert_left(a.root().left(), 8);

	vector_sec v=nivel_caminos_creciente(a,1);
	cout<<endl;
	for (auto it_v=v.begin(); it_v!=v.end(); ++it_v) {
		for (auto it_l = it_v->begin(); it_l != it_v->end(); ++it_l)
			cout << *it_l << " ";

		cout<<endl;
	}

}