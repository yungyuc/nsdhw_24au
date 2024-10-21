#include "matrix-multiply.hpp"
#include <stdexcept>

#ifdef UBUNTU
#include <mkl/mkl.h>
#else
#include <mkl.h>
#endif

matrix_2d multiply_naive(matrix_2d const &A, matrix_2d const &B) {
    if (A.get_ncol() != B.get_nrow()) {
        throw std::out_of_range("Matrix dimensions do not match");
    }

    auto row_iter = A.get_nrow();
    auto col_iter = B.get_ncol();
    auto inner_iter = A.get_ncol();
    matrix_2d C(row_iter, col_iter);
    for (size_t i = 0; i < row_iter; ++i) {
        for (size_t j = 0; j < col_iter; ++j) {
            double sum = 0;
            for (size_t k = 0; k < inner_iter; ++k) {
                sum += A(i, k) * B(k, j);
            }
            C(i, j) = sum;
        }
    }
    return C;
}

matrix_2d multiply_tile(matrix_2d const &A, matrix_2d const &B, size_t tsize){
    if (A.get_ncol() != B.get_nrow()) {
        throw std::out_of_range("Matrix dimensions do not match");
    }

    const size_t row_iter = A.get_nrow();
    const size_t col_iter = B.get_ncol();
    const size_t inner_iter = A.get_ncol();

    matrix_2d C(row_iter, col_iter);
    for (size_t i = 0; i < row_iter; i += tsize) {
        for (size_t j = 0; j < col_iter; j += tsize) {
            for (size_t k = 0; k < inner_iter; k += tsize) {
                const size_t ii_iter = std::min(i + tsize, row_iter);
                const size_t jj_iter = std::min(j + tsize, col_iter);
                const size_t kk_iter = std::min(k + tsize, inner_iter);

                for (size_t ii = i; ii < ii_iter; ++ii) {
                    for (size_t jj = j; jj < jj_iter; ++jj) {
                        double sum = 0;
                        for (size_t kk = k; kk < kk_iter; ++kk) {
                            sum += A(ii, kk) * B(kk, jj);
                        }
                        C(ii, jj) += sum;
                    }
                }
            }
        }
    }
    return C;
}

matrix_2d multiply_mkl(matrix_2d const &A, matrix_2d const &B){
    if (A.get_ncol() != B.get_nrow()) {
        throw std::out_of_range("Matrix dimensions do not match");
    }

    matrix_2d C(A.get_nrow(), B.get_ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                A.get_nrow(), B.get_ncol(), A.get_ncol(), 
                1.0, A.get_buffer(), A.get_ncol(), 
                B.get_buffer(), B.get_ncol(), 
                0.0, C.get_buffer(), C.get_ncol());
    return C;
}
