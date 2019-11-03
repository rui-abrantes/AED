# AED, last modified abl 2019.04.02
#
# To compile prog:
#    make
# To run tests:
#    make t
#
# NOTE:
# In case of trouble with the shell for loop, GNU Make has 'foreach':
#	$(foreach file,$(FILES),./labconn $(file);)
# https://stackoverflow.com/questions/1490949/how-to-write-loop-in-a-makefile
#----------------------------------------------------------------------
#   Compiler, Compiler Flags
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic

#   Sources
SOURCES = word.c orda.c ordb.c

#   Objects  ('Make' automatically compiles .c to .o)
OBJECTS_A = word.o orda.o
OBJECTS_B = word.o ordb.o

orda: $(OBJECTS_A)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_A)

#   must create ordb.c
ordb: $(OBJECTS_B)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_B)

word.o: word.c word.h defs.h
   
orda.o: orda.c word.h defs.h

ordb.o: ordb.c word.h defs.h

clean:
	rm -f *.o *.~ words *.gch


FILES = $(shell ls ../test/*.txt)

VALG = valgrind --leak-check=full

t:
	for F in ${FILES}; do  ./orda $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./orda $${F} ; done;


tt:
	for F in ${FILES}; do  time ./orda $${F} ; done;


# same for ordb
bt:
	for F in ${FILES}; do  ./ordb $${F} ; done;


btv:
	for F in ${FILES}; do ${VALG} ./ordb $${F} ; done;


btt:
	for F in ${FILES}; do  time ./ordb $${F} ; done;
