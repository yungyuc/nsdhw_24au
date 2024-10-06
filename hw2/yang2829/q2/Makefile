target = _vector$(shell python3-config --extension-suffix)

CXX = g++
CXXFLAGS = -std=c++11 -Wall -shared -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)

all: $(target)

$(target): cal_deg.cpp
	$(CXX) $(CXXFLAGS) cal_deg.cpp -o $(target)

test: $(target)
	python3 -m pytest

clean:
	rm -rf $(executables) __pycache__ *.pyc *.so