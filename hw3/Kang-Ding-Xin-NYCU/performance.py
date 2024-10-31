import _matrix
import timeit
import sys

def benchmark():
    setup = '''
import _matrix

mat1 = _matrix.Matrix(size,size)
mat2 = _matrix.Matrix(size,size)

for it in range(size):
    for jt in range(size):
        mat1[it, jt] = it * size + jt + 1
        mat2[it, jt] = it * size + jt + 1
'''

    naive = '''
_matrix.multiply_naive(mat1, mat2)
'''

    tile  = '''
_matrix.multiply_tile(mat1, mat2, time)
'''

    mkl  = '''
_matrix.multiply_mkl(mat1, mat2)
'''
    size = 1000
    naive_time = timeit.Timer(stmt=naive, setup=setup, globals=locals()).timeit(number=1)
    min_time = sys.float_info.max
    for time in range(56, 66):
        min_time = min(min_time, timeit.Timer(stmt=tile, setup=setup, globals=locals()).timeit(number=1))
    tile_time = min_time
    mkl_time = timeit.Timer(stmt=mkl, setup=setup, globals=locals()).timeit(number=1)

    with open('performance.txt', 'w') as txt:
        txt.write(f"Naive multiplication time: {naive_time:.6f} seconds\n")
        txt.write(f"Tiled multiplication time: {tile_time:.6f} seconds\n")
        txt.write(f"MKL multiplication time: {mkl_time:.6f} seconds\n")
        txt.write(f"Tiled speedup over naive: {naive_time/tile_time:.6f}x\n")
        txt.write(f"MKL speedup over naive: {naive_time/mkl_time:.6f}x\n")

if __name__ == '__main__':
    benchmark()