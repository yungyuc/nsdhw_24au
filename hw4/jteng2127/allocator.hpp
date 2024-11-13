#pragma once

#include<cstddef>
#include<cstdlib>
#include<iostream>

template <typename T>
class CustomAllocator {
public:
  using value_type = T;

  CustomAllocator() = default;
  template <class U> constexpr
  CustomAllocator(const CustomAllocator<U>&) noexcept {}

  T* allocate(std::size_t n) {
    const std::size_t bytes = n * sizeof(T);
    allocated_bytes += bytes;
    total_bytes += bytes;
    return static_cast<T*>(std::calloc(n, sizeof(T)));
  }

  void deallocate(T* p, std::size_t n) {
    std::free(p);
    std::size_t bytes = n * sizeof(T);
    deallocated_bytes += bytes;
    total_bytes -= bytes;
  }

  static std::size_t bytes() { return allocated_bytes - deallocated_bytes; }
  static std::size_t allocated() { return allocated_bytes; }
  static std::size_t deallocated() { return deallocated_bytes; }

private:
  static inline std::size_t total_bytes = 0;
  static inline std::size_t allocated_bytes = 0;
  static inline std::size_t deallocated_bytes = 0;
};