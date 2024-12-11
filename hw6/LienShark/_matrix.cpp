#include <mkl/mkl.h>
#include <mkl/mkl_cblas.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <bits/stdc++.h>

#define MATRIX_H
namespace py = pybind11;

class Matrix
{
public:
    double *m_buffer;
    Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol)
    {
        size_t nelement = nrow * ncol;
        m_buffer = new double[nelement];
        memset(m_buffer, 0, nelement * sizeof(double));
    }

    Matrix(const Matrix &m) : m_nrow(m.nrow()), m_ncol(m.ncol())
    {
        size_t nelement = m_nrow * m_ncol;
        m_buffer = new double[nelement];
        memcpy(m_buffer, m.m_buffer, nelement * sizeof(double));
    }

    ~Matrix() { delete[] m_buffer; }

    double operator()(size_t row, size_t col) const
    {
        return m_buffer[row * m_ncol + col];
    }
    double &operator()(size_t row, size_t col)
    {
        return m_buffer[row * m_ncol + col];
    }

    bool operator==(const Matrix &other) const
    {
        if (nrow() != other.nrow() || ncol() != other.ncol())
        {
            return false;
        }

        for (size_t i = 0; i < m_nrow; i++)
        {
            for (size_t j = 0; j < m_ncol; j++)
            {
                if ((*this)(i, j) != other(i, j))
                {
                    return false;
                }
            }
        }
        return true;
    }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    double *in_buffer() { return m_buffer; }

private:
    size_t m_nrow;
    size_t m_ncol;
};
Matrix multiply_naive(Matrix &a, Matrix &b)
{
    if (a.ncol() != b.nrow())
    {
        exit(1);
    }

    Matrix c(a.nrow(), b.ncol());
    for (size_t i = 0; i < a.nrow(); i++)
    {
        for (size_t j = 0; j < b.ncol(); j++)
        {
            for (size_t k = 0; k < a.ncol(); k++)
            {
                c(i, j) += a(i, k) * b(k, j);
            }
        }
    }
    return c;
}

Matrix multiply_tile(Matrix const &a, Matrix const &b, size_t const tile_size)
{
    if (a.ncol() != b.nrow())
    {
        exit(1);
    }

    Matrix c(a.nrow(), b.ncol());
    for (size_t i = 0; i < a.nrow(); i += tile_size)
    {
        for (size_t k = 0; k < a.ncol(); k += tile_size)
        {
            for (size_t j = 0; j < b.ncol(); j += tile_size)
            {
                for (size_t ti = i; ti < std::min(i + tile_size, a.nrow());
                     ti++)
                {
                    for (size_t tk = k; tk < std::min(k + tile_size, a.ncol());
                         tk++)
                    {
                        for (size_t tj = j;
                             tj < std::min(j + tile_size, b.ncol()); tj++)
                        {
                            c(ti, tj) += a(ti, tk) * b(tk, tj);
                        }
                    }
                }
            }
        }
    }
    return c;
}

Matrix multiply_mkl(Matrix const &mat1, Matrix const &mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        exit(1);
    }

    mkl_set_num_threads(1);

    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(CblasRowMajor,
                CblasNoTrans,
                CblasNoTrans,
                mat1.nrow(),
                mat2.ncol(),
                mat1.ncol(),
                1.0,
                mat1.m_buffer,
                mat1.ncol(),
                mat2.m_buffer,
                mat2.ncol(),
                0.0,
                ret.m_buffer,
                ret.ncol());

    return ret;
}

PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "matrix-matrix multiplication";

    m.def("multiply_naive", &multiply_naive, "multiply_naive");
    m.def("multiply_tile", &multiply_tile, "multiply_tile");
    m.def("multiply_mkl", &multiply_mkl, "multiply_mkl");
    py::class_<Matrix>(m, "Matrix", pybind11::buffer_protocol())
        .def(py::init<size_t, size_t>())
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def_property_readonly("array", [](Matrix &m)
                               {
                                  size_t _size = 8 ;
                                  return pybind11::array_t<double>(
                                    {m.nrow(), m.ncol()},
                                    {_size*m.ncol(), _size},
                                    m.in_buffer(),
                                    pybind11::cast(m)); })
        .def("__eq__", [](const Matrix &a, const Matrix &b)
             { return a == b; })
        .def("__setitem__",
             [](Matrix &self, std::pair<size_t, size_t> idx, double val)
             {
                 self(idx.first, idx.second) = val;
             })
        .def("__getitem__",
             [](const Matrix &self, std::pair<size_t, size_t> idx)
             {
                 return self(idx.first, idx.second);
             });
}