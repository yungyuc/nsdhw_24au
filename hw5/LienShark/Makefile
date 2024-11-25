UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	DYNAMIC_LOOKUP_FLAG = -undefined dynamic_lookup
else
    DYNAMIC_LOOKUP_FLAG =
endif

ifeq ($(UNAME_S),Linux)
    MKLINCLUDE = -lblas -I/usr/include/mkl
    MKLLIB = -L/usr/lib/mkl
	LDFLAGS = -L/usr/lib/mkl -lmkl_rt -lmkl_intel_ilp64 -lmkl_core -lmkl_sequential -lmkl_def -lpthread -lm -ldl
else ifeq ($(UNAME_S),Darwin)
    MKLINCLUDE = -I/opt/intel/oneapi/mkl/2023.2.2/include
    MKLLIB = -L/opt/intel/oneapi/mkl/2023.2.2/lib
    LDFLAGS = -L/opt/intel/oneapi/mkl/2023.2.2/lib \
          -L/opt/intel/oneapi/compiler/latest/mac/compiler/lib \
          -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core \
          -liomp5 -lpthread -lm -ldl -undefined dynamic_lookup \
          -Wl,-rpath,/opt/intel/oneapi/mkl/2023.2.2/lib \
          -Wl,-rpath,/opt/intel/oneapi/compiler/latest/mac/compiler/lib

	#LDFLAGS += -L/opt/intel/oneapi/compiler/latest/mac/compiler/lib -liomp5

# LDFLAGS = $(MKLLIB)/libmkl_intel_ilp64.dylib \
#          $(MKLLIB)/libmkl_intel_thread.dylib \
#          $(MKLLIB)/libmkl_core.dylib \
#          -L$(COMPILERLIB) -Wl,-rpath,$(MKLLIB) -Wl,-rpath,$(COMPILERLIB) \
#          -liomp5 -lpthread -lm -ldl $(DYNAMIC_LOOKUP_FLAG)
else
    $(error "Unsupported operating system")
endif

COMPILERLIB = /opt/intel/oneapi/compiler/latest/mac/compiler/lib
NUMPYINCLUDE=$(shell python3 -c 'import numpy; print(numpy.get_include())')

# 編譯器選項
CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC -DMKL_ILP64 -m64 $(MKLINCLUDE) `python3-config --includes` -I$(NUMPYINCLUDE)



# 目標名稱
TARGET := _matrix$(shell python3-config --extension-suffix)
ALLOCATOR = _allocate.hpp
PYBIND_OBJ = _pybind.o
MATRIX_OBJ = _matrix.o
# 編譯規則
all: $(TARGET)

$(TARGET): $(MATRIX_OBJ) mod.o
	$(CXX) $(CXXFLAGS) `python3 -m pybind11 --includes` $(MATRIX_OBJ) mod.o -o $(TARGET) $(LDFLAGS) `python3-config --includes`

# 編譯 allocate.hpp
#$(ALLOCATOR_OBJ): _allocate.cpp _allocate.hpp
 #$(CXX) $(CXXFLAGS) -c _allocate.cpp -o $(ALLOCATOR_OBJ)

# 編譯 pybind.cpp
#$(PYBIND_OBJ): _pybind.cpp _matrix.cpp _allocate.hpp
# $(CXX) $(CXXFLAGS) python3 -m pybind11 --includes -c _pybind.cpp -o $(PYBIND_OBJ)

# 編譯 matrix.cpp
$(MATRIX_OBJ): _matrix.cpp _matrix.hpp _allocate.hpp mod.cpp
	$(CXX) $(CXXFLAGS) -I$(NUMPYINCLUDE) -c _matrix.cpp -o $(MATRIX_OBJ)
 
mod.o: mod.cpp
	$(CXX) $(CXXFLAGS) -I$(NUMPYINCLUDE) `python3 -m pybind11 --includes` -c mod.cpp -o mod.o


# 測試規則
test: $(TARGET)
	python3 ../validate.py

# 清理指令
clean:
	rm -f $(TARGET) *.o
	rm -f *.so
	rm -f *.o
