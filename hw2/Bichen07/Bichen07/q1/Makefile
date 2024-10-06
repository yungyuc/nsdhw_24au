CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O3

main: line.o main.o
	${CXX} ${CXXFLAGS} line.o main.o -o main
line.o: line.cpp line.hpp
	${CXX} ${CXXFLAGS} -c line.cpp -o line.o
main.o: main.cpp line.hpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o

.PHONY: run check clean

run: main
	./main

check: main
	./main > result.txt

clean:
	rm -f main Line.o main.o result.txt
