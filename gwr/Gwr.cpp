/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gwr.cpp
 * Author: samuel
 * 
 * Created on 28 de Janeiro de 2018, 14:55
 */

#include "Gwr.h"
#include "NodeGwr.h"
#include "Counter.h"

Gwr::Gwr() {
    eW = 0.02;
    eN = 0.06;
    aMax = 50;
    currentNode.count = 0;
    currentIteration = 1;
    alphaT = 0.90;
    alphaB = 1.05;
    alphaN = 1.05;
    tauB = 3.33;
    tauN = 14.3;
    firingThreshold = 0.1;
    sT = 1;
    epoch = -1;
    h0 = 1;
}

Gwr::Gwr(const Gwr& orig) {
}

Gwr::~Gwr() {
}

void Gwr::init() {
    Sample randomPosition;



    randomPosition = gerateRandomPosition();
    NodeGwr* firstNode = new NodeGwr(randomPosition, currentNode.label);
    addNeuron(firstNode);

    randomPosition = gerateRandomPosition();
    NodeGwr* secondNode = new NodeGwr(randomPosition, currentNode.label);
    addNeuron(secondNode);


}







Sample Gwr::gerateRandomPosition() {

    Sample position;
    double a;
    double maxIntensity = 1000000;
    double intensity = 0.01 * maxIntensity;
    std::vector<double> info;
    int sampleSize = dataSet.getSampleSize();

    for (int i = 0; i < sampleSize; i++) {

        a = (rand() % int(intensity)) / maxIntensity;



        info.push_back(a);
    }
    position.setFeatures(info);

    return position;
}

void Gwr::initialize(std::string fileData) {
    //load input file
      dataSet.loadDataFromFile(fileData);
    //dataSet.loadDataFromCsvFile(fileData);
    // dataSet.show();
    init();
}

void Gwr::execute() {
    NodeGwr* first;
    NodeGwr* second;
    Edge* edge;
    std::list<Edge*>largerAges;
    std::list<NodeGwr*>emptyEdges;
    NodeGwr* newNode;
    std::list<Nodo*>* neighbours;
    double activityOfNode;

    //Generate a data sample j for input to the network.
    bool firstSample = dataSet.getRandomSample(currentSample);

    if (firstSample)
        epoch++;
    
    
    

    /*Select the best matching node, and the second best, that
      is the nodes s,t */
    findTheNearestNodes(first, second, currentSample);

    //If there is not a connection between s and t, create it
    if (first->isConnectedWitth(second, edge)) {
        edge->setValue(0);
    } else { // otherwise, set the age of the connection to 0.
        connectEdge( first, second,0,"age");
    }

    //Calculate the activity of the best matching unit
    activityOfNode = activity(first);

    // If the activity < activity threshold and firing counter < firing threshold 
    if (activityOfNode < alphaT and first->getFiringCounter() < firingThreshold) {
        //then a new node should be added
        //Add the new node, r
        insertNewNode(newNode, first, second);
        //Insert edges between r and s and between r and t
        connectEdge(newNode, first,0,"age");
        connectEdge(newNode, second,0,"age");

        //Remove the link between s and t
        removeEdge(first,second);
    } else { /*If a new node is not added, adapt the positions of the winning node and its neighbours,
           * i, that is the nodes to which it is connected */
        MoveTheWinnerAndTopologicalNeighbors(first, currentSample);
    }

    // Age edges with an end at s
    incrementTheAges(first);

    //Reduce the counter of how frequently the winning node s has fired
    reduceTheCounter(first);
    

    //and the counters of its neighbours
    neighbours = first->getNeighbors();
    reduceTheCounterOfNeighbours(neighbours);






    /*If there are any edges with an age larger than aMax then remove
      them.*/
    if (anyEdgesWithAgeLarger(largerAges)) {
        removeEdges(largerAges);
    }

    /*If, after this, there are nodes with no edges then remove
      these nodes.*/
    if (haveNodesWithNoEdges(emptyEdges)) {

        removeNeurons(emptyEdges);
      
    }
    
    std::cout << nodos->size() << endl;




}

void Gwr::executeOneIt() {




}

void Gwr::findTheNearestNodes(NodeGwr*& first, NodeGwr*& second, Sample*& s) {

    findTheBest(first, s);
    findTheBest(second, s);

    first->isTheWinner(false);
    second->isTheWinner(false);

}

void Gwr::findTheBest(NodeGwr*& bestNode, Sample *s) {
    NodeGwr* auxNode;
    auxNode = gerateNodeWithMaxDistance();

    //std::cout << auxNode->squaredDistance(s) << std::endl;



    for (auto itN = nodos->begin(); itN != nodos->end(); itN++) {
        NodeGwr* tempN = dynamic_cast<NodeGwr*>(*itN); 
        if ((*itN)->distance(*s) <   ( dynamic_cast<Nodo*>( auxNode ))->distance(*s) and tempN->getWinnerStatus() == false) {
            auxNode = tempN;
        }
    }

    //  std::cout << auxNode->squaredDistance(s) << std::endl;

    bestNode = auxNode;
    bestNode->isTheWinner();


}

Sample Gwr::gerateMaxDistance() {
    Sample position;

    double feature = MAXDOUBLE;

    std::vector<double> info;
    int sampleSize = dataSet.getSampleSize();

    for (int i = 0; i < sampleSize; i++) {

        info.push_back(feature);
    }

    position.setFeatures(info);

    return position;


}

Sample Gwr::makeTheNewNodeFeature(Sample& first, Sample& second) {
    Sample r = first + second;
    r = r / 2;

    return r;


}

NodeGwr* Gwr::gerateNodeWithMaxDistance() {
    Sample maxDistance;
    maxDistance = gerateMaxDistance();
    NodeGwr* auxNode = new NodeGwr(maxDistance);
    return auxNode;

}

double Gwr::activity(NodeGwr*& bestNode) {

    return exp(-bestNode->distance(*currentSample));

}

void Gwr::insertNewNode(NodeGwr*& newNode, NodeGwr*& first, NodeGwr*& second) {
    newNode = new NodeGwr(currentSample, currentNode.label);

    //    Sample firstSample = first->getFeatures();
    //    Sample secondSample = (*currentSample);
    //    Sample newSample = makeTheNewNodeFeature(firstSample, secondSample);
    //    newNode = new NodeGwr(newSample, currentNode.label);

    addNeuron(newNode);



}

void Gwr::MoveTheWinnerAndTopologicalNeighbors(NodeGwr*& winner, Sample*& s) {

    std::list<Nodo*> *neighbors;


    double firingCounter = winner->getFiringCounter();
    //winner->updateFeatures(eW *firingCounter, currentSample);
    winner->updateFeatures(eW * firingCounter, currentSample);
    neighbors = winner->getNeighbors();
    MoveTheNeighbours(neighbors, currentSample);

}

void Gwr::MoveTheNeighbours(std::list<Nodo*>*& neighbors, Sample*& s) {
    double firingCounter;
    for (auto itN = neighbors->begin(); itN != neighbors->end(); itN++) {

        
        firingCounter = toNodeGwr(*itN)->getFiringCounter();
        (*itN)->updateFeatures(eN*firingCounter, s);

    }


}

void Gwr::incrementTheAges(NodeGwr*& winner) {
    std::list<Edge*> edges;
    
    edges = winner->getEdges();

    for (std::list<Edge*>::iterator itE = edges.begin(); itE != edges.end(); itE++) {
        (*itE)->incrementValue();
    }


}

void Gwr::reduceTheCounter(NodeGwr*& winner) {
    std::list<NodeGwr*>* neighbours;


    double ht = winner->getFiringCounter();
    double dH = (alphaB * (h0 - ht) - 1) / tauB;

    winner->incrementTheTheFiringCounter(dH);
}

void Gwr::reduceTheCounterOfNeighbours(std::list<Nodo*>*& neighbours) {
    double ht;
    double dH;

    for (auto itN = neighbours->begin(); itN != neighbours->end(); itN++) {
        NodeGwr* tempN = dynamic_cast<NodeGwr*>(*itN); 
        ht = tempN->getFiringCounter();

        dH = (alphaN * (h0 - ht) - 1) / tauN;

        tempN->incrementTheTheFiringCounter(dH);
    }


}

bool Gwr::anyEdgesWithAgeLarger(std::list<Edge*>& EdgesOfLargerAge) {
    bool isLarger = false;


    for (auto itE = edges->begin(); itE != edges->end(); itE++) {

        if ((*itE)->getValue() > aMax) {

            EdgesOfLargerAge.push_back(*itE);
            isLarger = true;
        }



    }


    return isLarger;



}

void Gwr::removeEdges(std::list<Edge*>& edges) {
    NodeGwr* headNeuron;
    NodeGwr* backNeuron;

    for (auto itE = edges.begin(); itE != edges.end(); itE++) {

        headNeuron = dynamic_cast<NodeGwr*>( (*itE)->getAheadNeuron() );
        backNeuron = dynamic_cast<NodeGwr*>( (*itE)->getBackNeuron() );

        headNeuron->removeEdge((*itE));
        backNeuron->removeEdge((*itE));
        headNeuron->removeNeighbor(backNeuron);
        backNeuron->removeNeighbor(headNeuron);


        this->edges->remove(*itE);

        delete (*itE);

    }
}

bool Gwr::haveNodesWithNoEdges(std::list<NodeGwr*>& emptyEdges) {
    bool isEmpty = false;

    for (auto itN = nodos->begin(); itN != nodos->end(); itN++) {

        if ((*itN)->getNeighborsSize() == 0) {
            
            emptyEdges.push_back(toNodeGwr(*itN));
            isEmpty = true;
        }


        // std::cout << "getNeighborsSize: " << (*itN)->getNeighborsSize() << std::endl;
        // std::cout << "currentIterantion: " << currentIteration<< std::endl;
    }

    return isEmpty;

}

void Gwr::removeNeurons(std::list<NodeGwr*>& emptyEdges) {
    for (auto itN = emptyEdges.begin(); itN != emptyEdges.end(); itN++) {

        //(*itN)->showEdges();
        nodos->remove(*itN);
        delete (*itN);
        *itN = NULL; 
    }


}

void Gwr::networkTojson(std::string fileName) {

    nlohmann::json jsonFile;

    getNodesJson(jsonFile);
    getEdgesJson(jsonFile);
    jsonFile["properties"]["eW"] = eW;
    jsonFile["properties"]["eN"] = eN;
    jsonFile["properties"]["aMax"] = aMax;
    jsonFile["properties"]["firingThreshold"] = firingThreshold;
    jsonFile["properties"]["talN"] = tauN;
    jsonFile["properties"]["talB"] = tauB;
    jsonFile["properties"]["alphaB"] = alphaB;
    jsonFile["properties"]["alphaT"] = alphaT;

    jsonFile["properties"]["currentIteration"] = currentIteration;

    saveJson(jsonFile, fileName);



}

void Gwr::getNodesJson(nlohmann::json& jsonFile) {
    for (auto itN = nodos->begin(); itN != nodos->end(); itN++) {
        
        jsonFile["node"].push_back(dynamic_cast<NodeGwr*>(*itN)->toJson());

    }

}

void Gwr::getEdgesJson(nlohmann::json& jsonFile) {

    for (auto itE = edges->begin(); itE != edges->end(); itE++) {
        //(*itE)->print();
        jsonFile["edge"].push_back((*itE)->toJson());
    }

}

void Gwr::saveJson(nlohmann::json& jsonFile, std::string fileName) {
    ofstream file;
    file.open(fileName, ios::out);

    file << std::setw(4) << jsonFile << std::endl;



}
