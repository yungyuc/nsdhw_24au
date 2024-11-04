// CustomAllocator.hpp
#ifndef CUSTOM_ALLOCATOR_HPP
#define CUSTOM_ALLOCATOR_HPP

#include <cstddef>
#include <memory>
#include <iostream>

template <typename T>
class CustomAllocator {
public:
    using value_type = T;

    CustomAllocator() = default;
    template <class U> CustomAllocator(const CustomAllocator<U>&) noexcept {}

    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n) noexcept;

    static std::size_t getBytesInUse();
    static std::size_t getTotalAllocated();
    static std::size_t getTotalDeallocated();

private:
    static inline std::size_t bytes_in_use = 0;
    static inline std::size_t total_allocated = 0;
    static inline std::size_t total_deallocated = 0;
};

#include "CustomAllocator.cpp"
#endif // CUSTOM_ALLOCATOR_HPP
