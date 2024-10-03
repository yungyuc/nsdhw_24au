# 指定編譯器
CXX = g++
CXXFLAGS = -std=c++11

# 生成可執行檔 hw2
hw2: main.o
	$(CXX) $(CXXFLAGS) main.o -o hw2

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

.PHONY: clean
clean:
	rm -rf *.o hw2 result.txt
	
run: hw2
	./hw2
	
check: hw2
	./hw2 > result.txt
