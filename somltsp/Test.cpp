/* 
 * File:   Tests.cpp
 * Author: oriva
 * 
 * Created on 10 de Outubro de 2014, 14:15
 */

#include <iostream>

#include "Test.h"
#include "NodoTsp.h"
#include "SomTsp.h"

Test::Test() {
    pathDataSets = "../data/test/";
}

Test::Test(const Test& orig) {
}


void Test::nodoOperations() {
    std::vector<double> info;
    info.push_back(1);
    info.push_back(2);
    info.push_back(3);
    Sample s1(info);
    
    Nodo n1(s1); 
    
    std::cout << "N1: " << n1.toString() << std::endl;
    
    info[0] = 0;
    info[1] = 3;
    info[2] = 5;
    Sample s2(info);
    
    n1.updateFeatures(0.1,&s2); 
    
    std::cout << "N1 atualizado d=0.1 e S2("<< s2.toString() << "): " << n1.toString() << std::endl;
    
    NodoTsp* nt1 = new NodoTsp(s1); 
    Nodo* pn; 
    nt1->increaseWins(); 
}

void Test::convertDataFile(){
 
    DataSet ds1("../data/maestro/IMG_3262_dif1.txt");
    std::cout << "Base de dados: " << std::endl;
    ds1.show();
    ds1.savePartToFile("/tmp/maestro1.txt",1,2);
}



void Test::somTsp(){
    std::string dataFile = pathDataSets;
    dataFile.append("pontos_2d_v1.txt");
    
    SomTsp st; 
    st.initialize(dataFile);
    st.execute();     
}

void Test::somTspMestro1(){
    
    SomTsp st; 
    st.initialize("../data/maestro/maestro1XY.txt");
    st.execute();     
}

Test::~Test() {
    
}

