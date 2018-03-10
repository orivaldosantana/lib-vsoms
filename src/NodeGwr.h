/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeGwr.h
 * Author: samuel
 *
 * Created on 28 de Janeiro de 2018, 14:55
 */

#ifndef NODEGWR_H
#define NODEGWR_H
#include "Nodo.h"


class NodeGwr : public Nodo {
public:
    NodeGwr();
    NodeGwr(const NodeGwr& orig);
    virtual ~NodeGwr();
    NodeGwr(const Sample &s, std::string l = "n ", double _firingCounter = 1, std::string d = "d ");
    NodeGwr(Sample*&s, std::string l = "n ", double _firingCounter = 1, std::string d = "d ");
    NodeGwr(nlohmann::json& jsonFile);
    void setFiringCounter(double _firingCounter);
    void incrementTheTheFiringCounter(double f);
    void decreaseTheFiringCounter(double f);
    void showFeatures();
    void showNeighbors();
    void showEdges();
    void showLabel();
    void showWinner();
    void isTheWinner(bool _winner = true);
    void walk(double d);
 
    bool getWinnerStatus();
    bool isConnectedWitth(NodeGwr* &node, Edge* &edge);
 
    

    
    double squaredDistance(Sample* &s);
    
    double getFiringCounter();
    
    void removeTime();
 
    nlohmann::json getEdgesJson(nlohmann::json& jsonFile);
    nlohmann::json toJson();
 
    std::string to_csvFile();
    
private:
    double firingCounter;

};

#endif /* NODEGWR_H */

