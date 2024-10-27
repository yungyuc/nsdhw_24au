CXX       := g++
CXX_FLAGS := -O3 -Wall -shared -std=c++11 -fPIC
INC_FLAGS := -I/usr/include/mkl $(shell python3 -m pybind11 --includes)
LIB_FLAGS := -lmkl_rt
NAME      := _matrix$(shell python3-config --extension-suffix)


all: _matrix.hpp bind.cpp
	${CXX} ${CXX_FLAGS} bind.cpp -o ${NAME} ${INC_FLAGS} ${LIB_FLAGS}

test:
	make
	python -m unittest

clean:
	rm -rf ${NAME} __pycache__
