#include "Line.hpp"

Line::Line(size_t size){
    xs.resize(size);
    ys.resize(size);
}

Line::Line(Line const & _line){
    xs = _line.xs;
    ys = _line.ys;
}

Line & Line::operator=(Line const & _line){
    xs = _line.xs;
    ys = _line.ys;
    return *this;
}

Line::~Line(){
    xs.clear();
    ys.clear();
}

size_t Line::size() const{
    return xs.size();
}

float & Line::x(size_t it){
    return xs[it];
}

float & Line::y(size_t it){
    return ys[it];
}