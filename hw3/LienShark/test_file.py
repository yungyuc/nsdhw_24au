from _matrix import Matrix, multiply_naive, multiply_tile, multiply_mkl

import pytest
from pytest import approx as ap
from timeit import Timer

class Testclass:
    def test_matrix_basic(self):
        size = 20
        mat1 = Matrix(size, size)
        mat2 = Matrix(size, size)
        mat3 = Matrix(size, size)
        for i in range(size):
            for j in range(size):
                mat1[i, j] = 2
                mat2[i, j] = 7
                mat3[i, j] = 0
        ans_naive = multiply_naive(mat1, mat3)
        ans_mkl = multiply_mkl(mat1, mat3)
        ans_tile = multiply_tile(mat2, mat3, 64)
        assert ans_naive.nrow == size 
        assert ans_naive.ncol == size 
        assert ans_mkl.nrow == size 

        for i in range(size):
            for j in range(size):
                assert ans_naive[i, j] == ap(0.0)
                assert ans_mkl[i, j] == ap(0.0)
                assert ans_tile[i, j] == ap(0.0)
    def test_matrix_complicate(self):
        size = 20
        mat1 = Matrix(size, size)
        mat2 = Matrix(size, size)
        mat3 = Matrix(size, size)
        for i in range(size):
            for j in range(size):
                mat1[i, j] = 2
                mat2[i, j] = 7
                mat3[i, j] = 8
        ans_naive = multiply_naive(mat1, mat3)
        ans_mkl = multiply_mkl(mat1, mat3)
        ans_tile = multiply_tile(mat1, mat3, 64)
        assert ans_naive.nrow == size 
        assert ans_naive.ncol == size 
        assert ans_mkl.nrow == size 

        for i in range(size):
            for j in range(size):
                assert ans_naive[i, j] == ap(ans_mkl[i, j])
                assert ans_mkl[i, j] == ap(ans_tile[i, j])

def get_performance():

    setup = '''
from _matrix import Matrix, multiply_naive, multiply_tile, multiply_mkl
size = 1000
mat1 = Matrix(size,size)
mat2 = Matrix(size,size)
for it in range(size):
    for jt in range(size):
        mat1[it, jt] = it * size + jt + 1
        mat2[it, jt] = it * size + jt + 1
    '''

    naive = Timer('multiply_naive(mat1, mat2)', setup=setup)
    mkl = Timer('multiply_mkl(mat1, mat2)', setup=setup)

    repeat = 5

    with open('performance.txt', 'w') as f:

        log = 'multiply_naive : '
        naive_sec  = min(naive.repeat(repeat=repeat, number=1))
        log += f'{naive_sec} seconds\n'

        log += f'multiply_mkl :'
        mkl_sec = min(mkl.repeat(repeat=repeat, number=1))
        log += f'{mkl_sec} seconds\n'

        log += f'mkl speed-up over naive: {naive_sec/mkl_sec}'
        f.write(log)
if __name__ == '__main__':
    get_performance()