/**
 * @file 2.Pilas.Inversas.cpp
 * @author Arturo Olivares Martos
 * @brief  Programa que determina si una pila y una cola son inversas.
 *
 * Se dice que una pila es inversa a una cola cuando el listado de los elementos de la pila coincide
 * con el listado de los elementos de la cola pero en orden inverso.
 *
 * Ejemplo de ejecución:
 * @code{.sh}
 * ./Inversas
 * Pila: [1, 3, 7, 7, 2]
 * Cola: [2, 7, 7, 3, 1]
 * ¿Son inversas? 1
 * @endcode
 */

#include <iostream>
#include <stack>
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
 * @brief Sobrecarga del operador de salida para la clase stack.
 * @tparam T Tipo de dato almacenado en la pila.
 * @param os  Flujo de salida.
 * @param s  Pila a mostrar.
 * @return  Referencia al flujo de salida.
 */
template <typename T>
ostream& operator<<(ostream& os, const stack<T>& s) {
	stack<T> aux = s;
	os << "[";
	while (!aux.empty()) {
		os << aux.top();
		aux.pop();
		if (!aux.empty()) os << ", ";
	}
	os << "]";
	return os;
}


/**
 * @brief Función que determina si una pila y una cola son inversas.
 * @tparam T  Tipo de dato almacenado en la pila y la cola.
 * @param s  Pila.
 * @param q  Cola.
 * @return  @retval true si la pila y la cola son inversas.
 * 			@retval false en caso contrario.
 */
template <class T>
bool soniversas(stack<T> &s, queue<T> &q){

	bool inversas = q.size() == s.size();

	if(inversas){ // Ya tienen el mismo tamaño

		// Invierto la pila
		stack<T> aux;
		while (!s.empty()){
			aux.push(s.top());
			s.pop();
		}

		while(inversas && !aux.empty()){
			inversas &= aux.top() == q.front();
			aux.pop();
			q.pop();
		}

	} // if inversas

	return inversas;
}



/**
 * @brief Función principal
 * @return 0 si todo se ejecuta correctamente
 */
int main() {

	stack<int> s;
	queue<int> q;

	s.push(2);
	s.push(7);
	s.push(7);
	s.push(3);
	s.push(1);

	q.push(2);
	q.push(7);
	q.push(7);
	q.push(3);
	q.push(1);

	cout << "Pila: " << s << endl;
	cout << "Cola: " << q << endl;

	cout << "¿Son inversas? " << soniversas(s, q) << endl;

	return 0;
}