#ifndef __LINE_HPP__
#define __LINE_HPP__

#include <vector>

using namespace std;

class Line {

public:

    Line();
    Line(size_t size);
    Line(Line const &);
    Line(Line &&);
    Line & operator=(Line const &);
    Line & operator=(Line &&);
    ~Line();
    size_t size() const;
    float const & x(size_t  it) const;
    float & x(size_t it);
    float const & y(size_t it) const;
    float & y(size_t it);


private:

    size_t _size;
    std::vector<float> _x;
    std::vector<float> _y;
};

#endif
