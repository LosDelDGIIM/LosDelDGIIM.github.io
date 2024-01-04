/**
 * @file 2021_Enero_Ej2.cpp
 *
 * @brief Resolución del ejercicio 2 de la Convocatoria Oridinaria
 * 	  de Enero de 2021 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2020-21.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 2 - Convocatoria Ordinaria de Enero de 2021.
 *
 * @details Enunciado:  (1.5 puntos)
 *
 * 	  Se define una matriz sesgada como una matriz nxn en la solo unos pocos
 * 	  elementos son pares.
 *
 * 	  Un ejemplo de este tipo de matrices es la matriz que se muestra. Es
 * 	  una matriz 6x6 de valores enteros. De los 36 elementos, solo 2 son pares:
 * 	  el elemento (0,2) y el elemento (4,3).
 * 	  @code
 * 	  7  9  4  5  1  3
 * 	  5  9  7  1  3  5
 * 	  1  3  7  3  3  1
 * 	  5  5  5  5  5  5
 * 	  3  1  1  2  9  9
 * 	  1  5  1  3  7  7
 * 	  @endcode
 *
 * 	  Proponer una representación eficiente (basada en el tipo vector<list>) para la matriz e implementar:
 * 	  - El operator() que devuelva el elemento en la fila fil, columna col.
 * 	  - Un iterador que itere sobre los elementos pares de la matriz. Han de implementarse
 * 	  (aparte de las de la clase iteradora) las funciones begin() y end().
*/

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
using namespace std;

/**
 * @brief Clase que representa una matriz sesgada.
 *
 * Una matriz sesgada es una matriz nxn en la solo unos pocos elementos son pares.
 *
 * @pre Es una matriz cuadrada.
 */
class matriz_sesgada{
private:

	/**
	 * @brief Vector de listas que contiene los elementos de la matriz.
	 */
	vector<list<int>> datos;
public:
	matriz_sesgada(){}

	/**
	 * @brief Constructor de la clase.
	 *
	 * Construye una matriz sesgada a partir de una matriz de enteros.
	 *
	 * **No es necesario**. Solo está hecho para poder probar el iterador en una función main().
	 * En el examen, no se haría.
	 *
	 * @tparam R  Número de filas de la matriz.
	 * @tparam C  Número de columnas de la matriz.
	 * @param dat  Matriz de enteros.
	 *
	 * @pre La matriz es cuadrada (R=C).
	 */
	template <int R,int C>
	matriz_sesgada(int (&dat)[R][C]){
		assert(R==C);
		int n=R;
		datos =vector<list<int>>(n);
		for (int i=0; i<n; i++){
			datos[i]=list<int>(dat[i],dat[i]+n);
		}
	}

	/**
	 * @brief Devuelve el número de filas de la matriz.
	 * @return Número de filas de la matriz.
	 */
	int numfilas() const{
		return datos.size();
	}

	/**
	 * @brief Devuelve el número de columnas de la matriz.
	 * @return Número de columnas de la matriz.
	 */
	int numcols() const{
		return datos.size(); // La matriz es cuadrada
	}


	/**
	 * Sobrecarga del operador () para acceder a los elementos de la matriz.
	 */
	int operator()(int fil, int col){
		auto it = datos.at(fil).begin();
		advance(it, col);
		return *it;
	}

	class iterator{
	private:
		vector<list<int>>::iterator it_fil, final;
		list<int>::iterator it_col;

		bool condicion(){
			return *it_col %2 ==0;
		}
	public:
		iterator(){}

		iterator& operator++(){
			do{
				++it_col;
				if (it_col == it_fil->end()) {
					++it_fil;
					if(it_fil != final)
						it_col = it_fil->begin();
				}
			}while(it_fil!=final && !condicion());
		}

		bool operator==(const iterator& other){
			return (this->it_fil == other.it_fil) && ((it_fil==final) || (this->it_col==other.it_col));
		}

		bool operator!=(const iterator& other){
			return !(*this==other);
		}

		int & operator*(){
			return *it_col;
		}

		friend class matriz_sesgada;
	};

	iterator begin(){
		iterator it;
		it.it_fil = datos.begin();
		it.final = datos.end();
		if(it.it_fil != datos.end()) {
			it.it_col = it.it_fil->begin();

			if (!it.condicion()) ++it;
		}

		return it;
	}

	iterator end(){
		iterator it;
		it.it_fil = datos.end();
		it.final = datos.end();

		return it;
	}
};




int main() {
	int m[6][6] = {
			{7, 9, 4, 5, 1, 3},
			{5, 9, 3, 7, 1, 5},
			{1, 3, 7, 3, 3, 1},
			{5, 5, 5, 5, 5, 5},
			{3, 1, 1, 2, 9, 9},
			{1, 5, 1, 3, 7, 7}
	};
	matriz_sesgada mimatriz(m);
	cout << "Salida usando el operator ()..." << endl;
	for (int i = 0; i < mimatriz.numfilas(); i++) {
		for (int j = 0; j < mimatriz.numcols(); j++) {
			cout << mimatriz(i, j) << "\t";
		}
		cout << endl;
	}
	cout << endl << endl;

	cout<<"Salida de los pares..."<<endl;
	for (auto it = mimatriz.begin(); it!=mimatriz.end(); ++it){
		cout<<*it<<" ";
	}


	return 0;
}