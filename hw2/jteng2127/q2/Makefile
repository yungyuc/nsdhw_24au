.PHONY: all test clean

CXX=g++
CXXFLAGS= -O3 -Wall -shared -std=c++11 -fPIC $(shell python3 -m pybind11 --includes) -Wl,-undefined,dynamic_lookup $(shell python3-config --ldflags --includes)
TARGET = _vector
SO = $(TARGET)$(shell python3-config --extension-suffix)

all: $(SO)

$(SO): $(TARGET).cpp
	@$(CXX) $(CXXFLAGS) $< -o $@

test: $(SO)
	python -m pytest

clean:
	rm -rf $(SO) __pycache__ .pytest_cache
