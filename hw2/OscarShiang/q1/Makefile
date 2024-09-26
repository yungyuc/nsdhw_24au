CXX             := g++
CXXFLAGS        := -std=c++11 -Iinclude -Wall -g
LDFLAGS         := 

EXEC            := q1
OBJS            := line.o point.o main.o

all: $(EXEC)

$(EXEC): $(OBJS:%=src/%)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

run: $(EXEC)
	./$(EXEC)
.PHONY: run

check: $(EXEC)
	./$(EXEC) > result.txt
.PHONY: check

clean:
	$(RM) $(EXEC) $(OBJS:%=src/%) result.txt
.PHONY: clean
