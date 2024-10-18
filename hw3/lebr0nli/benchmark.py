import timeit
import _matrix


def create_matrices(size):
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)

    for it in range(size):
        for jt in range(size):
            value = it * size + jt + 1
            mat1[it, jt] = value
            mat2[it, jt] = value

    return mat1, mat2


def benchmark_multiply(func, args, repeat=5):
    timer = timeit.Timer(lambda: func(*args))
    times = timer.repeat(repeat=repeat, number=1)
    return min(times)


class BenchmarkWriter:
    def __init__(self, filename):
        self.file = open(filename, "w")

    def write(self, *args):
        self.file.write(" ".join(map(str, args)) + "\n")

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.file.close()


def run_benchmark(sizes=[500, 1000], repeat=5, tile_size=64):
    with BenchmarkWriter("performance.txt") as writer:
        for size in sizes:
            mat1, mat2 = create_matrices(size)

            naive_time = benchmark_multiply(
                _matrix.multiply_naive, (mat1, mat2), repeat
            )
            mkl_time = benchmark_multiply(_matrix.multiply_mkl, (mat1, mat2), repeat)
            tile_time = benchmark_multiply(
                _matrix.multiply_tile, (mat1, mat2, tile_size), repeat
            )

            mkl_speedup = naive_time / mkl_time
            tile_speedup = naive_time / tile_time

            writer.write(f"Matrix size: {size}x{size}")
            writer.write(f"Repeat: {repeat}")
            writer.write(f"multiply_naive time: {naive_time:.6f} seconds")
            writer.write(f"multiply_tile time: {tile_time:.6f} seconds")
            writer.write(f"multiply_mkl time: {mkl_time:.6f} seconds")
            writer.write(f"Tile speed-up over naive: {tile_speedup:.2f}x")
            writer.write(f"MKL speed-up over naive: {mkl_speedup:.2f}x")
            writer.write()  # Add an empty line between iterations


if __name__ == "__main__":
    run_benchmark()
