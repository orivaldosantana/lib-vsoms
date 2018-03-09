    /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Age.cpp
 * Author: samuel
 * 
 * Created on 13 de Dezembro de 2017, 23:40
 */

#include "Edge.h"

Edge::Edge() {
}

Edge::Edge(const Edge& orig) {
}

Edge::~Edge() {
}
//double v = 0, Nodo* o = NULL, Nodo* t = NULL, std::string l = "w "

Edge::Edge(double v = 0, Nodo* o = NULL, Nodo* t = NULL, std::string l = "age") {
    value = v;
    pOrigin = o;
    pTarget = t;
    label = l;
}
Edge::Edge(nlohmann::json& jsonFile){
    Nodo* _pOrigin  = new Nodo (jsonFile["pOrigin"]);
    Nodo* _pTarget  = new Nodo (jsonFile["pTarget"]);
    
    
    
    value   = jsonFile["value"];
    pOrigin = _pOrigin;
    pTarget = _pTarget;
    label   =  jsonFile["label"];
    
   
    
    
}

Nodo* Edge::getAheadNeuron(){
    return pTarget;
}

Nodo* Edge::getBackNeuron(){
     return pOrigin;
}

std::string Edge::getLabel(){
    return label;
}

double Edge::getValue(){
    return value;
}
    
void Edge::print(){
    
     std::cout << pTarget->getLabel() << "---Ege: " << value << " ---" << pOrigin->getLabel() << ", ";
    
}
void Edge::setValue(double v){
    value = v;
}

void Edge::incrementValue(){
    value++;
}

nlohmann::json Edge::toJson(){
    nlohmann::json edge;
    edge["value"] = value;
    edge["pOrigin"] = pOrigin->toJson();
    edge["pTarget"] = pTarget->toJson();
    edge["label"] = label;
    
    return edge;
    
}

void Edge::setpOrigin(Nodo*& _pOrigin){
    pOrigin = _pOrigin;
    
}

void Edge::setpTarget(Nodo*& _pTarget){
    pTarget = _pTarget;
}