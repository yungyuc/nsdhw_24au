CXX = g++
CXXFLAGES = -std=c++11 -Wall -Wextra -02

all: main

main: line.o
	$(CXX) $(CXXFLAGS) -o main main.cpp line.o

line.o: line.cpp line.hpp
	$(CXX) $(CXXFLAGS) -c line.cpp

run: main
	./main

check: main
	./main > result.txt

clean:
	rm -f main line.o result.txt

