.PHONY: all

CFLAGS = -std=c++17

all: line.o main.o
	$(CXX) $(CFLAGS) line.o main.o -o main

line.o: line.hpp line.cpp
	$(CXX) $(CFLAGS) -c line.cpp -o line.o

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp -o main.o

run:
	./main

clean:
	rm *.o main

check:
	./main > result.txt