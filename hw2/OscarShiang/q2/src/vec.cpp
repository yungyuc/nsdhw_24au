#include <cmath>
#include <pybind11/pybind11.h>

#include "vec.h"

namespace py = pybind11;

Vec::Vec(float x, float y): x_(x), y_(y) {}

float Vec::angle(Vec const &v) {
    float dot = x_ * v.x() + y_ * v.y();
    float len = this->len() * v.len();

    return acos(dot / len);
}

float Vec::len() const {
    return sqrt(pow(x_, 2) + pow(y_, 2));
}

float const & Vec::x() const {
    return x_;
}

float const & Vec::y() const {
    return y_;
}

PYBIND11_MODULE(vec, m) {
    py::class_<Vec>(m, "Vec")
        .def(py::init<float, float>())
        .def("angle", &Vec::angle)
        .def("len", &Vec::len)
        .def("x", &Vec::x)
        .def("y", &Vec::y);
}
