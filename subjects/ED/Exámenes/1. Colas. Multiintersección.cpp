/**
 * @file 1.Colas. Multiintersección.cpp
 * @author Arturo Olivares Martos
 * @brief Programa que calcula la multiintersección de dos colas.
 *
 * Dadas dos colas con elementos repetidos y ordenadas de menor a mayor, calcula la multiintersección de ambas.
 * La multiintersección de dos colas es una cola que contiene los elementos que están en ambas colas
 * repetidos tantas veces como estén en ambas colas.
 *
 * Ejemplo de ejecución:
 * @code{.sh}
 * ./Multiinterseccion
 * q1: [2, 2, 3, 3]
 * q2: [1, 2, 3, 3, 3, 4]
 * Multiinterseccion: [2, 3, 3]
 * @endcode
 */

#include <iostream>
#include <queue>

using namespace std;

/**
 * @brief Sobrecarga del operador de salida para la clase queue.
 * @tparam T Tipo de dato almacenado en la cola.
 * @param os  Flujo de salida.
 * @param q  Cola a mostrar.
 * @return  Referencia al flujo de salida.
 */
template <typename T>
ostream& operator<<(ostream& os, const queue<T>& q) {
	queue<T> aux = q;
	os << "[";
	while (!aux.empty()) {
		os << aux.front();
		aux.pop();
		if (!aux.empty()) os << ", ";
	}
	os << "]";
	return os;
}


/**
 * @brief Función que calcula la multiintersección de dos colas.
 * @param q1  Primera cola.
 * @param q2  Segunda cola.
 * @return  Cola con la multiintersección de las dos colas.
 * @pre  Las colas deben estar ordenadas de menor a mayor.
 */
queue<int> multiinterseccion (queue<int> &q1, queue<int> &q2) {

	queue<int> multinter;

	while (!q1.empty() && !q2.empty()){

		// Si son iguales, lo añado a la multiintersección y los elemino
		if (q1.front() == q2.front()){
			multinter.push(q1.front());
			q1.pop();
			q2.pop();
		}

		// Si son distintos, elimino el menor
		else if (q1.front() > q2.front())
			q2.pop();

		else // (q1.front() < q2.front())
			q1.pop();
	}

	return multinter;
}

/**
 * @brief Función principal
 * @return 0 si todo se ejecuta correctamente
*/
int main() {

	queue<int> q1, q2;

	q1.push(2);
	q1.push(2);
	q1.push(3);
	q1.push(3);

	q2.push(1);
	q2.push(2);
	q2.push(3);
	q2.push(3);
	q2.push(3);
	q2.push(4);

	cout << "q1: " << q1 << endl;
	cout << "q2: " << q2 << endl;

	queue<int> q3 = multiinterseccion(q1, q2);

	cout << "Multiinterseccion: " << q3 << endl;
	return 0;
}