import pytest
import _matrix

def test_matrix_creation():
    mat = _matrix.Matrix(3, 3)
    assert mat.nrow() == 3
    assert mat.ncol() == 3
    assert mat(0, 0) == 0.0  # Initialized to 0

def test_matrix_multiplication_equal():
    size = 100
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)

    mat3_naive = _matrix.multiply_naive(mat1, mat2)
    mat3_tile = _matrix.multiply_tile(mat1, mat2)
    mat3_mkl = _matrix.multiply_mkl(mat1, mat2)
    assert mat3_naive == mat3_tile
    assert mat3_naive == mat3_mkl

def test_matrix_multiplication_naive():
    mat1 = _matrix.Matrix(2, 2, 1.0)  # 2x2 matrix filled with 1.0
    mat2 = _matrix.Matrix(2, 2, 2.0)  # 2x2 matrix filled with 2.0
    result = _matrix.multiply_naive(mat1, mat2)
    
    assert result.nrow() == 2
    assert result.ncol() == 2
    for i in range(2):
        for j in range(2):
            assert result(i, j) == 4.0  # 1*2 + 1*2 = 4

def test_matrix_multiplication_tile():
    mat1 = _matrix.Matrix(2, 2, 1.0)
    mat2 = _matrix.Matrix(2, 2, 2.0)
    result = _matrix.multiply_tile(mat1, mat2, 1)  # Tiling with block size 1

    assert result.nrow() == 2
    assert result.ncol() == 2
    for i in range(2):
        for j in range(2):
            assert result(i, j) == 4.0

def test_matrix_multiplication_mkl():
    mat1 = _matrix.Matrix(2, 2, 1.0)
    mat2 = _matrix.Matrix(2, 2, 2.0)
    result = _matrix.multiply_mkl(mat1, mat2)

    assert result.nrow() == 2
    assert result.ncol() == 2
    for i in range(2):
        for j in range(2):
            assert result(i, j) == 4.0
