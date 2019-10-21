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
## P2

#  Sources
PUBSOURCES2 =  p2-pub.c

#  Objects
PUBOBJECTS2 = p2-pub.o


p2:	$(PUBSOURCES2)
p2-pub: $(PUBOBJECTS2)
	$(CC) -g -o $@ $(PUBOBJECTS2)

p2-pub.o: $(PUBSOURCES2)
	$(CC) -g -c $(PUBSOURCES2)

p2-pub-vg: p2-pub
	valgrind --leak-check=full ./p2-pub p2.test


clean::
	rm -f *.o core a.out p2-pub *~

depend::
	makedepend $(SOURCES)


# DO NOT DELETE
