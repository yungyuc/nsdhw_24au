#include "matrix.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
#include <mkl_cblas.h>

namespace py = pybind11;

Matrix multiply_naive(const Matrix& A, const Matrix& B) {
    if (A.get_cols() != B.get_rows())
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");

    Matrix C(A.get_rows(), B.get_cols());
    for (size_t i = 0; i < A.get_rows(); ++i) {
        for (size_t j = 0; j < B.get_cols(); ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < A.get_cols(); ++k) {
                sum += A(i, k) * B(k, j);
            }
            C(i, j) = sum;
        }
    }
    return C;
}

Matrix multiply_tile(const Matrix& A, const Matrix& B, size_t tile_size) {
    if (A.get_cols() != B.get_rows())
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");

    Matrix C(A.get_rows(), B.get_cols());
    const size_t M = A.get_rows();
    const size_t N = B.get_cols();
    const size_t K = A.get_cols();

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
    if (A.get_cols() != B.get_rows())
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");

    Matrix C(A.get_rows(), B.get_cols());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                A.get_rows(), B.get_cols(), A.get_cols(),
                1.0, A.get_data(), A.get_cols(),
                B.get_data(), B.get_cols(),
                0.0, C.get_data(), C.get_cols());
    return C;
}

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def("__getitem__", [](const Matrix &m, std::pair<size_t, size_t> idx) {
            return m(idx.first, idx.second);
        })
        .def("__setitem__", [](Matrix &m, std::pair<size_t, size_t> idx, double value) {
            m(idx.first, idx.second) = value;
        })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def_property_readonly("nrow", &Matrix::get_rows)
        .def_property_readonly("ncol", &Matrix::get_cols)
        .def("data", [](Matrix &m) -> py::array_t<double> {
            return py::array_t<double>(
                {m.get_rows(), m.get_cols()},
                {m.get_cols() * sizeof(double), sizeof(double)},
                m.get_data(),
                py::cast(m));
        })
        .def("__repr__", [](const Matrix &m) {
            std::stringstream ss;
            ss << "Matrix(" << m.get_rows() << ", " << m.get_cols() << ")";
            return ss.str();
        });

    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}