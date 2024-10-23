import pytest
import math
import _matrix
import time

def test_matrix_oop():
    mat1 = _matrix.Matrix(2, 2)
    mat4 = _matrix.Matrix(1000, 1000)
    assert(mat1.nrow == mat1.ncol == 2)
    assert(mat4.nrow == mat4.ncol == 1000)
    arr = [1, 0, 0, 1]
    mat3 = _matrix.Matrix(2, 2, arr)
    for i in range(mat3.nrow):
        for j in range(mat3.ncol):
            assert(arr[i*mat3.nrow+j] == mat3[i, j])
    mat4 = mat1 + mat3
    assert(mat4 == mat3)

def test_mul():
    mat1 = _matrix.Matrix(1000, 1000)
    mat2 = _matrix.Matrix(1000, 1000)
    for i in range(1000):
        for j in range(1000):
            mat1[i,j] = 1.0
            mat2[i,j] = 2.0
    mat_naive = _matrix.multiply_naive(mat1, mat2)
    mat_tile = _matrix.multiply_tile(mat1, mat2, 32)
    mat_mkl = _matrix.multiply_mkl(mat1, mat2)
    for i in range(1000):
        for j in range(1000):
            assert(mat_naive[i,j] == 2000)   
            assert(mat_tile[i,j] == 2000) 
            assert(mat_mkl[i,j] == 2000) 

def performance_comp(matrix_size = 1024, epoch = 10):
    size = matrix_size
    total_epoch = epoch
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)
    for i in range(size):
        for j in range(size):
            mat1[i,j] = 1.0
            mat2[i,j] = 2.0
    
    naive_total_time = 0
    tile_total_time = 0
    mkl_total_time = 0

    for idx, s in enumerate(["naive_multiplex", "tile_multiplex", "mkl_multiplex"]):
        for i in range(total_epoch):
            total = 0
            if(idx == 0):
                start = time.process_time()
                mattemp = _matrix.multiply_naive(mat1, mat2)
                end = time.process_time()
                total = end - start
                naive_total_time += total

            if(idx == 1):
                start = time.process_time()
                mattemp = _matrix.multiply_tile(mat1, mat2, 64)
                end = time.process_time()
                total = end - start
                tile_total_time += total

            if(idx == 2):
                start = time.process_time()
                mattemp = _matrix.multiply_mkl(mat1, mat2)
                end = time.process_time()
                total = end - start
                mkl_total_time += total

            print(s," for epoch ",i, " : ", total,"s")
            
        

    naive_total_time /= total_epoch
    tile_total_time /= total_epoch
    mkl_total_time /= total_epoch

    print("Average time for naive_multiplex with matrix size", size, "*",size,": ", naive_total_time,"s")                
    print("Average time for tile_multiplex with matrix size", size, "*",size,": ", tile_total_time,"s") 
    print("Average time for mkl_multiplex with matrix size", size, "*",size,": ", mkl_total_time,"s") 
    print("Tile is ",naive_total_time/tile_total_time, " times faster than naive.")
    print("Mkl is ",naive_total_time/mkl_total_time, " times faster than naive.")

if __name__ == '__main__':
    performance_comp(1024, 1)