OBJS = main.o SlicingNode.o 
CC = g++
DEBUG = -g 
CFLAGS = -Wall -c $(DEBUG) 
LFLAGS = -Wall -o 
EXEC= main

all: clean main

main: $(OBJS)
	$(CC) $(LFLAGS) $(EXEC) $(OBJS)

main.o: main.cpp parameters.h
	$(CC) $(CFLAGS) main.cpp 

SlicingNode.o: SlicingNode.cpp SlicingNode.h 
	$(CC) $(CFLAGS) SlicingNode.cpp 

clean:
	rm -rf *.o $(EXEC) *.txt *~
