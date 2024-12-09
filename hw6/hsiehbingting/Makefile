CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall -shared -fPIC -Wno-unused-function
MKLFLAGS = -I/usr/include/mkl
INCFLAGS = $(shell python3 -m pybind11 --includes)
IDFFLAGS = $(shell python3-config --includes --ldflags)
LIB = _matrix$(shell python3-config --extension-suffix)

NUMPY = $(shell python3 -c "import numpy; print(numpy.get_include())")

all: ${LIB}

${LIB}: matrix.cpp matrix.hpp
	${CXX} ${CXXFLAGS} ${INCFLAGS} ${IDFFLAGS} -I. -I${NUMPY} ${MKLFLAGS} $^ -lblas -o $@ 

test: ${LIB}
	python3 -m pytest -v

clean: 
	rm -rf *.so *.o *.out  __pycache__ .pytest_cache 
