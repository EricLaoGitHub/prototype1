OBJS = main.o slicingNode.o
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

slicingNode.o: slicingNode.cpp slicingNode.h
	$(CC) $(CFLAGS) slicingNode.cpp 
clean:
	rm -rf *.o $(EXEC)
