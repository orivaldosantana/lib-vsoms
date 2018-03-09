/* 
 * File:   Nodo.h
 * Author: oriva
 *
 * Created on 13 de Outubro de 2014, 17:15
 */

#ifndef NODO_H
#define	NODO_H

#include <iostream> 
#include "Edge.h"
#include "Sample.h"
#include <list>

#include "json.hpp"

class Edge;

class Nodo: public Sample  {
     
public:
    
    Nodo                ( );
    Nodo                (nlohmann::json& jsonFile); 
    Nodo                (const Nodo&               orig);
    Nodo                (const Sample                &s,
                         std::string           l = "n ",
                         std::string           d = "d "); 
    virtual ~Nodo();
    void                addNeighbor                 (Nodo*                   n);
    void                addEdge                   (Edge*                iw);
    void                clear                       ( );
    bool                isInserted                  ( );
    bool                isNeighbor                  (Nodo*                   n);  
    Edge*             getCommomEdge             (Nodo*                   n); 
    std::string         getLabel                    ( ); 
    double              getFeature                  (int                     i);        
    std::list<Nodo*>*   getNeighbors                ( );
    int                 getNeighborsSize            ( ); 
    void                print                       ( );
    void                printNeigbors               ( ); 
    void                setInserted                 (bool b = true); 
    void                setFeatures                 (Sample                 *s); 
    void                setFeature                  (double f, int i); 

    //std::string         toString                    ( );
    void                removeEdge                (Edge*                 w);
    void                removeNeighbor              (Nodo*                   n);
    void                updateFeatures              (double                  d,
                                                     Sample*                 s);
    // métodos para exportar para JSON 
    nlohmann::json toJson(); 
    void  jsonInformationToVectorInformation(nlohmann::json& jsonFile);
     

protected:
    std::list<Edge*>            edges;
    std::list<Nodo*>           *neighbors;
    std::string                 label;
    std::string                 description;
    bool                        inserted;
    bool                        winner; 
};

#endif	/* NODO_H */

