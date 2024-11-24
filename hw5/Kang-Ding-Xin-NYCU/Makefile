CXX := g++
CXXFLAGS := -O3 -Wall -shared -std=c++17 -fPIC -m64 $(shell python3 -m pybind11 --includes)

PYTHON := $(shell python3-config --includes --ldflags)

MKL_INCLUDE := /usr/include/mkl
NUMPY_INCLUDE := $(shell python3 -c "import numpy; print(numpy.get_include())")

MKL_LIB := -lmkl_rt

TARGET := _matrix.so
SOURCE := matrix.cpp matrix.hpp ../mod.cpp

.PHONY: default clean

default: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -I./ -I$(MKL_INCLUDE) -I$(NUMPY_INCLUDE) $(PYTHON) -o $@ $(MKL_LIB)

test: $(TARGET)
	python -m pytest -v

banchmark: $(TARGET)
	python performance.py	

clean:
	rm -rf *.so __pycache__ .pytest_cache