#include <cmath>
#include <stdexcept>
#include "vector_angle.h"

double calculate_angle(const std::vector<double>& v1, const std::vector<double>& v2) {
  if (v1.size() != 2 || v2.size() != 2) {
    throw std::invalid_argument("Vectors must be 2-dimensional");
  }

  double x1 = v1[0], y1 = v1[1];
  double x2 = v2[0], y2 = v2[1];

  double dot_product = x1 * x2 + y1 * y2;

  double magnitude_v1 = std::sqrt(x1 * x1 + y1 * y1);
  double magnitude_v2 = std::sqrt(x2 * x2 + y2 * y2);

  double cos_theta = dot_product / (magnitude_v1 * magnitude_v2);

  return std::acos(cos_theta);
}