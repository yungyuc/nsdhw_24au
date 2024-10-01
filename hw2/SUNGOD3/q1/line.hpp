#include <vector>
#include <cstddef>

class Line {
public:
    Line() = default;
    Line(size_t size);
    size_t size() const;
    float &x(size_t it);
    float &y(size_t it);
private:
    std::vector<std::pair<float, float>> m_points; // 2D points
}; /* end class Line */