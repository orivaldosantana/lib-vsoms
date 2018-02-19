/* 
 * File:   SomTsp.h
 * Author: oriva
 *
 * Created on 17 de Outubro de 2014, 13:45
 */

#ifndef SOMTSP_H
#define	SOMTSP_H

#include "BasicNeuralNetwork.h"
#include "NodoTsp.h"

/** Classe que implementa o SOM para o problema do caixeiro viajante (TSP)
 *  [1] 
 */
class SomTsp: public BasicNeuralNetwork {
public:
    SomTsp();
    SomTsp(const SomTsp& orig);
    virtual ~SomTsp();
    
    void                execute();
    void                executeOneIt(); 
    
    void                 deleteNeurons           ( ); 
    void                 removeNeuron            (Nodo*                     n);   
    void                 initialize              (DataSet &dt); 
    void                 initialize              (std::string         fileData);
    void                 getNeighborList         (std::list<Nodo*>*  listNN, 
                                                  NodoTsp*              startN, 
                                                  int                    depth);
   
    int                  getMaxSize              ( ) const;     
    double               getSigma                ( ) const; 
    void                 printStatus             ( );     
    void                 unCheckNeuronList       (std::list<Nodo*>*      nl);
    void                 updateNeighborFeatures  (NodoTsp*                  bn,
                                                  float                      d, 
                                                  std::list<Nodo*>*      nl, 
                                                  Sample*                    s);

    void                 setMaxSize              (int maxSize);
    std::vector<Nodo*>*  getNodos              ( ) const;
    void                 setSigma                (double sigma);
               
    
private:
    void enableNeurons();
    
    double sigma; 
    //std::vector<NodoTsp*>* nodos; 
    std::list<Nodo*>* tempListNN;
    int maxSize;


};

#endif	/* SOMTSP_H */

// [1] http://www.sciencedirect.com/science/article/pii/0893608088900020  
