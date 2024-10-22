import _matrix
import timeit
import random

def generate_matrix(size):
    mat = _matrix.Matrix(size, size)
    for i in range(size):
        for j in range(size):
            mat[i, j] = random.random()
    return mat

def benchmark():
    size = 1000
    mat1 = generate_matrix(size)
    mat2 = generate_matrix(size)
    blocksize = 50

    time_naive = min(timeit.repeat(lambda: _matrix.multiply_naive(mat1, mat2), number=1, repeat=3))
    time_tile = min(timeit.repeat(lambda: _matrix.multiply_tile(mat1, mat2, blocksize), number=1, repeat=3))
    time_mkl = min(timeit.repeat(lambda: _matrix.multiply_mkl(mat1, mat2), number=1, repeat=3))

    # Output results to performance.txt
    with open('performance.txt', 'w') as f:
        f.write(f"Matrix multiplication performance ({size} x {size} matrix):\n")
        f.write(f"Naive method: {time_naive:.6f} seconds\n")
        f.write(f"Tiled method (block size = {blocksize}): {time_tile:.6f} seconds\n")
        f.write(f"MKL method: {time_mkl:.6f} seconds\n")
        f.write(f"Speed-up of tiled over naive: {time_naive / time_tile:.2f}x\n")
        f.write(f"Speed-up of MKL over naive: {time_naive / time_mkl:.2f}x\n")

if __name__ == '__main__':
    benchmark()
