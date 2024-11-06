#include <iostream>
#include <iomanip>
#include <atomic>
#include <vector>
#include <stdexcept>
#include <limits>
#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>


/* ByteCounter (Many Allocators use the same ByteCounter) */
class ByteCounter {

public:
    
    ByteCounter() = default;
    ByteCounter & operator=(ByteCounter const * other);

    void increase(int bytes);
    void decrease(int bytes);
    int allocated() const;
    int deallocated() const;

private:

    int m_allocated = 0;
    int m_deallocated = 0;

}; /* end class ByteCounter */

bool operator==(ByteCounter const & a, ByteCounter const & b);


template <class T>
struct MyAllocator {

    using value_type = T;

    MyAllocator();
    MyAllocator(ByteCounter *byte_counter);

    template <class U>
    constexpr MyAllocator(const MyAllocator<U>& other) noexcept;

    T * allocate(std::size_t n);
    void deallocate(T* p, std::size_t n) noexcept;

    ByteCounter *byte_counter;

}; /* end struct MyAllocator */

template <class T>
bool operator== (const MyAllocator<T>& a, const MyAllocator<T>& b);

template <class T>
bool operator!= (const MyAllocator<T>& a, const MyAllocator<T>& b);

static ByteCounter *byte_counter = new ByteCounter;
static MyAllocator<double> alloc(byte_counter);

class Matrix {

public:
    /* Member variable */
    size_t nrow = 0;
    size_t ncol = 0;
    std::vector<double, MyAllocator<double>> data = std::vector<double, MyAllocator<double>>(alloc);

    Matrix(size_t num_row, size_t num_col);
    Matrix(size_t num_row, size_t num_col, std::vector<double> const & vec);

    Matrix & operator=(std::vector<double> const & vec);
    bool operator==(const Matrix &m) const;

    /* copy constructor */
    Matrix(Matrix const & other);

    /* copy assignment operator */
    Matrix & operator=(Matrix const & other);

    /* move constructor */
    Matrix(Matrix && other);

    /* move assignment operator */
    Matrix & operator=(Matrix && other);

    /* Destructor */
    ~Matrix();

    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);

    // void reset_buffer(size_t nrow, size_t ncol);

};

std::ostream & operator << (std::ostream & ostr, Matrix const & mat);

/* Allocator function */
int bytes();
int allocated();
int deallocated();

/* Naive matrix matrix multiplication */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2);

/* Matrix matrix multiplication using tiling */
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t tile_size);


/* Matrix matrix multiplication using DGEMM */
Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2);