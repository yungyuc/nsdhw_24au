#include "_matrix.hpp"

// Constructor
Matrix::Matrix(size_t nrow, size_t ncol)
    : m_nrow(nrow), m_ncol(ncol), data(nrow * ncol, 0.0) {}

// Copy Constructor
Matrix::Matrix(const Matrix &other)
    : m_nrow(other.m_nrow), m_ncol(other.m_ncol), data(other.data) {}

// Assignment Operator
Matrix &Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
        data = other.data;
    }
    return *this;
}

// Accessors
size_t Matrix::nrow() const { return m_nrow; }
size_t Matrix::ncol() const { return m_ncol; }

double &Matrix::operator()(size_t row, size_t col) {
    return data[row * m_ncol + col];
}

const double &Matrix::operator()(size_t row, size_t col) const {
    return data[row * m_ncol + col];
}

bool Matrix::operator==(const Matrix &other) const {
    return m_nrow == other.m_nrow && m_ncol == other.m_ncol && data == other.data;
}

#include <pybind11/pybind11.h>
#include "_matrix.hpp"
#include "CustomAllocator.hpp"

size_t bytes() { return CustomAllocator<double>::getBytesInUse(); }
size_t allocated() { return CustomAllocator<double>::getTotalAllocated(); }
size_t deallocated() { return CustomAllocator<double>::getTotalDeallocated(); }

PYBIND11_MODULE(_matrix, m) {
    m.def("bytes", &bytes, "Get current bytes in use");
    m.def("allocated", &allocated, "Get total bytes allocated");
    m.def("deallocated", &deallocated, "Get total bytes deallocated");

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def("nrow", &Matrix::nrow)
        .def("ncol", &Matrix::ncol)
        .def("__call__", static_cast<double&(Matrix::*)(size_t, size_t)>(&Matrix::operator()))
        .def("__eq__", &Matrix::operator==);
}
