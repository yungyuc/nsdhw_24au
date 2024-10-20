import _matrix
import timeit

def benchmark():
    size = 1000
    A = _matrix.Matrix(size, size)
    B = _matrix.Matrix(size, size)
    for i in range(size):
        for j in range(size):
            A[i, j] = i * size + j + 1
            B[i, j] = i * size + j + 1

    naive_time = min(timeit.repeat(lambda: _matrix.multiply_naive(A, B), number=1, repeat=3))
    tile_time = min(timeit.repeat(lambda: _matrix.multiply_tile(A, B, 64), number=1, repeat=3))
    mkl_time = min(timeit.repeat(lambda: _matrix.multiply_mkl(A, B), number=1, repeat=3))

    with open('performance.txt', 'w') as f:
        f.write(f"Naive multiplication time: {naive_time:.6f} seconds\n")
        f.write(f"Tiled multiplication time: {tile_time:.6f} seconds\n")
        f.write(f"MKL multiplication time: {mkl_time:.6f} seconds\n")
        f.write(f"Tiled speedup over naive: {naive_time/tile_time:.2f}x\n")
        f.write(f"MKL speedup over naive: {naive_time/mkl_time:.2f}x\n")

if __name__ == '__main__':
    benchmark()