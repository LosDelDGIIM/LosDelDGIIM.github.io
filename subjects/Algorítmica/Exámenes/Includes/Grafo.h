/**
 * @file Grafo.h
 * @author Arturo Olivares Martos
 * @brief Implementación de la estructura de datos Grafo
 */
#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include <iostream>
#include <iomanip>
#include "Arco.h"

using namespace std;

/**
 * @brief Clase que representa un grafo
 * 
 */
class Grafo{
private:

    // Constante que indica que dos nodos no están conectados
    static constexpr double NO_CONECTADO = -1;

    // Matriz de adyacencia del grafo
    vector<vector<double>> matriz_adyacencia;
    
    
public:
    /**
     * @brief Constructor por defecto de la clase Grafo
     * 
     * Construye una matriz de adyacencia vacía
     * 
     * @note Eficiencia: O(1)
     */
    Grafo ()=default;

    /**
     * @brief Constructor de la clase Grafo con un número de nodos
     * 
     * @param n Número de nodos del grafo
     * @param valor_inicial Valor inicial de la matriz de adyacencia
     * 
     * @note Eficiencia: O(n^2) siendo n el número de nodos del grafo
     */
    Grafo(int n, double valor_inicial = NO_CONECTADO){
        matriz_adyacencia.clear();
        matriz_adyacencia.resize(n, vector<double>(n, valor_inicial));
    }

    /**
     * @brief Constructor de la clase Grafo con una matriz de adyacencia 
     * 
     * @param matriz_adyacencia Matriz de adyacencia del grafo
     * 
     * @note Eficiencia: O(n^2) siendo n el número de nodos del grafo
     */
    Grafo(const vector<vector<double>> &matriz_adyacencia) : matriz_adyacencia(matriz_adyacencia){}

    /**
     * @brief Constructor de la clase Grafo con una matriz de enteros
     * 
     * @param matriz Matriz de enteros que representa el grafo
     */
    Grafo(const vector<vector<int>> &matriz) : Grafo(matriz.size()){
        // Copiamos los valores de la matriz de enteros a la matriz de dobles
        for (int i = 0; i < matriz.size(); ++i){
            for (int j = 0; j < matriz.size(); ++j){
                if (matriz[i][j] != NO_CONECTADO){
                    matriz_adyacencia[i][j] = matriz[i][j];
                }
            }
        }
    }

    /**
     * @brief Constructor de la clase Grafo a partir de un vector de arcos
     * 
     * @param arcos Vector con los arcos del grafo 
     * @param n  Número de nodos del grafo
     * 
     * @note Eficiencia: O(n^2) siendo n el número de nodos del grafo
     */
    Grafo(const vector<Arco> &arcos, int n): Grafo(n){
        for (const Arco &arco : arcos){
            setArco(arco);
        }
    }


    /**
     * @brief Devuelve el número de nodos del grafo
     * 
     * @return size_t  Número de nodos del grafo
     * 
     * @note Eficiencia: O(1)
     */
    size_t getNumNodos() const{
        return matriz_adyacencia.size();
    }

    /**
     * @brief Obtiene las aristas del grafo
     * 
     * @return vector<Arco>  Vector con los arcos del grafo
     * 
     * @note Eficiencia: O(n^2) siendo n el número de nodos del grafo
     */
    virtual vector<Arco> getArcos() const{
        vector<Arco> arcos;

        for (int i = 0; i < getNumNodos(); ++i){
            for (int j = 0; j < getNumNodos(); ++j){
                if (conectados(i, j)){
                    arcos.push_back(Arco(i, j, matriz_adyacencia[i][j]));
                }
            }
        }

        return arcos;
    }

    /**
     * @brief Establece un arco en el grafo
     * 
     * @param arco Arco a establecer
     * 
     * @note Eficiencia: O(1)
     */
    virtual void setArco(const Arco &arco){
        matriz_adyacencia[arco.origen][arco.destino] = arco.peso;
    }

    /**
     * @brief Informa si dos nodos están conectados
     * 
     * @param origen Nodo origen
     * @param destino Nodo destino
     * @return true Si hay un arco desde origen a destino
     * @return false Si no hay un arco desde origen a destino
     * 
     * @note Eficiencia: O(1)
     */
    bool conectados(int origen, int destino) const{
        return matriz_adyacencia[origen][destino] != NO_CONECTADO;
    }

    /**
     * @brief Devuelve el valor de la constante que indica que dos nodos no están conectados
     * 
     * @return double  Valor de la constante que indica que dos nodos no están conectados
     */
    static double charNoConectado(){
        return NO_CONECTADO;
    }


    /**
     * @brief Calcula la suma de los pesos de los arcos de un grafo
     * 
     * @param arcos  Vector con los arcos de los que se quiere calcular la suma de los pesos
     * @return double  Suma de los pesos de los arcos
     */
    double sumaPesos() const{
        vector<Arco> arcos = getArcos();
        double suma = 0;
        for (const Arco &arco : arcos){
            suma += arco.peso;
        }

        return suma;
    }



    friend ostream &operator<<(ostream &os, const Grafo &G);

protected:
    /**
     * @brief Obtiene el peso de un arco
     * 
     * @param origen Nodo origen
     * @param destino Nodo destino
     * @return double Peso del arco desde origen a destino
     */
    double getPeso(int origen, int destino) const{
        return matriz_adyacencia[origen][destino];
    }
};


/**
 * @brief Sobrecarga del operador de salida para la clase Grafo
 * 
 * @param os Flujo de salida
 * @param G Grafo a imprimir
 * @return ostream&  Referencia al flujo de salida
 * 
 * @note Eficiencia: O(n^2) siendo n el número de nodos del grafo
 */
ostream &operator<<(ostream &os, const Grafo &G){
    int ANCHO = 3;
    const char C_NO_CONECTADO = 'X';

    for ( int i=0; i<G.getNumNodos(); ++i){
        for (int j=0; j<G.getNumNodos(); ++j){
            if (G.conectados(i, j))
                os << setw(ANCHO) << G.getPeso(i, j);
            else
                os << setw(ANCHO) << C_NO_CONECTADO;
        }
        os << endl;
    }

    return os;
}



#endif