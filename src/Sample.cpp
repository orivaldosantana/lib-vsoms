/* 
 * File:   Sample.cpp
 * Author: oriva
 * 
 * Created on 10 de Outubro de 2014, 14:20
 */

#include "Sample.h"

Sample::Sample(){
    
}

Sample::Sample(int s) {
    for (int i = 0; i < s; i++) {
        information.push_back(0);
    }
}

Sample::Sample(std::vector<double>& info){
    information = info; 
}

Sample::Sample(const Sample& orig) {
     
    information = orig.information; 
}

Sample Sample::operator +(Sample& sIn) {
    int size = information.size(); 
    Sample r(size);
    for (int i = 0; i < size; i++) {
        r.information[i] = this->information[i] + sIn.information[i];
    }
    return r;
}

Sample Sample::operator -(Sample& sIn) {
    int size = information.size();     
    Sample r(size);
    for (int i = 0; i < size; i++) {
        r.information[i] = this->information[i] - sIn.information[i];
    }
    return r;
}

Sample Sample::operator /(double d) {
    int size = information.size();     
    Sample r(size);
    for (int i = 0; i <  size; i++) {
        r.information[i] = this->information[i] / d;
    }
    return r;
}

double Sample::distance(Sample& sIn){
   double sum = 0;
   std::vector<double>::iterator itB;
   std::vector<double>::iterator itA;
   itB = sIn.information.begin();
   for (itA = information.begin(); (itA < information.end()) and (itB < sIn.information.end()); itA++) {
      sum +=  (*itA - *itB)*(*itA - *itB);  // (ai - bi)^2 
      itB++;
   }
   return sqrt(sum);
}

double Sample::partialDistance(Sample& sIn, Range& r) {
   double sum = 0;
   int ib = r.begin;
   for (int ia = r.begin;( ia < r.end ) and (ib < r.end) and (ia < this->information.size()) and (ib < sIn.information.size()); ia++) {
      sum +=  (information[ia] - sIn.information[ib])*(information[ia] - sIn.information[ib]);  // (ai - bi)^2 
      ib++;
   }
   return sqrt(sum); 
}

std::string Sample::toString() {
    std::stringstream result;
    for (int i = 0; i < information.size(); i++) {
        result << information.at(i) << " ";
    }
    std::string s = result.str(); 
    return s;
}
 
void Sample::getFeatures(std::vector<double>  &info){
    info = information; 
}

double Sample::getFeature(int index){
    double v = 0;
    try {
        v = information.at(index); 
    }
    catch (exception& e)
    {
        cout <<" Erro ao acessar índice do vetor de características: " << e.what() << endl;
    }
    return v;
}

int Sample::getSize() {
    return information.size();
}

void Sample::putNormalNoise(double s){
    for ( std::vector<double>::iterator itI = information.begin(); itI != information.end(); itI++ ) {
      *itI += Utils::normalDistribution(0,s);
   }
}

void Sample::setFeatures(std::vector<double>  &info){
    information = info; 
}

Sample::~Sample() {
}

