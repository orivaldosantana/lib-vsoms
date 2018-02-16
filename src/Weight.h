/* 
 * File:   Weight.h
 * Author: oriva
 *
 * Created on 13 de Outubro de 2014, 17:27
 */

#ifndef WEIGHT_H
#define	WEIGHT_H


#include "Nodo.h" 

class Nodo;

class Weight {
public:
    Weight(const Weight& orig);
    virtual ~Weight();

    Weight(double v,
            Nodo* o,
            Nodo* t,
            std::string l);
    Nodo* getAheadNeuron();
    Nodo* getBackNeuron();
    std::string getLabel();
    double getValue();
    void setValue(double v);
    void print();

private:
    double value;
    Nodo* pOrigin;
    Nodo* pTarget;
    std::string label;

};

#endif	/* WEIGHT_H */

