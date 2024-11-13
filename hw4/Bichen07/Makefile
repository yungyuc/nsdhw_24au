# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -shared -fPIC $(shell python3 -m pybind11 --includes)
# Target shared library
TARGET = _matrix$(shell python3-config --extension-suffix)  # _matrix.so (or appropriate suffix)


LDFLAGS = $(shell python3-config --includes --ldflags)
MKL_INCLUDE_PATH = -I /usr/include/mkl

# Source files
source = _matrix.cpp custom_allocator.h

# Build target
all: $(TARGET)

# Compile shared library with custom allocator
$(TARGET): $(source)
	$(CXX) $(CXXFLAGS) $(MKL_INCLUDE_PATH) ${LDFLAGS} -o $(TARGET) $(source) -lblas -lmkl_rt

# Run tests with pytest in verbose mode
test: $(TARGET)
	python3 -m pytest -v test_matrix.py

# Clean up generated files and cache directories
clean:
	rm -f $(TARGET) *.o
	rm -rf __pycache__ .pytest_cache
