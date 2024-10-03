#include "line.hpp"


Line::Line(Line const &other){
    points_.reserve(other.size());
    for(size_t i = 0; i < other.size(); i++)
        points_.emplace_back(other.x(i), other.y(i));
}

Line::Line(Line &&other)
    : points_(std::move(other.points_))
{
}

Line & Line::operator=(Line const &other){
    points_.reserve(other.size());
    for(size_t i = 0; i < other.size(); i++)
        points_.emplace_back(other.x(i), other.y(i));
    return *this;
}

Line & Line::operator=(Line &&other){
    points_ = std::move(other.points_);
    return *this;
}

Line::Line(size_t size){
    points_.resize(size);
}

size_t Line::size() const {
    return points_.size();
}

float const & Line::x(size_t it) const {
    return points_[it].first;
}

float & Line::x(size_t it){
    return points_[it].first;
}

float const & Line::y(size_t it) const {
    return points_[it].second;
}

float & Line::y(size_t it){
    return points_[it].second;
}