# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3 -fPIC

# Pybind11
PYBIND11_INCLUDE = $(shell python3 -m pybind11 --includes)

# Linker flags for MKL (Intel Math Kernel Library)
MKLFLAGS = -lmkl_rt -lpthread -lm -ldl

# Target
TARGET = _matrix.so

# Source files
source = _matrix.cpp _matrix.hpp

# Run the Python tests using pytest
test: ${TARGET}
	python3 -m pytest test_matrix.py

# Compile
all: $(TARGET)

$(TARGET): $(source)
	$(CXX) $(CXXFLAGS) $(PYBIND11_INCLUDE) -shared -o $(TARGET) $(source) $(MKLFLAGS)

clean:
	rm -f $(TARGET)
