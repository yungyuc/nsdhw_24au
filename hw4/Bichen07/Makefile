# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -shared -fPIC $(shell python3 -m pybind11 --includes)
LDFLAGS = $(shell python3-config --ldflags)
TARGET = _matrix$(shell python3-config --extension-suffix)

MKL_INCLUDE_PATH = /usr/include/mkl


# Build target
all: $(TARGET)

# Compile shared library with custom allocator
$(TARGET): _matrix.cpp custom_allocator.h
	$(CXX) $(CXXFLAGS) -I$(MKL_INCLUDE_PATH) `python3-config --includes --ldflags` -o $@ $^ $(LDFLAGS) -lblas -lmkl_rt

# Run tests with pytest in verbose mode
test: $(TARGET)
	python3 -m pytest -v test_matrix.py

# Clean up generated files and cache directories
clean:
	rm -f $(TARGET) *.o
	rm -rf __pycache__ .pytest_cache
