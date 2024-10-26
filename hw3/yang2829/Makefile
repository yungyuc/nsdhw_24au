target = _matrix$(shell python3-config --extension-suffix)

CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3 -shared -fPIC -m64 $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)
MKL_INC = /usr/include/mkl
PYTEST = test_matrix.py

all: $(target)

$(target): _matrix.cpp
	$(CXX) $(CXXFLAGS) -I$(MKL_INC) -o $@ $^ -lblas -lmkl_rt

test: $(target) $(PYTEST)
	python3 -m pytest -v

clean:
	rm -rf $(executables) __pycache__ *.pyc *.so