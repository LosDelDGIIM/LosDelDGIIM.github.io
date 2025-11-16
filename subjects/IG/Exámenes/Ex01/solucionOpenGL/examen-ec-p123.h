#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP

#include "malla-ind.h"
#include "grafo-escena.h"

class Ejercicio1 : public MallaInd {
    public:
        Ejercicio1();
};

class Ejercicio2 : public MallaInd {
    public:
        Ejercicio2(unsigned int n);
};

class Ejercicio3 : public NodoGrafoEscena
{
    protected:
        glm::mat4 *pm_rot = nullptr;
        glm::mat4 *pm_scal = nullptr;
        
    public:
        Ejercicio3(float w, float h);
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
};

#endif
