# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3 -shared -fPIC `python3 -m pybind11 --includes`

MKL_INCLUDE_PATH = /usr/include/mkl

# Target
TARGET = _matrix.so

# Source files
source = _matrix.cpp _matrix.hpp

# Compile
all: $(TARGET)

# Run the Python tests using pytest
test: $(TARGET)
	python3 -m pytest -v test_matrix.py

$(TARGET): $(source)
	$(CXX) $(CXXFLAGS) -I$(MKL_INCLUDE_PATH) `python3-config --includes --ldflags` -o $(TARGET) $(source) -lblas -lmkl_rt

clean:
	rm -rf *.so __pycache__ .pytest*

clean_txt:
	rm -rf *.txt