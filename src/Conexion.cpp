/* 
 * File:   Conexion.cpp
 * Author: oriva
 * 
 * Created on 13 de Outubro de 2014, 17:27
 */

#include "Conexion.h"

Conexion::Conexion(const Conexion& orig) {
}

Conexion::~Conexion() {
}


Conexion::Conexion(){
   one = NULL;
   two = NULL;
   distance = std::numeric_limits<double>::max();
}

Conexion::Conexion(Nodo* n1, Nodo* n2, float d){
   setValues(n1,n2,d);
}

void Conexion::setValues(Nodo* n1, Nodo* n2, float d){
   one = n1;
   two = n2;
   distance = d;
}

void Conexion::setDistance(double distance) {
    this->distance = distance;
}

double Conexion::getDistance() const {
    return distance;
}

void Conexion::setTwo(Nodo* two) {
    this->two = two;
}

Nodo* Conexion::getTwo() const {
    return two;
}

void Conexion::setOne(Nodo* one) {
    this->one = one;
}

Nodo* Conexion::getOne() const {
    return one;
}
