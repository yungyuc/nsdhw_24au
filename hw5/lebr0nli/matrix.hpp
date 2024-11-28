#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

template <typename T> class Mallocator {
public:
    using value_type = T;
    static inline size_t bytes_allocated = 0;
    static inline size_t total_allocated = 0;
    static inline size_t total_deallocated = 0;

    Mallocator() noexcept {}
    template <typename U> Mallocator(const Mallocator<U> &) noexcept {}

    T *allocate(std::size_t n);

    void deallocate(T *p, std::size_t n) noexcept;
};

template <typename T, typename U> bool operator==(const Mallocator<T> &, const Mallocator<U> &) {
    return true;
}

template <typename T, typename U> bool operator!=(const Mallocator<T> &, const Mallocator<U> &) {
    return false;
}

struct Matrix {
    size_t rows;
    size_t cols;
    std::vector<double, Mallocator<double>> data;

    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    Matrix &operator=(const Matrix &other);
    Matrix &operator=(Matrix &&other) noexcept;
    ~Matrix() = default;

    inline double &operator()(size_t row, size_t col) { return data[row * cols + col]; }

    inline const double &operator()(size_t row, size_t col) const { return data[row * cols + col]; }

    bool operator==(const Matrix &other) const;

    size_t nrow() const { return rows; }
    size_t ncol() const { return cols; }
};

inline double &Matrix_at(Matrix &m, size_t i, size_t j) { return m.data[i * m.cols + j]; }

inline const double &Matrix_at(const Matrix &m, size_t i, size_t j) {
    return m.data[i * m.cols + j];
}

double Matrix_getitem(const Matrix &m, const std::pair<size_t, size_t> &indices);
void Matrix_setitem(Matrix &m, const std::pair<size_t, size_t> &indices, double value);

Matrix multiply_naive(const Matrix &a, const Matrix &b);
Matrix multiply_tile(const Matrix &a, const Matrix &b, size_t tile_size);
Matrix multiply_mkl(const Matrix &a, const Matrix &b);

#endif // _MATRIX_H_
