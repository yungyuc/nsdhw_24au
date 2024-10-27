import unittest
import _matrix


class TestMatrix(unittest.TestCase):
    def test_init(self):
        mat = _matrix.Matrix(10, 15)
        self.assertEqual(mat.nrow, 10)
        self.assertEqual(mat.ncol, 15)

    def test_set_get_elem(self):
        mat = _matrix.Matrix(10, 10)
        mat[0, 0] = -1.2
        mat[3, 4] = 5.3
        self.assertEqual(mat[0, 0], -1.2)
        self.assertEqual(mat[3, 4], 5.3)

    def test_shape(self):
        mat1, mat2, mat3 = make_matrices(10)
        self.assertTrue(is_matrix_same_shape(mat1, mat2))
        self.assertTrue(is_matrix_same_shape(mat1, mat3))
        self.assertTrue(is_matrix_same_shape(mat2, mat3))

    def test_bound_check(self):
        mat = _matrix.Matrix(10, 15)
        with self.assertRaises(ValueError):
            mat[99,99]

    def test_multiply_naive(self):
        mat1, mat2, _ = make_matrices(10)
        res_naive = _matrix.multiply_naive(mat1, mat2)
        res_mkl   = _matrix.multiply_mkl(mat1, mat2)
        self.assertEqual(res_naive, res_mkl)
    
    def test_multiply_tile(self):
        mat1, mat2, _ = make_matrices(10)
        res_tile = _matrix.multiply_tile(mat1, mat2, 8)
        res_mkl  = _matrix.multiply_mkl(mat1, mat2)
        self.assertEqual(res_tile, res_mkl)


def make_matrices(size: int) -> tuple[_matrix.Matrix, _matrix.Matrix, _matrix.Matrix]:
    mat1 = _matrix.Matrix(size,size)
    mat2 = _matrix.Matrix(size,size)
    mat3 = _matrix.Matrix(size,size)
    for it in range(size):
        for jt in range(size):
            mat1[it, jt] = it * size + jt + 1
            mat2[it, jt] = it * size + jt + 1
            mat3[it, jt] = 0
    return mat1, mat2, mat3


def is_matrix_same_shape(mat1: _matrix.Matrix, mat2: _matrix.Matrix) -> bool:
    return mat1.nrow == mat2.nrow and mat1.ncol == mat2.ncol
