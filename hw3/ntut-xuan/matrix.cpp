#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
#include <mkl.h>

#include "matrix.hpp"

namespace py = pybind11;

Matrix multiply_naive(Matrix a, Matrix b) {
    Matrix result(a.GetRow(), b.GetColumn());

    for(int i = 0; i < a.GetRow(); i++){
        for(int j = 0; j < b.GetColumn(); j++){
            double val = 0;
            for(int k = 0; k < a.GetColumn(); k++){
                val += GetMatrixData(a, i, k) * GetMatrixData(b, k, j);
            }
            GetMatrixData(result, i, j) = val;
        }
    }

    return result;
}

Matrix multiply_tile(Matrix a, Matrix b, size_t tile_size) {
    Matrix result(a.GetRow(), b.GetColumn());

    std::fill(result.matrix_data.data(),
              result.matrix_data.data() + result.GetRow() * result.GetColumn(), 0.0);

    for(int i = 0; i < a.GetRow(); i++){
        for(int j = 0; j < b.GetColumn(); j++){
            for(int k = 0; k < a.GetColumn(); k++){
                size_t i_end = std::min(a.GetRow(), i + tile_size);
                size_t k_end = std::min(a.GetColumn(), k + tile_size);
                size_t j_end = std::min(b.GetColumn(), j + tile_size);

                for (size_t ii = i; ii < i_end; ++ii) {
                    for (size_t kk = k; kk < k_end; ++kk) {
                        double r = GetMatrixData(a, ii, kk);
                        for (size_t jj = j; jj < j_end; ++jj) {
                            GetMatrixData(result, ii, jj) +=
                                r * GetMatrixData(b, kk, jj);
                        }
                    }
                }
            }
        }
    }

    return result;
}


Matrix multiply_mkl(Matrix a, Matrix b) {
    Matrix result(a.GetRow(), b.GetColumn());

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a.GetRow(), b.GetColumn(),
                a.GetColumn(), 1.0, a.matrix_data.data(), a.GetColumn(), b.matrix_data.data(), b.GetColumn(),
                0.0, result.matrix_data.data(), result.GetColumn());

    return result;
}

double& GetMatrixData(Matrix &matrix, int row, int column){
    return matrix.matrix_data[row * matrix.GetColumn() + column];
}

PYBIND11_MODULE(_matrix, m){
    m.doc() = R"pbdoc(
        matrix
        -----------------------

        .. currentmodule:: matrix

        .. autosummary::
           :toctree: _generate

           _matrix
    )pbdoc";

    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def("SetMatrixData", &Matrix::SetMatrixData)
        .def("GetMatrixData", &Matrix::GetMatrixData);


    m.def("multiply_naive", &multiply_naive, "Multiply Naive");        
    m.def("multiply_tile", &multiply_tile, "Multiply tile");        
    m.def("multiply_mkl", &multiply_mkl, "Multiply MKL");        
    m.def("GetMatrixData", &GetMatrixData, "Get matrix data");        
}