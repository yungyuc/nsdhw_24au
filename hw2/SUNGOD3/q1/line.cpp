#include "line.hpp"

Line::Line(size_t size) {
    m_points.resize(size);
}

size_t Line::size() const {
    return this->m_points.size();
}

float &Line::x(size_t it) {
    return this->m_points[it].first;
}

float &Line::y(size_t it) { 
    return this->m_points[it].second; 
};