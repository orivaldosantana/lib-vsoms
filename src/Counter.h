/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Counter.h
 * Author: samuel
 *
 * Created on 25 de Dezembro de 2017, 09:58
 */

#ifndef COUNTER_H
#define COUNTER_H
#include <iostream>
#include <string>

class Counter {
public:

    Counter(int _count = 0);
    Counter(int _count, std::string _label);

    Counter operator++(int);
 


    std::string label;
    int count;


};

#endif /* COUNTER_H */

