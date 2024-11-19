#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <mkl.h>
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

    bool operator == (Matrix const &mat1)const 
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


Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t size);
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2);
Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2);
std::ostream & operator << (std::ostream & ostr, Matrix const & mat);