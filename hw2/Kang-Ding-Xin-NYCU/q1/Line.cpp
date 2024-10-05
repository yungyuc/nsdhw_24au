#include "Line.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

Line::Line(Line const & other){
    datasize = other.size();
    for(int i = 0;i < datasize;i++){
        datax.push_back(other.x(i));
        datay.push_back(other.y(i));
    }
}

Line & Line::operator=(Line const & other){
    datasize = other.size();
    for(int i = 0;i < datasize;i++){
        datax.push_back(other.x(i));
        datay.push_back(other.y(i));
    }
    return *this;
}

Line::Line(size_t size){
    datax.reserve(size);
    datay.reserve(size);
    datasize = size;
}

Line::~Line(){
    datax.clear();
    datay.clear();
}

size_t Line::size() const{
    return datasize;
}

float const & Line::x(size_t it) const{
    if(it > datasize - 1){
        throw std::out_of_range("Line index out of range");
    }
    return datax[it];
}

float & Line::x(size_t it){
    if(it > datasize - 1){
        throw std::out_of_range("Line index out of range");
    }
    return datax[it];
}

float const & Line::y(size_t it) const{
    if(it > datasize - 1){
        throw std::out_of_range("Line index out of range");
    }
    return datay[it];
}

float & Line::y(size_t it){
    if(it > datasize - 1){
        throw std::out_of_range("Line index out of range");
    }
    return datay[it];
}