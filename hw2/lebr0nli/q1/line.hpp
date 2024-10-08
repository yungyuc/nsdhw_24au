#ifndef Q1_LINE_H_
#define Q1_LINE_H_

#include <cstddef>
#include <vector>


class Line {
public:
    Line();

    Line(Line const &);

    Line(Line &&) noexcept;

    Line &operator=(Line const &);

    Line &operator=(Line &&) noexcept;

    explicit Line(size_t size);

    ~Line();

    size_t size() const;

    float const &x(size_t it) const;

    float &x(size_t it);

    float const &y(size_t it) const;

    float &y(size_t it);

private:
    std::vector<float> _x;
    std::vector<float> _y;
}; /* end class Line */


#endif //Q1_LINE_H_
