/**
 * @file 2023_Febrero_Ej2.cpp
 *
 * @brief Resolución del ejercicio 2 de la Convocatoria Oridinaria
 * 	  de Febrero de 2023 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2022-23.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 2 - Convocatoria Ordinaria de Febrero de 2023.
 *
 * @details Enunciado:  (1 punto)
 *
 * 	  Tenemos un contenedor de pares de elementos, {clave, bintree<int>} definida como:
 * 	  @code
 * 	  template <typename T>
 * 	  class contenedor {
 * 	  private:
 * 	  	unordered_map<T, bintree<int> > datos;
 * 	  .............
 * 	  };
 * 	  @endcode
 *
 * 	  Implementar un iterador que itere sobre las claves que cumplan la propiedad de que el
 * 	  bintree asociado tenga como suma de sus etiquetas un número par. Se deben implementar
 * 	  (aparte de las de la clase iterator) las funciones begin() y end() de la clase contenedor.
*/

#include <iostream>
#include <unordered_map>
#include <utility>
#include "bintree/bintree.h"
using namespace std;

/**
 * @brief Clase que representa un contenedor de pares de elementos.
 *
 * @tparam T Tipo de dato de la clave.
 */
template <typename T>
class contenedor {
public: // Se pone public para que se pueda acceder a los datos desde el main solo para pruebas
	/**
	 * @brief Mapa que contiene los pares de elementos.
	 */
	unordered_map<T, bintree<int>> datos;
public:
	class iterator{
	private:

		typename unordered_map<T, bintree<int>>::iterator it, final;

		/**
		 * @brief Función que calcula la suma de las etiquetas de un árbol.
		 * @param n  Nodo del árbol.
		 * @return  Suma de las etiquetas del árbol.
		 */
		int suma_arbol(const bintree<int>::node & n) const{
			if (n.null()) return 0;

			else
				return *n + suma_arbol(n.left()) + suma_arbol(n.right());
		}

		// Función que comprueba si la condición se cumple
		bool condicion(){
			return suma_arbol(it->second.root())%2==0;
		}

	public:
		iterator (){}

		bool operator==(const iterator & other) const{
			return this->it=other.it;
		}

		bool operator!=(const iterator & other) const{
			return this->it != other.it;
		}

		pair<const T, bintree<int>>& operator*()const{
			return *it;
		}

		iterator & operator++(){
			++it;
			while (it!=final && !condicion())
				++it;

			return *this;
		}

		friend class contenedor;
	};

	iterator begin(){
		iterator it;
		it.it = datos.begin();
		it.final = datos.end();

		if (it.it != it.final && !it.condicion())
			++it;
		

		return it;
	}

	iterator end(){
		iterator it;
		it.it = datos.end();
		it.final = datos.end();

		return it;
	}

};

/**
 * @brief Sobrecarga del operador de salida para imprimir un árbol.
 *
 * **No es necesario**. Solo está hecho para poder probarlo en una función main().
 * En el examen, no se haría.
 *
 * @param os  Flujo de salida.
 * @param arbol  Árbol a imprimir.
 * @return  Referencia al flujo de salida.
 */
ostream & operator<<(ostream & os, const bintree<int> & arbol){
	auto it = arbol.begin_postorder();
	auto it_end = arbol.end_postorder();

	while (it!=it_end){
		os << *it << " ";
		++it;
	}

	return os;
}


/**
 * @brief Función principal.
 *
 * **No es necesario**. Solo está hecho para poder probarlo en una función main().
 * En el examen, no se haría.
 */
int main(){

	contenedor<int> c;

	// Insertamos los pares de elementos. Los árboles son de prueba, con solo un nodo
	c.datos.insert(make_pair(1, bintree<int>(1)));
	c.datos.insert(make_pair(2, bintree<int>(2)));
	c.datos.insert(make_pair(3, bintree<int>(3)));
	c.datos.insert(make_pair(4, bintree<int>(4)));
	c.datos.insert(make_pair(5, bintree<int>(5)));
	c.datos.insert(make_pair(6, bintree<int>(6)));
	c.datos.insert(make_pair(7, bintree<int>(7)));
	c.datos.insert(make_pair(8, bintree<int>(8)));
	c.datos.insert(make_pair(9, bintree<int>(9)));
	c.datos.insert(make_pair(10, bintree<int>(10)));
	c.datos.insert(make_pair(11, bintree<int>(11)));

	// Imprimimos los pares de elementos
	for (auto it = c.begin(); it != c.end(); ++it)
		cout << (*it).first << " " << (*it).second << endl;


	return 0;
}
