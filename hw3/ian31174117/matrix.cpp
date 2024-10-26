#include "matrix.hpp"
#include <mkl.h>

Matrix::Matrix(size_t _row, size_t _col){
    this->nrow = _row;
    this->ncol = _col;
    this->buffer = new double[_row * _col];
    std::fill(this->buffer, this->buffer + _row * _col, 0.0);
}

Matrix::~Matrix(){
    delete[] this->buffer;
}

Matrix multiply_naive(const Matrix &A, const Matrix &B){
    if(A.get_col() != B.get_row()){
        throw std::invalid_argument("col of A does not match row of B");
    }
    Matrix result(A.get_row(), B.get_col());
    //init result
    for(size_t i = 0; i < A.get_row(); ++i){
        for(size_t j = 0; j < B.get_col(); ++j){
            double sum = 0;
            for(size_t k = 0; k < A.get_col(); ++k){
                sum += A(i, k) * B(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
};

Matrix multiply_mkl(const Matrix &A, const Matrix &B){
    if(A.get_col() != B.get_row()){
        throw std::invalid_argument("col of A does not match row of B");
    }
    Matrix result(A.get_row(), B.get_col());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                A.get_row(), B.get_col(), A.get_col(), 1.0, 
                A.buffer_ref(), A.get_col(),
                B.buffer_ref(), B.get_col(),
                0.0,
                result.buffer_ref(), result.get_col());
    return result;
};

Matrix multiply_tile(const Matrix &A, const Matrix &B, size_t tile_size) {
    if (A.get_col() != B.get_row()) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }
    
    Matrix result(A.get_row(), B.get_col());

    size_t n = A.get_row();
    size_t m = A.get_col();
    size_t p = B.get_col();

    for (size_t i = 0; i < n; i += tile_size) {
        for (size_t j = 0; j < p; j += tile_size) {
            for (size_t k = 0; k < m; k += tile_size) {
                size_t i_end = std::min(i + tile_size, n);
                size_t j_end = std::min(j + tile_size, p);
                size_t k_end = std::min(k + tile_size, m);

                for (size_t ii = i; ii < i_end; ++ii) {
                    for (size_t jj = j; jj < j_end; ++jj) {
                        double sum = result(ii, jj);
                        for (size_t kk = k; kk < k_end; ++kk) {
                            sum += A(ii, kk) * B(kk, jj);
                        }
                        result(ii, jj) = sum;
                    }
                }
            }
        }
    }

    return result;
}


PYBIND11_MODULE(_matrix, m){
    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def_property("nrow", &Matrix::get_row, nullptr)
        .def_property("ncol", &Matrix::get_col, nullptr)
        .def("__getitem__", [](Matrix &self, std::pair<size_t, size_t> i) {
            return self(i.first, i.second);
        })
        .def("__setitem__", [](Matrix &self, std::pair<size_t, size_t> i, double val) {
            self(i.first, i.second) = val;
        })
        .def("__eq__", &Matrix::operator==);
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_mkl", &multiply_mkl);
    m.def("multiply_tile", &multiply_tile);
}