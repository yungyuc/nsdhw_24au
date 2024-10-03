#include <pybind11/pybind11.h>
#include <iostream>
#include <cmath>
using namespace std;
namespace py = pybind11;

float angle_cal(float node1_x, float node1_y, float node2_x, float node2_y){
    float dot = node1_x*node2_x + node1_y*node2_y;
    float x_val = sqrt(node1_x*node1_x + node1_y*node1_y);
    float y_val = sqrt(node2_x*node2_x + node2_y*node2_y);

    return acos(dot/(x_val*y_val));
}

PYBIND11_MODULE(_vector, m){
    m.def("angle_cal", &angle_cal, " calculates the angle");
}