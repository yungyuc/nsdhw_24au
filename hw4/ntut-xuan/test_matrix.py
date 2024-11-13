import pytest
from _matrix import Matrix, multiply_naive, multiply_mkl, multiply_tile, bytes, allocated, deallocated

def test_naive_matrix_manupication():
    m1 = Matrix(3, 2)
    m2 = Matrix(2, 1)

    m1[0, 0] = 2.0
    m1[0, 1] = 1.0
    m1[1, 0] = 2.0
    m1[1, 1] = 3.0
    m1[2, 0] = 2.0
    m1[2, 1] = 4.0

    m2[0, 0] = 1.0
    m2[0, 1] = 2.0

    m3 = multiply_naive(m1, m2)

    assert m3[0, 0] == 4.0
    assert m3[1, 0] == 8
    assert m3[2, 0] == 10


def test_tile_matrix_manupication():
    m1 = Matrix(3, 2)
    m2 = Matrix(2, 1)

    m1[0, 0] = 2.0
    m1[0, 1] = 1.0
    m1[1, 0] = 2.0
    m1[1, 1] = 3.0
    m1[2, 0] = 2.0
    m1[2, 1] = 4.0

    m2[0, 0] = 1.0
    m2[0, 1] = 2.0

    m3 = multiply_tile(m1, m2, 1)

    assert m3[0, 0] == 4
    assert m3[1, 0] == 8
    assert m3[2, 0] == 10


def test_mkl_matrix_manupication():
    m1 = Matrix(3, 2)
    m2 = Matrix(2, 1)

    m1[0, 0] = 2.0
    m1[0, 1] = 1.0
    m1[1, 0] = 2.0
    m1[1, 1] = 3.0
    m1[2, 0] = 2.0
    m1[2, 1] = 4.0

    m2[0, 0] = 1.0
    m2[0, 1] = 2.0

    m3 = multiply_mkl(m1, m2)

    assert m3[0, 0] == 4
    assert m3[1, 0] == 8
    assert m3[2, 0] == 10

def test_our_allocator():

    assert bytes() == 0

    m1 = Matrix(3, 2)
    m2 = Matrix(2, 1)

    assert bytes() == 3 * 2 * 8 + 2 * 1 * 8

def test_our_allocator_after_free_it():

    assert bytes() == 0
    base_allocated = allocated()
    base_deallocated = deallocated()

    m1 = Matrix(3, 2)
    m2 = Matrix(2, 1)

    assert allocated() == 3 * 2 * 8 + 2 * 1 * 8 + base_allocated

    m1 = 0
    m2 = 0

    assert deallocated() == 3 * 2 * 8 + 2 * 1 * 8 + base_deallocated
    assert bytes() == 0