CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O3

all: main

main: main.cpp line.cpp line.hpp
	$(CXX) $(CXXFLAGS) -o $@ $^

run: main
	./main

check: main
	./main > result.txt

clean:
	-rm -f *.o main result.txt