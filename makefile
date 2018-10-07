CC=g++

CFLAGS=-g

all: Node.o AStar.o
	$(CC) $(CFLAGS) -o AStar Node.o AStar.o
	-rm AStar.o Node.o

Node.o: Node.cpp
	$(CC) $(CFLAGS) -c Node.cpp

AStar.o: AStar.cpp	
	$(CC) $(CFLAGS) -c AStar.cpp

test:
	./Astar tests/test1
	./Astar tests/test2
	./Astar tests/test3

clean: 
	-rm AStar 


