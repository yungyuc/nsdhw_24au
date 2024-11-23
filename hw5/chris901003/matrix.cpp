#include "matrix.hpp"
#include <stdexcept>
#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>

using namespace std;

Matrix::Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol) {
    if (nrow <= 0 || ncol <= 0) {
        throw "Invalid matrix size";
    }
    data = new double[nrow * ncol];
    for (size_t i = 0; i < nrow * ncol; i++) {
        data[i] = 0;
    }
}

Matrix::Matrix(size_t nrow, size_t ncol, double init) : m_nrow(nrow), m_ncol(ncol) {
    if (nrow <= 0 || ncol <= 0) {
        throw "Invalid matrix size";
    }
    data = new double[nrow * ncol];
    for (size_t i = 0; i < nrow * ncol; i++) {
        data[i] = init;
    }
}

Matrix::Matrix(size_t nrow, size_t ncol, vector<double> &init) : m_nrow(nrow), m_ncol(ncol) {
    if (nrow <= 0 || ncol <= 0) {
        throw "Invalid matrix size";
    }
    data = new double[nrow * ncol];
    for (size_t i = 0; i < nrow * ncol; i++) {
        data[i] = init[i];
    }
}

Matrix::Matrix(const Matrix &m) : m_nrow(m.nrow()), m_ncol(m.ncol()) {
    data = new double[m_nrow * m_ncol];
    for (size_t i = 0; i < m_nrow * m_ncol; i++) {
        data[i] = m.data[i];
    }
}

Matrix::~Matrix() {
    delete[] data;
}

size_t Matrix::nrow() const {
    return m_nrow;
}

size_t Matrix::ncol() const {
    return m_ncol;
}

size_t Matrix::index(size_t i, size_t j) const {
    if (i >= m_nrow || j >= m_ncol || i < 0 || j < 0) {
        throw "Index out of range";
    }
    return i * m_ncol + j;
}

double* Matrix::getData() const {
    return data;
}

vector<double> Matrix::getVector() const {
    vector<double> v(data, data + m_nrow * m_ncol);
    return v;
}

double Matrix::operator()(size_t i, size_t j) const {
    if (i >= m_nrow || j >= m_ncol || i < 0 || j < 0) {
        throw "Index out of range";
    }
    return data[index(i, j)];
}

double& Matrix::operator()(size_t i, size_t j) {
    if (i >= m_nrow || j >= m_ncol || i < 0 || j < 0) {
        throw "Index out of range";
    }
    return data[index(i, j)];
}

bool Matrix::operator==(const Matrix &m) const {
    if (m_nrow != m.nrow() || m_ncol != m.ncol()) {
        return false;
    }
    for (size_t i = 0; i < m_nrow * m_ncol; i++) {
        if (data[i] != m.data[i]) {
            return false;
        }
    }
    return true;
}

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