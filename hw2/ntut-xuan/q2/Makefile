.PHONY: all

CFLAGS = -std=c++11 -shared -fPIC $(shell python3 -m pybind11 --includes)

all: vector.hpp vector.cpp
	$(CXX) $(CFLAGS) vector.cpp $(shell python3-config --includes) $(shell python3-config --embed --ldflags) -o _vector`python3-config --extension-suffix` -I/usr/local/include/pybind11

test:
	python3 -m pytest .

clean:
	rm *.so