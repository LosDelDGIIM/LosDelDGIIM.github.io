/**
 * @file 2023_Febrero_Ej4.cpp
 *
 * @brief Resolución del ejercicio 5 de la Convocatoria Oridinaria
 * 	  de Febrero de 2023 de la asignatura Estructura de Datos (ED).
 *
 * - Asignatura: Estructura de Datos.
 * - Curso Académico: 2022-23.
 * - Grado: Común a todos los grados.
 * - Descripción: Ejercicio 5 - Convocatoria Ordinaria de Febrero de 2023.
 *
 * @details Enunciado:  (1 punto)
 *
 * 	  Implementar una función:
 * 	  @code
 * 	  bool tiene_suma_constante (set<int> & s, int M);
 * 	  @endcode
 *
 * 	  ue dado un conjunto de enteros s y un entero M, devuelva true si existe un subconjunto
 * 	  de elementos enteros de s cuyos valores sumen exactamente M.
 *
 * 	  Ejemplo:
 * 	  s={1,2,3,4,5,6};
 * 	  	tiene_suma_constante(s,15) devolvería true
 * 	  	tiene_suma_constante(s,22) devolvería false
 *
*/

#include <iostream>
#include <set>
using namespace std;

/**
 * @brief Comprueba si existe un subconjunto de elementos enteros de s cuyos valores sumen exactamente M.
 * @param s Conjunto de enteros.
 * @param M Entero.
 * @retval true si existe un subconjunto de elementos enteros de s cuyos valores sumen exactamente M.
 * @retval false si no existe un subconjunto de elementos enteros de s cuyos valores sumen exactamente M.
 */
bool tiene_suma_constante (set<int> & s, int M){

	// Caso base
	if (M==0)
		return true;

	// Caso base
	if (s.size()==0)
		return false;

	// Caso base
	if (*s.begin()>M) // Si el primer elemento es mayor que M, todos son mayores que M (está ordenado)
		return false;

	// Caso base
	if (s.find(M)!=s.end())
		return true;


	// Caso recursivo
	for (auto it=s.begin(); it!=s.end(); ++it){

		// Guardo el elemento
		int elem = *it;

		// Lo borro
		s.erase(it);

		// Llamo recursivamente
		bool tiene_suma = tiene_suma_constante(s, M-elem);

		// Lo vuelvo a insertar
		s.insert(elem);

		// Si tiene suma, devuelvo true
		if (tiene_suma)
			return true;
	} // for elemento in S

	return false;
}

/**
 * @brief Función main de prueba del programa.
 *
 * **No es necesario**. Solo está hecho para poder probarlo en una función main().
 * En el examen, no se haría.
 */
int main(){
	set<int>s={6,2,3,4,5,1, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	if (tiene_suma_constante(s,10)) cout<<"Si existe un subconjunto "<<endl;
	else cout<<"No existe un subconjunto "<<endl;
}