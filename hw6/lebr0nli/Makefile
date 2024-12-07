PYTHON := python3
CXX := g++

MKL_INCLUDE_DIR := /usr/include/mkl
CXXFLAGS := -O3 -march=native -ffast-math -shared -std=c++17 -fPIC
CXXFLAGS += -Wall -Wextra
CXXFLAGS += $(shell $(PYTHON)-config --includes)
CXXFLAGS += $(shell $(PYTHON) -m pybind11 --includes)
CXXFLAGS += $(shell $(PYTHON) -c "import numpy; print('-I' + numpy.get_include())")
CXXFLAGS += -I$(MKL_INCLUDE_DIR)
CXXFLAGS += -I.
LDFLAGS := $(shell $(PYTHON)-config --ldflags) -lmkl_rt -lblas

SOURCES := matrix.hpp matrix.cpp module.cpp

MODULE := _matrix$(shell $(PYTHON)-config --extension-suffix)

.PHONY: all clean

all: $(MODULE)

$(MODULE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES) $(LDFLAGS)

clean:
	rm -rf $(MODULE)

