#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <mkl.h>
// based on https://yyc.solvcon.net/en/latest/nsd/04matrix/matrix.html
using namespace std;

class Matrix
{

public:
    size_t m_nrow;
    size_t m_ncol;
    double *m_buffer = nullptr;
    //constructor
    Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }
    //function 
    void reset_buffer(size_t nrow, size_t ncol)
    {
        if(m_buffer) //need to reset
        {
            delete[] m_buffer;
        }
        m_buffer = new double[nrow*ncol];
    }
    size_t nrow() const 
    {
        return m_nrow;
    }
    size_t ncol() const 
    {
        return m_ncol;
    }
    // operator
    double operator()(size_t row, size_t col) const
    {
        size_t idx = row * m_ncol + col;
        return m_buffer[idx];
    }
    double &operator()(size_t row, size_t col) 
    {
        size_t idx = row * m_ncol + col;
        return m_buffer[idx];
    }
    bool operator==(const Matrix &other) const
    {
        //bool flag = true
        for (size_t i = 0; i < m_nrow; ++i)
        {
            for (size_t j = 0; j < m_ncol; ++j)
            {
                size_t idx = i * m_ncol + j;
                if (m_buffer[idx] != other.m_buffer[idx])
                    return false;
            }
        }

        return true;
    }
};

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2)
{
    if(mat1.ncol() != mat2.nrow()){ throw std::out_of_range("matrix column differs from vector size");}
        
    Matrix mat3(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < mat1.nrow(); ++i) {
        for (size_t j = 0; j < mat2.ncol(); ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < mat1.ncol(); ++k) {
                    sum += mat1(i, k) * mat2(k, j);
                }
                mat3(i, j) = sum; // 將計算結果存入 C
            }
        }

    return mat3;
}

// matrix tiled
Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2,  size_t len_size)
{
    Matrix ret(mat1.nrow(), mat2.ncol());
    for (size_t i_start = 0; i_start < mat1.nrow(); i_start += len_size)
    {
        for (size_t k_start = 0; k_start < mat2.ncol(); k_start += len_size)
        {
            for (size_t j_start = 0; j_start < mat1.ncol(); j_start += len_size)
            {
                size_t i_end = min(i_start + len_size, mat1.nrow());
                size_t k_end = min(k_start + len_size, mat2.ncol());
                size_t j_end = min(j_start + len_size, mat1.ncol());

                for (size_t i = i_start; i < i_end; i++)
                {
                    for (size_t k = k_start; k < k_end; k++)
                    {
                        for (size_t j = j_start; j < j_end; j++)
                        {
                            ret(i, k) += mat1(i, j) * mat2(j, k);
                        }
                    }
                }
            }
        }    
    }
    return ret;
}


Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2)
{
    Matrix ret(mat1.nrow(), mat2.ncol());
    size_t m = mat1.nrow();
    size_t n = mat2.ncol();
    size_t k = mat1.ncol();
    double alpha = 1.0;
    double beta = 0.0;
    double* A = mat1.m_buffer;
    double* B = mat2.m_buffer;
    double* C = ret.m_buffer;
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, k, alpha, A, k, B, n, beta, C, n);
    return ret;
}

PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "maxtrix multiply function";
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_mkl", &multiply_mkl);
    m.def("multiply_tile", &multiply_tile);
    pybind11::class_<Matrix>(m, "Matrix")        
        .def(pybind11::init<size_t, size_t>())
        .def("__setitem__", [](Matrix &mat1, pair<size_t, size_t> row_col, double val) 
        {
            mat1(row_col.first, row_col.second) = val;
        })
        .def("__getitem__", [](Matrix &mat, pair<size_t, size_t> row_col)
        {
            return mat(row_col.first, row_col.second);
        })
        .def("__eq__", &Matrix::operator==)
        .def_property("nrow", &Matrix::nrow, nullptr)
        .def_property("ncol", &Matrix::ncol, nullptr);
}
