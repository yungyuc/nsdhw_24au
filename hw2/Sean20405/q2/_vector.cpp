# include <iostream>
# include <utility>
# include <cmath>
# include <pybind11/pybind11.h>

namespace py = pybind11;

double calculateAngle(std::pair<double, double> p1, std::pair<double, double> p2) {
    double inner_product = p1.first * p2.first + p1.second * p2.second;
    double p1_norm = std::sqrt(p1.first * p1.first + p1.second * p1.second);
    double p2_norm = std::sqrt(p2.first * p2.first + p2.second * p2.second);
    double angle = std::acos(inner_product / (p1_norm * p2_norm));
    return angle;
}

PYBIND11_MODULE(_vector, m) {
    m.doc() = "Module for vectors."; // optional module docstring

    m.def("calculateAngle", &calculateAngle, "Calculate the angle of two vectors.");
}