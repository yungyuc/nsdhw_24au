#pragma once

#include "matrix.hpp"

Matrix multiply_naive(
    Matrix const &A, Matrix const &B
);

Matrix multiply_tile(
    Matrix const &A, Matrix const &B, size_t tsize
);

Matrix multiply_mkl(
    Matrix const &A, Matrix const &B
);
