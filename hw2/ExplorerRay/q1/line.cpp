#include "line.hpp"

Line &Line::operator=(Line const & rhs)
{
    if (this != &rhs) {
        m_points = rhs.m_points;
    }
    return *this;
}

Line &Line::operator=(Line && rhs)
{
    if (this != &rhs) {
        std::swap(rhs.m_points, m_points);
    }
    return *this;
}

Line::Line(size_t size) {
    m_points.resize(size);
}

size_t Line::size() const {
    return this->m_points.size();
}

float const &Line::x(size_t it) const {
    return this->m_points[it].first;
}

float &Line::x(size_t it) {
    return this->m_points[it].first;
}

float const &Line::y(size_t it) const { 
    return this->m_points[it].second; 
};

float &Line::y(size_t it) { 
    return this->m_points[it].second; 
};
