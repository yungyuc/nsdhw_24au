.PHONY: all test clean

CXX=g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC -m64 $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags) -I/usr/include/mkl 
LDFLAGS= -lblas -lmkl_rt
SO = _matrix$(shell python3-config --extension-suffix)

all: $(SO)

$(SO): matrix.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) 

test: $(SO)
	python3 -m pytest

clean:
	rm -rf $(SO) __pycache__ .pytest_cache