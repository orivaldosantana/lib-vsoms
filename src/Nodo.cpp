/* 
 * File:   Nodo.cpp
 * Author: oriva
 * 
 * Created on 13 de Outubro de 2014, 17:15
 */

#include "Nodo.h"
#include <sstream>

Nodo::Nodo(){
    label = "";
    description = "";
    neighbors = new std::list<Nodo*>;
}

Nodo::Nodo(nlohmann::json& jsonFile){
    jsonInformationToVectorInformation(jsonFile["information"]); 
    label = jsonFile["label"];
    description = jsonFile["description"]; 
    inserted = false; 
    winner = false; 
    
} 

Nodo::Nodo(const Nodo& orig) {

}

Nodo::Nodo(const Sample& s, std::string l, std::string d) {
    information = s.information;
    label = l;
    description = d;
    neighbors = new std::list<Nodo*>;
    inserted = false; 
}

Nodo::~Nodo() {
    clear();
}

void Nodo::addNeighbor(Nodo* n) {
    neighbors->push_back(n);
}

void Nodo::addWeight(Weight* iw) {
    weights.push_back(iw);
}

void Nodo::clear() {
    std::list<Weight*>::iterator itW;
    itW = weights.begin();
    while (itW != weights.end()) {
        delete (*itW);
        itW++;
    }
    weights.clear();
}

Weight* Nodo::getCommomWeight(Nodo* n){
   std::list<Weight*>::iterator itW;
   itW = weights.begin();
   while (itW != weights.end())
   {
      if  ((*itW)->getAheadNeuron() == n)  {
         return *itW;
         //delete *itW;
         break;
      }
      else if ((*itW)->getBackNeuron() == n)  {
         return *itW;
         //delete *itW;
         break;
      }
      itW++;
   }
   return NULL;
}

std::string Nodo::getLabel() {
    return label;
}

std::list<Nodo*>* Nodo::getNeighbors() {
    return neighbors;
}

int Nodo::getNeighborsSize() {
    return neighbors->size();
}

double Nodo::getFeature(int i){
    if ( i < information.size() )
        return information.at(i);
    return 0;
}

void Nodo::setInserted(bool b) {
    inserted = b;
}

void Nodo::setFeature(double f, int i){
    if ( i < information.size() )
        information.at(i) = f;
    
}

void Nodo::setFeatures(Sample* s) {
    information = s->information;
}

nlohmann::json Nodo::toJson(){
    nlohmann::json node; 
    
    node["information"] = information; 
    node["label"] = label; 
    node["description"] = description; 
    
    return node; 
} 

bool Nodo::isInserted() {
    return inserted;
}

bool Nodo::isNeighbor(Nodo* n) {
    bool b = false;
    std::list<Weight*>::iterator itW;
    itW = weights.begin();
    while (itW != weights.end()) {
        if ((*itW)->getAheadNeuron() == n) {
            b = true;
            break;
        } else if ((*itW)->getBackNeuron() == n) {
            b = true;
            break;
        }
        itW++;
    }
    return b;
}

void Nodo::print() {
    std::list<Weight*>::iterator itW;
    itW = weights.begin();
    std::cout << label << " : ";
    while (itW != weights.end()) {
        std::cout << (*itW)->getAheadNeuron()->getLabel() << " - " << (*itW)->getBackNeuron()->getLabel() << ", ";
        itW++;
    }
    std::cout << std::endl;
}

/*
std::string Nodo::toString() {
    std:stringstream result;
    for (int i =0; i < information.size(); i++){
        result << information[i];
        result << " ";
    }
    return result.str(); 
}
*/

void Nodo::printNeigbors() {
    std::list<Nodo*>::iterator itN;
    itN = neighbors->begin();
    std::cout << label << ": ";
    while (itN != neighbors->end()) {
        std::cout << (*itN)->getLabel() << ", ";
        itN++;
    }
    std::cout << std::endl;
}

void Nodo::removeNeighbor(Nodo* n) {
    neighbors->remove(n);
}


//Cuidado ao chamar este método pois  Weight faz referência a outro neurônio 
void Nodo::removeWeight(Weight* w) {
    weights.remove(w);
}

void Nodo::updateFeatures(double d, Sample* s) {
    std::vector<double>::iterator itS = s->information.begin();
    for (std::vector<double>::iterator it = information.begin(); (itS != s->information.end())
            and (it != information.end()); it++) {
        *it += d * (*itS - *it);
        itS++;
    }
}

void  Nodo::jsonInformationToVectorInformation(nlohmann::json& jsonFile){
    
    for (nlohmann::json::iterator itJ =  jsonFile.begin() ; itJ !=jsonFile.end(); itJ++){
        double number = (*itJ);
       information.push_back(number);
    }
    
    
}

