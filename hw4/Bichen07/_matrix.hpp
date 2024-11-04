// Matrix.hpp
#include "CustomAllocator.hpp"
#include <vector>

class Matrix {
private:
    size_t m_nrow, m_ncol;
    std::vector<double, CustomAllocator<double>> data;  // Replace double* with std::vector

public:
    Matrix(size_t nrow, size_t ncol);
    Matrix(const Matrix &);
    Matrix &operator=(const Matrix &);
    ~Matrix();

    size_t nrow() const;
    size_t ncol() const;
    double &operator()(size_t row, size_t col);
    const double &operator()(size_t row, size_t col) const;

    bool operator==(const Matrix &other) const;
};
