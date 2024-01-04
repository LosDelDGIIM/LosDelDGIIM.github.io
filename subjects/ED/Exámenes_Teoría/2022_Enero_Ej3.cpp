/**
 * @file 2022_Enero_Ej3.cpp
 *
 * @brief Resolución del ejercicio 3 de la Convocatoria Oridinaria
 * 	  de Enero de 2022 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2021-22.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 3 - Convocatoria Ordinaria de Enero de 2022.
 *
 * @details Enunciado:  (1 punto)
 *
 * 	  Implementa una función:
 * 	  @code
 *		void resumecola(list<int> &L,queue<int> &Q);
 * 	  @endcode
 *
 * 	  que va tomando un elemento entero n de la cola Q y, si es estrictamente positivo, saca n
 * 	  elementos de L (si ya no quedan n elementos, saca todos los que queden) y los reemplaza
 * 	  por su producto. Si el elemento de la cola es negativo o cero, no hace nada.
 *
 * 	  Esto ocurre con todos los elementos de Q hasta que se acaben, o bien se acaben los elementos de L.
 *
 * 	  No pueden usarse estructuras auxiliares.
 *
 * 	  Ejemplo:
 * 	  Si L=(1,3,2,1,4,5,3,2,4,1) y Q=(3,2,-1,0,2,5,2,-3), tras la ejecución de la función resumecola(L,Q), deberán quedar:
 * 	  L=(6,4,15,8), y Q=(2,-3) (es decir, sobran elementos de Q).
 *
 * 	  Si L=(1,3,2,1,4,5,3,2,4,1,3,2,1,4,7) y Q=(3,2,-1,0,2,5), tras la ejecución de la función resumecola(L,Q), deberán quedar:
 * 	  L=(6,4,15,48,1,4,7), y Q=() (es decir, sobran elementos de L que quedan como estaban en la lista)
*/

#include <iostream>
#include <queue>
#include <list>
using namespace std;

/**
 * @brief Toma un elemento entero n de la cola Q y, si es estrictamente positivo, saca n
 * 	  elementos de L (si ya no quedan n elementos, saca todos los que queden) y los reemplaza
 * 	  por su producto. Si el elemento de la cola es negativo o cero, no hace nada.
 *
 * 	  Esto ocurre con todos los elementos de Q hasta que se acaben, o bien se acaben los elementos de L
 * @param L Lista de enteros que se va a modificar.
 * @param Q  Cola de enteros que se va a usar para modificar la lista.
 */
void resumecola(list<int> &L,queue<int> &Q){

	auto it_list = L.begin();

	while(Q.size()>0 && it_list != L.end()){

		int n=Q.front();
		Q.pop();

		// Si es <= 0, no hago nada
		if (n>0){
			int prod=1;
			// Saco n elementos de la lista (mientras queden) y los multiplico
			for(int i=0; i<n && it_list!=L.end(); ++i){
				prod *= *it_list;
				it_list = L.erase(it_list);
			}
			L.insert(it_list, prod);
		} // if (n>0)
	} // while(Q.size()>0 && it_list != L.end())
}








/**
 * @brief Sobrecarga de << para las listas template
 *
 * **No es necesario**. Solo está hecho para poder probarlo en una función main().
 * En el examen, no se haría.
 *
 * @tparam T  Tipo de los elementos de la lista.
 * @param os  Flujo de salida.
 * @param l  Lista de elementos.
 * @return Referencia al flujo de salida.
 */
template <typename T>
ostream& operator<< (ostream& os, const list<T>& l){
	for (auto it=l.begin(); it!=l.end(); ++it)
		os << *it << " ";
	return os;
}

/**
 * @brief Sobrecarga de << para las colas template
 *
 * **No es necesario**. Solo está hecho para poder probarlo en una función main().
 * En el examen, no se haría.
 *
 * @tparam T  Tipo de los elementos de la cola.
 * @param os  Flujo de salida.
 * @param q  cola de elementos.
 * @return Referencia al flujo de salida.
 */
template <typename T>
ostream& operator<< (ostream& os, const queue<T>& q){
	queue<T> q_aux = q;
	while(!q_aux.empty()){
		os << q_aux.front() << " ";
		q_aux.pop();
	}
	return os;
}

#define EJ1

/**
 * @brief Programa principal para probar la función @c resumecola.
 *
 * **No es necesario**. Solo está hecho para poder probarlo en una función main().
 * En el examen, no se haría.
 */
int main(){
#ifdef EJ1
	// Ejemplo 1
	list<int> L={1,3,2,1,4,5,3,2,4,1};
	// queue<int> Q={3,2,-1,0,2,5,2,-3};
	queue<int>Q;
	Q.push(3);Q.push(2); Q.push(-1);
	Q.push(0);Q.push(2);Q.push(5);
	Q.push(2); Q.push(-3);
#endif // EJ1
#ifdef EJ2
	// Ejemplo 2
	list<int> L={1,3,2,1,4,5,3,2,4,1,3,2,1,4,7};
	//queue<int> Q={3,2,-1,0,2,5};
	queue<int>Q;
	Q.push(3);
	Q.push(2);Q.push(-1);Q.push(0);
	Q.push(2); Q.push(5);
#endif // EJ2


	cout<<"Original: "<<endl;
	cout<<"\t L: "<<L<<endl;
	cout<<"\t Q: "<<Q<<endl << endl;

	resumecola(L,Q);

	cout<<"Resultado: "<<endl;
	cout<<"\t L: "<<L<<endl;
	cout<<"\t Q: "<<Q<<endl;
}