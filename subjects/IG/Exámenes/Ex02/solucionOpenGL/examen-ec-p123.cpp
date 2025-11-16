#include "examen-ec-p123.h"

Ejercicio1::Ejercicio1 () { // Poner vértices, y triángulos tanteando para que quede como en el examen
    vertices = {
        {0, 0, 1}, // 0
        {1, 0, 1}, // 1
        {1, 0, 0}, // 2
        {2, 1, 1}, // 3
        {2, 0, 0}, // 4
        {3, 0, 1}, // 5
        {3, 1, 0}, // 6
        {4, 0, 1}, // 7
        {4, 0, 0}, // 8
        {5, 0, 0}  // 9
    };

    triangulos = {
        {0, 1, 2},
        {1, 2, 4},
        {1, 4, 6},
        {1, 6, 3},
        {3, 6, 5},
        {5, 6, 8},
        {5, 8, 9},
        {5, 9, 7}
    };

    col_ver = { // Se nos dice que tome un color gris, luego deben ser valores flotanes más cercanos a 0.0 que a 1.0
        {0.2,0.2,0.2}, // 0
        {0.2,0.2,0.2}, // 1
        {0.2,0.2,0.2}, // 2
        {1,1,1},       // 3
        {0.2,0.2,0.2}, // 4
        {0.2,0.2,0.2}, // 5
        {1,1,1},       // 6
        {0.2,0.2,0.2}, // 7
        {0.2,0.2,0.2}, // 8
        {0.2,0.2,0.2}  // 9
    };
}

Ejercicio2::Ejercicio2 (unsigned n) { // Hay que replicar un patrón. Si reusas vértices, 100% de la nota, si no, 80% de la nota.
    if (n < 1) {
        std::cout << "Para la clase Ejercicio 2 el parametro n debe ser mayor o igual que 1." << std::endl;
        exit(1);
    }

    // ¿Podría ponerse assert ( n >= 1)?

    // Como sabemos que n debe ser mayor o igual que 1, podemos definir la primera réplica

    // Defino los vértices de forma que los 4 primeros, estén a la izquierda de la réplica,
    // y los 4 últimos a la derecha, para poder reutilizarlos con más facilidad.
    vertices = {
        {0, 0, 0}, // 0
        {0, 0, 1}, // 1
        {0, 1, 2}, // 2
        {0, 0, 3}, // 3
        {0, 0, 4}, // 4
        {1, 0, 0}, // 5
        {1, 0, 1}, // 6
        {1, 1, 2}, // 7
        {1, 0, 3}, // 8
        {1, 0, 4}  // 9
    };

    triangulos = {
        {0, 1, 5}, {1, 5, 6}, // Primer rectángulo plano
        {1, 2, 6}, {2, 6, 7}, // Primer rectángulo inclinado
        {2, 3, 7}, {3, 7, 8}, // Segundo rectángulo inclinado
        {3, 4, 8}, {4, 8, 9}  // Segundo rectángulo plano
    };

    // Ya tenemos la primera réplica, ahora debemos hacer un bucle e ir añadiendo los vértices y triángulos correspondientes
    float x=2, z=0; // Variables auxiliares
    int contador = 5;
    // Cabe destacar que como ya tenemos una réplica, inicializamos i a 1
    for (unsigned i = 1; i < n; i++) {
        // Sabemos que los últimos 4 vértices son los vértices de la izquierda de esta nueva réplica
        // por lo que debemos añadir los siguientes 4 de la izquierda
        vertices.push_back({x, 0, 0});
        vertices.push_back({x, 0, 1});
        vertices.push_back({x, 1, 2});
        vertices.push_back({x, 0, 3});
        vertices.push_back({x, 0, 4});

        // Asignamos los triángulos
        for (unsigned j=0; j<4; j++) {
            triangulos.push_back({contador+j, contador+j+1, contador+j+5});
            triangulos.push_back({contador+j+1, contador+j+5, contador+j+6});
        }

        x++;
        contador += 5;
    }
}
                        // Ancho    Alto de los dos cubos
Ejercicio3::Ejercicio3 (float w, float h) {
    using namespace glm;

    NodoGrafoEscena *cubo = new NodoGrafoEscena();
    NodoGrafoEscena *cuboArriba = new NodoGrafoEscena();

    cuboArriba->agregar(translate(vec3(0, 2*h, 0)));
    cuboArriba->agregar(scale(vec3(w, h, w)));
    cuboArriba->agregar(translate(vec3(2.0, 0.0, 0.0)));
    unsigned int_rot_tras_cub_arriba = cuboArriba->agregar(rotate(0.0f, vec3(0.0, 0.0, 1.0)));
    rot_tras_cub_arriba = cuboArriba->leerPtrMatriz(int_rot_tras_cub_arriba);

    cuboArriba->agregar(translate(vec3(-1.0, 1.0, 1.0)));
    cuboArriba->agregar( new Cubo() );

    cubo->agregar(cuboArriba);

    cubo->agregar(scale(vec3(w, h, w)));
    unsigned int_esc_cub_abajo = cubo->agregar(scale(vec3(1.0, 1.0, 1.0)));
    esc_cub_abajo = cubo->leerPtrMatriz(int_esc_cub_abajo);
    cubo->agregar(translate(vec3{1.0, 1.0, 1.0})); // Pongo el cubo en el (0,0,0)
    // TODO: Escalar el cubo a w y h
    cubo->agregar( new Cubo() );

    ponerColor({1.0f, 1.0f, 1.0f});
    agregar(cubo);
}

unsigned Ejercicio3::leerNumParametros() const {
    return 2; // Tenemos dos grados de libertad
}

void Ejercicio3::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {
    using namespace glm;

    const float amplitud = 0.5f * sin(t_sec) + 0.8;
    const float angulo = 2.5f * sin(t_sec);

    const float amplitud2 = sin(t_sec);
    switch (iParam)
    {
    case 0: 
        *rot_tras_cub_arriba = translate(vec3(0.0f, amplitud2 - 0.4f, 0.0f)) * rotate(-abs(angulo), vec3(0.0, 0.0, 1.0));
        break;
    case 1: // Animación para escalar el prisma
        *esc_cub_abajo = scale(vec3(1.0, amplitud, 1.0));
        break;
    }
}
