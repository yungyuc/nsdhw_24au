#include <iostream>
#include <cmath>
#include <utility>
#include <pybind11/pybind11.h>

double angleBetweenVectors(std::pair<float, float> A, std::pair<float, float> B) {
    double dotProduct = A.first * B.first + A.second * B.second;
    double magnitudeA = std::sqrt(A.first * A.first + A.second * A.second);
    double magnitudeB = std::sqrt(B.first * B.first + B.second * B.second);
    if (magnitudeA == 0.0 || magnitudeB == 0.0) {
        throw std::invalid_argument("Error: One of the vectors has zero magnitude.");
    }
    double cosTheta = dotProduct / (magnitudeA * magnitudeB);
    cosTheta = std::fmax(-1.0, std::fmin(1.0, cosTheta));
    return std::acos(cosTheta);
}

PYBIND11_MODULE(_vector, m) {
    m.doc() = "Module for vector operations";
    m.def("angleBetweenVectors", &angleBetweenVectors, "Calculate the angle between two vectors");
}
