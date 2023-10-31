/**
 * @file 4. Colas. Creciente.cpp
 * @author José Juan Urrutia Milán "JJ"
 * @date 31/10/2023
 * @doc
 * 		- **Asignatura:** Estrucutras de Datos.
 * 		- **Curso Académico:** 2023-24.
 * 		- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
 * 		- **Grupo:** A.
 * 		- **Profesor:** José Enrique Cano Ocaña.
 * 		- **Descripción:** Examen de Prácticas I de la asignatura de Estructuras de Datos.
 * 		- **Duración:** 60 minutos
 * @brief Programa que elimina los elementos de una cola que no están en orden creciente.
 *
 * Tan solo hay que implementar la función creciente, el resto del código se proporciona.
 *
 * Ejemplo de ejecución:
 * @code{.sh}
 * ./Creciente
 * Cola Entrada: 5 5 9 13 19 17 16 20 19 21
 * Cola Creciente: 5 5 9 13 19 20 21
 * @endcode
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * @brief Imprime una cola de enteros.
 * @param Cola Cola a imprimir.
 */
void Imprimir(queue<int> Cola){

	while (!Cola.empty()){
		cout<<Cola.front()<<" ";
		Cola.pop();
	}
}

/**
 * @brief Función que elimina los elementos de una cola que no están en orden creciente.
 * @param Q Cola a modificar.
 * @post Q es una cola con los elementos en orden creciente.
 */
void creciente(queue<int> & Q){
	// Trabajamos sobre una cola auxiliar
	queue<int> aux;

	// Si Q no está vacía, metemos el primer elemento en aux
	if(!Q.empty()){
		aux.push(Q.front());
		Q.pop();
	}

	// Recorremos Q vaciándola
	while(!Q.empty()){
		// Si el frente de Q es mayor o igual que el último elemento de aux lo añadimos a aux
		if(aux.back() <= Q.front())
			aux.push(Q.front());

		Q.pop();
	}

	Q = aux;
}


/**
 * @brief Función principal
 * @return 0 si todo se ejecuta correctamente
 */
int main(){
	vector<int> V={5,5,9,13,19,17,16,20,19,21};
	queue<int> Q;

	for(int i=0; i<V.size(); i++)
		Q.push(V[i]);

	cout<<"Cola Entrada: ";
	Imprimir(Q);
	cout<<endl;

	creciente(Q);

	cout<<"Cola Creciente: ";
	Imprimir(Q);
	cout<<endl;
}