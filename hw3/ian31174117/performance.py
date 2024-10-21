import _matrix
import timeit

def benchmark():
    setup = '''
import _matrix

size = 1000

mat1 = _matrix.Matrix(size,size)
mat2 = _matrix.Matrix(size,size)

for it in range(size):
    for jt in range(size):
        mat1[it, jt] = it * size + jt + 1
        mat2[it, jt] = it * size + jt + 1
'''
    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)
    tile = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 16)', setup=setup)

    repeat = 5

    with open('performance.txt', 'w') as fobj:
        fobj.write('size: 1000 * 1000\n')
        naive_time = min(naive.repeat(repeat, 1))
        fobj.write('naive: {} seconds\n'.format(naive_time))
        mkl_time = min(mkl.repeat(repeat, 1))
        fobj.write('mkl: {} seconds\n'.format(mkl_time))
        tile_time = min(tile.repeat(repeat, 1))
        fobj.write('tile: {} seconds\n'.format(tile_time))
        fobj.write('mkl speedup over naive: {}\n'.format(naive_time / mkl_time))
        fobj.write('tile speedup over naive: {}\n'.format(naive_time / tile_time))
    return
if __name__ == '__main__':
    benchmark()