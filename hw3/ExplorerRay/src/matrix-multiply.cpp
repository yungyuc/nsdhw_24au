#include "matrix-multiply.hpp"
#include <mkl.h>
#include <stdexcept>

matrix_2d multiply_naive(matrix_2d const &A, matrix_2d const &B) {
    if (A.get_ncol() != B.get_nrow()) {
        throw std::out_of_range("Matrix dimensions do not match");
    }

    matrix_2d C(A.get_nrow(), B.get_ncol());
    for (uint i = 0; i < A.get_nrow(); ++i) {
        for (uint j = 0; j < B.get_ncol(); ++j) {
            double sum = 0;
            for (uint k = 0; k < A.get_ncol(); ++k) {
                sum += A(i, k) * B(k, j);
            }
            C(i, j) = sum;
            printf("%lf\n", C(i, j));
        }
    }
    return C;
}

matrix_2d multiply_tile(matrix_2d const &A, matrix_2d const &B, size_t tsize){
    if (A.get_ncol() != B.get_nrow()) {
        throw std::out_of_range("Matrix dimensions do not match");
    }

    matrix_2d C(A.get_nrow(), B.get_ncol());
    for (uint i = 0; i < A.get_nrow(); i += tsize) {
        for (uint j = 0; j < B.get_ncol(); j += tsize) {
            for (uint k = 0; k < A.get_ncol(); k += tsize) {
                for (uint ii = i; ii < std::min(i + tsize, A.get_nrow()); ++ii) {
                    for (uint jj = j; jj < std::min(j + tsize, B.get_ncol()); ++jj) {
                        double sum = 0;
                        for (uint kk = k; kk < std::min(k + tsize, A.get_ncol()); ++kk) {
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
