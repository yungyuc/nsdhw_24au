MKL_INCLUDE_DIR = /usr/include/mkl
PYBIND11_INCLUDES := $(shell python3 -m pybind11 --includes)
PYTHON_INCLUDE := $(shell python3-config --includes)
PYTHON_LIB := $(shell python3-config --ldflags)
NUMPY_INCLUDES = $(shell python3 -c "import numpy; print(numpy.get_include())")

_matrix.so: ../mod.cpp matrix.hpp
	g++ -O2 -shared -std=c++17 -fPIC $(PYBIND11_INCLUDES) $(PYTHON_INCLUDE) $^ -I$(MKL_INCLUDE_DIR) -I$(NUMPY_INCLUDES) -I. -o $@ $(PYTHON_LIB) -lblas -lmkl_rt

test: _matrix.so test_matrix_math.py
	python3 -m pytest -v test_matrix_math.py

clean:
	rm -rf *.so
