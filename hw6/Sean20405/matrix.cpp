#include "matrix.hpp"

/* Matrix */
Matrix::Matrix(size_t num_row, size_t num_col) : m_nrow(num_row), m_ncol(num_col) {
    m_data = std::vector<double>(num_row * num_col, 0);
}

Matrix::Matrix(size_t num_row, size_t num_col, std::vector<double> const & vec) : m_nrow(num_row), m_ncol(num_col) {
    m_data = std::vector<double>(num_row * num_col, 0);
}

Matrix & Matrix::operator=(std::vector<double> const & vec) {
    if (m_data.size() != vec.size()) {
        throw std::out_of_range("number of elements mismatch");
    }

    size_t k = 0;
    for (size_t i=0; i<m_nrow; ++i) {
        for (size_t j=0; j<m_ncol; ++j) {
            (*this)(i, j) = vec[k];
            ++k;
        }
    }

    return *this;
}

bool Matrix::operator==(const Matrix &m) const {
    if (m_nrow != m.m_nrow || m_ncol != m.m_ncol) {
        return false;
    }

    for (size_t i=0; i<m_nrow; ++i) {
        for (size_t j=0; j<m_ncol; ++j) {
            if ((*this)(i, j) != m(i, j)) {
                return false;
            }
        }
    }

    return true;
}

/* copy constructor */
Matrix::Matrix(Matrix const & other) : m_nrow(other.m_nrow), m_ncol(other.m_ncol) {
    m_data = other.m_data;
}

/* copy assignment operator */
Matrix & Matrix::operator=(Matrix const & other) {
    if (this == &other) { return *this; }
    
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
    }

    m_data = other.m_data;

    return *this;
}

/* move constructor */
Matrix::Matrix(Matrix && other) : m_nrow(other.m_nrow), m_ncol(other.m_ncol) {    
    std::swap(m_nrow, other.m_nrow);
    std::swap(m_ncol, other.m_ncol);
    m_data.swap(other.m_data);
}

/* move assignment operator */
Matrix & Matrix::operator=(Matrix && other) {
    if (this == &other) { return *this; }
    std::swap(m_nrow, other.m_nrow);
    std::swap(m_ncol, other.m_ncol);
    m_data.swap(other.m_data);
    return *this;
}

Matrix::~Matrix() {
    m_data.clear();
    m_nrow = 0;
    m_ncol = 0;
}

size_t Matrix::nrow() const { return m_nrow; }
size_t Matrix::ncol() const { return m_ncol; }
const double* Matrix::data() const { return m_data.data(); }
double* Matrix::data() { return m_data.data(); }

double   Matrix::operator() (size_t row, size_t col) const { return m_data[m_ncol * row + col]; }
double & Matrix::operator() (size_t row, size_t col)       { return m_data[m_ncol * row + col]; }

py::array_t<double> Matrix::to_numpy() const {
    return py::array_t<double>(
        {m_nrow, m_ncol},  // shape
        {m_ncol * sizeof(double), sizeof(double)},  // C-style contiguous strides for double
        m_data.data(),  // the pointer to the data
        py::cast(this)  // parent
    );
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
            for (size_t j=0; j<mat1.ncol(); ++j) {
                ret(i, k) += mat1(i, j) * mat2(j, k);
            }
        }
    }

    return ret;
}

/* Matrix matrix multiplication using tiling */
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t tile_size) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    size_t mat1_nrow = mat1.nrow();
    size_t mat1_ncol = mat1.ncol();
    size_t mat2_ncol = mat2.ncol();

    Matrix ret(mat1_nrow, mat2_ncol);

    for (size_t tile_i=0; tile_i<mat1_nrow; tile_i+=tile_size) {
        for (size_t tile_k=0; tile_k<mat2_ncol; tile_k+=tile_size) {
            for (size_t tile_j=0; tile_j<mat1_ncol; tile_j+=tile_size) {
                size_t tile_i_end = std::min(tile_i + tile_size, mat1_nrow);
                size_t tile_k_end = std::min(tile_k + tile_size, mat2_ncol);
                size_t tile_j_end = std::min(tile_j + tile_size, mat1_ncol);

                for (size_t i=tile_i; i<tile_i_end; ++i) {
                    for (size_t k=tile_k; k<tile_k_end; ++k) {
                        double tmp = mat1(i, k);
                        for (size_t j=tile_j; j<tile_j_end; ++j) {
                            ret(i, j) += tmp * mat2(k, j);
                        }
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
      , mat1.data()  // const double *A
      , mat1.ncol()       // The size of the first dimension of matrix A
      , mat2.data()  // const double *B
      , mat2.ncol()       // The size of the first dimension of matrix B
      , 0.0               // const double beta
      , ret.data()   // double *C
      , ret.ncol()        // The size of the first dimension of matrix C
    );

    return ret;
}
/* End Matrix related function */


PYBIND11_MODULE(_matrix, m) {
    m.doc() = "Multiplication module for matrices."; // optional module docstring

    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def(py::init<size_t, size_t, std::vector<double>>())
        .def("__repr__", [](Matrix const & mat) {
            return "Matrix(" + std::to_string(mat.nrow()) + ", " + std::to_string(mat.ncol()) + ")";
        })
        .def("__call__", (double (Matrix::*)(size_t, size_t) const) &Matrix::operator())
        .def("__call__", (double& (Matrix::*)(size_t, size_t)) &Matrix::operator())
        .def("__getitem__", [](const Matrix &m, std::pair<size_t, size_t> i) {
            return m(i.first, i.second);
        })
        .def("__setitem__", [](Matrix &m, std::pair<size_t, size_t> i, double val) {
            m(i.first, i.second) = val;
        })
        .def("__eq__", &Matrix::operator==)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def_property("array", &Matrix::to_numpy, nullptr);

    m.def("multiply_naive", &multiply_naive, "Matirx multiplication by the naive approach.");
    m.def("multiply_tile", &multiply_tile, "Matirx multiplication leveraging tiling.");
    m.def("multiply_mkl", &multiply_mkl, "Matirx multiplication using the MKL");
}