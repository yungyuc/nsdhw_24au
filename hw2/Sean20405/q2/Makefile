CXX = g++
PYTHON_SUFFIX = $(python3-config --extension-suffix)

.PHONY: default
default: build
build: calculate_angle.cpp
	$(CXX) -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` calculate_angle.cpp -o calculate_angle$(PYTHON_SUFFIX)

.PHONY: test
test: test_*.py calculate_angle$(PYTHON_SUFFIX)
	pytest

.PHONY: clean
clean:
	rm -rf *