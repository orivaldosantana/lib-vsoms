/* 
 * File:   Weight.cpp
 * Author: oriva
 * 
 * Created on 13 de Outubro de 2014, 17:27
 */

#include "Weight.h"


Weight::Weight(const Weight& orig) {
}

Weight::~Weight() {
}

Weight::Weight(double v = 0, Nodo* o = NULL, Nodo* t = NULL, std::string l = "w "){
   value = v;
   pOrigin = o;
   pTarget = t;
   label = l;
}


Nodo* Weight::getAheadNeuron(){
   return pTarget;
}

Nodo* Weight::getBackNeuron(){
   return pOrigin;
}

std::string Weight::getLabel(){
   return label;
}

double Weight::getValue(){
   return value;
}

void Weight::setValue(double v){
   value = v;
}

void Weight::print(){
//   std::cout << pOrigin->getLabel() << " <> " << pTarget->getLabel() ;
}
