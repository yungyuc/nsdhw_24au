#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/detail/common.h>

#include "vector.hpp"

namespace py = pybind11;

Vector::Vector(double x, double y){
    this->x = x;
    this->y = y;
}

double Vector::GetX(){
    return x;
}

double Vector::GetY(){
    return y;
}

double Vector::GetAngle(Vector other){
    if(std::sqrt(other.x * other.x) + (other.y * other.y) == 0){
        throw std::string("other vector distance is zero.");
    }

    if(std::sqrt(x * x) + (y * y) == 0){
        throw std::string("this vector distance is zero.");
    }

    return std::acos((x * other.x + y * other.y) / (this->GetDistance() * other.GetDistance()));
}

double Vector::GetDistance(){
    return std::sqrt(x * x + y * y);
}

PYBIND11_MODULE(_vector, m){
    m.doc() = R"pbdoc(
        vector
        -----------------------

        .. currentmodule:: vector

        .. autosummary::
           :toctree: _generate

           _vector
    )pbdoc";

    py::class_<Vector>(m, "Vector")
        .def(py::init())
        .def(py::init<double, double>())
        .def("GetX", &Vector::GetX, "Get X of vector")
        .def("GetY", &Vector::GetY, "Get Y of vector")
        .def("GetAngle", &Vector::GetAngle, "Get angle with other vector")
        .def("GetDistance", &Vector::GetDistance, "Get distance of vector")
        .doc() = "Vector class";
}