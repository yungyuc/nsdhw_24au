#include<vector>
#include<iostream>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

class Matrix{
    public:
        Matrix(size_t _row, size_t _col);
        ~Matrix();
        size_t get_row() const { return this->nrow; };
        size_t get_col() const { return this->ncol; };
        double operator() (int i, int j) const { return buffer[i * ncol + j]; };
        double& operator() (int i, int j) { return buffer[i * ncol + j]; };
        Matrix(Matrix&& other) noexcept : nrow(other.nrow), ncol(other.ncol), buffer(other.buffer){
            other.buffer = nullptr;
        };
        Matrix & operator=(Matrix && other){
            if (this == &other) { return *this; }
            delete[] buffer;
            nrow = other.nrow;
            ncol = other.ncol;
            buffer = other.buffer;
            other.buffer = nullptr;
            return *this;
        };
        bool operator==(Matrix const &mat1){
            if (this->nrow != mat1.nrow || this->ncol != mat1.ncol)
                return false;
            for (size_t i = 0; i < mat1.nrow; ++i)
            {
                for (size_t j = 0; j < mat1.ncol; ++j)
                {
                    if (this->buffer[i*this->ncol+j] != mat1(i, j))
                        return false;
                }
            }
            return true;
        };
        size_t nrow, ncol;
        double* buffer_ref() const { return this->buffer; };
    private:
        double* buffer;
};