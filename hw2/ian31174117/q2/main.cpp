#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <cmath>
float cal_angle_between_vec(const std::vector<float> &vec1, const std::vector<float> &vec2) {
    if(vec1.size()!=2 || vec2.size()!=2){
        throw std::invalid_argument("The size of the vectors must be 2");
    }
    float dot_product = 0;
    float norm_vec1 = 0;
    float norm_vec2 = 0;
    for (int i = 0; i < vec1.size(); i++) {
        dot_product += vec1[i] * vec2[i];
        norm_vec1 += vec1[i] * vec1[i];
        norm_vec2 += vec2[i] * vec2[i];
    }
    norm_vec1 = sqrt(norm_vec1);
    norm_vec2 = sqrt(norm_vec2);
    return acos(dot_product / (norm_vec1 * norm_vec2));
}

PYBIND11_MODULE(_vector, m) {
    m.def("cal_angle_between_vec", &cal_angle_between_vec, "A function that calculates the angle between two vectors");
}