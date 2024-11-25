PYTHON          := $(shell which python3)
CXX             := g++
CXXFLAGS        := -O3 -Wall -shared -std=c++14 -fPIC \
                   $(shell ${PYTHON} -mpybind11 --includes) \
                   $(shell ${PYTHON}-config --includes)
LDFLAGS         := $(shell ${PYTHON}-config --ldflags) -lmkl_rt -lblas

LIB             := _matrix$(shell ${PYTHON}-config --extension-suffix)
OBJS            := mod.o

all: $(LIB)

$(LIB): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $^ $(CXXFLAGS)

test: $(LIB)
	$(PYTHON) -m pytest
.PHONY: test

clean:
	$(RM) $(LIB) $(OBJS)
.PHONY: clean
