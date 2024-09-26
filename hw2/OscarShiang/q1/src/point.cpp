#include "point.h"

Point::Point(float x, float y): x_(x), y_(y) {}

Point::Point() {}

Point::~Point() {}

float const & Point::x() const {
    return x_;
}

float & Point::x() {
    return x_;
}

float const & Point::y() const {
    return y_;
}

float & Point::y() {
    return y_;
}
