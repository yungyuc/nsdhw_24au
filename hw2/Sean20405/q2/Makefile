CXX := g++
CXX_FLAGS := -O3 -Wall -shared -std=c++11 -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --ldflags --includes)
OUTPUT := _vector$(shell python3-config --extension-suffix)

.PHONY: default
default: build
build: _vector.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $(OUTPUT)

.PHONY: test
test: test_*.py $(OUTPUT)
	pytest

.PHONY: clean
clean:
	rm -rf *