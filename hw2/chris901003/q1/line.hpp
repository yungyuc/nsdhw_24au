#include <cstddef>
#include <vector>
#include <utility>

class Line {
    private:
        size_t n;
        std::vector<std::pair<float, float>> point;
        void check(size_t i) const;
    public:
        Line(size_t n);
        ~Line();
        size_t size();
        float& x(size_t i);
        float& y(size_t i);
        float x(size_t i) const;
        float y(size_t i) const;
};