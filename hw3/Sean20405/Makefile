MKLROOT_DIR = ${MKLROOT}
CXX := g++
MKL_FLAGS := -m64 -L${MKLROOT}/lib -Wl,--no-as-needed -lmkl_intel_ilp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl
MKL_FLAGS_TEST := -I /usr/include/mkl -lblas
CXX_FLAGS := -O3 -Wall -shared -fPIC -std=c++11 $(shell python3 -m pybind11 --includes) $(shell python3-config --ldflags --includes) $(MKL_FLAGS)
OUTPUT := _matrix$(shell python3-config --extension-suffix)

.PHONY: default
default: build
build: matrix.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $(OUTPUT)

.PHONY: test
test: test_*.py $(OUTPUT)
	python3 -m pytest

.PHONY: clean
clean:
	rm -rf *