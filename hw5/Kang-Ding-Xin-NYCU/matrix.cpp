#include "matrix.hpp"

Matrix::Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol)
{
    reset_buffer(nrow, ncol);
}

Matrix::Matrix(Matrix const & other) : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
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

double Matrix::operator() (size_t row, size_t col) const
{
    return m_buffer[index(row, col)];
}

double & Matrix::operator() (size_t row, size_t col)
{
    return m_buffer[index(row, col)];
}

bool Matrix::operator==(Matrix const & other) const
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

double* Matrix::buf_get() const 
{ 
    return m_buffer;
}

void Matrix::buf_set(std::vector<double> &data) 
{ 
    for(size_t i = 0; i < m_nrow*m_ncol; i++)
    {
        m_buffer[i] = data[i];
    }
}

size_t Matrix::nrow() const { return m_nrow; }
size_t Matrix::ncol() const { return m_ncol; }
size_t Matrix::size() const { return m_nrow * m_ncol; }

void Matrix::printm(){
    std::cout << m_nrow << " " << m_ncol << "\n";
    for(size_t i = 0; i < m_nrow; ++i){
        for(size_t j = 0; j < m_ncol; ++j){
            std::cout << m_buffer[index(i, j)] << " ";
        }
        std::cout << "\n";
    }
}

size_t Matrix::index(size_t row, size_t col) const
{
    return row * m_ncol + col;
}

void Matrix::reset_buffer(size_t nrow, size_t ncol)
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

Matrix multiply_naive(Matrix const & m1, Matrix const & m2){
    if(m1.ncol()!=m2.nrow()){
        throw std::invalid_argument("wrong dimension");
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
    if(m1.ncol() != m2.nrow()){
        throw std::invalid_argument("wrong dimension");
    }
    Matrix res(m1.nrow(), m2.ncol());
    for(size_t i = 0; i < m1.nrow(); i += t){
        for(size_t j = 0; j < m2.ncol(); j += t){
            for(size_t k = 0; k < m1.ncol(); k += t){
                for(size_t it = i; it < std::min(m1.nrow(), i + t); ++it){
                    for(size_t jt = j; jt < std::min(m2.ncol(), j + t); ++jt){
                        double sum = 0.0;
                        for(size_t kt = k; kt < std::min(m1.ncol(), k + t); ++kt){
                            sum += m1(it, kt) * m2(kt, jt);
                        }
                        res(it, jt) += sum;
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