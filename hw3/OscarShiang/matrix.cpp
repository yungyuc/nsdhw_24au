#include <cstddef>
#include <stdexcept>
#include <cstring>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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

    size_t nrow() const { return m_nrow; }

    size_t ncol() const { return m_ncol; }

    static Matrix multiply_naive(Matrix const &a, Matrix const &b);
    static Matrix multiply_tile(Matrix const &a, Matrix const &b);
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

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__setitem__", [](Matrix &m, std::vector<size_t> idx, double val) {
            m(idx[0], idx[1]) = val;
        })
        .def("__getitem__", [](Matrix &m, std::vector<size_t> idx) {
            return m(idx[0], idx[1]);
        });
    m.def("multiply_naive", &Matrix::multiply_naive);
}
