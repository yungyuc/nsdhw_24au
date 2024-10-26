#include "_matrix.hpp"

Matrix::Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol) {
    if (nrow <= 0 || ncol <= 0) {
        throw "Invalid matrix size";
    }
    data = new double[nrow * ncol];
    for (size_t i = 0; i < nrow * ncol; i++) {
        data[i] = 0;
    }
}

Matrix::Matrix(size_t nrow, size_t ncol, double init) : m_nrow(nrow), m_ncol(ncol) {
    if (nrow <= 0 || ncol <= 0) {
        throw "Invalid matrix size";
    }
    data = new double[nrow * ncol];
    for (size_t i = 0; i < nrow * ncol; i++) {
        data[i] = init;
    }
}

Matrix::Matrix(size_t nrow, size_t ncol, vector<double> &init) : m_nrow(nrow), m_ncol(ncol) {
    if (nrow <= 0 || ncol <= 0) {
        throw "Invalid matrix size";
    }
    data = new double[nrow * ncol];
    for (size_t i = 0; i < nrow * ncol; i++) {
        data[i] = init[i];
    }
}

Matrix::Matrix(const Matrix &m) : m_nrow(m.nrow()), m_ncol(m.ncol()) {
    data = new double[m_nrow * m_ncol];
    for (size_t i = 0; i < m_nrow * m_ncol; i++) {
        data[i] = m.data[i];
    }
}

Matrix::~Matrix() {
    delete[] data;
}

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
    return data;
}

vector<double> Matrix::getVector() const {
    vector<double> v(data, data + m_nrow * m_ncol);
    return v;
}

double Matrix::operator()(size_t i, size_t j) const {
    if (i >= m_nrow || j >= m_ncol || i < 0 || j < 0) {
        throw "Index out of range";
    }
    return data[index(i, j)];
}

double& Matrix::operator()(size_t i, size_t j) {
    if (i >= m_nrow || j >= m_ncol || i < 0 || j < 0) {
        throw "Index out of range";
    }
    return data[index(i, j)];
}

bool Matrix::operator==(const Matrix &m) const {
    if (m_nrow != m.nrow() || m_ncol != m.ncol()) {
        return false;
    }
    for (size_t i = 0; i < m_nrow * m_ncol; i++) {
        if (data[i] != m.data[i]) {
            return false;
        }
    }
    return true;
}