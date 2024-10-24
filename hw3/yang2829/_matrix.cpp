#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <vector>

#include <mkl.h>
#include <mkl_lapack.h>
#include <mkl_lapacke.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

struct Matrix {

public:

    Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol) {
        m_buffer = new double[nrow * ncol];
        for (size_t i = 0; i < nrow * ncol; i++) {
            m_buffer[i] = 0;
        }
    }
    Matrix(size_t nrow, size_t ncol, std::vector<double> & vec) : m_nrow(nrow), m_ncol(ncol) {
        m_buffer = new double[nrow * ncol];
        for (size_t i = 0; i < nrow * ncol; i++) {
            m_buffer[i] = vec[i];
        }
    }
    Matrix(const Matrix &m) : m_nrow(m.nrow()), m_ncol(m.ncol()) {
        m_buffer = new double[m_nrow * m_ncol];
        for (size_t i = 0; i < m_nrow * m_ncol; i++) {
            m_buffer[i] = m.m_buffer[i];
        }
    }

    ~Matrix() {
        if (m_buffer) { delete[] m_buffer; }
    }

    double   operator() (size_t row, size_t col) const {
        return m_buffer[index(row, col)];
    }
    double& operator() (size_t row, size_t col) {
        return m_buffer[index(row, col)];
    }
    bool operator==(const Matrix &m) const {
        if (m_nrow != m.nrow() || m_ncol != m.ncol()) {
            return false;
        }
        for (size_t i = 0; i < m_nrow * m_ncol; i++) {
            if (m_buffer[i] != m.m_buffer[i]) {
                return false;
            }
        }
        return true;
    }
    size_t index(size_t row, size_t col) const {
        if (row >= m_nrow || col >= m_ncol)
            throw std::out_of_range("index out of range");
        return row * m_ncol + col;
    }

    std::vector<double> buffer_vector() const { return std::vector<double>(m_buffer, m_buffer+size()); }
    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    size_t size() const { return m_nrow * m_ncol; }

    double * m_buffer = nullptr;

private:
    size_t m_nrow = 0;
    size_t m_ncol = 0;
};

Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2) {
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

Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t tsize) {
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());

    const size_t nrow1 = mat1.nrow();
    const size_t ncol1 = mat1.ncol();
    const size_t ncol2 = mat2.ncol();

    for (size_t it=0; it<nrow1; it+=tsize) {
        size_t lim_i = std::min(it + tsize, nrow1);
        for (size_t jt=0; jt<ncol2; jt+=tsize) {
            size_t lim_j = std::min(jt + tsize, ncol2);
            for (size_t kt=0; kt<ncol1; kt+=tsize) {
                size_t lim_k = std::min(kt + tsize, ncol1);
                
                for (size_t i = it; i < lim_i; ++i) {
                    for (size_t j = jt; j < lim_j; ++j) {
                        double sum = 0.0;
                        for (size_t k = kt; k < lim_k; ++k) {
                            sum += mat1(i, k) * mat2(k, j);
                        }
                        ret(i, j) += sum;
                    }
                }
            }
        }
    }
    return ret;
}

Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2) {
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor
      , CblasNoTrans
      , CblasNoTrans 
      , mat1.nrow()
      , mat2.ncol() 
      , mat1.ncol() 
      , 1.0 
      , mat1.m_buffer 
      , mat1.ncol() 
      , mat2.m_buffer 
      , mat2.ncol() 
      , 0.0 
      , ret.m_buffer 
      , ret.ncol() 
    );
    return ret;
}

PYBIND11_MODULE(_matrix, m) {
    m.doc() = "hw3 Matrix";

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def(pybind11::init<size_t, size_t, std::vector<double> &>())
        .def(pybind11::init<const Matrix &>())
        .def("buffer_vector", &Matrix::buffer_vector)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__getitem__", [](Matrix &m, std::vector<std::size_t> idx) {
            return m(idx[0], idx[1]);
        })
        .def("__setitem__", [](Matrix &m, std::vector<std::size_t> idx, double val) {
            m(idx[0], idx[1]) = val;
        })
        .def("__eq__", &Matrix::operator==);

    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}
