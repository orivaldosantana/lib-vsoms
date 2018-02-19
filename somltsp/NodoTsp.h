/* 
 * File:   NodoTsp.h
 * Author: oriva
 *
 * Created on 17 de Outubro de 2014, 15:23
 */

#ifndef NODOTSP_H
#define	NODOTSP_H

#include "Nodo.h"

class NodoTsp: public Nodo {
public:
 
    NodoTsp             (const NodoTsp& orig);
    NodoTsp             (const Sample                &s,
                         std::string           l = "n ",
                         std::string           d = "d "); 
    virtual ~NodoTsp();
    
    void                resetNeuronWins             ( ); 
    int                 getWinsCount                ( ) const;
    void                decreaseWins                ( );
    void                increaseWins                ( ); 
    bool                isEnabled                   ( ); 
    bool                isMarkedToRemove            ( );
    bool                isMarkedToUpdate            ( );    
    void                setEnabled                  (bool              e); 
    void                setMarkedToUpdate           (bool             up);
    void                printStatus                 ( ); 
    
    
private:
    int                 winsCount;
    bool                enabled;
    bool                markedToUpdate; 
    bool                markedToRemove; 
    

};

#endif	/* NODOTSP_H */

