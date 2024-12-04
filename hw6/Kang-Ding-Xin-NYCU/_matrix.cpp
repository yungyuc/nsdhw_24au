#include <atomic>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <mkl.h>

template <class T>
class CustomAllocator
{
public:
    using value_type = T;
    CustomAllocator() = default;

    template <class U> 
    CustomAllocator(const CustomAllocator<U> & other) noexcept
    {
        m_current = other.bytes();
        m_allocated = other.allocated();
        m_deallocated = other.deallocated();
    }

    T * allocate(std::size_t n)
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
            throw std::bad_alloc();

        const std::size_t bytes = n*sizeof(T);
        T * p = static_cast<T *>(std::malloc(bytes));
        if(p)
        { 
            m_current += bytes;
            m_allocated += bytes;
        }
        else
        {
            throw std::bad_alloc();
        }
        return p;
    }

    void deallocate(T* p, std::size_t n) noexcept
    {
        std::free(p);
        const std::size_t bytes = n*sizeof(T);
        m_current -= bytes;
        m_deallocated += bytes;
    }

    static void reset_memory_tracking()
    {
        m_allocated = 0;
        m_deallocated = 0;
    }


    static std::size_t bytes() { return m_current; }
    static std::size_t allocated() { return m_allocated; }
    static std::size_t deallocated() { return m_deallocated; }

private:

    static std::size_t m_current;
    static std::size_t m_allocated;
    static std::size_t m_deallocated;

};

template <class T> std::size_t CustomAllocator<T>::m_current = 0;
template <class T> std::size_t CustomAllocator<T>::m_allocated = 0;
template <class T> std::size_t CustomAllocator<T>::m_deallocated = 0;

template <class T, class U>
bool operator==(const CustomAllocator<T> & a, const CustomAllocator<U> & b)
{
    if (a.bytes() != b.bytes()) { return false; }
    if (a.allocated() != b.allocated()) { return false; }
    if (a.deallocated() != b.deallocated()) { return false; }
    return true;
}

template <class T, class U>
bool operator!=(const CustomAllocator<T> & a, const CustomAllocator<U> & b)
{
    return !(a == b);
}

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

    Matrix(Matrix && other): m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
    }

    ~Matrix()
    {
        reset_buffer(0, 0);
    }

    double operator() (size_t row, size_t col) const
    {
        return m_buffer[index(row, col)];
    }

    double & operator() (size_t row, size_t col)
    {
        return m_buffer[index(row, col)];
    }

    bool operator==(Matrix const & other)
    {
        if ((this->m_nrow != other.nrow()) || (this->m_ncol != other.ncol()))
        {
            return false;
        }
        for(size_t i = 0; i < other.nrow(); i++)
        {
            for(size_t j = 0; j < other.ncol(); j++)
            {
                if(this->m_buffer[index(i, j)] != other(i, j))
                {
                    return false;
                }
            }
        }
        return true;
    }

    double* buf_get() const 
    {
        return (double *)m_buffer.data();
    }

    void buf_set(std::vector<double> &data) 
    { 
        for(size_t i = 0; i < m_nrow*m_ncol; ++i)
        {
            m_buffer[i] = data[i];
        }
    }

    size_t nrow() const {return m_nrow;}
    size_t ncol() const {return m_ncol;}
    size_t size() const {return m_nrow * m_ncol;}
    

private:

    size_t index(size_t row, size_t col) const
    {
        return row * m_ncol + col;
    }

    void reset_buffer(size_t nrow, size_t ncol)
    {
        m_buffer.clear();
        const size_t nelement = nrow * ncol;
        m_buffer.resize(nelement);
        for (size_t i=0; i<nelement; ++i)
            m_buffer[i] = 0;
        m_nrow = nrow;
        m_ncol = ncol;
    }
    size_t m_nrow;
    size_t m_ncol;
    std::vector<double, CustomAllocator<double>> m_buffer;
};

Matrix multiply_naive(Matrix const & m1, Matrix const & m2)
{
    if(m1.ncol()!=m2.nrow())
    {
        throw std::invalid_argument("wrong dimention");
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
    if(m1.ncol()!=m2.nrow())
    {
        throw std::invalid_argument("wrong dimention");
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
                        for(size_t kt = k; kt < std::min(m1.ncol(), k + t); ++kt)
                        {
                            res(it, jt) += m1(it, kt) * m2(kt, jt);
                        }
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

PYBIND11_MODULE(_matrix, m)
{
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
        .def_property("nrow", &Matrix::nrow, nullptr)
        .def_property("ncol", &Matrix::ncol, nullptr)
        .def_property("size", &Matrix::size, nullptr)
        .def_property("array", [](Matrix &array)
        {
            return pybind11::array_t<double>
            (
                {array.nrow(), array.ncol()},
                array.buf_get(),
                pybind11::cast(array)
            );
        },
        nullptr);
    m.def("bytes", &CustomAllocator<double>::bytes);
    m.def("allocated", &CustomAllocator<double>::allocated);
    m.def("deallocated", &CustomAllocator<double>::deallocated);
}