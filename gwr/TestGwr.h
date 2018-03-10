/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestGwr.h
 * Author: samuel
 *
 * Created on 26 de Fevereiro de 2018, 22:38
 */

#ifndef TESTGWR_H
#define TESTGWR_H

#include "Gwr.h"


class TestGwr {
public:
    TestGwr();
    TestGwr(const TestGwr& orig);
    void executeNetwork();
    virtual ~TestGwr();
private:

};

#endif /* TESTGWR_H */

