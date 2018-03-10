/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeGwr.cpp
 * Author: samuel
 * 
 * Created on 28 de Janeiro de 2018, 14:55
 */

#include "NodeGwr.h"

NodeGwr::NodeGwr() {
}

NodeGwr::NodeGwr(const NodeGwr& orig) {
}

NodeGwr::~NodeGwr() {
}

NodeGwr::NodeGwr(const Sample& s, std::string l, double _firingCounter, std::string d) {
    information = s.information;
    label = l;
    description = d;
    inserted = false;
    neighbors = new std::list<Nodo*>;
    firingCounter = _firingCounter;
    winner = false;


}
NodeGwr::NodeGwr(Sample*& s, std::string l , double _firingCounter, std::string d ){
    information = s->information;
    label = l;
    description = d;
    inserted = false;
    neighbors = new std::list<Nodo*>;
    firingCounter = _firingCounter;
    winner = false;
    
    
}





bool NodeGwr::isConnectedWitth(NodeGwr*& node, Edge*& edge) {

    for (auto itE = edges.begin(); itE != edges.end(); itE++) {
        if ((*itE)->getAheadNeuron() == node || (*itE)->getBackNeuron() == node) {
            edge = (*itE);
            //edge->print();
            return true;
        }
    }
    return false;

}

bool NodeGwr::getWinnerStatus() {
    return winner;
}

void NodeGwr::isTheWinner(bool _winner) {
    winner = _winner;

}
double NodeGwr::getFiringCounter(){
    return firingCounter;
}
 
void NodeGwr::setFiringCounter(double _firingCounter){
    firingCounter = _firingCounter;
}

void NodeGwr::decreaseTheFiringCounter(double f){
    firingCounter -= f;
}

void NodeGwr::incrementTheTheFiringCounter(double f){
     firingCounter += f;
}
 
 void NodeGwr::removeTime(){
     information.pop_back();
    
 }
 
 nlohmann::json NodeGwr::toJson(){
       nlohmann::json node;

    node["information"] = information;
    node["label"] = label;
    node["description"] = description;
    node["firingCounter"] = firingCounter;
    //node["threeRepresentation"] = 0; não precisa 
    //getEdges_json(node); falha

    return node;
     
 }
