/*
NOMBRE Y APELLIDOS: 
DNI: 
GRUPO DE PRACTICAS: 
 */

#include <cmath>
#include <iostream>
#include "servicio.h"

using namespace std;

string toString(const Pos & p) {
    string s = "(" + to_string(p.x) + "," + to_string(p.y) + ")";

    return s;
}

void imprimirArray(const Pos v[], int n) {
    for (int i = 0; i < n - 1; i++)
        cout << toString(v[i]) << ", ";

    cout << toString(v[n - 1]) << endl;
}

float distancia(const Pos & p, const Pos & k) {
    float tmp = (p.x - k.x) * (p.x - k.x) + (p.y - k.y) * (p.y - k.y);
    return sqrt(tmp);
}

bool cubierto(const Pos & p, const Pos & k, int R) {
    return (distancia(p, k) < R);
}

void distanciaPromedio(const Pos clientes[], int nClientes, const Pos & antena, int radioAntena, int & nCubiertos, float & distanciaMedia) {
    nCubiertos = 0;
    float sumaDistancias = 0;
    for (int i = 0; i < nClientes; i++) {
        if (cubierto(clientes[i], antena, radioAntena)) {
            nCubiertos++;
            sumaDistancias += distancia(clientes[i], antena);
        }
    }
    distanciaMedia = sumaDistancias / nCubiertos; // REVISIÓN: esto falla si nCubiertos es igual a 0, se debería hacer una comprobación.
}

void reducirArray(Pos* & arr, int util) {
    Pos* aux = new Pos[util];
    for (int i = 0; i < util; i++) {
        aux[i] = arr[i];
    }
    delete [] arr;
    arr = aux;
}

void servidosPorAntena(const Pos clientes[], int nClientes, const Pos & antena, int radioAntena, Pos* & aux, int & nAux) {
    if (aux != nullptr) {
        delete [] aux;
    }

    aux = new Pos[nClientes];
    nAux = 0;

    for (int i = 0; i < nClientes; i++) {
        if (cubierto(clientes[i], antena, radioAntena)) {
            aux[nAux++] = clientes[i];
        }
    }

    reducirArray(aux, nAux);
}

// Suponemos que nAntenas es mayor o igual que 1
void datosCliente(Pos antenas[], int nAntenas, const Pos & cliente, Pos* & antenaProxima, float & distanciaAntenaProxima) {
    // encontrar antena con distancia mínima a cliente

    antenaProxima = antenas;
    distanciaAntenaProxima = distancia(*antenaProxima, cliente);
    
    for (int i = 1; i < nAntenas; i++) {
        float distanciaAntenaActual = distancia(cliente, antenas[i]);
        if (distanciaAntenaActual < distanciaAntenaProxima) {
            distanciaAntenaProxima = distanciaAntenaActual;
            antenaProxima = antenas + i;
        }
    }
}