/**
 * @file 2022_Enero_Ej4.cpp
 *
 * @brief Resolución del ejercicio 4 de la Convocatoria Oridinaria
 * 	  de Enero de 2022 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2021-22.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 4 - Convocatoria Ordinaria de Enero de 2022.
 *
 * @details Enunciado:  (1 punto)
 *
 * 	  Dado un árbol binario A y un nodo n de ese árbol, implementa una función:
 * 	  @code
 * 	  bool secuencia_creciente (const bintree<int> &A, bintree<int>::node n);
 * 	  @endcode
 * 	  que devuelva true si existe algún camino desde n a una hoja en la que se cumpla que
 * 	  cada etiqueta de un nodo hijo tiene un valor mayor que la del nodo.
 *
 * 	  Ejemplo:
 *
 *		 	   3 <--n
 *			 /  \
 *			6    7
 *		   / \  / \
 *		  1  3  9  2
 *
 *			 true: {3, 7, 9}
 *
 *		     3 <----n
 *		   /  \
 *		  6    9
 *		 / \  / \
 *		1  3 8  2
 *
 *		    false
 *
 *		      3  <---n
 *			/   \
 *		   6     4
 *		  / \   / \
 *		 8  2  5  1
 *
 *		    true: {3, 4, 5} o {3,6,8}
 */

#include "bintree/bintree.h"
#include <iostream>
using namespace std;

/**
 * @brief Devuelve true si existe algún camino desde n a una hoja en la que se cumpla que
 * 	  cada etiqueta de un nodo hijo tiene un valor mayor que la del nodo.
 * @param A Árbol binario.
 * @param n Nodo del árbol.
 * @retval true Si existe algún camino desde n a una hoja en la que se cumpla que
 * 	  cada etiqueta de un nodo hijo tiene un valor mayor que la del nodo.
 * 	  false En caso contrario.
 */
bool secuencia_creciente (const bintree<int> &A, bintree<int>::node n){

	// Caso base: si es nulo, devuelvo true
	if (n.null()) return true;

	// Caso base: si es una hoja, devuelvo true
	if (n.left().null() && n.right().null()) return true;

	// Caso recursivo: si no es nulo, compruebo si es creciente
	bool res_dcha=false, res_izq=false;
	if (!n.left().null() && (*(n.left())>*n) )
		res_izq = secuencia_creciente(A, n.left());
	if (!n.right().null() && (*(n.right())>*n) )
		res_dcha = secuencia_creciente(A, n.right());

	bool res = res_izq || res_dcha; // Da igual si el camino es por la izq o por la dcha

	return res;
}




/**
 * @brief Función principal.
 *
 * **No es necesario**. Solo está hecho para poder probarlo en una función main().
 * En el examen, no se haría.
 *
 */
int main(){
	// Creamos el árbol:
	//         1
	//	     /  \
	//      8    5
	//	        / \
	//         14  7
	//          \
	//          22

	bintree<int> Arb(1);
	Arb.insert_left(Arb.root(), 8);
	Arb.insert_right(Arb.root(), 5);
	Arb.insert_right(Arb.root().right(), 7);
	Arb.insert_left(Arb.root().right(), 14);
	Arb.insert_right(Arb.root().right().left(), 22);

	if (secuencia_creciente(Arb,Arb.root()))
		cout<<"Se cumple la condición "<<endl;
	else
		cout<<"No se cumple la condición"<<endl;
}