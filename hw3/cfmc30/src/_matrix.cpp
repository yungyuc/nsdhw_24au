#include <cstddef>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <utility>

using data_t = float;

namespace py = pybind11;

class Matrix {
public:
  Matrix multiply_naive(Matrix a, Matrix b) {
    if (a.ncol != b.nrow) {
      throw std::invalid_argument(
          "Matrix dimensions do not allow multiplication.");
    }

    Matrix result(a.nrow, b.ncol);
    for (size_t i = 0; i < a.nrow; ++i) {
      for (size_t j = 0; j < b.ncol; ++j) {
        for (size_t k = 0; k < a.ncol; ++k) {
          result(i, j) += a(i, k) * b(k, j);
        }
      }
    }
    return result;
  }

  Matrix multiply_tile(Matrix a, Matrix b, size_t tile_size) {
    if (a.ncol != b.nrow) {
      throw std::invalid_argument(
          "Matrix dimensions do not allow multiplication.");
    }

    Matrix result(a.nrow, b.ncol);

    for (size_t i = 0; i < a.nrow; i += tile_size) {
      for (size_t j = 0; j < b.ncol; j += tile_size) {
        for (size_t k = 0; k < a.ncol; k += tile_size) {
          for (size_t ii = i; ii < std::min(i + tile_size, a.nrow); ++ii) {
            for (size_t jj = j; jj < std::min(j + tile_size, b.ncol); ++jj) {
              for (size_t kk = k; kk < std::min(k + tile_size, a.ncol); ++kk) {
                result(ii, jj) += a(ii, kk) * b(kk, jj);
              }
            }
          }
        }
      }
    }
    return result;
  }

  Matrix multiply_mkl(Matrix a, Matrix b) {}

  Matrix(size_t nrow, size_t ncol) : nrow(nrow), ncol(ncol) {
    data = new data_t[nrow * ncol];
  }

  data_t get_element(std::pair<size_t, size_t> idx) {
    return data[idx.first * ncol + idx.second];
  }

  data_t set_element(std::pair<size_t, size_t> idx, data_t val) {
    return data[idx.first * ncol + idx.second] = val;
  }

  data_t &operator()(size_t i, size_t j) { return data[i * ncol + j]; }

  data_t operator()(size_t i, size_t j) const { return data[i * ncol + j]; }

  size_t get_nrow() { return nrow; };

  size_t get_ncol() { return ncol; };

  size_t nrow, ncol;

private:
  data_t *data;
};

Matrix multiply_naive(Matrix a, Matrix b) {
  if (a.ncol != b.nrow) {
    throw std::invalid_argument(
        "Matrix dimensions do not allow multiplication.");
  }

  Matrix result(a.nrow, b.ncol);
  for (size_t i = 0; i < a.nrow; ++i) {
    for (size_t j = 0; j < b.ncol; ++j) {
      for (size_t k = 0; k < a.ncol; ++k) {
        result(i, j) += a(i, k) * b(k, j);
      }
    }
  }
  return result;
}

Matrix multiply_tile(Matrix a, Matrix b, size_t tile_size) {
  if (a.ncol != b.nrow) {
    throw std::invalid_argument(
        "Matrix dimensions do not allow multiplication.");
  }

  Matrix result(a.nrow, b.ncol);

  for (size_t i = 0; i < a.nrow; i += tile_size) {
    for (size_t j = 0; j < b.ncol; j += tile_size) {
      for (size_t k = 0; k < a.ncol; k += tile_size) {
        for (size_t ii = i; ii < std::min(i + tile_size, a.nrow); ++ii) {
          for (size_t jj = j; jj < std::min(j + tile_size, b.ncol); ++jj) {
            for (size_t kk = k; kk < std::min(k + tile_size, a.ncol); ++kk) {
              result(ii, jj) += a(ii, kk) * b(kk, jj);
            }
          }
        }
      }
    }
  }
  return result;
}

PYBIND11_MODULE(_matrix, m) {
  py::class_<Matrix>(m, "Matrix")
      .def(py::init<size_t, size_t>())
      .def("multiply_naive", &Matrix::multiply_naive)
      .def("multiply_tile", &Matrix::multiply_tile)
      .def("multiply_mkl", &Matrix::multiply_mkl)
      .def("__getitem__", &Matrix::get_element)
      .def("__setitem__", &Matrix::set_element)
      .def_property_readonly("nrow", &Matrix::get_ncol)
      .def_property_readonly("ncol", &Matrix::get_ncol);
  m.def("multiply_naive", &multiply_naive);
  m.def("multiply_tile", &multiply_tile);
}
