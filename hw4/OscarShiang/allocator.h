#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <atomic>
#include <ostream>
#include <stdexcept>

template <class T>
struct CustomAllocator
{
    using value_type = T;

    CustomAllocator()
    {
        allocated = 0;
        deallocated = 0;
        refcnt = 0;
    }

    T *allocate(size_t n)
    {
        size_t bytes = n * sizeof(T);
        m_buf = static_cast<T *>(std::malloc(bytes));
        if (!m_buf) {
            throw std::bad_alloc();
        }

        allocated += bytes;
        return m_buf;
    }

    void deallocate(T *ptr, size_t n) noexcept
    {
        if (ptr) {
            size_t bytes = n * sizeof(T);
            std::free(ptr);
            deallocated += bytes;
            if (ptr == m_buf) {
                m_buf = NULL;
            }
        }
    }

    T *m_buf = NULL;

    size_t allocated = 0;
    size_t deallocated = 0;
    size_t refcnt = 0;
};

#endif /* __ALLOCATOR_H__ */
