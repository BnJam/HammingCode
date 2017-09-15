CC = g++
CFLAGS = -g -W -Wall -std=c++11

all: main

main: main.o
	$(CC) main.o $(CFLAGS) -o main

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS) -o main.o

clean:
	(rm *.o) &
	(rm *~ */*~) &
