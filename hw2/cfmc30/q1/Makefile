CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

TARGET = q1

SRCS = q1.cpp line.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) result.txt
run: $(TARGET)
	./$(TARGET)
check: $(TARGET)
	./$(TARGET) > result.txt

