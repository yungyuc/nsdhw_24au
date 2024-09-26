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
    float const &x(size_t it) const;
    float &x(size_t it);
    float const &y(size_t it) const;
    float &y(size_t it);
private:
    std::vector<std::pair<float, float>> m_points; // 2D points
}; /* end class Line */
