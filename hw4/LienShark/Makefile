# 指定 MKL 的包含和庫路徑
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    DYNAMIC_LOOKUP_FLAG = -undefined dynamic_lookup
else
    DYNAMIC_LOOKUP_FLAG =
endif

ifeq ($(UNAME_S),Linux)
    MKLINCLUDE = -I/usr/include/mkl
    MKLLIB = -L/usr/lib/mkl
	LDFLAGS = -L/usr/lib/mkl -lmkl_intel_ilp64 -lmkl_core -lmkl_sequential -lmkl_def -lpthread -lm -ldl
else ifeq ($(UNAME_S),Darwin)
    MKLINCLUDE = -I/opt/intel/oneapi/mkl/2023.2.2/include
    MKLLIB = -L/opt/intel/oneapi/mkl/2023.2.2/lib
	LDFLAGS = $(MKLLIB)/libmkl_intel_ilp64.dylib \
          $(MKLLIB)/libmkl_intel_thread.dylib \
          $(MKLLIB)/libmkl_core.dylib \
          -L$(COMPILERLIB) -Wl,-rpath,$(MKLLIB) -Wl,-rpath,$(COMPILERLIB) \
          -liomp5 -lpthread -lm -ldl $(DYNAMIC_LOOKUP_FLAG)

else
    $(error "Unsupported operating system")
endif

COMPILERLIB = /opt/intel/oneapi/compiler/latest/mac/compiler/lib

# 編譯器選項
CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC -DMKL_ILP64 -m64 $(MKLINCLUDE) `python3-config --includes`

# 目標名稱
TARGET = _matrix$(shell python3-config --extension-suffix)
ALLOCATOR = _allocate.hpp
PYBIND_OBJ = _pybind.o
MATRIX_OBJ = _matrix.o
# 編譯規則
all: $(TARGET)

$(TARGET): $(MATRIX_OBJ) $(PYBIND_OBJ)
	$(CXX) $(CXXFLAGS) `python3 -m pybind11 --includes` $(MATRIX_OBJ) $(PYBIND_OBJ) -o $(TARGET) $(LDFLAGS) `python3-config --includes`

# 編譯 allocate.hpp
#$(ALLOCATOR_OBJ): _allocate.cpp _allocate.hpp
	#$(CXX) $(CXXFLAGS) -c _allocate.cpp -o $(ALLOCATOR_OBJ)

# 編譯 pybind.cpp
$(PYBIND_OBJ): _pybind.cpp _matrix.cpp _allocate.hpp
	$(CXX) $(CXXFLAGS) `python3 -m pybind11 --includes` -c _pybind.cpp -o $(PYBIND_OBJ)

# 編譯 matrix.cpp
$(MATRIX_OBJ): _matrix.cpp _matrix.hpp _allocate.hpp
	$(CXX) $(CXXFLAGS) -c _matrix.cpp -o $(MATRIX_OBJ)
# 測試規則
test: $(TARGET)
	python3 ../validate.py

# 清理指令
clean:
	rm -f $(TARGET) *.o