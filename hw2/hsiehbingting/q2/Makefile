CXX = g++
CXXFLAGS = -O3 -std=c++11 -Wall -Werror -Wextra 
CXXFLAGS += -shared -fPIC $(shell python3 -m pybind11 --includes) 
# $(python3-config --includes --ldflags)
LIB = _vector$(shell python3-config --extension-suffix)


all: ${LIB}

test: ${LIB}
	python3 -m pytest -v

clean: 
	rm -rf *.so __pycache__ .pytest_cache

${LIB}: calc_angle.cpp
	${CXX} ${CXXFLAGS} $^ -o $@ 