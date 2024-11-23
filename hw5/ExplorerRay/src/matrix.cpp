#include "matrix.hpp"

Matrix::Matrix(size_t m_nrow, size_t m_ncol)
  : m_nrow(m_nrow), m_ncol(m_ncol) {
    if (m_nrow <= 0 || m_ncol <= 0) {
        throw std::invalid_argument("Matrix: m_nrow and m_ncol must be positive");
    }

    size_t nelement = m_nrow * m_ncol;
    m_buffer.resize(nelement);
};

// Matrix::~Matrix() {
//     delete[] m_buffer;
// };

double   Matrix::operator() (size_t row, size_t col) const {
    return m_buffer[index(row, col)];
}
double & Matrix::operator() (size_t row, size_t col) {
    return m_buffer[index(row, col)];
}

bool Matrix::operator==(Matrix const &m) const {
    if (m_nrow != m.m_nrow || m_ncol != m.m_ncol) {
        return false;
    }

    for (size_t i = 0; i < m_nrow; i++) {
        for (size_t j = 0; j < m_ncol; j++) {
            if ((*this)(i, j) != m(i, j)) {
                return false;
            }
        }
    }

    return true;
}

Matrix & Matrix::transpose() {
    m_transpose = !m_transpose;
    std::swap(m_nrow, m_ncol);
    return *this;
}

size_t Matrix::index(size_t row, size_t col) const {
    if (row >= m_nrow || col >= m_ncol) {
        throw std::out_of_range("Matrix: index out of range");
    }

    // m_nrow and m_ncol are swapped if the matrix is transposed
    // specify row in transposed matrix is the same as specify col in original one
    // so this code will direct to the same element in m_buffer
    if (m_transpose) { return col * m_nrow + row; }
    else             { return row * m_ncol + col; }
}
bool Matrix::is_transposed() const { return m_transpose; }

size_t Matrix::get_nrow() const { return m_nrow; };
size_t Matrix::get_ncol() const { return m_ncol; };
size_t Matrix::nrow() const { return m_nrow; };
size_t Matrix::ncol() const { return m_ncol; };
const double* Matrix::get_buffer() const { return m_buffer.data(); };
