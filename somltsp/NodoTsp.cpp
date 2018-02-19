/* 
 * File:   NodoTsp.cpp
 * Author: oriva
 * 
 * Created on 17 de Outubro de 2014, 15:23
 */

#include "NodoTsp.h"

NodoTsp::NodoTsp(const Sample& s, std::string l, std::string d) {
    information = s.information;
    label = l;
    description = d;
    neighbors = new std::list<Nodo*>;
    enabled = false; 
    winsCount = 0;
    inserted = false;
    markedToUpdate = false; 
    enabled = true;
    markedToRemove = false; 
}

NodoTsp::NodoTsp(const NodoTsp& orig) {
}

NodoTsp::~NodoTsp() {
}



void NodoTsp::resetNeuronWins() {
    this->winsCount = 0; 
}

/**
 * Decrementa o contador de vitórias, caso o nodo não vença por três épocas 
 * consecutivas então este nodo é marcado para ser removido. Este mecanismo de 
 * contegem sucessivas funciona concomitantemente com o método de decremento. 
 * Quando un nodo ganha a contagem negativa é zerada.  
 */
void NodoTsp::decreaseWins(){
   winsCount = winsCount -1;
   if (winsCount == -3)
       markedToRemove = true;
}

int NodoTsp::getWinsCount() const {
    return winsCount;
}

/**
 * Incrementa o contador de vitórias. Quando o contandor for negativo ele é colocado 
 * em 0 e o incremento prossegue normalmente. 
 */
void NodoTsp::increaseWins(){
    if (winsCount < 0)
        winsCount = 0; 
    winsCount = winsCount +1;
}

void NodoTsp::printStatus(){
    std::cout << label << ": ";
    if (enabled)
        std::cout << "enabled, ";
    else
        std::cout << "desabled, ";
    if (markedToUpdate)
        std::cout << "do up, ";
    else
        std::cout << "not up, ";
    if (markedToRemove)
        std::cout << "do remove, ";
    else
        std::cout << "not remove, ";
    std::cout << " wins("<<winsCount<<")"; 
    std::cout << std::endl;
}

bool NodoTsp::isEnabled(){
    return enabled;
}
 
bool NodoTsp::isMarkedToUpdate(){
    return markedToUpdate; 
}
bool NodoTsp::isMarkedToRemove(){
    return markedToRemove; 
}

void NodoTsp::setMarkedToUpdate(bool up){
    markedToUpdate = up; 
}

void NodoTsp::setEnabled(bool e){
    enabled = e; 
}




