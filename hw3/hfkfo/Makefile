CXX = g++

CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes`
OBJ = _matrix.so

all: $(OBJ)

$(OBJ): _matrix.cpp
	$(CXX) $(CXXFLAGS) $< `python3-config --includes --ldflags` -o $@  -lblas -lmkl_rt

clean:
	rm -rf performance.txt *.so __pycache__ .pytest* 

test: test_matrix.py
	python3 -m pytest -v $1