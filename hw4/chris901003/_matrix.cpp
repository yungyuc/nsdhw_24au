#include "_matrix.hpp"

Matrix::Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol), m_buffer(nrow * ncol, 0.0) {
}

Matrix::Matrix(size_t nrow, size_t ncol, double init) : m_nrow(nrow), m_ncol(ncol) {
}

Matrix::Matrix(size_t nrow, size_t ncol, vector<double, CustomAllocator<double>> &init) : m_nrow(nrow), m_ncol(ncol), m_buffer(init) {
}

Matrix::Matrix(Matrix && other) 
    : m_nrow(std::move(other.m_nrow)), m_ncol(std::move(other.m_ncol)), m_buffer(std::move(other.m_buffer)) {
    other.m_nrow = 0;
    other.m_ncol = 0;
}

Matrix::~Matrix() = default;

size_t Matrix::nrow() const {
    return m_nrow;
}

size_t Matrix::ncol() const {
    return m_ncol;
}

size_t Matrix::index(size_t i, size_t j) const {
    if (i >= m_nrow || j >= m_ncol || i < 0 || j < 0) {
        throw "Index out of range";
    }
    return i * m_ncol + j;
}

double* Matrix::getData() const {
    double* d = const_cast<double*>(m_buffer.data());
    return d;
}

double* Matrix::buffer()
{ 
    return m_buffer.data();
}

const double* Matrix::buffer() const
{ 
    return m_buffer.data();
}

double Matrix::operator() (size_t row, size_t col) const
{
    return m_buffer[row * m_ncol + col];
}

double& Matrix::operator() (size_t row, size_t col)
{
    return m_buffer[row * m_ncol + col];
}

bool Matrix::operator==(const Matrix& other) const {
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
        return false;
    }
    for (size_t i = 0; i < m_nrow; i++) {
        for (size_t j = 0; j < m_ncol; j++) {
            if (m_buffer[i*m_ncol+j] != other.m_buffer[i*m_ncol+j]){
                return false;
            }
        }
    }
    return true;
}