export LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):/opt/intel/oneapi/mkl/2024.2/lib/intel64
CXX := g++
CXXFLAGS := -std=c++17 -O3 -fPIC -fopenmp -march=native
PYBIND11_INCLUDES := $(shell python3 -m pybind11 --includes)

# MKL 設置
MKL_ROOT := /opt/intel/oneapi/mkl/latest
MKL_INCLUDE := -I$(MKL_ROOT)/include
MKL_LIB := -L$(MKL_ROOT)/lib/intel64 -lmkl_rt

# Python 設置
PYTHON_INCLUDE := $(shell python3-config --includes)
PYTHON_LIB := $(shell python3-config --ldflags)

# 組合所有的 flags
ALL_INCLUDES := $(PYBIND11_INCLUDES) $(MKL_INCLUDE) $(PYTHON_INCLUDE)
ALL_LIBS := $(MKL_LIB) $(PYTHON_LIB)

SOURCES := matrix.cpp
TARGET := _matrix$(shell python3-config --extension-suffix)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(ALL_INCLUDES) -shared -o $@ $^ $(ALL_LIBS)

test: $(TARGET)
	python3 -m pytest -vvv .

clean:
	rm -f $(TARGET)