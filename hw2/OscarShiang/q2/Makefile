PYTHON          := $(shell which python3)
CXX             := g++
CXXFLAGS        := -O3 -Wall -shared -std=c++11 -fPIC -Iinclude \
                   $(shell ${PYTHON} -mpybind11 --includes)
LDFLAGS         :=

LIB             := vec$(shell ${PYTHON}-config --extension-suffix)
OBJS            := vec.o

all: $(LIB)

$(LIB): $(OBJS:%=src/%)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $^ $(CXXFLAGS)

test:
.PHONY: test

clean:
	$(RM) $(LIB) $(OBJS:%=src/%)
.PHONY: clean
