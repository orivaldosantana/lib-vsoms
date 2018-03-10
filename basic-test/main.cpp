/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: oriva
 *
 * Created on 16 de Fevereiro de 2018, 5:43
 */

#include <cstdlib>

#include "Test.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
	Test test;
	
    test.samplesOperations();
    test.dataSetOperations(); 
    test.nodoOperations(); 
    test.simpleNN();

    return 0;
}

