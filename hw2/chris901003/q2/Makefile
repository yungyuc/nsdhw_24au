sources = _vector.cpp
target = _vector$(shell python3-config --extension-suffix)

CXX = g++
CXXFLAGS = -std=c++14 -O3 -Wall -shared -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)

all: $(sources)
	$(CXX) $(CXXFLAGS) $(sources) -o $(target)

test:
	python3 -m pytest

clean:
	rm -rf $(executables) __pycache__ *.pyc *.so