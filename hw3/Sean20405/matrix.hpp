#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <mkl.h>

class Matrix {

public:
    /* Member variable */
    size_t nrow = 0;
    size_t ncol = 0;
    std::vector<double> data;

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

    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);
};


std::ostream & operator << (std::ostream & ostr, Matrix const & mat);


/* Naive matrix matrix multiplication */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2);

/* Matrix matrix multiplication using tiling */
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, int tile_size);


/* Matrix matrix multiplication using DGEMM */
Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2);