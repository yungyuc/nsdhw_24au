#include <algorithm>
#include <cstring>
#include <mkl.h>
#include <stdexcept>
#include <utility>

#include "_matrix.h"

Matrix::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    data_ = std::make_unique<double[]>(rows * cols);
}

Matrix::Matrix(const Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
    data_ = std::make_unique<double[]>(rows_ * cols_);
    std::memcpy(data_.get(), other.data_.get(), rows_ * cols_ * sizeof(double));
}

Matrix::Matrix(Matrix &&other) noexcept
    : data_(std::move(other.data_)), rows_(other.rows_), cols_(other.cols_) {
    other.rows_ = other.cols_ = 0;
}

Matrix &Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = std::make_unique<double[]>(rows_ * cols_);
        std::memcpy(data_.get(), other.data_.get(),
                    rows_ * cols_ * sizeof(double));
    }
    return *this;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        rows_ = other.rows_;
        cols_ = other.cols_;
        other.rows_ = other.cols_ = 0;
    }
    return *this;
}

double &Matrix::operator()(size_t row, size_t col) {
    return Matrix_at(*this, row, col);
}

const double &Matrix::operator()(size_t row, size_t col) const {
    return Matrix_at(*this, row, col);
}

bool Matrix::operator==(const Matrix &other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_)
        return false;
    return std::memcmp(data_.get(), other.data_.get(),
                       rows_ * cols_ * sizeof(double)) == 0;
}

double Matrix_getitem(const Matrix &m,
                      const std::pair<size_t, size_t> &indices) {
    size_t row = indices.first;
    size_t col = indices.second;
    if (row >= m.rows_ || col >= m.cols_) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return Matrix_at(m, row, col);
}

void Matrix_setitem(Matrix &m, const std::pair<size_t, size_t> &indices,
                    double value) {
    size_t row = indices.first;
    size_t col = indices.second;
    if (row >= m.rows_ || col >= m.cols_) {
        throw std::out_of_range("Matrix indices out of range");
    }
    Matrix_at(m, row, col) = value;
}

Matrix multiply_naive(const Matrix &a, const Matrix &b) {
    if (a.cols_ != b.rows_) {
        throw std::invalid_argument(
            "Matrix dimensions do not match for multiplication");
    }

    Matrix result(a.rows_, b.cols_);
    for (size_t i = 0; i < a.rows_; ++i) {
        for (size_t j = 0; j < b.cols_; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < a.cols_; ++k) {
                sum += Matrix_at(a, i, k) * Matrix_at(b, k, j);
            }
            Matrix_at(result, i, j) = sum;
        }
    }
    return result;
}

Matrix multiply_tile(const Matrix &a, const Matrix &b, size_t tile_size) {
    if (a.cols_ != b.rows_) {
        throw std::invalid_argument(
            "Matrix dimensions do not match for multiplication");
    }

    Matrix result(a.rows_, b.cols_);

    std::fill(result.data_.get(),
              result.data_.get() + result.rows_ * result.cols_, 0.0);

    for (size_t i = 0; i < a.rows_; i += tile_size) {
        for (size_t k = 0; k < a.cols_; k += tile_size) {
            for (size_t j = 0; j < b.cols_; j += tile_size) {
                size_t i_end = std::min(a.rows_, i + tile_size);
                size_t k_end = std::min(a.cols_, k + tile_size);
                size_t j_end = std::min(b.cols_, j + tile_size);

                for (size_t ii = i; ii < i_end; ++ii) {
                    for (size_t kk = k; kk < k_end; ++kk) {
                        double r = Matrix_at(a, ii, kk);
                        for (size_t jj = j; jj < j_end; ++jj) {
                            Matrix_at(result, ii, jj) +=
                                r * Matrix_at(b, kk, jj);
                        }
                    }
                }
            }
        }
    }
    return result;
}

Matrix multiply_mkl(const Matrix &a, const Matrix &b) {
    if (a.cols_ != b.rows_) {
        throw std::invalid_argument(
            "Matrix dimensions do not match for multiplication");
    }

    Matrix result(a.rows_, b.cols_);
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a.rows_, b.cols_,
                a.cols_, 1.0, a.data_.get(), a.cols_, b.data_.get(), b.cols_,
                0.0, result.data_.get(), result.cols_);
    return result;
}
