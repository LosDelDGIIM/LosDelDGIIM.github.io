/*
NOMBRE Y APELLIDOS:
DNI: 
GRUPO DE PRACTICAS:
 */

#include <iostream>
#include <cmath>
#include "servicio.h"

using namespace std;

int main() {
    // declare los arrays Ant (para las antenas), Cli (para los clientes), Aux (para resultados)
    // tama�os nCli, nAnt, nAux, respectivamente;

    int nCli, nAnt, radioAntena;
    int nAux = 0;


    // implemente la lectura de datos

    cin >> nCli;
    cin >> nAnt;
    cin >> radioAntena;

    Pos* cli = new Pos[nCli];
    Pos* ant = new Pos[nAnt];
    Pos* aux = nullptr;

    for (int i = 0; i < nCli; i++) {
        Pos pos;
        cin >> pos.x;
        cin >> pos.y;
        cli[i] = pos;
    }

    for (int i = 0; i < nAnt; i++) {
        Pos pos;
        cin >> pos.x;
        cin >> pos.y;
        ant[i] = pos;
    }

    // mostrar por pantalla los puntos leidos
    cout << "Conjunto de clientes: " << endl;
    imprimirArray(cli, nCli);

    cout << "\n\nConjunto de antenas: " << endl;
    imprimirArray(ant, nAnt);


    // para cada antena, muestre la distancia promedio a los clientes cubiertos
    float distanciaMedia = 0;
    int nClientesCubiertos = 0;

    for (int i = 0; i < nAnt; i++) {
        // LLAMAR FUNCION distanciaPromedio(.... Ant[i] .....);
        distanciaPromedio(cli, nCli, ant[i], radioAntena, nClientesCubiertos, distanciaMedia);

        cout << "Antena " << toString(ant[i]) << ", Nro Clientes: " << nClientesCubiertos << " Dist.Prom: " << distanciaMedia << endl;
    }




    // funcion servidosPorAntena con la antena Ant[0]
    // Los resultados se guardan en el array Aux con tama�o nAux

    servidosPorAntena(cli, nCli, ant[0], radioAntena, aux, nAux);
    cout << "\nClientes de antena: " << toString(ant[0]) << ": ";
    imprimirArray(aux, nAux);

    // funcion servidosPorAntena con la antena Ant[1]
    // Los resultados se guardan en el array Aux con tama�o nAux


    servidosPorAntena(cli, nCli, ant[1], radioAntena, aux, nAux);
    cout << "\nClientes de antena: " << toString(ant[1]) << ": ";
    imprimirArray(aux, nAux);

    //llamada a la funcion datosCliente utilizando el cliente Cli[0]


    Pos * antenaProxima = nullptr;
    float distanciaAntenaProxima = 0;
    datosCliente(ant, nAnt, cli[0], antenaProxima, distanciaAntenaProxima);
    cout << "\nCliente: " << toString(cli[0]) << " Dist: " << to_string(distanciaAntenaProxima) << " Antena: " << toString(*antenaProxima) << endl;


    delete [] ant;
    delete [] cli;
    delete [] aux;
    return 0;
}
