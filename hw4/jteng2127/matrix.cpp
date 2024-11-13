#include "matrix.hpp"

#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include <vector>
#include <cstring>
#include <stdexcept>
#include <mkl.h>

namespace py = pybind11;

Matrix::Matrix(size_t nrow, size_t ncol)
    : m_nrow(nrow), m_ncol(ncol), data(nrow * ncol) {}

Matrix::Matrix(const Matrix& other)
    : m_nrow(other.m_nrow),
      m_ncol(other.m_ncol),
      data(other.data) {}

Matrix::Matrix(Matrix&& other)
    : m_nrow(std::move(other.m_nrow)),
      m_ncol(std::move(other.m_ncol)),
      data(std::move(other.data)) {
  other.m_nrow = 0;
  other.m_ncol = 0;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    m_nrow = other.m_nrow;
    m_ncol = other.m_ncol;
    data = std::vector<double, CustomAllocator<double>>(other.data);
  }
  return *this;
}

Matrix::~Matrix() {}

size_t Matrix::nrow() const { return m_nrow; }

size_t Matrix::ncol() const { return m_ncol; }

double* Matrix::getData() const {
  double* d = const_cast<double*>(data.data());
  return d;
}

double& Matrix::operator()(size_t i, size_t j) {
  if (i >= m_nrow || j >= m_ncol) {
    throw std::out_of_range("Index out of bounds");
  }
  return data[i * m_ncol + j];
}

const double& Matrix::operator()(size_t i, size_t j) const {
  if (i >= m_nrow || j >= m_ncol) {
    throw std::out_of_range("Index out of bounds");
  }
  return data[i * m_ncol + j];
}

bool Matrix::operator==(const Matrix& m) const {
  if (m_nrow != m.m_nrow || m_ncol != m.m_ncol) {
    return false;
  }
  return data == m.data;
}

Matrix multiply_naive(const Matrix& A, const Matrix& B) {
  if (A.ncol() != B.nrow()) {
    throw std::invalid_argument(
        "Matrix dimensions do not match for multiplication");
  }

  Matrix C(A.nrow(), B.ncol());
  for (size_t i = 0; i < A.nrow(); ++i) {
    for (size_t j = 0; j < B.ncol(); ++j) {
      for (size_t k = 0; k < A.ncol(); ++k) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
  return C;
}

Matrix multiply_tile(const Matrix& A, const Matrix& B, size_t tile_size) {
  if (A.ncol() != B.nrow()) {
    throw std::invalid_argument(
        "Matrix dimensions do not match for multiplication");
  }

  Matrix C(A.nrow(), B.ncol());
  for (size_t i = 0; i < A.nrow(); i += tile_size) {
    for (size_t j = 0; j < B.ncol(); j += tile_size) {
      for (size_t k = 0; k < A.ncol(); k += tile_size) {
        size_t imax = std::min(i + tile_size, A.nrow());
        size_t jmax = std::min(j + tile_size, B.ncol());
        size_t kmax = std::min(k + tile_size, A.ncol());

        for (size_t ii = i; ii < imax; ++ii) {
          for (size_t jj = j; jj < jmax; ++jj) {
            for (size_t kk = k; kk < kmax; ++kk) {
              C(ii, jj) += A(ii, kk) * B(kk, jj);
            }
          }
        }
      }
    }
  }
  return C;
}

// Matrix multiplication using Intel MKL
Matrix multiply_mkl(const Matrix& A, const Matrix& B) {
  if (A.ncol() != B.nrow()) {
    throw std::invalid_argument(
        "Matrix dimensions do not match for multiplication");
  }

  Matrix C(A.nrow(), B.ncol());

  // Use MKL's cblas_dgemm for matrix multiplication
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
              A.nrow(), B.ncol(), A.ncol(),
              1.0,
              A.getData(), A.ncol(),
              B.getData(), B.ncol(),
              0.0,
              C.getData(), C.ncol());

  return C;
}

std::size_t bytes() {
  return CustomAllocator<double>::bytes();
}

std::size_t allocated() {
  return CustomAllocator<double>::allocated();
}

std::size_t deallocated() {
  return CustomAllocator<double>::deallocated();
}

PYBIND11_MODULE(_matrix, m) {
  py::class_<Matrix>(m, "Matrix")
      .def(py::init<size_t, size_t>(), "Constructor with rows and columns")
      .def_property_readonly("nrow", &Matrix::nrow, "Get number of rows")
      .def_property_readonly("ncol", &Matrix::ncol, "Get number of columns")
      .def("getData", &Matrix::getData, "Get the pointer to the matrix data")
      .def("__call__",
           (double& (Matrix::*)(size_t, size_t)) & Matrix::operator(),
           "Access matrix elements with (i, j) operator")
      .def("__call__",
           (const double& (Matrix::*)(size_t, size_t) const) &
               Matrix::operator(),
           "Access matrix elements with (i, j) operator (const)")
      .def(
          "__setitem__",
          [](Matrix& m, std::pair<size_t, size_t> idx, double value) {
            m(idx.first, idx.second) = value;
          },
          "Set matrix element at (i, j)")
      .def(
          "__getitem__",
          [](const Matrix& m, std::pair<size_t, size_t> idx) -> double {
            return m(idx.first, idx.second);
          },
          "Get matrix element at (i, j)")
      .def("getData", &Matrix::getData, py::return_value_policy::reference)
      .def(py::self == py::self, "Equality operator for matrices");

  m.def("multiply_naive", &multiply_naive, "Naive matrix multiplication",
        py::arg("A"), py::arg("B"));
  m.def("multiply_tile", &multiply_tile, "Tiled matrix multiplication",
        py::arg("A"), py::arg("B"), py::arg("tile_size"));
  m.def("multiply_mkl", &multiply_mkl, "MKL optimized matrix multiplication",
        py::arg("A"), py::arg("B"));
  m.def("bytes", &bytes, "Get total bytes allocated");
  m.def("allocated", &allocated, "Get total bytes allocated");
  m.def("deallocated", &deallocated, "Get total bytes deallocated");
}
