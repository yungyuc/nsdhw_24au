CXX = g++
CXXFLAGS = -O3 -std=c++11 -Wall -Werror -Wextra

all: main

run: main
	./main

check: main
	./main > result.txt

clean: 
	rm -f main main.o line.o result.txt

main: line.o main.o
	${CXX} ${CXXFLAGS} line.o main.o -o main
line.o: line.cpp line.hpp
	${CXX} ${CXXFLAGS} -c line.cpp -o line.o
main.o: main.cpp line.hpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o