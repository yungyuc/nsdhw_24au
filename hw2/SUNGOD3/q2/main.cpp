#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

double calc_angle(const std::pair<double, double>& v1, const std::pair<double, double>& v2) {
    if (v1 == std::make_pair(0.0, 0.0) || v2 == std::make_pair(0.0, 0.0)) {
        throw std::invalid_argument("One of the vectors is the zero vector");
    }
    return std::abs(std::atan2(v1.first * v2.second - v1.second * v2.first,
                               v1.first * v2.first + v1.second * v2.second));
}

PYBIND11_MODULE(_vector, m) {
    m.def("calc_angle", &calc_angle, "A function that calculates the angle between two vectors");
}