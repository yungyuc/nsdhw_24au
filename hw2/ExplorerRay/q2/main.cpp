#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

double calc_angle(std::vector<double> v1, std::vector<double> v2) {
    if(v1.size() != 2 || v2.size() != 2) {
        throw std::invalid_argument("Input vectors must have size 2");
    }
    
    double dot = v1[0] * v2[0] + v1[1] * v2[1];
    double det = v1[0] * v2[1] - v1[1] * v2[0];
    return atan2(det, dot);
}

PYBIND11_MODULE(_vector, m) {
    m.doc() = "pybind11 plugin"; // optional module docstring

    m.def("calc_angle", &calc_angle, "A C++ function that calculates the angle between two 2D vectors");
}
