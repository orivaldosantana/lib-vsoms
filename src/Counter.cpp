/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Counter.cpp
 * Author: samuel
 * 
 * Created on 25 de Dezembro de 2017, 09:58
 */

#include "Counter.h"

Counter::Counter(int _count) {
    count = _count;
    label = std::to_string(count);

}

Counter::Counter(int _count, std::string _label) {
    count = _count;
    label = _label;
}

Counter Counter::operator++(int) {

    count++;
    label = std::to_string(count);
    return *this;

}
