CC = g++

CFLAGS = -Wall -g

main: Source.o Graph.o ConSubG.o ReverseSearch.o SimpleForward.o
	$(CC) $(CFLAGS) -o subgraphs Source.o Graph.o ConSubG.o ReverseSearch.o SimpleForward.o

Source.o: Source.cpp Graph.h ConSubG.h ReverseSearch.h SimpleForward.h
	$(CC) $(CFLAGS) -c Source.cpp

Graph.o: Graph.h

ConSubG.o: ConSubG.h

ReverseSearch.o: ReverseSearch.h

SimpleForward.o: SimpleForward.h