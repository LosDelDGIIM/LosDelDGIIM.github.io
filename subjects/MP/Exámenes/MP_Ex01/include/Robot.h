/* 
 * File:   Robot.h
 * Author: Silvia Acid y Andrés Cano
 *
 * Created on 28 April 2023, 13:05
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <string>
class Robot{
public:
    /**
     * @brief Constructor sin parámetros
     * Inicializa a 0 los datos id, x, y, y carga
     */
    Robot();
    
    /**
     * Constructor 
     * Inicializa a 0 los datos x, y, carga. Inicializa id con el parámetro 
     * proporcionado
     * @param id Valor identificador
     */    
    Robot(long id);
    
    /**
     * Constructor 
     * Inicializa los datos id, x, y y carga con los argumentos proporcionados.
     * @param id Valor identificador. Si el parámetro no es positivo,
     * la carga se inicializa a 0.
     * @param x coordenada x
     * @param y coordenada y
     * @param valor Valor de carga
     */
    Robot(long id, float x, float y, double carga=0.0);

    /**
     * @brief Devuelve el id del robot
     * @return el id del robot
     */
    long getId() const;
    
    /**
     * @brief Devuelve la coordenada x del robot
     * @return la coordenada x del robot
     */
    
    float getX() const;
    
    /**
     * @brief Devuelve la coordenada y del robot
     * @return la coordenada y del robot
     */
    float getY() const;
    
    /**
     * @brief Devuelve la carga del robot
     * @return la carga del robot
    */
    double getCarga() const;

    /**
     * @brief Actualiza los datos del robot. La carga solo es actualiza con el
     * valor proporcionado si es mayor o igual a 0; en caso contrario se
     * pone a 0.
     * @param id Identificador
     * @param x Coordenada x
     * @param y Coordenada y
     * @param carga Carga
     */
    void set(long id, float x, float y, double carga=0.0);
 
    /**
     * @brief Devuelve un string con la información completa del robot
     * @return string
    */
    std::string toString() const;
    /**
     * @brief Calcula la distancia entre el robot implícito
     * y el robot proporcionado.
     * El cálculo de la distancia es simétrica y positiva.
     * @param rb robot hasta el que se quiere medir la distancia. 
     * @return La distancia calculada
     */
    float distancia(const Robot &rb) const;
    
private:

    bool esPositivo(double v) {
        return v >= 0;
    }
    long _id;
    float _x, _y;
    double _carga;
};


#endif /* ROBOT_H */

