# include "line.hpp"

Line::Line() = default;

Line::Line(Line const & rhs) = default;

Line::Line(Line && rhs) = default;

Line::~Line() = default;

Line &Line::operator=(Line const & ) = default;

Line &Line::operator=(Line &&) = default;

Line::Line(size_t size)
{
    this->m_points.resize(size);
}

size_t Line::size() const
{
    return this->m_points.size();
}

float const &Line::x(size_t it) const
{
    return this->m_points[it].first;
}

float &Line::x(size_t it)
{
    return this->m_points[it].first;
}

float const &Line::y(size_t it) const
{
    return this->m_points[it].second;
}

float &Line::y(size_t it)
{
    return this->m_points[it].second;
}