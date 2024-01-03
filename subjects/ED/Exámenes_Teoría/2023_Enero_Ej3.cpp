/**
 * @file 2023_Enero_Ej3.cpp
 *
 * @brief Resolución del ejercicio 3 de la Convocatoria Oridinaria
 * 	  de Enero de 2023 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2022-23.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 3 - Convocatoria Ordinaria de Enero de 2023.
 *
 * @details Enunciado:  (1 punto)
 *
 * 	  Implementar una función
 * 	  @code
 * 	  void intercambia_sec (list<int>& L);
 * 	  @endcode
 *
 * 	  que dada una lista @c L, intercambie el grupo de los primeros elementos consecutivos impares
 * 	  por el siguiente grupo de elementos consecutivos pares de principio a final de la lista.
 *
 * 	  No pueden usarse estructuras de datos auxiliares.
 *
 * 	  Ejemplo:
 * 	  @code
 * 	  L = {1,2,4,5,6,8,7,9,13,2,9}
 * 	  @endcode
 *
 * 	  @c intercambia_sec(L) debe devolver:
 * 	  @code
 * 	  L = {2, 4, 1, 6, 8, 5, 2, 7, 9, 13,9}
 * 	  @endcode
 *
 * 	  Como explicación del ejemplo, el primer grupo de elementos impares es {1} y el siguiente grupo
 * 	  de elementos pares es {2,4}. Por tanto, se intercambian los dos grupos y se obtiene la lista
 * 	  {2,4,1,5,6,8,7,9,13,2,9}.
 * 	  El siguiente grupo de elementos impares es {5} y el siguiente grupo de elementos pares es {6,8}.
 * 	  Por tanto, se intercambian los dos grupos y se obtiene la lista {2,4,1,6,8,5,7,9,13,2,9}.
 * 	  El siguiente grupo de elementos impares es {7,9,13} y el siguiente grupo de elementos pares es {2}.
 * 	  Por tanto, se intercambian los dos grupos y se obtiene la lista {2,4,1,6,8,5,2,9,13,7,9}.
 * 	  Como ya no hay más grupos de elementos pares, se termina la ejecución.
*/

#include <iostream>
#include <list>
using namespace std;

/**
 * @brief Intercambia los grupos de elementos impares por los grupos de elementos pares.
 * @param L Lista de enteros.
 * @post @c L contiene los grupos de elementos impares intercambiados por los grupos de elementos pares.
 */
void intercambia_sec (list<int>& L){

	auto it = L.begin();
	while(it != L.end()){

		// Busca el primer impar
		if (*it % 2 == 1){
			auto it_impar_start = it;


			// Busca el primer par
			auto it_par_start = it;
			do{
				++it_par_start;
			}while((it_par_start != L.end()) && (*it_par_start % 2 != 0));
			it = it_par_start; // Actualizar it.

			// Si hay algún par
			if (it_par_start != L.end()){
				// Busca el siguiente al último par (el primer impar)
				auto it_par_end = it_par_start;
				do{
					++it_par_end;
				}while((it_par_start != L.end()) &&(*it_par_end % 2 == 0));


				// Intercambiar los grupos de elementos impares y pares
				L.splice(it_impar_start, L, it_par_start, it_par_end);

				it = it_par_end; // Actualizar it.
			} // if (it_par_start != L.end()
		} // if (*it % 2 == 1)
		else ++it;
	} // while(it != L.end())
}

/**
 * @brief Programa principal para probar la función @c intercambia_sec.
 * **No es necesario**. Solo está hecho para poder probar el iterador en una función main().
 * En el examen, no se haría.
 */
int main(){
	list<int> L = {1,2,4,5,6,8,7,9,13,2,9};
	intercambia_sec(L);
	for (auto it=L.begin();it!=L.end();it++){
		cout << *it << " ";
	}
	cout << endl;
}