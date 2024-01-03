/**
 * @file 3. Pilas.Sombrero.cpp
 * @author Arturo Olivares Martos
 * @date 31/10/2023
 * @doc
 * 		- **Asignatura:** Estrucutras de Datos.
 * 		- **Curso Académico:** 2023-24.
 * 		- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
 * 		- **Grupo:** B.
 * 		- **Profesor:** Ignacio Aguilera Martos.
 * 		- **Descripción:** Examen de Prácticas I de la asignatura de Estructuras de Datos.
 * 		- **Duración:** 60 minutos
 * @brief Programa que determina si una pila es sombrero de otra.
 *
 * Tan solo se pide implementar la función sombrero, el resto del código se proporciona.
 *
 * Ejemplo de ejecución:
 * @code{.sh}
 * ./Sombrero 1 2 3 4 5 - 3 4 5
 * p: [1, 2, 3, 4, 5]
 * q: [3, 4, 5]
 * Es sombrero: si
 * @endcode
 */
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <string>

using namespace std;

/*
 * @brief Función que dice si la pila q es sombrero de la pila p.
 * 
 * Se dice que una pila q es sombrero de p
 * si todos los elementos de q están en p, en el mismo orden y en las posiciones más próximas al tope.
 * La pila vacía se considera sobrereo de cualquier pila.
 * @param q pila a comprobar si es sombrero.
 * @param p pila sobre la que comprobaremos si q es sombrero.
 * @return @retval true si es sombrero
 * @return @retval false si no lo es.
 */
bool sombrero(stack<int> p, stack<int> q){

    // Comprobamos que q tiene menos elementos que p, ya que todos los elementos de p deben estar en q
    bool es_sombrero = q.size() <= p.size();

    // Mientras que sea sombrero y no se hayan comprobado ya todos los elementos de q
    while (es_sombrero && !q.empty()){

        // Compruebo el tope y los elimino
        es_sombrero &= q.top() == p.top();
        p.pop();
        q.pop();
    }

    return es_sombrero;
}

/*
 * @brief Función básica para imprimir una pila p. Se recorre toda la pila desde el tope hasta que esta queda vacía
 * imprimiendo en cada paso el tope actual de la pila.
 * @param p Pila que queremos imprimir.
 * @post La pila p no se ve modificada.
 */
void printStack(stack<int> p){
    while(!p.empty()){
        cout << p.top();
        if(p.size()>1)
            cout << ", ";
        p.pop();
    }
    cout << endl;
}

int main(int argc, char* argv[]){
    // Pilas con las que se va a operar
    stack<int> p,q;
    // Booleano para gestionar la entrada
    bool second_stack=false;
    // Ejemplo de entrada 1 2 3 4 5 - 3 4 5 ==> p = <1,2,3,4,5>     q = <3,4,5>
    for(int i = 1; i<argc; ++i){ //                          ^ tope          ^ tope
        // si nos encontramos un - en la entrada es que vamos a cambiar de la primera pila a la segunda
        if(argv[i][0]=='-')
            second_stack=true;
        else{
            if(!second_stack)
                p.push(atoi(argv[i]));
            else
                q.push(atoi(argv[i]));
        }
    }
    // Imprimimos ambas pilas
    cout << "p: ";
    printStack(p);
    cout << "q: ";
    printStack(q);
    // Si es sombrero entonces se sustituye por un si, en otro caso por un no
    string s = sombrero(p,q) ? "si" : "no";
    cout << "Es sombrero: " << s << endl;
}
