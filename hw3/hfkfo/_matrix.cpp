#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <mkl.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

class Matrix {

public:

    Matrix(size_t nrow, size_t ncol)
      : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }

    Matrix(Matrix && other)
      : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
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

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

    size_t size() const { return m_nrow * m_ncol; }
    double* buffer() const { return m_buffer; }

    bool operator == (Matrix const &mat1)
    {
        if (this->m_nrow != mat1.nrow() || this->m_ncol != mat1.ncol())
            return false;
        for (size_t i = 0; i < mat1.nrow(); ++i)
        {
            for (size_t j = 0; j < mat1.ncol(); ++j)
            {
                if (this->m_buffer[index(i, j)] != mat1(i, j))
                    return false;
            }
        }
        return true;
    }
    

private:

    size_t index(size_t row, size_t col) const
    {
        return row + col * m_nrow;
    }

    void reset_buffer(size_t nrow, size_t ncol)
    {
        if (m_buffer) { delete[] m_buffer; }
        const size_t nelement = nrow * ncol;
        if (nelement) { 
            m_buffer = new double[nelement]; 
            std::fill(m_buffer, m_buffer + nelement, 0.0);
        }
        else          { m_buffer = nullptr; }
        m_nrow = nrow;
        m_ncol = ncol;
    }

    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double * m_buffer = nullptr;
};

/*
 * Naive matrix matrix multiplication.
 */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i=0; i<ret.nrow(); ++i)
    {
        for (size_t k=0; k<ret.ncol(); ++k)
        {
            double v = 0;
            for (size_t j=0; j<mat1.ncol(); ++j)
            {
                v += mat1(i,j) * mat2(j,k);
            }
            ret(i,k) = v;
        }
    }

    return ret;
}

Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t size)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for(size_t i = 0 ; i < mat1.nrow() ; i += size)
    {
        for(size_t k = 0 ; k < mat2.ncol() ; k += size)
        {
            for(size_t j = 0; j < mat1.ncol() ; j += size)
            {
                for(size_t ti = i; ti < std::min(mat1.nrow(), i + size) ; ++ti)
                {
                    for(size_t tk = k ; tk < std::min(mat2.ncol(), k + size) ; ++tk)
                    {
                        for(size_t tj = j ; tj < std::min(mat1.ncol(), j + size) ; ++tj)
                        {
                            ret(ti, tk) += mat1(ti, tj) * mat2(tj, tk);
                        }
                    }
                }
            }
        }
    }
    return ret;
}

Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());
    
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                mat1.nrow(), mat2.ncol(), mat1.ncol(), 1.0, 
                mat1.buffer(), mat1.ncol(),  // A matrix
                mat2.buffer(), mat2.ncol(),  // B matrix
                0.0, 
                ret.buffer(), ret.ncol());  // C matrix (result)

    return ret;
}

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




PYBIND11_MODULE(_matrix, m){
    m.def("multiply_naive", &multiply_naive, "use naive");
    m.def("multiply_mkl", &multiply_mkl, "use mkl");
    m.def("multiply_tile", &multiply_tile, "use tile");
    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def("__setitem__", [](Matrix &self, std::pair<size_t, size_t> i, double val) {
            self(i.first, i.second) = val;
        })
        .def("__getitem__", [](Matrix &self, std::pair<size_t, size_t> i) {
            return self(i.first, i.second);
        })
        .def("__eq__", &Matrix::operator==)
        .def_property("nrow", &Matrix::nrow, nullptr)
        .def_property("ncol", &Matrix::ncol, nullptr);
}