#include "matrix.hpp"

matrix_2d::matrix_2d(size_t nrow, size_t ncol)
  : m_nrow(nrow), m_ncol(ncol) {
    size_t nelement = nrow * ncol;
    m_buffer = new double[nelement];
};

matrix_2d::~matrix_2d() {
    delete[] m_buffer;
};

double   matrix_2d::operator() (size_t row, size_t col) const {
    return m_buffer[row*m_ncol + col];
}
double & matrix_2d::operator() (size_t row, size_t col) {
    return m_buffer[row*m_ncol + col];
}

matrix_2d & matrix_2d::transpose() {
    m_transpose = !m_transpose;
    std::swap(m_nrow, m_ncol);
    return *this;
}

size_t matrix_2d::index(size_t row, size_t col) const {
    // m_nrow and m_ncol are swapped if the matrix is transposed
    // specify row in transposed matrix is the same as specify col in original one
    // so this code will direct to the same element in m_buffer
    if (m_transpose) { return col * m_nrow + row; }
    else             { return row * m_ncol + col; }
}
bool matrix_2d::is_transposed() const { return m_transpose; }

size_t matrix_2d::get_nrow() const { return m_nrow; };
size_t matrix_2d::get_ncol() const { return m_ncol; };
