#include <vector>
#include <algorithm>

#ifndef LINE
#define LINE

class Line{
public:
    Line();
    Line(Line const & );
    Line & operator=(Line const & );
    Line(size_t size);
    ~Line();
    size_t size() const;
    float const & x(size_t it) const;
    float & x(size_t it);
    float const & y(size_t it) const;
    float & y(size_t it);
private:
    std::vector<float> datax;
    std::vector<float> datay;
    size_t datasize;
    // Member data.
};

#endif