#pragma once
#include <stdexcept>
#include <cstddef>

using namespace std;

class Matrix{

    private:
    size_t m_nrow, m_ncol;
    double *data;

    /* basic operations of matrix*/
    public:
    Matrix(size_t nrow, size_t ncol); // initialize Matrix value = 0
    Matrix(size_t nrow, size_t ncol, double init); // assign same value for each elements in matrix
    Matrix(Matrix const & ); // copy constructor
    Matrix & operator=(Matrix const & ); // copy assignment operator.
    ~Matrix(); // Desctructor

    /* get information operations of matrix*/
    size_t nrow() const;
    size_t ncol() const;
    size_t index(size_t i, size_t j) const;
    double* getData() const;

    // Overload operator to access elements
    double operator()(size_t i, size_t j) const;
    double& operator()(size_t i, size_t j);

    bool operator==(const Matrix &other) const; // Compare matrices
};
