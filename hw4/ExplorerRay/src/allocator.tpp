template <class T>
size_t CustomAllocator<T>::m_allocated = 0;
template <class T>
size_t CustomAllocator<T>::m_deallocated = 0;

template <class T>
CustomAllocator<T>::CustomAllocator() = default;
template <class T>
CustomAllocator<T>::~CustomAllocator() = default;

template <class T>
template <class U>
constexpr CustomAllocator<T>::CustomAllocator(const CustomAllocator<U>& other) noexcept {
    m_allocated = other.m_allocated;
    m_deallocated = other.m_deallocated;
}

template <class T>
T* CustomAllocator<T>::allocate(size_t n) {
    if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
        throw std::bad_alloc();
    }
    const size_t size = n * sizeof(T);

    T* p = static_cast<T*>(std::malloc(size));

    if (p) {
        m_allocated += size;
        return p;
    }
    else {
        throw std::bad_alloc();
    }
}

template <class T>
void CustomAllocator<T>::deallocate(T* p, size_t n) noexcept {
    m_deallocated += n * sizeof(T);
    std::free(p);
}

template <class T>
size_t CustomAllocator<T>::bytes() {
    return m_allocated - m_deallocated;
}
template <class T>
size_t CustomAllocator<T>::allocated() {
    return m_allocated;
}
template <class T>
size_t CustomAllocator<T>::deallocated() {
    return m_deallocated;
}

template <class T, class U>
bool operator==(const CustomAllocator<T> & a, const CustomAllocator<U> & b) {
    bool allo = a.m_allocated == b.m_allocated;
    bool deallo = a.m_deallocated == b.m_deallocated;
    return allo && deallo;
}

template <class T, class U>
bool operator!=(const CustomAllocator<T> & a, const CustomAllocator<U> & b) {
    return !(a == b);
}

template <class T>
std::ostream & operator << (std::ostream & out, const CustomAllocator<T> & alloc) {
    out << "allocator: bytes = " << alloc.bytes();
    out << " allocated = " << alloc.allocated();
    out << " deallocated = " << alloc.deallocated();
    return out;
}
