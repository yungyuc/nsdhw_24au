#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <sstream>

class Matrix {
private:
    double* data;
    size_t rows, cols;

public:
    // Constructor
    Matrix(size_t r, size_t c) : rows(r), cols(c) {
        data = new double[r * c]();  // Zero-initialize
    }

    // Copy constructor
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new double[rows * cols];
        std::copy(other.data, other.data + (rows * cols), data);
    }

    // Move constructor
    Matrix(Matrix&& other) noexcept : data(other.data), rows(other.rows), cols(other.cols) {
        other.data = nullptr;
        other.rows = other.cols = 0;
    }

    // Destructor
    ~Matrix() {
        delete[] data;
    }

    // Copy assignment operator
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            delete[] data;
            rows = other.rows;
            cols = other.cols;
            data = new double[rows * cols];
            std::copy(other.data, other.data + (rows * cols), data);
        }
        return *this;
    }

    // Move assignment operator
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            rows = other.rows;
            cols = other.cols;
            other.data = nullptr;
            other.rows = other.cols = 0;
        }
        return *this;
    }

    // Accessor methods matching mod.cpp expectations
    size_t nrow() const { return rows; }
    size_t ncol() const { return cols; }

    // Element access operator
    double& operator()(size_t i, size_t j) {
        if (i >= rows || j >= cols) throw std::out_of_range("Matrix index out of range");
        return data[i * cols + j];
    }

    const double& operator()(size_t i, size_t j) const {
        if (i >= rows || j >= cols) throw std::out_of_range("Matrix index out of range");
        return data[i * cols + j];
    }

    // Comparison operators
    bool operator==(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) return false;
        return std::memcmp(data, other.data, rows * cols * sizeof(double)) == 0;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    // For internal use by multiplication functions
    const double* get_data() const { return data; }
    double* get_data() { return data; }
};

// Explicit function declarations for multiplication functions
Matrix multiply_mkl(const Matrix& A, const Matrix& B);
Matrix multiply_naive(const Matrix& A, const Matrix& B);
Matrix multiply_tile(const Matrix& A, const Matrix& B, size_t tile_size = 32);
