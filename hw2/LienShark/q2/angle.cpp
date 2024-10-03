#include <vector>
#include <iostream>
#include <cmath>
#include <pybind11/pybind11.h>
namespace py = pybind11;
using namespace std;

double rad_calculate(tuple<double , double> a , tuple<double , double> b){
    double dot = get<0>(a) * get<0>(b) + get<1>(a) * get<1>(b);
    double dist_a = sqrt(pow(get<0>(a),2) + pow(get<1>(a),2)); 
    double dist_b = sqrt(pow(get<0>(b),2) + pow(get<1>(b),2));
    if(dist_a == 0 || dist_b == 0){return NAN;}else{
        double cos = dot/(dist_a * dist_b);
        double rad = acos(cos);
        return rad;
    }
}

PYBIND11_MODULE(_vector , m){
    m.def("radian" , &rad_calculate , "calculate the radian between vector A and B"
          , py::arg("A") , py::arg("B"));
}
