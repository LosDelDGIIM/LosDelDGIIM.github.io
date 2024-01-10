/**
 * @file 2023_Febrero_Ej4.cpp
 *
 * @brief Resolución del ejercicio 4 de la Convocatoria Oridinaria
 * 	  de Febrero de 2023 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2022-23.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 4 - Convocatoria Ordinaria de Febrero de 2023.
 *
 * @details Enunciado:  (1 punto)
 *
 * 	  Dado un bintree<int>, implementar una función
 * 	  @code
 * 	  void prom_nivel(bintree<int> &T, list<float> &P);
 * 	  @endcode
 *
 * 	  que genere una lista de reales P, donde el primer elemento de la lista sea el promedio de
 * 	  los valores de las etiquetas de los nodos del árbol de nivel 0, el segundo sea el promedio
 * 	  de los de nivel 1, el tercero el promedio de los de nivel 2, y así sucesivamente. Es decir,
 * 	  que si el árbol tiene profundidad N, la lista tendrá N+1 elementos de tipo float.
 *
 * 	  Ejemplo:					A
 * 					  1
 * 				    /   \
 * 	level 2---->   4     7
 *				  / \   / \
 *				 8  9  20 15
 *				   /	\   \
 *				  18     14  10
 *
 *		prom_nivel( A, P)
 *		P={1.0, 5.5, 13.0, 14.0}
 *
*/

#include <iostream>
#include <list>
#include "bintree/bintree.h"
using namespace std;

/**
 * @brief Genera una lista de reales P, donde el primer elemento de la lista sea el promedio de
 * 	  los valores de las etiquetas de los nodos del árbol de nivel 0, el segundo sea el promedio
 * 	  de los de nivel 1, el tercero el promedio de los de nivel 2, y así sucesivamente. Es decir,
 * 	  que si el árbol tiene profundidad N, la lista tendrá N+1 elementos de tipo float.
 * @param T Árbol binario de enteros.
 * @param P Lista de reales.
 * @post @c P contiene el promedio de los valores de las etiquetas de los nodos del árbol de nivel 0,
 * 	 el promedio de los de nivel 1, el promedio de los de nivel 2, y así sucesivamente.
 */
void prom_nivel(bintree<int> &T, list<float> &P){

	// Vaciamos P, para que no tenga contenido anterior.
	P.clear();

	// Creamos una cola de los nodos, para acceder por niveles. Metemos en el frente la raíz.
	queue<bintree<int>::node> cola_nodos;
	if (!T.root().null())
		cola_nodos.push(T.root());

	bintree<int>::node nod_aux; // Nodo auxiliar.

	while(!cola_nodos.empty()){

		/* Nos encontramos en el nivel nivel.
		 * Conforme vayamos iterando sobre cada nodo, añadiremos al final de la cola
		 * los nodos del nivel n+1, pero no queremos procesar estos ahora.
		 * Por tanto, iteramos tantas veces como elementos tenga cola_nodos ANTES de empezar a procesar el nivel.
		 */
		int size_nivel = cola_nodos.size();
		float prom_nivel = 0;

		// For cada nodo del nivel nivel
		for(int i = 0; i < size_nivel; ++i){

			// Añadimos al final de la cola los hijos del i-ésimo nodo.
			nod_aux = cola_nodos.front();
			cola_nodos.pop();
			if(!nod_aux.left().null())
				cola_nodos.push(nod_aux.left());
			if(!nod_aux.right().null())
				cola_nodos.push(nod_aux.right());

			// Procesamos el iésimo nodo del nivel nivel
			prom_nivel += *nod_aux;
		} // For nodo in nivel

		// Dividimos para hacer la media
		if (size_nivel!=0)
			prom_nivel /= size_nivel;

		// Lo añadimos a la lista
		P.push_back(prom_nivel);
	} // While cola_nodos no vacía
}


/**
 * @brief Sobrecarga del operador << para imprimir listas.
 *
 * **No es necesario**. Solo está hecho para poder probarlo en una función main().
 * En el examen, no se haría.
 *
 * @tparam T  Tipo de los elementos de la lista.
 * @param os  Flujo de salida.
 * @param L  Lista a imprimir.
 * @return  Referencia al flujo de salida.
 */
template <typename T>
ostream & operator << (ostream & os, const list<T> & L){
	for (auto it=L.begin(); it!=L.end(); ++it)
		os<<*it<<" ";
	return os;
}


/**
 * @brief Función principal.
 *
 * **No es necesario**. Solo está hecho para poder probarlo en una función main().
 * En el examen, no se haría.
 *
 */
int main(){
//
	//
	// Ejemplo:                A
	//                   1
	//                  / \
	// level 1---->    4   6        V= prom_nivel (A, V)
	//                / \
	//               8   3          V={ 1, 5 , 5.5 }
	//
	bintree<int> a(1);
	a.insert_left(a.root(), 4);
	a.insert_right(a.root(), 6);
	a.insert_right(a.root().left(), 3);
	a.insert_left(a.root().left(), 8);

	list<float>out;
	prom_nivel(a,out);
	cout<<"La lista con los promedios por nivel es..."<<endl;
	cout << out << endl;
}