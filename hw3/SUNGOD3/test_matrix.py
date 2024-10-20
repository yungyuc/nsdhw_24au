import pytest
import _matrix

def test_matrix_creation():
    mat = _matrix.Matrix(3, 3)
    assert mat.nrow == 3
    assert mat.ncol == 3

def test_matrix_multiplication():
    A = _matrix.Matrix(2, 2)
    B = _matrix.Matrix(2, 2)
    for i in range(2):
        for j in range(2):
            A[i, j] = i * 2 + j + 1
            B[i, j] = i * 2 + j + 1

    C_naive = _matrix.multiply_naive(A, B)
    C_tile = _matrix.multiply_tile(A, B, 1)
    C_mkl = _matrix.multiply_mkl(A, B)

    for i in range(2):
        for j in range(2):
            assert C_naive[i, j] == C_tile[i, j] == C_mkl[i, j]
