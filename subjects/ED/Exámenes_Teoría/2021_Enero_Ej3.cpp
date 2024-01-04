/**
 * @file 2021_Enero_Ej3.cpp
 *
 * @brief Resolución del ejercicio 3 de la Convocatoria Oridinaria
 * 	  de Enero de 2021 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2020-21.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 3 - Convocatoria Ordinaria de Enero de 2021.
 *
 *
 * @details Enunciado:  (1.5 puntos)
 *
 * 	  Dado un árbol binario A y un nodo n de ese árbol, implementa una función:
 * 	  @code
 * 	  bool camino_especial (bintree<int> A, bintree<int> :: node n, int k);
 * 	  @endcode
 * 	  que devuelva true si existe algún camino desde n a una hoja con las etiquetas de
 * 	  los nodos ordenadas ascendentemente y sumando una cantidad k.
 *
 * 	  Ejemplo (k=19):
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
 *		    false: {3, 4, 5} o {3,6,8}, pero no suman 19
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
bool camino_especial (const bintree<int> & A, const bintree<int>::node & n, int k){

	// Caso base: si es nulo, devuelvo false
	// Si inicialmente se le pasa un nodo no nulo, en el proceso recursivo no se llegará a un nodo nulo
	if (n.null()) return false;

	// Caso base: si es una hoja y suma k, devuelvo true
	if (n.left().null() && n.right().null()) return *n==k;

	// Caso recursivo: si no es nulo, compruebo si es creciente
	bool res_dcha=false, res_izq=false;
	if (!n.left().null() && (*(n.left())>*n) )
		res_izq = camino_especial(A, n.left(), k-*n);
	if (!n.right().null() && (*(n.right())>*n) )
		res_dcha = camino_especial(A, n.right(), k-*n);

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

	int k=42;
	if (camino_especial(Arb,Arb.root(), k))
		cout<<"Se cumple la condición "<<endl;
	else
		cout<<"No se cumple la condición"<<endl;
}