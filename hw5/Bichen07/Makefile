# Compiler and flags
CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall -Werror -Wextra -shared -fPIC -Wno-unused-function
IDFFLAGS = $(shell python3-config --includes --ldflags)
INCFLAGS = $(shell python3 -m pybind11 --includes)
MKL_INCLUDE_PATH = -I/usr/include/mkl

NUMPY = $(shell python3 -c "import numpy; print(numpy.get_include())")
# Target
TARGET = _matrix$(shell python3-config --extension-suffix)

# Source files
source = matrix.cpp matrix.hpp ../mod.cpp

# Compile
all: $(TARGET)

# Run the Python tests using pytest
test: $(TARGET)
	python3 -m pytest -v

$(TARGET): $(source)
	${CXX} ${CXXFLAGS} ${IDFFLAGS} ${INCFLAGS} -I. -I${NUMPY} ${MKL_INCLUDE_PATH} $(source) -lblas -o $(TARGET)

clean:
	rm -rf *.so __pycache__ .pytest*
