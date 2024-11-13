#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_
#include <vector>
#include <utility>
#include <mkl.h>
#include "_allocate.hpp"

using namespace std;
//CustomAllocator allocator;

class Matrix{
public:
    using Allocator = CustomAllocator<double>;
    using Buffer = vector<double, Allocator>;
    Matrix(size_t row , size_t col):m_nrow(row) , m_ncol(col) , m_buffer(row * col){}

    void reset_buffer(size_t row , size_t col){
        m_nrow = row;
        m_ncol = col;
        m_buffer = Buffer(col*row);
    }

    size_t nrow() const {
        return m_nrow;
    }

    size_t ncol() const {
        return m_ncol;
    }

    double operator()(size_t row, size_t col) const
    {
        return m_buffer[row*m_ncol + col];
    }

    double &operator()(size_t row , size_t col){
        return m_buffer[row*m_ncol + col];
    } 

    bool operator==(const Matrix &B){
        if((m_nrow != B.nrow()) || (m_ncol != B.ncol())){
            return false;
        }else{
            for(size_t i = 0 ; i < m_nrow ; ++i){
                for(size_t j = 0 ; j < m_ncol ; ++j){
                    if(m_buffer[i * m_ncol + j] != B.m_buffer[i * m_ncol + j]){
                        return false;
                    }
                }
            }
            return true;
        }
    }

    double* data() { return m_buffer.data(); }
    const double* data() const { return m_buffer.data(); }
    
private:
    size_t m_nrow;
    size_t m_ncol;
    Buffer m_buffer;
};

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2);
Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2,  size_t len_size);
Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2);
#endif