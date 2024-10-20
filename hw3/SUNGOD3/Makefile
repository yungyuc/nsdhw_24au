CXX := g++
CXXFLAGS := -std=c++17 -O3 -fPIC -fopenmp -march=native
PYBIND11_INCLUDES := $(shell python3 -m pybind11 --includes)

MKL_INC := /usr/include/mkl
MKL_LIB := -lmkl_rt

PYTHON_INCLUDE := $(shell python3-config --includes)
PYTHON_LIB := $(shell python3-config --ldflags)

ALL_INCLUDES := $(PYBIND11_INCLUDES) -I$(MKL_INC) $(PYTHON_INCLUDE)
ALL_LIBS := $(MKL_LIB) $(PYTHON_LIB)

SOURCES := matrix.cpp
HEADERS := matrix.hpp
TARGET := _matrix$(shell python3-config --extension-suffix)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(ALL_INCLUDES) -shared -o $@ $(SOURCES) $(ALL_LIBS)

test: $(TARGET)
	python3 -m pytest -vvv .

clean:
	rm -f $(TARGET)