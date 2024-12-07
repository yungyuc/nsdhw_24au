#include <iostream>
#include <iomanip>
#include <atomic>
#include <vector>
#include <stdexcept>
#include <limits>
#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>


namespace py = pybind11;

class Matrix {

private:
    /* Member variable */
    size_t m_nrow = 0;
    size_t m_ncol = 0;
    std::vector<double> m_data = std::vector<double>();

public:
    Matrix(size_t num_row, size_t num_col);
    Matrix(size_t num_row, size_t num_col, std::vector<double> const & vec);

    Matrix & operator=(std::vector<double> const & vec);
    bool operator==(const Matrix &m) const;

    /* copy constructor */
    Matrix(Matrix const & other);

    /* copy assignment operator */
    Matrix & operator=(Matrix const & other);

    /* move constructor */
    Matrix(Matrix && other);

    /* move assignment operator */
    Matrix & operator=(Matrix && other);

    /* Destructor */
    ~Matrix();

    size_t nrow() const;
    size_t ncol() const;
    const double* data() const;
    double* data();

    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);

    py::array_t<double> to_numpy() const;

    // void reset_buffer(size_t nrow, size_t ncol);

};

std::ostream & operator << (std::ostream & ostr, Matrix const & mat);

/* Naive matrix matrix multiplication */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2);

/* Matrix matrix multiplication using tiling */
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t tile_size);


/* Matrix matrix multiplication using DGEMM */
Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2);