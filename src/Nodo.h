/* 
 * File:   Nodo.h
 * Author: oriva
 *
 * Created on 13 de Outubro de 2014, 17:15
 */

#ifndef NODO_H
#define	NODO_H

#include <iostream> 
#include "Weight.h"
#include "Sample.h"
#include <list>

class Weight;

class Nodo: public Sample  {
     
public:
    
    Nodo                ( ); 
    Nodo                (const Nodo&               orig);
    Nodo                (const Sample                &s,
                         std::string           l = "n ",
                         std::string           d = "d "); 
    virtual ~Nodo();
    void                addNeighbor                 (Nodo*                   n);
    void                addWeight                   (Weight*                iw);
    void                clear                       ( );
    bool                isInserted                  ( );
    bool                isNeighbor                  (Nodo*                   n);  
    Weight*             getCommomWeight             (Nodo*                   n); 
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
    void                removeWeight                (Weight*                 w);
    void                removeNeighbor              (Nodo*                   n);
    void                updateFeatures              (double                  d,
                                                     Sample*                 s);
    
     

protected:
    std::list<Weight*>          weights;
    std::list<Nodo*>           *neighbors;
    std::string                 label;
    std::string                 description;
    bool                        inserted;
};

#endif	/* NODO_H */

