CXX = g++

CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes`

all: _vector.so

_vector.so: angle.cpp
	$(CXX) $(CXXFLAGS) $< `python3-config --ldflags` -o $@

clean:
	rm -f *.so

test:
	python3 test_angle.py -v