#include "matrix.hpp"

// #include <pybind11/stl.h>
// #include <pybind11/pybind11.h>

Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < mat1.nrow(); ++i)
    {
        for (size_t k = 0; k < mat2.ncol(); ++k)
        {
            double v = 0;
            for (size_t j = 0; j < mat1.ncol(); ++j)
            {
                v += mat1(i, j) * mat2(j, k);
            }
            ret(i, k) = v;
        }
    }

    return ret;
}

Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t tsize)
{
    if (mat1.ncol() != mat2.nrow())
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");

    Matrix ret(mat1.nrow(), mat2.ncol());
    for(size_t i = 0; i < mat1.nrow(); i += tsize)
    {
        size_t ii_limit = std::min(i+tsize, mat1.nrow());
        for(size_t j = 0; j < mat2.ncol(); j += tsize)
        {
            size_t jj_limit = std::min(j+tsize, mat2.ncol());
            for(size_t k = 0; k < mat1.ncol(); k += tsize)
            {
                size_t kk_limit = std::min(k+tsize, mat1.ncol());
                for(size_t ii = i; ii < ii_limit; ii++)
                {
                    for(size_t jj = j; jj < jj_limit; jj++)
                    {
                        double tmp_sum = 0.;
                        for(size_t kk = k; kk < kk_limit; kk++)
                        {
                            tmp_sum += mat1(ii, kk) * mat2(kk, jj);
                        }
                        ret(ii, jj) += tmp_sum;
                    }
                }
            }
        }
    }
    return ret;
}


Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());
    cblas_dgemm(
        CblasRowMajor,
        CblasNoTrans, 
        CblasNoTrans, 
        mat1.nrow(), 
        mat2.ncol(), 
        mat1.ncol(), 
        1.0, 
        mat1.get_buffer(), 
        mat1.ncol(), 
        mat2.get_buffer(), 
        mat2.ncol(), 
        0.0, 
        ret.get_buffer(), 
        ret.ncol()
    );
    return ret;
}

// PYBIND11_MODULE(_matrix, m)
// {
//     m.def("multiply_naive", &multiply_naive);
//     m.def("multiply_tile", &multiply_tile);
//     m.def("multiply_mkl", &multiply_mkl);
//     pybind11::class_<Matrix>(m, "Matrix")
//         .def(pybind11::init<size_t, size_t>())
//         .def(pybind11::init<size_t, size_t, std::vector<double> const &>())
//         .def(pybind11::init<Matrix const &>())
//         .def("__getitem__", [](Matrix & mat, std::pair<size_t, size_t> const & idx)
//         {
//             return mat(idx.first, idx.second);
//         })
//         .def("__getitem__", [](Matrix & mat, size_t const & idx)
//         {
//             return mat(idx);
//         })
//         .def("__setitem__", [](Matrix & mat, std::pair<size_t, size_t> const & idx, double val)
//         {
//             mat(idx.first, idx.second) = val;
//         })
//         .def("__setitem__", [](Matrix & mat, size_t const & idx, double val)
//         {
//             mat(idx) = val;
//         })
//         .def("__eq__", &Matrix::operator==)
//         .def_property("nrow", &Matrix::nrow, nullptr)
//         .def_property("ncol", &Matrix::ncol, nullptr)
//         .def("buffer", &Matrix::buffer)
//         .def("buffer_vector", &Matrix::buffer_vector)
//         .def("get_buffer", &Matrix::get_buffer);

// } 