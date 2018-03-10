/* 
 * File:   Tests.cpp
 * Author: oriva
 * 
 * Created on 10 de Outubro de 2014, 14:15
 */



#include "Test.h"
#include "SimpleNN.h"
#include "DataSet.h"


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
    
}

void Test::samplesOperations() {
    std::vector<double> info;
    info.push_back(1);
    info.push_back(2);
    info.push_back(3);
    Sample s1(info);

    info[0] = 2;
    info[1] = 2;
    info[2] = 2;
    Sample s2(info);

    std::cout << "S1: " << s1.toString() << std::endl;
    std::cout << "S2: " << s2.toString() << std::endl;
    Sample r = s1 + s2;
    std::cout << "S1 + S2: " << r.toString() << std::endl;
    std::cout << "S1 - S2: " << (s1 - s2).toString() << std::endl;
    std::cout << "S1 / 2: " << (s1 / 2).toString() << std::endl;
    std::cout << "Distância entre S1 e S2: " << s1.distance(s2) << std::endl;
    s1.putNormalNoise(0.1);
    std::cout << "Noise in S1 with s = 0.1: " << s1.toString() << std::endl;
    Sample s3(s2);
    std::cout << "Criando S3 a partir de S2: " << s3.toString() << std::endl;
}
 
void Test::simpleNN() {
    std::string dataFile = pathDataSets;
    dataFile.append("simple_set.dat");
    SimpleNN snn; 
    
    snn.initialize(dataFile);
    snn.execute(); 
    
    snn.toJson("/tmp/simplenn.json");
}



void Test::dataSetOperations() {
    std::string dataFile1 = pathDataSets;
    dataFile1.append("simple_set.dat");
    DataSet ds1(dataFile1);
    DataSet ds2(dataFile1);
    DataSet ds3(dataFile1);
    std::cout << "Base de dados: " << std::endl;
    ds1.show();

    std::cout << " Salva a Base de dados em formato do octave para /tmp/simple_set_octave.dat. " << std::endl;
    ds1.saveToFileOctaveFormat("/tmp/simple_set_octave.dat");

    std::cout << "Base de dados normalizada: " << std::endl;
    ds1.normalizeData();
    ds1.show();

    std::cout << "Base de dados com ruído s = 0.1" << std::endl;
    ds2.putNoise(0.1, 1);
    ds2.show();

    std::cout << "Salva a base de dados normalizada e com amostras aleatórias em /tmp/test_save_normalized.txt" << std::endl;
    ds3.saveToFile("/tmp/test_save_normalized.txt", true, true);
}

Test::~Test() {
    
}

