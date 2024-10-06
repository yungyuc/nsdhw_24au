#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <cmath>
#include <stdexcept>

// Function to calculate the angle between two 2D vectors
double calculate_angle(double x1, double y1, double x2, double y2) {
    // Calculate dot product
    double dot_product = x1 * x2 + y1 * y2;
    
    // Calculate magnitudes
    double magnitude_a = std::sqrt(x1 * x1 + y1 * y1);
    double magnitude_b = std::sqrt(x2 * x2 + y2 * y2);
    
    // Check if any vector is zero, which would make the angle undefined
    if (magnitude_a == 0 || magnitude_b == 0) {
        throw std::invalid_argument("One of the vectors has zero length.");
    }
    
    // Calculate the cosine of the angle
    double cos_theta = dot_product / (magnitude_a * magnitude_b);
    
    // Clamp value between -1 and 1 to handle floating-point precision issues
    cos_theta = std::max(-1.0, std::min(1.0, cos_theta));
    
    // Return the angle in radians
    return std::acos(cos_theta);
}

// Pybind11 wrapper
namespace py = pybind11;

PYBIND11_MODULE(_vector, m) {
    m.def("calculate_angle", &calculate_angle, "A function that calculates the angle between two 2D vectors");
}
