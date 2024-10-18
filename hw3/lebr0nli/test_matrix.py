import _matrix
import timeit


def make_matrices(size):
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)
    mat3 = _matrix.Matrix(size, size)

    for it in range(size):
        for jt in range(size):
            mat1[it, jt] = it * size + jt + 1
            mat2[it, jt] = it * size + jt + 1
            mat3[it, jt] = 0

    return mat1, mat2, mat3


def test_basic():
    size = 100
    mat1, mat2, mat3 = make_matrices(size)

    assert (
        size
        == mat1.nrow
        == mat1.ncol
        == mat2.nrow
        == mat2.ncol
        == mat3.nrow
        == mat3.ncol
    )

    assert mat1[0, 1] == 2
    assert mat1[1, 1] == size + 2
    assert mat1[1, size - 1] == size * 2
    assert mat1[size - 1, size - 1] == size * size

    for i in range(mat1.nrow):
        for j in range(mat1.ncol):
            assert mat1[i, j] != 0
            assert mat1[i, j] == mat2[i, j]
            assert mat3[i, j] == 0

    assert mat1 == mat2
    assert mat1 is not mat2


def test_match_naive_mkl():
    size = 100
    mat1, mat2, _ = make_matrices(size)

    ret_naive = _matrix.multiply_naive(mat1, mat2)
    ret_mkl = _matrix.multiply_mkl(mat1, mat2)

    assert size == ret_naive.nrow == ret_naive.ncol == ret_mkl.nrow == ret_mkl.ncol

    for i in range(ret_naive.nrow):
        for j in range(ret_naive.ncol):
            assert mat1[i, j] != ret_mkl[i, j]
            assert ret_naive[i, j] == ret_mkl[i, j]


def test_zero():
    size = 100
    mat1, _, mat3 = make_matrices(size)

    ret_naive = _matrix.multiply_naive(mat1, mat3)
    ret_mkl = _matrix.multiply_mkl(mat1, mat3)

    assert size == ret_naive.nrow == ret_naive.ncol == ret_mkl.nrow == ret_mkl.ncol

    for i in range(ret_naive.nrow):
        for j in range(ret_naive.ncol):
            assert ret_naive[i, j] == 0
            assert ret_mkl[i, j] == 0


def check_tile(mat1, mat2, tsize):
    if tsize == 0:
        ret_tile = _matrix.multiply_naive(mat1, mat2)
        tile_str = "_matrix.multiply_naive(mat1, mat2)"
    else:
        ret_tile = _matrix.multiply_tile(mat1, mat2, tsize)
        tile_str = "_matrix.multiply_tile(mat1, mat2, tsize)"
    ret_mkl = _matrix.multiply_mkl(mat1, mat2)

    for i in range(ret_tile.nrow):
        for j in range(ret_tile.ncol):
            assert mat1[i, j] != ret_mkl[i, j]
            assert ret_tile[i, j] == ret_mkl[i, j]

    ns = dict(_matrix=_matrix, mat1=mat1, mat2=mat2, tsize=tsize)
    t_tile = timeit.Timer(tile_str, globals=ns)
    t_mkl = timeit.Timer("_matrix.multiply_mkl(mat1, mat2)", globals=ns)

    time_tile = min(t_tile.repeat(10, 1))
    time_mkl = min(t_mkl.repeat(10, 1))
    ratio = time_tile / time_mkl

    return ratio, time_tile


def test_tile():
    mat1, mat2, _ = make_matrices(500)

    ratio0, time0 = check_tile(mat1, mat2, 0)
    print("naive ratio:", ratio0)

    ratio16, time16 = check_tile(mat1, mat2, 16)
    print("tile 16 ratio:", ratio16)
    print("time16 / time0:", time16 / time0)
    assert ratio16 / ratio0 < 0.8

    ratio17, time17 = check_tile(mat1, mat2, 17)
    print("tile 17 ratio:", ratio17)
    print("time17 / time0:", time17 / time0)
    assert ratio17 / ratio0 < 0.8

    ratio19, time19 = check_tile(mat1, mat2, 19)
    print("tile 19 ratio:", ratio19)
    print("time19 / time0:", time19 / time0)
    assert ratio19 / ratio0 < 0.8
