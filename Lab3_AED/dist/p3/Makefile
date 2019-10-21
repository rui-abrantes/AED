#
#  File name: Makefile
#
#  Author: 2019 Fall Semester AED Team
#
#  Release date: 2019/10/16
#
#  Description: Makefile for the individual evaluation lab (LAI) code
#
#  Usage:
#
#     1) To generate the executable file for the program p2-pub, run
#         $ make p2
#
#     2)  To generate the executable file for the program p3-pub, run
#         $ make p3
#
#     3) To clean all object files and the executable file, run
#         $ make clean
#
#     4) Some test run targets are included, e.g. t31
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -g -Wall -ansi


%.o: %.c

######################
## enunciado

enun: LabAval1920_1oS-Publico.tex
	pdflatex LabAval1920_1oS-Publico.tex


######################
## P3

#  Sources
PUBSOURCES3 =  LinkedList.c LinkedList.h filesys.c filesys.h p3-pub.c

#  Objects
PUBOBJECTS3 = LinkedList.o filesys.o p3-pub.o



p3:	p3-pub
p3-pub: $(PUBOBJECTS3)
	$(CC) -g -o $@ $(PUBOBJECTS3)

filesys.o: filesys.h filesys.c
	$(CC) -g -c filesys.c

LinkedList.o: LinkedList.h LinkedList.c
	$(CC) -g -c LinkedList.c

p3-pub.o: defs.h LinkedList.h filesys.h p3-pub.c
	$(CC) -g -c p3-pub.c

clean::
	rm -f *.o core a.out p3-pub pr-priv p2-pub p2-priv *~

depend::
	makedepend $(SOURCES)


# DO NOT DELETE
