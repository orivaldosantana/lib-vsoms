/* 
 * File:   BasicNeuralNetwork.cpp
 * Author: oriva
 * 
 * Created on 14 de Outubro de 2014, 11:00
 */

#include "BasicNeuralNetwork.h"

BasicNeuralNetwork::BasicNeuralNetwork() {
    edges = new std::list<Edge*>;
    nodos = new std::list<Nodo*>;
    epoch = 0; 
    nodeCount = 0; 
    maxEpoch = MAXINT; 
    maxSize = MAXINT; 
    currentIt = MAXINT; 
    
    
}

BasicNeuralNetwork::BasicNeuralNetwork(const BasicNeuralNetwork& orig) {

}

BasicNeuralNetwork::~BasicNeuralNetwork() {
    delete edges;
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

void BasicNeuralNetwork::addNeuron(Nodo* node) {

    if (!node->isInserted()) {
        nodos->push_back(node);
        node->setInserted(true);
        nodeCount++;
    }
}

void BasicNeuralNetwork::addEdge(Nodo* a, Nodo* b) {
    if (!a->isNeighbor(b)) {
        Edge* w = new Edge(0, a, b, "");
        a->addEdge(w);
        b->addEdge(w);
        a->addNeighbor(b);
        b->addNeighbor(a);
        edges->push_back(w);
    }
}

std::list<Edge*>* BasicNeuralNetwork::getEdges() {
    return edges;
}

std::list<Nodo*>* BasicNeuralNetwork::getNodes() {
    return nodos;
}

Nodo* BasicNeuralNetwork::getLastNeuron() {
    return nodos->back();
}

int BasicNeuralNetwork::getAmountEdges() {
    return edges->size();
}

int BasicNeuralNetwork::getAmountNeurons() {
    return nodos->size();
}

int BasicNeuralNetwork::getNodeCount() {
    return nodeCount.count;
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
    for (auto itN = nodos->begin(); itN != nodos->end(); itN++) {
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
    std::list<Nodo*>* neurons = getNodes();
    for (auto itN = neurons->begin(); itN != neurons->end(); itN++) {
        (*itN)->print();
    }
}

void BasicNeuralNetwork::printNodos(){
    std::cout << "Nodos: " << std::endl;
    for (auto itN = nodos->begin(); itN != nodos->end(); itN++) {
        std::cout << (*itN)->getLabel() << ": " << (*itN)->toString() << std::endl; 
    }
    std::cout << std::endl; 
}

void BasicNeuralNetwork::saveTxtNodos(std::string fileName ){
    std::string fullName = "/tmp/"+fileName+Utils::int2string(epoch)+ ".txt"; 
    std::ofstream file(fullName.c_str());
    
    file << nodos->size(); 
    if ( nodos->size() > 0 ) 
        file << " " << (*(nodos->begin()))->getSize() << std::endl; 
    else 
        file << " 0" << std::endl; 
    for (auto itN = nodos->begin(); itN != nodos->end(); itN++) {
        file << (*itN)->toString() << std::endl; 
    }
    file.close();  
    
}

void BasicNeuralNetwork::printNeighbors(){
    std::cout << "Neighbor Lists: " << std::endl;
    for (auto itN = nodos->begin(); itN != nodos->end(); itN++) {
        (*itN)->printNeigbors(); 
    }
    std::cout << std::endl; 
}




void BasicNeuralNetwork::removeEdge(Nodo* a, Nodo* b) {
    Edge* w = a->getCommomEdge(b);
    if (w != NULL) {
        a->removeEdge(w);
        b->removeEdge(w);
        a->removeNeighbor(b);
        b->removeNeighbor(a);
        edges->remove(w);
    }
}

void BasicNeuralNetwork::saveGraph(std::string fileName ){
    std::ofstream file(fileName.c_str());
    file << "graph G { " << std::endl;
    std::list<Edge*>* edges = getEdges();
    std::list<Edge*>::iterator itW = edges->begin();
    while (itW != edges->end()) {
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

void BasicNeuralNetwork::toJson(std::string fileName) {

    nlohmann::json jsonFile;


    getNodesJson(jsonFile);
    getEdgesJson(jsonFile);   

    jsonFile["properties"]["nodeCount"] = nodeCount.count;  
    jsonFile["properties"]["epoch"] = epoch; 
    jsonFile["properties"]["maxEpoch"] = maxEpoch; 
    jsonFile["properties"]["maxSize"] = maxSize; 
    jsonFile["properties"]["currentIt"] = currentIt; 

    
    
    saveJson(jsonFile, fileName);

}

void BasicNeuralNetwork::connectEdge(Nodo* a, Nodo* b, double v, string label) {
    if (!a->isNeighbor(b)) {
        Edge* e =  new Edge(v, a, b, label);
        a->addEdge(e);
        b->addEdge(e);
        a->addNeighbor(b);
        b->addNeighbor(a);
        edges->push_back(e);
    }

}

void BasicNeuralNetwork::getNodesJson(nlohmann::json& jsonFile) {
    for (auto itN = nodos->begin(); itN != nodos->end(); itN++) {
        jsonFile["node"].push_back((*itN)->toJson());

    }
}

void BasicNeuralNetwork::getEdgesJson(nlohmann::json& jsonFile) {

    for (auto itE = edges->begin(); itE != edges->end(); itE++) {
        //(*itE)->print();
        jsonFile["edge"].push_back((*itE)->toJson());
    }

}

void BasicNeuralNetwork::saveJson(nlohmann::json& jsonFile, std::string fileName) {
    ofstream file;
    file.open(fileName, ios::out);

    file << jsonFile << std::endl;
}


