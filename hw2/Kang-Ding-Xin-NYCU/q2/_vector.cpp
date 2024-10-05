#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cmath>
#include <iostream>

namespace py = pybind11;

float dot_pro(std::vector<float> v1, std::vector<float> v2){
    return v1[0]*v2[0]+v1[1]*v2[1];
}

float norm_pro(std::vector<float> v1, std::vector<float> v2){
    float v1_norm = std::sqrt(v1[0]*v1[0]+v1[1]*v1[1]);
    float v2_norm = std::sqrt(v2[0]*v2[0]+v2[1]*v2[1]);
    return v1_norm*v2_norm;
}

float angle(std::vector<float> v1, std::vector<float> v2){
    if((v1[0] == 0 && v1[1] == 0) || (v2[0] == 0 && v2[1] == 0)){
        throw std::invalid_argument("invalid input");
    }
    float angl = std::acos(dot_pro(v1, v2) / norm_pro(v1, v2));
    return angl;
}

PYBIND11_MODULE(_vector, m) {
    m.def("angle", &angle, "calculate angle");
}