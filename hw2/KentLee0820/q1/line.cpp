#include "line.hpp"

Line::Line(): _size(0) {}


Line::Line(size_t size): _size(size) 
{
    _x.resize(size);
    _y.resize(size);
}


Line::~Line()
{
    _x.clear();
    _y.clear();
}

Line::Line(Line const & line)
    : _size(line._size), _x(line._x), _y(line._y) {}


Line::Line(Line && line) 
{
    _size = std::move(line._size);
    _x = std::move(line._x);
    _y = std::move(line._y);
}


Line & Line::operator=(Line const & line)
{
    if (this != &line) {
        _size = line._size;
        _x = line._x;
        _y = line._y;
    }
    return *this;
}


Line & Line::operator=(Line && line)
{
    if (this != &line) {
        _size = std::move(line._size);
        _x = std::move(line._x);
        _y = std::move(line._y);
    }
    return *this;
}


size_t Line::size() const 
{
    return _size;
}


float const & Line::x(size_t it) const
{
    return _x.at(it);
}


float & Line::x(size_t it)
{
    return _x.at(it);
}


float const & Line::y(size_t it) const
{
    return _y.at(it);
}


float & Line::y(size_t it)
{
    return _y.at(it);
}

