/* 
 * File:   SimpleNN.h
 * Author: oriva
 *
 * Created on 14 de Outubro de 2014, 18:11
 */

#ifndef SIMPLENN_H
#define	SIMPLENN_H
#include "BasicNeuralNetwork.h"

class SimpleNN: public BasicNeuralNetwork {
public:
    SimpleNN();
    SimpleNN(const SimpleNN& orig);
    virtual ~SimpleNN();
    void executeOneIt(); 
    void execute(); 
    void initialize(std::string fileData);

private:

};

#endif	/* SIMPLENN_H */

