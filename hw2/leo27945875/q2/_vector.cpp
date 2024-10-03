#include <pybind11/pybind11.h>
#include <cmath>

namespace py = pybind11;


float calc_angle(float x0, float y0, float x1, float y1){
    float len0 = x0*x0 + y0*y0;
    float len1 = x1*x1 + y1*y1;
    if (len0 <= 0.f || len1 <= 0.f){
        throw std::invalid_argument("One of the 2D vector length is smaller than or equals to zero !");
    }
    return acos((x0 * x1 + y0 * y1) / sqrt((x0*x0 + y0*y0) * (x1*x1 + y1*y1)));
}


PYBIND11_MODULE(_vector, m){
    m.doc() = "leo27945875 hw2 question 2";
    m.def("calc_angle", &calc_angle, "Calculate the angle between two 2D vectors (in radian).", py::arg("x0"), py::arg("y0"), py::arg("x1"), py::arg("y1"));
}