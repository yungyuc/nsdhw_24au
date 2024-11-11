#pragma once
#include<vector>
#include<iostream>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

template <class T>
class CustomAllocator
{
    public:
    typedef T value_type;
        CustomAllocator() = default;
        ~CustomAllocator() = default;
        static size_t get_current() { return current; }
        static size_t get_allocated() { return allocated; }
        static size_t get_deallocated() { return deallocated; }
        T* allocate(size_t n, const void* hint=0)
        {
            current += n*sizeof(T);
            allocated += n*sizeof(T);
            std::allocator<T> alloc;
            return alloc.allocate(n, hint);
        }
        void deallocate(T* p, size_t n) noexcept
        {
            current -= n*sizeof(T);
            deallocated += n*sizeof(T);
            std::allocator<T> alloc;
            alloc.deallocate(p, n);
        }
    private:
        static size_t current;
        static size_t allocated;
        static size_t deallocated;
};

class Matrix{
    public:
        Matrix(size_t _row, size_t _col);
        ~Matrix() = default;
        size_t get_row() const { return this->nrow; };
        size_t get_col() const { return this->ncol; };
        double operator() (int i, int j) const { return buffer.data()[i * ncol + j]; };
        double& operator() (int i, int j) { return buffer.data()[i * ncol + j]; };
        Matrix(Matrix&& other) noexcept : nrow(other.nrow), ncol(other.ncol), buffer(std::move(other.buffer)){
            other.nrow = 0;
            other.ncol = 0;
        };
        bool operator==(Matrix const &mat1){
            if (this->nrow != mat1.nrow || this->ncol != mat1.ncol)
                return false;
            for (size_t i = 0; i < mat1.nrow; ++i)
            {
                for (size_t j = 0; j < mat1.ncol; ++j)
                {
                    if (this->buffer.data()[i*this->ncol+j] != mat1(i, j))
                        return false;
                }
            }
            return true;
        };
        size_t nrow, ncol;
        double* buffer_ref() const { return const_cast<double*>(buffer.data()); };
    private:
        //double* buffer;
        std::vector<double, CustomAllocator<double>> buffer;
};