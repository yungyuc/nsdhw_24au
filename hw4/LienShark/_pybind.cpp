#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "_matrix.hpp"
#include "_allocate.hpp"

PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "maxtrix multiply function and memory tracking functions";
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_mkl", &multiply_mkl);
    m.def("multiply_tile", &multiply_tile);
    m.def("bytes", &CustomAllocator<double>::bytes, "Get the total bytes currently used by the allocator");
    m.def("allocated", &CustomAllocator<double>::allocated, "Get the total bytes allocated by the allocator");
    m.def("deallocated", &CustomAllocator<double>::deallocated, "Get the total bytes deallocated by the allocator");
    pybind11::class_<Matrix>(m, "Matrix")        
        .def(pybind11::init<size_t, size_t>())
        .def("__setitem__", [](Matrix &mat1, pair<size_t, size_t> row_col, double val) 
        {
            mat1(row_col.first, row_col.second) = val;
        })
        .def("__getitem__", [](Matrix &mat, pair<size_t, size_t> row_col)
        {
            return mat(row_col.first, row_col.second);
        })
        .def("__eq__", &Matrix::operator==)
        .def_property("nrow", &Matrix::nrow, nullptr)
        .def_property("ncol", &Matrix::ncol, nullptr);
}