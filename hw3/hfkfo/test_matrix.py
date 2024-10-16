import _matrix
import pytest

def test_correctness():
    size = 500
    m1 = _matrix.Matrix(size, size)
    m2 = _matrix.Matrix(size, size)

    m3_naive = _matrix.multiply_naive(m1, m2)
    m3_tile = _matrix.multiply_tile(m1, m2, 32)
    m3_mkl = _matrix.multiply_mkl(m1, m2)
    for i in range(m3_naive.nrow):
            for j in range(m3_naive.ncol):
                assert m3_tile[i, j] == m3_naive[i, j]
                assert m3_mkl[i, j] == m3_naive[i, j]