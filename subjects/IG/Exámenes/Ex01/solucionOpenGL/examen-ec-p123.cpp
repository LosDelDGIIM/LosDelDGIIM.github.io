#include "examen-ec-p123.h"

Ejercicio1::Ejercicio1 () { 
    vertices = {
       {0.0, 0.0, 0.5},
       {0.0, 0.0, 1.5},
       {1.25, 0.0, 0.5},
       {1.25, 0.0, 1.5},
       {1.75, 0.0, 1.5},
       {2.0, 0.0, 1.5},
       {2.25, 0.0, 1.5},
       {2.5, 0.0, 1.5},
       {1.75, 0.5, -0.0},
       {2.0, 0.5, -0.0},
       {2.25, 0.5, -0.0},
       {2.5, 0.5, -0.0}
    };

    triangulos = {
       {0, 1, 3},
       {0, 2, 3},
       {2, 3, 4},
       {2, 8, 4},
       {4, 5, 8},
       {8, 9, 5},
       {5, 6, 9},
       {9, 6, 10},
       {6, 7, 10},
       {10, 11, 7}
    };

    col_ver = { 
       {0.2, 0.2, 0.2},
       {0.2, 0.2, 0.2},
       {0.2, 0.2, 0.2},
       {0.2, 0.2, 0.2},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0}
    };
}

Ejercicio2::Ejercicio2 (unsigned int n) { 

    using namespace glm;
    assert(n >= 1);

    vertices = {
       {0.0, 0.0, 0.5},
       {0.0, 0.0, 1.5},
       {1.25, 0.0, 0.5},
       {1.25, 0.0, 1.5},
       {1.75, 0.0, 1.5},
       {2.0, 0.0, 1.5},
       {2.25, 0.0, 1.5},
       {2.5, 0.0, 1.5},
       {1.75, 0.5, -0.0},
       {2.0, 0.5, -0.0},
       {2.25, 0.5, -0.0},
       {2.5, 0.5, -0.0}
    };

    triangulos = {
       {0, 1, 3},
       {0, 2, 3},
       {2, 3, 4},
       {2, 8, 4},
       {4, 5, 8},
       {8, 9, 5},
       {5, 6, 9},
       {9, 6, 10},
       {6, 7, 10},
       {10, 11, 7}
    };

    col_ver = { 
       {0.2, 0.2, 0.2},
       {0.2, 0.2, 0.2},
       {0.2, 0.2, 0.2},
       {0.2, 0.2, 0.2},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0},
       {1.0, 1.0, 1.0}
    };

    for(unsigned int i = 1; i < n; i++){
        float angulo = i*360.f/n;
        mat3 rotacion = rotate(radians(angulo), vec3(0.0, 0.0, 1.0));
        for(int j = 2; j < 12; j++){
            vertices.push_back(rotacion * vertices.at(j));
            if(j == 3 || j == 4){
                col_ver.push_back(vec3(0.2, 0.2, 0.2));
            }else{
                col_ver.push_back(vec3(1.0, 1.0, 1.0));
            }
                
        }   
    }


    int contador = 12;

    for (unsigned i = 1; i < n; i++) {
        triangulos.push_back({0, contador+1, contador});
        triangulos.push_back({0, 1, contador+1});
        triangulos.push_back({contador, contador+1, contador+2});
        triangulos.push_back({contador, contador+2, contador+6});
        triangulos.push_back({contador+6, contador+2, contador+3});
        triangulos.push_back({contador+6, contador+7, contador+3});
        triangulos.push_back({contador+8, contador+7, contador+4});
        triangulos.push_back({contador+7, contador+4, contador+3});
        triangulos.push_back({contador+7, contador+8, contador+4});
        triangulos.push_back({contador+4, contador+8, contador+5});
        triangulos.push_back({contador+9, contador+8, contador+5});
        

        contador += 10;
    }
    

}
                        
Ejercicio3::Ejercicio3 (float w, float h) {

    using namespace glm;

    assert(w>1 && h<0.3);

    NodoGrafoEscena *cubo = new NodoGrafoEscena();
    NodoGrafoEscena *cuboarriba = new NodoGrafoEscena();
    cuboarriba->agregar(translate(vec3(0, 5*h, 0)));
    unsigned int_pm_rot_prisma = cuboarriba->agregar(rotate(0.0f, vec3(0.0, 0.0, 1.0)));
    pm_rot = cuboarriba->leerPtrMatriz(int_pm_rot_prisma);
    cuboarriba->agregar(translate(vec3(w/2 - 0.2, 0.0, w/4-0.5)));
    cuboarriba->agregar(translate(vec3(0.0, 0.2, 0.0)));
    cuboarriba->agregar(scale(vec3(0.2, 1.0, 0.2)));
    cuboarriba->agregar( new Cubo() );


    
    unsigned int_pm_scal_prisma = cubo->agregar(scale(vec3(1.0, 1.0, 1.0)));
    pm_scal = cubo->leerPtrMatriz(int_pm_scal_prisma);
    cubo->agregar(scale(vec3(w, h, w)));
    cubo->agregar(translate(vec3{1.0, 1.0, 1.0}));
    cubo->agregar(new Cubo());

    cubo->agregar(cuboarriba);
    agregar(cubo);


}

unsigned Ejercicio3::leerNumParametros() const {
    return 2; // Dos grados de libertad
}

void Ejercicio3::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {
    using namespace glm;

    const float amplitud = 0.5f * sin(t_sec) + 1.0;
    const float angulo = 2*M_PI*(t_sec);
    switch (iParam)
    {
    case 0: // Animación para escalar el prisma
        *pm_scal = scale(vec3(1.0, amplitud, 1.0));
        break;
    case 1:
        *pm_rot = scale(vec3(1.0, 1/amplitud, 1.0))*rotate(abs(angulo), vec3(0.0, 1.0, 0.0));
        break;
    }
}
