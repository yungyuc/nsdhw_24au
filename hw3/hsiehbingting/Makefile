CXX = g++
CXXFLAGS = -O3 -std=c++11 -Wall -Werror -Wextra -shared -fPIC
MKLFLAGS = -I /usr/include/mkl
INCFLAGS = $(shell python3 -m pybind11 --includes)
IDFFLAGS = $(shell python3-config --includes --ldflags)
LIB = _matrix$(shell python3-config --extension-suffix)


all: ${LIB}

test: ${LIB}
	python3 -m pytest -v

clean: 
	rm -rf *.so *.o *.out  __pycache__ .pytest_cache 

${LIB}: _matrix.cpp
	${CXX} ${CXXFLAGS} ${INCFLAGS} ${IDFFLAGS} ${MKLFLAGS} $^ -lblas -o $@ 

