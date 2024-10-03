# include <iostream>
# include <utility>
# include <cmath>
# include <pybind11/pybind11.h>

namespace py = pybind11;

double calculateAngle(std::pair<double, double> v1, std::pair<double, double> v2) {
    if ((v1.first == 0 && v1.second == 0) || (v2.first == 0 && v2.second == 0)) {
        throw std::invalid_argument("The vectors should not be zero vector.");
    }

    double inner_product = v1.first * v2.first + v1.second * v2.second;
    double v1_norm = std::sqrt(v1.first * v1.first + v1.second * v1.second);
    double v2_norm = std::sqrt(v2.first * v2.first + v2.second * v2.second);
    double angle = std::acos(inner_product / (v1_norm * v2_norm));
    return angle;
}

PYBIND11_MODULE(_vector, m) {
    m.doc() = "Module for vectors."; // optional module docstring

    m.def("calculateAngle", &calculateAngle, "Calculate the angle of two vectors.");
}