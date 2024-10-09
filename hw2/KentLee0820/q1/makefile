CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

OBJ = main.o line.o

TARGET = main


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@  


.PHONY: clean check run

clean:
	rm -f *.o *.txt main

run: main
	./main

check:
	./main > result.txt
