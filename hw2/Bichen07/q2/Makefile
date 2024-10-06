# Compiler and flags
CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes`
source = angle.cpp
LIB = _vector.so

# Run the Python tests using pytest
test: ${LIB}
	python3 -m pytest test_angle.py

# Clean up build files
clean:
	rm -f ${LIB}
	rm -rf __pycache__
	rm -rf .pytest_cache

# Build the shared object from the source file
${LIB}: ${source}
	$(CXX) $(CXXFLAGS) ${source} `python3-config --includes --ldflags` -o ${LIB} 

# Declare phony targets
.PHONY: clean test
