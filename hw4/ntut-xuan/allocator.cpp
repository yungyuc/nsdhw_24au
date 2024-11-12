#include "allocator.hpp"

template<> int OurAllocator<double>::alloc_bytes = 0;
template<> int OurAllocator<double>::dealloc_bytes = 0;