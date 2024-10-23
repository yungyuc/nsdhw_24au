#include "matrix.hpp"

Matrix::Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol) {
    reset_buffer(nrow, ncol);
}

Matrix::Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec) : m_nrow(nrow), m_ncol(ncol) {
    reset_buffer(nrow, ncol);
    (*this) = vec;
}

Matrix & Matrix::operator=(std::vector<double> const & vec) {
    if (size() != vec.size()) {
        throw std::out_of_range("number of elements mismatch");
    }

    size_t k = 0;
    for (size_t i=0; i<m_nrow; ++i) {
        for (size_t j=0; j<m_ncol; ++j) {
            (*this)(i,j) = vec[k];
            ++k;
        }
    }

    return *this;
}

/* copy constructor */
Matrix::Matrix(Matrix const & other) : m_nrow(other.m_nrow), m_ncol(other.m_ncol) {
    reset_buffer(other.m_nrow, other.m_ncol);
    
    for (size_t i=0; i<m_nrow; ++i) {
        for (size_t j=0; j<m_ncol; ++j) {
            (*this)(i,j) = other(i,j);
        }
    }
}

/* copy assignment operator */
Matrix & Matrix::operator=(Matrix const & other) {
    if (this == &other) { return *this; }
    
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
        reset_buffer(other.m_nrow, other.m_ncol);
    }

    for (size_t i=0; i<m_nrow; ++i) {
        for (size_t j=0; j<m_ncol; ++j) {
            (*this)(i,j) = other(i,j);
        }
    }

    return *this;
}

/* move constructor */
Matrix::Matrix(Matrix && other) : m_nrow(other.m_nrow), m_ncol(other.m_ncol) {
    reset_buffer(0, 0);
    std::swap(m_nrow, other.m_nrow);
    std::swap(m_ncol, other.m_ncol);
    std::swap(m_buffer, other.m_buffer);
}

/* move assignment operator */
Matrix & Matrix::operator=(Matrix && other) {
    if (this == &other) { return *this; }
    reset_buffer(0, 0);
    std::swap(m_nrow, other.m_nrow);
    std::swap(m_ncol, other.m_ncol);
    std::swap(m_buffer, other.m_buffer);
    return *this;
}

/* Matrix addition */
Matrix Matrix::operator+(Matrix const & other) {
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(m_nrow, m_ncol);
    for (size_t i=0; i<m_nrow; ++i) {
        for (size_t j=0; j<m_ncol; ++j) {
            ret(i, j) = (*this)(i,j) + other(i,j);
        }
    }

    return ret;
}

Matrix::~Matrix() {
    reset_buffer(0, 0);
}

double   Matrix::operator() (size_t row, size_t col) const {
    return m_buffer[index(row, col)];
}
double & Matrix::operator() (size_t row, size_t col) {
    return m_buffer[index(row, col)];
}

size_t Matrix::nrow() const { return m_nrow; }
size_t Matrix::ncol() const { return m_ncol; }

size_t Matrix::size() const { return m_nrow * m_ncol; }
double Matrix::buffer(size_t i) const { return m_buffer[i]; }
std::vector<double> Matrix::buffer_vector() const {
    return std::vector<double>(m_buffer, m_buffer+size());
}
double * Matrix::getBuffer() const { return m_buffer; }

size_t Matrix::index(size_t row, size_t col) const {
    return row + col * m_nrow;
}

void Matrix::reset_buffer(size_t nrow, size_t ncol) {
    if (m_buffer) { delete[] m_buffer; }
    const size_t nelement = nrow * ncol;
    if (nelement) { m_buffer = new double[nelement]; }
    else          { m_buffer = nullptr; }
    m_nrow = nrow;
    m_ncol = ncol;
}

std::ostream & operator << (std::ostream & ostr, Matrix const & mat) {
    for (size_t i=0; i<mat.nrow(); ++i) {
        ostr << std::endl << " ";
        for (size_t j=0; j<mat.ncol(); ++j) {
            ostr << " " << std::setw(2) << mat(i, j);
        }
    }

    return ostr;
}


/* Naive matrix matrix multiplication */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i=0; i<mat1.nrow(); ++i) {
        for (size_t k=0; k<mat2.ncol(); ++k) {
            double v = 0;
            for (size_t j=0; j<mat1.ncol(); ++j) {
                v += mat1(i,j) * mat2(j,k);
            }
            ret(i,k) = v;
        }
    }

    return ret;
}

/* Matrix matrix multiplication using tiling */
Matrix multiple_tile(Matrix const & mat1, Matrix const & mat2, int tile_size) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (int tile_i=0; tile_i<mat1.nrow(); tile_i+=tile_size) {
        for (int tile_k=0; tile_k<mat2.ncol(); tile_k+=tile_size) {
            for (int tile_j=0; tile_j<mat1.ncol(); tile_j+=tile_size) {
                for (int i=tile_i; i<tile_i+tile_size; ++i) {
                    for (int k=tile_k; k<tile_k+tile_size; ++k) {
                        double v = 0;
                        for (int j=tile_j; j<tile_j+tile_size; ++j) {
                            v += mat1(i,j) * mat2(j,k);
                        }
                        ret(i,k) += v;
                    }
                }
            }
        }
    }

    return ret;
}


/* Matrix matrix multiplication using DGEMM */
Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor     // const CBLAS_LAYOUT Layout
      , CblasNoTrans      // const CBLAS_TRANSPOSE transa
      , CblasNoTrans      // const CBLAS_TRANSPOSE transb
      , mat1.nrow()       // const MKL_INT m
      , mat2.ncol()       // const MKL_INT n
      , mat1.ncol()       // const MKL_INT k
      , 1.0               // const double alpha
      , mat1.getBuffer()  // const double *A
      , mat1.ncol()       // The size of the first dimension of matrix A
      , mat2.getBuffer()  // const double *B
      , mat2.ncol()       // The size of the first dimension of matrix B
      , 0.0               // const double beta
      , ret.getBuffer()   // double *C
      , ret.ncol()        // The size of the first dimension of matrix C
    );

    return ret;
}
