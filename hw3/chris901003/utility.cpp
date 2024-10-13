#include "_matrix.hpp"

#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>

Matrix multiply_naive(Matrix const &m1, Matrix const &m2) {
    if(m1.ncol() != m2.nrow()){
        throw std::invalid_argument("matrix size does not match");
    }
    Matrix result(m1.nrow(), m2.ncol());
    for(size_t i = 0; i < m1.nrow(); i++){
        for(size_t j = 0; j < m2.ncol(); j++){
            for(size_t k = 0; k < m1.ncol(); k++){
                result(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }
    return result;
}

Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, size_t tsize) {

  if (mat1.ncol() != mat2.nrow()) {
    throw std::out_of_range("the number of first matrix column "
                            "differs from that of second matrix row");
  }

  Matrix result(mat1.nrow(), mat2.ncol());
  size_t max_i = mat1.nrow();
  size_t max_j = mat2.ncol();
  size_t max_k = mat1.ncol();

  for (size_t i = 0; i < max_i; i += tsize) {
    for (size_t j = 0; j < max_j; j += tsize) {
      for (size_t k = 0; k < max_k; k += tsize) {
        // compute the upper bound of the tile
        size_t upper_i = std::min(i + tsize, max_i);
        size_t upper_j = std::min(j + tsize, max_j);
        size_t upper_k = std::min(k + tsize, max_k);

        for (size_t t_i = i; t_i < upper_i; ++t_i) {
          for (size_t t_j = j; t_j < upper_j; ++t_j) {
            double sum = 0.0; // sum will live in the register
            for (size_t t_k = k; t_k < upper_k; ++t_k) {
              sum += mat1(t_i, t_k) * mat2(t_k, t_j);
            }
            result(t_i, t_j) += sum;
          }
        }
      }
    }
  }

  return result;
}

Matrix multiply_mkl(const Matrix &a, const Matrix &b) {
    if(a.ncol() != b.nrow()){
        throw std::invalid_argument("matrix size does not match");
    }
    Matrix result(a.nrow(), b.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a.nrow(), b.ncol(), a.ncol(), 1.0, a.getData(), a.ncol(), b.getData(), b.ncol(), 0.0, result.getData(), result.ncol());
    return result;
}


PYBIND11_MODULE(_matrix, m) {
    m.doc() = "Matrix multiplication module";

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def(pybind11::init<size_t, size_t, double>())
        .def(pybind11::init<size_t, size_t, std::vector<double> &>())
        .def(pybind11::init<const Matrix &>())
        .def("index", &Matrix::index)
        .def("getData", &Matrix::getData)
        .def("getVector", &Matrix::getVector)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__getitem__", [](Matrix &m, std::vector<std::size_t> idx) {
            return m(idx[0], idx[1]);
        })
        .def("__setitem__", [](Matrix &m, std::vector<std::size_t> idx, double val) {
            m(idx[0], idx[1]) = val;
        })
        .def("__eq__", &Matrix::operator==);

    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}