/**
 * @file UnionFind.cpp
 * @author Arturo Olivares Martos
 * @brief Implementación de la estructura de datos Union-Find para enteros
 */

#include <vector>
#include "UnionFind.h"

UnionFind::UnionFind(int n){
    nodos.resize(n);
    ult_conjunto.resize(n);

    // Inicializamos los nodos sin padres ni hijos
    for(int i = 0; i < n; i++){
        nodos[i].representante = i;
        nodos[i].padre = SIN_PADRE;
        nodos[i].hijo = SIN_HIJO;

        ult_conjunto[i] = i;
    }
}

void UnionFind::reverse(int x, int nuevo_representante){

    int primero_X = find_primero(x);
    int ultimo_X = find_ultimo(x);
    
    auto it = begin(x), it2 = it;
    while(it != end(x)){
        // Es necesario avanzar it antes de modificarlo, ya que al cambiar el hijo por el padre se perdería la referencia al siguiente nodo
        // Por tanto, se guarda una copia en it2 y se avanza it
        it2 = it;
        ++it;
        
        // Además de actualizar el representante, invertimos el orden de los nodos
        nodos[*it2].representante = nuevo_representante;
        std::swap(nodos[*it2].padre, nodos[*it2].hijo);
    }
    nodos[ultimo_X].padre = SIN_PADRE;     // Se quedará el primer nodo sin padre
    nodos[primero_X].hijo = SIN_HIJO;      // Se quedará el último nodo sin hijo

    // Actualizamos el último nodo del conjunto
    ult_conjunto[nuevo_representante] = primero_X;
}



void UnionFind::union_(int x, int y, bool invierte_x, bool invierte_y){
    
    // Si los nodos x e y pertenecen al mismo conjunto, no hacemos nada
    if(find_primero(x) == find_primero(y)) return;

    // Obtenemos los primeros y últimos nodos de los conjuntos a los que pertenecen x e y
    // Para evitar problemas con la inversión de los nodos, se hace antes de invertir
    int primero_X = find_primero(x);
    int ultimo_X = find_ultimo(x);
    int primero_Y = find_primero(y);
    int ultimo_Y = find_ultimo(y);
    
    // Tan solo invertimos x, no unimos
    if (invierte_x){
        std::swap(primero_X, ultimo_X);
        reverse(x, find_ultimo(x));
    }
    
    // Tan solo invertimos (si es el caso) y, y cambiamos el representante. No unimos aún.
    if (invierte_y){
        std::swap(primero_Y, ultimo_Y);
        reverse(y, find_primero(x));
    }
    
    else{ // No invertimos pero modificamos el representante
        int representante_X = find_primero(x);
        // Actualizamos el representante del conjunto Y
        for(auto it=begin(y); it!=end(y); ++it)
            nodos[*it].representante = representante_X;
    }

    nodos[primero_Y].padre = ultimo_X;
    nodos[ultimo_X].hijo = primero_Y;


    ult_conjunto[find_primero(x)] = ultimo_Y;
}


std::vector<int> UnionFind::obtenerConjunto(int x){

    std::vector<int> conjunto;

    // Recorremos el conjunto al que pertenece el nodo x
    for(auto it = begin(x); it != end(x); ++it)
        conjunto.push_back(*it);

    return conjunto;
}



std::ostream &operator<<(std::ostream &os, const UnionFind &uf){
    os << "Estructura de datos Union-Find:" << std::endl;
    for(size_t i = 0; i < uf.nodos.size(); i++){
        os << "- Nodo " << i << ": ";
        os << "Representante: " << uf.nodos[i].representante << " ";
        os << "Padre: " << uf.nodos[i].padre << " ";
        os << "Hijo: " << uf.nodos[i].hijo << std::endl;
    }

    return os;
}