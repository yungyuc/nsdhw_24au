#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <mkl.h>

class Matrix {

public:

    Matrix(size_t nrow, size_t ncol);
    Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec);

    Matrix & operator=(std::vector<double> const & vec);

    /* copy constructor */
    Matrix(Matrix const & other);

    /* copy assignment operator */
    Matrix & operator=(Matrix const & other);

    /* move constructor */
    Matrix(Matrix && other);

    /* move assignment operator */
    Matrix & operator=(Matrix && other);

    /* Matrix addition */
    Matrix operator+(Matrix const & other);

    ~Matrix();

    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);

    size_t nrow() const;
    size_t ncol() const;

    size_t size() const;
    double buffer(size_t i) const;
    std::vector<double> buffer_vector() const;
    double * getBuffer() const;


private:

    size_t index(size_t row, size_t col) const;
    void reset_buffer(size_t nrow, size_t ncol);
    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double * m_buffer = nullptr;
};


std::ostream & operator << (std::ostream & ostr, Matrix const & mat);


/* Naive matrix matrix multiplication */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2);

/* Matrix matrix multiplication using tiling */
Matrix multiple_tile(Matrix const & mat1, Matrix const & mat2);


/* Matrix matrix multiplication using DGEMM */
Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2);
