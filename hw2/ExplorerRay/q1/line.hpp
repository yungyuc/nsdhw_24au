#include <vector>
#include <cstddef>

class Line {
public:
    Line() = default;
    Line(Line const & ) = default; // copy
    Line(Line       &&) = default; // move
    ~Line() = default;
    Line &operator=(Line const & );
    Line &operator=(Line       &&);
    Line(size_t size);
    size_t size() const;
    double const &x(size_t it) const;
    double &x(size_t it);
    double const &y(size_t it) const;
    double &y(size_t it);
private:
    std::vector<std::pair<double, double>> m_points; // 2D points
}; /* end class Line */
