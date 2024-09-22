CXX = g++
CXXFLAGS = -Wall -Wextra -O2

q1: q1.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

q1.o: q1.cpp
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

run: q1
	./q1

check: q1
	./q1 > result.txt

.PHONY: clean
clean:
	-rm -f *.o q1 result.txt
