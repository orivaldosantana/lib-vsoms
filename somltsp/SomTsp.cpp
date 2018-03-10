/* 
 * File:   SomTsp.cpp
 * Author: oriva
 * 
 * Created on 17 de Outubro de 2014, 13:45
 */

#include "SomTsp.h"

SomTsp::SomTsp() {
    maxEpoch = 150; 
    maxSize = 120;  
    sigma = 4;
    epoch = 1;
    tempListNN = new std::list<Nodo*>; 
}

SomTsp::SomTsp(const SomTsp& orig) {
}

SomTsp::~SomTsp() {
    delete tempListNN; 
}

/**
 * Carrega o conjunto de dados a partir de fileData e em seguida inicializa a rede 
 * com três nodos. 
 * @param fileData nome do arquivo para leitura dos dados 
 */
void SomTsp::initialize(std::string fileData){
    loadDataSet(fileData);
    initialize(dataSet); 
    dataSet.show(); 
}

/**
 * Inicializa a rede com três nodos, cada um contendo a mesma informação. As 
 * conexões da rede são criadas de modo a forma uma rede cíclica de vizinhaça 2 
 * para cada nodo. 
 * @param dt conjunto de dados.
 */
void SomTsp::initialize(DataSet &dt) {

    std::vector<double>  info; 
    info.push_back(-0.3);
    info.push_back(0.2);
    
    Sample* s = new Sample(info);
    NodoTsp* a = new NodoTsp(*s, "1");
    addNeuron(a, s);

    info[0] = 0;
    info[1] = 0.2;
    s = new Sample(info);
    NodoTsp* b = new NodoTsp(*s, "2");
    addNeuron(b, s);
    addWeight(a, b);

    /*
    NodoTsp* c = new NodoTsp(*s, "3");
    addNeuron(c, s);
    addWeight(c, a);
    addWeight(c, b);
*/
    nodeCount = 2; 
}

/**
 * Ativa todos os neurônios e avalia o contador de vitórias.
 */
void SomTsp::enableNeurons() {
    for (std::vector<Nodo*>::iterator itN = nodos->begin(); itN != nodos->end(); itN++) {
        // abilita novamente o neurônio
        NodoTsp* nt = dynamic_cast<NodoTsp*>(*itN); 
        nt->setEnabled(true);
        // verifica se o neurônio foi vencedor 
        if (nt->getWinsCount() > 0)
            // reinicia o contador de vitórias 
            nt->resetNeuronWins();
        else
            nt->decreaseWins();
    }
}

/**
 * Deleta todos os neurônios marcados para serem deletados 
 */
void SomTsp::deleteNeurons() {
    NodoTsp* firstNeighbor;
    NodoTsp* secondNeighbor;
    for (std::vector<Nodo*>::iterator itN = nodos->begin(); itN != nodos->end(); itN++) {
        NodoTsp* nt = dynamic_cast<NodoTsp*>(*itN); 
        if (nt->isMarkedToRemove()) {
            std::list<Nodo*>* neighborNeurons = (*itN)->getNeighbors();
            //std::cout << " Marking to delete: Nodo " << (*itN)->getLabel() << " with " << neighborNeurons->size() << " nodos " << std::endl;
            removeNeuron(*itN);            
        }
    }
    for (std::vector<Nodo*>::iterator itN = nodos->begin(); itN != nodos->end(); itN++) {
        NodoTsp* nt = dynamic_cast<NodoTsp*>(*itN); 
        if (nt->isMarkedToRemove()) {
            //std::cout << " Deleting: " << nt->getLabel() << std::endl;
            nodos->erase(itN);
            itN = nodos->begin();
        }
    }
}

void SomTsp::execute() {
    if (!dataSet.isEmpty()) {
        epoch = 0; 
        while (epoch < maxEpoch) {    
            executeOneIt();
        }
    } else
        std::cout << " Data set is empty! " << std::endl;
}

void SomTsp::executeOneIt() {
    
    //Generate a data sample
    bool firstSample = dataSet.getRandomSample(currentSample);
    if (firstSample) {
        epoch++;
        std::cerr << " Epoch: " << epoch << std::endl;
        //update the gain G (sigma)
        sigma = (1 - 0.1) * sigma;
        //enable all nodes of the network
        enableNeurons();
        //remove nodes of the network 
        deleteNeurons();
        
        //printNodos(); 
        saveTxtNodos("somtsp");
    }
    //Find the best and second best neuron
    // find best neuron
    NodoTsp* bestN = dynamic_cast<NodoTsp*>(findBestNeuron(currentSample));   
    std::list<Nodo*>* neighborWinNeurons = bestN->getNeighbors();
    float secondBestDistance = INFINITY_FLOAT;
    NodoTsp* secondBestN = NULL;
    
    // find second best neuron (between the winner neighbors)
    for (std::list<Nodo*>::iterator itN = neighborWinNeurons->begin(); itN != neighborWinNeurons->end(); itN++) {
        float dist = (*itN)->distance(*currentSample);
        if (dist < secondBestDistance) {
            secondBestDistance = dist;
            secondBestN = dynamic_cast<NodoTsp*>(*itN);
        }
    }
    //Count the number of wins
    bestN->increaseWins();
    int wins = bestN->getWinsCount();
    //If the nodo is enabled
    if (bestN->isEnabled()) 
        //If the network size is less then maximum size and the wins count of
        //winner node is equal to 2 then add new node  
        if ((nodos->size() < maxSize) and (wins == 2) ) {
            // remove the conection between the best and the second best neuron
            removeWeight(bestN, secondBestN);
            //Neuron r, from imput
            //Sample* d = bestN->getData(); 
            //Create a new nodo at same place of the winner node 
            NodoTsp* nr = new NodoTsp(*bestN, Utils::int2string(getNodeCount() + 1));
            //Disable the new node and the winner node 
            nr->setEnabled(false); 
            bestN->setEnabled(false); 
            //Add the new nodo to the network
            addNeuron(nr, bestN);
            //Add conexions between the winner and the new node
            addWeight(bestN, nr);
            //Add conexions between the second best and the new node 
            addWeight(secondBestN, nr);
              
        //Else no new node is inserted, update the weights vector of the 
        //winner node and his neighbors 
        }else {
            double delta = 0.1; //0.70711;
            bestN->updateFeatures(delta, currentSample);
            bestN->setMarkedToUpdate(true);
            //int neighborOrder = 0;
            int depthList = (getAmountNeurons() / 2) - 1;
            // atualiza os vizinhos de cada lado do vencedor
            for (std::list<Nodo*>::iterator itN = neighborWinNeurons->begin(); itN != neighborWinNeurons->end(); itN++) {
                getNeighborList(tempListNN, dynamic_cast<NodoTsp*>(*itN), depthList);
                // atualiza os pesos dos nodos da lista
                updateNeighborFeatures(bestN, delta, tempListNN, currentSample);
                // desmarca os neurônios selecionados para atualização
                unCheckNeuronList(tempListNN);
                tempListNN->clear();
            }
             
            // umark to update the winner node  
            bestN->setMarkedToUpdate(false);
        }   
}


/**
 * Obtem os vizinhos de uma ramificação do nodo. Este método funciona marcando e adicionando 
 * cada vizinho até que uma desejada quantidade de vizinhos sejam adicionados
 * a uma lista.  
 * @param listNN lista contedo os vizinhos
 * @param startN primeiro vizinho 
 * @param depth quantidade de vizinhos da ramificação 
 */
void SomTsp::getNeighborList(std::list<Nodo*>* listNN, NodoTsp* startN, int depth) {

    int count = 0;
    NodoTsp* neighborN = startN;
    while (count < depth ) {
        listNN->push_back(neighborN);
        count++;
        neighborN->setMarkedToUpdate(true);
        std::list<Nodo*>* neighborNeurons = neighborN->getNeighbors();
        std::list<Nodo*>::iterator itN = neighborNeurons->begin();
        NodoTsp* nt;
        nt = dynamic_cast<NodoTsp*>(*itN);
        if (!(nt)->isMarkedToUpdate()) {
            neighborN = (nt);
        } else {
            itN++;
            // se não chegou no fim da lista de vizinhos 
            if ( itN != neighborNeurons->end() ) { 
                nt = dynamic_cast<NodoTsp*>(*itN);
                if (!(nt)->isMarkedToUpdate())
                    neighborN = (nt); // seleciona para atualização dos pesos 
                else {
                    itN--;
                    cout << " Erro ao buscar a lista de vizinhos de"<< startN->getLabel() <<", no nodo: " << (*itN)->getLabel() << " ";
                    break;
                }
            }
        }
    }
}

//TODO: só está removendo para dois vizinhos, fazer a remoção para todos os vizinhos 
// O nodo deve ser retirado da lista de nodos de cada vizinhos 
void SomTsp::removeNeuron(Nodo* n) {
    if (n != NULL) {
        std::list<Nodo*>* neighborNeurons = n->getNeighbors();
        if ( neighborNeurons->size() == 2 ) {
            std::list<Nodo*>::iterator itNeighbor = neighborNeurons->begin();
            Nodo* firstNeighbor = *itNeighbor;
            itNeighbor++;
            Nodo* secondNeighbor = *itNeighbor;
            removeWeight(firstNeighbor, n);
            removeWeight(secondNeighbor, n);
            addWeight(firstNeighbor, secondNeighbor);
        } else {
            std::cout << " Neuron " << n->getLabel() << " was not removed. " << std::endl; 
            
        }
    }
}

void SomTsp::updateNeighborFeatures(NodoTsp* bn, float d, std::list<Nodo*>* nl, Sample* s) {
    int neighborOrder = 1;
    for (std::list<Nodo*>::iterator itN = nl->begin(); itN != nl->end(); itN++) {
        double h = d * exp(-(pow(neighborOrder, 2) / ( pow(sigma, 2))));
        //std::cout << (*itN)->getLabel() << " " << h << ", ";
        (*itN)->updateFeatures(h, s);
        neighborOrder++;
    }
    //std::cout << std::endl;
}



void SomTsp::setMaxSize(int maxSize) {
    this->maxSize = maxSize;
}

int SomTsp::getMaxSize() const {
    return maxSize;
}

std::vector<Nodo*>* SomTsp::getNodos() const {
    return nodos;
}

void SomTsp::setSigma(double sigma) {
    this->sigma = sigma;
}

double SomTsp::getSigma() const {
    return sigma;
}

void SomTsp::printStatus(){
    std::cout << "Status: " << std::endl;
    for (std::vector<Nodo*>::iterator itN = nodos->begin(); itN < nodos->end(); itN++) {
        (dynamic_cast<NodoTsp*>(*itN))->printStatus(); 
    }
    std::cout << std::endl; 
}


void SomTsp::unCheckNeuronList(std::list<Nodo*>* nl) {
    for (std::list<Nodo*>::iterator itN = nl->begin(); itN != nl->end(); itN++) {
        (dynamic_cast<NodoTsp*>(*itN))->setMarkedToUpdate(false);
    }
}

