CXX = g++

CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` 
MKL_INCLUDE_DIR = /usr/include/mkl

_matrix.so: matrix.cpp matrix.hpp
	$(CXX) $(CXXFLAGS) matrix.cpp -I$(MKL_INCLUDE_DIR) `python3-config --includes --ldflags` -o $@ -lblas -lmkl_rt

test: _matrix.so test_matrix.py
	python3 -m pytest -v test_matrix.py

clean:
	rm -rf *.so