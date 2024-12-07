#include <algorithm>
#include <cstring>
#include <mkl.h>
#include <stdexcept>
#include <utility>

#include "matrix.hpp"

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data = std::make_unique<double[]>(rows * cols);
}

Matrix::Matrix(const Matrix &other) : rows(other.rows), cols(other.cols) {
    data = std::make_unique<double[]>(rows * cols);
    std::memcpy(data.get(), other.data.get(), rows * cols * sizeof(double));
}

Matrix::Matrix(Matrix &&other) noexcept
    : data(std::move(other.data)), rows(other.rows), cols(other.cols) {
    other.rows = other.cols = 0;
}

Matrix &Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = std::make_unique<double[]>(rows * cols);
        std::memcpy(data.get(), other.data.get(), rows * cols * sizeof(double));
    }
    return *this;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
        rows = other.rows;
        cols = other.cols;
        other.rows = other.cols = 0;
    }
    return *this;
}

double &Matrix::operator()(size_t row, size_t col) { return Matrix_at(*this, row, col); }

const double &Matrix::operator()(size_t row, size_t col) const {
    return Matrix_at(*this, row, col);
}

bool Matrix::operator==(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols)
        return false;
    return std::memcmp(data.get(), other.data.get(), rows * cols * sizeof(double)) == 0;
}

double Matrix_getitem(const Matrix &m, const std::pair<size_t, size_t> &indices) {
    size_t row = indices.first;
    size_t col = indices.second;
    if (row >= m.rows || col >= m.cols) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return Matrix_at(m, row, col);
}

void Matrix_setitem(Matrix &m, const std::pair<size_t, size_t> &indices, double value) {
    size_t row = indices.first;
    size_t col = indices.second;
    if (row >= m.rows || col >= m.cols) {
        throw std::out_of_range("Matrix indices out of range");
    }
    Matrix_at(m, row, col) = value;
}

Matrix multiply_naive(const Matrix &a, const Matrix &b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    Matrix result(a.rows, b.cols);
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < b.cols; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < a.cols; ++k) {
                sum += Matrix_at(a, i, k) * Matrix_at(b, k, j);
            }
            Matrix_at(result, i, j) = sum;
        }
    }
    return result;
}

Matrix multiply_tile(const Matrix &a, const Matrix &b, size_t tile_size) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    Matrix result(a.rows, b.cols);

    std::fill(result.data.get(), result.data.get() + result.rows * result.cols, 0.0);

    for (size_t i = 0; i < a.rows; i += tile_size) {
        for (size_t k = 0; k < a.cols; k += tile_size) {
            for (size_t j = 0; j < b.cols; j += tile_size) {
                size_t i_end = std::min(a.rows, i + tile_size);
                size_t k_end = std::min(a.cols, k + tile_size);
                size_t j_end = std::min(b.cols, j + tile_size);

                for (size_t ii = i; ii < i_end; ++ii) {
                    for (size_t kk = k; kk < k_end; ++kk) {
                        double r = Matrix_at(a, ii, kk);
                        for (size_t jj = j; jj < j_end; ++jj) {
                            Matrix_at(result, ii, jj) += r * Matrix_at(b, kk, jj);
                        }
                    }
                }
            }
        }
    }
    return result;
}

Matrix multiply_mkl(const Matrix &a, const Matrix &b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    Matrix result(a.rows, b.cols);
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a.rows, b.cols, a.cols, 1.0,
                a.data.get(), a.cols, b.data.get(), b.cols, 0.0, result.data.get(), result.cols);
    return result;
}
