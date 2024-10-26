import pytest
import _matrix
import numpy as np

def test_create():
    n = 3
    m = 3
    mat = _matrix.Matrix(n, m)
    assert n == mat.ncol and  m == mat.ncol

def test_set_get():
    n = 3
    m = 3
    mat = _matrix.Matrix(n, m)
    mat[1, 1] = 1
    assert mat[1, 1] == 1

def test_multiply_naive():
    def populate(mat):
        for i in range(mat.nrow):
            for j in range(mat.ncol):
                mat[i, j] = 0.5
    def print_mat(mat):
        for i in range(mat.nrow):
            for j in range(mat.ncol):
                print(mat[i, j], end=' ')
    mat1 = _matrix.Matrix(3, 3)
    mat2 = _matrix.Matrix(3, 3)
    populate(mat1)
    populate(mat2)
    result = _matrix.multiply_naive(mat1, mat2)
    for i in range(result.nrow):
        for j in range(result.ncol):
            assert result[i, j] == 0.75  
    
def test_multiply_mkl():
    def populate(mat):
        for i in range(mat.nrow):
            for j in range(mat.ncol):
                mat[i, j] = 0.5
    mat1 = _matrix.Matrix(3, 3)
    mat2 = _matrix.Matrix(3, 3)
    populate(mat1)
    populate(mat2)
    result = _matrix.multiply_mkl(mat1, mat2)
    for i in range(result.nrow):
        for j in range(result.ncol):
            assert result[i, j] == 0.75

def test_multiply_tile():
    def populate(mat):
        for i in range(mat.nrow):
            for j in range(mat.ncol):
                mat[i, j] = 0.5
    mat1 = _matrix.Matrix(300, 300)
    mat2 = _matrix.Matrix(300, 300)
    populate(mat1)
    populate(mat2)
    result = _matrix.multiply_tile(mat1, mat2, 16)
    for i in range(result.nrow):
        for j in range(result.ncol):
            assert result[i, j] == 75

def test_mkl_tile_match():
    def populate(mat):
        for i in range(mat.nrow):
            for j in range(mat.ncol):
                mat[i, j] = i*10+j
    mat1 = _matrix.Matrix(300, 300)
    mat2 = _matrix.Matrix(300, 300)
    populate(mat1)
    populate(mat2)
    result_mkl = _matrix.multiply_mkl(mat1, mat2)
    result_tile = _matrix.multiply_tile(mat1, mat2, 16)
    for i in range(result_mkl.nrow):
        for j in range(result_mkl.ncol):
            assert result_mkl[i, j] == result_tile[i, j]

if __name__ == '__main__':
    test_multiply_naive()