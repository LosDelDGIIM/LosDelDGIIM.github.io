/**
 * @file UnionFind.h
 * @author Arturo Olivares Martos
 * @brief Implementación de la estructura de datos Union-Find para enteros
 */

#include <vector>
#include <iostream>

/**
 * @brief Clase que implementa la estructura de datos Union-Find para enteros
 * 
 */
class UnionFind{

private:
    struct Nodo{
        int representante;
        int padre;
        int hijo;
    };
    
    const static int SIN_PADRE = -1;
    const static int SIN_HIJO = -2;

    std::vector<Nodo> nodos;
    std::vector<int> ult_conjunto;   // Vector que almacena el índice del último nodo de cada conjunto

public:

    /**
     * @brief Constructor de la clase UnionFind.
     * 
     * @param n Número de nodos
     * @post Crea una estructura de datos Union-Find con n nodos, inicializados sin padres ni hijos
     * @note Eficiencia: O(n)
     */
    UnionFind(int n);

    /**
     * @brief Método para encontrar el representante (primer elemento) del conjunto al que pertenece el nodo x
     * 
     * @param x Nodo
     * @return Representante del conjunto al que pertenece el nodo x
     * @note Eficiencia: O(1)
     */
    inline int find_primero(int x){
        return nodos[x].representante;
    }

    /**
     * @brief Método para encontrar el último elemento del conjunto al que pertenece el nodo x
     * 
     * @param x Nodo
     * @return Último elemento del conjunto al que pertenece el nodo x
     * @note Eficiencia: O(1)
     */
    inline int find_ultimo(int x){
        return ult_conjunto[find_primero(x)];
    }


    /**
     * @brief Método para unir los conjuntos a los que pertenecen los nodos x e y
     * 
     * @param x Nodo
     * @param y Nodo
     * 
     * @param invierte_x Indica si se quiere invertir el orden de los nodos del conjunto al que pertenece x.
     * @param invierte_y Indica si se quiere invertir el orden de los nodos del conjunto al que pertenece y.
     * @post Los conjuntos a los que pertenecen los nodos x e y quedan unidos
     * 
     * @note Eficiencia: O(n)
     */
    void union_(int x, int y, bool invierte_x = false, bool invierte_y = false);


    /**
     * @brief Clase iteradora para recorrer los hijos de un nodo
     * 
     */
    class Iterator{
        private:
            UnionFind* uf;      // Puntero a la clase UnionFind
            int id_nodo_actual; // Índice del nodo actual
        public:

            /**
             * @brief Constructor de la clase UnionFind::Iterator
             * 
             * @param uf Puntero a la clase UnionFind
             * @param id_nodo Índice del nodo actual
             */
            Iterator(UnionFind* uf, int id_nodo){
                this->uf = uf;
                this->id_nodo_actual = id_nodo;
            }

            /**
             * @brief Constructor sin parámetros de la clase UnionFind::Iterator
             * @post Crea un iterador inválido. Apunta a nullptr y no tiene hijo
             * 
             */
            Iterator(): Iterator(nullptr, SIN_HIJO){}

            /**
             * @brief Sobrecarga del operador de desreferenciación
             * 
             * @return int Índice del nodo actual
             */
            int operator*(){ return id_nodo_actual; }

            /**
             * @brief Sobrecarga del operador de incremento. Avanza al siguiente hijo
             * 
             * @return Iterator&  Referencia al iterador del siguiente hijo
             */
            Iterator& operator++(){
                id_nodo_actual = uf->nodos[id_nodo_actual].hijo;
                return *this;
            }

            /**
             * @brief Sobrecarga del operador de decremento. Retrocede al padre
             * 
             * @return Iterator&  Referencia al iterador del padre
             */
            Iterator& operator--(){
                id_nodo_actual = uf->nodos[id_nodo_actual].padre;
                return *this;
            }

            /**
             * @brief Sobrecarga del operador de comparación de desigualdad
             * 
             * @param it Iterador con el que se compara
             * @return true Si los iteradores son distintos
             * @return false Si los iteradores son iguales
             */
            bool operator!=(const Iterator& it){
                return id_nodo_actual != it.id_nodo_actual;
            }
    };
    
    /**
     * @brief Método para obtener un iterador que recorre el conjunto al que pertenece el nodo x
     * 
     * @param x Nodo
     * @return Iterator Iterador que apunta al representante del conjunto al que pertenece el nodo x
     */
    inline Iterator begin(int x){
        return Iterator(this, find_primero(x));
    }

    /**
     * @brief Método para obtener un iterador que apunta al final del conjunto al que pertenece el nodo x
     * 
     * @param x Nodo
     * @return Iterator  Iterador que apunta al final del conjunto al que pertenece el nodo x
     */
    inline Iterator end(int x){
        return Iterator(this, SIN_HIJO);
    }


    /**
     * @brief Clase iteradora para recorrer el conjunto al que pertenece un nodo desde el último nodo
     * 
     */
    class ReverseIterator{
        private:
            Iterator it;
        public:

            /**
             * @brief Constructor de la clase UnionFind::ReverseIterator
             * 
             * @param uf  Puntero a la clase UnionFind
             * @param id_nodo  Índice del nodo actual
             */
            ReverseIterator(UnionFind* uf, int id_nodo){
                it = Iterator(uf, id_nodo);
            }

            /**
             * @brief Constructor sin parámetros de la clase UnionFind::ReverseIterator
             * @post Crea un iterador inválido. Apunta a nullptr y no tiene padre
             * 
             */
            ReverseIterator() : ReverseIterator(nullptr, SIN_PADRE){}

            /**
             * @brief Sobrecarga del operador de desreferenciación
             * 
             * @return int Índice del nodo actual
             */
            int operator*(){
                return *it;
            }

            /**
             * @brief Sobrecarga del operador de incremento. Retrocede al padre
             * 
             * @return ReverseIterator&  Referencia al iterador del padre
             */
            ReverseIterator& operator++(){
                --it;
                return *this;
            }

            /**
             * @brief Sobrecarga del operador de decremento. Avanza al siguiente hijo
             * 
             * @return ReverseIterator&  Referencia al iterador del siguiente hijo
             */
            ReverseIterator& operator--(){
                ++it;
                return *this;
            }

            /**
             * @brief Sobrecarga del operador de comparación de desigualdad
             * 
             * @param rit Iterador con el que se compara
             * @return true Si los iteradores son distintos
             * @return false Si los iteradores son iguales
             */
            bool operator!=(const ReverseIterator& rit){
                return it != rit.it;
            }
    };
    
    /**
     * @brief Método para obtener un iterador que recorre el conjunto al que pertenece el nodo x desde el final
     * 
     * @param x  Nodo
     * @return ReverseIterator  Iterador que apunta al último nodo del conjunto al que pertenece el nodo x
     */
    inline ReverseIterator rbegin(int x){
        return ReverseIterator(this, find_ultimo(x));
    }

    /**
     * @brief Método para obtener un iterador que apunta al final del conjunto al que pertenece el nodo x
     * 
     * @param x Nodo
     * @return ReverseIterator  Iterador que apunta al final del conjunto al que pertenece el nodo x
     */
    inline ReverseIterator rend(int x){
        return ReverseIterator(this, SIN_PADRE);
    }


    /**
     * @brief Método para obtener el conjunto al que pertenece el nodo x
     * 
     * @param x Nodo de un conjunto
     * @return vector<vector<int>> Vector que representa el conjunto al que pertenece el nodo x
     * 
     * @note Eficiencia: O(n)
     */
    std::vector<int> obtenerConjunto(int x);


    friend std::ostream &operator<<(std::ostream &os, const UnionFind &uf);

private:
    /**
     * @brief Método para invertir el orden de los nodos del conjunto al que pertenece x
     * 
     * @param x  Nodo cuyo conjunto se quiere invertir
     * @param nuevo_representante Nuevo representante del conjunto que se está invirtiendo 
     */
    void reverse(int x, int nuevo_representante);
};

/**
 * @brief Sobrecarga del operador de inserción en flujo de salida para la clase UnionFind
 * 
 * @param os Flujo de salida
 * @param uf Clase UnionFind
 * @return std::ostream&  Referencia al flujo de salida
 */
std::ostream &operator<<(std::ostream &os, const UnionFind &uf);