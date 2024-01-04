/**
 * @file 2021_Enero_Ej4.cpp
 *
 * @brief Resolución del ejercicio 4 de la Convocatoria Oridinaria
 * 	  de Enero de 2021 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2020-21.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 4 - Convocatoria Ordinaria de Enero de 2021.
 *
 *
 * @details Enunciado:  (1.5 puntos)
 *
 * 	  Dado un vector de conjuntos vector<set<int> > V, implementar una función:
 * 	  @code
 * 	  void contar(const vector<set<int> > &V, map<int,int> &veces);
 * 	  @endcode
 * 	  que devuelva, a través del map veces, el número de conjuntos en los que aparece cada
 * 	  uno de los elementos presentes en v.
 *
 * 	  Ejemplo:
 * 	  V={ <1,2,3>, <2,4>, <3,4,5,9>}
 *	  tras ejecutar contar(V,veces) se debe tener:
 * 	  veces={ <1,1>, <2,2>, <3,2>, <4,2>, <5,1>, <9,1>}
 */

#include <vector>
#include <set>
#include <map>
#include <iostream>
using namespace std;

/**
 * @brief Devuelve, a través del map veces, el número de conjuntos en los que aparece cada
 * 	  uno de los elementos presentes en v.
 * @param V Vector de conjuntos.
 * @param veces Map que contiene el número de conjuntos en los que aparece cada
 * 	  uno de los elementos presentes en v.
 * @post @c veces contiene el número de conjuntos en los que aparece cada
 * 	  uno de los elementos presentes en v.
 */
void contar(const vector<set<int> > &V, map<int,int> &veces){

	for (auto it_vector=V.begin(); it_vector!=V.end(); ++it_vector)
		for(auto it_set=it_vector->begin(); it_set!=it_vector->end(); ++it_set)
			veces[*it_set]++;
}


int main(){
	vector<set<int>> miv;
	set<int> s1={1,2};
	set<int> s2={1,2,3,5};
	set<int> s3={1,2,3,5,10,12};
	miv.push_back(s1);
	miv.push_back(s2);
	miv.push_back(s3);

	map<int,int>veces;
	contar(miv,veces);
	for (auto it=veces.begin(); it!=veces.end(); ++it){
		cout<<it->first<<":\tfrecuencia\t"<<it->second<<endl;
	}
}


