#include <pybind11/pybind11.h>
#include <cmath>
int add(int i, int j) { return i + j; }

double ang(double x1, double y1, double x2, double y2) {
  double inner = x1 * x2 + y1 * y2;
  double mag1 = sqrt(x1 * x1 + y1 * y1);
  double mag2 = sqrt(x2 * x2 + y2 * y2);
  double cos = inner / (mag1 * mag2);
  return acos(cos);
}

PYBIND11_MODULE(fdct, m) {
    m.def("add", &add, "A function which adds two numbers");
    m.def("ang", &ang, "Compute angle between two vector.");
}
