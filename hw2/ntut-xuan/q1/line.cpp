#include "line.hpp"
#include <string>
#include <utility>

Line::Line(Line const &line) : x_datas(line.x_datas), y_datas(line.y_datas) {
    if(line.x_datas.size() != line.y_datas.size()){
        throw std::string("Size of x and y is not equal.");
    }
}

Line::Line(Line &&line) : x_datas(std::move(line.x_datas)), y_datas(std::move(line.x_datas)){
    if(line.x_datas.size() != line.y_datas.size()){
        throw std::string("Size of x and y is not equal.");
    }
}

Line& Line::operator=(Line const &line){
    if(line.x_datas.size() != line.y_datas.size()){
        throw std::string("Size of x and y is not equal.");
    }
    this->x_datas = line.x_datas;
    this->y_datas = line.y_datas;
    return *this;
}

Line& Line::operator=(Line &&line){
    if(line.x_datas.size() != line.y_datas.size()){
        throw std::string("Size of x and y is not equal.");
    }
    this->x_datas = std::move(line.x_datas);
    this->y_datas = std::move(line.y_datas);
    return *this;
}

Line::Line(size_t size){
    this->x_datas.resize(size);
    this->y_datas.resize(size);
}

size_t Line::size() const {
    return this->x_datas.size();
}

float const & Line::x(size_t it) const {
    if(it >= this->x_datas.size()){
        throw std::string("Out of range when access x array.");
    }
    return this->x_datas.data()[it];
}

float & Line::x(size_t it) {
    if(it >= this->x_datas.size()){
        throw std::string("Out of range when access x array.");
    }
    return this->x_datas.data()[it];
}

float const & Line::y(size_t it) const {
    if(it >= this->y_datas.size()){
        throw std::string("Out of range when access y array.");
    }
    return this->y_datas.data()[it];
}

float & Line::y(size_t it) {
    if(it >= this->x_datas.size()){
        throw std::string("Out of range when access y array.");
    }
    return this->y_datas.data()[it];
}