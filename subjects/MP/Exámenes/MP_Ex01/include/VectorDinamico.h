/* 
 * File:   VectorDinamico.h
 * Author: Silvia Acid y Andrés Cano
 *
 * Created on 2 de mayo de 2023, 9:36
 */

#ifndef VECTORDINAMICO_H
#define VECTORDINAMICO_H

#include "Robot.h"

bool afectado(const Robot& rt, const Robot& inhibidor, double radio);
void imprimirVector(const Robot* v, int n);
Robot* reservarM(int n);
void liberarM(Robot* &vR2D2);
void agnadeRobot(const Robot& nuevo, Robot* &v, int &tam);
void supervivientes(const Robot* vR2D2, int nR2D2, const Robot* vInhibidor, int nInhibidor, 
        Robot* &vSalida, int&  nSalida, double radio);
void lectura(Robot* &v, int& n);

#endif /* VECTORDINAMICO_H */

