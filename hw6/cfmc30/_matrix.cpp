#include <algorithm>
#include <vector>
#include <cstddef>
#include <memory>
#include <limits>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <utility>

#include <mkl/mkl.h>

using data_t = double;

namespace py = pybind11;

template <typename T> class MyAllocator {
public:
    typedef T value_type;
    static inline size_t allo_cnt = 0, bytes_cnt = 0, dallo_cnt = 0;
  
    MyAllocator() noexcept {}

    T* allocate(std::size_t n)
    {
      allo_cnt += n * sizeof(value_type);
      bytes_cnt += n * sizeof(value_type);
      // printf("a: %lu %lu %lu\n", allo_cnt, bytes_cnt, n);
        return static_cast<T*>(
            ::operator new(n * sizeof(value_type)));
    }

    void deallocate(T* p, std::size_t n) noexcept
    {
      dallo_cnt += n * sizeof(value_type);
      bytes_cnt -= n * sizeof(value_type);
      // printf("d: %lu %lu %lu\n", dallo_cnt, bytes_cnt, n);
        ::operator delete(p);
    }
  
    static size_t bytes() {
      return bytes_cnt;
    }

    static size_t allocated() {
      return allo_cnt;
    }

    static size_t deallocated() {
      return dallo_cnt;
    }
};

class Matrix {
public:
  Matrix multiply_naive(const Matrix &a, const Matrix &b) {
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

  Matrix multiply_tile(const Matrix &a, const Matrix &b, size_t tile_size) {
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

  Matrix multiply_mkl(const Matrix &a, const Matrix &b) {
    if (a.ncol != b.nrow) {
      throw std::invalid_argument(
          "Matrix dimensions do not allow multiplication.");
    }

    Matrix result(a.nrow, b.ncol);

    // Using cblas_sgemm for single-precision floating-point matrix
    // multiplication
    const float alpha = 1.0f;
    const float beta = 0.0f;

    // Perform the multiplication: result = alpha * (a * b) + beta * result
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a.nrow, b.ncol,
                a.ncol, alpha, a.data.data(), a.ncol,   // Matrix A
                b.data.data(), b.ncol,                  // Matrix B
                beta, result.data.data(), result.ncol); // Result matrix

    return result;
  }

  Matrix(size_t nrow, size_t ncol) : nrow(nrow), ncol(ncol) {
    this->data = std::vector<double, MyAllocator<double>>(nrow * ncol);
  }

  data_t get_element(std::pair<size_t, size_t> idx) {
    return data[idx.first * ncol + idx.second];
  }

  data_t set_element(std::pair<size_t, size_t> idx, data_t val) {
    return data[idx.first * ncol + idx.second] = val;
  }

  data_t &operator()(size_t i, size_t j) { return data[i * ncol + j]; }

  data_t operator()(size_t i, size_t j) const { return data[i * ncol + j]; }

  bool equal(Matrix const &m) const {
    if (this->nrow != m.nrow || this->ncol != m.ncol) {
      return false;
    }

    for (size_t i = 0; i < this->nrow; ++i) {
      for (size_t j = 0; j < this->ncol; ++j) {
        if ((*this)(i, j) != m(i, j)) {
          return false;
        }
      }
    }

    return true;
  }

  size_t get_nrow() { return nrow; };

  size_t get_ncol() { return ncol; };

  py::array_t<double> array() {
    return py::array_t<double> ({this->nrow, this->ncol}, this->data.data(), py::cast(*this));
  }
  
  size_t nrow, ncol;

  std::vector<double, MyAllocator<double>> data;
};

Matrix multiply_naive(const Matrix &a, const Matrix &b) {
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

Matrix multiply_tile(const Matrix &a, const Matrix &b, size_t tile_size) {
  if (a.ncol != b.nrow) {
    throw std::invalid_argument(
        "Matrix dimensions do not allow multiplication.");
  }

  Matrix result(a.nrow, b.ncol);

  for (size_t i = 0; i < a.nrow; i += tile_size) {
    for (size_t j = 0; j < b.ncol; j += tile_size) {
      for (size_t k = 0; k < a.ncol; k += tile_size) {
	size_t ii_lim = std::min(i + tile_size, a.nrow);
	size_t jj_lim = std::min(j + tile_size, b.ncol);
	size_t kk_lim = std::min(k + tile_size, a.ncol);
	for (size_t ii = i; ii < ii_lim; ++ii) {
          for (size_t kk = k; kk < kk_lim; ++kk) {
	    data_t a_ii_kk = a(ii, kk);
	    for (size_t jj = j; jj < jj_lim; ++jj) {
              result(ii, jj) += a_ii_kk * b(kk, jj);
            }
          }
        }
      }
    }
  }
  return result;
}

Matrix multiply_mkl(const Matrix &a, const Matrix &b) {
  if (a.ncol != b.nrow) {
    throw std::invalid_argument(
        "Matrix dimensions do not allow multiplication.");
  }

  Matrix result(a.nrow, b.ncol);

  const float alpha = 1.0f;
  const float beta = 0.0f;

  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a.nrow, b.ncol, a.ncol,
              alpha, a.data.data(), a.ncol, b.data.data(), b.ncol, beta, result.data.data(),
              result.ncol);

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
      .def("__eq__", &Matrix::equal)
      .def_property_readonly("nrow", &Matrix::get_ncol)
      .def_property_readonly("ncol", &Matrix::get_ncol)
    .def_property("array", &Matrix::array, nullptr);
  m.def("multiply_naive", &multiply_naive);
  m.def("multiply_tile", &multiply_tile);
  m.def("multiply_mkl", &multiply_mkl);
  m.def("bytes", &MyAllocator<double>::bytes);
  m.def("allocated", &MyAllocator<double>::allocated);
  m.def("deallocated", &MyAllocator<double>::deallocated);
}
