/**
 * @file GrafoNoDirigido.h
 * @author Arturo Olivares Martos
 * @brief Implementación de la estructura de datos de un Grafo No Dirigido
 */
#ifndef GRAFONODIRIGIDO_H
#define GRAFONODIRIGIDO_H

#include "Grafo.h"

/**
 * @brief Clase que representa un grafo no dirigido
 */
class GrafoNoDirigido : public Grafo{
public:

    // Para que se puedan usar los constructores de Grafo
    using Grafo::Grafo;

    /**
     * @copydoc Grafo::getArcos
     * 
     * Sobreescribe el método de la clase Grafo, para no obtener los arcos repetidos
     */
    vector<Arco> getArcos() const override{
        vector<Arco> arcos;
        for (int i = 0; i < getNumNodos(); i++){
            // En el bucle interior está la diferencia, ya que solo recorremos la mitad de la matriz
            for (int j = i+1; j < getNumNodos(); j++){
                if (conectados(i, j))
                    arcos.push_back({i, j, getPeso(i, j)});
            }
        }
        return arcos;
    }

    /**
     * @copydoc Grafo::setArco
     * 
     * Sobreescritura del método de la clase Grafo, para añadir el arco en ambas direcciones
     */
    virtual void setArco(const Arco &arco) override{
        Grafo::setArco(arco);
        Grafo::setArco(Arco(arco.destino, arco.origen, arco.peso));
    }
};
#endif