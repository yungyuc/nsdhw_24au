export LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):/opt/intel/oneapi/mkl/2024.2/lib/intel64

CXX = g++
CXXFLAGS = -O3 -march=native -std=c++17 -fPIC
PYTHON_CONFIG = python3-config
PYBIND11_INCLUDES = $(shell python3 -m pybind11 --includes)
PYTHON_INCLUDES = $(shell $(PYTHON_CONFIG) --includes)
PYTHON_LDFLAGS = $(shell $(PYTHON_CONFIG) --ldflags)

# MKL settings
MKL_ROOT = /opt/intel/oneapi/mkl/2024.2
MKL_INCLUDE = -I$(MKL_ROOT)/include
MKL_LIB = -L$(MKL_ROOT)/lib/intel64 -Wl,--start-group -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -Wl,--end-group -lgomp -lpthread -lm -ldl

# Update CXXFLAGS and add LDFLAGS
CXXFLAGS += $(MKL_INCLUDE) $(PYBIND11_INCLUDES) $(PYTHON_INCLUDES)
LDFLAGS = $(MKL_LIB) $(PYTHON_LDFLAGS)

all: _matrix.so

_matrix.so: matrix.cpp matrix.hpp
	$(CXX) $(CXXFLAGS) -shared -fPIC matrix.cpp -o $@ $(LDFLAGS)

test: _matrix.so
	python3 -m pytest test_matrix.py

benchmark: _matrix.so
	python3 benchmark.py

clean:
	rm -f *.o *.so performance.txt

.PHONY: all test benchmark clean