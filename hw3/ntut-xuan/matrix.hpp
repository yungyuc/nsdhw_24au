#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>

class Matrix {
public:
    size_t row, column;
    std::vector<double> matrix_data;

    Matrix(size_t r, size_t c) : row(r), column(c) { matrix_data = std::vector<double>(r * c);  }

    void SetMatrixData(std::vector<double> data) {
        this->matrix_data = data;
    }

    double& GetMatrixData(int row, int column){
        return matrix_data[row * column + column];
    }

    void SetMatrixValue(int i, int j, double value){
        this->matrix_data[i*this->row+j] = value;
    }

    size_t GetRow() const { return this->row; }
    size_t GetColumn() const { return this->column; }
};

inline double& GetMatrixData(Matrix &matrix, int row, int column);

Matrix multiply_naive(Matrix a, Matrix b);
Matrix multiply_mkl(Matrix a, Matrix b);
Matrix multiply_tile(Matrix a, Matrix b, size_t tile_size);

#endif