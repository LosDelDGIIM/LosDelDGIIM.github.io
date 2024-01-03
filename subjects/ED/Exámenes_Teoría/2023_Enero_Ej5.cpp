/**
 * @file 2023_Enero_Ej5.cpp
 *
 * @brief Resolución del ejercicio 5 de la Convocatoria Oridinaria
 * 	  de Enero de 2023 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2022-23.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 5 - Convocatoria Ordinaria de Enero de 2023.
 *
 * @details Enunciado:  (1 punto)
 *
 * Implementar una función:
 * @code
 * void solo_en_2(vector<set<int> > &VS,set<int> &S1);
 * @endcode
 *
 * que dado un vector de conjuntos enteros VS, encuentre el conjunto S1 de todos aquellos
 * elementos que están exactamente en dos de ellos.
 *
 * Ejemplo:
 * @code
 * VS=[{0,1,2,3}, {1,3,4,5}, {1,3,6,7}, {2,4,7,9}, {0,7,8,9}]
 * @endcode
 *
 * @c solo_en_2(VS,S1) debe devolver:
 * @code
 * S1={0,2,4,9}
 * @endcode
 *
*/

#include <iostream>
#include <set>
#include <vector>
using namespace std;

#define NUM 2

/**
 * @brief Encuentra el conjunto de elementos que están exactamente en dos de los conjuntos del vector.
 * @param VS Vector de conjuntos enteros.
 * @param S1 Conjunto de elementos que están exactamente en dos de los conjuntos del vector.
 * @post @c S1 contiene los elementos que están exactamente en dos de los conjuntos del vector.
 */
void solo_en_2(vector<set<int> > &VS,set<int> &S1){

	// Meto todos los números en un multiset
	multiset<int> total_numeros;
	for (auto it=VS.begin(); it!=VS.end(); ++it)
		total_numeros.insert(it->begin(), it->end());

	// Itero sobre todo el multiset y meto en S1 los que están exactamente NUM veces
	for (auto it=total_numeros.begin(); it!=total_numeros.end();){

		size_t num_veces = total_numeros.count(*it);
		if(num_veces == NUM)
			S1.insert(*it);

		// Avanzo el iterador hasta el siguiente número
		it = total_numeros.upper_bound(*it);

	}
}



int main(){
	//[{0,1,2,3}, {1,3,4,5}, {1,3,6,7}, {2,4,7,9}, {0,7,8,9}],
	vector<set<int> > VS;
	set<int> s1={0,1,2,3};
	VS.push_back(s1);
	set<int> s2={1,3,4,5};
	VS.push_back(s2);
	set<int> s3={1,3,6,7};
	VS.push_back(s3);
	set<int> s4={2,4,7,9};
	VS.push_back(s4);
	set<int> s5={0,7,8,9};
	VS.push_back(s5);

	set<int> Sol;
	solo_en_2(VS,Sol);

	for (auto it = Sol.begin();it!=Sol.end();++it){
		cout<<*it<<" ";
	}
}