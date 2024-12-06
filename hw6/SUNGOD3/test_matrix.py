import numpy as np
import pytest
from _matrix import Matrix

def test_matrix_creation():
    # Test basic matrix creation
    m = Matrix(3, 4)
    assert m.nrow() == 3
    assert m.ncol() == 4

def test_matrix_element_access():
    # Test element access and modification
    m = Matrix(2, 2)
    m(0, 0, 1.5)  # Assuming we modify the binding to support assignment
    m(1, 1, 2.5)
    assert m(0, 0) == 1.5
    assert m(1, 1) == 2.5

def test_matrix_multiply_naive():
    # Test naive matrix multiplication
    A = Matrix(2, 3)
    B = Matrix(3, 2)
    
    # Populate matrices
    for i in range(2):
        for j in range(3):
            A(i, j, i + j)
    
    for i in range(3):
        for j in range(2):
            B(i, j, i * j)
    
    C = Matrix.multiply_naive(A, B)
    
    # Verify dimensions
    assert C.nrow() == 2
    assert C.ncol() == 2

def test_matrix_as_numpy():
    # Test conversion to NumPy array
    m = Matrix(3, 4)
    
    # Populate matrix
    for i in range(3):
        for j in range(4):
            m(i, j, i * 4 + j)
    
    # Convert to NumPy array
    np_array = m.as_numpy()
    
    # Check array properties
    assert isinstance(np_array, np.ndarray)
    assert np_array.shape == (3, 4)
    
    # Verify data integrity
    for i in range(3):
        for j in range(4):
            assert np_array[i, j] == i * 4 + j

def test_matrix_multiplication_methods():
    # Test different multiplication methods
    A = Matrix(2, 3)
    B = Matrix(3, 2)
    
    # Populate matrices
    for i in range(2):
        for j in range(3):
            A(i, j, i + j)
    
    for i in range(3):
        for j in range(2):
            B(i, j, i * j)
    
    # Test naive multiplication
    naive_result = Matrix.multiply_naive(A, B)
    
    # Test tiled multiplication
    tiled_result = Matrix.multiply_tile(A, B)
    
    # Verify results are equal
    assert naive_result == tiled_result

def test_matrix_equality():
    # Test matrix equality
    m1 = Matrix(2, 2)
    m2 = Matrix(2, 2)
    
    for i in range(2):
        for j in range(2):
            m1(i, j, i + j)
            m2(i, j, i + j)
    
    assert m1 == m2

def test_matrix_inequality():
    # Test matrix inequality
    m1 = Matrix(2, 2)
    m2 = Matrix(2, 2)
    
    for i in range(2):
        for j in range(2):
            m1(i, j, i + j)
            m2(i, j, i * j)
    
    assert m1 != m2

def test_matrix_dimensions_mismatch():
    # Test multiplication with mismatched dimensions
    A = Matrix(2, 3)
    B = Matrix(4, 2)
    
    with pytest.raises(ValueError):
        Matrix.multiply_naive(A, B)

    with pytest.raises(ValueError):
        Matrix.multiply_tile(A, B)