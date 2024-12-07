#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class Matrix {
private:
    double* data;
    size_t rows, cols;

public:
    // Constructor
    Matrix(size_t r, size_t c) : rows(r), cols(c) {
        data = new double[r * c]();  // Zero-initialize
    }

    // Copy constructor
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new double[rows * cols];
        std::copy(other.data, other.data + (rows * cols), data);
    }

    // Move constructor
    Matrix(Matrix&& other) noexcept : data(other.data), rows(other.rows), cols(other.cols) {
        other.data = nullptr;
        other.rows = other.cols = 0;
    }

    // Destructor
    ~Matrix() {
        delete[] data;
    }

    // Copy assignment operator
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            delete[] data;
            rows = other.rows;
            cols = other.cols;
            data = new double[rows * cols];
            std::copy(other.data, other.data + (rows * cols), data);
        }
        return *this;
    }

    // Move assignment operator
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            rows = other.rows;
            cols = other.cols;
            other.data = nullptr;
            other.rows = other.cols = 0;
        }
        return *this;
    }

    // Accessor methods matching mod.cpp expectations
    size_t nrow() const { return rows; }
    size_t ncol() const { return cols; }

    // Element access operator
    double& operator()(size_t i, size_t j) {
        if (i >= rows || j >= cols) throw std::out_of_range("Matrix index out of range");
        return data[i * cols + j];
    }

    const double& operator()(size_t i, size_t j) const {
        if (i >= rows || j >= cols) throw std::out_of_range("Matrix index out of range");
        return data[i * cols + j];
    }

    // Comparison operators
    bool operator==(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) return false;
        return std::memcmp(data, other.data, rows * cols * sizeof(double)) == 0;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    // For internal use by multiplication functions
    const double* get_data() const { return data; }
    double* get_data() { return data; }
};

// Explicit function declarations for multiplication functions
Matrix multiply_mkl(const Matrix& A, const Matrix& B);
Matrix multiply_naive(const Matrix& A, const Matrix& B);
Matrix multiply_tile(const Matrix& A, const Matrix& B, size_t tile_size = 32);

PYBIND11_MODULE(_matrix, m) {
    // Bind the Matrix class
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def(py::init<const Matrix&>())
        
        // Use properties instead of methods
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        
        // Python-style indexing support
        .def("__getitem__", 
            [](Matrix& self, py::tuple key) {
                if (py::len(key) != 2)
                    throw std::invalid_argument("Indexing requires exactly two indices");
                size_t i = key[0].cast<size_t>();
                size_t j = key[1].cast<size_t>();
                return self(i, j);
            })
        .def("__setitem__", 
            [](Matrix& self, py::tuple key, double value) {
                if (py::len(key) != 2)
                    throw std::invalid_argument("Indexing requires exactly two indices");
                size_t i = key[0].cast<size_t>();
                size_t j = key[1].cast<size_t>();
                self(i, j) = value;
            })
        
        // Proper equality comparison
        .def("__eq__", 
            [](const Matrix& self, const Matrix& other) {
                if (self.nrow() != other.nrow() || self.ncol() != other.ncol())
                    return false;
                
                for (size_t i = 0; i < self.nrow(); ++i) {
                    for (size_t j = 0; j < self.ncol(); ++j) {
                        if (std::abs(self(i, j) - other(i, j)) > 1e-9)
                            return false;
                    }
                }
                return true;
            })
        .def("__ne__", 
            [](const Matrix& self, const Matrix& other) {
                return !(self == other);
            })
        
        // NumPy array conversion
        .def_property_readonly("array", 
            [](const Matrix& self) {
                return py::array_t<double>({self.nrow(), self.ncol()}, 
                                           {self.ncol() * sizeof(double), sizeof(double)}, 
                                           self.get_data(),
                                           py::cast(self));
            });

    // Expose multiplication functions at module level
    m.def("multiply_naive", &multiply_naive, 
          "Naive matrix multiplication", 
          py::arg("A"), py::arg("B"));
    
    m.def("multiply_tile", 
          [](const Matrix& A, const Matrix& B, size_t tile_size = 32) {
              return multiply_tile(A, B, tile_size);
          }, 
          "Tiled matrix multiplication", 
          py::arg("A"), py::arg("B"), py::arg("tile_size") = 32);
    
    m.def("multiply_mkl", &multiply_mkl, 
          "MKL matrix multiplication", 
          py::arg("A"), py::arg("B"));
}
