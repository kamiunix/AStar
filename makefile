CC=g++

CFLAGS=-g

all: Node.o findpath.o
	$(CC) $(CFLAGS) -o findpath Node.o findpath.o

Node.o: Node.cpp
	$(CC) $(CFLAGS) -c Node.cpp

findpath.o: findpath.cpp	
	$(CC) $(CFLAGS) -c findpath.cpp


clean: 
	-rm findpath.o Node.o findpath

