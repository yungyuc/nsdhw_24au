CXX := g++
CXXFLAGS := -O3 -Wall -shared -std=c++17 -fPIC -fopenmp -march=native
PYBIND11_INCLUDES := $(shell python3 -m pybind11 --includes)

MKL_INCLUDE_DIR := /usr/include/mkl
MKL_LIB := -lmkl_rt
NUMPY_INCLUDE := $(shell python3 -c "import numpy; print(numpy.get_include())")

PYTHON_INCLUDE := $(shell python3-config --includes)
PYTHON_LIB := $(shell python3-config --ldflags)

PYTHON_EXTENSION_SUFFIX := $(shell python3-config --extension-suffix)

ALL_INCLUDES := $(PYBIND11_INCLUDES) -I$(MKL_INCLUDE_DIR) -I$(NUMPY_INCLUDE) $(PYTHON_INCLUDE) -I.
ALL_LIBS := $(MKL_LIB) $(PYTHON_LIB)

SOURCES := ../mod.cpp matrix.cpp
HEADERS := matrix.hpp
TARGET := _matrix$(PYTHON_EXTENSION_SUFFIX)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(ALL_INCLUDES) -shared -o $@ $^ $(ALL_LIBS)

test: $(TARGET)
	python3 -m pytest -vvv .

clean:
	rm -f $(TARGET) *.o __pycache__ .pytest_cache _matrix*.so