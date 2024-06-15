/**
 * @file Arco.h
 * @author Arturo Olivares Martos
 * @brief Implementación de un arco de un grafo
 */
#ifndef ARCO_H
#define ARCO_H
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @brief Clase que representa un arco de un grafo
 * 
 * @note Los arcos se comparan en función de su peso * 
 */
class Arco{
public:
    int origen, destino;       // Vértices que une el arco
    double peso;       // Peso del arco

public:

    /**
     * @brief Constructor de la clase Arco
     * 
     * @param origen Origen del arco
     * @param destino Destino del arco 
     * @param peso Peso del arco
     */
    Arco(int origen, int destino, double peso) : origen(origen), destino(destino), peso(peso){}

    // Sobrecarga de operadores de relación en función del peso
    bool operator<(const Arco &a) const{
        return peso < a.peso;
    }
    bool operator>(const Arco &a) const{
        return peso > a.peso;
    }
    bool operator==(const Arco &a) const{
        return *this < a && a < *this;
    }
    bool operator<=(const Arco &a) const{
        return !(*this > a);
    }
    bool operator>=(const Arco &a) const{
        return !(*this < a);
    }

    friend class Grafo;

    friend ostream &operator<<(ostream &os, const Arco &a);
};

/**
 * @brief Sobrecarga del operador de salida para la clase Arco
 * 
 * @param os Flujo de salida
 * @param a Arco a imprimir
 * @return ostream&  Referencia al flujo de salida
 */
ostream &operator<<(ostream &os, const Arco &a){
    os << a.origen << " -> " << a.destino << " : " << a.peso;
    return os;
}

#endif