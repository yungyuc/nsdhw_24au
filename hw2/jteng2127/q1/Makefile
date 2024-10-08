.PHONY: all run check clean

CXX=g++
CXXFLAGS= -std=c++14 -O3 -Wall
SRCS=main.cpp line.cpp
OBJS=$(SRCS:.cpp=.o)
TARGET = main
OUTPUT = result.txt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

check: $(TARGET)
	./$(TARGET) > $(OUTPUT)

clean:
	rm -f $(TARGET) $(OBJS) $(OUTPUT)
