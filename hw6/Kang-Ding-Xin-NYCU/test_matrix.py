import pytest
import timeit
import _matrix

def test_creation():
    matA = _matrix.Matrix(3, 3)
    assert ((matA.nrow == 3) & (matA.ncol == 3))
    matA = _matrix.Matrix(4, 2)
    assert ((matA.nrow == 4) & (matA.ncol == 2))
    matA = _matrix.Matrix(2, 4)
    assert ((matA.nrow == 2) & (matA.ncol == 4))

def test_multiply_correct():

    A = [1., 0., 0.,
         0., 1., 0.,
         0., 0., 1.]
    B = [1., 2., 3.,
         4., 5., 6.,
         7., 8., 9.]
    C = [1., 2., 3., 4., 
         5., 6., 7., 8., 
         9., 10.,11.,12.]
    D = [1., 2., 3.,
         4., 5., 6.,
         7., 8., 9.,
         10.,11.,12.]
    
    matA = _matrix.Matrix(3, 3)
    matA.buf_set(A)
    matB = _matrix.Matrix(3, 3)
    matB.buf_set(B)
    matC = _matrix.Matrix(3, 4)
    matC.buf_set(C)
    matD = _matrix.Matrix(4, 3)
    matD.buf_set(D)
    
    res1 = _matrix.Matrix(3, 3)
    res1 = _matrix.multiply_naive(matA, matB)
    res2 = _matrix.Matrix(3, 3)
    res2 = _matrix.multiply_naive(matB, matA)
    res3 = _matrix.Matrix(3, 4)
    res3 = _matrix.multiply_naive(matA, matC)
    res4 = _matrix.Matrix(4, 3)
    res4 = _matrix.multiply_naive(matD, matA)
    assert ((matB == res1) & (matB == res2)  & (matC == res3)  & (matD == res4))

    res5 = _matrix.Matrix(3, 3)
    res5 = _matrix.multiply_tile(matA, matB, 2)
    res6 = _matrix.Matrix(3, 3)
    res6 = _matrix.multiply_tile(matB, matA, 2)
    res7 = _matrix.Matrix(3, 4) 
    res7 = _matrix.multiply_tile(matA, matC, 2)
    res8 = _matrix.Matrix(4, 3)
    res8 = _matrix.multiply_tile(matD, matA, 2)
    assert ((matB == res5) & (matB == res6)  & (matC == res7)  & (matD == res8))

    res9 = _matrix.Matrix(3, 3)
    res9 = _matrix.multiply_mkl(matA, matB)
    res10 = _matrix.Matrix(3, 3)
    res10 = _matrix.multiply_mkl(matB, matA)
    res11 = _matrix.Matrix(3, 4)
    res11 = _matrix.multiply_mkl(matA, matC)
    res12 = _matrix.Matrix(4, 3)
    res12 = _matrix.multiply_mkl(matD, matA)
    assert ((matB == res9) & (matB == res10) & (matC == res11) & (matD == res12))
    
def test_multiply_match():

    A = [9., 8., 7.,
         6., 5., 4.,
         3., 2., 1.]
    B = [1., 2., 3.,
         4., 5., 6.,
         7., 8., 9.]
    C = [1., 2., 3., 4., 
         5., 6., 7., 8., 
         9., 10.,11.,12.]
    D = [1., 2., 3.,
         4., 5., 6.,
         7., 8., 9.,
         10.,11.,12.]
    
    matA = _matrix.Matrix(3, 3)
    matA.buf_set(A)
    matB = _matrix.Matrix(3, 3)
    matB.buf_set(B)
    matC = _matrix.Matrix(3, 4)
    matC.buf_set(C)
    matD = _matrix.Matrix(4, 3)
    matD.buf_set(D)

    res1 = _matrix.Matrix(3, 3)
    res1 = _matrix.multiply_naive(matA, matB)
    res2 = _matrix.Matrix(3, 3)
    res2 = _matrix.multiply_tile(matA, matB, 2)
    res3 = _matrix.Matrix(3, 3)
    res3 = _matrix.multiply_mkl(matA, matB)
    assert ((res1 == res2) & (res2 == res3))

    res4 = _matrix.Matrix(3, 4)
    res4 = _matrix.multiply_naive(matA, matC)
    res5 = _matrix.Matrix(3, 4)
    res5 = _matrix.multiply_tile(matA, matC, 2)
    res6 = _matrix.Matrix(3, 4)
    res6 = _matrix.multiply_mkl(matA, matC)
    assert ((res4 == res5) & (res5 == res6))

    res7 = _matrix.Matrix(4, 3)
    res7 = _matrix.multiply_naive(matD, matA)
    res8 = _matrix.Matrix(4, 3)
    res8 = _matrix.multiply_tile(matD, matA, 2)
    res9 = _matrix.Matrix(4, 3)
    res9 = _matrix.multiply_mkl(matD, matA)
    assert ((res7 == res8) & (res8 == res9))

    res10 = _matrix.Matrix(3, 3)
    res10 = _matrix.multiply_naive(matC, matD)
    res11 = _matrix.Matrix(3, 3)
    res11 = _matrix.multiply_tile(matC, matD, 2)
    res12 = _matrix.Matrix(3, 3)
    res12 = _matrix.multiply_mkl(matC, matD)
    assert ((res10 == res11) & (res11 == res12))

def test_zero():
        
        assert(0 == _matrix.bytes())

        size = 200
        mat1 = _matrix.Matrix(200, 200)
        mat2 = _matrix.Matrix(200, 200)
        mat3 = _matrix.Matrix(200, 200)
        assert(3*8 * size*size == _matrix.bytes())
        base_alloc = _matrix.allocated()
        base_dealloc = _matrix.deallocated()

        ret_naive = _matrix.multiply_naive(mat1, mat3)
        ret_mkl = _matrix.multiply_mkl(mat1, mat3)

        assert(size == ret_naive.nrow)
        assert(size == ret_naive.ncol)
        assert(size == ret_mkl.nrow)
        assert(size == ret_mkl.ncol)

        for i in range(ret_naive.nrow):
            for j in range(ret_naive.ncol):
               assert(0 == ret_naive[i,j])
               assert(0 == ret_mkl[i,j])

        assert(5*8 * size*size == _matrix.bytes())
        assert(base_alloc + (2*8 * size*size) == _matrix.allocated())
        assert(base_dealloc == _matrix.deallocated())

def test_memory():
     
     assert(0 == _matrix.bytes())
     base_alloc = _matrix.allocated()
     base_dealloc = _matrix.deallocated()

     size = 100
     mat1 = _matrix.Matrix(100, 100)
     mat2 = _matrix.Matrix(100, 100)
     mat3 = _matrix.Matrix(100, 100)
     assert(3*8 * size*size == _matrix.bytes())
        # New allocation.
     assert(base_alloc + 3*8 * size*size == _matrix.allocated())
        # No deallocation.
     assert(base_dealloc == _matrix.deallocated())
     mat1 = mat2 = mat3 = None
        # Matrices are deallocated.
     assert(0 == _matrix.bytes())
     assert(base_dealloc + 3*8 * size*size == _matrix.deallocated())
     assert(base_alloc + 3*8 * size*size == _matrix.allocated())