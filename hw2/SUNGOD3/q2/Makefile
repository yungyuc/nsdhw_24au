CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -fPIC -shared
PYTHON_INCLUDE = $(shell python3 -c "from sysconfig import get_paths as gp; print(gp()['include'])")
PYBIND11_INCLUDE = $(shell python3 -m pybind11 --includes)
OUTPUT = _vector$(shell python3-config --extension-suffix)

.PHONY: all test clean

all: $(OUTPUT)

$(OUTPUT): main.o
	$(CXX) $(CXXFLAGS) -I$(PYTHON_INCLUDE) $(PYBIND11_INCLUDE) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(PYTHON_INCLUDE) $(PYBIND11_INCLUDE) -c $< -o $@

test: $(OUTPUT)
	python3 -m pytest -v

clean:
	rm -f *.o $(OUTPUT)