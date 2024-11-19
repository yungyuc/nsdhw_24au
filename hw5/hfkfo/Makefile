CXX = g++

CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC `python3 -m pybind11 --includes`
OBJ = _matrix${PYCONFIG}
PYCONFIG      := $(shell python3-config --extension-suffix)
MKL_INCLUDE_DIR = /usr/include/mkl
NUMPY = $(shell python3 -c "import numpy; print(numpy.get_include())")

all: $(OBJ)

$(OBJ): ../mod.cpp matrix.cpp
	$(CXX) $(CXXFLAGS) -I./ -I$(MKL_INCLUDE_DIR) -I$(NUMPY) `python3-config --includes --ldflags` $^ -o $@  -lblas -lmkl_rt

test: all
	python3 -m pytest

clean:
	rm -rf __pycache__ .pytest_cache _matrix*.so