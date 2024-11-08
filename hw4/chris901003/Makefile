CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC  -m64 $(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS)
LDFLAGS = -lblas -lmkl_rt

PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
PYTHON_SUF = $(shell python3-config --extension-suffix)

MKL_INC = /usr/include/mkl

TAR = _matrix.so
SRC = _matrix.cpp utility.cpp
PERF_SRC = performance.py
PERF_OUTPUT = performance.txt
PYTEST = test_matrix.py
LIBS = ./_matrix$(PYTHON_SUF)

all: $(LIBS)

$(LIBS): $(SRC)
	$(CXX) $(CXXFLAGS) -I$(MKL_INC) -o $@ $^ $(LDFLAGS)

.PHONY:
test: $(LIBS) $(PYTEST)
	python3 -m pytest -v

.PHONY: clean
clean:
	rm -f $(LIBS)
	rm -rf __pycache__ .pytest* *.so performance.txt

.PHONY: perf
perf: $(LIBS)
	rm -f $(PERF_OUTPUT)
	python3 $(PERF_SRC)