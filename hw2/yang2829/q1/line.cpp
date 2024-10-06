#include "line.hpp"
#include <iostream>
#include <vector>
#define pdd std::pair<float, float>

Line::Line(size_t size)
{
    if (size < 0) {
        std::cout << "size < 0" << std::endl;
        return;
    }
    n = size;
    points = std::vector<pdd> (3, pdd(0.0, 0.0));
}

size_t Line::size() const{ return n; }

float const & Line::x(size_t it) const
{
    if (it >= n)
        throw std::out_of_range("Index out of range");
    return points[it].first;
}

float & Line::x(size_t it)
{
    if (it >= n)
        throw std::out_of_range("Index out of range");
    return points[it].first;
}

float const & Line::y(size_t it) const
{
    if (it >= n)
        throw std::out_of_range("Index out of range");
    return points[it].second;
}

float & Line::y(size_t it)
{
    if (it >= n)
        throw std::out_of_range("Index out of range");
    return points[it].second;
}