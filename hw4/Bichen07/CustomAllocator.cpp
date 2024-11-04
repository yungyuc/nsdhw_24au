// CustomAllocator.cpp
#include "CustomAllocator.hpp"

template <typename T>
T* CustomAllocator<T>::allocate(std::size_t n) {
    std::size_t bytes = n * sizeof(T);
    bytes_in_use += bytes;
    total_allocated += bytes;
    return static_cast<T*>(::operator new(bytes));
}

template <typename T>
void CustomAllocator<T>::deallocate(T* p, std::size_t n) noexcept {
    std::size_t bytes = n * sizeof(T);
    bytes_in_use -= bytes;
    total_deallocated += bytes;
    ::operator delete(p);
}

template <typename T>
std::size_t CustomAllocator<T>::getBytesInUse() {
    return bytes_in_use;
}

template <typename T>
std::size_t CustomAllocator<T>::getTotalAllocated() {
    return total_allocated;
}

template <typename T>
std::size_t CustomAllocator<T>::getTotalDeallocated() {
    return total_deallocated;
}

// Template instantiation for double, so we don't need to define methods in header
template class CustomAllocator<double>;
