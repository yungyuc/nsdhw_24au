#include "matrix.hpp"
#include "matrix-multiply.hpp"
#include "allocator.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) {
    m.doc() = "pybind11 matrix_2d module"; // optional module docstring

    py::class_<matrix_2d>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def_property_readonly("nrow", &matrix_2d::get_nrow)
        .def_property_readonly("ncol", &matrix_2d::get_ncol)
        .def("__setitem__", [](matrix_2d &mat, std::pair<size_t, size_t> idx, double val) {
            mat(idx.first, idx.second) = val;
        })
        .def("__getitem__", [](matrix_2d &mat, std::pair<size_t, size_t> idx) {
            return mat(idx.first, idx.second);
        })
        .def("__eq__", [](matrix_2d &mat, matrix_2d &other) {
            return mat == other;
        })
        .def_property("array", [](matrix_2d &mat) {
            return py::array_t<double>(
                {mat.get_nrow(), mat.get_ncol()}, // shape
                mat.get_buffer(), // pointer
                py::cast(mat) // handle
            );
        }, nullptr); // can directly set so without setter

    m.def("bytes", &CustomAllocator<double>::bytes);
    m.def("allocated", &CustomAllocator<double>::allocated);
    m.def("deallocated", &CustomAllocator<double>::deallocated);

    m.def("multiply_naive", &multiply_naive, "A C++ function that multiply 2D matrix (naive)");
    m.def("multiply_tile", &multiply_tile, "A C++ function that multiply 2D matrix (tile)");
    m.def("multiply_mkl", &multiply_mkl, "A C++ function that multiply 2D matrix (intel MKL)");
}
