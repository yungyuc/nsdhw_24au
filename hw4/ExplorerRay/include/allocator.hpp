#pragma once

#include <memory>
#include <iostream>
#include <limits>

// struct ByteCount {
//     size_t allocated;
//     size_t deallocated;
// };

template <class T>
class CustomAllocator {
public:
    using value_type = T;
    CustomAllocator();
    ~CustomAllocator();

    template<class U>
    constexpr CustomAllocator(const CustomAllocator<U>& other) noexcept;

    T* allocate(size_t);
    void deallocate(T*, size_t) noexcept;

    static size_t bytes();
    static size_t allocated();
    static size_t deallocated();

private:
    static size_t m_allocated;
    static size_t m_deallocated;
    // static ByteCount* m_byte_count;
}; /* end class CustomAllocator */

template <class T, class U>
bool operator==(const CustomAllocator<T> & a, const CustomAllocator<U> & b);

template <class T, class U>
bool operator!=(const CustomAllocator<T> & a, const CustomAllocator<U> & b);

template <class T>
std::ostream & operator << (std::ostream & out, const CustomAllocator<T> & alloc);

// refers to https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
#include "../src/allocator.tpp"
