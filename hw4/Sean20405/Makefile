MKLROOT_DIR = ${MKLROOT}
CXX := g++
MKL_FLAGS_OLD := -m64 -L${MKLROOT}/lib -Wl,--no-as-needed -lmkl_intel_ilp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl
INCLUDE_FLAGS := -I/usr/include/mkl $(shell python3 -m pybind11 --includes) $(shell python3-config --includes)
LD_FLAGS := $(shell python3-config --ldflags) -lblas -lmkl_rt
CXX_FLAGS := -Ofast -Wall -shared -fPIC -std=c++17
OUTPUT := _matrix$(shell python3-config --extension-suffix)

.PHONY: default
default: $(OUTPUT)
$(OUTPUT): matrix.cpp matrix.hpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) $^ -o $(OUTPUT) $(LD_FLAGS)

.PHONY: test
test: test_*.py $(OUTPUT)
	python3 -m pytest

.PHONY: clean
clean:
	rm -rf *.so *.o __pycache__