#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

struct Matrix {
    std::unique_ptr<double[]> data_;
    size_t rows_;
    size_t cols_;

    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    Matrix &operator=(const Matrix &other);
    Matrix &operator=(Matrix &&other) noexcept;
    ~Matrix() = default;

    double &operator()(size_t row, size_t col);
    const double &operator()(size_t row, size_t col) const;
    bool operator==(const Matrix &other) const;

    size_t nrow() const { return rows_; }
    size_t ncol() const { return cols_; }
};

inline double &Matrix_at(Matrix &m, size_t i, size_t j) {
    return m.data_[i * m.cols_ + j];
}

inline const double &Matrix_at(const Matrix &m, size_t i, size_t j) {
    return m.data_[i * m.cols_ + j];
}

double Matrix_getitem(const Matrix &m,
                      const std::pair<size_t, size_t> &indices);
void Matrix_setitem(Matrix &m, const std::pair<size_t, size_t> &indices,
                    double value);

Matrix multiply_naive(const Matrix &a, const Matrix &b);
Matrix multiply_tile(const Matrix &a, const Matrix &b, size_t tile_size);
Matrix multiply_mkl(const Matrix &a, const Matrix &b);

#endif // _MATRIX_H_
