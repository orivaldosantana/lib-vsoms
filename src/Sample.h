/* 
 * File:   Sample.h
 * Author: oriva
 *
 * Created on 10 de Outubro de 2014, 14:20
 */

#include <vector>
#include <string>
#include <sstream>
#include "utils.h"

#ifndef SAMPLE_H
#define	SAMPLE_H

class Range {
public:
    int begin; 
    int end;
};

class Sample {
    friend class Nodo; 
    friend class NodoTsp;
    friend class SomStg2Node; 
    friend class NodeSomCstg; 
    friend class NodeGwr; 
public:
    Sample(); 
    Sample(int s);
    Sample(std::vector<double>  &info); 
    Sample(const Sample& orig);
    virtual ~Sample();
    

    Sample              operator+                 (Sample                &sIn);
    Sample              operator-                 (Sample                &sIn);
    Sample              operator/                 (double                   d);

    double              distance                  (Sample                &sIn);
    double              distance(std::vector<double> &sIn, unsigned int initPos, unsigned int finalPos);
    
    double              distance(Sample *s, int initPos, int finalPos);
    int                 getSize                   ( );
    void                getFeatures               (std::vector<double>  &info); 
    double              getFeature                (int index); 
    //void                initialize                (std::vector<double>  &info);    
    //void                print                     ( );
    double              partialDistance           (Sample                &sIn,
                                                   Range                   &r);
    void                putNormalNoise             (double s);
    //void                setSize                   (int                      s);
    void                setFeatures               (std::vector<double>  &info);
    std::string         toString                  ( );        

protected:
    std::vector<double>     information;
 
    
    
};

#endif	/* SAMPLE_H */

