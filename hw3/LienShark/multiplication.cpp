//
//  main.cpp
//  numericial_test
//
//  Created by 許承晏 on 2024/10/20.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <limits>
#include <stdio.h>
#include <random>
#include <stddef.h>
#include <mkl/mkl.h>
#include <vector>
#include <utility>
#include <tuple>
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

using namespace std;

Matrix multiply_naive(Matrix & mat1, Matrix & mat2){
    //Matrix(mat1.nrow(), mat2.ncol());
    
    if(mat1.ncol() != mat2.nrow()){ throw std::out_of_range("matrix column differs from vector size");}
    
    Matrix mat3(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < mat1.nrow(); ++i) {
        for (size_t j = 0; j < mat2.ncol(); ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < mat1.ncol(); ++k) {
                    sum += mat1(i, k) * mat2(k, j);
                }
                mat3(i, j) = sum; // 將計算結果存入 C
            }
        }

    return mat3;
}
Matrix multiply_tile(Matrix & mat1, Matrix & mat2, size_t t_size) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("matrix column differs from vector size");
    }

    Matrix mat3(mat1.nrow(), mat2.ncol());
    size_t row1 = mat1.nrow();
    size_t col1 = mat1.ncol();
    size_t col2 = mat2.ncol();

    // 遍歷區塊
    for (size_t i = 0; i < row1; i += t_size) {
        for (size_t j = 0; j < col2; j += t_size) {
            for (size_t k = 0; k < col1; k += t_size) {
                
                // 處理非整除情況下剩餘的部分，計算當前區塊的大小
                size_t current_t_size_i = std::min(t_size, row1 - i);
                size_t current_t_size_j = std::min(t_size, col2 - j);
                size_t current_t_size_k = std::min(t_size, col1 - k);
                
                // 遍歷區塊內的元素
                for (size_t ii = 0; ii < current_t_size_i; ii++) {
                    for (size_t jj = 0; jj < current_t_size_j; jj++) {
                        double sum = 0;
                        for (size_t kk = 0; kk < current_t_size_k; kk++) {
                            // 進行矩陣乘法
                            sum += mat1(i + ii, k + kk) * mat2(k + kk, j + jj);
                        }
                        mat3(i + ii, j + jj) += sum;
                    }
                }
            }
        }
    }

    return mat3;
}

Matrix multiply_mkl(const Matrix& A, const Matrix& B) {
    if (A.ncol() != B.nrow()) {
        throw std::out_of_range("Matrix dimensions do not match for multiplication");
    }

    // 創建結果矩陣，行數是A的行數，列數是B的列數
    Matrix C(A.nrow(), B.ncol());

    // 使用 MKL 函數進行矩陣乘法
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                A.nrow(), B.ncol(), A.ncol(),
                1.0, A.data(), A.ncol(),  // A 的數據指針和列數
                B.data(), B.ncol(),       // B 的數據指針和列數
                0.0, C.data(), C.ncol()); // C 的數據指針和列數
    return C;
}
PYBIND11_MODULE(_matrix, m)
{
    m.def("multiply_mkl", &multiply_mkl, "use cblas", py::arg("mat1"), py::arg("mat2"));
    m.def("multiply_naive", &multiply_naive, "navie ", py::arg("mat1"), py::arg("mat2"));
    m.def("multiply_tile", &multiply_tile, "tile version", py::arg("mat1"), py::arg("mat2"), py::arg("tile_size"));

    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def_readonly("nrow", &Matrix::m_row)
        .def_readonly("ncol", &Matrix::m_col)
        .def(
            "__getitem__", [](Matrix &c, std::tuple<size_t, size_t> a)
            { return c(std::get<0>(a), std::get<1>(a)); },
            py::is_operator())
        .def(
            "__setitem__", [](Matrix &c, std::tuple<size_t, size_t> a, double value)
            { c(std::get<0>(a), std::get<1>(a)) = value; },
            py::is_operator())
        .def(
            "__eq__", [](Matrix &c, Matrix &a)
            { return c == a; },
            py::is_operator())
        .def(
            "__ne__", [](Matrix &c, Matrix &a)
            { return !(c == a); },
            py::is_operator());
}
