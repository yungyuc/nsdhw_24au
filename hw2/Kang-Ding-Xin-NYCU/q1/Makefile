CXX = g++

.PHONY: default clean

default: main

main: main.o Line.o
	$(CXX) main.o Line.o -o main

main.o: main.cpp Line.hpp
	$(CXX) -c main.cpp -o main.o

Line.o: Line.cpp Line.hpp
	$(CXX) -c Line.cpp -o Line.o

run:
	./main

check:
	./main >> result.txt

clean:
	rm main.o Line.o main result.txt
