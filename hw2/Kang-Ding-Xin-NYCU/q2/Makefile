CXX = g++
CXXFLAGS =  -O3 -Wall -shared -std=c++11 -fPIC $(shell python3 -m pybind11 --includes)
TARGET = _vector

.PHONY: default clean

default: $(TARGET)

$(TARGET): _vector.cpp
	$(CXX) $(CXXFLAGS) _vector.cpp -o $(TARGET)

test:
	python -m pytest -v

clean:
	rm -r __pycache__ .pytest_cache *.so