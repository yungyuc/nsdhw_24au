#ifndef __LINE_H__
#define __LINE_H__

#include <vector>

#include "point.h"

class Line
{
public:
    Line(const Line &l);
    Line(std::size_t size);
    ~Line();

    std::size_t size() const;

    float const & x(std::size_t it) const;
    float & x(std::size_t it);
    float const & y(std::size_t it) const;
    float & y(std::size_t it);

private:
    std::vector<Point> points_;
};

#endif /* __LINE_H__ */
