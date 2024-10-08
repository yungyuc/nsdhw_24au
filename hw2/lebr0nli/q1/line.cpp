#include "line.hpp"


Line::Line() : _x(), _y() {}

Line::Line(const Line &other) : _x(other._x), _y(other._y) {}

Line::Line(Line &&other) noexcept: _x(std::move(other._x)), _y(std::move(other._y)) {
}

Line &Line::operator=(const Line &other) {
    if (this != &other) {
        _x = other._x;
        _y = other._y;
    }
    return *this;
}

Line &Line::operator=(Line &&other) noexcept {
    if (this != &other) {
        _x = std::move(other._x);
        _y = std::move(other._y);
    }
    return *this;
}

Line::Line(size_t size) : _x(size), _y(size) {}

Line::~Line() = default;

size_t Line::size() const {
    return _x.size();
}

float const &Line::x(size_t it) const {
    return _x.at(it);
}

float &Line::x(size_t it) {
    return _x.at(it);
}

float const &Line::y(size_t it) const {
    return _y.at(it);
}

float &Line::y(size_t it) {
    return _y.at(it);
}

