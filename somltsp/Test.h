/* 
 * File:   Tests.h
 * Author: oriva
 *
 * Created on 10 de Outubro de 2014, 14:15
 */

#ifndef TEST_H
#define	TEST_H

#include "Sample.h"
#include "DataSet.h" 
#include "Nodo.h"

class Test {
public:
    Test();
    Test(const Test& orig);
    virtual ~Test();
    

    void nodoOperations(); 
    void convertDataFile(); 
    void somTsp(); 
    void somTspMestro1(); 
private:
    std::string pathDataSets; 

};

#endif	/* TESTS_H */

