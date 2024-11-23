#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <mkl.h>
#include "_matrix.hpp"
// based on https://yyc.solvcon.net/en/latest/nsd/04matrix/matrix.html
using namespace std;
Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2)
{
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

// matrix tiled
Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2,  size_t len_size)
{
    Matrix ret(mat1.nrow(), mat2.ncol());
    for (size_t i_start = 0; i_start < mat1.nrow(); i_start += len_size)
    {
        for (size_t k_start = 0; k_start < mat2.ncol(); k_start += len_size)
        {
            for (size_t j_start = 0; j_start < mat1.ncol(); j_start += len_size)
            {
                size_t i_end = min(i_start + len_size, mat1.nrow());
                size_t k_end = min(k_start + len_size, mat2.ncol());
                size_t j_end = min(j_start + len_size, mat1.ncol());

                for (size_t i = i_start; i < i_end; i++)
                {
                    for (size_t k = k_start; k < k_end; k++)
                    {
                        for (size_t j = j_start; j < j_end; j++)
                        {
                            ret(i, k) += mat1(i, j) * mat2(j, k);
                        }
                    }
                }
            }
        }    
    }
    return ret;
}


Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2)
{
    Matrix ret(mat1.nrow(), mat2.ncol());
    size_t m = mat1.nrow();
    size_t n = mat2.ncol();
    size_t k = mat1.ncol();
    double alpha = 1.0;
    double beta = 0.0;
    const double* A = mat1.data();
    const double* B = mat2.data();
    double* C = ret.data();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, k, alpha, A, k, B, n, beta, C, n);
    return ret;
}