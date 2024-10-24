import time
import pytest
import random
import numpy as np
import _matrix

def get_ans(mat1, mat2, mat_size):
    mat1 = np.array(mat1.data).reshape(mat_size, mat_size)
    mat2 = np.array(mat2.data).reshape(mat_size, mat_size)

    return (mat1 @ mat2).flatten().tolist()

def test_naive_unit():
    mat_size = 1000
    mat_unit = _matrix.Matrix(mat_size, mat_size, [1 if i == j else 0 for i in range(mat_size) for j in range(mat_size)])

    result = _matrix.multiply_naive(mat_unit, mat_unit)

    assert result.data == get_ans(mat_unit, mat_unit, mat_size)

def test_naive_random():
    num_tests = 5
    mat_size = 1000
    total_time = []

    for _ in range(num_tests):
        data1 = [float(random.randint(-100, 100)) for _ in range(mat_size * mat_size)]
        data2 = [float(random.randint(-100, 100)) for _ in range(mat_size * mat_size)]
        mat1 = _matrix.Matrix(mat_size, mat_size, data1)
        mat2 = _matrix.Matrix(mat_size, mat_size, data2)

        start = time.time()
        result = _matrix.multiply_naive(mat1, mat2)
        end = time.time()
        total_time.append(end - start)

        assert result.data == pytest.approx(get_ans(mat1, mat2, mat_size))

    with open('performance.txt', 'a') as f:
        f.write("=== Naive ===\n")
        f.write(f'> Matrix size:\t{mat_size}x{mat_size}\n')
        f.write(f'> Repeated:\t\t{num_tests}\n')
        f.write(f'> Time:\t{total_time}\n')
        f.write(f'> Total time:\t{sum(total_time)}\n')
        f.write(f'> Average time:\t{sum(total_time) / num_tests}\n\n')

def test_tiling_unit():
    mat_size = 1000
    mat_unit = _matrix.Matrix(mat_size, mat_size, [1 if i == j else 0 for i in range(mat_size) for j in range(mat_size)])

    result = _matrix.multiply_tile(mat_unit, mat_unit, 8)

    assert result.data == get_ans(mat_unit, mat_unit, mat_size)

def test_tiling_random():
    num_tests = 5
    mat_size = 1000
    tile_size = 128
    total_time = []

    for _ in range(num_tests):
        data1 = [float(random.randint(-100, 100)) for _ in range(mat_size * mat_size)]
        data2 = [float(random.randint(-100, 100)) for _ in range(mat_size * mat_size)]
        mat1 = _matrix.Matrix(mat_size, mat_size, data1)
        mat2 = _matrix.Matrix(mat_size, mat_size, data2)

        start = time.time()
        result = _matrix.multiply_tile(mat1, mat2, tile_size)
        end = time.time()
        total_time.append(end - start)

        assert result.data == pytest.approx(get_ans(mat1, mat2, mat_size))
    
    with open('performance.txt', 'a') as f:
        f.write("=== Tiling ===\n")
        f.write(f'> Matrix size:\t{mat_size}x{mat_size}\n')
        f.write(f'> Repeated:\t\t{num_tests}\n')
        f.write(f'> Tile size:\t{tile_size}\n')
        f.write(f'> Time:\t{total_time}\n')
        f.write(f'> Total time:\t{sum(total_time)}\n')
        f.write(f'> Average time:\t{sum(total_time) / num_tests}\n\n')

def test_mkl_unit():
    mat_size = 1000
    mat_unit = _matrix.Matrix(mat_size, mat_size, [1 if i == j else 0 for i in range(mat_size) for j in range(mat_size)])

    result = _matrix.multiply_mkl(mat_unit, mat_unit)

    assert result.data == get_ans(mat_unit, mat_unit, mat_size)

def test_mkl_random():
    num_tests = 5
    mat_size = 1000
    total_time = []

    for _ in range(num_tests):
        
        data1 = [float(random.randint(-100, 100)) for _ in range(mat_size * mat_size)]
        data2 = [float(random.randint(-100, 100)) for _ in range(mat_size * mat_size)]
        mat1 = _matrix.Matrix(mat_size, mat_size, data1)
        mat2 = _matrix.Matrix(mat_size, mat_size, data2)

        start = time.time()
        result = _matrix.multiply_mkl(mat1, mat2)
        end = time.time()
        total_time.append(end - start)

        assert result.data == pytest.approx(get_ans(mat1, mat2, mat_size))

    with open('performance.txt', 'a') as f:
        f.write("=== dgemm ===\n")
        f.write(f'> Matrix size:\t{mat_size}x{mat_size}\n')
        f.write(f'> Repeated:\t\t{num_tests}\n')
        f.write(f'> Time:\t{total_time}\n')
        f.write(f'> Total time:\t{sum(total_time)}\n')
        f.write(f'> Average time:\t{sum(total_time) / num_tests}\n\n')


# def test_simple():
#     mat_size = 4
#     mat1 = _matrix.Matrix(mat_size, mat_size, [i for i in range(mat_size * mat_size)])
#     mat2 = _matrix.Matrix(mat_size, mat_size, [i for i in range(mat_size * mat_size)])

#     # print(mat1.data)
#     # print(np.array(mat1.data).reshape(mat_size, mat_size))

#     result = _matrix.multiply_naive(mat1, mat2)

#     assert result.data == pytest.approx(get_ans(mat1, mat2, mat_size))

# test_naive_random()