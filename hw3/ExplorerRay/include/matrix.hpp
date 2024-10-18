#include <cstdio>
#include <algorithm>

class matrix_2d {
public:
    matrix_2d() = delete;
    matrix_2d(size_t nrow, size_t ncol);
    matrix_2d(matrix_2d const &m) = default;
    matrix_2d(matrix_2d &&m) = default;
    matrix_2d &operator=(matrix_2d const &m) = default;
    matrix_2d &operator=(matrix_2d &&m) = default;
    ~matrix_2d();

    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);

    matrix_2d & transpose();

    size_t index(size_t row, size_t col) const;
    bool is_transposed() const;

    // matrix_2d &operator=(const matrix_2d &m);
    // double *operator[](int i);
    // const double *operator[](int i) const;
    size_t get_nrow() const;
    size_t get_ncol() const;
    
private:
    size_t m_nrow;
    size_t m_ncol;
    double *m_buffer;
    bool m_transpose = false;
};
