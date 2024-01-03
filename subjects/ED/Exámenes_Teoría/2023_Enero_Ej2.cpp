/**
 * @file 2023_Enero_Ej2.cpp
 *
 * @brief Resolución del ejercicio 2 de la Convocatoria Oridinaria
 * 	  de Enero de 2023 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2022-23.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 2 - Convocatoria Ordinaria de Enero de 2023.
 *
 * @details Enunciado:  (1 punto)
 *
 * 	  Se desea construir un traductor de un idioma origen a un idioma destino.
 *
 * 	  Una palabra en el idioma origen puede tener más de una traducción en el idioma destino.
 * 	  Usando como representación para el TDA Traductor un @c map<string,set<string>>:
 *
 * 	  Implementar una clase iteradora dentro de la clase Traductor para dada una palabra en
 * 	  el idioma de destino, iterar por todas las palabras del idioma de origen que tengan como
 * 	  traducción esa palabra. Han de implementarse (aparte de las de la clase iteradora) las
 * 	  funciones @c begin y @c end.
*/

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Traductor {
private:
	/**
	 * @brief Mapa que contiene las palabras a traducir.
	 */
	map<string,set<string>> datos;
public:

	/**
	 * @brief Constructor por defecto de la clase.
	 * @return Crea un objeto vacío de la clase Traductor.
	 */
	Traductor(){}

	/**
	 * @brief Constructor de la clase Traductor.
	 *
	 * **No es necesario**. Solo está hecho para poder probar el iterador en una función main().
	 * En el examen, no se haría.
	 *
	 * Construye un Traductor a partir de un vector de pares de strings. Cada par de strings
	 * representa una palabra en el idioma origen y su traducción en el idioma destino.
	 *
	 * @param d Vector de pares de strings que contiene las palabras a traducir.
	 *
	 * @return Crea un objeto de la clase Traductor a partir de un vector de pares de strings.
	 */
	Traductor(const vector<pair<string,string> >& d){
		for (int i=0;i<d.size();i++){
			auto it =datos.find(d[i].first);
			if (it!=datos.end()){
				it->second.insert(d[i].second);
			}
			else {
				set<string> s1;
				s1.insert(d[i].second);
				datos.emplace(d[i].first,s1);
			}
		}
	}

	/**
	 * Clase iteradora de la clase Traductor.
	 */
	class iterator {
	private:

		string dest_word;
		map<string,set<string>>::iterator it, final;

		/**
		 * @brief Comprueba si la palabra @c dest_word está en el conjunto de traducciones
		 * 	  de la palabra apuntada por el iterador.
		 * @retval true Si la palabra @c dest_word está en el conjunto de traducciones
		 * 	     de la palabra apuntada por el iterador.
		 * 	     false En caso contrario.
		 */
		bool es_traduccion(){
			return it->second.find(dest_word)!=it->second.end();
		}

	public:

		iterator(){}

		/**
		 * @brief Operador de pre-incremento.
		 * @return Devuelve un iterador que apunta a la siguiente palabra del idioma origen
		 * 	   que tiene como traducción la palabra @c dest_word.
		 */
		iterator operator++(){
			do{
				++it;
			}while(it!=final && !es_traduccion()); // Mientras no sea la palabra que buscamos o no se haya llegado al final del mapa

			return *this;
		}

		bool operator==(const iterator & other) const{
			return it==other.it && dest_word==other.dest_word && final==other.final;
		}

		bool operator!=(const iterator & other) const{
			return !(*this == other);
		}

		pair<const string,set<string>> & operator*(){
			return *it;
		}

		pair<const string,set<string>> * operator->(){
			return &(*it);
		}

		friend class Traductor;
	};

	/**
	 * @brief Devuelve un iterador que apunta a la primera palabra del idioma origen
	 * 	  que tiene como traducción la palabra @c word.
	 * @param word  Palabra del idioma destino.
	 * @return  Devuelve un iterador que apunta a la primera palabra del idioma origen
	 * 	   que tiene como traducción la palabra @c word.
	 */
	iterator begin(const string & word) {
		iterator i;

		i.dest_word = word;
		i.it = datos.begin();
		i.final = datos.end();

		if (i.it!=i.final && !i.es_traduccion()) // Si la primera palabra no es la que buscamos, buscamos la siguiente
			++i;

		return i;
	}

	iterator end(const string & word) {
		iterator i;

		i.dest_word = word;
		i.it = datos.end();
		i.final = datos.end();

		return i;
	}
};



/**
 * @brief Función principal.
 * @return  Devuelve 0 si todo se ejecuta correctamente.
 * 	     Devuelve 1 si hay algún error.
 *
 * 	     **No es necesario**. Solo está hecho para poder probar el iterador en una función main().
 * 	     En el examen, no se haría.
 *
 * 	     Crea un Traductor a partir de un vector de pares de strings y prueba el iterador.
 * 	     Imprime por pantalla las palabras del idioma origen que tienen como traducción
 * 	     la palabra @c "flor".
 */
int main(){
	vector<pair<string,string> > d1;
	// Vector de pares de strings que formarán el Traductor
	d1.emplace(d1.end(),"hello","hola");
	d1.emplace(d1.end(),"hi","hola");
	d1.emplace(d1.end(),"hey","hola");
	d1.emplace(d1.end(),"flower","flor");
	d1.emplace(d1.end(),"blossom","flor");
	d1.emplace(d1.end(),"blossom","florecer");
	d1.emplace(d1.end(),"posy","flor");
	d1.emplace(d1.end(),"posy","ramillete de flores");
	d1.emplace(d1.end(),"orange","naranjo");
	d1.emplace(d1.end(),"orange","naranja");
	Traductor T(d1);

	Traductor::iterator it;
	for (it=T.begin("flor"); it!=T.end("flor");++it){
		cout<<"Palabra origen "<<it->first<<" Palabras destino: " ;
		for (auto it2=it->second.begin(); it2!=it->second.end();++it2){
			cout<<*it2<<" ";
		}
		cout<<endl;
	}
}