CXX = g++

CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC `python3 -m pybind11 --includes` 
MKL_INCLUDE_DIR = /usr/include/mkl
NP_INCLUDE_DIR = $(shell python3 -c "import numpy; print(numpy.get_include())")

_matrix.so: ../mod.cpp matrix.cpp matrix.hpp 
	$(CXX) $(CXXFLAGS) matrix.cpp ../mod.cpp -I$(NP_INCLUDE_DIR) -I$(MKL_INCLUDE_DIR) -I./ `python3-config --includes --ldflags` -o $@ -lblas -lmkl_rt

clean:
	rm -rf *.so