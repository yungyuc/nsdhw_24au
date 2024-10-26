#include <iostream>
#include <iomanip>
#include <mkl/mkl.h>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <vector>

class Matrix {
public:
    Matrix(size_t nrow, size_t ncol): m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }

    Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec): m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
        (*this) = vec;
    }

    Matrix & operator=(std::vector<double> const & vec)
    {
        if (size() != vec.size())
            throw std::out_of_range("number of elements mismatch");

        size_t k = 0;
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = vec[k];
                ++k;
            }
        }
        return *this;
    }

    Matrix(Matrix const & other): m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(other.m_nrow, other.m_ncol);
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = other(i,j);
            }
        }
    }

    Matrix & operator=(Matrix const & other)
    {
        if (this == &other) { return *this; }
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
            reset_buffer(other.m_nrow, other.m_ncol);

        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = other(i,j);
            }
        }
        return *this;
    }

    Matrix(Matrix && other): m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
    }

    Matrix & operator=(Matrix && other)
    {
        if (this == &other) { return *this; }
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
        return *this;
    }

    ~Matrix()
    {
        reset_buffer(0, 0);
    }

    double   operator() (size_t row, size_t col) const
    {
        return m_buffer[index(row, col)];
    }
    double & operator() (size_t row, size_t col)
    {
        return m_buffer[index(row, col)];
    }
    double   operator() (size_t s) const
    {
        return m_buffer[s];
    }
    double & operator() (size_t s)
    {
        return m_buffer[s];
    }
    bool operator== (Matrix const & other) const
    {
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
            return false;
        for (size_t i = 0; i < m_nrow; ++i)
        {
            for (size_t j = 0; j < m_ncol; ++j)
            {
                if ((*this)(i,j) != other(i,j))
                    return false;
            }
        }
        return true;
    }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    size_t size() const { return m_nrow * m_ncol; }
    double buffer(size_t i) const { return m_buffer[i]; }
    std::vector<double> buffer_vector() const
    {
        return std::vector<double>(m_buffer, m_buffer+size());
    }
    double * get_buffer() const { return m_buffer; }

private:

    size_t index(size_t row, size_t col) const
    {
        return row*m_ncol + col;
    }

    void reset_buffer(size_t nrow, size_t ncol)
    {
        if (m_buffer) { delete[] m_buffer; }
        const size_t nelement = nrow * ncol;
        if (nelement)
        {
            m_buffer = new double[nelement];
            for (size_t i=0; i<nelement; ++i)
                m_buffer[i] = 0;
        }
        else          { m_buffer = nullptr; }
        m_nrow = nrow;
        m_ncol = ncol;
    }

    size_t m_nrow ;
    size_t m_ncol ;
    double * m_buffer = nullptr;

}; // close class Matrix

std::ostream & operator << (std::ostream & ostr, Matrix const & mat)
{
    for (size_t i=0; i<mat.nrow(); ++i)
    {
        ostr << std::endl << " ";
        for (size_t j=0; j<mat.ncol(); ++j)
        {
            ostr << " " << std::setw(2) << mat(i, j);
        }
    }

    return ostr;
}

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

Matrix multiply_tile (Matrix const & mat1, Matrix const & mat2, size_t tsize)
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
                        double tmp_sum = 0;
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

PYBIND11_MODULE(_matrix, m)
{
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def(pybind11::init<size_t, size_t, std::vector<double> const &>())
        .def(pybind11::init<Matrix const &>())
        .def("__getitem__", [](Matrix & mat, std::pair<size_t, size_t> const & idx)
        {
            return mat(idx.first, idx.second);
        })
        .def("__getitem__", [](Matrix & mat, size_t const & idx)
        {
            return mat(idx);
        })
        .def("__setitem__", [](Matrix & mat, std::pair<size_t, size_t> const & idx, double val)
        {
            mat(idx.first, idx.second) = val;
        })
        .def("__setitem__", [](Matrix & mat, size_t const & idx, double val)
        {
            mat(idx) = val;
        })
        .def("__eq__", &Matrix::operator==)
        .def_property("nrow", &Matrix::nrow, nullptr)
        .def_property("ncol", &Matrix::ncol, nullptr)
        .def("buffer", &Matrix::buffer)
        .def("buffer_vector", &Matrix::buffer_vector)
        .def("get_buffer", &Matrix::get_buffer);

} 

