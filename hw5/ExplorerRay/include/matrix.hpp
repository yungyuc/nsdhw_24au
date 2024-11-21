#pragma once

#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "allocator.hpp"

class Matrix {
public:
    Matrix() = delete;
    Matrix(size_t nrow, size_t ncol);
    Matrix(Matrix const &m) = default;
    Matrix(Matrix &&m) = default;
    Matrix &operator=(Matrix const &m) = default;
    Matrix &operator=(Matrix &&m) = default;
    ~Matrix() = default;

    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);
    bool operator==(Matrix const &m) const;

    Matrix & transpose();

    size_t index(size_t row, size_t col) const;
    bool is_transposed() const;

    size_t get_nrow() const;
    size_t get_ncol() const;
    size_t nrow() const;
    size_t ncol() const;
    const double* get_buffer() const;
    std::vector<double, CustomAllocator<double>> m_buffer;

private:
    size_t m_nrow;
    size_t m_ncol;
    bool m_transpose = false;
};

#include "matrix-multiply.hpp"
