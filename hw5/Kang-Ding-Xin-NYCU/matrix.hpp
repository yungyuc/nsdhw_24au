#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <mkl.h>
#include <vector>

class Matrix {

public:

    Matrix(size_t nrow, size_t ncol);

    Matrix(Matrix const & other);

    double   operator() (size_t row, size_t col) const;

    double & operator() (size_t row, size_t col);

    bool operator==(Matrix const & other) const;
    double* buf_get() const;

    void buf_set(std::vector<double> &data);

    size_t nrow() const;
    size_t ncol() const;
    size_t size() const;

    void printm();
    

private:

    size_t index(size_t row, size_t col) const;

    void reset_buffer(size_t nrow, size_t ncol);

    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double * m_buffer = nullptr;
};

Matrix multiply_naive(Matrix const & m1, Matrix const & m2);
Matrix multiply_tile(Matrix const & m1, Matrix const & m2, size_t t);
Matrix multiply_mkl(Matrix const & m1, Matrix const & m2);

#endif