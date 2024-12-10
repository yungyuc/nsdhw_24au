#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <iomanip>
#include <mkl/mkl.h>
#include <vector>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

class Matrix {
public:
    Matrix() { m_nrow = 0; m_ncol = 0; m_buffer = nullptr; };
    Matrix(std::size_t nrow, std::size_t ncol) {
        m_nrow = nrow; m_ncol = ncol; 
        m_buffer = new double[nrow*ncol]; 
        for (std::size_t i=0; i<nrow; ++i)
        { 
            for (std::size_t j=0; j<ncol; ++j)
            { 
                (*this)(i,j) = 0; 
            } 
        }
    };
    Matrix(const Matrix& other)
    { 
        m_nrow = other.m_nrow; 
        m_ncol = other.m_ncol; 
        m_buffer = new double[m_nrow*m_ncol]; 
        for (std::size_t i=0; i<m_nrow; ++i)
        { 
            for (std::size_t j=0; j<m_ncol; ++j)
            { 
                (*this)(i,j) = other(i,j); 
            } 
        } 
    };
    ~Matrix() 
    { 
        reset_buffer(0, 0);
        // delete [] m_buffer;
    };

    double operator() (std::size_t row, std::size_t col) const { return m_buffer[row*m_ncol + col]; };
    double & operator() (std::size_t row, std::size_t col) { return m_buffer[row*m_ncol + col]; };
    
    
    bool operator==(const Matrix& other) const
    {
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
            return false;
        for (std::size_t i = 0; i < m_nrow; ++i)
        {
            for (std::size_t j = 0; j < m_ncol; ++j)
            {
                if ((*this)(i,j) != other(i,j))
                    return false;
            }
        }
        return true;
    };
    std::size_t nrow() const { return m_nrow; };
    std::size_t ncol() const { return m_ncol; };
    double* get_buffer() const { return m_buffer; };
    pybind11::array_t<double> array() const
    {
        return pybind11::array_t<double>
        (
            {m_nrow, m_ncol}, 
            {m_ncol * sizeof(double), sizeof(double)},
            m_buffer,
            pybind11::capsule(m_buffer, [](void *f) {})
        );
    }


private:
    std::size_t m_nrow;
    std::size_t m_ncol;
    double * m_buffer;

    void reset_buffer(std::size_t nrow, std::size_t ncol)
    {
        if (m_buffer) { delete[] m_buffer; }
        const std::size_t nelement = nrow * ncol;
        if (nelement)
        {
            m_buffer = new double[nelement];
            // for (std::size_t i=0; i<nelement; ++i)
            //     m_buffer[i] = 0;
        }
        else { m_buffer = nullptr; }
        m_nrow = nrow;
        m_ncol = ncol;
    };
}; // close class Matrix


Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2);
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, std::size_t tsize);
Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2);

#endif // __MATRIX_HPP__