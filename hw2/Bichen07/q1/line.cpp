#include "line.hpp"
#include <stdexcept>

// Default constructor
Line::Line() = default;

// Constructor with size
Line::Line(size_t size){
    x_coords.resize(size);
    y_coords.resize(size);  
}

// Copy constructor
Line::Line(Line const & line){
    x_coords = line.x_coords;
    y_coords = line.y_coords;
}

// // Move constructor
// Line::Line(Line&& line) noexcept 
//     : x_coords(std::move(line.x_coords)), y_coords(std::move(line.y_coords)) {}

// Copy assignment operator
Line& Line::operator=(const Line& line) {
    x_coords = line.x_coords;
    y_coords = line.y_coords;
    return *this;
}

// Destructor
Line::~Line() {}

// Return the number of points
size_t Line::size() const {
    return x_coords.size();
}

// get or set x-coordinate
float& Line::x(size_t index) {
    if (index >= x_coords.size()) throw std::out_of_range("Index out of range");
    return x_coords[index];
}

// get or set y-coordinate
float& Line::y(size_t index) {
    if (index >= y_coords.size()) throw std::out_of_range("Index out of range");
    return y_coords[index];
}
