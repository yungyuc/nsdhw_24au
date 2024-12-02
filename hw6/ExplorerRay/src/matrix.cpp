#include "matrix.hpp"

matrix_2d::matrix_2d(size_t nrow, size_t ncol)
  : m_nrow(nrow), m_ncol(ncol) {
    if (nrow <= 0 || ncol <= 0) {
        throw std::invalid_argument("matrix_2d: nrow and ncol must be positive");
    }

    size_t nelement = nrow * ncol;
    m_buffer.resize(nelement);
};

// matrix_2d::~matrix_2d() {
//     delete[] m_buffer;
// };

double   matrix_2d::operator() (size_t row, size_t col) const {
    return m_buffer[index(row, col)];
}
double & matrix_2d::operator() (size_t row, size_t col) {
    return m_buffer[index(row, col)];
}

bool matrix_2d::operator==(matrix_2d const &m) const {
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

matrix_2d & matrix_2d::transpose() {
    m_transpose = !m_transpose;
    std::swap(m_nrow, m_ncol);
    return *this;
}

size_t matrix_2d::index(size_t row, size_t col) const {
    if (row >= m_nrow || col >= m_ncol) {
        throw std::out_of_range("matrix_2d: index out of range");
    }

    // m_nrow and m_ncol are swapped if the matrix is transposed
    // specify row in transposed matrix is the same as specify col in original one
    // so this code will direct to the same element in m_buffer
    if (m_transpose) { return col * m_nrow + row; }
    else             { return row * m_ncol + col; }
}
bool matrix_2d::is_transposed() const { return m_transpose; }

size_t matrix_2d::get_nrow() const { return m_nrow; };
size_t matrix_2d::get_ncol() const { return m_ncol; };
const double* matrix_2d::get_buffer() const { return m_buffer.data(); };
