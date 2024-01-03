/**
 * @file 5. Set. Intersección.cpp
 * @author José Juan Urrutia Milán "JJ"
 * @date 21/11/2023
 * @doc
 * 		- **Asignatura:** Estrucutras de Datos.
 * 		- **Curso Académico:** 2023-24.
 * 		- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
 * 		- **Grupo:** A.
 * 		- **Profesor:** José Enrique Cano Ocaña.
 * 		- **Descripción:** Examen de Prácticas II de la asignatura de Estructuras de Datos.
 * 		- **Duración:** 60 minutos
 * 
 * @brief Calcula la intersección de tres conjuntos de una forma determinada, explicada en inter().
 * 
 * Tan solo hay que implementar la función creciente, el resto del código se proporciona.
 *
 * Ejemplo de ejecución:
 * @code{.sh}
 * ./interseccion
 * Conjunto A: 1,2,3,4,5,6
 * Conjunto B: 4,5,7,8,9,10
 * Conjunto C: 5,6,10,11,12,13
 * 
 * Conjunto Resultado: 4,6,10
 * 
 * @endcode
 */

#include <iostream>
#include <set>

using namespace std;
/**
 * @brief Imprime un set<int> por pantalla.
 * 
 * @param Conjunto set<int> a imprimir.
 */
void Imprimir(set<int> Conjunto){

   for(auto it=Conjunto.begin(); it!=Conjunto.end(); ++it)
      cout<< *it <<" ";
   cout << endl << endl;
}

typedef set<int>::iterator iset;

/**
 * @brief Calcula la unión de los siguientes conjuntos:
 * - Los elementos de A intersección con B; pero que no están en C.
 * - Los elementos de A intersección con C; pero que no están en B.
 * - Los elementos de B intersección con C; pero que no están en A.
 * 
 * @param A Primer conjunto a considerar.
 * @param B Segundo conjunto a considerar.
 * @param C Tercer conjunto a considerar.
 * @param Resul Conjunto resultante.
 */
void inter(set<int> &A, set<int> &B, set<int> &C, set<int> &Resul){

	set<int> aux = A;
	Resul.clear();
	
	iset it;

	// En aux se guardan los elementos de A\cup (B\setminus A).
	//		Es decir, los elementos de A y los de B que no están en A.
	//
	// En result, se guardan los comunes a A y B.
	for(it = B.begin(); it != B.end(); ++it){

		if(aux.count(*it) != 0)
			Resul.insert(*it);

		else
			aux.insert(*it);
		
	}
	

	// Si uno de los comunes a A y B está en C, se elimina de result.
	// Si uno de los de C está en A o B, se añade a result.
	for(it = C.begin(); it != C.end(); ++it){

		if(Resul.count(*it) != 0)
			Resul.erase(*it);
		
		else if(aux.count(*it) != 0)
			Resul.insert(*it);
		
	}
	
}


int main(){
   set<int> A={1,2,3,4,5,6};
   set<int> B={4,5,7,8,9,10};
   set<int> C={5,6,10,11,12,13};
   set<int> Result;
   
   cout<<"Conjunto A: ";
   Imprimir(A);
   cout<<"Conjunto B: ";
   Imprimir(B);
   cout<<"Conjunto C: ";
   Imprimir(C);
   
   inter(A,B,C,Result);
   
   cout<<"Conjunto Resultado: ";
   Imprimir(Result);
}

