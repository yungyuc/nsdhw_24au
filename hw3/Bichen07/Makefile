# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3 -fPIC `python3 -m pybind11 --includes`

# Intel MKL paths (adjust if needed)
MKL_INCLUDE_PATH = /usr/include/mkl
MKL_LIB_PATH = /usr/lib/x86_64-linux-gnu

# Linker flags for MKL
MKLFLAGS = -L$(MKL_LIB_PATH) -lmkl_rt -lpthread -lm -ldl

# Target
TARGET = _matrix.so

# Source files
source = _matrix.cpp _matrix.hpp

# Run the Python tests using pytest
test: $(TARGET)
    python3 -m pytest test_matrix.py

# Compile
all: $(TARGET)

$(TARGET): $(source)
    $(CXX) $(CXXFLAGS) -I$(MKL_INCLUDE_PATH) `python3-config --includes --ldflags` -o $(TARGET) $(source) $(MKLFLAGS)

clean:
    rm -rf *.so __pycache__ .pytest*
