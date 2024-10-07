#include "line.hpp"
#include <cstddef>
#include <utility>

Line::Line() {}

Line::Line(Line const &line) {
  this->_x = line._x;
  this->_y = line._y;
}

Line::Line(Line &&line) {
  this->_x = std::move(line._x);
  this->_y = std::move(line._y);
}

Line &Line::operator=(Line const &line) {
  if (this == &line)
    return *this;
  this->_x = line._x;
  this->_y = line._y;

  return *this;
}

Line &Line::operator=(Line &&line) {
  if (this == &line) {
    return *this;
  }
  this->_x = std::move(line._x);
  this->_y = std::move(line._y);

  return *this;
}

Line::Line(size_t size) {
   _x.resize(size);
   _y.resize(size);
}

size_t Line::size() const{
   return _x.size();
}

float const &Line::x(size_t it) const { return _x[it]; }

float &Line::x(size_t it) { return _x[it]; }

float const &Line::y(size_t it) const { return _y[it]; }

float &Line::y(size_t it) { return _y[it]; }

Line::~Line() {}
