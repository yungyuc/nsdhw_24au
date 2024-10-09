PYTHON = python3
PYBIND11_INCLUDE = $(shell $(PYTHON) -m pybind11 --includes) 

CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall -shared -fPIC `python3-config --includes --ldflags` -Wl,-undefined,dynamic_lookup `python3 -m pybind11 --includes`


_vector.so: vector_angle.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)


.PHONY: clean test

test:
	$(PYTHON) -m pytest -q test_angle.py

clean:
	rm -rf *.so __pycache__ .pytest_cache
