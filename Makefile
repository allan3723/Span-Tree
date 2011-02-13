#ache; Cheng, Allan

CC = g++

all: spantree

spantree: spantree.o
	$(CC) -o spantree spantree.o

spantree.o: spantree.cpp classes.h
	$(CC) -o spantree.o -c -O3 -g spantree.cpp

clean:
	rm spantree spantree.o
