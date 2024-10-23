import pytest
from _matrix import Matrix, multiply_naive, multiply_mkl, multiply_tile, GetMatrixData

def test_naive_matrix_manupication():
    m1 = Matrix(3, 2)
    m2 = Matrix(2, 1)

    m1.SetMatrixData([2.0, 1.0, 2.0, 3.0, 2.0, 4.0])
    m2.SetMatrixData([1.0, 2.0])

    m3 = multiply_naive(m1, m2)

    assert GetMatrixData(m3, 0, 0) == 4
    assert GetMatrixData(m3, 1, 0) == 8
    assert GetMatrixData(m3, 2, 0) == 10


def test_tile_matrix_manupication():
    m1 = Matrix(3, 2)
    m2 = Matrix(2, 1)

    m1.SetMatrixData([2.0, 1.0, 2.0, 3.0, 2.0, 4.0])
    m2.SetMatrixData([1.0, 2.0])

    m3 = multiply_tile(m1, m2, 1)

    assert GetMatrixData(m3, 0, 0) == 4
    assert GetMatrixData(m3, 1, 0) == 8
    assert GetMatrixData(m3, 2, 0) == 10


def test_mkl_matrix_manupication():
    m1 = Matrix(3, 2)
    m2 = Matrix(2, 1)

    m1.SetMatrixData([2.0, 1.0, 2.0, 3.0, 2.0, 4.0])
    m2.SetMatrixData([1.0, 2.0])

    m3 = multiply_mkl(m1, m2)

    assert GetMatrixData(m3, 0, 0) == 4
    assert GetMatrixData(m3, 1, 0) == 8
    assert GetMatrixData(m3, 2, 0) == 10