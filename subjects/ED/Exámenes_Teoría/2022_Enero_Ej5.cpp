/**
 * @file 2022_Enero_Ej4.cpp
 *
 * @brief Resolución del ejercicio 5 de la Convocatoria Oridinaria
 * 	  de Enero de 2022 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2021-22.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio54 - Convocatoria Ordinaria de Enero de 2022.
 *
 * @details Enunciado:  (1 punto)
 *
 * 	  Dado un vector de conjuntos vector<set<int> > V, implementa una función
 * 	  @code
 * 	  void esta_en_conjunto(vector<set<int> > &v, map<int,list<int> > &recuento);
 * 	  @endcode
 *
 * 	  que devuelva a través del map recuento cada uno de los elementos que aparecen en
 * 	  algún conjunto y una lista de las posiciones del vector en las que se puede encontrar.
 *
 * 	  Ejemplo:
 * 	  v=[ {1,20,3}, {20,3,45}, {3,45,5,93}, {20,45,6,8}, {93}, {1,3,5}]
 * 	  recuento={ {1,{0,5}}, {20, {0, 1,3}}, {3,{0,1,2,5}}, {5,{2,5}}, ...}
 */

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <list>
using namespace std;

/**
 * @brief Devuelve a través del map recuento cada uno de los elementos que aparecen en
 * 	  algún conjunto y una lista de las posiciones del vector en las que se puede encontrar.
 * @param v Vector de conjuntos.
 * @param recuento Map que contiene cada uno de los elementos que aparecen en
 * 	  algún conjunto y una lista de las posiciones del vector en las que se puede encontrar.
 * @post @c recuento contiene cada uno de los elementos que aparecen en
 * 	  algún conjunto y una lista de las posiciones del vector en las que se puede encontrar.
 */
void esta_en_conjunto(vector<set<int> > &v, map<int,list<int> > &recuento){

	for(int i_vector=0; i_vector<v.size(); ++i_vector)
		for (auto it_set=v[i_vector].begin(); it_set!=v[i_vector].end(); ++it_set)
			recuento[*it_set].push_back(i_vector);
}



/**
 * @brief Función principal
 *
 * **No es necesario**. Solo está hecho para poder probarlo en una función main().
 * En el examen, no se haría.
 */
int main(){
	set<int>s1={1,20,3},s2={20,3,45},s3={3,45,5,93},
			s4={20,45,6,8},s5={93},s6={1,3,5};
	vector<set<int> > miv={s1,s2,s3,s4,s5,s6};
	map<int,list<int> > re;
	esta_en_conjunto(miv,re);
	for (auto it =re.begin(); it!=re.end();++it){
		cout<<"Elemento "<<it->first<<"\t aparece en:\t ";
		for (auto it2=it->second.begin();it2!=it->second.end();++it2)
			cout<<*it2<<"\t";
		cout<<endl;
	}
}
