#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <mkl.h>
#include <pybind11/numpy.h>

struct Matrix {

public:

    Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol) {
        m_buffer = new double[nrow * ncol];
    }
    Matrix(Matrix && other) : m_nrow(other.m_nrow), m_ncol(other.m_ncol) {
        if (m_buffer) delete[] m_buffer;
        m_buffer = nullptr;
        m_nrow = 0;
        m_ncol = 0;
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
    }
    ~Matrix() {
        if (m_buffer) { delete[] m_buffer; }
    }

    double   operator() (size_t row, size_t col) const {
        return m_buffer[index(row, col)];
    }
    double& operator() (size_t row, size_t col) {
        return m_buffer[index(row, col)];
    }
    Matrix& operator=(Matrix && other) {
        if (this == &other) { return *this; }
        if (m_buffer) delete[] m_buffer;
        m_buffer = nullptr;
        m_nrow = 0;
        m_ncol = 0;
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
        return *this;
    }
    bool operator==(const Matrix &m) const {
        if (m_nrow != m.nrow() || m_ncol != m.ncol()) {
            return false;
        }
        for (size_t i = 0; i < m_nrow * m_ncol; i++) {
            if (m_buffer[i] != m.m_buffer[i]) {
                return false;
            }
        }
        return true;
    }
    pybind11::array_t<double> to_numpy() const{
        return pybind11::array_t<double>(
            {m_nrow, m_ncol},            
            {m_ncol * sizeof(double),
            sizeof(double)},
            m_buffer,
            pybind11::capsule(m_buffer, [](void *f) {})
        );
    }
    size_t index(size_t row, size_t col) const {
        if (row >= m_nrow || col >= m_ncol)
            throw std::out_of_range("index out of range");
        return row * m_ncol + col;
    }

    double* buffer() const { return m_buffer; }
    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    size_t size() const { return m_nrow * m_ncol; }

private:
    double* m_buffer = nullptr;
    size_t m_nrow = 0;
    size_t m_ncol = 0;
};

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2);
Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, size_t tsize);
Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2);