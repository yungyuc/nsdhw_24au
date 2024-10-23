import _matrix
import pytest


def test_matrix():
    arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
    mat1 = _matrix.Matrix(3, 4, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])
    assert mat1.nrow == 3
    assert mat1.ncol == 4
    for i in range(12):
        assert mat1[i] == arr[i]
    for i in range(3):
        for j in range(4):
            assert mat1[i, j] == arr[i*4+j]
    mat1[1, 2] = 100
    assert mat1[6] == 100
    mat1[6] = 200
    assert mat1[1, 2] == 200



def test_multiply1():
    mat1 = _matrix.Matrix(500, 800, [ i for i in range(400000)])
    mat2 = _matrix.Matrix(800, 400, [ i for i in range(320000)])
    ret1 = _matrix.multiply_naive(mat1, mat2)
    ret2 = _matrix.multiply_tile(mat1, mat2, 32)
    ret3 = _matrix.multiply_mkl(mat1, mat2)

    assert ret1.nrow == ret2.nrow == ret3.nrow == mat1.nrow
    assert ret1.ncol == ret2.ncol == ret3.ncol == mat2.ncol
    for i in range(ret1.nrow*ret1.ncol):
        assert abs(ret1[i] - ret2[i]) < 1e-6
        assert abs(ret1[i] - ret3[i]) < 1e-6

def test_multiply2():
    mat1 = _matrix.Matrix(100, 100, [ 0.02*i for i in range(10000)])
    mat2 = _matrix.Matrix(100, 100, [ 0.05*i for i in range(10000)])
    ret1 = _matrix.multiply_naive(mat1, mat2)
    ret2 = _matrix.multiply_tile(mat1, mat2, 16)
    ret3 = _matrix.multiply_mkl(mat1, mat2)

    assert ret1.nrow == ret2.nrow == ret3.nrow == mat1.nrow
    assert ret1.ncol == ret2.ncol == ret3.ncol == mat2.ncol
    for i in range(ret1.nrow*ret1.ncol):
        assert abs(ret1[i] - ret2[i]) < 1e-6
        assert abs(ret1[i] - ret3[i]) < 1e-6
