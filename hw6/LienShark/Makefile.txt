CXX             = g++
SRC          = _matrix.cpp
FLAGS           = -O3 -Wall -shared -std=c++11 -fPIC
INCLUDES        = -I$(MKL_INCLUDE_DIR) $(PYINC) $(PYBIND11_INC)
LDFLAGS         = $(MKL_LIB_FLAGS)
MKL_INCLUDE_DIR = /usr/include/mkl
MKL_LIB_FLAGS   = -lmkl_rt

PYEXEC     = python3
PYINC      = $(shell $(PYEXEC)-config --includes)
PYBIND11_INC    = $(shell $(PYEXEC) -m pybind11 --includes)
PYSUFFIX = $(shell $(PYEXEC)-config --extension-suffix)
PYBIND11_MODULE     = _matrix
PYTAR = $(PYBIND11_MODULE)$(PYSUFFIX)

all: $(PYTAR)

$(PYTAR): $(SRC)
	$(CXX) $(FLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)
.PHONY: all

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/
.PHONY: clean