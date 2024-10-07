#include <iostream>
#include <cmath>
#include <utility>
#include <pybind11/pybind11.h>

#define pff std::pair<float, float>
#define x first
#define y second

double cal_deg(pff a, pff b)
{
    double dot_ab = a.x*b.x + a.y*b.y;
    double alen = std::sqrt(a.x*a.x + a.y*a.y);
    double blen = std::sqrt(b.x*b.x + b.y*b.y);
    if (alen == 0 || blen == 0)
        throw std::invalid_argument("vector length can not be 0");
    return std::acos(std::fmax(-1, std::fmin(1, dot_ab/(alen*blen))));
}

PYBIND11_MODULE(_vector, m) {
    m.def("cal_deg", &cal_deg, "Calculate the angle between two 2-vectors");
}
