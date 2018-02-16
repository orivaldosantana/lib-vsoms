/* 
 * File:   Conexion.h
 * Author: oriva
 *
 * Created on 13 de Outubro de 2014, 17:27
 */

#ifndef CONEXION_H
#define	CONEXION_H

#include "Nodo.h"

#include <limits> 

class Conexion {
public:
    Conexion();
    Conexion(const Conexion& orig);
    virtual ~Conexion();
    Conexion(Nodo* n1, Nodo* n2, float d);

    void            setValues(Nodo* n1, Nodo* n2, float d);
    void            setDistance(double distance);
    double          getDistance() const;
    void            setTwo(Nodo* two);
    Nodo*           getTwo() const;
    void            setOne(Nodo* one);
    Nodo*           getOne() const;
    
private:
    Nodo* one;
    Nodo* two;
    double distance;

};

#endif	/* CONEXION_H */

