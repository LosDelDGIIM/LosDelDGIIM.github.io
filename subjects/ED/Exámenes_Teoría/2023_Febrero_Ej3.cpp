/**
 * @file 2023_Febrero_Ej3.cpp
 *
 * @brief Resolución del ejercicio 3 de la Convocatoria Oridinaria
 * 	  de Febrero de 2023 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2022-23.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 3 - Convocatoria Ordinaria de Febrero de 2023.
 *
 * @details Enunciado:  (1 punto)
 *
 * 	  Implementar una función
 * 	  @code
 * 	  bool permutalista (list<int> & L1, list<int> & L2)
 * 	  @endcode
 *
 * 	  que devuelva true si L1 y L2 tienen la misma cantidad de elementos y los elementos de L1
 * 	  son una permutación de los de L2.
 *
 * 	  Ejemplo: 	L1={1,23,21,4,2,3,0} 	y 	L2={21,1,3,2,4,23,0} => true
 * 	  			L1={1,3,5} 				y 	L2={1, 5, 4} => false
 *
 * 	  Si hay elementos repetidos tienen que estar el mismo número de veces en las 2 listas para
 * 	  poder ser TRUE. No pueden usarse estructuras auxiliares, el algoritmo puede ser
 * 	  destructivo y no conservar las listas iniciales y no puede usarse ningún algoritmo de ordenación.
*/

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;


/**
 * @brief Función que comprueba si dos listas son permutaciones la una de la otra.
 * @param L1 Lista 1.
 * @param L2 Lista 2.
 * @retval true si las listas son permutaciones la una de la otra.
 * @retval false si las listas no son permutaciones la una de la otra.
 */
bool permutalista (list<int> & L1, list<int> & L2) {

	if (L1.size()!=L2.size())
		return false;

	// Ya tienen el mismo tamaño
	bool iguales=true; // Para que entre la primera vez
	for (auto it_L1=L1.begin(); iguales && it_L1!=L1.end(); ++it_L1){

		// Buscamos *it_L1 en L2
		auto it_L2 = find(L2.begin(), L2.end(), *it_L1);

		if (it_L2!=L2.end()) // Si está, lo borramos, para controlar el aspecto de los elementos repetidos.
			L2.erase(it_L2);
		else  // Si no está, no son iguales, y nos salimos.
			iguales=false;
	} // for L1

	return iguales;
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
	list<int>L1={1,23,21,4,2,3,0};
	list<int>L2={21,1,3,2,4,23,0};
	cout<<"L1: " << L1 << endl;
	cout<<endl;
	cout<<"L2: " << L2 << endl;
	cout<<endl;

	if (permutalista(L1,L2))
		cout<<"L1 es una premutacion de L2"<<endl;
	else cout<<"L1 no es una permutacion de L2"<<endl;
}