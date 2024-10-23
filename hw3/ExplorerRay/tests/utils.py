from _matrix import Matrix
import random

def generate_matrix_2d(nrow, ncol):
    # use random to create matrix
    mat = Matrix(nrow, ncol)
    for i in range(nrow):
        for j in range(ncol):
            mat[i,j] = random.randint(0, 100)
    
    return mat
        

