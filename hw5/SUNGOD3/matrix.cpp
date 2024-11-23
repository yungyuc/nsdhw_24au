#include "matrix.hpp"
#include <mkl.h>
#include <stdexcept>
#include <algorithm>

// Multiplication function implementations
Matrix multiply_naive(const Matrix& A, const Matrix& B) {
    if (A.ncol() != B.nrow())
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");

    Matrix C(A.nrow(), B.ncol());
    for (size_t i = 0; i < A.nrow(); ++i) {
        for (size_t j = 0; j < B.ncol(); ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < A.ncol(); ++k) {
                sum += A(i, k) * B(k, j);
            }
            C(i, j) = sum;
        }
    }
    return C;
}

Matrix multiply_tile(const Matrix& A, const Matrix& B, size_t tile_size) {
    if (A.ncol() != B.nrow())
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");

    Matrix C(A.nrow(), B.ncol());
    const size_t M = A.nrow();
    const size_t N = B.ncol();
    const size_t K = A.ncol();

    for (size_t i = 0; i < M; i += tile_size) {
        for (size_t j = 0; j < N; j += tile_size) {
            for (size_t k = 0; k < K; k += tile_size) {
                // Compute tile boundaries
                size_t i_end = std::min(i + tile_size, M);
                size_t j_end = std::min(j + tile_size, N);
                size_t k_end = std::min(k + tile_size, K);

                // Perform matrix multiplication for this tile
                for (size_t ii = i; ii < i_end; ++ii) {
                    for (size_t kk = k; kk < k_end; ++kk) {
                        double r = A(ii, kk);
                        for (size_t jj = j; jj < j_end; ++jj) {
                            C(ii, jj) += r * B(kk, jj);
                        }
                    }
                }
            }
        }
    }
    return C;
}

Matrix multiply_mkl(const Matrix& A, const Matrix& B) {
    if (A.ncol() != B.nrow())
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");

    Matrix C(A.nrow(), B.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                A.nrow(), B.ncol(), A.ncol(),
                1.0, A.get_data(), A.ncol(),
                B.get_data(), B.ncol(),
                0.0, C.get_data(), C.ncol());
    return C;
}
