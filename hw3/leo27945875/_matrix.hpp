#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <string.h>
#include <mkl.h>


class Matrix {
public:
    Matrix(size_t nrow, size_t ncol)
        : m_nrow(nrow), m_ncol(ncol), m_buffer(new double[nrow * ncol])
    {
        memset(m_buffer, 0, nrow * ncol * sizeof(double));
    }
    Matrix(const Matrix& other)
        : m_nrow(other.nrow()), m_ncol(other.ncol())
    {
        size_t n_elem = m_nrow * m_ncol;
        m_buffer = new double[n_elem];
        memcpy(m_buffer, other.data_ptr(), n_elem * sizeof(double));
    }
    ~Matrix()
    {
        delete[] m_buffer;
    }

    Matrix& operator=(const Matrix& other){
        delete[] m_buffer;
        m_nrow = other.nrow();
        m_ncol = other.ncol();
        size_t n_elem = m_nrow * m_ncol;
        m_buffer = new double[n_elem];
        memcpy(m_buffer, other.data_ptr(), n_elem * sizeof(double));
        return *this;
    }
    bool operator==(const Matrix& other) const {
        if (m_nrow != other.nrow() || m_ncol != other.ncol())
            return false;
        for (size_t i = 0; i < m_nrow; i++)
        for (size_t j = 0; j < m_ncol; j++)
            if (this->operator()(i, j) != other(i, j))
                return false;
        return true;
    }
    double operator() (size_t row, size_t col) const
    {
        if (isOut(row, col))
            throw std::invalid_argument("Index out of range.");
        return m_buffer[row*m_ncol + col];
    }
    double & operator() (size_t row, size_t col)
    {
        if (isOut(row, col))
            throw std::invalid_argument("Index out of range.");
        return m_buffer[row*m_ncol + col];
    }

    double   get(size_t row, size_t col) const { return this->operator()(row, col); }
    double & set(size_t row, size_t col)       { return this->operator()(row, col); }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    double *  data_ptr() const { return m_buffer; }
    double *& data_ptr()       { return m_buffer; }

    bool isOut(size_t row, size_t col) const { 
        return row >= m_nrow || col >= m_ncol; 
    }
    void show() const {
        for (size_t i = 0; i < nrow(); i++){
            for (size_t j = 0; j < ncol(); j++)
                std::cout << this->operator()(i, j) << " ";
            std::cout << std::endl;
        }
    }
    void randInit(){
        for (size_t i = 0; i < nrow(); i++)
            for (size_t j = 0; j < ncol(); j++)
                this->operator()(i, j) = (float)(rand()) / (float)(RAND_MAX);;
    }

private:
    size_t m_nrow;
    size_t m_ncol;
    double *m_buffer;

};


Matrix multiply_naive(const Matrix &A, const Matrix &B){
    Matrix C(A.nrow(), B.ncol());
    for (size_t i = 0; i < A.nrow(); i++){
        for (size_t j = 0; j < B.ncol(); j++){
            for (size_t k = 0; k < B.nrow(); k++){
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return C;
}


Matrix multiply_tile(const Matrix &A, const Matrix &B, size_t tile){
    Matrix C(A.nrow(), B.ncol());
    for (size_t ti = 0; ti < A.nrow(); ti+=tile)
    for (size_t tj = 0; tj < B.ncol(); tj+=tile)
    for (size_t tk = 0; tk < B.nrow(); tk+=tile)
    for (size_t i = ti; i < ti + tile && i < A.nrow(); i++){
        for (size_t j = tj; j < tj + tile && j < B.ncol(); j++){
            for (size_t k = tk; k < tk + tile && k < B.nrow(); k++){
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return C;
}


Matrix multiply_mkl(const Matrix &A, const Matrix &B){
    Matrix C(A.nrow(), B.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, A.nrow(), B.ncol(), A.ncol(), 1., A.data_ptr(), A.ncol(), B.data_ptr(), B.ncol(), 0., C.data_ptr(), C.ncol());
    return C;
}



