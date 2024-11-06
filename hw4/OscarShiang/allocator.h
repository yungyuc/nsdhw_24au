#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <atomic>
#include <ostream>
#include <stdexcept>

template <class T>
struct CustomAllocator
{
    using value_type = T;

    CustomAllocator() = default;

    T *allocate(size_t n)
    {
        size_t size = n * sizeof(T);
        m_buf = static_cast<T *>(std::malloc(size));
        if (!m_buf) {
            throw std::bad_alloc();
        }
        m_allocated += size;
        return m_buf;
    }

    void deallocate(T *ptr, size_t n) noexcept
    {
        size_t size = n * sizeof(T);
        if (ptr) {
            std::free(ptr);
            if (ptr == m_buf) {
                m_buf = NULL;
            }
        }
        m_deallocated += size;
    }

    T *m_buf = NULL;

    static size_t allocated() { return m_allocated; }
    static size_t deallocated() { return m_deallocated; }
    static size_t bytes() { return m_allocated - m_deallocated; }

    static std::atomic_size_t m_allocated;
    static std::atomic_size_t m_deallocated;
    static std::atomic_size_t m_refcnt;
};

template <class T> std::atomic_size_t CustomAllocator<T>::m_allocated(0);
template <class T> std::atomic_size_t CustomAllocator<T>::m_deallocated(0);
template <class T> std::atomic_size_t CustomAllocator<T>::m_refcnt(0);

#endif /* __ALLOCATOR_H__ */
