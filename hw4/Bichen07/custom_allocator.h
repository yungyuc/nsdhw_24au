#include <memory>
#include <iostream>
#include <limits> 

template <typename T>
class CustomAllocator {
public:
    using value_type = T;

    CustomAllocator() = default;

    template <class U>
    constexpr CustomAllocator(const CustomAllocator<U>& other) noexcept {
        m_allocated = other.m_allocated;
        m_deallocated = other.m_deallocated;
        m_refcount = other.m_refcount;
    }

    T *allocate(std::size_t n) {
        // Ensure the requested size is within safe limits
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
            throw std::bad_alloc();
        }

        const std::size_t bytes = n * sizeof(T);
        T *p = static_cast<T *>(std::malloc(bytes)); // Allocate memory

        if (!p) { // Check if allocation failed
            throw std::bad_alloc();
        }

        // Track allocated bytes
        m_allocated += bytes;
        return p;
    }

    void deallocate(T *p, std::size_t n) noexcept {
        if (p) {
            std::free(p); // Free memory
            const std::size_t bytes = n * sizeof(T);

            // Track deallocated bytes
            m_deallocated += bytes;
        }
    }


    static std::size_t bytes() { return m_allocated - m_deallocated; }
    static std::size_t allocated() { return m_allocated; }
    static std::size_t deallocated() { return m_deallocated; }
    static std::size_t refcount() { return m_refcount; }
    // static std::size_t m_allocated;

private:
    static std::size_t m_allocated;
    static std::size_t m_deallocated;
    static std::size_t m_refcount;
};
template <class T> std::size_t CustomAllocator<T>::m_allocated = 0;
template <class T> std::size_t CustomAllocator<T>::m_deallocated = 0;
template <class T> std::size_t CustomAllocator<T>::m_refcount = 0;

template <class T, class U>
bool operator==(const CustomAllocator<T> & a, const CustomAllocator<U> & b)
{
    if (a.allocated() != b.allocated()) { return false; }
    if (a.deallocated() != b.deallocated()) { return false; }
    if (a.refcount() != b.refcount()) { return false; }
    return true;
}

template <class T, class U>
bool operator!=(const CustomAllocator<T> & a, const CustomAllocator<U> & b)
{
    return !(a == b);
}