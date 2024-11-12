#include <vector>
#include <algorithm>
#include <cstring>
#include <memory>
#include <atomic>
#include <stdexcept>

// Global counters for memory tracking
struct MemoryStats {
    static std::atomic<size_t> current_bytes;
    static std::atomic<size_t> total_allocated;
    static std::atomic<size_t> total_deallocated;
};

std::atomic<size_t> MemoryStats::current_bytes(0);
std::atomic<size_t> MemoryStats::total_allocated(0);
std::atomic<size_t> MemoryStats::total_deallocated(0);

template <typename T>
class MemoryTrackingAllocator {
public:
    using value_type = T;
    
    MemoryTrackingAllocator() noexcept = default;
    
    template <typename U>
    MemoryTrackingAllocator(const MemoryTrackingAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        size_t bytes = n * sizeof(T);
        MemoryStats::current_bytes += bytes;
        MemoryStats::total_allocated += bytes;
        return static_cast<T*>(::operator new(bytes));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        size_t bytes = n * sizeof(T);
        MemoryStats::current_bytes -= bytes;
        MemoryStats::total_deallocated += bytes;
        ::operator delete(p);
    }
};

template <typename T, typename U>
bool operator==(const MemoryTrackingAllocator<T>&, const MemoryTrackingAllocator<U>&) { return true; }

template <typename T, typename U>
bool operator!=(const MemoryTrackingAllocator<T>&, const MemoryTrackingAllocator<U>&) { return false; }

class Matrix {
private:
    std::vector<double, MemoryTrackingAllocator<double>> data;
    size_t rows, cols;

public:
    Matrix(size_t r, size_t c) : data(r * c, 0.0), rows(r), cols(c) {}

    // Copy constructor
    Matrix(const Matrix& other) : data(other.data), rows(other.rows), cols(other.cols) {}

    // Move constructor
    Matrix(Matrix&& other) noexcept 
        : data(std::move(other.data)), rows(other.rows), cols(other.cols) {
        other.rows = other.cols = 0;
    }

    // Copy assignment operator
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            data = other.data;
            rows = other.rows;
            cols = other.cols;
        }
        return *this;
    }

    // Move assignment operator
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            rows = other.rows;
            cols = other.cols;
            other.rows = other.cols = 0;
        }
        return *this;
    }

    double& operator()(size_t i, size_t j) {
        if (i >= rows || j >= cols) throw std::out_of_range("Matrix index out of range");
        return data[i * cols + j];
    }

    const double& operator()(size_t i, size_t j) const {
        if (i >= rows || j >= cols) throw std::out_of_range("Matrix index out of range");
        return data[i * cols + j];
    }

    bool operator==(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) return false;
        return data == other.data;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    size_t get_rows() const { return rows; }
    size_t get_cols() const { return cols; }
    const double* get_data() const { return data.data(); }
    double* get_data() { return data.data(); }
};