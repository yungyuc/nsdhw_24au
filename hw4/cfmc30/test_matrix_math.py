import _matrix

def test_matrix_operations():
    # Create two matrices (2x2) and initialize their values
    mat1 = _matrix.Matrix(2, 2)
    mat2 = _matrix.Matrix(2, 2)

    # Initialize mat1
    mat1[0, 0] = 1.0
    mat1[0, 1] = 2.0
    mat1[1, 0] = 3.0
    mat1[1, 1] = 4.0

    # Initialize mat2
    mat2[0, 0] = 5.0
    mat2[0, 1] = 6.0
    mat2[1, 0] = 7.0
    mat2[1, 1] = 8.0

    # Naive multiplication test
    result_naive = mat1.multiply_naive(mat1, mat2)
    
    print("Result of Naive Multiplication:")
    for i in range(2):
        for j in range(2):
            print(result_naive[i, j], end=" ")
        print()

    # Tile-based multiplication test (tile size of 1)
    result_tile = mat1.multiply_tile(mat1, mat2, 1)
    
    print("\nResult of Tile Multiplication:")
    for i in range(2):
        for j in range(2):
            print(result_tile[i, j], end=" ")
        print()

if __name__ == "__main__":
    test_matrix_operations()
