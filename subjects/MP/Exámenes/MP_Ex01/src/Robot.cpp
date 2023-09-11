/* 
 * File:   Robot.cpp
 * Author: Silvia Acid y Andrés Cano
 * 
 * Created on 28 April 2023, 13:05
 */

#include <cmath>

#include "Robot.h"

using namespace std;

Robot::Robot(){
    _x = _y = 0;
    _id = 0;
    _carga = 0;
}
Robot::Robot(long id){
    _x = _y = 0;
    _id = id;
    _carga = 0;
}
Robot::Robot(long id, float x, float y, double carga){
    _x = x;
    _y = y;
    _id = id;
    if (esPositivo(carga))
       _carga = carga;
    else _carga = 0.0;
}
long Robot::getId() const{
    return _id;
}
float Robot::getX() const{
    return _x;
}
float Robot::getY() const{
    return _y;
}
double Robot::getCarga()const{
    return _carga;
}
void Robot::set(long id, float x, float y, double carga){
    _x = x;
    _y = y;
    _id = id;
    if (esPositivo(carga))
       _carga = carga;
    else _carga = 0;
}

string Robot::toString() const{
      string ss = to_string(getId()) + "->(" + to_string(getX()) + "," + to_string(getY())
              + "," + to_string(getCarga()) + "),";
      return ss;
}

float Robot::distancia(const Robot &rb) const{
    float x = fabs(this->getX() - rb.getX());
    float y = fabs(this->getY() - rb.getY());

    return (sqrt(x * x + y * y));
}

