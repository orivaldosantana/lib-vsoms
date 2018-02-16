/* 
 * File:   BasicNeuralNetwork.h
 * Author: oriva
 *
 * Created on 14 de Outubro de 2014, 11:00
 */

#ifndef BASICNEURALNETWORK_H
#define	BASICNEURALNETWORK_H

#include "Nodo.h"
#include "DataSet.h"

class BasicNeuralNetwork {
protected:
    std::vector<Nodo*>*   nodos; //!< Nodos 
    std::list<Weight*>*   weights; //!< Pesos 
    int                   nodeCount; //!< Contador de nodos adicionados na rede 
    DataSet               dataSet; //!< Dados de treinamento 
    int                   epoch;  //!< Uma apresentação completa de todas as amostras da base de dados 
    int                   maxEpoch; //!< Número máximo de épocas de treinamento 
    int                   maxSize; ///< Tamanho máximo atingido pela rede durante o treinamento     
    int                   currentIt; //!< Número da iteração atual 
    Sample*               currentSample; //!< Amostra atual 
    double                nodeDrawRadius; //!< Tamanho do raio para desenhar cada nodo no software de visualização 
    

    void                 removeWeight            (Nodo*                     a,
                                                  Nodo*                     b);

  
public:
    BasicNeuralNetwork();
    BasicNeuralNetwork(const BasicNeuralNetwork& orig);
    virtual ~BasicNeuralNetwork();

    bool                 addNeuron               (Nodo*                     n,
                                                  Sample*                   s);
    void                 addWeight               (Nodo*                     a,
                                                  Nodo*                     b);
    virtual void         execute                 ( ) = 0; 
    virtual void         executeOneIt            ( ) = 0; 
    Nodo*                getLastNeuron           ( );
    int                  getAmountWeights        ( );
    int                  getAmountNeurons        ( );
   // Weight*              getWeight               (int                       i);
    double                  getNodeDrawRadius       ( ) const;     
    int                  getMaxSize              ( ) const;         
    std::list<Weight*>*  getWeights              ( );
    int                  getNodeCount            ( ); 
    std::vector<Nodo*>*  getNodes                ( );
    virtual void         initialize              (std::string         fileData) = 0;
    void                 loadDataSet             (std::string         fileName); 
    void                 printConections         ( );  
    void                 printNeighbors          ( ); 
    void                 printNodos              ( );
    void                 putNoiseInData          (float sigma, int repetitions); 
    Nodo*                findBestNeuron          (Sample*                    s);   
    void                 saveGraph               (std::string fileName = "graph_nn_temp.dot");
    void                 savePdfGraph            (std::string fileName);
    int                  getMaxEpoch             ( ) const;    
    void                 setMaxSize              (int maxSize);    
    void                 setMaxEpoch             (int maxEpoch);
    void                 setNodeDrawRadius       (int NodeDrawRadius);

};

#endif	/* BASICNEURALNETWORK_H */

