#include "line.h"

Line::Line(const Line &l) {
    points_.assign(l.points_.begin(), l.points_.end());
}

Line::Line(std::size_t size) {
    if (size != 0) {
        points_.assign(size, Point());
    }
}

Line::~Line() {
    points_.clear();
}

std::size_t Line::size() const {
    return points_.size();
}

float const & Line::x(std::size_t it) const {
    return points_.at(it).x();
}

float & Line::x(std::size_t it) {
    return points_.at(it).x();
}

float const & Line::y(std::size_t it) const {
    return points_.at(it).y();
}

float & Line::y(std::size_t it) {
    return points_.at(it).y();
}
