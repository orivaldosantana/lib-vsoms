/* 
 * File:   BasicNeuralNetwork.cpp
 * Author: oriva
 * 
 * Created on 14 de Outubro de 2014, 11:00
 */

#include "BasicNeuralNetwork.h"

BasicNeuralNetwork::BasicNeuralNetwork() {
    weights = new std::list<Weight*>;
    nodos = new std::vector<Nodo*>;
    nodeDrawRadius = 0.012; 
}

BasicNeuralNetwork::BasicNeuralNetwork(const BasicNeuralNetwork& orig) {

}

BasicNeuralNetwork::~BasicNeuralNetwork() {
    delete weights;
    delete nodos;
}

bool BasicNeuralNetwork::addNeuron(Nodo* n, Sample* s) {
    if (!n->isInserted()) {
        n->setFeatures(s);
        n->setInserted(true);
        nodos->push_back(n);
        nodeCount++;
        return true;
    }
    return false;
}

void BasicNeuralNetwork::addWeight(Nodo* a, Nodo* b) {
    if (!a->isNeighbor(b)) {
        Weight* w = new Weight(0, a, b, "");
        a->addWeight(w);
        b->addWeight(w);
        a->addNeighbor(b);
        b->addNeighbor(a);
        weights->push_back(w);
    }
}

std::list<Weight*>* BasicNeuralNetwork::getWeights() {
    return weights;
}

std::vector<Nodo*>* BasicNeuralNetwork::getNodes() {
    return nodos;
}

Nodo* BasicNeuralNetwork::getLastNeuron() {
    return nodos->back();
}

int BasicNeuralNetwork::getAmountWeights() {
    return weights->size();
}

int BasicNeuralNetwork::getAmountNeurons() {
    return nodos->size();
}

int BasicNeuralNetwork::getNodeCount() {
    return nodeCount;
}

void BasicNeuralNetwork::loadDataSet(std::string fileName){
    dataSet.loadDataFromFile(fileName); 
}

void BasicNeuralNetwork::putNoiseInData(float sigma, int repetitions){
    dataSet.putNoise(sigma,repetitions); 
    dataSet.generateRandomIndex(); 
}

Nodo* BasicNeuralNetwork::findBestNeuron(Sample* s) {
    Nodo* bestN = NULL;
    double bestDistance = std::numeric_limits<double>::max();
    // find best neuron
    for (std::vector<Nodo*>::iterator itN = nodos->begin(); itN < nodos->end(); itN++) {
        double dist = (*itN)->distance(*s);
        if (dist < bestDistance) {
            bestDistance = dist;
            bestN = *itN;
        }
    }
    return bestN;
}

void BasicNeuralNetwork::printConections() {
    std::cout << "Conections: " << std::endl;
    std::vector<Nodo*>* neurons = getNodes();
    for (std::vector<Nodo*>::iterator itN = neurons->begin(); itN != neurons->end(); itN++) {
        (*itN)->print();
    }
}

void BasicNeuralNetwork::printNodos(){
    std::cout << "Nodos: " << std::endl;
    for (std::vector<Nodo*>::iterator itN = nodos->begin(); itN < nodos->end(); itN++) {
        std::cout << (*itN)->getLabel() << ": " << (*itN)->toString() << std::endl; 
    }
    std::cout << std::endl; 
}

void BasicNeuralNetwork::saveTxtNodos(std::string fileName ){
    std::string fullName = "/tmp/"+fileName+Utils::int2string(epoch)+ ".txt"; 
    std::ofstream file(fullName.c_str());
    
    file << nodos->size(); 
    if ( nodos->size() > 0 ) 
        file << " " << (*nodos)[0]->getSize() << std::endl; 
    else 
        file << " 0" << std::endl; 
    for (std::vector<Nodo*>::iterator itN = nodos->begin(); itN < nodos->end(); itN++) {
        file << (*itN)->toString() << std::endl; 
    }
    file.close();  
    
}

void BasicNeuralNetwork::printNeighbors(){
    std::cout << "Neighbor Lists: " << std::endl;
    for (std::vector<Nodo*>::iterator itN = nodos->begin(); itN < nodos->end(); itN++) {
        (*itN)->printNeigbors(); 
    }
    std::cout << std::endl; 
}




void BasicNeuralNetwork::removeWeight(Nodo* a, Nodo* b) {
    Weight* w = a->getCommomWeight(b);
    if (w != NULL) {
        a->removeWeight(w);
        b->removeWeight(w);
        a->removeNeighbor(b);
        b->removeNeighbor(a);
        weights->remove(w);
    }
}

void BasicNeuralNetwork::saveGraph(std::string fileName ){
    std::ofstream file(fileName.c_str());
    file << "graph G { " << std::endl;
    std::list<Weight*>* weights = getWeights();
    std::list<Weight*>::iterator itW = weights->begin();
    while (itW != weights->end()) {
        Nodo* n1 = (*itW)->getAheadNeuron();
        file << n1->getLabel() << " -- ";
        Nodo* n2 = (*itW)->getBackNeuron();       
        file << n2->getLabel() << ";" << std::endl;
        itW++;
    }
    file << " } " << std::endl;
    file.close(); 
}

void BasicNeuralNetwork::savePdfGraph(std::string fileName){
    std::string tempGraphName = "temp_graph.dot"; 
    saveGraph(tempGraphName); 
    std::string command("neato -Tpdf ");
    command.append(tempGraphName);
    command.append(" -o ");
    command.append(fileName);
    command.append(".pdf");
    if (system(NULL)) {
        system(command.c_str());
    }
}

int BasicNeuralNetwork::getMaxEpoch() const {
    return maxEpoch;
}

void BasicNeuralNetwork::setMaxEpoch(int maxEpoch) {
    this->maxEpoch = maxEpoch;
}

void BasicNeuralNetwork::setNodeDrawRadius(int nodeDrawRadius) {
    this->nodeDrawRadius = nodeDrawRadius;
}

double BasicNeuralNetwork::getNodeDrawRadius() const {
    return nodeDrawRadius;
}

void BasicNeuralNetwork::setMaxSize(int maxSize) {
    this->maxSize = maxSize;
}

int BasicNeuralNetwork::getMaxSize() const {
    return maxSize;
}
