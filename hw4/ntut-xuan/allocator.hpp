#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>

template <typename T>
class OurAllocator {
private:
    static int alloc_bytes;
    static int dealloc_bytes;
public:
    typedef T value_type;

    OurAllocator<T>(){
        // std::cout << "Construct allocator" << std::endl;
    }
    
    T* allocate(size_t n){
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)){
            throw std::bad_array_new_length();
        }
        alloc_bytes += sizeof(T) * n;
        // std::cout << "Allocate " << alloc_bytes - dealloc_bytes << " bytes" << std::endl;
        return new T[n];
    }
    void deallocate(T* p, std::size_t n) noexcept {
        dealloc_bytes += sizeof(T) * n;
        std::free(p);
    }

    static int bytes(){
        return alloc_bytes - dealloc_bytes;
    }

    static int allocated(){
        return alloc_bytes;
    }
    
    static int deallocated(){
        return dealloc_bytes;
    }
};

template<class T, class U>
bool operator==(const OurAllocator<T>&, const OurAllocator<U>&) { return true; }
 
template<class T, class U>
bool operator!=(const OurAllocator<T>&, const OurAllocator<U>&) { return false; }