.PHONY: all

CFLAGS = -std=c++11 -shared -fPIC $(shell python3 -m pybind11 --includes)

all: matrix.hpp matrix.cpp
	$(CXX) $(CFLAGS) matrix.cpp $(shell python3-config --includes) $(shell python3-config --embed --ldflags) -o _matrix`python3-config --extension-suffix` -I/usr/local/include/pybind11 -lblas -I/usr/include/mkl

test:
	python3 -m pytest .

clean:
	rm -rf *.so