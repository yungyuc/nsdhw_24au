#include <pybind11/pybind11.h>
#include<iostream>

#include <cmath>

double calRadianAngle(double x1, double y1, double x2, double y2) {
  double dot = x1 * x2 + y1 * y2;
  double length1 = std::sqrt(x1 * x1 + y1 * y1);
  double length2 = std::sqrt(x2 * x2 + y2 * y2);

  if (length1 == 0 || length2 == 0) {
    throw std::invalid_argument("The length of the vector cannot be zero");
  }

  double cosine = dot / (length1 * length2);

  std::cout << "cosine: " << cosine << std::endl;
  cosine = std::max(-1.0, std::min(1.0, cosine));

  return std::acos(cosine);
}

PYBIND11_MODULE(_vector, m) {
    m.def("calRadianAngle", &calRadianAngle, "calculates the angle (in radians) between two vectors");
}
