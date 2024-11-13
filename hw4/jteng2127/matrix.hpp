#pragma once

#include<cstddef>
#include<vector>
#include "allocator.hpp"

class Matrix {
 private:
  size_t m_nrow, m_ncol;
  std::vector<double, CustomAllocator<double>> data;

 public:
  Matrix(size_t nrow, size_t ncol);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  size_t nrow() const;
  size_t ncol() const;
  double* getData() const;

  Matrix& operator=(const Matrix& other);

  double& operator()(size_t i, size_t j);
  const double& operator()(size_t i, size_t j) const;
  bool operator==(const Matrix &m) const;
};

Matrix multiply_naive(const Matrix& A, const Matrix& B);
Matrix multiply_tile(const Matrix& A, const Matrix& B, size_t tile_size);
Matrix multiply_mkl(const Matrix& A, const Matrix& B);

std::size_t bytes();
std::size_t allocated();
std::size_t deallocated();