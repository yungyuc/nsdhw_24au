#include "matrix.hpp"

Matrix multiply_naive(Matrix const & m1, Matrix const & m2)
{
    if(m1.ncol()!=m2.nrow())
    {
        throw std::invalid_argument("wrong dimension");
    }
    Matrix res(m1.nrow(), m2.ncol());
    for(size_t i = 0; i < m1.nrow(); ++i)
    {
        for(size_t j = 0; j < m2.ncol(); ++j)
        {
            double element = 0;
            for(size_t k = 0; k < m1.ncol(); ++k)
            {
                element += m1(i, k) * m2(k, j);
            }
            res(i, j) = element;
        }
    }
    return res;
}

Matrix multiply_tile(Matrix const & m1, Matrix const & m2, size_t t)
{
    if(m1.ncol() != m2.nrow())
    {
        throw std::invalid_argument("wrong dimension");
    }
    Matrix res(m1.nrow(), m2.ncol());
    for(size_t i = 0; i < m1.nrow(); i += t)
    {
        for(size_t j = 0; j < m2.ncol(); j += t)
        {
            for(size_t k = 0; k < m1.ncol(); k += t)
            {
                for(size_t it = i; it < std::min(m1.nrow(), i + t); ++it)
                {
                    for(size_t jt = j; jt < std::min(m2.ncol(), j + t); ++jt)
                    {
                        double element = 0.0;
                        for(size_t kt = k; kt < std::min(m1.ncol(), k + t); ++kt)
                        {
                            element += m1(it, kt) * m2(kt, jt);
                        }
                        res(it, jt) += element;
                    }
                }
            }
        }
    }
    return res;
}

Matrix multiply_mkl(Matrix const & m1, Matrix const & m2)
{
    if(m1.ncol()!=m2.nrow())
    {
        throw std::invalid_argument("wrong dimension");
    }
    Matrix res(m1.nrow(), m2.ncol());
    size_t m = m1.nrow();
    size_t n = m2.ncol();
    size_t k = m1.ncol();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, 1.0, m1.buf_get(), k, m2.buf_get(), n, 1.0, res.buf_get(), n);
    return res;
}