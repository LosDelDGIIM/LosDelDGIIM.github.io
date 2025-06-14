/*
NOMBRE Y APELLIDOS:
DNI: 
GRUPO DE PRACTICAS:
*/

#ifndef SERVICIO_H
#define SERVICIO_H

#include <iostream>
using namespace std;

struct Pos {
    int x, y;
};

string toString(const Pos & p);

void imprimirArray(const Pos v[], int n);

float distancia(const Pos & p, const Pos & k);

bool cubierto(const Pos & p, const Pos & k, int R);

void distanciaPromedio(const Pos clientes[], int nClientes, const Pos & antena, int radioAntena, int & nCubiertos, float & distanciaMedia);

void servidosPorAntena(const Pos clientes[], int nClientes, const Pos & antena, int radioAntena, Pos* & aux, int & nAux);

void datosCliente(Pos antenas[], int nAntenas, const Pos & cliente, Pos* & antenaProxima, float & distanciaAntenaProxima);

#endif