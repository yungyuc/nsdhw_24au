#pragma once
#include<vector>
#include<iostream>
#include<mkl.h>

class Matrix{
    public:
        Matrix(size_t _row, size_t _col);
        ~Matrix();
        size_t get_row() const { return this->nrow(); };
        size_t get_col() const { return this->ncol(); };
        size_t nrow() const { return this->nrow_num; };
        size_t ncol() const { return this->ncol_num; };
        double operator() (int i, int j) const { return buffer[i * ncol() + j]; };
        double& operator() (int i, int j) { return buffer[i * ncol() + j]; };
        Matrix(Matrix&& other) noexcept : nrow_num(other.nrow()), ncol_num(other.ncol()), buffer(other.buffer){
            other.buffer = nullptr;
        };
        Matrix & operator=(Matrix && other){
            if (this == &other) { return *this; }
            delete[] buffer;
            nrow_num = other.nrow();
            ncol_num = other.ncol();
            buffer = other.buffer;
            other.buffer = nullptr;
            return *this;
        };
        bool operator==(Matrix const &mat1) const{
            if (this->nrow() != mat1.nrow() || this->ncol() != mat1.ncol())
                return false;
            for (size_t i = 0; i < mat1.nrow(); ++i)
            {
                for (size_t j = 0; j < mat1.ncol(); ++j)
                {
                    if (this->buffer[i*this->ncol()+j] != mat1(i, j))
                        return false;
                }
            }
            return true;
        };
        size_t nrow_num, ncol_num;
        double* buffer_ref() const { return this->buffer; };
    private:
        double* buffer;
};

Matrix multiply_naive(const Matrix &A, const Matrix &B);
Matrix multiply_mkl(const Matrix &A, const Matrix &B);
Matrix multiply_tile(const Matrix &A, const Matrix &B, size_t tile_size);