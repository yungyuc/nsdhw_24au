main: Line.o main.o
	g++ -o main Line.o main.o
Line.o: Line.cpp Line.hpp
	g++ -c Line.cpp
main.o: main.cpp Line.hpp
	g++ -c main.cpp

.PHONY: clean run check

clean:
	rm -f main Line.o main.o result.txt

run:
	./main

check:
	./main > result.txt