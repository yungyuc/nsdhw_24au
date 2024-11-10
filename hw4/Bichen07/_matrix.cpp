#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <mkl.h>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include "custom_allocator.h"
#include <vector>
#include <limits>  // Include this to fix std::numeric_limits error


/* basic operations of matrix*/

class Matrix {
public:
    Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol), data(nrow * ncol) {}

    double& operator()(size_t row, size_t col) { return data[row * m_ncol + col]; }
    const double& operator()(size_t row, size_t col) const { return data[row * m_ncol + col]; }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

    // Tracking functions
    static size_t bytes() { return CustomAllocator<double>::bytes(); }
    static size_t allocated() { return CustomAllocator<double>::allocated(); }
    static size_t deallocated() { return CustomAllocator<double>::deallocated(); }

private:
    size_t m_nrow, m_ncol;
    std::vector<double, CustomAllocator<double>> data;  // Use the custom allocator
};

// Initialize Matrix with value = 0
Matrix::Matrix(size_t nrow, size_t ncol): m_nrow(nrow), m_ncol(ncol){
    data = new double[nrow * ncol]; 
    for (size_t i = 0; i < nrow * ncol; i++) {
        data[i] = 0;
    }  
}

// assign same value for each elements in matrix
Matrix::Matrix(size_t nrow, size_t ncol, double init): m_nrow(nrow), m_ncol(ncol){
    data = new double[nrow * ncol]; 
    for (size_t i = 0; i < nrow * ncol; i++) {
        data[i] = init;
    }  
}


// Copy Constructor (Deep Copy)
Matrix::Matrix(const Matrix &mat): m_nrow(mat.m_nrow), m_ncol(mat.m_ncol){
    data = new double[m_nrow * m_ncol]; 
    for (size_t i = 0; i < m_nrow * m_ncol; i++) {
        data[i] = mat.data[i];
    } 
} 

// Copy Assignment Operator (Deep Copy)
Matrix& Matrix::operator=(const Matrix &mat) {
    // Step 1: Self-assignment check
    if (this == &mat) {
        return *this; // Return *this to allow chained assignment (e.g., a = b = c)
    }

    // Step 2: Delete old data
    delete[] data;

    // Step 3: Copy the dimensions and allocate new memory
    m_nrow = mat.m_nrow;
    m_ncol = mat.m_ncol;
    data = new double[m_nrow * m_ncol];

    // Step 4: Copy the elements
    for (size_t i = 0; i < m_nrow * m_ncol; i++) {
        data[i] = mat.data[i];
    }

    // Step 5: Return *this to allow chained assignments
    return *this;
}

// Desctructor
Matrix::~Matrix() {
    delete[] data;
}

/* get size*/
// return size of row and col
size_t Matrix::nrow() const { return m_nrow; }
size_t Matrix::ncol() const { return m_ncol; }

// return index of (i, j) element
size_t Matrix::index(size_t i, size_t j) const {
    return i * m_ncol + j;
}

double *Matrix::getData() const {
    return data;
}

/* Overload operator to access and compare elements */
double &Matrix::operator()(size_t row, size_t col) {
    return data[index(row, col)];
}

const double &Matrix::operator()(size_t row, size_t col) const {
    return data[index(row, col)];
}

bool Matrix::operator==(const Matrix &other) const {
    // Check if the dimensions are the same
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
        return false;
    }
    // Compare each element
    for (size_t i = 0; i < m_nrow * m_ncol; i++) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
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
                        double sum = 0.0;
                        for (size_t kk = k; kk < std::min(k + blockSize, m); ++kk) {
                            sum += mat1(ii, kk) * mat2(kk, jj);
                        }
                        result(ii, jj) += sum;
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
namespace py = pybind11;

PYBIND11_MODULE(matrix_allocator, m) {
    m.def("bytes", &CustomAllocator<double>::bytes, "Return the number of bytes currently used");
    m.def("allocated", &CustomAllocator<double>::allocated, "Return the total number of bytes allocated");
    m.def("deallocated", &CustomAllocator<double>::deallocated, "Return the total number of bytes deallocated");

    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__getitem__", [](const Matrix &self, std::pair<size_t, size_t> index) {
            return self(index.first, index.second);
        })
        .def("__setitem__", [](Matrix &self, std::pair<size_t, size_t> index, double value) {
            self(index.first, index.second) = value;
        });
}