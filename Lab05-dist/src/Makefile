# AED 2019-2020, sem.1
# Makefile for Trees lab
# Last edit: abl 2019.11.12
#-----------------------------------------------------------------------
#   Compiler Flags

CFLAGS= -g -Wall -ansi -pedantic

lab05: lab05.o tree.o queue.o
	gcc $(CFLAGS) -o lab05 tree.o lab05.o queue.o

queue.o: queue.c queue.h tree.h
	gcc $(CFLAGS) -c queue.c

lab05.o: lab05.c tree.h queue.h
	gcc $(CFLAGS) -c lab05.c

tree.o: tree.c tree.h queue.h
	gcc $(CFLAGS) -c tree.c

clean:
	rm -f *.o *.~ lab05 *.gch
