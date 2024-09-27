CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

.PHONY: all run check clean

all: q1

q1: main.o line.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: q1
	./q1

check: q1
	./q1 > result.txt

clean:
	-rm -f *.o q1 result.txt
