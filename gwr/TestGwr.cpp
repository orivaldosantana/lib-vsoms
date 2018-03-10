/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGwr.cpp
 * Author: samuel
 * 
 * Created on 26 de Fevereiro de 2018, 22:38
 */

#include "TestGwr.h"

TestGwr::TestGwr() {
}

TestGwr::TestGwr(const TestGwr& orig) {
}

TestGwr::~TestGwr() {
}

void TestGwr::executeNetwork() {

    Gwr network;

    network.initialize ("testData/smartPhone/frenteType2.csv");
    int iterations = 20000;

    for (int i = 0; i < iterations; i++) {
        network.execute();

    }
    network.networkTojson("testData/ver.json");



}

void TestGwr::maestro1(){
        Gwr network;

    network.initialize("../data/maestro/maestro1XY.txt");
    int iterations = 20000;

    for (int i = 0; i < iterations; i++) {
        network.execute();

    }
    network.networkTojson("testData/ver.json");

}

