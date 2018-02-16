/* 
 * File:   SimpleNN.cpp
 * Author: oriva
 * 
 * Created on 14 de Outubro de 2014, 18:11
 */

#include "SimpleNN.h"

SimpleNN::SimpleNN() {
}

SimpleNN::SimpleNN(const SimpleNN& orig) {
}

SimpleNN::~SimpleNN() {
}

void SimpleNN::initialize(std::string fileData){
    dataSet.loadDataFromFile(fileData); 
}

/** Constroi uma rede simples contendo 5 nodos. Desenha a rede em formato de grafo
 * em um aquivo pdf na pasta output. Mostra as conexões e os nodos na tela. Remove
 * uma conexão desenha a rede em arquivo pdf, imprime na tela as conexões e os nodos. 
 */
void SimpleNN::executeOneIt() {
    /*****************Adicionando Nodos******************/
    Sample* s = dataSet.getRandomSample();
    Nodo* a = new Nodo(*s, "a");
    addNeuron(a, s);

    s = dataSet.getRandomSample();
    Nodo* b = new Nodo(*s, "b");
    addNeuron(b, s);

    s = dataSet.getRandomSample();
    Nodo* c = new Nodo(*s, "c");
    addNeuron(c, s);

    s = dataSet.getRandomSample();
    Nodo* d = new Nodo(*s, "d");
    addNeuron(d, s);

    s = dataSet.getRandomSample();
    Nodo* e = new Nodo(*s, "e");
    addNeuron(e, s);

    /***************Adicionando conexões ***************/
    addWeight(a,b);
    addWeight(c,b);
    addWeight(c,d);
    addWeight(d,e);
    addWeight(e,a);

    /*****Gerando o pdf do com o grafo da rede**********/
    savePdfGraph("../output/simple_nn_test");

    /************* impriminto no terminal **************/
    printConections();
    printNodos(); 

    /*************** Excluindo uma conexão *************/
    removeWeight(c,d); 
    savePdfGraph("../output/simple_nn_test_removed_conexion_c_d");
    printConections();
    printNodos(); 
    
    /********* Impriminto Listas de vizinhos ***********/
    printNeighbors();
}

/**
 * Executa uma iteração do algoritmo 
 */
void SimpleNN::execute(){
    if ( ! dataSet.isEmpty()) {
        executeOneIt(); 
    }
    else
        std::cout << " Base de dados está vazia! " << endl; 
}

