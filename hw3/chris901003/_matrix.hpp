#pragma once

#include <vector>

using namespace std;

class Matrix {
    private:
    size_t m_nrow, m_ncol;
    double *data;
    public:
    Matrix(size_t nrow, size_t ncol);
    Matrix(size_t nrow, size_t ncol, double init);
    Matrix(size_t nrow, size_t ncol, vector<double> &init);
    Matrix(const Matrix &m);
    ~Matrix();

    size_t nrow() const;
    size_t ncol() const;
    size_t index(size_t i, size_t j) const;
    double* getData() const;
    vector<double> getVector() const;

    double operator()(size_t i, size_t j) const;
    double& operator()(size_t i, size_t j);
    bool operator==(const Matrix &m) const;
};