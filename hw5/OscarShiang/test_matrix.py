import pytest
import random
import _matrix

def test_construct():
    a = _matrix.Matrix(2, 2)
    a[0, 0] = 1
    a[0, 1] = 2
    a[1, 0] = 3
    a[1, 1] = 4

    b = _matrix.Matrix(2, 2)
    b[0, 0] = 1
    b[0, 1] = 2
    b[1, 0] = 3
    b[1, 1] = 4

    assert a == b

def test_naive():
    a = _matrix.Matrix(2, 2)
    a[0, 0] = 1
    a[0, 1] = 2
    a[1, 0] = 3
    a[1, 1] = 4

    b = _matrix.Matrix(2, 2)
    b[0, 0] = 1
    b[0, 1] = 2
    b[1, 0] = 3
    b[1, 1] = 4

    c = _matrix.multiply_naive(a, b)

    assert c[0, 0] == 7 and c[0, 1] == 10 and c[1, 0] == 15 and c[1, 1] == 22

def test_tile():
    a = _matrix.Matrix(1000, 1005)
    for i in range(1000):
        for j in range(1005):
            a[i, j] = random.randrange(100)

    b = _matrix.Matrix(1005, 1000)
    for i in range(1005):
        for j in range(1000):
            b[i, j] = random.randrange(100)

    m1 = _matrix.multiply_naive(a, b)
    m2 = _matrix.multiply_tile(a, b, 500)

    assert(m1 == m2)

def test_mkl():
    a = _matrix.Matrix(1000, 1005)
    for i in range(1000):
        for j in range(1005):
            a[i, j] = random.randrange(100)

    b = _matrix.Matrix(1005, 1000)
    for i in range(1005):
        for j in range(1000):
            b[i, j] = random.randrange(100)

    m1 = _matrix.multiply_naive(a, b)
    m2 = _matrix.multiply_mkl(a, b)

    assert(m1 == m2)
