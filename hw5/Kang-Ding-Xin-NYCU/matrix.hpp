#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <mkl.h>
#include <vector>

class Matrix 
{

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
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = other(i,j);
            }
        }
    }

    double   operator() (size_t row, size_t col) const
    {
        return m_buffer[index(row, col)];
    }

    double & operator() (size_t row, size_t col)
    {
        return m_buffer[index(row, col)];
    }

    bool operator==(Matrix const & other) const 
    {
        if ((this->m_nrow != other.nrow()) || (this->m_ncol != other.ncol())){
            return false;
        }
        for(size_t i = 0; i < other.nrow(); i++){
            for(size_t j = 0; j < other.ncol(); j++){
                if(this->m_buffer[index(i, j)] != other(i, j)){
                    return false;
                }
            }
        }
        return true;
    }

    double* buf_get() const 
    { 
        return m_buffer;
    }

    void   buf_set(std::vector<double> &data) 
    { 
        for(size_t i = 0; i < m_nrow*m_ncol; i++)
        {
            m_buffer[i] = data[i];
        }
    }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    size_t size() const { return m_nrow * m_ncol; }

private:

    size_t index(size_t row, size_t col) const
    {
        return row * m_ncol + col;
    }

    void reset_buffer(size_t nrow, size_t ncol)
    {
        if (m_buffer) { delete[] m_buffer; }
        const size_t nelement = nrow * ncol;
        if (nelement) {
            m_buffer = new double[nelement];
            for(size_t i = 0; i < nelement; i++){
                m_buffer[i] = 0;
            }
        }
        else          { m_buffer = nullptr; }
        m_nrow = nrow;
        m_ncol = ncol;
    }

    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double * m_buffer = nullptr;
};

Matrix multiply_naive(Matrix const & m1, Matrix const & m2);
Matrix multiply_tile(Matrix const & m1, Matrix const & m2, size_t t);
Matrix multiply_mkl(Matrix const & m1, Matrix const & m2);

#endif