#Makefile for Project 6
CC = gcc
CFLAGS = -Wall -std=c99 -g

#driver executable and its dependencies
driver: input.o map.o integer.o text.o vtype.o
driver.o: input.h map.h vtype.h integer.h text.h

#object file dependencies
input.o: input.h
map.o: map.h vtype.h
integer.o: integer.h vtype.h
text.o: text.h vtype.h
vtype.o: vtype.h

#test component dependencies
mapTest: map.o vtype.o integer.o text.o
textTest: text.o vtype.o

clean:
	rm -f *.o
	rm -f output.txt
	rm -f *Test
	rm -f driver
	rm -f input
	rm -f map
	rm -f integer
	rm -f text
	rm -f vtype