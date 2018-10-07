CC=g++

CFLAGS=-g

all: Node.o AStar.o
	$(CC) $(CFLAGS) -o AStar Node.o AStar.o

Node.o: Node.cpp
	$(CC) $(CFLAGS) -c Node.cpp

AStar.o: AStar.cpp	
	$(CC) $(CFLAGS) -c AStar.cpp


clean: 
	-rm AStar.o Node.o AStar 

