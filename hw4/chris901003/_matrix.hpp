#pragma once

#include <vector>
#include <cstdint>

using namespace std;

template<typename T>
class CustomAllocator: public std::allocator<T> {
    public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;
    
    template<typename U>
    struct rebind {
        typedef CustomAllocator<U> other;
    };

    CustomAllocator() = default;

    template <typename U>
    CustomAllocator(const CustomAllocator<U>&) {}

    ~CustomAllocator() = default;

    pointer allocate(size_type n, const void* hint = 0) {
        current_allocated += n * sizeof(T);
        allocated_bytes += n * sizeof(T);
        return std::allocator<T>::allocate(n, hint);

    }

    void deallocate(pointer p, size_type n) noexcept {
        current_allocated -= n * sizeof(T);
        deallocated_bytes += n * sizeof(T);
        std::allocator<T>::deallocate(p, n);
    }

    static size_t get_current_allocated() {
        return current_allocated;
    }

    static size_t get_allocated_bytes() {
        return allocated_bytes;
    }

    static size_t get_deallocated_bytes() {
        return deallocated_bytes;
    }
    

    private:
    static size_t allocated_bytes;
    static size_t deallocated_bytes;
    static size_t current_allocated;
};

template<typename T>
size_t CustomAllocator<T>::current_allocated = 0;

template<typename T>
size_t CustomAllocator<T>::allocated_bytes = 0;

template<typename T>
size_t CustomAllocator<T>::deallocated_bytes = 0;

class Matrix {
    private:
    size_t m_nrow, m_ncol;
    vector<double, CustomAllocator<double>> m_buffer;
    public:
    Matrix(size_t nrow, size_t ncol);
    Matrix(size_t nrow, size_t ncol, double init);
    Matrix(size_t nrow, size_t ncol, vector<double, CustomAllocator<double>> &init);
    Matrix(Matrix       &&);
    ~Matrix();

    size_t nrow() const;
    size_t ncol() const;
    size_t index(size_t i, size_t j) const;
    double* getData() const;

    double* buffer();
    const double* buffer() const;

    double operator()(size_t i, size_t j) const;
    double& operator()(size_t i, size_t j);
    bool operator==(const Matrix &m) const;
};