OS = $(shell cat /etc/os-release | grep -oP '(?<=^ID=).+' | tr -d '"')
ifeq ($(OS),ubuntu)
	OSDEF = -DUBUNTU
else ifeq ($(OS),debian)
	OSDEF = -DDEBIAN
else
	OSDEF = -DOTHER
endif

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Ofast -march=native -m64 -fPIC $(OSDEF)
LDFLAGS = -shared
INCLUDE = -I./include -Ithird_party/pybind11/include $(shell python3-config --includes)

MKL_ROOT = /opt/intel/oneapi/mkl/latest
MKL_INCLUDE = -I$(MKL_ROOT)/include
MKL_LINK = -Wl,-rpath,$(MKL_ROOT)/lib -L$(MKL_ROOT)/lib -lmkl_rt

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))
TARGET = _matrix$(shell python3-config --extension-suffix)

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(MKL_LINK)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(MKL_INCLUDE) -c $< -o $@

test: $(TARGET)
	python3 -m pytest -v

clean:
	-rm -f $(OBJS) $(TARGET)
