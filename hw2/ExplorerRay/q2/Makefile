CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -fPIC -shared
INCLUDE = -Iextern/pybind11/include $(shell python3-config --includes)
OUTPUT = _vector$(shell python3-config --extension-suffix)

.PHONY: all test clean

all: $(OUTPUT)

$(OUTPUT): main.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

test: $(OUTPUT)
	python3 -m pytest -v

clean:
	-rm -f *.o *.so $(OUTPUT)
