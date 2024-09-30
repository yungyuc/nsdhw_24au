CC     := g++
CFLAGS := -O3 -Wall -I. -std=c++11
EXEC   := q1

.PHONY: all run check clean


all: *.o
	${CC} ${CFLAGS} -o ${EXEC} $^

%.o: %.cpp
	${CC} ${CFLAGS} -c $^ 


run:
	./${EXEC}

check:
	./${EXEC} > result.txt

clean:
	rm ${EXEC} *.o result.txt