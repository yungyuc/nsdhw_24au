CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` -I./

main: _vector.so

_vector.so: main.cpp
	g++ $(CXXFLAGS) -o _vector.so main.cpp

.PHONY: clean test main

clean:
	rm -f _vector.so main

test: _vector.so
	python3 -m pytest -v