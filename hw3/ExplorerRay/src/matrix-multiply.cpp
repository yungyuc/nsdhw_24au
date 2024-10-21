#include "matrix-multiply.hpp"
#include <stdexcept>

#ifdef UBUNTU
#include <mkl/mkl.h>
#else
#include <mkl.h>
#endif

template<size_t N>
struct Block
{
    static constexpr const size_t NDIM = N;

    double   operator[] (size_t idx) const { return m_buffer[idx]; }
    double & operator[] (size_t idx)       { return m_buffer[idx]; }

    Block<N> & operator= (double v)
    {
        for (size_t i=0; i<N*N; ++i) { m_buffer[i] = v; }
        return *this;
    }

    Block<N> & operator+= (Block<N> const & other)
    {
        for (size_t i=0; i<N*N; ++i) { m_buffer[i] += other.m_buffer[i]; }
        return *this;
    }

    void save(matrix_2d & mat, size_t it, size_t jt);

    double m_buffer[N * N];
};

template<size_t N> void Block<N>::save(
    matrix_2d & mat, size_t it, size_t jt
)
{
    const size_t ncol = mat.get_ncol();

    for (size_t i=0; i<NDIM; ++i)
    {
        const size_t base_s = i*NDIM;
        const size_t base_t = (it*NDIM + i) * ncol + jt*NDIM;

        for (size_t j=0; j<NDIM; ++j)
        {
            mat.m_buffer[base_t + j] = m_buffer[base_s + j];
        }
    }
}

template<size_t N>
struct Tiler
{
    static constexpr const size_t NDIM = N;

    void load(
        matrix_2d const & mat1, size_t it1, size_t jt1
      , matrix_2d const & mat2, size_t it2, size_t jt2
    );

    void multiply();

    Block<N> m_mat1; // row-major
    Block<N> m_mat2; // column-major
    Block<N> m_ret; // row-major
};

template<size_t N> void Tiler<N>::load(
    matrix_2d const & mat1, size_t it1, size_t jt1
  , matrix_2d const & mat2, size_t it2, size_t jt2
)
{
    const size_t ncol1 = mat1.get_ncol();

    for (size_t i=0; i<NDIM; ++i)
    {
        const size_t base_t = i*NDIM;
        const size_t base_s = (it1*NDIM + i) * ncol1 + jt1*NDIM;

        for (size_t j=0; j<NDIM; ++j)
        {
            m_mat1[base_t + j] = mat1.m_buffer[base_s + j];
        }
    }

    const size_t ncol2 = mat2.get_ncol();

    for (size_t i=0; i<NDIM; ++i)
    {
        const size_t base_t = i*NDIM;
        const size_t base_s = (it2*NDIM + i) * ncol2 + jt2*NDIM;

        for (size_t j=0; j<NDIM; ++j)
        {
            m_ret[base_t + j] = mat2.m_buffer[base_s + j];
        }
    }

    for (size_t i=0; i<NDIM; ++i)
    {
        const size_t base = i*NDIM;

        for (size_t j=0; j<NDIM; ++j)
        {
            m_mat2[j*NDIM + i] = m_ret[base + j];
        }
    }
}

template<size_t N> void Tiler<N>::multiply()
{
    for (size_t i=0; i<NDIM; ++i)
    {
        const size_t base1 = i*NDIM;

        for (size_t k=0; k<NDIM; ++k)
        {
            const size_t base2 = k*NDIM;

            double v = 0;
            for (size_t j=0; j<NDIM; ++j)
            {
                v += m_mat1[base1 + j] * m_mat2[base2 + j];
            }
            m_ret[base1 + k] = v;
        }
    }
}

matrix_2d multiply_naive(matrix_2d const &A, matrix_2d const &B) {
    if (A.get_ncol() != B.get_nrow()) {
        throw std::out_of_range("Matrix dimensions do not match");
    }

    auto row_iter = A.get_nrow();
    auto col_iter = B.get_ncol();
    auto inner_iter = A.get_ncol();
    matrix_2d C(row_iter, col_iter);
    for (size_t i = 0; i < row_iter; ++i) {
        for (size_t j = 0; j < col_iter; ++j) {
            double sum = 0;
            for (size_t k = 0; k < inner_iter; ++k) {
                sum += A(i, k) * B(k, j);
            }
            C(i, j) = sum;
        }
    }
    return C;
}

matrix_2d multiply_tile(matrix_2d const &A, matrix_2d const &B, size_t tsize){
    if (A.get_ncol() != B.get_nrow()) {
        throw std::out_of_range("Matrix dimensions do not match");
    }

    (void)tsize;

    const size_t row_iter = A.get_nrow();
    const size_t col_iter = B.get_ncol();
    const size_t inner_iter = A.get_ncol();

    matrix_2d C(row_iter, col_iter);

    const size_t ntrow1 = row_iter / 10;
    const size_t ntcol1 = col_iter / 10;
    const size_t ntcol2 = inner_iter / 10;

    Block<10> value;
    Tiler<10> tiler;

    for (size_t it=0; it<ntrow1; ++it){
        for (size_t kt=0; kt<ntcol2; ++kt) {
            value = 0;
            for (size_t jt=0; jt<ntcol1; ++jt)
{
                tiler.load(A, it, jt, B, jt, kt);
                tiler.multiply();
                value += tiler.m_ret;
            }
            value.save(C, it, kt);
        }
    }
    
    return C;
}

matrix_2d multiply_mkl(matrix_2d const &A, matrix_2d const &B){
    if (A.get_ncol() != B.get_nrow()) {
        throw std::out_of_range("Matrix dimensions do not match");
    }

    matrix_2d C(A.get_nrow(), B.get_ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                A.get_nrow(), B.get_ncol(), A.get_ncol(), 
                1.0, A.get_buffer(), A.get_ncol(), 
                B.get_buffer(), B.get_ncol(), 
                0.0, C.get_buffer(), C.get_ncol());
    return C;
}
