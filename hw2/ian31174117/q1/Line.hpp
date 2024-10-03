#include <vector>
#include <iostream>

class Line
{
public:
    Line(size_t size);
    Line(Line const & _line);
    //Line(Line       && _line);
    Line & operator=(Line const & _line);
    //Line & operator=(Line       && _line);
    ~Line();
    size_t size() const;
    //float const & x(size_t it) const;
    float & x(size_t it);
    //float const & y(size_t it) const;
    float & y(size_t it);
private:
    // Member data.
    std::vector<float> xs;
    std::vector<float> ys;
};