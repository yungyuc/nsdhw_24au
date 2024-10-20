#include "_matrix.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <mkl.h>

/* basic operations of matrix*/

// initialize Matrix value = 0
Matrix::Matrix(size_t nrow, size_t ncol)
    : m_nrow(nrow), m_ncol(ncol), data(nrow * ncol) {
    for (size_t i = 0; i < nrow * ncol; i++) {
        data[i] = 0;
    }
}  

// assign same value for each elements in matrix
Matrix::Matrix(size_t nrow, size_t ncol, double init)
    : m_nrow(nrow), m_ncol(ncol), data(nrow * ncol, init) {
    for (size_t i = 0; i < nrow * ncol; i++) {
        data[i] = init;
    }
    }  

// Copy Constructor (Deep Copy)
Matrix::Matrix(const Matrix &mat)
    : m_nrow(mat.m_nrow), m_ncol(mat.m_ncol), data(new double[mat.m_nrow * mat.m_ncol]) {
    std::copy(mat.data, mat.data + (mat.m_nrow * mat.m_ncol), data);  // Deep copy of the data
}

// Copy Assignment Operator (Deep Copy)
Matrix& Matrix::operator=(const Matrix &mat) {
    if (this == &mat)  // Prevent self-assignment
        return *this;

    delete[] data;  // Clean up existing data

    m_nrow = mat.m_nrow;
    m_ncol = mat.m_ncol;
    data = new double[m_nrow * m_ncol];  // Allocate new memory
    std::copy(mat.data, mat.data + (m_nrow * m_ncol), data);  // Deep copy of the data

    return *this;
}

// Desctructor
Matrix::~Matrix() {
    delete[] data;
}



/* get size*/

// return size of row and col
size_t nrow() const { return m_nrow; }
size_t ncol() const { return m_ncol; }

// return index of (i, j) element
size_t index(size_t i, size_t j) const {
    return i * m_ncol + j;
}

// return data of index (i, j)
double operator()(size_t i, size_t j) const {
    return data[index(i, j)];
}

double* Matrix::getData() const {
    return data;
}

//  Naive matrix matrix multiplication.
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2){
    if(mat1.ncol() != mat2.nrow()){
        throw std::invalid_argument("columns of first matrix does not match rows of second matrix");
    }
    Matrix result(mat1.nrow(), mat2.ncol());
    for(size_t i = 0; i < mat1.nrow(); i++){
        for(size_t j = 0; j < mat2.ncol(); j++){
            for(size_t k = 0; k < mat1.ncol(); k++){
                result(i, j) += mat1(i, k) * mat2(k, j); 
            }
        }
    }
    return result;
}

// reduces cache misses by working on small blocks of the matrix at a time
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t blockSize = 16){
    if(mat1.ncol() != mat2.nrow()){
        throw std::invalid_argument("columns of first matrix does not match rows of second matrix");
    }

    Matrix result(mat1.nrow(), mat2.ncol());
    size_t n = mat1.nrow();
    size_t m = mat1.ncol();  // or mat2.nrow()
    size_t p = mat2.ncol();

    for (size_t i = 0; i < n; i += blockSize) {
        for (size_t j = 0; j < p; j += blockSize) {
            for (size_t k = 0; k < m; k += blockSize) {
                // Multiply sub-blocks of the matrices
                for (size_t ii = i; ii < std::min(i + blockSize, n); ++ii) {
                    for (size_t jj = j; jj < std::min(j + blockSize, p); ++jj) {
                        for (size_t kk = k; kk < std::min(k + blockSize, m); ++kk) {
                            result(ii, jj) += mat1(ii, kk) * mat2(kk, jj);
                        }
                    }
                }
            }
        }
    }

    return result;
}

Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2){
    if(mat1.ncol() != mat2.nrow()){
        throw std::invalid_argument("columns of first matrix does not match rows of second matrix");
    }

    Matrix result(mat1.nrow(), mat2.ncol());

    // Parameters for cblas_dgemm
    const CBLAS_LAYOUT layout = CblasRowMajor;  // row-major order
    const CBLAS_TRANSPOSE transA = CblasNoTrans;  // no transpose for A
    const CBLAS_TRANSPOSE transB = CblasNoTrans;  // no transpose for B
    const double alpha = 1.0;  // scaling factor for A * B
    const double beta = 0.0;   // scaling factor for C (result initialized as 0)

    // Call to MKL's cblas_dgemm function for matrix multiplication
    cblas_dgemm(layout, transA, transB, 
                mat1.nrow(), mat2.ncol(), mat1.ncol(), alpha, 
                mat1.getData(), mat1.ncol(), // matrix A
                mat2.getData(), mat2.ncol(), // matrix B
                beta, 
                result.getData(), result.ncol()); // matrix C

    return result;
}

// Binding Matrix class to Python
PYBIND11_MODULE(_matrix, mat){
    mat.def("multiply_naive", &multiply_naive, "use naive");
    mat.def("multiply_mkl", &multiply_mkl, "use mkl");
    mat.def("multiply_tile", &multiply_tile, "use tile");
    // Expose the Matrix class
    pybind11::class_<Matrix>(mat, "Matrix")
        // Expose the constructor Matrix(size_t nrow, size_t ncol)
        .def(pybind11::init<size_t, size_t>(), "Constructor with rows and columns")
        // Expose the constructor Matrix(size_t nrow, size_t ncol, double init)
        .def(pybind11::init<size_t, size_t, double>(), "Constructor with rows, columns, and initial value");
}