#pragma once

#include "matrix.hpp"

matrix_2d multiply_naive(
    matrix_2d const &A, matrix_2d const &B
);

matrix_2d multiply_tile(
    matrix_2d const &A, matrix_2d const &B, size_t tsize
);

matrix_2d multiply_mkl(
    matrix_2d const &A, matrix_2d const &B
);
