import timeit
import random
from statistics import mean
import _matrix

a = _matrix.Matrix(1000, 1005)
for i in range(1000):
    for j in range(1005):
        a[i, j] = random.randrange(100)

b = _matrix.Matrix(1005, 1000)
for i in range(1005):
    for j in range(1000):
        b[i, j] = random.randrange(100)

naive_time = mean(timeit.repeat(lambda: _matrix.multiply_naive(a, b), number=1))
tile_time = mean(timeit.repeat(lambda: _matrix.multiply_tile(a, b, 100), number=1))
mkl_time = mean(timeit.repeat(lambda: _matrix.multiply_mkl(a, b), number=1))

with open('performance.txt', 'w') as f:
    f.write(f'func\ttime\tspeedup\n')
    f.write(f'naive\t{naive_time:.3f}s\t{naive_time / naive_time:.2f}x\n')
    f.write(f'tile\t{tile_time:.3f}s\t{naive_time / tile_time:.2f}x\n')
    f.write(f'mkl\t{mkl_time:.3f}s\t{naive_time / mkl_time:.2f}x\n')
