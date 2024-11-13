#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

struct Matrix {
    size_t rows;
    size_t cols;
    std::vector<double> data;

    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    Matrix &operator=(const Matrix &other);
    Matrix &operator=(Matrix &&other) noexcept;
    ~Matrix() = default;

    inline double &operator()(size_t row, size_t col);
    inline const double &operator()(size_t row, size_t col) const;
    bool operator==(const Matrix &other) const;

    size_t nrow() const { return rows; }
    size_t ncol() const { return cols; }
};

inline double &Matrix_at(Matrix &m, size_t i, size_t j) {
    return m.data[i * m.cols + j];
}

inline const double &Matrix_at(const Matrix &m, size_t i, size_t j) {
    return m.data[i * m.cols + j];
}

double Matrix_getitem(const Matrix &m,
                      const std::pair<size_t, size_t> &indices);
void Matrix_setitem(Matrix &m, const std::pair<size_t, size_t> &indices,
                    double value);

Matrix multiply_naive(const Matrix &a, const Matrix &b);
Matrix multiply_tile(const Matrix &a, const Matrix &b, size_t tile_size);
Matrix multiply_mkl(const Matrix &a, const Matrix &b);

#endif // _MATRIX_H_
