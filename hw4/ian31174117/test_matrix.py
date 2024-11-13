import pytest
import _matrix
import numpy as np

def make_matrices(size):
    mat1 = _matrix.Matrix(size,size)
    mat2 = _matrix.Matrix(size,size)
    mat3 = _matrix.Matrix(size,size)
    for it in range(size):
        for jt in range(size):
            mat1[it, jt] = it * size + jt + 1
            mat2[it, jt] = it * size + jt + 1
            mat3[it, jt] = 0
    return mat1, mat2, mat3

def test_basic():
    assert np.allclose(0, _matrix.bytes())
    size = 100
    mat1, mat2, mat3 = make_matrices(size)
    assert np.allclose(3*8 * size*size, _matrix.bytes())
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()

    assert np.allclose(size, mat1.nrow)
    assert np.allclose(size, mat1.ncol)
    assert np.allclose(size, mat2.nrow)
    assert np.allclose(size, mat2.ncol)
    assert np.allclose(size, mat3.nrow)
    assert np.allclose(size, mat3.ncol)

    assert np.allclose(2, mat1[0,1])
    assert np.allclose(size+2, mat1[1,1])
    assert np.allclose(size*2, mat1[1,size-1])
    assert np.allclose(size*size, mat1[size-1,size-1])

    for i in range(mat1.nrow):
        for j in range(mat1.ncol):
            assert np.allclose(0, mat3[i,j])
            assert np.allclose(mat1[i,j], mat2[i,j])
            assert np.allclose(0, mat3[i,j])
    
    assert np.allclose(True, mat1 is not mat2)

    assert np.allclose(3*8 * size*size, _matrix.bytes())
    assert np.allclose(base_alloc, _matrix.allocated())
    assert np.allclose(base_dealloc, _matrix.deallocated())

def test_match_naive_mkl():
    assert np.allclose(0, _matrix.bytes())
    size = 100
    mat1, mat2, *_ = make_matrices(size)
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()
    mat3 = _matrix.multiply_naive(mat1, mat2)
    mat4 = _matrix.multiply_mkl(mat1, mat2)
    for i in range(mat3.nrow):
        for j in range(mat3.ncol):
            assert np.allclose(mat3[i,j], mat4[i,j])

    assert np.allclose(base_alloc + 2*8 * size*size, _matrix.allocated())
    assert np.allclose(base_dealloc, _matrix.deallocated())

def test_memory():
    assert np.allclose(0, _matrix.bytes())
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()
    size = 100
    mat1, mat2, mat3 = make_matrices(size)
    assert np.allclose(3*8 * size*size, _matrix.bytes())
    assert np.allclose(base_alloc+3*8*size*size, _matrix.allocated())
    assert np.allclose(base_dealloc, _matrix.deallocated())

    mat1 = mat2 = mat3 = None
    assert np.allclose(0, _matrix.bytes())
    assert np.allclose(base_alloc+3*8*size*size, _matrix.allocated())
    assert np.allclose(base_dealloc+3*8*size*size, _matrix.deallocated())