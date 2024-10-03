# Makefile for Q2

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17 -fPIC -shared

# Detect platform
UNAME_S := $(shell uname -s)

# Python3 configuration
PYTHON3_INCLUDE = $(shell python3 -c "from sysconfig import get_paths as gp; print(gp()['include'])")
PYTHON3_LIB = $(shell python3 -c "import sysconfig; print(sysconfig.get_config_var('LIBDIR'))")
PYTHON3_LIBFILE = $(shell python3-config --ldflags)

# Target names
TARGET = _vector.so
SOURCE = angle.cpp

# macOS-specific linking for Python
ifeq ($(UNAME_S), Darwin)
    LDFLAGS = -undefined dynamic_lookup
else
    LDFLAGS = -L$(PYTHON3_LIB)
endif

# Default rule to build the shared object
all: $(TARGET)

# Rule to compile the C++ code into a shared object
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -I$(PYTHON3_INCLUDE) $(LDFLAGS) $(SOURCE) -o $(TARGET)

# Test rule to run pytest
test:
	PYTHONPATH=".:$$PYTHONPATH" python3 -m pytest -v

# Clean rule to remove the built shared object
clean:
	rm -f $(TARGET)
	rm -f *.o

# Phony targets to ensure they're always executed
.PHONY: all test clean





