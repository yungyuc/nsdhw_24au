
MKL_INCLUDE_DIR = /usr/include/mkl

_matrix.so: _matrix.cpp
	g++ -Ofast -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` _matrix.cpp -I$(MKL_INCLUDE_DIR) `python3-config --includes --ldflags` -o $@ -lblas -lmkl_rt

test: _matrix.so test_matrix_math.py
	python3 -m pytest -v test_matrix_math.py

clean:
	rm -rf *.so
