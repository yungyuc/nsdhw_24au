#include "line.hpp"
#include <iostream>

Line::Line(size_t n) : n(n), point(n) {}

Line::~Line() {}

size_t Line::size() { return n; }

void Line::check(size_t i) const { 
    if (i >= n) {
        throw std::out_of_range("Index out of range");
    }
}

float& Line::x(size_t i) { 
    check(i);
    return point[i].first; 
}

float& Line::y(size_t i) {
    check(i);
    return point[i].second; 
}

float Line::x(size_t i) const { 
    check(i);
    return point[i].first; 
}

float Line::y(size_t i) const { 
    check(i);
    return point[i].second; 
}
