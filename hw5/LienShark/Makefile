CXX=g++
CXXFLAGS=-O3 -g -m64 -Wall -Wextra -shared -std=c++17 -fPIC -Wno-unused-function

PYBIND_INCLUDE=$(shell python3 -m pybind11 --includes)
PYINCLUDE=$(shell python3-config --includes)
TARGET=_matrix$(shell python3-config --extension-suffix)
OBJECTS = matrix.o mod.o

NUMPYINCLUDE=$(shell python3 -c 'import numpy; print(numpy.get_include())')

MKL_INC=-I/usr/include/mkl
MKL_LIB=-L/usr/lib/x86_64-linux-gnu -lblas
IBLAS=-lblas
LDFLAGS := -shared -fPIC

.PHONY: all test clean

all: $(TARGET)



$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(IBLAS)

$(OBJECTS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) $(MKL_INC) $(PYINCLUDE) -I $(NUMPYINCLUDE) -I ./$(PYBIND_INCLUDE) -c $< -o $@ $(IBLAS)

test: $(TARGET)
	python3 -m pytest -v


clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf __pycache__ ../__pycache__
	rm -rf .pytest*
	rm -rf ../.pytest_cache

