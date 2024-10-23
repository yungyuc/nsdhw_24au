import pytest
import _matrix

def test_matrix_creation():
    mat = _matrix.Matrix(3, 3)
    assert mat.nrow == 3
    assert mat.ncol == 3

def test_matrix_element_access():
    mat = _matrix.Matrix(3, 3)
    mat[0, 0] = 10.0
    assert mat[0, 0] == 10.0

def test_matrix_equality():
    mat1 = _matrix.Matrix(3, 3)
    mat2 = _matrix.Matrix(3, 3)
    assert mat1 == mat2
    mat1[0, 0] = 5.0
    assert mat1 != mat2

def create_matrix_3x3_A():
    A = _matrix.Matrix(3, 3)
    A[0, 0] = 1.0
    A[0, 1] = 2.0
    A[0, 2] = 3.0
    A[1, 0] = 4.0
    A[1, 1] = 5.0
    A[1, 2] = 6.0
    A[2, 0] = 7.0
    A[2, 1] = 8.0
    A[2, 2] = 9.0
    return A

def create_matrix_3x3_B():
    B = _matrix.Matrix(3, 3)
    B[0, 0] = 9.0
    B[0, 1] = 8.0
    B[0, 2] = 7.0
    B[1, 0] = 6.0
    B[1, 1] = 5.0
    B[1, 2] = 4.0
    B[2, 0] = 3.0
    B[2, 1] = 2.0
    B[2, 2] = 1.0
    return B

def test_naive_multiplication():
    A = create_matrix_3x3_A()
    B = create_matrix_3x3_B()

    C = _matrix.multiply_naive(A, B)
    
    assert C[0, 0] == 30.0
    assert C[0, 1] == 24.0
    assert C[0, 2] == 18.0
    assert C[1, 0] == 84.0
    assert C[1, 1] == 69.0
    assert C[1, 2] == 54.0
    assert C[2, 0] == 138.0
    assert C[2, 1] == 114.0
    assert C[2, 2] == 90.0

def test_tile_multiplication():
    A = create_matrix_3x3_A()
    B = create_matrix_3x3_B()

    C = _matrix.multiply_tile(A, B, tile_size=1)
    
    assert C[0, 0] == 30.0
    assert C[0, 1] == 24.0
    assert C[0, 2] == 18.0
    assert C[1, 0] == 84.0
    assert C[1, 1] == 69.0
    assert C[1, 2] == 54.0
    assert C[2, 0] == 138.0
    assert C[2, 1] == 114.0
    assert C[2, 2] == 90.0



def test_mkl_multiplication():
    A = _matrix.Matrix(2, 2)
    B = _matrix.Matrix(2, 2)
    A[0, 0] = 1.0
    A[0, 1] = 2.0
    A[1, 0] = 3.0
    A[1, 1] = 4.0

    B[0, 0] = 1.0
    B[0, 1] = 0.0
    B[1, 0] = 0.0
    B[1, 1] = 1.0

    C = _matrix.multiply_mkl(A, B)
    
    assert C[0, 0] == 1.0
    assert C[0, 1] == 2.0
    assert C[1, 0] == 3.0
    assert C[1, 1] == 4.0

