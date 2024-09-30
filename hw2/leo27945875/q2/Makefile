CC     := g++
CFLAGS := -O3 -Wall -shared -std=c++11 -fPIC
EXEC   := _vector

PY_INCUDES := $(shell python3 -m pybind11 --includes) $(shell python3-config --includes)
PY_SUFFIX  := $(shell python3-config --extension-suffix)


.PHONY: all test clean


all:
	${CC} -O3 -Wall -shared -std=c++11 -fPIC ${PY_INCUDES} ${EXEC}.cpp -o ${EXEC}${PY_SUFFIX}

test:
	pytest

clean:
	rm ${EXEC}${PY_SUFFIX}