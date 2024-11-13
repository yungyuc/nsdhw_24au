#ifndef _ALLOCATOR_HPP_
#define _ALLOCATOR_HPP_
#include <vector>
#include <memory>
#include <iostream>
using namespace std;


template<typename T>
class CustomAllocator{
public:
    using value_type = T;
    CustomAllocator() = default;
    bool operator==(const CustomAllocator& B) const { 
        if(total_bytes == B.bytes()){
            return true; 
        }else{
            return false;
        }
    }
    bool operator!=(const CustomAllocator& B) const {
        if(total_bytes != B.bytes()){
            return true;
        }else{
            return false;
        }
    }
    value_type* allocate(size_t n){
        size_t bytes = n * sizeof(value_type);
        allocated_bytes += bytes;
        total_bytes += bytes;
        return static_cast<value_type*>(::operator new(total_bytes));
    }

    void deallocate(value_type* p , size_t n){
        size_t bytes = n * sizeof(value_type);
        deallocated_bytes += bytes;
        total_bytes -= bytes;
        ::operator delete(p);
    }

    static std::size_t allocated() { return allocated_bytes; }
    static std::size_t deallocated() { return deallocated_bytes; }
    static std::size_t bytes() { return total_bytes; }
    
private:
    static inline std::size_t allocated_bytes = 0;
    static inline std::size_t deallocated_bytes = 0;
    static inline std::size_t total_bytes = 0;
};
#endif