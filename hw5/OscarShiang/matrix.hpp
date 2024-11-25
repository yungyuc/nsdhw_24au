#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstddef>
#include <stdexcept>
#include <cstring>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <mkl/mkl.h>

namespace py = pybind11;

class Matrix {
public:
    Matrix(size_t nrow, size_t ncol)
      : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }

    Matrix(Matrix const & other)
      : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(other.m_nrow, other.m_ncol);
        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                (*this)(i, j) = other(i, j);
            }
        }
    }

    Matrix &operator=(Matrix const & other)
    {
        if (this == &other) {
            return *this;
        }
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
            reset_buffer(other.m_nrow, other.m_ncol);
        }
        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                (*this)(i, j) = other(i, j);
            }
        }
        return *this;
    }

    ~Matrix()
    {
        reset_buffer(0, 0);
    }

    double operator() (size_t row, size_t col) const
    {
        return m_buffer[index(row, col)];
    }
    double &operator() (size_t row, size_t col)
    {
        return m_buffer[index(row, col)];
    }

    bool operator== (Matrix const &m)
    {
        if (m_nrow != m.nrow() || m_ncol != m.ncol()) {
            return false;
        }

        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                if (m_buffer[i * m_ncol + j] != m(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    std::string to_string()
    {
        std::string retval = "";
        for (size_t i = 0; i < m_nrow; ++i) {
            retval += std::to_string(m_buffer[i * m_ncol]);
            for (size_t j = 1; j < m_ncol; ++j) {
                retval += "\t" + std::to_string(m_buffer[i * m_ncol + j]);
            }
            if (i != m_nrow - 1) {
                retval += "\n";
            }
        }
        return retval;
    }

    double *data() const { return m_buffer; }

    size_t nrow() const { return m_nrow; }

    size_t ncol() const { return m_ncol; }

    static Matrix multiply_naive(Matrix const &a, Matrix const &b);
    static Matrix multiply_tile(Matrix const &a, Matrix const &b, const size_t step);
    static Matrix multiply_mkl(Matrix const &a, Matrix const &b);

private:
    size_t index(size_t row, size_t col) const
    {
        return row * m_ncol + col;
    }

    void reset_buffer(size_t nrow, size_t ncol)
    {
        if (m_buffer) {
            delete[] m_buffer;
        }
        const size_t nelement = nrow * ncol;
        if (nelement) {
            m_buffer = new double[nelement];
            memset(m_buffer, 0, sizeof(double) * nelement);
        } else {
            m_buffer = nullptr;
        }
        m_nrow = nrow;
        m_ncol = ncol;
    }

    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double *m_buffer = nullptr;
};

Matrix Matrix::multiply_naive(Matrix const &mat1, Matrix const &mat2)
{
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("Dimesion mismatch");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < ret.nrow(); ++i) {
        for (size_t k = 0; k < ret.ncol(); ++k) {
            double val = 0;
            for (size_t j = 0; j < mat1.ncol(); ++j) {
                val += mat1(i, j) * mat2(j, k);
            }
            ret(i, k) = val;
        }
    }
    return ret;
}

Matrix Matrix::multiply_tile(Matrix const &mat1, Matrix const &mat2, const size_t step)
{
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("Dimension mismatch");
    }

    // XXX: Can we simplify these loops with multiply_naive?
    Matrix m(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < mat1.nrow(); i += step) {
        for (size_t k = 0; k < mat2.ncol(); k += step) {
            for (size_t j = 0; j < mat1.ncol(); j += step) {
                for (size_t ti = i; ti < std::min(mat1.nrow(), i + step); ++ti) {
                    for (size_t tk = k; tk < std::min(mat2.ncol(), k + step); ++tk) {
                        for (size_t tj = j; tj < std::min(mat1.ncol(), j + step); ++tj) {
                            m(ti, tk) += mat1(ti, tj) * mat2(tj, tk);
                        }
                    }
                }
            }
        }
    }
    return m;
}

Matrix Matrix::multiply_mkl(Matrix const &mat1, Matrix const &mat2)
{
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("Dimension mismatch");
    }

    Matrix m(mat1.nrow(), mat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat1.nrow(),
                mat2.ncol(), mat1.ncol(), 1, mat1.data(), mat1.ncol(),
                mat2.data(), mat2.ncol(), 0, m.data(), m.ncol());

    return m;
}

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__assign__", &Matrix::operator=)
        .def("__setitem__", [](Matrix &m, std::vector<size_t> idx, double val) {
            m(idx[0], idx[1]) = val;
        })
        .def("__getitem__", [](Matrix &m, std::vector<size_t> idx) {
            return m(idx[0], idx[1]);
        })
        .def("__repr__", &Matrix::to_string)
        .def("__eq__", &Matrix::operator==);
    m.def("multiply_naive", &Matrix::multiply_naive);
    m.def("multiply_tile", &Matrix::multiply_tile);
    m.def("multiply_mkl", &Matrix::multiply_mkl);
}

#endif /* __MATRIX_HPP__ */
