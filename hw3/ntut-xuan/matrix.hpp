#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstddef>
#include <cstring>
#include <vector>

class Matrix {
public:
    size_t row, column;
    std::vector<double> matrix_data;

    Matrix(size_t r, size_t c) : row(r), column(c) { matrix_data = std::vector<double>(r * c, 0);  }

    void SetMatrixData(std::vector<double> data) {
        this->matrix_data = data;
    }

    void SetMatrixValue(int i, int j, double value){
        this->matrix_data[i*this->row+j] = value;
    }

    double   operator() (size_t row, size_t col) const
    {
        return matrix_data[row * col + col];
    }
    double & operator() (size_t row, size_t col)
    {
        return matrix_data[row * col + col];
    }

    Matrix(const Matrix &other) : row(other.row), column(other.column) {
        matrix_data = std::vector<double>(row * column);
        std::memcpy(matrix_data.data(), other.matrix_data.data(), row * column * sizeof(double));
    }

    Matrix(Matrix &&other) noexcept
        : matrix_data(std::move(other.matrix_data)), row(other.row), column(other.column) {
        other.row = other.column = 0;
    }
    
    Matrix &operator=(const Matrix &other) {
        if (this != &other) {
            row = other.row;
            column = other.column;
            matrix_data = std::vector<double>(row * column);
            std::memcpy(matrix_data.data(), other.matrix_data.data(),
                        row * column * sizeof(double));
        }
        return *this;
    }

    Matrix &operator=(Matrix &&other) noexcept {
        if (this != &other) {
            matrix_data = std::move(other.matrix_data);
            row = other.row;
            column = other.column;
            other.row = other.column = 0;
        }
        return *this;
    }

    bool operator==(const Matrix &other) const {
        if (row != other.GetRow() || column != other.GetColumn())
            return false;
        return std::memcmp((double*) matrix_data.data(), (double*) other.matrix_data.data(),
                        row * column * sizeof(double)) == 0;
    }

    size_t GetRow() const { return this->row; }
    size_t GetColumn() const { return this->column; }
};

inline const double& GetMatrixData(const Matrix &matrix, size_t row, size_t column);
inline double& GetMatrixData(Matrix &matrix, size_t row, size_t column);

double MatrixGetItem(const Matrix &m, const std::pair<size_t, size_t> &indices);
void MatrixSetItem(Matrix &m, const std::pair<size_t, size_t> &indices, double value);

Matrix multiply_naive(Matrix &a, Matrix &b);
Matrix multiply_mkl(Matrix &a, Matrix &b);
Matrix multiply_tile(Matrix &a, Matrix &b, size_t tile_size);

#endif