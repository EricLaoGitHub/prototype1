OBJS = main.o SlicingNode.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c 
LFLAGS = -Wall -o
EXEC= main
GPROF= -pg

all: clean main

main: $(OBJS)
	$(CC) $(LFLAGS) $(EXEC) $(OBJS) 
	./$(EXEC)

main.o: main.cpp parameters.h
	$(CC) $(CFLAGS) main.cpp 

SlicingNode.o: SlicingNode.cpp SlicingNode.h 
	$(CC) $(CFLAGS) SlicingNode.cpp 

clean:
	rm -rf *.o $(EXEC) *.txt *~ *.out stats.txt *.ods

valgrind: 
	$(CC) $(CFLAGS) $(DEBUG) main.cpp
	$(CC) $(CFLAGS) $(DEBUG) SlicingNode.cpp 
	$(CC) $(LFLAGS) $(EXEC) $(DEBUG) $(OBJS) -g 
	valgrind --leak-check=full ./$(EXEC)


gprof: 
	$(CC) $(CFLAGS) $(GPROF) main.cpp
	$(CC) $(CFLAGS) $(GPROF) SlicingNode.cpp 
	$(CC) $(LFLAGS) $(EXEC) $(OBJS) $(GPROF) 
	./$(EXEC)
	gprof $(EXEC) gmon.out > stats.txt
