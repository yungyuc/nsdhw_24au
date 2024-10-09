#ifndef LINE_H
#define LINE_H

#include <cstddef>
#include <vector>

class Line {
    std::vector<float> x_datas;
    std::vector<float> y_datas;
public:
    Line() = default;
    Line(Line const & );
    Line(Line       &&);
    Line & operator=(Line const & );
    Line & operator=(Line       &&);
    Line(size_t size);
    ~Line() = default;
    size_t size() const;
    float const & x(size_t it) const;
    float & x(size_t it);
    float const & y(size_t it) const;
    float & y(size_t it);
};

#endif