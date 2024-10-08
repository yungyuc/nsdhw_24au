#include <vector>

class Line {
 public:
  Line(size_t size);
  float const &x(size_t it) const;
  float &x(size_t it);
  float const &y(size_t it) const;
  float &y(size_t it);
  size_t size() const;
 private:
  std::vector<float> vx;
  std::vector<float> vy;
};