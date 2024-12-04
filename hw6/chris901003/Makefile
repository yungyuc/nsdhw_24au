CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall -shared -fPIC
LDFLAGS = -lblas -lmkl_rt

PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
NUMPY = $(shell python3 -c "import numpy; print(numpy.get_include())")


MKL_PATH = /usr/include/mkl

TAR = _matrix.so
INC = ./matrix.hpp
SRC = ./matrix.cpp

all: $(TAR)

$(TAR): $(INC) $(SRC)
		pip install pybind11
		$(CXX) $(CXXFLAGS) -I./ -I$(MKL_PATH) $(PYTHON_LIB_FLAGS) $(PYBIND_INC_FLAGS) -I$(NUMPY) $^ -o $@ $(LDFLAGS)

test: $(TAR)
		python3 test_matrix.py
		python3 -m pytest -v -s test_matrix.py
.PHONY: test

clean:
		rm -rf *.o *.out *.so __pycache__/ .pytest_cache/
.PHONY: clean
