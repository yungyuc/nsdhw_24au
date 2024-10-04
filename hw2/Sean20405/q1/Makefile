CXX = g++

.PHONY: default
default: line
line: line.o
	$(CXX) line.o -o line

line.o: line.cpp
	$(CXX) -c line.cpp -o line.o

.PHONY: run
run: line
	./line

.PHONY: check
check: line
	./line > result.txt

.PHONY: clean
clean:
	rm -rf *