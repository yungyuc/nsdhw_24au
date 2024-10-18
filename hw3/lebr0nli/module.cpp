#include "_matrix.h"
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def(py::init<const Matrix &>())
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def(py::self == py::self)
        .def("__getitem__", &Matrix_getitem)
        .def("__setitem__", &Matrix_setitem);

    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile, py::arg("a"), py::arg("b"),
          py::arg("tile_size"));
    m.def("multiply_mkl", &multiply_mkl);
}