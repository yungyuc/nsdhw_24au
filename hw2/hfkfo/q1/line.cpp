#include "line.hpp"
#include<iostream>

Line::Line(){
    m_node = {};
}

Line::Line(Line const &tmp ){
    m_node = tmp.m_node;
}

Line::Line(size_t size){
    m_node.resize(size);
}

Line & Line::operator=(Line const &tmp){
    m_node = tmp.m_node;
    return *this;
}

Line::~Line(){
    m_node.clear();
}

size_t Line::size() const{
    return this->m_node.size();
}

float const & Line::x(size_t it) const{
    return this->m_node.at(it).first;
}

float & Line::x(size_t it){
    return this->m_node.at(it).first;
}

float const & Line::y(size_t it) const{
    return this->m_node.at(it).second;
}

float & Line::y(size_t it){
    return this->m_node.at(it).second;
}



