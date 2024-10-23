# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -O2
PYTHON = python3

# Targets
TARGET = multiplication
OBJECTS = _matrix.o multiplication.o

# Default rule: build the main target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile the _matrix.cpp source file
_matrix.o: _matrix.cpp
	$(CXX) $(CXXFLAGS) -c _matrix.cpp

# Compile the multiplication.cpp source file
multiplication.o: multiplication.cpp
	$(CXX) $(CXXFLAGS) -c multiplication.cpp

# Clean up object files, the executable, and any shared object files (.so)
clean:
	rm -f $(OBJECTS) $(TARGET) *.so

# Run Python test script
test:
	$(PYTHON) test_performance.py

# Phony targets to avoid conflict with files named clean or test
.PHONY: clean test


