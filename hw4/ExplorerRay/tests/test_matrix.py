import _matrix
import pytest
import random
from utils import generate_matrix_2d

def test_constructor():
    row = random.randint(1, 100)
    col = random.randint(1, 100)
    mat = _matrix.Matrix(row, col)
    assert mat.nrow == row
    assert mat.ncol == col

def test_generate_matrix():
    row = random.randint(1, 100)
    col = random.randint(1, 100)
    mat = generate_matrix_2d(row, col)
    assert mat.nrow == row
    assert mat.ncol == col

def test_false_row():
    with pytest.raises(ValueError):
        mat = _matrix.Matrix(0, 1)
    
def test_false_col():
    with pytest.raises(ValueError):
        mat = _matrix.Matrix(1, 0)

def test_false_row_col():
    with pytest.raises(ValueError):
        mat = _matrix.Matrix(0, 0)

def test_basic():
    size = 100
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)
    mat3 = _matrix.Matrix(size, size)

    for it in range(size):
        for jt in range(size):
            mat1[it, jt] = it * size + jt + 1
            mat2[it, jt] = it * size + jt + 1
            mat3[it, jt] = 0

    assert size == mat1.nrow
    assert size == mat1.ncol
    assert size == mat2.nrow
    assert size == mat2.ncol

    assert 2 == mat1[0,1]
    assert size+2 == mat1[1,1]
    assert size*2 == mat1[1,size-1]
    assert size*size == mat1[size-1,size-1]

    for i in range(mat1.nrow):
        for j in range(mat1.ncol):
            assert 0 != mat1[i,j]
            assert mat1[i,j] == mat2[i,j]
            assert 0 == mat3[i,j]

    assert mat1 == mat2
    assert mat1 is not mat2
