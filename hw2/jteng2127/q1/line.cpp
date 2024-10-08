#include "line.hpp"

#include <iostream>
#include <vector>

Line::Line(size_t size) {
  vx.resize(size);
  vy.resize(size);
}

float const &Line::x(size_t it) const { return vx[it]; }

float &Line::x(size_t it) { return vx[it]; }

float const &Line::y(size_t it) const { return vy[it]; }

float &Line::y(size_t it) { return vy[it]; }

size_t Line::size() const { return vx.size(); }