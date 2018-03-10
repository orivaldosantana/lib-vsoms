/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Edge.h
 * Author: samuel
 *
 * Created on 13 de Dezembro de 2017, 23:40
 */

#ifndef EDGE_H
#define EDGE_H
#include "Nodo.h"
#include "json.hpp"

class Nodo;

class Edge {
    
public:
    Edge();
    Edge(const Edge& orig);
    virtual ~Edge();

    Edge(double v, Nodo* o, Nodo* t, std::string l);
    Edge( nlohmann::json& jsonFile );
    Nodo* getAheadNeuron();
    Nodo* getBackNeuron();
    std::string getLabel();
    double getValue();
    void setValue(double v);
    void print();
    void incrementValue();
    void setpOrigin(Nodo*& _pOrigin);
    void setpTarget(Nodo*& _pTarget);
    nlohmann::json toJson();
private:
    double value;
    Nodo* pOrigin;
    Nodo* pTarget;
    std::string label;

};

#endif /* EDGE_H */

