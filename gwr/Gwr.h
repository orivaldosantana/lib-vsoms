/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gwr.h
 * Author: samuel
 *
 * Created on 28 de Janeiro de 2018, 14:55
 */

#ifndef GWR_H
#define GWR_H

#include "BasicNeuralNetwork.h"
#include "NodeGwr.h"
#include "Counter.h"

class Gwr : public BasicNeuralNetwork {
public:
    Gwr();
    Gwr(const Gwr& orig);
    Gwr(std::string jsonFile);
    virtual ~Gwr();
    void initialize(std::string fileData);
    void initializeFromCSV(std::string fileData);
    void init();
    void execute();
    void executeOneIt();

    void seTfiringThreshold(double f);
    void setActivityThreshold(double a);
    
    void networkTojson(std::string fileName);

    // void saveNodesToCsvFile(std::string fileName, std::string fileHeader); Json > csv
    //void saveGraph(std::string filename);  Json > all
   

private:
    Sample gerateRandomPosition();
    Sample gerateMaxDistance();
    Sample makeTheNewNodeFeature(Sample& first, Sample& second);
    NodeGwr* gerateNodeWithMaxDistance();
    
    void removeEdges(std::list<Edge*>&edges);


    void insertNewNode(NodeGwr* &newNode, NodeGwr*& first, NodeGwr*& second);
    void removeNeurons(std::list<NodeGwr*>& emptyEdges);
    void findTheNearestNodes(NodeGwr* &first, NodeGwr* &second, Sample* &s);
    void findTheBest(NodeGwr* &bestNode, Sample* s);
    void findBest(std::vector<double> &infoB, int initPos, int finalPos);
    void findTheNodeWithLargestError(NodeGwr* &worse, std::list<NodeGwr*>*& worseNeighbours);
    void findTheNodeWithLargestErrorAmomgTheNeighbours(NodeGwr* &worse, std::list<NodeGwr*>*& worseNeighbours);
    void updateLocalError(NodeGwr* &winner, Sample* &s);
    void MoveTheWinnerAndTopologicalNeighbors(NodeGwr* &winner, Sample* &s);
    void MoveTheNeighbours(std::list<Nodo*> * &neighbors, Sample* &s);
    void incrementTheAges(NodeGwr* &winner);
    void reduceTheCounter(NodeGwr* &winner);
    void getNodesJson(nlohmann::json& jsonFile);
    void setNodesJson(nlohmann::json& jsonFile);
    void getEdgesJson(nlohmann::json& jsonFile);
    void setEdgesJson(nlohmann::json& jsonFile);
    void loadNetworkbyJson(std::string fileName);
    bool anyEdgesWithAgeLarger(std::list<Edge*>&EdgesOfLargerAge);
    bool haveNodesWithNoEdges(std::list<NodeGwr*>& emptyEdges);
    void showNodes();
    void reduceTheCounterOfNeighbours(std::list<Nodo*>*& neighbours);
    double activity(NodeGwr*& bestNode);
    void setNeighbors();
    NodeGwr* findNode(NodeGwr*& node);
    void saveJson(nlohmann::json& jsonFile, std::string fileName);
    nlohmann::json loadJson(std::string fileName);
    inline NodeGwr* toNodeGwr(Nodo* nodo){ return  dynamic_cast<NodeGwr*>(nodo);}
    inline Nodo* toNodo(NodeGwr* nodo){ return  dynamic_cast<Nodo*>(nodo);}
    

    double eW;
    double eN;
    double alphaT;
    double alphaN;
    double alphaB;
    double tauB;
    double tauN;
    double firingThreshold;
    double sT;
    double h0;
    double aMax;
    



    Counter currentNode;
    int currentIteration;

};

#endif /* GWR_H */

