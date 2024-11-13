#pragma once

#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "allocator.hpp"

class matrix_2d {
public:
    matrix_2d() = delete;
    matrix_2d(size_t nrow, size_t ncol);
    matrix_2d(matrix_2d const &m) = default;
    matrix_2d(matrix_2d &&m) = default;
    matrix_2d &operator=(matrix_2d const &m) = default;
    matrix_2d &operator=(matrix_2d &&m) = default;
    ~matrix_2d() = default;

    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);
    bool operator==(matrix_2d const &m) const;

    matrix_2d & transpose();

    size_t index(size_t row, size_t col) const;
    bool is_transposed() const;

    size_t get_nrow() const;
    size_t get_ncol() const;
    const double* get_buffer() const;
    std::vector<double, CustomAllocator<double>> m_buffer;

private:
    size_t m_nrow;
    size_t m_ncol;
    bool m_transpose = false;
};
