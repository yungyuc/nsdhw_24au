.PHONY: all test clean

CXX=g++
CXXFLAGS= -O3 -Wall -shared -std=c++11 -fPIC $(shell python3 -m pybind11 --includes) -Wl,-undefined,dynamic_lookup
LDFLAGS=$(shell python3-config --ldflags)
TARGET = matrix
SO = _$(TARGET)$(shell python3-config --extension-suffix)

all: $(SO)

$(SO): $(TARGET).cpp $(TARGET).hpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@

test: $(SO)
	python -m pytest

clean:
	rm -rf $(SO) __pycache__ .pytest_cache