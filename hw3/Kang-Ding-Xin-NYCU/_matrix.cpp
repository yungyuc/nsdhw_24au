#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <mkl.h>
#include <vector>

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

    bool operator==(Matrix const & other)
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

    double*   buf_get() const 
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

    void printm(){
        std::cout << m_nrow << " " << m_ncol << "\n";
        for(size_t i = 0; i < m_nrow; ++i){
            for(size_t j = 0; j < m_ncol; ++j){
                std::cout << m_buffer[index(i, j)] << " ";
            }
            std::cout << "\n";
        }
    }
    

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

Matrix multiply_naive(Matrix const & m1, Matrix const & m2){
    if(m1.ncol()!=m2.nrow()){
        throw std::invalid_argument("wrong dimention");
    }
    Matrix res(m1.nrow(), m2.ncol());
    for(size_t i = 0; i < m1.nrow(); ++i){
        for(size_t j = 0; j < m2.ncol(); ++j){
            double element = 0;
            for(size_t k = 0; k < m1.ncol(); ++k){
                element += m1(i, k) * m2(k, j);
            }
            res(i, j) = element;
        }
    }
    return res;
}

Matrix multiply_tile(Matrix const & m1, Matrix const & m2, size_t t){
    if(m1.ncol()!=m2.nrow()){
        throw std::invalid_argument("wrong dimention");
    }
    Matrix res(m1.nrow(), m2.ncol());
    for(size_t i = 0; i < m1.nrow(); i += t){
        for(size_t j = 0; j < m2.ncol(); j += t){
            for(size_t k = 0; k < m1.ncol(); k += t){
                for(size_t it = i; it < std::min(m1.nrow(), i + t); ++it){
                    for(size_t jt = j; jt < std::min(m2.ncol(), j + t); ++jt){
                        for(size_t kt = k; kt < std::min(m1.ncol(), k + t); ++kt){
                            res(it, jt) += m1(it, kt) * m2(kt, jt);
                        }
                    }
                }
            }
        }
    }

    return res;
}

Matrix multiply_mkl(Matrix const & m1, Matrix const & m2){
    if(m1.ncol()!=m2.nrow()){
        throw std::invalid_argument("wrong dimention");
    }
    Matrix res(m1.nrow(), m2.ncol());
    size_t m = m1.nrow();
    size_t n = m2.ncol();
    size_t k = m1.ncol();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, 1.0, m1.buf_get(), k, m2.buf_get(), n, 1.0, res.buf_get(), n);
    return res;
}

PYBIND11_MODULE(_matrix, m){
    m.def("multiply_naive", &multiply_naive, "use naive");
    m.def("multiply_tile", &multiply_tile, "use tile");
    m.def("multiply_mkl", &multiply_mkl, "use mkl");
    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def(pybind11::init<Matrix const &>())
        .def("__setitem__", [](Matrix &self, std::pair<size_t, size_t> i, double val) {
            self(i.first, i.second) = val;
        })
        .def("__getitem__", [](Matrix &self, std::pair<size_t, size_t> i) {
            return self(i.first, i.second);
        })
        .def("__eq__", &Matrix::operator==)
        .def("buf_get", &Matrix::buf_get)
        .def("buf_set", &Matrix::buf_set)
        .def("buf_set", &Matrix::buf_set)
        .def("printm", &Matrix::printm)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def_property_readonly("size", &Matrix::size);
}