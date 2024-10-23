CC = g++
MKLINCLUDE = -I/usr/include/mkl
INCLUDE = `python3 -m pybind11 --includes`
POSFIX = `python3-config --extension-suffix`
CONFIG = `python3-config --includes`
CFLAGS = -O3 -Wall -shared -std=c++11 -fPIC



#MKLCONFIG = -L/usr/lib/x86_64-linux-gnu -lblas -I/opt/intel/mkl #-I/usr/include/mkl #


.PHONY: all, matrix, test, clean

all: matrix test

matrix: _matrix.cpp
	$(CC)  $(CFLAGS) $(INCLUDE) _matrix.cpp -o _matrix$(POSFIX)  -lblas $(MKLINCLUDE) $(CONFIG)

test: matrix
	python3  test_file.py -v
clean:
	rm -f *.so
	rm -rf __pycache* .pytest*

