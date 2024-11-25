#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <mkl.h>

struct Matrix {

public:

    Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol) {
        m_buffer = new double[nrow * ncol];
        for (size_t i = 0; i < nrow * ncol; i++) {
            m_buffer[i] = 0;
        }
    }
    Matrix(size_t nrow, size_t ncol, std::vector<double> & vec) : m_nrow(nrow), m_ncol(ncol) {
        m_buffer = new double[nrow * ncol];
        for (size_t i = 0; i < nrow * ncol; i++) {
            m_buffer[i] = vec[i];
        }
    }
    Matrix(const Matrix &m) : m_nrow(m.nrow()), m_ncol(m.ncol()) {
        m_buffer = new double[m_nrow * m_ncol];
        for (size_t i = 0; i < m_nrow * m_ncol; i++) {
            m_buffer[i] = m.m_buffer[i];
        }
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
    size_t index(size_t row, size_t col) const {
        if (row >= m_nrow || col >= m_ncol)
            throw std::out_of_range("index out of range");
        return row * m_ncol + col;
    }

    std::vector<double> buffer_vector() const { return std::vector<double>(m_buffer, m_buffer+size()); }
    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    size_t size() const { return m_nrow * m_ncol; }

    double * m_buffer = nullptr;

private:
    size_t m_nrow = 0;
    size_t m_ncol = 0;
};

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2);
Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, size_t tsize);
Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2);