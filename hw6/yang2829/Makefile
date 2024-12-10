target = _matrix$(shell python3-config --extension-suffix)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -shared -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)
MKL_INC = /usr/include/mkl
PYTEST = test_matrix.py
source = ./matrix.cpp

all: $(target)

$(target): $(source)
	$(CXX) $(CXXFLAGS) -I$(MKL_INC) -o $@ $^ -lblas -lmkl_rt

test: $(target) $(PYTEST)
	python3 -m pytest -v

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/