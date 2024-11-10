CXX := g++
CXXFLAGS := -O3 -Wall -shared -std=c++11 -fPIC -m64 $(shell python3 -m pybind11 --includes)

PYTHON := $(shell python3-config --includes --ldflags)

MKL_INCLUDE := /usr/include/mkl
MKL_LIB := -lmkl_rt

TARGET := _matrix.so
SOURCE := _matrix.cpp

.PHONY: default clean

default: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -I$(MKL_INCLUDE) $(PYTHON) -o $@ $(MKL_LIB)
	

test: $(TARGET)
	python -m pytest -v

banchmark: $(TARGET)
	python performance.py	

clean:
	rm -rf *.so __pycache__ .pytest_cache