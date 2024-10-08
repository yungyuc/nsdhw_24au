#include <pybind11/pybind11.h>
#include <pybind11/stl.h> 
#include "vector_angle.h"

namespace py = pybind11;

PYBIND11_MODULE(_vector, m) {
    m.doc() = "HW2 Q2";
    
    // Binding the CalculateAngle function
    m.def("calculate_angle", &calculate_angle, "Calculate angle between two 2D vectors",
          py::arg("v1"), py::arg("v2"));
}