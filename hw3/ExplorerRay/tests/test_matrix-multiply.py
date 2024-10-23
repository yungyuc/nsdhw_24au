import _matrix
import pytest
import random
from utils import generate_matrix_2d

def test_multiply_naive():
    size = 100
    mat1 = generate_matrix_2d(size, size)
    mat2 = generate_matrix_2d(size, size)

    ret = _matrix.multiply_naive(mat1, mat2)
    # use python to calculate the result
    for i in range(size):
        for j in range(size):
            assert ret[i, j] == sum([mat1[i, k] * mat2[k, j] for k in range(size)])

def test_multiply_tile():
    tsize = random.randint(1, 100)
    size = 100
    mat1 = generate_matrix_2d(size, size)
    mat2 = generate_matrix_2d(size, size)
    
    ret_n = _matrix.multiply_naive(mat1, mat2)
    ret_t = _matrix.multiply_tile(mat1, mat2, tsize)

    for i in range(size):
        for j in range(size):
            assert ret_n[i, j] == ret_t[i, j]


def test_multiply_mkl():
    size = 100
    mat1 = generate_matrix_2d(size, size)
    mat2 = generate_matrix_2d(size, size)

    ret_n = _matrix.multiply_naive(mat1, mat2)
    ret_mkl = _matrix.multiply_mkl(mat1, mat2)
    # use python to calculate the result
    for i in range(size):
        for j in range(size):
            assert ret_n[i, j] == ret_mkl[i, j]
