.PHONY: all

CFLAGS = -std=c++17 -O3 -shared -fPIC $(shell python3 -m pybind11 --includes)
 
all:
	$(CXX) $(CFLAGS) matrix.cpp matrix.hpp ../mod.cpp $(shell python3-config --includes) $(shell python3-config --embed --ldflags) -o _matrix`python3-config --extension-suffix` -I/usr/local/include/pybind11 -I./ -I/usr/include/mkl -L/opt/intel/mkl/lib/intel64 -I$(shell python3 -c 'import numpy; print(numpy.get_include())') -lblas

test: all
	python3 -m pytest .

clean:
	rm -rf *.so *.o