/**
 * @file 2022_Enero_Ej2.cpp
 *
 * @brief Resolución del ejercicio 2 de la Convocatoria Oridinaria
 * 	  de Enero de 2022 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2021-22.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 2 - Convocatoria Ordinaria de Enero de 2022.
 *
 * @details Enunciado:  (1.25 puntos)
 *
 * 	  Tenemos una clase libro que permite gestionar las palabras de un libro. Para
 * 	  ello usa un @c map<string,list<pair<int,int>>> de forma que para cada palabra hay una
 * 	  lista @c list<pair<int,int>> dónde cada par contiene un número de capítulo y la posición
 * 	  dentro del mismo en la que aparece dicha palabra.
 *
 * 	  - Implementa un método @c convertir_vector que devuelva @c vector<list<string>> de
 * 	  forma que en la posición i contenga todas las palabras del capítulo i+1 ordenadas
 * 	  alfabéticamente y sin repeticiones. Por ejemplo, si tenemos el map:
 *
 * 	  		<informática, {<1,10>,<2,10>,<3,41>}>
 * 	  		<telemática, {<1,2>,<1,21>,<2,50>,<3,31> }>
 * 	  		<robótica, {<3,30>,<4,5>}>
 *
 * 	  el vector contendría:
 * 	  		v[0]={informática,telemática,telemática} ->v[0]={informática,telemática}
 * 	  		v[1]={informática, telemática}
 * 	  		v[2]={informática,robótica,telemática}
 * 	  		v[3]={robótica}
 *
 *	  - Implementa una clase iterator que itere sobre las palabras del libro que aparezcan en
 *	  capítulos impares y en posiciones pares de ese capítulo. Implementa los métodos de la
 *	  clase iterator y los métodos @c begin() y @c end() de la la clase libro.
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <list>
#include <algorithm> // for_each
using namespace std;

class Libro {
private:
	/**
	 * @brief Mapa que contiene las palabras del libro.
	 */
	map<string,list<pair<int,int>>> datos;

public:

	/**
	 * @brief Constructor por defecto de la clase.
	 * @return Crea un objeto vacío de la clase Libro.
	 */
	Libro(){}

	/**
	 * @brief Constructor de la clase Libro.
	 *
	 * **No es necesario**. Solo está hecho para poder probar el iterador en una función main().
	 * En el examen, no se haría.
	 *
	 * Construye un Libro a partir de un vector de pares de strings. Cada par de strings
	 * representa una palabra y su posición en el libro.
	 *
	 * @param d Vector de pares de strings que contiene las palabras del libro.
	 *
	 * @return Crea un objeto de la clase Libro a partir de un vector de pares de strings.
	 */
	Libro(const vector<pair<string,pair<int,int> > >& d){
		for (int i=0;i<d.size();i++){
			auto it =datos.find(d[i].first);
			if (it!=datos.end()){
				it->second.push_back(d[i].second);
			}
			else {
				list<pair<int,int>> l1;
				l1.push_back(d[i].second);
				datos.emplace(d[i].first,l1);
			}
		} // for (int i=0;i<d.size();i++)
	}

	vector<list<string>> convertir_vector(){

		map<int, list<string>> map_aux;

		for(auto it_map = datos.begin(); it_map!=datos.end(); ++it_map)
			for (auto it_list = it_map->second.begin(); it_list!=it_map->second.end(); ++it_list){
				map_aux[it_list->first].push_back(it_map->first);
			}

		// Variable que contiene el número de capítulos del libro,
		// empezando a contar desde 1, tal y como lo dan en los datos
		int num_ult_cap = 0;
		if (map_aux.size() != 0)
			num_ult_cap = (--map_aux.end())->first; // Como el map ordena por el int, end() será el siguiente al ultimo.


		vector<list<string>> vout(num_ult_cap);
		for (int i=0; i<num_ult_cap; ++i){
			map_aux[i+1].sort();
			map_aux[i+1].unique();
			vout[i] = map_aux[i+1];
		}

		return vout;
	}


	class iterator {
	private:
		map<string,list<pair<int,int>>>::iterator it, final;
		list<pair<int, int>>::iterator it_l;

		bool condicion(){
			return (it_l->first %2 == 1) && (it_l->second %2 == 0);
		}
	public:
		iterator(){}

		bool operator==(const iterator & i) const{
			if (i.it==final && it==final) return true;
			else if (i.it==it && i.it_l == it_l) return true;
			else return false;
		}

		bool operator!=(const iterator & other) const{
			return !(*this==other);
		}

		pair<const string, pair<int, int>> operator*(){
			pair<const string,pair<int,int> > out(it->first,*it_l);
			return out;
		}

		iterator & operator++(){
			do{
				++it_l;
				if (it_l == it->second.end()) {
					++it;

					if (it!=final)
						it_l = it->second.begin();
				}
			}while(it!=final && !condicion());

			return *this;
		}

		friend class Libro;
	};

	iterator begin(){
		iterator iter;
		iter.it = datos.begin();
		iter.final = datos.end();

		if(iter.it != datos.end()){

			iter.it_l = iter.it->second.begin();
			if(!iter.condicion()) ++iter;
		}

		return iter;
	}

	iterator end(){
		iterator iter;
		iter.it = datos.end();
		iter.final = datos.end();

		return iter;
	}
};



/**
 * @brief Programa principal para probar la clase Libro.
 *
 * **No es necesario**. Solo está hecho para poder probar el iterador en una función main().
 * En el examen, no se haría.
 */
int main(){

	// Ejemplo de uso de la clase Libro
	vector<pair<string,pair<int,int> > > v;
	v.push_back(make_pair("informática",make_pair(1,10)));
	v.push_back(make_pair("informática",make_pair(2,10)));
	v.push_back(make_pair("informática",make_pair(3,41)));
	v.push_back(make_pair("telemática",make_pair(1,2)));
	v.push_back(make_pair("telemática",make_pair(1,21)));
	v.push_back(make_pair("telemática",make_pair(2,50)));
	v.push_back(make_pair("telemática",make_pair(3,31)));
	v.push_back(make_pair("robótica",make_pair(3,30)));
	v.push_back(make_pair("robótica",make_pair(4,5)));
	Libro mibook(v);



	vector<list<string>> vector=mibook.convertir_vector();
	cout<<"Comprobando el metodo...."<<endl;
	for (int i=0;i<vector.size();i++){
		cout<<"Chapter "<<i+1<<": ";
		for_each(vector[i].begin(),vector[i].end(), [](string &a){ cout<<a<<'\t';});
		cout<<endl;
	}



	cout<<"Comprobando iteradores...."<<endl;
	//Probando el iterator
	for (Libro::iterator i = mibook.begin(); i!=mibook.end();++i)
		cout<<(*i).first<<" "<<(*i).second.first<<" "<<(*i).second.second<<endl;
}


