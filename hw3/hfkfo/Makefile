CXX = g++

CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes`
OBJ = _matrix.so
MKL_INCLUDE_DIR = /usr/include/mkl

all: $(OBJ)

_matrix.so: _matrix.cpp
	$(CXX) $(CXXFLAGS) $< -I$(MKL_INCLUDE_DIR) `python3-config --includes --ldflags` -o $@  -lblas -lmkl_rt

clean:
	rm -rf *.so __pycache__ .pytest* 

test: $(OBJ) test_matrix.py
	python3 -m pytest -v $2