CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = q1

SRCS = main.cpp line.cpp

OBJS = $(SRCS:.cpp=.o)

RESULTS = result.txt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

check: $(TARGET)
	./$(TARGET) > $(RESULTS)

clean:
	rm -f $(OBJS) $(TARGET) $(RESULTS)

.PHONY: all run check clean