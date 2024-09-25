sources = _vector.cpp
executables = _vector$$(python3-config --extension-suffix)

CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC $$(python3 -m pybind11 --includes)

all: $(sources)
	$(CXX) $(CXXFLAGS) $(sources) -o $(executables)

test:
	python3 -m pytest

clean:
	rm -rf $(executables) __pycache__ *.pyc