# 指定 MKL 的包含和庫路徑
MKLINCLUDE = -I/opt/intel/oneapi/mkl/2023.2.2/include
MKLLIB = /opt/intel/oneapi/mkl/2023.2.2/lib
COMPILERLIB = /opt/intel/oneapi/compiler/latest/mac/compiler/lib

# 編譯器選項
CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC -DMKL_ILP64 -m64 $(MKLINCLUDE) `python3-config --includes`
LDFLAGS = $(MKLLIB)/libmkl_intel_ilp64.dylib \
          $(MKLLIB)/libmkl_intel_thread.dylib \
          $(MKLLIB)/libmkl_core.dylib \
          -L$(COMPILERLIB) -Wl,-rpath,$(MKLLIB) -Wl,-rpath,$(COMPILERLIB) \
          -liomp5 -lpthread -lm -ldl -undefined dynamic_lookup

# 目標名稱
TARGET = _matrix$(shell python3-config --extension-suffix)
ALLOCATOR = _allocate.hpp
ALLOCATOR_OBJ = _allocate.o
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
	rm -f $(TARGET)